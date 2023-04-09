#ifndef CODEGEN_H
#define CODEGEN_H 

#include "codeGenDef.h"
#include <stdio.h>

void generateAssembly(FILE* asmFile);

void readWriteST(bool isRead, int width, symbolRecord* rec, FILE* asmFile);
#endif