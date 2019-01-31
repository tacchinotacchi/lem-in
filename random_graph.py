import random
import sys

if len(sys.argv) < 4:
    print("Usage: random_graph.py ants nodes average_rank")
    sys.exit(0)

print(sys.argv[1])

edges = []
nodes = int(sys.argv[2])
random.seed()
for i in range(0, int(sys.argv[3]) * nodes // 2):
    edges.append(random.sample(range(0, nodes), 2));

endpoints = random.sample(range(0, nodes), 2);
for i in range(0, nodes):
    if i == endpoints[0]:
        print("##start")
        print("start", random.randint(0, 1000), random.randint(0, 1000))
    elif i == endpoints[1]:
        print("##end")
        print("end", random.randint(0, 1000), random.randint(0, 1000))
    else:
        print(i, random.randint(0, 1000), random.randint(0, 1000), sep=" ")

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
