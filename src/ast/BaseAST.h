#ifndef COMPILER_AST_ASTBASE_H_
#define COMPILER_AST_ASTBASE_H_

#include "./../CompileUnit.h"
#include "./../Token.h"
#include <iomanip>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Value.h>

class BaseAST
{
  public:
    BaseAST(CompileUnit *unit);
    virtual ~BaseAST();
    CompileUnit *unit;
    TokenSource  source;
};

#endif /* COMPILER_AST_ASTBASE_H_ */
