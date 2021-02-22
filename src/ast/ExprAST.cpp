#include "ExprAST.h"
#include "../CompileError.hpp"
#include "../utils.h"
#include "AssignmentAST.h"
#include "BinaryExprAST.h"
#include "BoolExprAST.h"
#include "CallExprAST.h"
#include "CodeBlockAST.h"
#include "IfExprAST.h"
#include "IntExprAST.h"
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
    BinopPrecedence["=="] = 100;
    BinopPrecedence[">"]  = 100;
    BinopPrecedence["<"]  = 100;
    BinopPrecedence[">="] = 100;
    BinopPrecedence["<="] = 100;
    BinopPrecedence["+"]  = 200;
    BinopPrecedence["-"]  = 200;
    BinopPrecedence["*"]  = 300;
    BinopPrecedence["/"]  = 300;

    int TokPrec = BinopPrecedence[tok.tokenValue];
    if (TokPrec <= 0) {
        return -1;
    }
    return TokPrec;
}

ExprAST::ExprAST(CompileUnit *unit) : BaseAST(unit)
{
    this->type = nullptr;
    // TODO Auto-generated constructor stub
}

ExprAST::~ExprAST()
{
    // TODO Auto-generated destructor stub
}

ExprAST *ExprAST::ParsePrimary(CompileUnit *unit, CodeBlockAST *codeblock)
{
    // todo:除了函数调用之外的语句解析
    Token token = *unit->icurTok;
    switch (token.type) {
    case tok_number: {
        unit->next_tok();
        return new IntExprAST(unit, strtol(token.tokenValue.c_str(), NULL, 10));
    }
    case tok_key_literal: {
        if (token.tokenValue == "true") {
            return new BoolExprAST(unit, true);
        } else {
            return new BoolExprAST(unit, false);
        }
        break;
    }
    case tok_key_if: {
        return IfExprAST::ParseIfExpr(unit, codeblock);
    }
    case tok_key_while: {
        return WhileExprAST::ParseWhileExpr(unit, codeblock);
    }
    case tok_syntax: {
        if (token.tokenValue == "(") {
            unit->next_tok();
            ExprAST *result = ParseExpression(unit, codeblock, false);
            token           = *unit->icurTok;
            if (token.type != tok_syntax || token.tokenValue != ")") {
                CompileError e("missing ')'");
                throw e;
            }
            token = unit->next_tok();
            return result;
        } else {
            return new UnaryExprAST(unit, token.tokenValue,
                                    ParseExpression(unit, codeblock, false));
            std::cerr << "error3:" << token.dump() << std::endl;
        }
        break;
    }
    case tok_identifier: {
        //函数调用或定义
        std::string idName = token.tokenValue;
        token              = *(unit->icurTok + 1);
        if (token.type == tok_identifier) {
            //定义
            VariableDefExprAST *varAST =
                VariableDefExprAST::ParseVar(unit, codeblock);
            return varAST;
        } else if (token.tokenValue == "=") {
            token = unit->next_tok();
            //赋值
            return AssignmentAST::ParseAssignment(unit, codeblock, idName);
        } else if (token.tokenValue == "(") {
            //函数调用
            token = unit->next_tok();
            token = unit->next_tok();
            std::vector<ExprAST *> args;
            while (true) {
                token = *unit->icurTok;
                if (token.type == tok_syntax && token.tokenValue == ")") {
                    unit->next_tok();
                    break;
                }
                if (token.type == tok_syntax && token.tokenValue == ",") {
                    continue;
                }

                ExprAST *arg = ExprAST::ParseExpression(unit, codeblock, false);
                args.push_back(arg);
                // todo:异常处理
            }

            return new CallExprAST(unit, idName, args);
        } else {
            //变量
            unit->next_tok();
            return new VariableExprAST(unit, codeblock, idName);
        }
        break;
    }
    default: {
        CompileError e("不期待的token：" + token.dump());
        throw e;
    }
    }
    return nullptr;
}

static ExprAST *ParseBinOpRHS(CompileUnit *unit, CodeBlockAST *codeblock,
                              int ExprPrec, ExprAST *LHS)
{
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
        LHS = new BinaryExprAST(unit, token.tokenValue, LHS, RHS);
    }
}

ExprAST *ExprAST::ParseExpression(CompileUnit *unit, CodeBlockAST *codeblock,
                                  bool root)
{
    ExprAST *LHS = ParsePrimary(unit, codeblock);
    if (LHS == nullptr) {
        return nullptr;
    }
    ExprAST *result = ParseBinOpRHS(unit, codeblock, 0, LHS);
    if (IfExprAST *v = dynamic_cast<IfExprAST *>(result)) {
        return result; //跳过分号
    }
    if (WhileExprAST *v = dynamic_cast<WhileExprAST *>(result)) {
        return result; //跳过分号
    }
    if (root) {
        Token token = *(unit->icurTok);
        if (token.type != tok_syntax || token.tokenValue != ";") {
            CompileError e("丟失分号: \"" + token.dump() + "\" 前");
            throw e;
        }
        unit->next_tok();
    }
    return result;
}
