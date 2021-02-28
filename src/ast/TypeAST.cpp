/*
 * TypeAST.cpp
 *
 *  Created on: Feb 16, 2021
 *      Author: zbc
 */

#include "TypeAST.h"
#include "../CompileError.hpp"
#include "CompileUnit.h"

TypeAST::TypeAST(CompileUnit *unit, std::string baseClass,
                 std::vector<TypeAST *> genericTypes)
    : BaseAST(unit)
{
    this->baseClass    = baseClass;
    this->genericTypes = genericTypes;
    //生成name
    this->name = baseClass;
    if (genericTypes.size() != 0) {
        this->name += "<";
        for (unsigned int i = 0; i < genericTypes.size() - 1; i++) {
            this->name += genericTypes[i]->name + ",";
        }
        this->name += genericTypes[genericTypes.size() - 1]->name + ">";
    }
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
    std::string baseClass = token.tokenValue;

    token = unit->next_tok();
    if (token.type == tok_syntax && token.tokenValue == "<") {
        std::vector<TypeAST *> genericTypes;
        unit->next_tok();
        while (!(token.type == tok_syntax && token.tokenValue == ">")) {
            genericTypes.push_back(TypeAST::ParseType(unit));
            token = *unit->icurTok;
        }
        unit->next_tok();
        TypeAST *result = new TypeAST(unit, baseClass, genericTypes);
        return result;
    }
    TypeAST *result = new TypeAST(unit, baseClass);
    return result;
}
