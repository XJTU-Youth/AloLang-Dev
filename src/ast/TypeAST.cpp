/*
 * TypeAST.cpp
 *
 *  Created on: Feb 16, 2021
 *      Author: zbc
 */

#include "TypeAST.h"
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
    llvm::StructType *llvm_S = llvm::StructType::create(*unit->context, name);
    std::vector<llvm::Type *> members;
    for (TypeAST *member : innerType) {
        members.push_back(member->Codegen());
    }
    return llvm_S;
}
