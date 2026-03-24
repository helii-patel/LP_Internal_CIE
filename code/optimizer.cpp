#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <cctype>
using namespace std;

int main() {
    ifstream in("../output/tac.txt");
    ofstream out("../output/optimized_tac.txt");

    string line;
    map<string, string> exprMap;

    while(getline(in, line)) {
        stringstream ss(line);
        string lhs, eq, op1, op, op2;

        ss >> lhs >> eq >> op1 >> op >> op2;

        if(op == "+" || op == "-" || op == "*" || op == "/") {

            // Constant Folding
            if(isdigit(op1[0]) && isdigit(op2[0])) {
                int a = stoi(op1);
                int b = stoi(op2);
                int res;

                if(op == "+") res = a + b;
                if(op == "-") res = a - b;
                if(op == "*") res = a * b;
                if(op == "/") res = a / b;

                out << lhs << " = " << res << endl;
                continue;
            }

            string expr = op1 + op + op2;

            // CSE
            if(exprMap.find(expr) != exprMap.end()) {
                out << lhs << " = " << exprMap[expr] << endl;
            } else {
                exprMap[expr] = lhs;
                out << line << endl;
            }
        } else {
            out << line << endl;
        }
    }

    in.close();
    out.close();
}