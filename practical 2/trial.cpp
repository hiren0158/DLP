#include <iostream>
using namespace std;

const int MAX = 100;  // Max states and symbols

int main() {
    int numSymbols;
    cout << "Enter number of input symbols: ";
    cin >> numSymbols;

    char symbols[MAX];
    int symbolIndex[256] = {0};  // map symbol to column index

    cout << "Enter input symbols: ";
    for (int i = 0; i < numSymbols; i++) {
        cin >> symbols[i];
        symbolIndex[symbols[i]] = i;
    }

    int numStates;
    cout << "Enter number of states: ";
    cin >> numStates;

    int transitionTable[MAX][MAX];

   

    int initialState;
    cout << "Enter initial state: ";
    cin >> initialState;

    int numAccepting;
    cout << "Enter number of accepting states: ";
    cin >> numAccepting;

    int acceptingStates[MAX] = {0};
    cout << "Enter accepting states: ";
    for (int i = 0; i < numAccepting; i++) {
        int state;
        cin >> state;
        acceptingStates[state] = 1;
    }
    cout << "Enter transitions (from_state symbol to_state): \n";
    for (int i = 0; i < numStates * numSymbols; i++) {
        int from, to;
        char sym;
        cin >> from >> sym >> to;
        int col = symbolIndex[sym];
        transitionTable[from][col] = to;
    }

    string input;
    cout << "Enter input string: ";
    cin >> input;

    // Run the FA
    int currentState = initialState;
    for (int i = 0; i < input.length(); i++) {
        char ch = input[i];
        if (symbolIndex[ch] == 0 && ch != symbols[0]) {
            cout << "Invalid symbol: " << ch << endl;
            return 0;
        }
        int col = symbolIndex[ch];
        currentState = transitionTable[currentState][col];
    }

    if (acceptingStates[currentState]) {
        cout << "Valid String (Accepted by FA)\n";
    } else {
        cout << "Invalid String (Rejected by FA)\n";
    }

    return 0;
}
