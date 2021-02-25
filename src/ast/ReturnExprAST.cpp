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

std::vector<llvm::Value *> ReturnExprAST::Codegen(llvm::IRBuilder<> *builder)
{
    std::vector<llvm::Value *> returnValue = returnExpr->CodegenChain(builder);
    llvm::Function *function = builder->GetInsertBlock()->getParent();

    llvm::IRBuilder<> sBuilder(&function->getEntryBlock(),
                               function->getEntryBlock().begin());

    llvm::StructType *sType  = (llvm::StructType *)function->getReturnType();
    llvm::AllocaInst *alloca = sBuilder.CreateAlloca(sType);
    for (int i = 0; i < returnValue.size(); i++) {
        llvm::IntegerType *type = llvm::IntegerType::get(*unit->context, 32);
        llvm::ConstantInt *res  = llvm::ConstantInt::get(type, i, true);

        llvm::Value *member_ptr = builder->CreateGEP(
            sType, alloca, {llvm::ConstantInt::get(type, 0, true), res});
        builder->CreateStore(returnValue[i], member_ptr);
        // builder->CreateLoad(member_ptr);
    }
    builder->CreateRet(builder->CreateLoad(alloca));
    return std::vector<llvm::Value *>();
}
