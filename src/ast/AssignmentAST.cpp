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
    Token                  token  = *unit->icurTok;
    ExprAST *              curVar = nullptr;
    while (true) {
        token = *unit->icurTok;
        if (token.type == tok_identifier) {
            curVar = new VariableExprAST(unit, codeblock, token.tokenValue);
            unit->next_tok();
        }
        if (token.type == tok_syntax) {
            if (curVar == nullptr) {
                CompileError e("Expected variable before assignment");
                throw e;
            }
            if (token.tokenValue == "=") {
                LHS.push_back(curVar);
                curVar = nullptr;
                break;
            } else if (token.tokenValue == ",") {
                unit->next_tok();
                LHS.push_back(curVar);
                curVar = nullptr;
            } else if (token.tokenValue == ".") {
                curVar =
                    MemberExprAST::ParseMemberExprAST(unit, codeblock, curVar);
            }
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
        ExprAST *              curAST = LHS[i];
        std::vector<ExprAST *> chain;
        while (true) {
            chain.push_back(curAST);
            if (MemberExprAST *v = dynamic_cast<MemberExprAST *>(curAST)) {
                curAST = v->LHS;
            } else if (VariableExprAST *v =
                           dynamic_cast<VariableExprAST *>(curAST)) {
                break;
            } else {
                CompileError e("Unknown AST.");
                throw e;
            }
        }
        VariableExprAST *start =
            dynamic_cast<VariableExprAST *>(chain[chain.size() - 1]);
        llvm::Value *             pointer = start->getAlloca();
        std::vector<unsigned int> idx;
        std::string               curType = start->type[0]->baseClass;
        for (int i = chain.size() - 2; i >= 0; i--) {
            MemberExprAST *v         = dynamic_cast<MemberExprAST *>(chain[i]);
            std::string    member    = v->member;
            ClassAST *     baseClass = unit->classes[curType];
            auto           memberAST = baseClass->members.find(member);
            if (memberAST == baseClass->members.end()) {
                CompileError e("Member" + member + " not found.");
                throw e;
            }
            unsigned int index =
                std::distance(std::begin(baseClass->members), memberAST);
            idx.push_back(index);
            curType = baseClass->members[member]->variableType->name;
        }
        std::vector<llvm::Value *> idxl;
        llvm::IntegerType *itype = llvm::IntegerType::get(*unit->context, 32);

        idxl.push_back(llvm::ConstantInt::get(itype, 0, true));
        for (unsigned int pid : idx) {
            idxl.push_back(llvm::ConstantInt::get(itype, pid, true));
        }
        if (idx.size() != 0) {
            pointer =
                builder->CreateGEP(start->type[0]->Codegen(), pointer, idxl);
        }

        builder->CreateStore(RHSV[i], pointer);
    }
    return std::vector<llvm::Value *>();
}
