#include <iostream>
#include "stack.h"
using namespace std;

int precedence(char);

inline void Line()
{
    cout << "\n====================================\n"; // Line
}

int precedence(char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return 0;
    if (c == '+' || c == '-')
        return 1;
    if (c == '/' || c == '*')
        return 2;
    if (c == '^')
        return 3;
    if (c == '(')
        return 6;
    if (c == ')')
        return 5;
}
float result(float n1, char op, float n2)
{
    float res = n1;
    switch (op)
    {
    case '+':
        return (n1 + n2);

        break;
    case '-':
        return (n1 - n2);
        break;
    case '/':
        return (n1 / n2);
        break;
    case '*':
        return (n1 * n2);
        break;
    case '^':

        for (int i = 1; i < n2; i++)
            res = res * n1;
        return res;
        break;

    default:
        break;
    }
}

//String Reverse Function
void reverse(char *s)
{
    int i = 0, k = 0, t;
    char c;
    while (s[i] != '\0')
        i++;
    i--;
    t = i;
    while (i > t / 2)
    {
        //Swapping
        c = s[i];
        s[i] = s[k];
        s[k] = c;
        k++;
        i--;
    }
}

class Expression
{
  public:
    char infix[40];
    char postfix[40];
    char prefix[40];
    void input() // Accept and validate the infix expression from user
    {
        cout << "\nEnter The infix Expression : ";
        cin >> infix;
    }

    void toPrefix()
    {
        Stack<char> S;
        int i, j;
        i = j = 0;
        reverse(infix);
        while (infix[i] != '\0')
        {
            if (precedence(infix[i]) == 0) // Operands
            {
                prefix[j] = infix[i];
                j++;
            }
            else if (!S.isEmpty())
            {
                if (precedence(infix[i]) == 6) // '('
                {

                    while (precedence(S.seek()) != 5) // Till ')'
                    {
                        prefix[j] = S.pop();
                        j++;
                    }
                    S.pop(); // Removing '('
                }
                else if (precedence(infix[i]) < precedence(S.seek())) // INCOMING IS LESS
                {
                    if (precedence(S.seek()) == 5) // FOR ')'
                        S.push(infix[i]);
                    else
                    {
                        prefix[j] = S.pop();
                        j++;
                        continue;
                    }
                }
                else if (precedence(infix[i]) >= precedence(S.seek())) // INCOMING IS GREATER
                {
                    if (precedence(S.seek()) == 4 && precedence(infix[4])) // FOR '^'
                    {
                        prefix[j] = S.pop();
                        j++;
                    }
                    S.push(infix[i]);
                }
            }
            else
                S.push(infix[i]);

            i++;
        }
        while (!S.isEmpty()) // POP THE REMAINING OPERATORS
        {

            prefix[j] = S.pop();
            j++;
        }
        prefix[j] = '\0';
        reverse(infix);
        reverse(prefix);
    }

    void toPostfix() //A*B+C/D
    {
        Stack<char> S;
        int i, j;
        i = j = 0;
        while (infix[i] != '\0')
        {
            if (precedence(infix[i]) == 0)
            {
                postfix[j] = infix[i];
                j++;
            }
            else if (!S.isEmpty())
            {
                if (precedence(infix[i]) == 5) // ')'
                {

                    while (precedence(S.seek()) != 6) // Till '('
                    {

                        postfix[j] = S.pop();
                        j++;
                    }
                    S.pop(); // Removing '('
                }
                else if (precedence(infix[i]) <= precedence(S.seek()))
                {
                    if ((precedence(S.seek()) == 4 && precedence(infix[i]) == 4) || (precedence(S.seek()) == 6)) //^
                        S.push(infix[i]);
                    else
                    {
                        postfix[j] = S.pop();
                        j++;
                        continue;
                    }
                }
                else if (precedence(infix[i]) > precedence(S.seek()))
                    S.push(infix[i]);
            }
            else
                S.push(infix[i]);

            i++;
        }
        while (!S.isEmpty())
        {

            postfix[j] = S.pop();
            j++;
        }
        postfix[j] = '\0';
    }
    void postfixEvalutaion()
    {
        Stack<float> S;
        int i;
        float num, num2,res;
        for (i = 0; postfix[i] != '\0'; i++)
        {
            if (precedence(postfix[i]) == 0)
            {
                cout << "Enter the value for " << postfix[i] << " : ";
                cin >> num;
                cout << "\nPUSH : " << num;
                S.push(num);
            }
            else if (precedence(postfix[i]) >= 1 && precedence(postfix[i]) <= 3)
            {
                num = S.pop();
                num2 = S.pop();
                res = result(num2, postfix[i], num);
                cout << "\nresult : " << res;
                S.push(res);
            }
        }
        cout << "\nResult : " << S.pop();
    }

    void prefixEvalutaion()
    {

        Stack<float> S;
        int i;
        float num, num2,res;
        reverse(prefix);
        for (i = 0; prefix[i] != '\0'; i++)
        {
            if (precedence(prefix[i]) == 0)
            {
                cout << "Enter the value for " << prefix[i] << " : ";
                cin >> num;
                cout << "\nPUSH : " << num;
                S.push(num);
            }
            else if (precedence(prefix[i]) >= 1 && precedence(prefix[i]) <= 3)
            {
                num = S.pop();
                num2 = S.pop();
                res = result(num, prefix[i], num2);
                cout << "\nresult : " << res;
                S.push(res);
            }
        }
        cout << "\nResult : " << S.pop();
        reverse(prefix);
    }
};

int main()
{
    int ch;
    Expression E;
    cout << "/n TOP " << result(2, '^', 3);
    while (1)
    {
        Line();
        cout << "\n ___________________________________"
                "\n|               MENU                |"
                "\n|   1) Enter Infix Expression       |"
                "\n|   2) Display Infix                |"
                "\n|   3) Display Postfix              |"
                "\n|   4) Display Prefix               |"
                "\n|   5) Postfix Evaluation           |"
                "\n|   6) Prefix Evaluation            |"
                "\n|   7) Exit                         |"
                "\n-------------------------------------"
                "\nYour Choice : ";
        cin >> ch;
        switch (ch)
        {

        //Choice 1 : Input infix Expression (A-B/C)*(A/K-L)
        case 1:

            E.input();
            E.toPostfix();
            E.toPrefix();

            break;

        //Choice 2 : Display infix Expression
        case 2:
            cout << "\nINFIX :" << E.infix;
            break;

        //Choice 3 : Display postfix Expression
        case 3:
            cout << "\nPostfix : " << E.postfix;
            break;

        //Choice 4 : Display prefix Expression
        case 4:
            cout << "\nPrefix : " << E.prefix;
            break;

        //Choice 5 : 
        case 5:
            E.postfixEvalutaion();
            break;

        //Choice 6 :
        case 6:
            break;

        //Choice 7: To exit from the program
        case 7:
            exit(0);
            break;

        default:
            break;
        }
    }

    return 0;
}