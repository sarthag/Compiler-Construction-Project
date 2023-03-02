import json
from enum import IntEnum
import numpy as np

firstSet = []
followSet = []

with open('firstSets.json', 'r') as f:
    firstSet = json.load(f)

with open('followSets.json', 'r') as f:
    followSet = json.load(f)

class Terminals(IntEnum):
    MINUS = 0
    NE = 1
    BO = 2
    BC = 3
    MUL = 4
    COMMENTMARK = 5
    COMMA = 6
    RANGEOP = 7
    DIV = 8
    COLON = 9
    ASSIGNOP = 10
    SEMICOL = 11
    SQBO = 12
    SQBC = 13
    PLUS = 14
    LT = 15
    DEF = 16
    DRIVERDEF = 17
    LE = 18
    EQ = 19
    GT = 20
    GE = 21
    ENDDEF = 22
    DRIVERENDDEF = 23
    NUM = 24
    RNUM = 25
    ID = 26
    AND = 27
    ARRAY = 28
    BOOLEAN = 29
    BREAK = 30
    CASE = 31
    DECLARE = 32
    DEFAULT = 33
    DRIVER = 34
    END = 35
    FOR = 36
    GET_VALUE = 37
    IN = 38
    INPUT = 39
    INTEGER = 40
    MODULE = 41
    OF = 42
    OR = 43
    PARAMETERS = 44
    PRINT = 45
    PROGRAM = 46
    REAL = 47
    RETURNS = 48
    START = 49
    SWITCH = 50
    TAKES = 51
    USE = 52
    WHILE = 53
    WITH = 54
    FALSE = 55
    TRUE = 56
    DOLLAR = 57
    EPSILON = 58
class NonTerminals(IntEnum):
    actualParaList = 0
    anyTerm = 1
    arithmeticExpr = 2
    arithmeticOrBooleanExpr = 3
    arrExpr = 4
    arrFactor = 5
    arrTerm = 6
    arr_N4 = 7
    arr_N5 = 8
    assignmentStmt = 9
    boolConstt = 10
    caseStmt1 = 11
    caseStmt2 = 12
    conditionalStmt = 13
    dataType = 14
    declareStmt = 15
    default1 = 16
    driverModule = 17
    element_index_with_expressions = 18
    expression = 19
    factor = 20
    idList1 = 21
    idList2 = 22
    id_num_rnum = 23
    index_arr = 24
    index_for_loop = 25
    input_plist1 = 26
    input_plist2 = 27
    ioStmt = 28
    iterativeStmt = 29
    logicalOp = 30
    module = 31
    moduleDeclaration = 32
    moduleDeclarations = 33
    moduleDef = 34
    moduleReuseStmt = 35
    n1 = 36
    n2 = 37
    n3 = 38
    n4 = 39
    n5 = 40
    n6 = 41
    n7 = 42
    new_NT = 43
    new_index = 44
    new_index_for_loop = 45
    op1 = 46
    op2 = 47
    optional = 48
    otherModules = 49
    output_plist1 = 50
    output_plist2 = 51
    p1 = 52
    program = 53
    range_arrays = 54
    range_for_loop = 55
    relationalOp = 56
    ret = 57
    sign = 58
    sign_for_loop = 59
    simpleStmt = 60
    statement = 61
    statements = 62
    term = 63
    type = 64
    u = 65
    unary_op = 66
    value = 67
    var_id_num = 68
    var_print = 69
    valueIDStmt = 70
    valueARRStmt = 71
    whichStmt = 72


firstArr = np.zeros((74, 59), dtype=np.int32)
followArr = np.zeros((74, 59), dtype=np.int32)

print(firstSet['program'])

for nt in firstSet.keys():
    for t in firstSet[nt]:
        # print(NonTerminals[nt], Terminals[t])
        firstArr[NonTerminals[nt].value][Terminals[t].value] = 1

for nt in followSet.keys():
    for t in followSet[nt]:
        followArr[NonTerminals[nt].value][Terminals[t].value] = 1

print(NonTerminals.program.value)
print(firstArr[NonTerminals.program.value])

print(firstArr)
print(followArr)

import pickle

with open('firstArr.txt', 'w') as f:
    for row in firstArr.tolist():
        line = ','.join([str(x) for x in row])
        f.write(line + '\n')

with open('followArr.txt', 'w') as f:
    for row in followArr.tolist():
        line = ','.join([str(x) for x in row])
        f.write(line + '\n')

# with open('firstArr.pkl', 'wb') as f:
#     pickle.dump(firstArr.tolist(), f)

# with open('followArr.pkl', 'wb') as f:
#     pickle.dump(followArr.tolist(), f)

# print(Terminals['TAKES'].value)

# print(firstSet)