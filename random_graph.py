import random

print(100000)

edges = []
nodes = 10000
random.seed()
for i in range(0, 7 * nodes // 2):
    edges.append(random.sample(range(0, nodes), 2));

endpoints = random.sample(range(0, nodes), 2);
for i in range(0, nodes):
    if i == endpoints[0]:
        print("##start")
        print("start", i, i)
    elif i == endpoints[1]:
        print("##end")
        print("end", i, i)
    else:
        print(i, i, i, sep=" ")

for edge in edges:
    if edge[0] == endpoints[0]:
        first_name = "start"
    elif edge[0] == endpoints[1]:
        first_name = "end"
    else:
        first_name = edge[0]
    if edge[1] == endpoints[0]:
        second_name = "start"
    elif edge[1] == endpoints[1]:
        second_name = "end"
    else:
        second_name = edge[1]
    print(first_name, second_name, sep="-");
