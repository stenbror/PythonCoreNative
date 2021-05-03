#pragma once

#include <PythonCoreTokenizer.h>
#include <SyntaxError.h>

#include <ast/ExpressionNode.h>
#include <ast/StatementNode.h>
#include <ast/TypeNode.h>

#include <ast/AtomFalseNode.h>
#include <ast/AtomTrueNode.h>
#include <ast/AtomNoneNode.h>
#include <ast/AtomElipsisNode.h>
#include <ast/AtomNameNode.h>
#include <ast/AtomNumberNode.h>
#include <ast/AtomStringNode.h>
#include <ast/AtomTupleNode.h>
#include <ast/AtomListNode.h>
#include <ast/AtomDictionaryNode.h>
#include <ast/AtomSetNode.h>
#include <ast/AtomExprNode.h>
#include <ast/PowerNode.h>
#include <ast/UnaryPlusNode.h>
#include <ast/UnaryMinusNode.h>
#include <ast/UnaryBitInvertNode.h>
#include <ast/MulNode.h>
#include <ast/DivNode.h>
#include <ast/ModuloNode.h>
#include <ast/MatriceNode.h>
#include <ast/FloorDivNode.h>
#include <ast/PlusNode.h>
#include <ast/MinusNode.h>
#include <ast/ShiftLeftNode.h>
#include <ast/ShiftRightNode.h>
#include <ast/BitAndNode.h>
#include <ast/BitXorNode.h>
#include <ast/BitOrNode.h>
#include <ast/StarExprNode.h>
#include <ast/CompareLessNode.h>
#include <ast/CompareLessEqualNode.h>
#include <ast/CompareEqualNode.h>
#include <ast/CompareGreaterNode.h>
#include <ast/CompareGreaterEqualNode.h>
#include <ast/CompareNotEqualNode.h>
#include <ast/CompareIsNode.h>
#include <ast/CompareIsNotNode.h>
#include <ast/CompareNotInNode.h>
#include <ast/CompareInNode.h>
#include <ast/NotTestNode.h>
#include <ast/AndTestNode.h>
#include <ast/OrTestNode.h>
#include <ast/LambdaNode.h>
#include <ast/TestNode.h>
#include <ast/NamedExprNode.h>
#include <ast/TestListCompNode.h>
#include <ast/CallNode.h>
#include <ast/IndexNode.h>
#include <ast/DotNameNode.h>


#include <memory>

namespace PythonCoreNative::RunTime::Parser
{
    class PythonCoreParser
    {
        public:
            PythonCoreParser(std::shared_ptr<PythonCoreTokenizer> lexer);

            std::shared_ptr<AST::TypeNode> ParseFuncTypeInput();
            std::shared_ptr<AST::StatementNode> ParseSingleInput();
            std::shared_ptr<AST::StatementNode> ParseFileInput();
            std::shared_ptr<AST::StatementNode> ParseEvalInput();


        protected:
            std::shared_ptr<AST::ExpressionNode> ParseAtom();
            std::shared_ptr<AST::ExpressionNode> ParseAtomExpr();
            std::shared_ptr<AST::ExpressionNode> ParsePower();
            std::shared_ptr<AST::ExpressionNode> ParseFactor();
            std::shared_ptr<AST::ExpressionNode> ParseTerm();
            std::shared_ptr<AST::ExpressionNode> ParseArith();
            std::shared_ptr<AST::ExpressionNode> ParseShift();
            std::shared_ptr<AST::ExpressionNode> ParseAndExpr();
            std::shared_ptr<AST::ExpressionNode> ParseXorExpr();
            std::shared_ptr<AST::ExpressionNode> ParseOrExpr();
            std::shared_ptr<AST::ExpressionNode> ParseStarExpr();
            std::shared_ptr<AST::ExpressionNode> ParseComparison();
            std::shared_ptr<AST::ExpressionNode> ParseNotTest();
            std::shared_ptr<AST::ExpressionNode> ParseAndTest();
            std::shared_ptr<AST::ExpressionNode> ParseOrTest();
            std::shared_ptr<AST::ExpressionNode> ParseLambda(bool isCond);
            std::shared_ptr<AST::ExpressionNode> ParseTestNoCond();
            std::shared_ptr<AST::ExpressionNode> ParseTest();
            std::shared_ptr<AST::ExpressionNode> ParseNamedExpr();
            std::shared_ptr<AST::ExpressionNode> ParseTestListComp();
            std::shared_ptr<AST::ExpressionNode> ParseTrailer();
            std::shared_ptr<AST::ExpressionNode> ParseSubscriptList();
            std::shared_ptr<AST::ExpressionNode> ParseSubscript();
            std::shared_ptr<AST::ExpressionNode> ParseExprList();
            std::shared_ptr<AST::ExpressionNode> ParseTestList();
            std::shared_ptr<AST::ExpressionNode> ParseDictorSetMaker();
            std::shared_ptr<AST::ExpressionNode> ParseArgList();
            std::shared_ptr<AST::ExpressionNode> ParseArgument();
            std::shared_ptr<AST::ExpressionNode> ParseCompIter();
            std::shared_ptr<AST::ExpressionNode> ParseSyncCompFor();
            std::shared_ptr<AST::ExpressionNode> ParseCompFor();
            std::shared_ptr<AST::ExpressionNode> ParseCompIf();
            std::shared_ptr<AST::ExpressionNode> ParseYieldExpr();
            std::shared_ptr<AST::ExpressionNode> ParseVarArgsList();
            std::shared_ptr<AST::ExpressionNode> ParseVFPAssign();

        protected:
            std::shared_ptr<AST::StatementNode> ParseCompound();
            std::shared_ptr<AST::StatementNode> ParseIf();
            std::shared_ptr<AST::StatementNode> ParseElif();
            std::shared_ptr<AST::StatementNode> ParseElse();
            std::shared_ptr<AST::StatementNode> ParseWhile();
            std::shared_ptr<AST::StatementNode> ParseFor();
            std::shared_ptr<AST::StatementNode> ParseWith();
            std::shared_ptr<AST::StatementNode> ParseWithItem();
            std::shared_ptr<AST::StatementNode> ParseTry();
            std::shared_ptr<AST::StatementNode> ParseExcept();
            std::shared_ptr<AST::StatementNode> ParseExceptClause();
            std::shared_ptr<AST::StatementNode> ParseDecorated();
            std::shared_ptr<AST::StatementNode> ParseDecorators();
            std::shared_ptr<AST::StatementNode> ParseDecorator();
            std::shared_ptr<AST::StatementNode> ParseAsyncFuncDef();
            std::shared_ptr<AST::StatementNode> ParseFuncDef();
            std::shared_ptr<AST::StatementNode> ParseParameter();
            std::shared_ptr<AST::StatementNode> ParseFuncBodySuite();
            std::shared_ptr<AST::StatementNode> ParseTypedArgsList();
            std::shared_ptr<AST::StatementNode> ParseTypedAssign();
            std::shared_ptr<AST::StatementNode> ParseTFPDef();
            std::shared_ptr<AST::StatementNode> ParseClass();
            std::shared_ptr<AST::StatementNode> ParseSuite();
            std::shared_ptr<AST::StatementNode> ParseAsync();
            std::shared_ptr<AST::StatementNode> ParseStmt();
            std::shared_ptr<AST::StatementNode> ParseSimpleStmt();
            std::shared_ptr<AST::StatementNode> ParseSmallStmt();
            std::shared_ptr<AST::StatementNode> ParseExpr();
            std::shared_ptr<AST::StatementNode> ParseAnnAssign();
            std::shared_ptr<AST::StatementNode> ParseTestListStarExpr();
            std::shared_ptr<AST::StatementNode> ParseDel();
            std::shared_ptr<AST::StatementNode> ParsePass();
            std::shared_ptr<AST::StatementNode> ParseBreak();
            std::shared_ptr<AST::StatementNode> ParseContinue();
            std::shared_ptr<AST::StatementNode> ParseReturn();
            std::shared_ptr<AST::StatementNode> ParseYieldStmt();
            std::shared_ptr<AST::StatementNode> ParseRaise();
            std::shared_ptr<AST::StatementNode> ParseImport();
            std::shared_ptr<AST::StatementNode> ParseImportName();
            std::shared_ptr<AST::StatementNode> ParseImportFrom();
            std::shared_ptr<AST::StatementNode> ParseImportAsName();
            std::shared_ptr<AST::StatementNode> ParseDottedAsName();
            std::shared_ptr<AST::StatementNode> ParseImportAsNames();
            std::shared_ptr<AST::StatementNode> ParseDottedAsNames();
            std::shared_ptr<AST::StatementNode> ParseDottedName();
            std::shared_ptr<AST::StatementNode> ParseGlobal();
            std::shared_ptr<AST::StatementNode> ParseNonlocal();
            std::shared_ptr<AST::StatementNode> ParseAssert();

        protected:
            std::shared_ptr<AST::TypeNode> ParseFuncType();
            std::shared_ptr<AST::TypeNode> ParseTypeList();

        protected:
            std::shared_ptr<PythonCoreTokenizer> mLexer;
    };
}
