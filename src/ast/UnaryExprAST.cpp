/*
 * UnaryExprAST.cpp
 *
 *  Created on: Feb 21, 2021
 *      Author: zbc
 */

#include "UnaryExprAST.h"
#include "../CompileError.hpp"
#include "ClassAST.h"
#include "MemberExprAST.h"
#include "TypeAST.h"
#include "VariableExprAST.h"

UnaryExprAST::UnaryExprAST(CompileUnit *unit, const std::string &op,
                           ExprAST *operand, bool leftop)
    : ExprAST(unit)
{
    this->op      = op;
    this->operand = operand;
    this->leftop  = leftop;
    /*if (op == "!") {
        this->type.push_back(new TypeAST(unit, "bool"));
    } else if (op == "&") {
        this->type.push_back(new TypeAST(unit, "bool"));
    } else {
        CompileError e("一元运算符:" + op + "未实现");
        throw e;
    }*/
}

UnaryExprAST::~UnaryExprAST()
{
    // TODO Auto-generated destructor stub
}

std::vector<llvm::Value *> UnaryExprAST::Codegen(llvm::IRBuilder<> *builder)
{
    std::vector<llvm::Value *> result;
    if (op == "&") {
        if (VariableExprAST *v = dynamic_cast<VariableExprAST *>(operand)) {
            result.push_back(v->getAlloca());
            this->type.push_back(new TypeAST(unit, operand->type[0]));
        } else if (MemberExprAST *v = dynamic_cast<MemberExprAST *>(operand)) {
            llvm::Value *          pointer;
            std::vector<ExprAST *> chain;
            ExprAST *              curAST = operand;
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
            pointer = start->getAlloca();
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
            result.push_back(pointer);
        } else {
            CompileError e("& can only be used with variable");
            throw e;
        }
    } else {
        //值操作
        std::vector<llvm::Value *> Rs = operand->CodegenChain(builder);
        if (Rs.size() != 1) {
            CompileError e("Unary Expr length != 1");
            throw e;
        }

        if (op == "!") {
            this->type.push_back(new TypeAST(unit, "bool"));
            result.push_back(builder->CreateXor(Rs[0], 1));
        } else if (op == "*") {
            if (operand->type[0]->pointee == nullptr) {
                CompileError e("operator * must be used on pointer");
                throw e;
            }
            this->type.push_back(operand->type[0]->pointee);
            result.push_back(builder->CreateLoad(Rs[0]));
        } else {
            CompileError e("一元运算符:" + op + "未实现");
            throw e;
        }
    }
    return result;
}
