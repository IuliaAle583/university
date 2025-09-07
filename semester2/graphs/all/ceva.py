import sys


class Graph():
    def __init__(self, vertices):
        self.V = vertices
        self.graph = [[0 for column in range(vertices)]
                      for row in range(vertices)]

    # A utility function to print
    # the constructed MST stored in parent[]
    def printMST(self, parent):
        print("Edge \tWeight")
        for i in range(1, self.V):
            print(parent[i], "-", i, "\t", self.graph[parent[i]][i])

    # A utility function to find the vertex with
    # minimum distance value, from the set of vertices
    # not yet included in shortest path tree
    def minKey(self, key, mstSet):

        # Initialize min value
        min = sys.maxsize

        for v in range(self.V):
            if key[v] < min and mstSet[v] == False:
                min = key[v]
                min_index = v

        return min_index

    # Function to construct and print MST for a graph
    # represented using adjacency matrix representation
    def primMST(self):

        # Key values used to pick minimum weight edge in cut
        key = [sys.maxsize] * self.V
        parent = [None] * self.V  # Array to store constructed MST
        # Make key 0 so that this vertex is picked as first vertex
        key[0] = 0
        mstSet = [False] * self.V

        parent[0] = -1  # First node is always the root of

        for cout in range(self.V):

            # Pick the minimum distance vertex from
            # the set of vertices not yet processed.
            # u is always equal to src in first iteration
            u = self.minKey(key, mstSet)

            # Put the minimum distance vertex in
            # the shortest path tree
            mstSet[u] = True

            # Update dist value of the adjacent vertices
            # of the picked vertex only if the current
            # distance is greater than new distance and
            # the vertex in not in the shortest path tree
            for v in range(self.V):

                # graph[u][v] is non zero only for adjacent vertices of m
                # mstSet[v] is false for vertices not yet included in MST
                # Update the key only if graph[u][v] is smaller than key[v]
                if self.graph[u][v] > 0 and mstSet[v] == False and key[v] > self.graph[u][v]:
                    key[v] = self.graph[u][v]
                    parent[v] = u

        self.printMST(parent)


def create_adjacency_matrix(num_vertices, edges):
    # Inițializăm matricea cu 0 (fără legătură)
    matrix = [[0 for _ in range(num_vertices)] for _ in range(num_vertices)]

    # Parcurgem lista de muchii și completăm matricea
    for x, y, cost in edges:
        matrix[x][y] = cost
        matrix[y][x] = cost  # pentru graf neorientat

    return matrix

# Driver's code
if __name__ == '__main__':
    """g = Graph(8)
    g.graph = [[0, 4, 6, 2, 0, 0, 0, 5],
    [4, 0, 3, 0, 5, 0, 0, 0],
    [6, 3, 0, 1, 0, 7, 0, 0],
    [2, 0, 1, 0, 0, 3, 0, 0],
    [0, 5, 0, 0, 0, 0, 2, 0],
    [0, 0, 7, 3, 0, 0, 4, 0],
    [0, 0, 0, 0, 2, 4, 0, 6],
    [5, 0, 0, 0, 0, 0, 6, 0]]

    g.primMST()"""
    num_vertices = 8
    edges = [
        (0, 1, 4),
        (0, 2, 6),
        (0, 3, 2),
        (1, 2, 3),
        (1, 4, 5),
        (2, 3, 1),
        (2, 5, 7),
        (3, 5, 3),
        (4, 6, 2),
        (5, 6, 4),
        (6, 7, 6),
        (7, 0, 5)
    ]

    adjacency_matrix = create_adjacency_matrix(num_vertices, edges)

    for row in adjacency_matrix:
        print(row)