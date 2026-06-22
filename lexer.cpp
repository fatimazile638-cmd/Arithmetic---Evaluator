#include "lexer.h"
#include <cctype>
#include <stdexcept>

Lexer::Lexer(const std::string& source) : src(source), index(0) {}

char Lexer::currentChar() {
    if (index < src.length()) {
        return src[index];
    }
    return '\0'; // String khatam hone par null character
}

void Lexer::advance() {
    index++;
}

void Lexer::skipWhitespace() {
    while (currentChar() != '\0' && std::isspace(currentChar())) {
        advance();
    }
}

// Agar character number hai, to poora integer (e.g., 123) extract karna
Token Lexer::integer() {
    std::string result = "";
    while (currentChar() != '\0' && std::isdigit(currentChar())) {
        result += currentChar();
        advance();
    }
    return Token{TOKEN_INT, result};
}

// Main function jo poori string ko tokens mein convert karega
std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;

    while (currentChar() != '\0') {
        skipWhitespace();

        if (currentChar() == '\0') break;

        // Numbers check karna
        if (std::isdigit(currentChar())) {
            tokens.push_back(integer());
            continue;
        }

        // Operators aur Brackets check karna
        switch (currentChar()) {
            case '+':
                tokens.push_back(Token{TOKEN_PLUS, "+"});
                advance();
                break;
            case '-':
                tokens.push_back(Token{TOKEN_MINUS, "-"});
                advance();
                break;
            case '*':
                tokens.push_back(Token{TOKEN_MUL, "*"});
                advance();
                break;
            case '/':
                tokens.push_back(Token{TOKEN_DIV, "/"});
                advance();
                break;
            case '(':
                tokens.push_back(Token{TOKEN_LPAREN, "("});
                advance();
                break;
            case ')':
                tokens.push_back(Token{TOKEN_RPAREN, ")"});
                advance();
                break;
            default:
                throw std::runtime_error(std::string("Lexical Error: Unknown character '") + currentChar() + "' found.");
        }
    }

    // End of file token add karna
    tokens.push_back(Token{TOKEN_EOF, ""});
    return tokens;
}