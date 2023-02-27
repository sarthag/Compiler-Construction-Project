#ifndef ADT_H
#define ADT_H 

#include "adtDef.h"

void initStack(struct Stack* stack);
int isEmptyStack(struct Stack* stack);
void push(struct Stack* stack, int id, node_type nodeType);
int pop(struct Stack* stack);

#endif