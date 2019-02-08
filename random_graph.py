import random
import sys

if len(sys.argv) < 4:
    print("Usage: random_graph.py ants nodes average_rank")
    sys.exit(0)

print(sys.argv[1])

nodes = int(sys.argv[2])
connections = int(sys.argv[3])
random.seed()

endpoints = random.sample(range(0, nodes), 2)

node_list = []
for node in range(0, nodes):
    if (node == endpoints[0]):
        print("##start")
        print("start", random.randint(0, 1000000), random.randint(0, 1000000), sep=' ')
        node_list.append("start")
    elif (node == endpoints[1]):
        print("##end")
        print("end", random.randint(0, 1000000), random.randint(0, 1000000), sep=' ')
        node_list.append("end")
    else:
        print(node, random.randint(0, 1000000), random.randint(0, 1000000), sep=' ')
        node_list.append(node)

adjacency = []
s = 0
while s < (nodes * connections // 2):
    coords = random.sample(range(0, nodes), 2)
    i = coords[0]
    j = coords[1]
    if j < i:
        temp = i
        i = j
        j = temp
    if i != j and (i, j) not in adjacency:
        s += 1
        adjacency.append((i, j))
        if random.randint(0, 1) == 1:
            print(node_list[i], node_list[j], sep="-")
        else:
            print(node_list[j], node_list[i], sep="-")
