import json

prod_rules = []
with open('grammar.txt', 'r') as f:
    for line in f.readlines():
        print(line.split())
        tmp = {
            'left': line.split()[0],
            'right': line.split()[1:]
            }
        prod_rules.append(tmp)
with open('grammar.json', 'w') as f:
    json.dump(prod_rules, f)
