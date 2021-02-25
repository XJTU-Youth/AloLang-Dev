/*
 * MemberExprAST.cpp
 *
 *  Created on: Feb 25, 2021
 *      Author: zbc
 */

#include "MemberExprAST.h"
#include "../CompileError.hpp"
#include "ClassAST.h"
#include "TypeAST.h"

MemberExprAST::MemberExprAST(CompileUnit *unit, ExprAST *LHS,
                             std::string member)
    : ExprAST(unit)
{
    this->LHS    = LHS;
    this->member = member;
}

MemberExprAST::~MemberExprAST()
{
    // TODO Auto-generated destructor stub
}

MemberExprAST *MemberExprAST::ParseMemberExprAST(CompileUnit * unit,
                                                 CodeBlockAST *codeblock,
                                                 ExprAST *     LHS)
{
    Token token = unit->next_tok();
    if (token.type != tok_identifier) {
        CompileError e("Expected identifier");
        throw e;
    }
    MemberExprAST *result = new MemberExprAST(unit, LHS, token.tokenValue);
    unit->next_tok();
    return result;
}

std::vector<llvm::Value *> MemberExprAST::Codegen(llvm::IRBuilder<> *builder)
{
    std::vector<llvm::Value *> result;
    std::vector<llvm::Value *> bases = LHS->Codegen(builder);
    if (bases.size() != 1) {
        CompileError e("Multi/Void type found.");
        throw e;
    }

    llvm::Value *base = bases[0];

    ClassAST *   baseClass = unit->classes[LHS->type[0]->name];
    unsigned int index     = std::distance(std::begin(baseClass->members),
                                       baseClass->members.find(member));
    type.push_back(baseClass->members[member]->variableType);
    llvm::Value *member = builder->CreateExtractValue(base, {index});
    result.push_back(member);
    return result;
}
