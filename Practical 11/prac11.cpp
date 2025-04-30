#include <iostream>
#include <vector>
#include <stack>
#include <sstream>
using namespace std;
struct Quad {
    string op;    
    string val1;  
    string val2;   
    string res;   
};

bool isOp(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

string toPostfix(string expr) {
    stack<char> ops;  
    string result;
    string number;     

    for (char ch : expr) {
        if (isdigit(ch)) {
            number += ch;  
        } else {
            if (!number.empty()) {
                result += number + " ";  
                number = "";
            }
            if (isOp(ch)) {
                while (!ops.empty() && precedence(ops.top()) >= precedence(ch)) {
                    result += ops.top();
                    result += " ";
                    ops.pop();
                }
                ops.push(ch);
            }
        }
    }


    if (!number.empty()) {
        result += number + " ";
    }

    while (!ops.empty()) {
        result += ops.top();
        result += " ";
        ops.pop();
    }

    return result;
}

vector<Quad> makeQuadruples(string postfix) {
    vector<Quad> quads;
    stack<string> values;
    stringstream ss(postfix);
    string token;
    int tempCount = 1;

    while (ss >> token) {
        if (isdigit(token[0])) {
            values.push(token); 

            string val2 = values.top();
            values.pop();
            string val1 = values.top();
            values.pop();

            string tempVar = "t" + to_string(tempCount++);
            quads.push_back({token, val1, val2, tempVar});
            values.push(tempVar);
        }
    }

    return quads;
}


void showQuadruples(vector<Quad> quads) {
    cout << "Operator\tOperand1\tOperand2\tResult" << endl;
    for (Quad q : quads) {
        cout << q.op << "\t\t" << q.val1 << "\t\t" << q.val2 << "\t\t" << q.res << endl;
    }
}

int main() {
    string expr;
    cout << "Enter an arithmetic expression (e.g., 9+42*8): ";
    cin >> expr;

    string postfixExpr = toPostfix(expr);
    vector<Quad> quads = makeQuadruples(postfixExpr);

    cout << "\nQuadruple Table:\n";
    showQuadruples(quads);

    return 0;
}
