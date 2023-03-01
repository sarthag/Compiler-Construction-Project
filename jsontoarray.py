import json

with open('firstSets.json', 'r') as f:
    firstdict = json.load(f)

print(len(firstdict))