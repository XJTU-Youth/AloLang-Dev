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
    //内置类型处理
    if (name == "int") {
        return llvm::Type::getInt64Ty(*unit->context);
    } else if (name == "bool") {
        return llvm::Type::getInt1Ty(*unit->context);
    } else {
        //用户定义的类型
        llvm::StructType *llvm_S =
            llvm::StructType::create(*unit->context, name);
        std::vector<llvm::Type *> members;
        for (TypeAST *member : innerType) {
            members.push_back(member->Codegen());
        }
        return llvm_S;
    }
}
