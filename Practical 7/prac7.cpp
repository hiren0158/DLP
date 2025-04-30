#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>

using namespace std;

map<char, set<char>> firstSets, followSets;
map<char, vector<string>> productions;
set<char> visitedFollow;
char startSymbol;

// Compute FIRST set
void computeFirst(char symbol) {
    if (!isupper(symbol)) {
        firstSets[symbol].insert(symbol);
        return;
    }

    for (string rule : productions[symbol]) {
        bool containsNull = true;

        for (char ch : rule) {
            computeFirst(ch);

            for (char firstVal : firstSets[ch]) {
                if (firstVal != '#')
                    firstSets[symbol].insert(firstVal);
            }

            if (firstSets[ch].count('#') == 0) {
                containsNull = false;
                break;
            }
        }

        if (containsNull)
            firstSets[symbol].insert('#');
    }
}

// Improved FOLLOW set logic
void computeFollow(char nonTerminal) {
    if (visitedFollow.count(nonTerminal)) return;
    visitedFollow.insert(nonTerminal);

    if (nonTerminal == startSymbol) {
        followSets[nonTerminal].insert('$');
    }

    for (auto rule : productions) {
        char lhs = rule.first;
        for (string prod : rule.second) {
            for (int i = 0; i < prod.size(); i++) {
                if (prod[i] == nonTerminal) {
                    if (i + 1 < prod.size()) {
                        char next = prod[i + 1];
                        if (!isupper(next)) {
                            followSets[nonTerminal].insert(next);
                        } else {
                            for (char ch : firstSets[next]) {
                                if (ch != '#')
                                    followSets[nonTerminal].insert(ch);
                            }

                            if (firstSets[next].count('#')) {
                                computeFollow(lhs);
                                for (char ch : followSets[lhs]) {
                                    followSets[nonTerminal].insert(ch);
                                }
                            }
                        }
                    } else {
                        if (lhs != nonTerminal) {
                            computeFollow(lhs);
                            for (char ch : followSets[lhs]) {
                                followSets[nonTerminal].insert(ch);
                            }
                        }
                    }
                }
            }
        }
    }
}

void displaySets(string setName, map<char, set<char>> &sets, bool excludeTerminals) {
    cout << setName << " sets:\n";
    for (auto &entry : sets) {
        if (excludeTerminals && !isupper(entry.first)) continue;

        cout << entry.first << " = { ";
        for (char ch : entry.second) {
            cout << ch << " ";
        }
        cout << "}\n";
    }
}

int main() {
    productions = {
        {'S', {"ABC", "D"}},
        {'A', {"a", "#"}},
        {'B', {"b", "#"}},
        {'C', {"(S)", "c"}},
        {'D', {"AC"}}
    };

    startSymbol = 'S';

    for (auto &prod : productions) {
        computeFirst(prod.first);
    }

    for (auto &prod : productions) {
        computeFollow(prod.first);
    }

    displaySets("First", firstSets, true);
    displaySets("Follow", followSets, false);

    return 0;
}
