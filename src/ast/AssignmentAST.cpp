/*
 * AssignmentAST.cpp
 *
 *  Created on: Feb 17, 2021
 *      Author: zbc
 */

#include "AssignmentAST.h"
#include "../CompileError.hpp"
#include "ClassAST.h"
#include "CodeBlockAST.h"
#include "MemberExprAST.h"
#include "TypeAST.h"
#include "VariableExprAST.h"

AssignmentAST::AssignmentAST(CompileUnit *unit, std::vector<ExprAST *> LHS,
                             ExprAST *RHS)
    : ExprAST(unit)
{
    this->LHS = LHS;
    this->RHS = RHS;
}

AssignmentAST::~AssignmentAST()
{
    // TODO Auto-generated destructor stub
}

AssignmentAST *AssignmentAST::ParseAssignment(CompileUnit * unit,
                                              CodeBlockAST *codeblock)
{
    std::vector<ExprAST *> LHS; //左侧变量
    Token                  token = *unit->icurTok;

    while (true) {
        token = *unit->icurTok;
        if (token.type == tok_identifier) {
            VariableExprAST *var =
                new VariableExprAST(unit, codeblock, token.tokenValue);
            if ((unit->icurTok + 1)->type == tok_syntax &&
                (unit->icurTok + 1)->tokenValue == ".") {
                unit->next_tok();
                LHS.push_back(
                    MemberExprAST::ParseMemberExprAST(unit, codeblock, var));
            } else {
                LHS.push_back(var);
                token = unit->next_tok();
            }
        } else if (token.type == tok_syntax) {
            if (token.tokenValue == "=") {
                break;
            }
            token = unit->next_tok();
        }
    }
    unit->next_tok();
    return new AssignmentAST(unit, LHS,
                             ExprAST::ParseExpression(unit, codeblock, false));
}

std::vector<llvm::Value *> AssignmentAST::Codegen(llvm::IRBuilder<> *builder)
{
    std::vector<llvm::Value *> RHSV = RHS->CodegenChain(builder);
    if (RHSV.size() != LHS.size()) {
        CompileError e("the length of expression isn't equal.");
        throw e;
    }
    for (unsigned int i = 0; i < LHS.size(); i++) {
        if (MemberExprAST *v = dynamic_cast<MemberExprAST *>(LHS[i])) {
            std::vector<llvm::Value *> result;
            std::vector<llvm::Value *> bases = v->LHS->Codegen(builder);
            if (bases.size() != 1) {
                CompileError e("Multi/Void type found.");
                throw e;
            }

            llvm::Value *base = bases[0];

            ClassAST *   baseClass = unit->classes[v->LHS->type[0]->name];
            unsigned int index =
                std::distance(std::begin(baseClass->members),
                              baseClass->members.find(v->member));
            llvm::Value *av =
                builder->CreateInsertValue(base, RHSV[i], {index});
            if (VariableExprAST *basev =
                    dynamic_cast<VariableExprAST *>(v->LHS)) {
                builder->CreateStore(av, basev->getAlloca());
            } else {
                CompileError e("Base isn't variable.");
                throw e;
            }
        } else if (VariableExprAST *v =
                       dynamic_cast<VariableExprAST *>(LHS[i])) {
            builder->CreateStore(RHSV[i],
                                 v->getAlloca()); // todo:对函数参数赋值
        }
    }
    return std::vector<llvm::Value *>();
}
