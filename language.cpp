#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <cctype>

using namespace std;

unordered_map<string, int> variables;

vector<Token> tokenize(const string& line) {
    vector<Token> tokens;
    istringstream stream(line);
    string word;
    while (stream >> word) {
        if (isdigit(word[0])) tokens.push_back({NUMBER, word});
        else if (word == "=") tokens.push_back({ASSIGN, word});
        else if (word == "print") tokens.push_back({PRINT, word});
        else if (isalpha(word[0])) tokens.push_back({IDENTIFIER, word});
        else tokens.push_back({INVALID, word});
    }
    return tokens;
}

void interpret(const vector<Token>& tokens) {
    if (tokens.empty()) return;

    if (tokens[0].type == PRINT && tokens.size() == 2) {
        string var = tokens[1].text;
        if (variables.count(var)) cout << variables[var] << endl;
        else cout << "Undefined variable: " << var << endl;
    } else if (tokens.size() == 3 && tokens[1].type == ASSIGN) {
        string var = tokens[0].text;
        int value = stoi(tokens[2].text);
        variables[var] = value;
    } else {
        cout << "Syntax error.\n";
    }
}
int main() {
    cout << "Welcome to Easylang! Type 'exit' to quit.\n";
    string line;
    while (true) {
        cout << ">> ";
        getline(cin, line);
        if (line == "exit") break;
        if (line.empty() || line[0] == '#') continue;

        vector<Token> tokens = tokenize(line);
        interpret(tokens);
    }
    return 0;
}
