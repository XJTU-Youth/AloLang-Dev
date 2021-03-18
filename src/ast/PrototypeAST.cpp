/*
 * PrototypeAST.cpp
 *
 *  Created on: Dec 21, 2020
 *      Author: zbc
 */

#include "PrototypeAST.h"
#include "../CompileError.hpp"
#include "../utils.h"
#include "ClassAST.h"
#include "TypeAST.h"
#include <iostream>

PrototypeAST::PrototypeAST(
    CompileUnit *unit, const std::string &name,
    const std::vector<std::pair<TypeAST *, std::string>> &args,
    const std::vector<TypeAST *> &returnTypes, ClassAST *parentClass)
    : BaseAST(unit)
{
    this->name           = name;
    this->args           = args;
    this->returnDirectly = false;
    this->returnTypes    = returnTypes;
    this->parentClass    = parentClass;
}

PrototypeAST::~PrototypeAST()
{
    // TODO Auto-generated destructor stub
}

PrototypeAST *PrototypeAST::ParsePrototype(CompileUnit *unit, bool hasBody,
                                           ClassAST *parentClass)
{
    std::vector<std::pair<TypeAST *, std::string>> args;
    Token                                          token  = unit->next_tok();
    TokenSource                                    source = token.source;
    if (token.type != tok_identifier) {
        std::cerr << "error1" << std::endl;
        // TODO:异常处理
    }

    std::string FnName = token.tokenValue;
    token              = unit->next_tok();

    if (token.type != tok_syntax || token.tokenValue != "(") {
        std::cerr << "error2" << std::endl;
        // TODO:异常处理
    }

    while (true) {
        token = unit->next_tok();
        if (token.type == tok_syntax && token.tokenValue == ",") {
            continue;
        }
        if (token.type == tok_syntax && token.tokenValue == ")") {
            unit->next_tok();
            break;
        }
        TypeAST *type = TypeAST::ParseType(unit);
        // todo:错误处理
        token                                  = *unit->icurTok;
        std::string                       name = token.tokenValue;
        std::pair<TypeAST *, std::string> pair;
        type->inClass = parentClass;
        pair.first    = type;
        pair.second   = name;
        args.push_back(pair);
    }
    if (token.type != tok_syntax || token.tokenValue != ")") {
        std::cout << "error3" << std::endl;
        // TODO:异常处理
    }

    token = *(unit->icurTok); // -> or ; or {
    std::vector<TypeAST *> returnTypes;
    if (token.type == tok_syntax && token.tokenValue == "->") {
        unit->next_tok();
        int bc = 0;
        while (true) {
            // todo:大量异常处理
            token = *unit->icurTok;
            if (token.type == tok_syntax) {
                if (token.tokenValue == "(") {
                    bc++;
                    unit->next_tok();
                    continue;
                } else if (token.tokenValue == ")") {
                    bc--;
                    unit->next_tok();
                    continue;
                } else if (token.tokenValue == ",") {
                    unit->next_tok();
                    continue;
                } else {
                    break;
                }
            }
            TypeAST *returnType = TypeAST::ParseType(unit);
            returnType->inClass = parentClass;
            returnTypes.push_back(returnType);
        }
    } else {
        if (token.tokenValue == "{") {
            if (!hasBody) {
                CompileError e("Unexpected function body", token.source);
                throw e;
            }
        }
        if (token.tokenValue == ";") {
            if (hasBody) {
                CompileError e("Unexpected ;", token.source);
                throw e;
            }
        }
    }
    PrototypeAST *retV =
        new PrototypeAST(unit, FnName, args, returnTypes, parentClass);
    retV->source = source;
    return retV;
}

llvm::Function *PrototypeAST::Codegen(std::vector<TypeAST *> igenericTypes)
{
    std::vector<TypeAST *> argStr;
    for (std::pair<TypeAST *, std::string> pair : args) {
        if (parentClass == nullptr) {
            argStr.push_back(pair.first);
        } else {
            argStr.push_back(
                parentClass->getRealType(pair.first, igenericTypes));
        }
    }
    std::string demangledName;
    if (name != "main") {
        if (parentClass == nullptr) {
            demangledName = demangle(name, argStr);
        } else {
            demangledName = demangle(
                name, argStr, parentClass->getRealNameForMangle(igenericTypes));
        }
    } else {
        demangledName = "main";
    }

    std::vector<llvm::Type *> llvmArgs;
    for (int i = 0; i < argStr.size(); i++) {
        llvmArgs.push_back(argStr[i]->Codegen());
    }
    llvm::Type *returnType;
    if (returnDirectly) {
        if (returnTypes.size() > 1) {
            CompileError e(
                "Prototype with \"S\" flag returned more than one values.",
                source);
            throw e;
        } else if (returnTypes.size() == 0) {
            returnType = llvm::Type::getVoidTy(*unit->context);
        } else {
            returnType = returnTypes[0]->Codegen();
        }

    } else {
        if (name != "main") {
            llvm::StructType *llvm_S = llvm::StructType::create(*unit->context);
            std::vector<llvm::Type *> members;
            for (TypeAST *member : returnTypes) {
                members.push_back(member->Codegen());
            }
            llvm_S->setBody(members);
            returnType = llvm_S;
        } else {
            returnType = llvm::IntegerType::get(*unit->context, 32);
        }
    }

    llvm::FunctionType *FT =
        llvm::FunctionType::get(returnType, llvmArgs, false);
    llvm::Function *F = llvm::Function::Create(
        FT, llvm::GlobalValue::ExternalLinkage, demangledName, unit->module);

    // If F conflicted, there was already something named 'Name'.  If it has a
    // body, don't allow redefinition or reextern.
    // todo:重定义异常处理
    /*if (F->getName() != Name) {
     // Delete the one we just made and get the existing one.
     F->eraseFromParent();
     F = TheModule->getFunction(Name);

     // If F already has a body, reject this.
     if (!F->empty()) {
     ErrorF("redefinition of function");
     return 0;
     }

     // If F took a different number of args, reject.
     if (F->arg_size() != Args.size()) {
     ErrorF("redefinition of function with different # args");
     return 0;
     }
     }*/
    return F;
}
