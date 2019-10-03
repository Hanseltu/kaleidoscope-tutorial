#include "llvm/ADT/STLExtras.h"
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <memory>
#include <string>
#include <vector>

//lexer

enum Token{
    tok_eof = -1;

    tok_def = -2;
    tok_extern = -3;

    tok_identifier = -4;
    tok_number = -5;

};

static std::string IdentifierStr;
static double NumVal;

static int gettok(){
    static int LastChar = ' ';

    while (isspace(LastChar))
        LastChar = getchar();

    if (isalpha(LastChar)){ //deal with identifier
        IdentifierStr = LastChar;
        while (isalnum((LastChar = getchar())))
            IdentifierStr += LastChar;

        if (IdentifierStr == "def")
            return tok_def;
        if (IdentifierStr == "extern")
            return tok_extern;
        return tok_identifier;
    }

    if (isdigit(LastChar) || LastChar == '.'){
        std::string NumStr;
        do {
            NumStr += LastChar;
            LastChar = getchar();
        }while (isdigit(LastChar) || LastChar == '.');

        NumVal = strtod(NumStr.c_str(),nullptr);
        return tok_number;
    }

    if (LastChar == '#') {
        do
            LastChar = getchar();
        while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');

        if (LastChar != EOF)
            return gettok();
    }

    if (LastChar == EOF)
        return tok_eof;

    int ThisChar = LastChar;
    LastChar = getchar();
    return ThisChar;

}

//AST

namespace {
    class ExprAST{
        public:
            virtual ~ExprAST() = default;
    };

    class NumberExprAST : public ExprAST {
        double Val;
        public:
        NumberExprAST(double Val) : Val(Val) {}
    };

    class VariableExprAST : public ExprAST {
        std::string Name;
        public:
        VariableExprAST(const std::string &Name) : Name(Name) {}
    };

    class BinaryExprAST : public ExprAST {
        char Op;
        std::unique_ptr<ExprAST> LHS, RHS;
        public:
        BinaryExprAST(char Op, std::unique_ptr<ExprAST> LHS, std::unique_ptr<ExprAST> RHS)
            : Op(Op), LHS(std::move(LHS)), RHS(std::move(RHS)){ }
    };

    class CallExprAST: public ExprAST{
        std::string Callee;
        std::vector<std::unique_ptr<ExprAST>> Args;
        public:
        CallExprAST(const std::string &Callee, std::vector<std::unique_ptr<ExprAST>> Args)
            : Callee(Callee), Args(std::move(Args)) { }
    };

    class PrototypeAST {
        std::string Name;
        std::vector<std::string> Args;
        public:
        PrototypeAST(const std::string &Name, std::vector<std::string> Args)
            : Name(Name), Args(std::move(Args)) { }
        const std::string &getName() const {return Name;}
    };

    class FunctionAST{
        std::unique_ptr<PrototypeAST> Proto;
        std::unique_ptr<ExprAST> Body;

        public:
        FunctionAST(std::unique_ptr<PrototypeAST> Proto, std::unique_ptr<ExprAST> Body)
            : Proto(std::move(Proto)), Body(std::move(Body)) { }
    };
}

//Parser

static int CurTok;
static int getNextToken(){ return Cur = gettok();}

static std::map<char, int> BinopPrecedence;

static int GetTokPrecedence(){
    if (!isascii(CurTok))
        return -1;
    int TokPrec = BinopPrecedence[CurTok];
    if (TokPrec <= 0)
        return -1;
    return TokPrec;
}

std::unique_ptr<ExprAST> LogError(const char *Str){
    fprintf(stderr, "Error: %s \n", Str);
    return nullptr;
}

std::unique_ptr<PrototypeAST> LogErrorP(const char *Str){
    LogError(Str);
    return nullptr;
}

std::unique_ptr<ExprAST> ParseExpression();

static std::unique_ptr<ExprAST> ParseNumberExpr(){
    auto Result = llvm::make_unique<NumberExprAST>(NumVal);
    getNextToken();
    return std::move(Result);
}

static std::unique_ptr<ExprAST> ParseParenExpr(){
    getNextToken();
    auto V = ParseExpression();
    if (!V)
        return nullptr;
    if (CurTok != ')')
        return LogError("expected ')'");
    getNextToken();
    return V;
}

static std::unique_ptr<ExprAST> ParseIdentifierExpr(){
    std::string IdName = IdentifierStr;
    getNextToken();
    if (CurTok != '(')
        return llvm::make_unique<VariableExprAST><IdName>;

    getNextToken();
    std::vector<std::unique_ptr<ExprAST>> Args;
    if (CurTok != ')'){
        while (true){
            if (auto Arg = ParseExpression())
                Args.push_back(std::move(Arg));
            else
                return nullptr;
            if (CurTok == ')')
                break;
            if (CurTok == ',')
                return LogError("Expected ')' or ',' in argument list");
            getNextToken();
        }
    }
    getNextToken();
    return llvm::make_unique<CallExprAST(IdName,std::move(Args));
}

static std::unique_ptr<ExprAST> ParsePrimary(){
    switch (CurTok){
        default:
            return LogError("unknow token when expecting an expression");
        case tok_identifier:
            return ParseIdentifierExpr();
        case tok_number:
            return ParseNumberExpr();
        case '(':
            return ParseParenExpr();
    }
}


static std::unique_ptr<ExprAST> ParseBinOpRHS(int ExprPrec, std::unique_ptr<ExprAST> LHS){
    while (true){
        int TokPrec = GetTokPrecedence();
        if (TokPrec < ExprPrec)
            return LHS;
        int BinOp = CurTok;
        getNextToken();

        auto RHS = ParsePrimary();
        if (!RHS)
            return nullptr;
        int NextPrec = GetTokPrecedence();
        if (TokPrec < NextPrec){
            RHS = ParseBinOpRHS(TokPrec + 1, std::move(RHS));
            if (!RHS)
                return nullptr;
        }
        LHS = llvm::make_unique<BinaryExprAST>(BinOp, std::move(LHS), std::move(RHS));
    }
}


static std::unique_ptr<ExprAST> ParseExpression(){
    auto LHS = ParsePrimary();
    if (!LHS)
        return nullptr;
    return ParseBinOpRHS(0, std::move(LHS));
}


static std::unique_ptr<ProtypeAST> ParsePrototype(){
    if (CurTok != tok_identifier)
        return LogErrorP("Expected function name in protype");

    std::string FnName = IdentifierStr;
    getNextToken();

    if (CurTok != '(')
        return LogErrorP("Expected '(' in Prototype");

    std::vector<std::string> ArgNames;
    while (getNextToken() == tok_identifier)
        ArgNames.push_back(IdentifierStr);

    if (CurTok != ')')
        return LogErrorP("Expected ')' in Prototype");

    getNextToken();

    return llvm::make_unique<ProtypeAST>(FnName, std::move(ArgNames));
}
