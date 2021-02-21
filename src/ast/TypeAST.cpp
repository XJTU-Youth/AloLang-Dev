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
    /*
            //用户定义的类型
            llvm::StructType *llvm_S =
                llvm::StructType::create(*unit->context, name);
            std::vector<llvm::Type *> members;
            for (TypeAST *member : innerType) {
                members.push_back(member->Codegen());
            }
            return llvm_S;*/
}

TypeAST *TypeAST::ParseType(CompileUnit *unit)
{
    Token token = unit->next_tok();
    if (token.type != tok_identifier) {
        CompileError e("Expected type but got " + token.dump());
        throw e;
    }
    return nullptr;
}
