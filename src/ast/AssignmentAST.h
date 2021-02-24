/*
 * AssignmentAST.h
 *
 *  Created on: Feb 17, 2021
 *      Author: zbc
 */

#ifndef SRC_AST_ASSIGNMENTAST_H_
#define SRC_AST_ASSIGNMENTAST_H_

#include "ExprAST.h"

class VariableExprAST;
class AssignmentAST : public ExprAST
{
  public:
    AssignmentAST(CompileUnit *unit, std::vector<VariableExprAST *> LHS,
                  ExprAST *RHS);
    virtual ~AssignmentAST();
    std::vector<llvm::Value *>     Codegen(llvm::IRBuilder<> *builder);
    static AssignmentAST *         ParseAssignment(CompileUnit * unit,
                                                   CodeBlockAST *codeblock);
    std::vector<VariableExprAST *> LHS; //左侧变量
    ExprAST *                      RHS;
};

#endif /* SRC_AST_ASSIGNMENTAST_H_ */
