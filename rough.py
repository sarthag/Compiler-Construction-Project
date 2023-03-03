import json

prod_rules = []
with open('inputllcheck.txt', 'r') as f:
    for line in f.readlines():
        # prin
        print(line.split())
        # tmp = {
        #     'left': line.split()[0],
        #     'right': line.split()[1:]
        #     }
        # prod_rules.append(tmp)
        tmp = line.split()[0] + '->'
        print(tmp)
        for token in line.split()[1:]:
            tmp = tmp + ' ' + token
        print(tmp)
        break


# print(len(prod_rules))
# with open('grammar.json', 'w') as f:
#     json.dump(prod_rules, f)
