#include <stdio.h>
#include <math.h>
#include "Stack.h"
#include "dStack.h"
#include <iostream>

using namespace std;

#define DOT '.'
//-----NAGLOWKI FUNKCJI--------------
void Calc();
double GetNum();
char GetOper();
void SkipSpaces();
int prior(char cOper);
int isDigit(char c); 
int isOper(char cOper);
double Eval(char cOper, double arg1, double arg2);
//-----------------------------------


int main(int argc, char* argv[])
{

	printf("Podaj wyrazenie: ");

	Calc();
	
	printf("\n\nKONIEC\n");
	getchar();

	return 0;
	
}

//----------------------------------
void Calc()
{
	Stack* pStack = InitStack();
	dStack* dpStack = dInitStack(); 
	
	char c;
	int isPos = 1;
	dpush(GetNum(), &dpStack);
	while (isOper(c = GetOper()))
	{
		//prior operatora MUSI byc silnie wiekszy od prior szczytu stosu
		char x = GetOper();
		if (x == '-')
		{
			isPos = -1;
		}
		else
		{
			ungetc(x, stdin);
		}

		if (c == '(')
		{
			push(c, &pStack);
			dpush(GetNum()*isPos, &dpStack);
		}
		else if (c == ')') 
		{
			while ((c = pop(&pStack)) != '(')
			{
				double arg = dpop(&dpStack);
				dpush(Eval(c, dpop(&dpStack), arg ), &dpStack);
			}
		}
		else
		{
			while (prior(c) <= prior(top(pStack)))
			{
				double arg = dpop(&dpStack);
				dpush(Eval(pop(&pStack), dpop(&dpStack), arg) , &dpStack);
			}
			push(c, &pStack);
			c = GetOper();
			ungetc(c, stdin);
			if(!isOper(c)) dpush(GetNum()*isPos, &dpStack);
		}
		isPos = 1;
	}
	while (!isEmpty(pStack))
	{
		double arg = dpop(&dpStack);
		dpush(Eval(pop(&pStack), dpop(&dpStack), arg), &dpStack);
	}
	
	printf("WYNIK: %0.2lf", dtop(dpStack));
	RemoveStack(&pStack);
	dRemoveStack(&dpStack);

	
}


//------------------------
double GetNum()// pobiera liczbe zmiennoprzecinkowa
{
	char c;
	double res = 0; //uzywamy Hornera

	SkipSpaces();

	while (isDigit(c = getc(stdin)))
	{
		res = res * 10 + (c - '0');
	}

	if (c == DOT)
	{
		double coef = 0.1;
		while (isDigit(c = getc(stdin)))
		{
			res = res + (c - '0') * coef;
			coef *= 0.1;
		}
	}

	ungetc(c, stdin);
	return res;

}

//----------------------------
char GetOper()
{
	SkipSpaces();
	return getc(stdin); // getchar() zwraca znak ze standardowego wejscia
}

//---------------------------------
void SkipSpaces()
{
	char c;
	while ((c = getchar()) == ' ');
	ungetc(c, stdin);
}

//---------------------------
int prior(char cOper) // funkcja przypisuje operatorom odpowiedni priorytet
{
	switch (cOper)
	{
	case '(':
	case ')': return 1;
	case '+':
	case '-': return 2;
	case '*':
	case '/': return 3;
	case '^':return 4;
	}
	return 0;

}

//-----------------------------
int isDigit(char c)
{
	return (c >= '0') && (c <= '9');
}

//------------------------------
int isOper(char cOper)
{
	switch (cOper)
	{
	case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '^': return 1;
	default: return 0;
	}
}

//---------------------------
double Eval(char cOper, double arg1, double arg2)
{
	switch (cOper)
	{
	case '+': return arg1 + arg2;
	case '-': return arg1 - arg2;
	case '*': return arg1 * arg2;
	case '/': if (arg2 >= 1e-14) return arg1 / arg2;
		perror("ERROR: division by 0!!");
		break;
	case '^': return pow(arg1, arg2);
	}
	return 0;
}

//---------------------------------------