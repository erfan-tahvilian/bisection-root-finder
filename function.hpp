#include <math.h>
using namespace std;

template<class type, int length>
class Stack {
    int top;
    type items[length];

public:
    Stack() {
        top = -1;
    }

    bool empty() {
        if (top == -1)
            return true;
        return false;
    }

    bool push(type x) {
        if (top == length-1)
            return false;
        items[++top] = x;
        return true;
    }

    type pop() {
        if (empty()) {
            cout << "Stack is empty" << endl;
            exit(1);
        }
        return items[top--];
    }

    type stackTop() {
        if (empty()) {
            cout << "Stack is empty" << endl;
            exit(1);
        }
        return items[top];
    }
};
bool precedence(char op1, char op2) {
    if (op1 == '(' || op2 == '(')
        return false;
    if (op1 == 's' || op1 == 'c')
        return true;
    if (op2 == 's' || op2 == 'c')
        return false;
    if (op1 == '!')
        return true;
    if (op2 == '!')
        return false;
    if (op2 == '^')
        return false;
    if (op1 == '^')
        return true;
    if (op2 == '_')
        return false;
    if (op1 == '_')
        return true;
    if (op1 == '*' || op1 == '/')
        return true;
    if (op2 == '*' || op2 == '/')
        return false;
    if (op1 == '+' || op1 == '-')
        return true;
    if (op2 == '+' || op2 == '-')
        return false;
}

void infixConverter(char infix[], char infix2[]) {
    int i, j;
    i = j = 0;
    while (infix[i] != '\0') {
        if (infix[i+1] != '\0' && isdigit(infix[i]) && (isdigit(infix[i+1]) || infix[i+1] == '.')) {
            infix2[j++] = '~';
            infix2[j++] = infix[i++];
            while (infix[i] != '\0' && (isdigit(infix[i]) || infix[i] == '.')) {
                infix2[j++] = infix[i++];
            }
            infix2[j++] = '~';
            continue;
        }
        else if (infix[i] == 's') {
            i += 2;
            infix2[j++] = 's';
        } else if (infix[i] == 'c') {
            i += 2;
            infix2[j++] = 'c';
        } else if (i != 0 && infix[i] == '-' && (infix[i-1] == 'x' || infix[i-1] == ')' || isdigit(infix[i-1])))
            infix2[j++] = '-';
        else if (infix[i] != '-')
            infix2[j++] = infix[i];
        else
            infix2[j++] = '_';
        i++;
    }
    infix2[j] = '\0';
}

void postfixConverter(char infix[], char postfix[]) {
    Stack <char, 100> stack;
    int i, j;
    i = j = 0;
    while (infix[i] != '\0') {
        if (infix[i] == 'x' || isdigit(infix[i]) || infix[i] == '.' || infix[i] == '~')
            postfix[j++] = infix[i];
        else {
            if (infix[i] == ')') {
                while (!stack.empty()) {
                    if (stack.stackTop() == '(') {
                        stack.pop();
                        break;
                    } else
                        postfix[j++] = stack.pop();
                }
            } else {
                while (!stack.empty() && precedence(stack.stackTop(), infix[i])) {
                    postfix[j++] = stack.pop();
                }
                stack.push(infix[i]);
            }

        }
        i++;
    }
    while (!stack.empty())
        postfix[j++] = stack.pop();
    postfix[j] = '\0';
}

double postfixCalculator(char postfix[], double x) {
    Stack <double, 100> stack;
    int i = 0;
    while (postfix[i] != '\0') {
        if (postfix[i] == 'x')
            stack.push(x);
        else if (postfix[i] == '~') {
            i++;
            string temp;
            while (postfix[i] != '~')
                temp += postfix[i++];
            stack.push(stod(temp));
        }
        else if (isdigit(postfix[i]))
            stack.push(postfix[i]-48);
        else {
            if (postfix[i] == '!') {
                double fact = 1;
                double x = stack.pop();
                for (int j = 2; j <= x; j++)
                    fact *= j;
                stack.push(fact);
            }
            else if (postfix[i] == 's') {
                double x = stack.pop();
                stack.push(sin(x));
            }
            else if (postfix[i] == 'c') {
                double x = stack.pop();
                stack.push(cos(x));
            }
            else if (postfix[i] == '^') {
                double x = stack.pop();
                double y = stack.pop();
                stack.push(pow(y, x));
            }
            else if (postfix[i] == '*') {
                double x = stack.pop();
                double y = stack.pop();
                stack.push(y*x);
            }
            else if (postfix[i] == '/') {
                double x = stack.pop();
                double y = stack.pop();
                stack.push(y/x);
            }
            else if (postfix[i] == '+') {
                double x = stack.pop();
                double y = stack.pop();
                stack.push(y+x);
            }
            else if (postfix[i] == '-') {
                double x = stack.pop();
                double y = stack.pop();
                stack.push(y-x);
            }
            else if (postfix[i] == '_') {
                double x = stack.pop();
                stack.push(-x);
            }
        }
        i++;
    }
    return stack.pop();
}

int parentheses(string infix) {
    Stack <char, 100> stack;
    int i, j;
    i = j = 0;
    while (infix[i] != '\0') {
        if (infix[i] == '(')
            stack.push(infix[i]);
        if (infix[i] == ')') {
            if (stack.empty())
                return -1;
            else
                stack.pop();
        }
        i++;
    }
    if (!stack.empty())
        return 0;
    return 1;
}

double function(string func, double x) {
    char f[100], f1[100], f2[100];
    strcpy(f1, func.c_str());
    infixConverter(f1, f2);
    postfixConverter(f2, f);
    double result = postfixCalculator(f, x);
    return result;
}