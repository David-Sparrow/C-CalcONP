#include "Stack.h"
#include <iostream>
#include <stdlib.h>
#include <memory.h>
using namespace std;


//-----------------------------------
Stack* InitStack()
{
	return NULL;
}

//----------------------------------------
void RemoveStack(Stack ** pStack)
{
	while (!isEmpty(*pStack))
		del(pStack);
	*pStack = NULL;
}

//---------------------------------------------------
//insert a new character c into stack
void push(char c, Stack** pStack)
{
	Stack* v = (Stack*)malloc(sizeof(Stack)); //malloc ma byc takiego typu jak na poczatku linijki
	if (v) // if(v!=NULL)
	{
		memset(v, 0, sizeof(Stack));
		v->cKey = c;//(*v).cKey = c; upierdliwe
		//dowiazanie
		v->pNext = *pStack;
		*pStack = v;
	}
	else
		perror("ERROR push: stack overflow");
}

//--------------------------------------
//get the top character from the stack and delete it
char pop(Stack** pStack)
{
	if (!isEmpty(*pStack))
	{
		char c = top(*pStack);
		del(pStack);
		return c;
	}
	perror("ERROR pop: stack underflow");
	return 0;
}

//----------------------------------------
//get the top character from the stack
char top(Stack* pStack)
{
	if (!isEmpty(pStack))
		return pStack->cKey;

	return 0;
}

//---------------------------------------
//delete the top character from the stack
void del(Stack** pStack)
{
	if (!isEmpty(*pStack))
	{
		Stack* p = *pStack;
		*pStack = p->pNext; // *pStack = (*pStack)->pNext;
		free(p); //nie gwarantuje NULL-a!!
	}
	else
		perror("ERROR del: Stack underflow");
}

//----------------------------------------------
//return TRUE if the stack is empty and FALSE..
int isEmpty(Stack* pStack)
{
	return !pStack;
}