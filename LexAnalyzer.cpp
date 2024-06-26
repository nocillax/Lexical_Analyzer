#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <set>
#include <map>
using namespace std;

// Function to read the file
string readFile() {
    string outputString = "";
    string x;
    fstream newfile;

    newfile.open("input.txt", ios::in);
    if (newfile.is_open()) {
        while (getline(newfile, x)) {
            outputString += x + "\n";
        }
        newfile.close();
    } else {
        cout << "Error: Unable to open the file." << endl;
    }
    return outputString;
}

bool isNum(char c){

    bool isNum = false;

    if(c >= '0' && c <= '9'){
        isNum = true;
    }
    else {
        return false;
    }

    return isNum;
}

bool isConstant(const string& word) {
    if (word.empty()) return false;

    bool isConst = false;

    for (char c : word) {
        if (isNum(c) || (word.front() == '"' && word.back() == '"') || (word.front() == '\'' && word.back() == '\'') ) {
            isConst = true;
        } else {
            return false; // Constants can only contain digits, single quotes, or double quotes.
        }
    }

    return isConst;
}

bool isIdentifier(const string& word) {
    if (word.empty()) return false;

    // Check for invalid characters in the first loop
    for (char c : word) {
        if (!((c >= 'a' && c <= 'z') ||
              (c >= 'A' && c <= 'Z') ||
              (c == '_') ||
              (c >= '0' && c <= '9'))) {
            return false;
        }
    }

    // Check for digits and additional symbols in the second loop
    for(int i = 0; i < word.length(); i++) {
        if ( (word[i] >= '0' && word[i] <= '9') || 
           (word[i] == '+' || word[i] == '-' || word[i] == '*' || word[i] == '/' || word[i] == '%' ||
            word[i] == '=' || word[i] == '!' || word[i] == '<' || word[i] == '>' || word[i] == '&' ||
            word[i] == '|' || word[i] == '^' || word[i] == '~' || word[i] == '.' || word[i] == ',' ||
            word[i] == ';' || word[i] == ':' || word[i] == '\"' || word[i] == '\'' ||
            word[i] == '(' || word[i] == ')' || word[i] == '[' || word[i] == ']' || word[i] == '{' || word[i] == '}') 
            ) {
            return false;
        }
    }

    // If no invalid characters are found, return true
    return true;
}



int main() {
    string text;
    text = readFile();

    // Split the text into lines
    stringstream ss(text);
    string line;

    set<string> keywords = {
        "if", "else", "switch", "case", "default",
        "for", "while", "do", "break", "continue", "return",
        "int", "char", "float", "double", "string", "bool", "void", "auto", "const",
        "static", "extern", "register", "mutable", "class", "struct", "this",
        "new", "delete", "public", "private", "protected",
        "namespace", "try", "catch", "throw", "true", "false",
        "inline", "explicit", "virtual"
    };

    set<string> operators = {
        "=", "+", "-", "*", "/", "%", "==", "!=", "<", ">", "<=", ">=", "&&", "||", "!", "&", "|", "^", "~"
    };

    set<string> punctuation = {
        ",", ".", ";", ":", "\"", "'", "(", ")", "[", "]", "{", "}"
    };

    while (getline(ss, line, '\n')) {
        cout << "Analyzing line: " << line << endl;

        istringstream lineStream(line);
        string word;
        vector<string> invalidIdentifiers;  
        map<string, vector<string>> lineCategories;


        while (lineStream >> word) {
            // Process each word in the line

            if (keywords.find(word) != keywords.end()) {
                lineCategories["Keywords"].push_back(word);
            } else if (operators.find(word) != operators.end()) {
                lineCategories["Operators"].push_back(word);
            } else if (punctuation.find(word) != punctuation.end()) {
                lineCategories["Punctuation"].push_back(word);
            } else if (isConstant(word)) {
                lineCategories["Constants"].push_back(word);
            } else if (!isIdentifier(word)) {
                invalidIdentifiers.push_back(word); // Store invalid identifier for the current line
            } else {
                lineCategories["Identifiers"].push_back(word);
            }
        }
        

        for (const auto &category : lineCategories) {
            if (!category.second.empty()) {
                cout << category.first << " : ";
                for (size_t i = 0; i < category.second.size(); ++i) {
                    cout << category.second[i];
                    if (i < category.second.size() - 1) {
                        cout << "  ";
                    }
                }
                cout << endl;
            }
        }

        // Display invalid identifiers for the current line
        if (!invalidIdentifiers.empty()) {
            cout << "Invalid Identifiers:";
            for (const string& invalidIdentifier : invalidIdentifiers) {
                cout << " " << invalidIdentifier;
            }
            cout << endl;
        }

        cout << endl;
        cout << "------------------------------------------------------------------"<< endl;
        cout << endl;
    }
}
