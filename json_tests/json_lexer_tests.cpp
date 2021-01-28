#include <gtest/gtest.h>
#include <json/json_lexer.h>

using namespace std;
using namespace json;

TEST(JsonLexerTests, EmptyStringTest)
{
    const wstring EMPTY_STRING;
    JsonLexer lexer(EMPTY_STRING);
    const auto token = lexer.GetNextToken();
    EXPECT_EQ(JsonLexer::Token::END ,token.type);
}

TEST(JsonLexerTests, BracesBracketTest)
{
    const auto TEST_STRING = L"{}[]"s;
    JsonLexer lexer(TEST_STRING);
    EXPECT_EQ(JsonLexer::Token::BRACE_LEFT, lexer.GetNextToken().type);
    EXPECT_EQ(JsonLexer::Token::BRACE_RIGTH, lexer.GetNextToken().type);
    EXPECT_EQ(JsonLexer::Token::BRACKET_LEFT, lexer.GetNextToken().type);
    EXPECT_EQ(JsonLexer::Token::BRACKET_RIGTH, lexer.GetNextToken().type);
    EXPECT_EQ(JsonLexer::Token::END, lexer.GetNextToken().type);
}

TEST(JsonLexerTests, JsonSimpleObjectTest)
{
    const auto JSON_ELEMENT_STRING = LR"({"key" : 1337})"s;
    JsonLexer lexer(JSON_ELEMENT_STRING);
    EXPECT_EQ(JsonLexer::Token::BRACE_LEFT, lexer.GetNextToken().type);

    const auto stringInfo = lexer.GetNextToken();
    EXPECT_EQ(JsonLexer::Token::STRING, stringInfo.type);
    EXPECT_EQ(L"key", JSON_ELEMENT_STRING.substr(stringInfo.offset, stringInfo.size));

    EXPECT_EQ(JsonLexer::Token::SPACE, lexer.GetNextToken().type);
    EXPECT_EQ(JsonLexer::Token::COLON, lexer.GetNextToken().type);
    EXPECT_EQ(JsonLexer::Token::SPACE, lexer.GetNextToken().type);
    EXPECT_EQ(JsonLexer::Token::NUMBER, lexer.GetNextToken().type);
    EXPECT_EQ(JsonLexer::Token::BRACE_RIGTH, lexer.GetNextToken().type);
    EXPECT_EQ(JsonLexer::Token::END, lexer.GetNextToken().type);
}

TEST(JsonLexerTests, JsonComplcatedObjectTest)
{
    const auto JSON_ELEMENT_STRING =
        LR"({
                "key" : [
                    "value",1337,true,false
                ]
            })"s
        ;
    JsonLexer lexer(JSON_ELEMENT_STRING);
    EXPECT_EQ(JsonLexer::Token::BRACE_LEFT, lexer.GetNextToken().type);
    EXPECT_EQ(JsonLexer::Token::NEW_LINE, lexer.GetNextToken().type);
    EXPECT_EQ(JsonLexer::Token::SPACE, lexer.GetNextToken().type);
    EXPECT_EQ(JsonLexer::Token::STRING, lexer.GetNextToken().type);
    EXPECT_EQ(JsonLexer::Token::SPACE, lexer.GetNextToken().type);
    EXPECT_EQ(JsonLexer::Token::COLON, lexer.GetNextToken().type);
    EXPECT_EQ(JsonLexer::Token::SPACE, lexer.GetNextToken().type);
    EXPECT_EQ(JsonLexer::Token::BRACKET_LEFT, lexer.GetNextToken().type);
    EXPECT_EQ(JsonLexer::Token::NEW_LINE, lexer.GetNextToken().type);
    EXPECT_EQ(JsonLexer::Token::SPACE, lexer.GetNextToken().type);
    EXPECT_EQ(JsonLexer::Token::STRING, lexer.GetNextToken().type);
    EXPECT_EQ(JsonLexer::Token::COMMA, lexer.GetNextToken().type);
    EXPECT_EQ(JsonLexer::Token::NUMBER, lexer.GetNextToken().type);
    EXPECT_EQ(JsonLexer::Token::COMMA, lexer.GetNextToken().type);
    EXPECT_EQ(JsonLexer::Token::TRUE, lexer.GetNextToken().type);
    EXPECT_EQ(JsonLexer::Token::COMMA, lexer.GetNextToken().type);
    EXPECT_EQ(JsonLexer::Token::FALSE, lexer.GetNextToken().type);
    EXPECT_EQ(JsonLexer::Token::NEW_LINE, lexer.GetNextToken().type);
    EXPECT_EQ(JsonLexer::Token::SPACE, lexer.GetNextToken().type);
    EXPECT_EQ(JsonLexer::Token::BRACKET_RIGTH, lexer.GetNextToken().type);
    EXPECT_EQ(JsonLexer::Token::NEW_LINE, lexer.GetNextToken().type);
    EXPECT_EQ(JsonLexer::Token::SPACE, lexer.GetNextToken().type);
    EXPECT_EQ(JsonLexer::Token::BRACE_RIGTH, lexer.GetNextToken().type);
    EXPECT_EQ(JsonLexer::Token::END, lexer.GetNextToken().type);
}
