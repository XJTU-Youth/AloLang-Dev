/*
 * CallExprAST.cpp
 *
 *  Created on: Dec 24, 2020
 *      Author: zbc
 */

#include "CallExprAST.h"
#include "../CompileError.hpp"

#include <iostream>

#include "../utils.h"

CallExprAST::CallExprAST(CompileUnit *unit, const std::string &callee,
                         std::vector<ExprAST *> &args)
    : ExprAST(unit)
{
    this->callee = callee;
    this->args   = args;
    std::cout << std::left << std::setw(35)
              << "Function call found:" << this->callee << std::endl;
}

CallExprAST::~CallExprAST()
{
    // TODO Auto-generated destructor stub
}

llvm::Value *CallExprAST::Codegen(llvm::IRBuilder<> *builder)
{
    std::vector<llvm::Value *> argsV;

    for (unsigned i = 0, e = args.size(); i != e; ++i) {
        argsV.push_back(args[i]->Codegen(builder));
    }

    std::vector<std::string> argStr;
    for (ExprAST *ast : args) {
        argStr.push_back(ast->type);
    }
    std::string dname = demangle(callee, argStr);
    if (callee == "main") {
        dname = "main";
    }

    llvm::Function *CalleeF = unit->module->getFunction(dname);
    if (CalleeF == 0) {
        CompileError e("Function " + dname + " not found");
        throw e;
    }

    return builder->CreateCall(CalleeF, argsV);
}
