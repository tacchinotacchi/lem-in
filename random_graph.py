import random

print(100)

edges = []
nodes = 3500
random.seed()
for i in range(0, 5 * nodes):
    edges.append(random.sample(range(0, nodes), 2));

endpoints = random.sample(range(0, nodes), 2);
for i in range(0, nodes):
    if i == endpoints[0]:
        print("##start")
    elif i == endpoints[1]:
        print("##end")
    print(i, i, i, sep=" ")

for edge in edges:
    print(edge[0], edge[1], sep="-");
