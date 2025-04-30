#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

// Finite Automaton for strings with 'a' and 'b'
bool finite(const string& ip) {
    int states = 4;
    int initialstate = 1;
    int finalstate = 2;
    vector<vector<int>> transitionTable = {
        {2, 3},
        {1, 4},
        {4, 1},
        {3, 2}
    };

    int currentState = initialstate;

    for (char input : ip) {
        int idx = -1;
        if (input == 'a') {
            idx = 0;
        } else if (input == 'b') {
            idx = 1;
        } else {
            cout << "Invalid input symbol: " << input << endl;
            return false;
        }

        currentState = transitionTable[currentState - 1][idx];
    }
    return currentState == finalstate;
}

// Case 1: Validate string with '0' and '1', where every '0' is immediately followed by '11'
bool testCase1(const string& ip) {
    int n = ip.size();
    for (int i = 0; i < n; i++) {
        if (ip[i] == '0') {
            if (i + 2 >= n || ip[i + 1] != '1' && ip[i + 2] != '1') {
                return false;
            }
            i =i+ 2;
        }
    }
    return true;
}

// Case 2: string over a b c, starts and end with same letter
bool testCase2(const string& ip) {
    if (ip.empty()) return false;
    for (char ch : ip) {
        if (ch != 'a' && ch != 'b' && ch != 'c') {
            return false;
        }
    }

    return ip.front() == ip.back();
}

// Case 3: Validate string that starts with an alphabet
bool testCase3(const string& ip) {
    return !ip.empty() && isalpha(ip[0]);
}


int main() {
    string ip;

    cout << "Finite Automaton (only 'a' and 'b'): ";
    cin >> ip;
    if (finite(ip)) {
        cout << "Valid String\n";
    } else {
        cout << "Invalid String\n";
    }

    cout << "Case 1 (0 and 1 only): ";
    cin >> ip;
    if (testCase1(ip)) {
        cout << "Valid String\n";
    } else {
        cout << "Invalid String\n";
    }

    cout << "Case 2 (starts and ends with the same letter): ";
    cin >> ip;
    if (testCase2(ip)) {
        cout << "Valid String\n";
    } else {
        cout << "Invalid String\n";
    }

    cout << "Case 3 (starts with a letter): ";
    cin >> ip;
    if (testCase3(ip)) {
        cout << "Valid String\n";
    } else {
        cout << "Invalid String\n";
    }

    return 0;
}
