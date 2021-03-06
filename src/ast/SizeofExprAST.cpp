/*
 * SizeofExprAST.cpp
 *
 *  Created on: Mar 6, 2021
 *      Author: zbc
 */

#include "SizeofExprAST.h"
#include "IntExprAST.h"
#include "TypeAST.h"

SizeofExprAST::SizeofExprAST(CompileUnit *unit, TypeAST *Stype) : ExprAST(unit)
{
    this->Stype = Stype;
}

SizeofExprAST::~SizeofExprAST()
{
    // TODO Auto-generated destructor stub
}

std::vector<llvm::Value *> SizeofExprAST::Codegen(llvm::IRBuilder<> *builder)
{
    std::vector<llvm::Value *> result;
    this->type.push_back(new TypeAST(unit, "int"));
    llvm::DataLayout *TD   = new llvm::DataLayout(unit->module);
    int               size = TD->getTypeAllocSize(Stype->Codegen());
    result.push_back((new IntExprAST(unit, size))->Codegen(builder)[0]);
    return result;
}
