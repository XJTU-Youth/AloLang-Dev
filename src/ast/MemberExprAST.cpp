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
                             std::string member, bool isPointer)
    : ExprAST(unit)
{
    this->LHS       = LHS;
    this->member    = member;
    this->isPointer = isPointer;
}

MemberExprAST::~MemberExprAST()
{
    // TODO Auto-generated destructor stub
}

std::vector<llvm::Value *> MemberExprAST::Codegen(llvm::IRBuilder<> *builder)
{
    if (isPointer) {
        CompileError e("未实现.");
        throw e;
    }
    std::vector<llvm::Value *> result;
    std::vector<llvm::Value *> bases = LHS->Codegen(builder);
    if (bases.size() != 1) {
        CompileError e("Multi/Void type found.");
        throw e;
    }

    llvm::Value *base = bases[0];

    ClassAST *baseClass = unit->classes[LHS->type[0]->baseClass];
    auto      memberAST = baseClass->members.find(member);
    if (memberAST == baseClass->members.end()) {
        CompileError e("Member " + member + " not found.");
        throw e;
    }
    unsigned int index =
        std::distance(std::begin(baseClass->members), memberAST);

    type.push_back(baseClass->getRealType(
        baseClass->members[member]->variableType, LHS->type[0]->genericTypes));
    llvm::Value *member = builder->CreateExtractValue(base, {index});
    result.push_back(member);
    return result;
}
