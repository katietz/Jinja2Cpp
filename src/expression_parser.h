#ifndef EXPRESSION_PARSER_H
#define EXPRESSION_PARSER_H

#include "lexer.h"
#include "error_handling.h"
#include "expression_evaluator.h"
#include "renderer.h"

#include <nonstd/expected.hpp>
#include <jinja2cpp/template_env.h>

namespace jinja2
{
class ExpressionParser
{
public:
    template<typename T>
    using ParseResult = nonstd::expected<T, ParseError>;

    explicit ExpressionParser(const Settings& settings, TemplateEnv* env = nullptr);
    ParseResult<RendererPtr> Parse(LexScanner& lexer);
    ParseResult<ExpressionEvaluatorPtr<FullExpressionEvaluator>> ParseFullExpression(LexScanner& lexer, bool includeIfPart = true);
    ParseResult<CallParamsInfo> ParseCallParams(LexScanner& lexer);
    ParseResult<CallParamsInfo> ParseCallParams(LexScanner& lexer, ExpressionEvaluatorPtr<Expression> &left);
    ParseResult<ExpressionEvaluatorPtr<ExpressionFilter>> ParseFilterExpression(LexScanner& lexer, int elem, ExpressionEvaluatorPtr<Expression> &left);
private:
    ParseResult<ExpressionEvaluatorPtr<Expression>> ParseLiteral(LexScanner& lexer, Token::Type &typ);
    ParseResult<ExpressionEvaluatorPtr<Expression>> ParseEnclosure(LexScanner& lexer, Token::Type &typ);
    ParseResult<ExpressionEvaluatorPtr<Expression>> ParseAtomic(LexScanner& lexer, Token::Type &typ);

    ParseResult<ExpressionEvaluatorPtr<Expression>> ParseLogicalNot(LexScanner& lexer);
    ParseResult<ExpressionEvaluatorPtr<Expression>> ParseBinaryOr(LexScanner& lexer);
    ParseResult<ExpressionEvaluatorPtr<Expression>> ParseBinaryAnd(LexScanner& lexer);
    ParseResult<ExpressionEvaluatorPtr<Expression>> ParseBinaryXor(LexScanner& lexer);
    ParseResult<ExpressionEvaluatorPtr<Expression>> ParseLogicalOr(LexScanner& lexer);
    ParseResult<ExpressionEvaluatorPtr<Expression>> ParseLogicalAnd(LexScanner& lexer);
    ParseResult<ExpressionEvaluatorPtr<Expression>> ParseLogicalCompare(LexScanner& lexer);
    ParseResult<ExpressionEvaluatorPtr<Expression>> ParseStringConcat(LexScanner& lexer);
    ParseResult<ExpressionEvaluatorPtr<Expression>> ParseMathPow(LexScanner& lexer);
    ParseResult<ExpressionEvaluatorPtr<Expression>> ParseMathMulDiv(LexScanner& lexer);
    ParseResult<ExpressionEvaluatorPtr<Expression>> ParseMathPlusMinus(LexScanner& lexer);
    ParseResult<ExpressionEvaluatorPtr<Expression>> ParseShift(LexScanner& lexer);
    ParseResult<ExpressionEvaluatorPtr<Expression>> ParseUnaryPlusMinus(LexScanner& lexer);
    ParseResult<ExpressionEvaluatorPtr<Expression>> ParseValueExpression(LexScanner& lexer);
    ParseResult<ExpressionEvaluatorPtr<Expression>> ParseBracedExpressionOrTuple(LexScanner& lexer);
    ParseResult<ExpressionEvaluatorPtr<Expression>> ParseDictionary(LexScanner& lexer);
    ParseResult<ExpressionEvaluatorPtr<Expression>> ParseTuple(LexScanner& lexer);
    ParseResult<ExpressionEvaluatorPtr<Expression>> ParseCall(LexScanner& lexer, ExpressionEvaluatorPtr<Expression> valueRef);
    ParseResult<ExpressionEvaluatorPtr<Expression>> ParseSubscript(LexScanner& lexer, ExpressionEvaluatorPtr<Expression> valueRef);
    ParseResult<ExpressionEvaluatorPtr<Expression>> ParseSubscriptDotName(LexScanner& lexer, ExpressionEvaluatorPtr<Expression> valueRef);
    ParseResult<ExpressionEvaluatorPtr<IfExpression>> ParseIfExpression(LexScanner& lexer);

private:
    ComposedRenderer* m_topLevelRenderer = nullptr;
};

} // jinja2

#endif // EXPRESSION_PARSER_H
