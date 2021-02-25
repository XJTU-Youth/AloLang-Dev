/*
 * TypeAST.cpp
 *
 *  Created on: Feb 16, 2021
 *      Author: zbc
 */

#include "TypeAST.h"
#include "../CompileError.hpp"
#include "CompileUnit.h"

TypeAST::TypeAST(CompileUnit *unit, std::string name) : BaseAST(unit)
{
    this->name = name;
}

TypeAST::~TypeAST()
{
    // TODO Auto-generated destructor stub
}
llvm::Type *TypeAST::Codegen()
{
    auto typeAST = unit->types.find(name);
    if (typeAST == unit->types.end()) {
        CompileError e("can't find type:" + name);
        throw e;
    }
    return typeAST->second;
}

TypeAST *TypeAST::ParseType(CompileUnit *unit)
{
    Token token = *unit->icurTok;
    if (token.type != tok_identifier) {
        CompileError e("Expected type but got " + token.dump());
        throw e;
    }
    TypeAST *result = new TypeAST(unit, token.tokenValue);
    token           = unit->next_tok();
    return result;
}
