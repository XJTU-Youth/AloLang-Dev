/*
 * CodeBlockAST.h
 *
 *  Created on: Dec 27, 2020
 *      Author: zbc
 */

#ifndef COMPILER_AST_CODEBLOCKAST_H_
#define COMPILER_AST_CODEBLOCKAST_H_

#include "BaseAST.h"
#include "ExprAST.h"
#include "llvm/IR/Instructions.h"
#include <map>

class VariableDefExprAST;
class CodeBlockAST : public BaseAST
{
  public:
    CodeBlockAST(CompileUnit *unit, std::vector<ExprAST *> exprs,
                 std::string name, CodeBlockAST *parent = nullptr);
    virtual ~CodeBlockAST();
    static CodeBlockAST *
                      ParseCodeBlock(CompileUnit *unit, std::string name,
                                     CodeBlockAST *                          parent = nullptr,
                                     const std::vector<VariableDefExprAST *> args =
                                         std::vector<VariableDefExprAST *>());
    llvm::BasicBlock *Codegen(llvm::Function *function);

    llvm::IRBuilder<> *    builder;
    std::vector<ExprAST *> body;
    std::map<std::string, std::pair<std::string, llvm::AllocaInst *>>
                      namedValues; // Codegen阶段用
    std::string       name;
    CodeBlockAST *    parent;
    llvm::BasicBlock *endBB;
};

#endif /* COMPILER_AST_CODEBLOCKAST_H_ */
