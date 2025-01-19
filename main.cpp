/*
 * Individual Contributor: Eshan Mughal
 *
 * PEMDAS Calculator using stacks in c++
 *
 * This project utilizes stacks to create a PEMDAS calculator. Utilizing the stacks FILO structure, it can identify when
 * to evaluate, and it also discriminates between parentheses.
 *
 * Version 1.0 COMPLETED
 *      addition and subtraction functionality added
 *
 * Version 2.0 IN PROGRESS
 *      multiplication and operator precedence functionality currently being implemented
 *
 */

#include <iostream>
#include <stack>

using namespace std;

/***
 * Function to compute an operation on two given integers
 * @param a: first integer
 * @param b: second integer
 * @param op: provided operation
 * @return : the single number after the operation has finished
 */
int compute(int a, int b, char op){
    if(op == '+'){
        return a + b;
    }
    else{
        return a - b;
    }
}

/***
 * Reads in the entire string, breaking it down into numbers and operators, stored in stacks.
 * Evaluates as it goes.
 * @param equation: the equation to be solved in string format
 * @return : the answer to the provided equation
 */
int evaluate(const string& equation){
    stack<int> vals;
    stack<char> ops;

    for(int i=0; i<equation.length(); i++){
        char c = equation[i];

        // Case 1: a digit
        // extract the entire number and then push onto the stack
        if(isdigit(c)){
            string num = "";
            while(i < equation.length() && isdigit(equation[i])){
                num += equation[i];
                i++;
            }
            i--;
            vals.push(stoi(num));
        }
        // Case 2: open parenthesis
        // simply pushed onto the stack
        else if(c == '('){
            ops.push(c);
        }
        // Case 3: closed parenthesis
        // now that it is closed, we need to do the operations in that parenthesis
        else if(c == ')'){
            // so we need to go until we reach the beginning of the parenthesis (or end)
            while(!ops.empty() && ops.top() != '('){
                int b = vals.top();
                vals.pop();
                int a = vals.top();
                vals.pop();
                char op = ops.top();
                ops.pop();
                vals.push(compute(a,b,op));
            }
            ops.pop();
        }
        // Case 4: an operator
        // we need to evaluate everything before the operator, then push it onto the stack
        else if(c == '+' || c == '-'){
            while(!ops.empty() && ops.top() != '('){
                int b = vals.top();
                vals.pop();
                int a = vals.top();
                vals.pop();
                char op = ops.top();
                ops.pop();
                vals.push(compute(a,b,op));
            }
            ops.push(c);
        }
    }

    // Edge Case: the entire equation has been broken down into stacks
    // finishing the job, completing all the remaining
    while(!ops.empty() && ops.top() != '('){
        int b = vals.top();
        vals.pop();
        int a = vals.top();
        vals.pop();
        char op = ops.top();
        ops.pop();
        vals.push(compute(a,b,op));
    }

    return vals.top();
}

int main(int argc, char* argv[]) {
    string equation;
    getline(cin, equation);

    cout << evaluate(equation) << endl;

    return 0;
}
