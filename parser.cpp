#include "parser.h"

Parser::Parser(const std::vector<Token>& tokenList) : tokens(tokenList), currentIndex(0) {}

Token Parser::currentToken() const {
    if (currentIndex < tokens.size()) {
        return tokens[currentIndex];
    }
    return Token{TOKEN_EOF, ""}; // End of file token
}

void Parser::consume(TokenType type, const std::string& errorMessage) {
    if (currentToken().type == type) {
        currentIndex++;
    } else {
        throw std::runtime_error("Syntax Error: " + errorMessage);
    }
}

// Main parse function jo execution shuru karta hai
int Parser::parse() {
    int result = expression();
    if (currentToken().type != TOKEN_EOF) {
        throw std::runtime_error("Syntax Error: Unexpected tokens at the end.");
    }
    return result;
}

// Plus (+) aur Minus (-) ke liye handling
int Parser::expression() {
    int result = term();
    
    while (currentToken().type == TOKEN_PLUS || currentToken().type == TOKEN_MINUS) {
        Token op = currentToken();
        currentIndex++; // operator ko consume kiya
        
        if (op.type == TOKEN_PLUS) {
            result += term();
        } else if (op.type == TOKEN_MINUS) {
            result -= term();
        }
    }
    return result;
}

// Multiply (*) aur Divide (/) ke liye handling (BODMAS priority)
int Parser::term() {
    int result = factor();
    
    while (currentToken().type == TOKEN_MUL || currentToken().type == TOKEN_DIV) {
        Token op = currentToken();
        currentIndex++; // operator ko consume kiya
        
        if (op.type == TOKEN_MUL) {
            result *= factor();
        } else if (op.type == TOKEN_DIV) {
            int nextFactor = factor();
            if (nextFactor == 0) {
                throw std::runtime_error("Runtime Error: Division by zero is not allowed!");
            }
            result /= nextFactor;
        }
    }
    return result;
}

// Numbers aur Brackets () ke liye handling
int Parser::factor() {
    Token token = currentToken();
    
    if (token.type == TOKEN_INT) {
        currentIndex++;
        return std::stoi(token.value);
    } 
    else if (token.type == TOKEN_LPAREN) {
        currentIndex++; // '(' ko consume kiya
        int result = expression(); // Bracket ke andar ka poora expression solve karein
        consume(TOKEN_RPAREN, "Expected closing parenthesis ')'");
        return result;
    }
    
    throw std::runtime_error("Syntax Error: Expected a number or opening parenthesis, but found '" + token.value + "'");
}