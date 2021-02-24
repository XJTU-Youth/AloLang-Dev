/*
 * ReturnExprAST.cpp
 *
 *  Created on: Feb 24, 2021
 *      Author: zbc
 */

#include "ReturnExprAST.h"

ReturnExprAST::ReturnExprAST(CompileUnit *unit) : ExprAST(unit)
{
    returnExpr = nullptr;
    // TODO Auto-generated constructor stub
}

ReturnExprAST::~ReturnExprAST()
{
    // TODO Auto-generated destructor stub
}

ReturnExprAST *ReturnExprAST::ParseReturnExprAST(CompileUnit * unit,
                                                 CodeBlockAST *codeblock)
{
    unit->next_tok();
    ReturnExprAST *result = new ReturnExprAST(unit);
    result->returnExpr    = ExprAST::ParseExpression(unit, codeblock, false);
    return result;
}

llvm::Value *getGEP(llvm::IRBuilder<> &Builder, llvm::Value *Base,
                    llvm::ArrayRef<llvm::Value *> Offset)
{
    return Builder.CreateGEP(
        llvm::cast<llvm::PointerType>(Base->getType()->getScalarType())
            ->getElementType(),
        Base, Offset, "a");
}

std::vector<llvm::Value *> ReturnExprAST::Codegen(llvm::IRBuilder<> *builder)
{
    std::vector<llvm::Value *> returnValue = returnExpr->Codegen(builder);
    llvm::Function *function = builder->GetInsertBlock()->getParent();

    llvm::IRBuilder<> sBuilder(&function->getEntryBlock(),
                               function->getEntryBlock().begin());

    llvm::StructType *sType  = (llvm::StructType *)function->getReturnType();
    llvm::AllocaInst *alloca = sBuilder.CreateAlloca(sType);
    std::vector<llvm::Value *> processedValue;
    for (llvm::Value *value : returnValue) {
        builder->CreateStore(value, getGEP(*builder, alloca, processedValue));
        processedValue.push_back(value);
    }
    builder->CreateRet(builder->CreateLoad(alloca));
    return std::vector<llvm::Value *>();
}
