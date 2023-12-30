#include <iostream>
#include <cctype>

class SyntaxAnalyzer {
public:
    SyntaxAnalyzer(const std::string& input) : input(input), currentPos(0) {}

    bool parse() {
        return expression();
    }

private:
    bool expression() {
        return term() && expressionTail();
    }

    bool expressionTail() {
        if (match('+') || match('-')) {
            return term() && expressionTail();
        }
        return true;
    }

    bool term() {
        return factor() && termTail();
    }

    bool termTail() {
        if (match('*') || match('/')) {
            return factor() && termTail();
        }
        return true;
    }

    bool factor() {
        if (match('(')) {
            bool result = expression();
            return result && match(')');
        } else if (std::isdigit(peek())) {
            consume();
            return true;
        }
        return false;
    }

    char peek() const {
        return (currentPos < input.length()) ? input[currentPos] : '\0';
    }

    bool match(char expected) {
        if (peek() == expected) {
            consume();
            return true;
        }
        return false;
    }

    void consume() {
        if (currentPos < input.length()) {
            currentPos++;
        }
    }

    const std::string& input;
    size_t currentPos;
};

int main() {
    std::string input;
    std::cout << "Enter an arithmetic expression: ";
    std::getline(std::cin, input);

    SyntaxAnalyzer syntaxAnalyzer(input);
    if (syntaxAnalyzer.parse()) {
        std::cout << "Syntax analysis successful.\n";
    } else {
        std::cout << "Syntax error.\n";
    }

    return 0;
}