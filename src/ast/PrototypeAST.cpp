/*
 * PrototypeAST.cpp
 *
 *  Created on: Dec 21, 2020
 *      Author: zbc
 */

#include "PrototypeAST.h"
#include "../CompileError.hpp"
#include "../utils.h"
#include "TypeAST.h"

#include <iostream>

PrototypeAST::PrototypeAST(
    CompileUnit *unit, const std::string &name,
    const std::vector<std::pair<TypeAST *, std::string>> &args,
    const std::vector<TypeAST *> &                        returnTypes)
    : BaseAST(unit)
{
    this->name           = name;
    this->args           = args;
    this->returnDirectly = false;
    this->returnTypes    = returnTypes;
    std::vector<TypeAST *> argStr;
    for (std::pair<TypeAST *, std::string> pair : args) {
        argStr.push_back(pair.first);
    }
    if (name != "main") {
        this->demangledName = demangle(name, argStr);
    } else {
        this->demangledName = "main";
    }
}

PrototypeAST::~PrototypeAST()
{
    // TODO Auto-generated destructor stub
}

PrototypeAST *PrototypeAST::ParsePrototype(CompileUnit *unit, bool hasBody)
{
    std::vector<std::pair<TypeAST *, std::string>> args;
    Token                                          token = unit->next_tok();
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
        if (FnName == "main") {
            token = unit->next_tok(); // ).
            break;
        }
        token = *(unit->icurTok + 1);
        if (token.type == tok_syntax && token.tokenValue == ",") {
            token = unit->next_tok();
            continue;
        }
        if (token.type == tok_syntax && token.tokenValue == ")") {
            unit->next_tok();
            break;
        }
        TypeAST *type = TypeAST::ParseType(unit);
        // todo:错误处理
        token                                  = unit->next_tok();
        std::string                       name = token.tokenValue;
        std::pair<TypeAST *, std::string> pair;
        pair.first  = type;
        pair.second = name;
        args.push_back(pair);
    }
    if (token.type != tok_syntax || token.tokenValue != ")") {
        std::cout << "error3" << std::endl;
        // TODO:异常处理
    }

    token = *(unit->icurTok + 1); // -> or ; or {
    std::vector<TypeAST *> returnTypes;
    if (token.type == tok_return_type) {
        unit->next_tok();
        int bc = 0;
        while (true) {
            // todo:大量异常处理
            token = *(unit->icurTok + 1); // identifier.
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
            returnTypes.push_back(TypeAST::ParseType(unit));
        }
    } else {
        if (token.tokenValue == "{") {
            if (!hasBody) {
                CompileError e("Unexpected function body");
                throw e;
            }
        }
        if (token.tokenValue == ";") {
            if (hasBody) {
                CompileError e("Unexpected ;");
                throw e;
            }
        }
    }
    return new PrototypeAST(unit, FnName, args, returnTypes);
}

llvm::Function *PrototypeAST::Codegen()
{
    std::vector<llvm::Type *> llvmArgs;
    for (int i = 0; i < args.size(); i++) {
        llvmArgs.push_back(args[i].first->Codegen());
    }
    llvm::Type *returnType;
    if (returnDirectly) {
        if (returnTypes.size() > 1) {
            CompileError e("return more than one type:");
            throw e;
        } else if (returnTypes.size() == 0) {
            returnType = llvm::Type::getVoidTy(*unit->context);
        } else {
            returnType = returnTypes[0]->Codegen();
        }

    } else {
        returnType = llvm::Type::getVoidTy(*unit->context);
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
    // todo:参数处理
    // Set names for all arguments.

    unsigned Idx = 0;
    for (llvm::Function::arg_iterator AI = F->arg_begin(); Idx != args.size();
         ++AI, ++Idx) {
        AI->setName(args[Idx].second);

        // Add arguments to variable symbol table.
        // NamedValues[args[Idx]] = AI;
    }

    return F;
}
