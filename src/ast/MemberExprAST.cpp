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
#include "UnaryExprAST.h"
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
        CompileError e("Multi/Void type found.", source);
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
    //查找变量位置
    unsigned int index     = 0;
    bool         foundFlag = false;
    for (; index < baseClass->omembers.size(); index++) {
        if (baseClass->omembers[index]->idName == this->member) {
            foundFlag = true;
            break;
        }
    }
    if (!foundFlag) {
        CompileError e("Member " + this->member + " not found.", source);
        throw e;
    }

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
        } else if (UnaryExprAST *v = dynamic_cast<UnaryExprAST *>(curAST)) {
            if (v->op == "*") {
                pointerFlag = true;
                chain.push_back(v->operand);
                break;
            } else {
                CompileError e("Unknown AST.", source);
                throw e;
            }
            break;
        } else {
            CompileError e("Unknown AST.", source);
            throw e;
        }
    }
    TypeAST *curType, *startType;
    if (pointerFlag) {
        ExprAST *start = chain[chain.size() - 1];
        pointer        = start->Codegen(builder)[0];
        curType        = start->type[0]->pointee;
        startType      = start->type[0]->pointee;
    } else {
        VariableExprAST *start =
            dynamic_cast<VariableExprAST *>(chain[chain.size() - 1]);
        pointer = start->getAlloca(builder);
        if (pointer == nullptr) {
            CompileError e("No memory allocaed", source);
            throw e;
        }
        curType   = start->type[0];
        startType = start->type[0];
    }
    std::vector<unsigned int> idx;
    for (int i = chain.size() - 2; i >= 0; i--) {
        MemberExprAST *v         = dynamic_cast<MemberExprAST *>(chain[i]);
        std::string    cmember   = v->member;
        ClassAST *     baseClass = unit->classes[curType->baseClass];
        if (baseClass == nullptr) {
            CompileError e("Class " + curType->baseClass + " not found.",
                           source);
            throw e;
        }
        unsigned int index     = 0;
        bool         foundFlag = false;
        for (; index < baseClass->omembers.size(); index++) {
            if (baseClass->omembers[index]->idName == cmember) {
                foundFlag = true;
                break;
            }
        }
        if (!foundFlag) {
            CompileError e("Member " + cmember + " not found.", source);
            throw e;
        }
        idx.push_back(index);
        curType = baseClass->members[cmember]->variableType;
        curType = baseClass->getRealType(curType);
    }
    std::vector<llvm::Value *> idxl;
    llvm::IntegerType *itype = llvm::IntegerType::get(*unit->context, 32);

    idxl.push_back(llvm::ConstantInt::get(itype, 0, true));
    for (unsigned int pid : idx) {
        idxl.push_back(llvm::ConstantInt::get(itype, pid, true));
    }
    if (idx.size() != 0) {
        auto typeAST = unit->types.find(startType->getName());

        pointer = builder->CreateGEP(typeAST->second, pointer, idxl);
    }
    type.push_back(curType);

    return pointer;
}
