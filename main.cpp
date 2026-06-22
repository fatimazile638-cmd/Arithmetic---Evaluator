#include <iostream>
#include <string>
#include "lexer.h"
#include "parser.h"

 int main() {
    std::string expression;
    std::cout << "=== Arithmetic Compiler/Evaluator ===" << std::endl;
    
    while (true) {
        std::cout << "\nEnter arithmetic expression (or 'exit' to quit): ";
        std::getline(std::cin, expression);

        if (expression == "exit") break;
        if (expression.empty()) continue;
        
        try {
            // Step 1: Lexical Analysis (Tokens banana)
            Lexer lexer(expression);
            std::vector<Token> tokens = lexer.tokenize();
            
            // Step 2: Parsing & Evaluation (Syntax check aur solve karna)
            Parser parser(tokens);
            int result = parser.parse();
            
            // Output display
            std::cout << "Success! Final Result: " << result << std::endl;
        } 
        catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    }
    return 0;
}