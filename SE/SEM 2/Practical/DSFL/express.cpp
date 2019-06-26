//============================================================================
// Name        : Expression
// Author      : Ayan Gadpal
// Batch       : H11
// Roll No.    : 23370
// Description : To perform
//				1) Input Infix\n
//				2) Infix To Prefix
//				3) Infix To Postfix
//				3) Prefix and Postfix Evaluation
//============================================================================

#include <iostream>
#include "stack.h"
#include <string.h>

using namespace std;

void reverse(char *);
int prec(char);
float result(float, float, char);

//Expression class having infix postfix and prefix
class Expression
{
  private:
	char infix[40];
	char postfix[40];
	char prefix[40];

  public:
	//Default Constructor
	Expression()
	{
		infix[0] = '\0';
		postfix[0] = '\0';
		prefix[0] = '\0';
	}
	//To take Input
	void input()
	{
		//opn : Operand Count
		//opr : Operator Count
		int i, opn, opr, flag = 1;
		stack<char> S;
		//Initialization
		i = opn = opr = 0;
		cout << "\nEnter the infix :";
		cin >> infix;

		//Validation
		while (infix[i] != '\0')
		{
			if (prec(infix[i]) == 6)
			{
				if (i > 0 && prec(infix[i - 1]) == 0)
				{
					flag = 0; // TO INVALIDATE A(B+C)
					break;
				}
				S.push('(');
			}
			else if (prec(infix[i]) == 5)
			{
				if (prec(infix[i + 1]) == 0)
				{
					flag = 0; // TO INVALIDATE (B+C)D
					break;
				}
				S.pop();
			}
			else if (prec(infix[i]) >= 1 && prec(infix[i]) <= 4)
				opr++;
			else
				opn++;
			i++;
		}

		if (!(opn == opr + 1 && S.underFlow()) || flag == 0)
		{
			cout << "\n NOT VALID INPUT \n";
			//Again Taking the Input
			input();
		}
	}
	//To Display Infix
	void displayInfix()
	{
		//Validation if Infix Expression is Present or not
		if (strlen(infix) == 0)
		{
			cout << "\nNo Infix Expression Entered\n";
			return;
		}
		cout << "\nINFIX : " << strlen(infix);
	}
	//To Display Prefix
	void displayPrefix()
	{
		cout << "\nPrefix : " << prefix;
	}
	//To Display Prefix
	void displayPostfix()
	{
		cout << "\nPostfix : " << postfix;
	}
	//Infix to Prefix Conversion
	void inPrefix()
	{
		//Validation if Infix Expression is Present or not
		if (strlen(infix) == 0)
			input(); //If not taking the Infix as Input

		stack<char> S;
		int i = 0, j = 0;
		reverse(infix);
		while (infix[i] != '\0')
		{

			if (prec(infix[i]) == 0)
			{
				prefix[j] = infix[i];
				j++;
			}
			else if (!S.underFlow())
			{

				if (prec(infix[i]) == 6)
				{

					while (prec(S.Top()) != 5 && !S.underFlow())
					{
						prefix[j] = S.pop();
						j++;
					}
					S.pop();
				}
				else if (prec(infix[i]) < prec(S.Top()))
				{
					//brackets
					if (prec(S.Top()) == 5)
						S.push(infix[i]);
					else
					{
						prefix[j] = S.pop();
						j++;
						continue;
					}
				}
				else if (prec(infix[i]) >= prec(S.Top()))
				{
					//^
					if (prec(S.Top()) == 4 && prec(infix[i]) == 4) // ^
					{
						prefix[j] = S.pop();
						S.push(infix[i]);
						j++;
					}
					else
						S.push(infix[i]);
				}
			}
			else
				S.push(infix[i]);
			i++;
		}
		while (!S.underFlow())
		{
			prefix[j] = S.pop();
			j++;
		}
		prefix[j] = '\0';
		reverse(infix);
		reverse(prefix);
	}

	//INFIX TO POSTFIX CONVERSION
	void inPostfix()
	{
		//Validation if Infix Expression is Present or not
		if (strlen(infix) == 0)
			input(); //If not taking the Infix as Input

		stack<char> S;
		int i = 0, j = 0;
		while (infix[i] != '\0')
		{
			//OPERAND
			if (prec(infix[i]) == 0)
			{
				postfix[j] = infix[i];
				j++;
			}
			else if (!S.underFlow())
			{

				if (prec(infix[i]) == 5) // FOR ')'
				{

					while (prec(S.Top()) != 6 && !S.underFlow()) //FOR '('
					{
						postfix[j] = S.pop();
						j++;
					}
					S.pop();
				}
				else if (prec(infix[i]) <= prec(S.Top()))
				{
					if (prec(S.Top()) == 4 && prec(infix[i]) == 4)//'^'
						S.push(infix[i]);
					else if (prec(S.Top()) == 6)
						S.push(infix[i]);
					else
					{
						postfix[j] = S.pop();
						j++;
						continue;
					}
				}
				else if (prec(infix[i]) > prec(S.Top()))
					S.push(infix[i]);
			}
			else
				S.push(infix[i]);
			i++;
		}
		while (!S.underFlow())
		{
			postfix[j] = S.pop();
			j++;
		}
		postfix[j] = '\0';
	}
	void prefixEvalution()
	{
		stack<float> S;
		int i = 0;
		float res, op1, op2;
		reverse(prefix);
		while (prefix[i] != '\0')
		{
			if (prec(prefix[i]) == 0)
			{
				S.push((float)prefix[i] - 48.00f);
			}
			else
			{
				op1 = S.pop();
				op2 = S.pop();
				res = result(op1, op2, prefix[i]);
				S.push(res);
				cout << "\nPASS " << i << ": op1 " << op1 << " \top2 " << op2 << "\t operator " << prefix[i] << "\nResult: " << res;
			}
			i++;
		}
		cout << "\nFinal RESULT" << S.pop();
	}
	void postfixEvalution()
	{
		stack<float> S;
		int i = 0;
		float res, op1, op2;
		while (postfix[i] != '\0')
		{
			if (prec(postfix[i]) == 0)
			{
				S.push((float)postfix[i] - 48.00f);
			}
			else
			{
				op2 = S.pop();
				op1 = S.pop();
				res = result(op1, op2, postfix[i]);
				S.push(res);
				cout << "\nPASS " << i << ": op1 " << op1 << " \top2 " << op2 << "\t operator " << postfix[i] << "\nResult: " << res;
			}
			i++;
		}
		cout << "\nFinal RESULT" << S.pop();
	}
};
//TO preform Operation
float result(float op1, float op2, char op)
{
	float res;
	switch (op)
	{
	case '+':
		res = (op1 + op2);
		break;
	case '-':
		res = op1 - op2;
		break;
	case '/':
		res = op1 / op2;
		break;
	case '*':
		res = op1 * op2;
		break;
	}
	return res;
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
//Precedence Higher To Lower
int prec(char c)
{
	switch (c)
	{
	case '(':
		return 6;
	case ')':
		return 5;
	case '^':
		return 4;
	case '%':
		return 3;
	case '*':
		return 2;
	case '/':
		return 2;
	case '+':
		return 1;
	case '-':
		return 1;
	case '\0':
		return -1;
	default:
		return 0; //CHAR OR NUMBER
	}
}
//A SIMPLE LINE
void line()
{
	cout << "\n====================================================\n";
}
//START MAIN
int main()
{
	Expression E;

	int ch = 0;
	while (ch != 7)
	{
		line();
		cout << "\nEnter Your Choice\n"
				"1) Input Infix\n"
				"2) Display Infix\n"
				"3) Infix To Prefix\n"
				"4) Infix To Postfix\n"
				"5) Prefix Evaluation\n"
				"6) Postfix Evaluation\n"
				"7) EXIT\n"
				"YOUR CHOICE : ";
		cin >> ch;
		switch (ch)
		{
		case 1:
			line();
			E.input();
			break;
		case 2:
			line();
			E.displayInfix();
			break;
		case 3:
			line();
			E.inPrefix();
			E.displayPrefix();
			break;
		case 4:
			line();
			E.inPostfix();
			E.displayPostfix();
			break;
		case 5:
			line();
			E.inPrefix();
			E.displayPrefix();
			E.prefixEvalution();
			break;
		case 6:
			line();
			E.inPostfix();
			E.displayPostfix();
			E.postfixEvalution();
			break;
		}
	}
	return 0;
} //END
