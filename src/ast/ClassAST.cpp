/*
 * ClassAST.cpp
 *
 *  Created on: Feb 22, 2021
 *      Author: zbc
 */

#include "ClassAST.h"
#include "../CompileError.hpp"
#include "TypeAST.h"

ClassAST::ClassAST(CompileUnit *unit, const std::string &className,
                   std::vector<VariableDefExprAST *> members)
    : BaseAST(unit)
{
    this->className = className;
    this->members   = members;
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
    std::vector<VariableDefExprAST *> members;
    while (true) {
        token = unit->next_tok();
        //解析成员方法，成员变量
        if (token.type == tok_syntax && token.tokenValue == "}") {
            break;
        }
        VariableDefExprAST *memberDef =
            VariableDefExprAST::ParseVar(unit, nullptr);
        members.push_back(memberDef);
    }
    token              = unit->next_tok();
    ClassAST *classAST = new ClassAST(unit, className, members);
    return classAST;
}

llvm::Type *ClassAST::Codegen()
{
    llvm::StructType *llvm_S =
        llvm::StructType::create(*unit->context, className);
    std::vector<llvm::Type *> sMembers;
    for (VariableDefExprAST *member : members) {
        sMembers.push_back(member->variableType->Codegen());
    }
    llvm_S->setBody(sMembers);
    return llvm_S;
}
