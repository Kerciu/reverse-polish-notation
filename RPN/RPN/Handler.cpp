#include <iostream>
#include <string>
#include "Handler.h"
#include "Operator.h"

Handler::Handler() : expression("") { }

Handler::Handler(std::string express) : expression(express) { }

int Handler::calculateStringLength(std::string str) {
    int count = 0;
    for (const char& ch : str) {
        count++;
    }
    return count;
}

bool Handler::checkIfCorrectExpression(std::string express) {
    std::string correctChars = "0123456789 +-*/%^";
    for (const char& ch : express) {
        if (std::find(correctChars.begin(), correctChars.end(), ch) != correctChars.end()) return false;
    }
    return true;
}

bool Handler::checkIfDigit(const char& ch) {
    std::string digits = "0123456789";
    return std::find(digits.begin(), digits.end(), ch) != digits.end();
}

bool Handler::checkIfOperator(const char& ch) {
    std::string operators = "+-*/%";
    return std::find(operators.begin(), operators.end(), ch) != operators.end();
}

int Handler::stackifyExpression(Stack& stack)
{
    std::vector<int> setToCompute;
    Operator oper;
    int lenOfExpression = calculateStringLength(expression);

    if (expression.empty()) throw std::out_of_range("Cannot compute empty expressions");

    if (!checkIfCorrectExpression(expression)) throw std::out_of_range("Incorrect expression!");


    // Add digits and their operators to the new set
    for (int i = 0; i < lenOfExpression; i++) {
        char ch = expression[i];

        if (checkIfDigit(ch)) {
            stack.push(ch - '0');
        }
        else if (checkIfOperator(ch)) {

            if (stack.size() < 2) {
                // For now throw error
                throw std::out_of_range("Insufficient arguments!");
            }
            else
            {
                if (stack.isEmpty()) throw std::out_of_range("Stack is empty!");
                int operand2 = stack.pop();
                if (stack.isEmpty()) throw std::out_of_range("Stack is empty!");
                int operand1 = stack.pop();

                int result = oper.handleOperator(operand1, operand2);

                stack.push(result);
            }
        }
    }
    return stack.peek();
}

std::istream& operator>>(std::istream & is, Handler & h)
{
    std::string input;

    if (std::getline(is, input)) h.expression = input;

    return is;
    
}