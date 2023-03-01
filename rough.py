non_terminals = []
with open('grammar.txt', 'r') as f:
    for line in f.readlines():
        if line.split()[0] not in non_terminals:
            non_terminals.append(line.split()[0])
with open('non_terminals.txt', 'w') as f:
    for non_terminal in non_terminals:
        f.write(non_terminal + '\n')