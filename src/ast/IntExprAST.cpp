/*
 * NumberExprAST.cpp
 *
 *  Created on: Aug 28, 2020
 *      Author: zbc
 */

#include "IntExprAST.h"
#include "TypeAST.h"
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>

IntExprAST::IntExprAST(CompileUnit *unit, long long val) : ExprAST(unit)
{
    this->val = val;
    this->type.push_back(new TypeAST(unit, "int"));
}

IntExprAST::~IntExprAST()
{
    // TODO Auto-generated destructor stub
}

std::vector<llvm::Value *> IntExprAST::Codegen(llvm::IRBuilder<> *builder)
{
    std::vector<llvm::Value *> result;
    llvm::IntegerType *rtype = llvm::IntegerType::get(*unit->context, 64);
    llvm::ConstantInt *res   = llvm::ConstantInt::get(rtype, val, true);
    result.push_back(res);
    if (subExpr != nullptr) {
        std::vector<llvm::Value *> subResult = subExpr->Codegen(builder);
        std::vector<TypeAST *>     subType   = subExpr->type;
        result.insert(result.end(), subResult.begin(), subResult.end());
        type.insert(type.end(), subType.begin(), subType.end());
    }
    return result;
}
