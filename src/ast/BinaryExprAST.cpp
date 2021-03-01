/*
 * BinaryExprAST.cpp
 *
 *  Created on: Feb 12, 2021
 *      Author: zbc
 */

#include "BinaryExprAST.h"
#include "../CompileError.hpp"
#include "ClassAST.h"
#include "MemberExprAST.h"
#include "TypeAST.h"
#include "VariableExprAST.h"

BinaryExprAST::BinaryExprAST(CompileUnit *unit, std::string binOP, ExprAST *LHS,
                             ExprAST *RHS)
    : ExprAST(unit)
{
    this->binOP = binOP;
    this->LHS   = LHS;
    this->RHS   = RHS;
}

BinaryExprAST::~BinaryExprAST()
{
    // TODO Auto-generated destructor stub
}

llvm::Value *
BinaryExprAST::processInnerBinaryOperator(llvm::Value *L, llvm::Value *R,
                                          llvm::IRBuilder<> *builder)
{
    if (LHS->type[0]->name == "int" && RHS->type[0]->name == "int") {
        if (binOP == "+") {
            return builder->CreateAdd(L, R);
        } else if (binOP == "-") {
            return builder->CreateSub(L, R);
        } else if (binOP == "*") {
            return builder->CreateMul(L, R);
        } else if (binOP == "/") {
            TypeAST *    doubleType = new TypeAST(unit, "double");
            llvm::Value *lv = builder->CreateSIToFP(L, doubleType->Codegen());
            llvm::Value *rv = builder->CreateSIToFP(R, doubleType->Codegen());
            return (builder->CreateFDiv(lv, rv));
        } else if (binOP == "%") {
            return builder->CreateSRem(L, R);
        } else if (binOP == "==") {
            return builder->CreateICmpEQ(L, R);
        } else if (binOP == "!=") {
            return builder->CreateICmpNE(L, R);
        } else if (binOP == ">") {
            return builder->CreateICmpSGT(L, R);
        } else if (binOP == "<") {
            return builder->CreateICmpSLT(L, R);
        } else if (binOP == ">=") {
            return builder->CreateICmpSGE(L, R);
        } else if (binOP == "<=") {
            return builder->CreateICmpSLE(L, R);
        }
    } else if (LHS->type[0]->name == "double" &&
               RHS->type[0]->name == "double") {
        if (binOP == "+") {
            return builder->CreateFAdd(L, R);
        } else if (binOP == "-") {
            return builder->CreateFSub(L, R);
        } else if (binOP == "*") {
            return builder->CreateFMul(L, R);
        } else if (binOP == "/") {
            return builder->CreateFDiv(L, R);
        } else if (binOP == "==") {
            return builder->CreateFCmpOEQ(L, R);
        } else if (binOP == "!=") {
            return builder->CreateFCmpONE(L, R);
        } else if (binOP == ">") {
            return builder->CreateFCmpOGT(L, R);
        } else if (binOP == "<") {
            return builder->CreateFCmpOLT(L, R);
        } else if (binOP == ">=") {
            return builder->CreateFCmpOGE(L, R);
        } else if (binOP == "<=") {
            return builder->CreateFCmpOLE(L, R);
        }
    }
    return nullptr;
}
std::vector<llvm::Value *> BinaryExprAST::Codegen(llvm::IRBuilder<> *builder)
{
    std::vector<llvm::Value *> result;

    if (binOP == "=") {
        std::vector<llvm::Value *> RHSV = RHS->CodegenChain(builder);
        std::vector<ExprAST *>     LHS;
        ExprAST *                  curExpr = this->LHS;
        while (curExpr != nullptr) {
            LHS.push_back(curExpr);
            curExpr = curExpr->subExpr;
        }
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
                MemberExprAST *v      = dynamic_cast<MemberExprAST *>(chain[i]);
                std::string    member = v->member;
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
            llvm::IntegerType *        itype =
                llvm::IntegerType::get(*unit->context, 32);

            idxl.push_back(llvm::ConstantInt::get(itype, 0, true));
            for (unsigned int pid : idx) {
                idxl.push_back(llvm::ConstantInt::get(itype, pid, true));
            }
            if (idx.size() != 0) {
                pointer = builder->CreateGEP(start->type[0]->Codegen(), pointer,
                                             idxl);
            }

            builder->CreateStore(RHSV[i], pointer);
        }
    } else {
        std::vector<llvm::Value *> L = LHS->CodegenChain(builder);
        std::vector<llvm::Value *> R = RHS->CodegenChain(builder);
        if (L.size() != 1 || R.size() != 1) {
            CompileError e("Bin Expr length != 1");
            throw e;
        }
        std::string LHStype = LHS->type[0]->name;
        std::string RHStype = RHS->type[0]->name;
        auto operate = unit->binOperators.find({LHStype, RHStype, binOP});
        if (operate == unit->binOperators.end()) {
            CompileError e("Unknown operator " + binOP + "with type " +
                           LHStype + " and " + RHStype);
            throw e;
        }
        this->type.push_back(operate->second.second);
        if (operate->second.first == nullptr) {
            //内置运算符
            result.push_back(processInnerBinaryOperator(L[0], R[0], builder));
        } else {
            //用户定义运算符
            CompileError e("User-def operator not implemented");
            throw e;
        }
    }
    return result;
}
