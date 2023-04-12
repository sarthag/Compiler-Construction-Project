#ifndef CODEGEN2_H
#define CODEGEN2_H 

#include "codeGenDef.h"
#include <stdio.h>

void generateAssembly(FILE* asmFile, astNode* astRoot);

#endif