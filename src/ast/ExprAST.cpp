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
#include "SizeofExprAST.h"
#include "UnaryExprAST.h"
#include "VariableDefExprAST.h"
#include "VariableExprAST.h"
#include "WhileExprAST.h"
#include <iostream>

std::map<std::string, int> BinopPrecedence;
std::map<std::string, int> LUnaryopPrecedence;
std::map<std::string, int> RUnaryopPrecedence;

void initTokPrecedence()
{
    BinopPrecedence["="] = 1;

    BinopPrecedence[","]  = 2;
    BinopPrecedence["||"] = 3;

    BinopPrecedence["&&"] = 4;

    BinopPrecedence["|"] = 5;

    BinopPrecedence["^"] = 6;

    BinopPrecedence["&"] = 7;

    BinopPrecedence["=="] = 8;
    BinopPrecedence["!="] = 8;

    BinopPrecedence[">"]  = 9;
    BinopPrecedence["<"]  = 9;
    BinopPrecedence[">="] = 9;
    BinopPrecedence["<="] = 9;

    BinopPrecedence[">>"] = 9;
    BinopPrecedence["<<"] = 9;

    BinopPrecedence["+"] = 10;
    BinopPrecedence["-"] = 10;

    BinopPrecedence["*"] = 11;
    BinopPrecedence["/"] = 11;
    BinopPrecedence["%"] = 11;

    BinopPrecedence[".*"] = 12;

    BinopPrecedence["."]  = 14;
    BinopPrecedence["->"] = 14;

    LUnaryopPrecedence["*"] = 13;
    LUnaryopPrecedence["!"] = 13;
    LUnaryopPrecedence["&"] = 13;
}

int GetBinTokPrecedence(Token tok)
{
    if (tok.type != tok_syntax) {
        return -1;
    }

    int TokPrec = BinopPrecedence[tok.tokenValue];
    if (TokPrec <= 0) {
        return -1;
    }
    return TokPrec;
}

int GetLUnaryTokPrecedence(Token tok)
{
    if (tok.type != tok_syntax) {
        return -1;
    }

    int TokPrec = LUnaryopPrecedence[tok.tokenValue];
    if (TokPrec <= 0) {
        return -1;
    }
    return TokPrec;
}

int GetRUnaryTokPrecedence(Token tok)
{
    if (tok.type != tok_syntax) {
        return -1;
    }

    int TokPrec = RUnaryopPrecedence[tok.tokenValue];
    if (TokPrec <= 0) {
        return -1;
    }
    return TokPrec;
}

ExprAST::ExprAST(CompileUnit *unit) : BaseAST(unit)
{
    subExpr = nullptr;
    initTokPrecedence();
}

ExprAST::~ExprAST()
{
    // TODO Auto-generated destructor stub
}

llvm::Value *ExprAST::getAlloca(llvm::IRBuilder<> *builder) { return nullptr; }

ExprAST *ExprAST::ParsePrimary(CompileUnit *unit, CodeBlockAST *codeblock,
                               bool root)
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
        } else {
            result = new EmptyExprAST(unit);
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
            //变量或变量定义
            int i = 1, ci = 1;
            while (true) {
                token = *(unit->icurTok + i);
                if (token.type == tok_syntax) {
                    if (token.tokenValue == "*" && root) {
                        i++;
                        ci++;
                        continue;
                    }
                    if (token.tokenValue != "<" || !root) {
                        //变量
                        unit->next_tok();
                        result = new VariableExprAST(unit, codeblock, idName);
                    } else if (token.tokenValue == "<" && root) {
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
        result = ReturnExprAST::ParseReturnExprAST(unit, codeblock);
        break;
    }
    case tok_key_sizeof: {
        unit->next_tok(); // sizeof
        unit->next_tok(); //(
        TypeAST *type = TypeAST::ParseType(unit);
        unit->next_tok(); //)
        result = new SizeofExprAST(unit, type);
        break;
    }
    default: {
        CompileError e("不期待的token：" + token.dump(), token.file,
                       token.lineno);
        throw e;
    }
    }
    return result;
}

void ExprAST::appendSubExpr(ExprAST *expr)
{
    ExprAST *curAST = this;
    while (curAST->subExpr == nullptr) {
        curAST = curAST->subExpr;
    }
    curAST->subExpr = expr;
}

static ExprAST *ParseBinOpRHS(CompileUnit *unit, CodeBlockAST *codeblock,
                              int ExprPrec, ExprAST *LHS)
{
    while (1) {
        Token token = *unit->icurTok;
        int   TokPrec;
        if (LHS == nullptr) {
            TokPrec = GetLUnaryTokPrecedence(token);
        } else {
            TokPrec = GetBinTokPrecedence(token);
        }
        if (TokPrec < ExprPrec) {
            return LHS;
        }
        unit->next_tok();

        ExprAST *RHS = ExprAST::ParsePrimary(unit, codeblock);
        if (!RHS)
            return nullptr;

        int NextPrec = GetBinTokPrecedence(*(unit->icurTok));
        if (TokPrec < NextPrec) {
            RHS = ParseBinOpRHS(unit, codeblock, TokPrec + 1, RHS);
            if (RHS == nullptr) {
                return nullptr;
            }
        }
        if (token.tokenValue == ",") {
            LHS->appendSubExpr(RHS);
        } else if (token.tokenValue == ".") {
            if (VariableExprAST *v = dynamic_cast<VariableExprAST *>(RHS)) {
                LHS = new MemberExprAST(unit, LHS, v->idName, false);
            } else if (CallExprAST *v = dynamic_cast<CallExprAST *>(RHS)) {
                v->LHS = LHS;
                LHS    = v;
            } else {
                CompileError e("未知的操作");
                throw e;
            }
        } else if (token.tokenValue == "->") {
            if (VariableExprAST *v = dynamic_cast<VariableExprAST *>(RHS)) {
                LHS = new MemberExprAST(unit, LHS, v->idName, true);
            } else {
                CompileError e("成员方法调用未实现");
                throw e;
            }
        } else if (dynamic_cast<EmptyExprAST *>(LHS) != nullptr &&
                   GetLUnaryTokPrecedence(token) != -1) {
            //左一元运算符
            LHS = new UnaryExprAST(unit, token.tokenValue, RHS, true);
        } else if (dynamic_cast<EmptyExprAST *>(RHS) != nullptr &&
                   GetRUnaryTokPrecedence(token) != -1) {
            //右一元运算符
            LHS = new UnaryExprAST(unit, token.tokenValue, LHS, false);
        } else {
            LHS = new BinaryExprAST(unit, token.tokenValue, LHS, RHS);
        }
    }
}

ExprAST *ExprAST::ParseExpression(CompileUnit *unit, CodeBlockAST *codeblock,
                                  bool root)
{
    ExprAST *result = ParsePrimary(unit, codeblock, root);

    /*while (unit->icurTok->type == tok_syntax &&
           unit->icurTok->tokenValue == ".") {
        LHS = MemberExprAST::ParseMemberExprAST(unit, codeblock, LHS);
    }*/

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
            CompileError e("丟失分号: \"" + token.dump() + "\" 前", token.file,
                           token.lineno);
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
