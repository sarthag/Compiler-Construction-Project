from pprint import pprint
import json
def add(listA,x):
    if x not in listA: listA.append(x)
# def first_set(G,T,Nt):
#     firstA = {}
#     tempA = {}
#     for NonT in Nt: firstA[NonT] = []
#     while True:
#         for NonT in Nt:
#             tempA[NonT] = [i for i in firstA[NonT]]
#         for i in range(len(G)):
#             lhs = G[i][0]
#             rhs = G[i][1]   
#             if rhs == ['EPSILON']: 
#                 add(tempA[lhs],'EPSILON')
#             elif rhs[0] in Nt:
#                 if 'EPSILON' not in firstA[rhs[0]]:
#                     for k in firstA[rhs[0]]: add(tempA[lhs],k)
#                 else:
#                     listA = [k for k in firstA[rhs[0]] if k != 'EPSILON']
#                     for j in range(1, len(rhs)):
#                         if rhs[j] not in Nt: continue
#                         if 'EPSILON' in firstA[rhs[j]]:
#                             for k in firstA[rhs[j]]: add(listA, k)
#                             listA.remove('EPSILON')
#                         else:
#                             for k in firstA[rhs[j]]: add(listA, k)
#                             break
#                     if 'EPSILON' in listA and 'EPSILON' not in firstA[rhs[-1]]:
#                         listA.remove('EPSILON')
#                     # r = listA.index('EPSILON')
#                     # del listA[r]
#                     for k in listA: add(tempA[lhs],k)
#             elif G[i][1][0] in T: add(tempA[lhs],rhs[0])
#         flag = True
#         for NonT in Nt: 
#             flag = flag and (tempA[NonT] == firstA[NonT])
#         if flag: break
#         for NonT in Nt: firstA[NonT] = [i for i in tempA[NonT]]
#     return firstA
# def follow_set(G,S,T,Nt):
#     followA = {}
#     tempA = {}
#     for NonT in Nt: followA[NonT] = ['DOLLAR'] if NonT == S else []
#     first_set_list = first_set(G,T,Nt)
#     while True:
#         for NonT in followA:
#             tempA[NonT] = [i for i in followA[NonT]]
#         for production in G:
#             Aj,rhs = production[0],list(production[1])
#             for i in range(len(rhs)):
#                 Ai = rhs[i]
#                 if Ai in Nt:
#                     if i+1 == len(rhs): w = ''
#                     else: w = rhs[i+1]
#                     if w == '' or (w in Nt and '' in first_set_list[w]):
#                         for k in followA[Aj]: add(tempA[Ai],k)
#                     if w in T: add(tempA[Ai],w)
#                     if w in Nt:
#                         for k in first_set_list[w]: add(tempA[Ai],k) if k!='' else add(tempA[Ai],'DOLLAR')
#             flag = True
#         for NonT in Nt: flag = flag and (tempA[NonT] == followA[NonT])
#         if flag: break
#         for NonT in Nt: followA[NonT] = [i for i in tempA[NonT]]
#     return followA
def import_grammar(fileHandle):
    G,T,Nt = [],[],[]
    for lines in fileHandle:
        production = lines.split(' ')
        if production[0] not in Nt: Nt.append(production[0])
        listStr = production[1:]
        if listStr[-1][-1] == '\n':
            # print(listStr)
            listStr[-1] = listStr[-1][:-1]
            # print(listStr)
        # del listStr[-1]
        # production[1] = ''.join(i for i in listStr)
        for char in listStr:
            if 65<=ord(char[0]) and ord(char[0])<= 90:
                if char not in T: T.append(char)
            else:
                if char not in Nt: Nt.append(char)
        if production not in G: G.append((production[0],listStr))
    T.append('DOLLAR')
    T.remove('EPSILON')
    return G,T,Nt
def parse_table(G,terminal,first,follow):
    M = {}
    grammar = {}
    for i in range(len(G)):
        if G[i][0] not in grammar: grammar[G[i][0]] = []
        add(grammar[G[i][0]],G[i][1])
    print('Grammar for Parse Table')
    pprint(grammar)
    for A in grammar:
        if A not in M: M[A] = {}
        for alpha in grammar[A]:
            print(A,'->',alpha)
            if alpha == ['EPSILON']:
                for b in follow[A]:
                    if b not in M[A]: M[A][b] = {}
                    if A not in M[A][b]: M[A][b][A] = []
                    M[A][b][A].append(alpha)
            elif alpha[0] in terminal:
                if alpha[0] not in M[A]: M[A][alpha[0]] = {}
                if A not in M[A][alpha[0]]: M[A][alpha[0]][A] = []
                M[A][alpha[0]][A].append(alpha)
            else:
                for a in first[alpha[0]]:
                    if a not in M[A] and a != 'EPSILON': M[A][a] = {}
                    if A not in M[A][a]: M[A][a][A] = []
                    if a != 'EPSILON': M[A][a][A].append(alpha)
    return M
stack,post = [],'EPSILON'
def predictive_parsing(M,T):
    global stack,post
    ip,X,top = 0,stack[0],0
    while X != 'DOLLAR':
        a = post[ip]
        print(a,X,stack)
        if X==a:
            del stack[top]
            ip = ip + 1
        elif X in T and X!='DOLLAR':
            print('terminal not encountered',X)
            print('Syntax error')
            return
        elif a not in M[X]:
            print('terminal not in parse table',a,X)
            print('Syntax error')
            return
        elif len(M[X][a][X]) == 1:
            Y = list(M[X][a][X][0])
            del stack[top]
            for i in range(len(Y)): stack.insert(top,Y[len(Y)-1-i])
        elif len(M[X][a][X]) > 1:
            print('Grammar not in LL1')
            break
        X = stack[top]
    print('Accepted')
    stack,post = [],'EPSILON'
def driver():
    global stack,post
    fileHandle = open('inputllcheck.txt')
    G,T,Nt = import_grammar(fileHandle)
    # pprint(G)
    # print(T)
    # print(Nt)
    # print(len(G), len(T), len(Nt))
    # exit(0)
    # first_set_list = first_set(G,T,Nt)
    # follow_set_list = follow_set(G,G[0][0],T,Nt)
    with open('firstSets.json', 'r') as f:
        first_set_list = json.load(f)
    with open('followSets.json', 'r') as f:
        follow_set_list = json.load(f)
    # print('First')
    # print(first_set_list)
    # print('Follow')
    # print(follow_set_list)
    # exit(0)
    parseTable = parse_table(G,T,first_set_list,follow_set_list)
    pprint(parseTable)
    post = raw_input('Enter some string to test ....')+'DOLLAR'
    stack = [G[0][0],'DOLLAR']
    predictive_parsing(parseTable,T)
driver()