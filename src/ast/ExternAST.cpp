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
            CompileError e("Unknown flag:" + flag.tokenValue);
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
    Token token = unit->next_tok();
    if (token.type != tok_syntax || token.tokenValue != ";") {
        CompileError e("丟失分号: \"" + token.dump() + "\" 前");
        throw e;
    }

    return new ExternAST(unit, proto);
}

std::string ExternAST::getDemangledName() { return proto->demangledName; }

llvm::Function *ExternAST::Codegen()
{
    proto->Codegen();
    return 0;
}
