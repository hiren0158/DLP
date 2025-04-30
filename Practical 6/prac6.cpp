#include <iostream>
#include <string>
using namespace std;

class RDP {
    string input;
    int pos;

    char peek() { return pos < input.size() ? input[pos] : '\0'; }
    void advance() { pos++; }

public:
    RDP(const string &str) : input(str), pos(0) {}
    bool parse() { return S() && pos == input.size(); }
    
    bool S() {
        if (peek() == '(') { 
            advance(); 
            if (L() && peek() == ')') { advance(); return true; }
            return false;
        } 
        if (peek() == 'a') { advance(); return true; }
        return false;
    }
    
    bool L() {
        if (!S()) return false;
        while (peek() == ',') { advance(); if (!S()) return false; }
        return true;
    }
};

int main() {
    string testCases[] = {"a", "(a)", "(a,a)", "(a,(a,a),a)","(a,a),(a,a)", "a)", "(a", "a,a","a,","(a,a),a"};
    for (const string &test : testCases) {
        cout << "Input: " << test << " -> " << (RDP(test).parse() ? "Valid String" : "Invalid String") << endl;
    }
    return 0;
}
