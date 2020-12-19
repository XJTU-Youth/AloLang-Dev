/*
 * code_parser.cpp
 *
 *  Created on: Aug 10, 2020
 *      Author: zbc
 */
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Verifier.h>
#include <ast/ExprAST.h>
#include <ast/FunctionAST.h>
#include <string>
#include <sstream>
#include <utils.h>
#include <fstream>
#include <iostream>

double numVal;
std::string identifierStr;
int curTok;

