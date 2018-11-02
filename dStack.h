#ifndef DSTACK_H
#define DSTACK_H

typedef struct dtagStack
{
	double fKey;
	dtagStack* pNext;

} dStack;

dStack* dInitStack();
void dRemoveStack(dStack ** pStack);
void dpush(double c, dStack** pStack);
double dpop(dStack** pStack);
double dtop(dStack* pStack);
void ddel(dStack** pStack);
int disEmpty(dStack* pStack);

#endif
