from graph import *
import random

def read_graph_from_file(filename):
    with open(filename, "r") as file:
        n, m = map(int, file.readline().split())
        graph = DirectedGraph(n)
        graph.initial_vertices = n
        for _ in range(m):
            x, y, c = map(int, file.readline().split())
            graph.add_edge(x, y, c)
    return graph

def write_graph_to_file(graph, filename):
    with open(filename, "w") as file:
        file.write(f"{graph.get_num_vertices()} {len(graph.edge_costs)}\n")
        for (x, y), cost in graph.edge_costs.items():
            file.write(f"{x} {y} {cost}\n")

"""
def generate_random_graph(num_vertices, num_edges):
    graph = DirectedGraph(num_vertices)
    edges_set = set()
    max_attempts = 10000
    attempts = 0

    while len(edges_set) < num_edges and attempts < max_attempts:
        x, y = random.randint(0, num_vertices - 1), random.randint(0, num_vertices - 1)

        if x != y and (x, y) not in edges_set:
            cost = random.randint(1, 100)
            graph.add_edge(x, y, cost)
            edges_set.add((x, y))  

        attempts += 1

    if attempts >= max_attempts:
        print(f"Couldn't generate {num_edges} unique edges after {max_attempts} attempts.")

    return graph
"""
def generate_random_graph(filename, n, m):
    graph = DirectedGraph(n)
    if m > n * n:
        with open(filename, "w") as file:
            file.write("0\n")
        return False

    for _ in range(n):
        graph.add_vertex()

    edges_added = 0
    edge_set = set()

    while edges_added < m:
        x = random.randint(0, n - 1)
        y = random.randint(0, n - 1)
        if (x, y) not in edge_set:
            cost = random.randint(1, 100)
            graph.add_edge(x, y, cost)
            edge_set.add((x, y))
            edges_added += 1

    return graph