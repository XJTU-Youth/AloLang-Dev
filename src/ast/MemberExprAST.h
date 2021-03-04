/*
 * MemberExprAST.h
 *
 *  Created on: Feb 25, 2021
 *      Author: zbc
 */

#ifndef SRC_AST_MEMBEREXPRAST_H_
#define SRC_AST_MEMBEREXPRAST_H_

#include "ExprAST.h"

class MemberExprAST : public ExprAST
{
  public:
    MemberExprAST(CompileUnit *unit, ExprAST *LHS, std::string member,
                  bool isPointer);
    virtual ~MemberExprAST();
    std::vector<llvm::Value *> Codegen(llvm::IRBuilder<> *builder);
    ExprAST *                  LHS;
    std::string                member;
    bool                       isPointer;
};

#endif /* SRC_AST_MEMBEREXPRAST_H_ */
