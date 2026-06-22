#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

// Token ki types define kar rahe hain
enum TokenType {
    TOKEN_INT,      // Numbers (e.g., 10, 25)
    TOKEN_PLUS,     // +
    TOKEN_MINUS,    // -
    TOKEN_MUL,      // *
    TOKEN_DIV,      // /
    TOKEN_LPAREN,   // (
    TOKEN_RPAREN,   // )
    TOKEN_EOF       // End of File / Expression khatam
};

// Har Token ka structure
struct Token {
    TokenType type;
    std::string value;
};

class Lexer {
private:
    std::string src;
    size_t index;
    char currentChar();
    void advance();
    void skipWhitespace();
    Token integer();

public:
    explicit Lexer(const std::string& source);
    std::vector<Token> tokenize();
};

#endif // LEXER_H