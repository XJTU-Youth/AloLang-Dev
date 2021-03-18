/*
 * ExternAST.cpp
 *
 *  Created on: Dec 23, 2020
 *      Author: zbc
 */

#include "ExternAST.h"
#include "../CompileError.hpp"
#include <iostream>

ExternAST::ExternAST(CompileUnit *unit, PrototypeAST *proto) : BaseAST(unit)
{
    this->proto = proto;
}

ExternAST::~ExternAST()
{
    // TODO Auto-generated destructor stub
}

ExternAST *ExternAST::ParseExtern(CompileUnit *unit)
{
    bool C = false;
    bool S = false;
    if ((unit->icurTok + 1)->type == tok_str) {
        Token flag = unit->next_tok();
        if (flag.tokenValue == "S") {
            S = true;
        } else if (flag.tokenValue == "C") {
            C = true;
        } else {
            CompileError e("Unknown flag:" + flag.tokenValue, flag.source);
            throw e;
        }
    }
    unit->next_tok();
    PrototypeAST *proto = PrototypeAST::ParsePrototype(unit, false);
    if (S) {
        proto->returnDirectly = true;
    }
    // todo:对externC的处理
    std::cout << std::left << std::setw(35)
              << "Function extern found:" << proto->name << std::endl;
    Token token = *(unit->icurTok);
    if (token.type != tok_syntax || token.tokenValue != ";") {
        CompileError e("丟失分号: \"" + token.dump() + "\" 前", token.source);
        throw e;
    }
    token = unit->next_tok();

    return new ExternAST(unit, proto);
}

llvm::Function *ExternAST::Codegen() { return proto->Codegen(); }
