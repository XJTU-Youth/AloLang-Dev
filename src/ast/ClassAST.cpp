/*
 * ClassAST.cpp
 *
 *  Created on: Feb 22, 2021
 *      Author: zbc
 */

#include "ClassAST.h"
#include "../CompileError.hpp"

ClassAST::ClassAST(CompileUnit *unit) : BaseAST(unit)
{
    // TODO Auto-generated constructor stub
}

ClassAST::~ClassAST()
{
    // TODO Auto-generated destructor stub
}

ClassAST *ClassAST::ParseClass(CompileUnit *unit)
{
    Token token = unit->next_tok();
    if (token.type != tok_identifier) {
        CompileError e("Expected identifier");
        throw e;
    }
    std::string className = token.tokenValue;
    std::cout << std::left << std::setw(35)
              << "Class definition found:" << className << std::endl;
    token = unit->next_tok();
    if (token.type != tok_syntax || token.tokenValue != "{") {
        CompileError e("Expected {");
        throw e;
    }
    while (true) {
        token = unit->next_tok();
        //解析成员方法，成员变量
        if (token.type == tok_syntax && token.tokenValue == "}") {
            break;
        }
    }
    token              = unit->next_tok();
    ClassAST *classAST = new ClassAST(unit);
    return classAST;
}

llvm::Type *ClassAST::Codegen() { return nullptr; }
