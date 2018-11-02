#include "dStack.h"
#include <iostream>
#include <stdlib.h>
#include <memory.h>
using namespace std;


//-----------------------------------
dStack* dInitStack()
{
	return NULL;
}
//----------------------------------------
void dRemoveStack(dStack ** pStack)
{
	while (!disEmpty(*pStack))
		ddel(pStack);
	*pStack = NULL;
}
//---------------------------------------------------
//insert a new character c into stack
void dpush(double c, dStack** pStack)
{
	dStack* v = (dStack*)malloc(sizeof(dStack)); //malloc ma byc takiego typu jak na poczatku linijki
	if (v) // if(v!=NULL)
	{
		memset(v, 0, sizeof(dStack));
		v->fKey = c;//(*v).fKey = c; upierdliwe
		//dowiazanie
		v->pNext = *pStack;
		*pStack = v;
	}
	else
		perror("ERROR push: stack overflow");
}

//--------------------------------------
//get the top character from the stack and delete it
double dpop(dStack** pStack)
{
	if (!disEmpty(*pStack))
	{
		double c = dtop(*pStack);
		ddel(pStack);
		return c;
	}
	perror("ERROR pop: dstack underflow");
	return 0;
}

//----------------------------------------
//get the top character from the stack
double dtop(dStack* pStack)
{
	if (!disEmpty(pStack))
		return pStack->fKey;

	return 0;
}

//---------------------------------------
//delete the top character from the stack
void ddel(dStack** pStack)
{
	if (!disEmpty(*pStack))
	{
		dStack* p = *pStack;
		*pStack = p->pNext; // *pStack = (*pStack)->pNext;
		free(p); //nie gwarantuje NULL-a!!
	}
	else
		perror("ERROR del: Stack underflow");
}

//----------------------------------------------
//return TRUE if the stack is empty and FALSE..
int disEmpty(dStack* pStack)
{
	return !pStack;
}