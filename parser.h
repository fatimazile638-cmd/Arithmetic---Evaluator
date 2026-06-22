#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>
#include <stdexcept>
#include "lexer.h" // Lexer ke tokens ko access karne ke liye

class Parser {
private:
    std::vector<Token> tokens;
    size_t currentIndex;

    Token currentToken() const;
    void consume(TokenType type, const std::string& errorMessage);
    
    // BODMAS grammar functions
    int expression();
    int term();
    int factor();

public:
    explicit Parser(const std::vector<Token>& tokenList);
    int parse();
};

#endif // PARSER_H
