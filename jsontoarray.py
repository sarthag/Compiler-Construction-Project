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
    array_element_for_print = 9
    assignmentStmt = 10
    boolConstt = 11
    caseStmt1 = 12
    caseStmt2 = 13
    conditionalStmt = 14
    dataType = 15
    declareStmt = 16
    default1 = 17
    driverModule = 18
    element_index_with_expressions = 19
    expression = 20
    factor = 21
    idList1 = 22
    idList2 = 23
    id_num_rnum = 24
    index_arr = 25
    index_for_loop = 26
    input_plist1 = 27
    input_plist2 = 28
    ioStmt = 29
    iterativeStmt = 30
    logicalOp = 31
    module = 32
    moduleDeclaration = 33
    moduleDeclarations = 34
    moduleDef = 35
    moduleReuseStmt = 36
    n1 = 37
    n2 = 38
    n3 = 39
    n4 = 40
    n5 = 41
    n6 = 42
    n7 = 43
    new_NT = 44
    new_index = 45
    new_index_for_loop = 46
    op1 = 47
    op2 = 48
    optional = 49
    otherModules = 50
    output_plist1 = 51
    output_plist2 = 52
    p1 = 53
    program = 54
    range_arrays = 55
    range_for_loop = 56
    relationalOp = 57
    ret = 58
    sign = 59
    sign_for_loop = 60
    simpleStmt = 61
    statement = 62
    statements = 63
    term = 64
    type = 65
    u = 66
    unary_op = 67
    value = 68
    var_id_num = 69
    var_print = 70
    valueIDStmt = 71
    valueARRStmt = 72
    whichStmt = 73

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