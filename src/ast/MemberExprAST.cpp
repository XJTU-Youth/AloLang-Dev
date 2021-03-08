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
#include "VariableExprAST.h"

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
    type.clear();

    std::vector<llvm::Value *> result;
    std::vector<llvm::Value *> bases = LHS->Codegen(builder);
    if (bases.size() != 1) {
        CompileError e("Multi/Void type found.");
        throw e;
    }

    llvm::Value *          base      = bases[0];
    ClassAST *             baseClass = unit->classes[LHS->type[0]->baseClass];
    std::vector<TypeAST *> genericTypes = LHS->type[0]->genericTypes;
    if (isPointer) {
        baseClass    = unit->classes[LHS->type[0]->pointee->baseClass];
        base         = builder->CreateLoad(base);
        genericTypes = LHS->type[0]->pointee->genericTypes;
    }
    auto memberAST = baseClass->members.find(member);
    if (memberAST == baseClass->members.end()) {
        CompileError e("Member " + member + " not found.");
        throw e;
    }
    unsigned int index =
        std::distance(std::begin(baseClass->members), memberAST);

    type.push_back(baseClass->getRealType(
        baseClass->members[member]->variableType, genericTypes));
    llvm::Value *member = builder->CreateExtractValue(base, {index});
    result.push_back(member);
    return result;
}

llvm::Value *MemberExprAST::getAlloca(llvm::IRBuilder<> *builder)
{
    type.clear();
    ExprAST *              curAST = this;
    std::vector<ExprAST *> chain;
    llvm::Value *          pointer;
    bool                   pointerFlag = false;
    while (true) {
        chain.push_back(curAST);
        if (MemberExprAST *v = dynamic_cast<MemberExprAST *>(curAST)) {
            if (v->isPointer) {
                pointerFlag = true;
                chain.push_back(v->LHS);
                break;
            }
            curAST = v->LHS;
        } else if (VariableExprAST *v =
                       dynamic_cast<VariableExprAST *>(curAST)) {
            pointerFlag = false;
            break;
        } else {
            CompileError e("Unknown AST.");
            throw e;
        }
    }
    std::string curType, startType;
    if (pointerFlag) {
        ExprAST *start = chain[chain.size() - 1];
        pointer        = start->Codegen(builder)[0];
        curType        = start->type[0]->pointee->baseClass;
        startType      = start->type[0]->pointee->getName();
    } else {
        VariableExprAST *start =
            dynamic_cast<VariableExprAST *>(chain[chain.size() - 1]);
        pointer = start->getAlloca(builder);
        if (pointer == nullptr) {
            CompileError e("No memory allocaed");
            throw e;
        }
        curType   = start->type[0]->baseClass;
        startType = start->type[0]->getName();
    }
    std::vector<unsigned int> idx;
    for (int i = chain.size() - 2; i >= 0; i--) {
        MemberExprAST *v         = dynamic_cast<MemberExprAST *>(chain[i]);
        std::string    member    = v->member;
        ClassAST *     baseClass = unit->classes[curType];
        if (baseClass == nullptr) {
            CompileError e("Class " + curType + " not found.");
            throw e;
        }
        auto memberAST = baseClass->members.find(member);
        if (memberAST == baseClass->members.end()) {
            CompileError e("Member" + member + " not found.");
            throw e;
        }
        unsigned int index =
            std::distance(std::begin(baseClass->members), memberAST);
        idx.push_back(index);
        curType = baseClass->members[member]->variableType->getName();
    }
    std::vector<llvm::Value *> idxl;
    llvm::IntegerType *itype = llvm::IntegerType::get(*unit->context, 32);

    idxl.push_back(llvm::ConstantInt::get(itype, 0, true));
    for (unsigned int pid : idx) {
        idxl.push_back(llvm::ConstantInt::get(itype, pid, true));
    }
    if (idx.size() != 0) {
        auto typeAST = unit->types.find(startType);

        pointer = builder->CreateGEP(typeAST->second, pointer, idxl);
    }
    type.push_back(new TypeAST(unit, curType));

    return pointer;
}
