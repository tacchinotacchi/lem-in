## lem-in

lem-in is a solver for finding the min-cost max-flow in a graph with undirected edges of capacity 1.
This repository includes a 3D visualizer for the graph that attempts to find the optimal arrangement of nodes for visualizing, with a linear regression.

## Compilation

Compile with

```
make
```

You'll need OpenGL and SDL2 to use the visualizer.

## Usage

Generating a random graph:

```
python random_graph.py num_ants num_nodes average_node_rank > example.map
```

Writing the solution to solution.txt:

```
./lem-in < example.map > solution.txt
```

Using the visualizer:
```
# Visualize the graph
./visualizer < example.map

# Visualize the graph and the solution
./visualizer < solution.txt
```

When visualizing the solition, press `m` to see the movement of the flow through the graph.