#include "ExprAST.h"
#include "../CompileError.hpp"
#include "../utils.h"
#include "BinaryExprAST.h"
#include "BoolExprAST.h"
#include "CallExprAST.h"
#include "CodeBlockAST.h"
#include "DoubleExprAST.h"
#include "EmptyExprAST.h"
#include "IfExprAST.h"
#include "IntExprAST.h"
#include "MemberExprAST.h"
#include "ReturnExprAST.h"
#include "UnaryExprAST.h"
#include "VariableDefExprAST.h"
#include "VariableExprAST.h"
#include "WhileExprAST.h"
#include <iostream>

int GetTokPrecedence(Token tok)
{
    if (tok.type != tok_syntax) {
        return -1;
    }
    std::map<std::string, int> BinopPrecedence;
    BinopPrecedence["=="] = 200;
    BinopPrecedence[">"]  = 200;
    BinopPrecedence["<"]  = 200;
    BinopPrecedence[">="] = 200;
    BinopPrecedence["<="] = 200;
    BinopPrecedence["+"]  = 300;
    BinopPrecedence["-"]  = 300;
    BinopPrecedence["*"]  = 400;
    BinopPrecedence["/"]  = 400;
    BinopPrecedence["%"]  = 400;
    BinopPrecedence["="]  = 100;
    BinopPrecedence[","]  = 200;

    int TokPrec = BinopPrecedence[tok.tokenValue];
    if (TokPrec <= 0) {
        return -1;
    }
    return TokPrec;
}

ExprAST::ExprAST(CompileUnit *unit) : BaseAST(unit) { subExpr = nullptr; }

ExprAST::~ExprAST()
{
    // TODO Auto-generated destructor stub
}

ExprAST *ExprAST::ParsePrimary(CompileUnit *unit, CodeBlockAST *codeblock)
{
    ExprAST *result;
    // todo:除了函数调用之外的语句解析
    Token token = *unit->icurTok;
    switch (token.type) {
    case tok_number: {
        unit->next_tok();
        if (token.tokenValue.find(".") == std::string::npos) {
            result = new IntExprAST(unit,
                                    strtol(token.tokenValue.c_str(), NULL, 10));
        } else {
            result =
                new DoubleExprAST(unit, std::stod(token.tokenValue.c_str()));
        }
        break;
    }
    case tok_key_literal: {
        unit->next_tok();
        if (token.tokenValue == "true") {
            result = new BoolExprAST(unit, true);
        } else {
            result = new BoolExprAST(unit, false);
        }
        break;
    }
    case tok_key_if: {
        result = IfExprAST::ParseIfExpr(unit, codeblock);
        break;
    }
    case tok_key_while: {
        result = WhileExprAST::ParseWhileExpr(unit, codeblock);
        break;
    }
    case tok_syntax: {
        if (token.tokenValue == "(") {
            unit->next_tok();
            result = ParseExpression(unit, codeblock, false);
            token  = *unit->icurTok;
            if (token.type != tok_syntax || token.tokenValue != ")") {
                CompileError e("missing ')'");
                throw e;
            }
            unit->next_tok();
        } else if (token.tokenValue == ")") {
            result = new EmptyExprAST(unit);
        } else {
            unit->next_tok();
            result = new UnaryExprAST(unit, token.tokenValue,
                                      ParsePrimary(unit, codeblock));
        }
        break;
    }
    case tok_identifier: {
        //函数调用或定义
        std::string idName = token.tokenValue;
        token              = *(unit->icurTok + 1);
        if (token.tokenValue == "(") {
            //函数调用
            token         = unit->next_tok();
            ExprAST *args = ExprAST::ParseExpression(unit, codeblock, false);
            result        = new CallExprAST(unit, idName, args);
        } else {
            //变量或变量定义或赋值
            int i = 1, ci = 1;
            while (true) {
                token = *(unit->icurTok + i);
                if (token.type == tok_syntax) {
                    if (token.tokenValue == "*") {
                        i++;
                        ci++;
                        continue;
                    }
                    if (token.tokenValue != "." && token.tokenValue != "<") {
                        //变量
                        unit->next_tok();
                        result = new VariableExprAST(unit, codeblock, idName);
                    } else if (token.tokenValue == "<") {
                        //变量定义
                        result = VariableDefExprAST::ParseVar(unit, codeblock);
                    }
                    break;
                } else if (token.type == tok_identifier && i == ci) {
                    //变量定义
                    result = VariableDefExprAST::ParseVar(unit, codeblock);
                    break;
                }
                i++;
            }
        }
        break;
    }
    case tok_return: {
        return ReturnExprAST::ParseReturnExprAST(unit, codeblock);
    }
    default: {
        CompileError e("不期待的token：" + token.dump());
        throw e;
    }
    }
    if (result == nullptr) {
        return nullptr;
    }
    /*if (token.type == tok_syntax && token.tokenValue == ",") {
        unit->next_tok();
        ExprAST *subExpr = ParseBinOpRHS(unit, codeblock, 200, result);
        if (BinaryExprAST *v = dynamic_cast<BinaryExprAST *>(subExpr)) {
            subExpr = v->RHS;
        }
        result->subExpr = subExpr;
    }*/
    return result;
}

static ExprAST *ParseBinOpRHS(CompileUnit *unit, CodeBlockAST *codeblock,
                              int ExprPrec, ExprAST *LHS)
{
    ExprAST *cExpr = LHS;
    while (1) {
        Token token   = *unit->icurTok;
        int   TokPrec = GetTokPrecedence(token);
        if (TokPrec < ExprPrec) {
            return LHS;
        }
        unit->next_tok();

        ExprAST *RHS = ExprAST::ParsePrimary(unit, codeblock);
        if (!RHS)
            return nullptr;

        int NextPrec = GetTokPrecedence(*(unit->icurTok));
        if (TokPrec < NextPrec) {
            RHS = ParseBinOpRHS(unit, codeblock, TokPrec + 1, RHS);
            if (RHS == nullptr) {
                return nullptr;
            }
        }
        if (token.tokenValue == ",") {
            cExpr->subExpr = RHS;
            cExpr          = RHS;
        } else {
            LHS = new BinaryExprAST(unit, token.tokenValue, LHS, RHS);
        }
    }
}

ExprAST *ExprAST::ParseExpression(CompileUnit *unit, CodeBlockAST *codeblock,
                                  bool root)
{
    ExprAST *LHS = ParsePrimary(unit, codeblock);
    if (LHS == nullptr) {
        return nullptr;
    }
    ExprAST *result = LHS;

    while (unit->icurTok->type == tok_syntax &&
           unit->icurTok->tokenValue == ".") {
        LHS = MemberExprAST::ParseMemberExprAST(unit, codeblock, LHS);
    }

    result = ParseBinOpRHS(unit, codeblock, 0, result);

    if (IfExprAST *v = dynamic_cast<IfExprAST *>(result)) {
        return result; //跳过分号
    }
    if (WhileExprAST *v = dynamic_cast<WhileExprAST *>(result)) {
        return result; //跳过分号
    }
    Token token = *(unit->icurTok);
    if (root) {
        if (token.type != tok_syntax || token.tokenValue != ";") {
            CompileError e("丟失分号: \"" + token.dump() + "\" 前");
            throw e;
        }
        unit->next_tok();
    }
    return result;
}

std::vector<llvm::Value *> ExprAST::CodegenChain(llvm::IRBuilder<> *builder)
{
    std::vector<llvm::Value *> result = this->Codegen(builder);
    if (subExpr != nullptr) {
        std::vector<llvm::Value *> subResult = subExpr->Codegen(builder);
        std::vector<TypeAST *>     subType   = subExpr->type;
        result.insert(result.end(), subResult.begin(), subResult.end());
        type.insert(type.end(), subType.begin(), subType.end());
    }
    return result;
}
