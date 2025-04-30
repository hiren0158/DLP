#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <cmath>
#include <stdexcept>
using namespace std;

int precedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

bool isRightAssociative(char op) {
    return op == '^';
}

bool isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

bool isDigitOrDot(char ch) {
    return isdigit(ch) || ch == '.';
}

vector<string> infixToPostfix(const string& expr) {
    stack<char> opStack;
    vector<string> output;
    string num = "";

    for (char ch : expr) {
        if (isspace(ch)) continue;

        if (isDigitOrDot(ch)) {
            num += ch;
        } else {
            if (!num.empty()) {
                output.push_back(num);
                num = "";
            }

            if (ch == '(') {
                opStack.push(ch);
            } else if (ch == ')') {
                while (!opStack.empty() && opStack.top() != '(') {
                    output.push_back(string(1, opStack.top()));
                    opStack.pop();
                }
                opStack.pop();
            } else if (isOperator(ch)) {
                while (!opStack.empty() && isOperator(opStack.top()) &&
                       ((precedence(opStack.top()) > precedence(ch)) ||
                        (precedence(opStack.top()) == precedence(ch) && !isRightAssociative(ch)))) {
                    output.push_back(string(1, opStack.top()));
                    opStack.pop();
                }
                opStack.push(ch);
            } else {
                throw invalid_argument("Invalid character");
            }
        }
    }

    if (!num.empty()) output.push_back(num);

    while (!opStack.empty()) {
        if (opStack.top() == '(')
            throw invalid_argument("Mismatched parentheses");
        output.push_back(string(1, opStack.top()));
        opStack.pop();
    }

    return output;
}

double evaluatePostfix(const vector<string>& postfix) {
    stack<double> evalStack;

    for (const string& token : postfix) {
        if (isdigit(token[0]) || (token[0] == '-' && token.size() > 1)) {
            evalStack.push(stod(token));
        } else {
            if (evalStack.size() < 2)
                throw invalid_argument("Invalid expression");

            double b = evalStack.top(); evalStack.pop();
            double a = evalStack.top(); evalStack.pop();

            if (token == "+") evalStack.push(a + b);
            else if (token == "-") evalStack.push(a - b);
            else if (token == "*") evalStack.push(a * b);
            else if (token == "/") {
                if (b == 0) throw invalid_argument("Division by zero");
                evalStack.push(a / b);
            } else if (token == "^") evalStack.push(pow(a, b));
        }
    }

    if (evalStack.size() != 1)
        throw invalid_argument("Invalid postfix expression");

    return evalStack.top();
}

int main() {
    string input;
    cout << "Enter arithmetic expression: ";
    getline(cin, input);

    try {
        vector<string> postfix = infixToPostfix(input);
        double result = evaluatePostfix(postfix);
        cout << result << endl;
    } catch (exception& e) {
        cout << "Invalid expression" << endl;
    }

    return 0;
}
