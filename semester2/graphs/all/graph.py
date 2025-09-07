import copy
from collections import deque


class EdgeIterator:
    def __init__(self, edges):
        self.edges = list(edges.items())
        self.index = 0

    def __iter__(self):
        return self

    def __next__(self):
        if self.index >= len(self.edges):
            raise StopIteration
        edge = self.edges[self.index]
        self.index += 1
        return edge


class DirectedGraph:
    def __init__(self, num_vertices):
        self.initial_vertices = 0
        self.num_vertices = num_vertices
        self.out_edges = {i: {} for i in range(num_vertices)}
        self.in_edges = {i: {} for i in range(num_vertices)}
        self.edge_costs = {}

    def get_initial_vertices(self):
        return self.initial_vertices

    def add_edge(self, x, y, cost):
        if x not in self.out_edges or y not in self.in_edges:
            return False

        if y in self.out_edges[x]:
            return False

        if y not in self.out_edges[x]:
            self.out_edges[x][y] = (x, y)
            self.in_edges[y][x] = (x, y)
            self.edge_costs[(x, y)] = cost
        return True

    def remove_edge(self, x, y):
        if x not in self.out_edges or y not in self.out_edges or y not in self.out_edges[x]:
            return False
        del self.out_edges[x][y]
        del self.in_edges[y][x]
        del self.edge_costs[(x, y)]
        return True

    def add_vertex(self):
        self.num_vertices += 1
        self.initial_vertices += 1
        self.out_edges[self.initial_vertices-1] = {}
        self.in_edges[self.initial_vertices-1] = {}
        #if filename:
            #self.write_graph_to_file(filename)

    def remove_vertex(self, vertex):
        if vertex not in self.out_edges:
            return False

        for target in list(self.out_edges[vertex].keys()):
            del self.in_edges[target][vertex]
            del self.edge_costs[(vertex, target)]

        del self.out_edges[vertex]

        for source in list(self.in_edges[vertex].keys()):
            del self.out_edges[source][vertex]
            del self.edge_costs[(source, vertex)]

        del self.in_edges[vertex]

        self.num_vertices -= 1
        return True

    def get_num_vertices(self):
        return self.num_vertices

    def get_vertices(self):
        return iter(self.out_edges.keys())

    def has_edge(self, x, y):
        return y in self.out_edges.get(x, {})

    def get_in_degree(self, vertex):
        if vertex not in self.in_edges:
            return None
        return len(self.in_edges[vertex])

    def get_out_degree(self, vertex):
        if vertex not in self.out_edges:
            return None
        return len(self.out_edges[vertex])

    def get_out_edges(self, vertex):
        if vertex not in self.out_edges:
            return EdgeIterator({})
        return EdgeIterator(self.out_edges[vertex])

    def get_in_edges(self, vertex):
        if vertex not in self.in_edges:
            return EdgeIterator({})
        return EdgeIterator(self.in_edges[vertex])

    def get_edge_endpoints(self, edge_id):
        return edge_id if edge_id in self.edge_costs else None

    def get_edge_cost(self, edge_id):
        return self.edge_costs.get(edge_id, None)

    def set_edge_cost(self, edge_id, cost):
        if edge_id not in self.edge_costs:
            return False
        self.edge_costs[edge_id] = cost
        return True

    def copy_graph(self):
        return copy.deepcopy(self)

    #homework 2
    def connected_components(self):
        visited = set() # set to keep track of visited nodes
        components = [] # list to store all connected components
        vertices=set(self.out_edges.keys()) | set(self.in_edges.keys())
        for vertex in vertices:
            # if the vertex hasn't been visited yet, it's part of a new component
            if vertex not in visited:
                # perform BFS to find the whole component and mark visited nodes
                component=self.bfs(vertex,visited)
                components.append(component)
        return components

    def bfs(self, vertex, visited):
        queue = deque([vertex])  # queue for BFS, initialized with the starting vertex
        component=[]    # list to store the current connected component
        while queue:
            vertex=queue.popleft()
            if vertex not in visited:
                visited.add(vertex)
                component.append(vertex)
                # get all neighbors (both incoming and outgoing edges)
                neighbours=set(self.out_edges[vertex]) | set(self.in_edges[vertex])
                for neighbour in neighbours:
                    if neighbour not in visited:
                        queue.append(neighbour) # add unvisited neighbors to the queue
        return component  # return the complete connected component

    #bonus problems
    def tarjan_strongly_connected_components(self):
        index = 0  # global index counter for discovery time
        stack = []  # stack of visited vertices
        on_stack = set()  # set for fast lookup to check if a vertex is in the stack
        indices = {}  # discovery index of each vertex
        low_index = {}  # lowest reachable index
        strong_components = []  # final list

        def strong_connect(vertex):
            nonlocal index, stack, on_stack, indices, low_index, strong_components
            # assign the current node an index and set its low-link value
            indices[vertex] = index
            low_index[vertex] = index
            index += 1
            stack.append(vertex)
            on_stack.add(vertex)

            # explore all the neighbors of the vertex
            for j in self.out_edges[vertex]:
                if j not in indices:
                    # if neighbor has not been visited, recurse on it
                    strong_connect(j)
                    # update the low-link value
                    low_index[vertex] = min(low_index[vertex], low_index[j])
                elif j in on_stack:
                    # if the neighbor is on the stack, it's part of the current SCC
                    low_index[vertex] = min(low_index[vertex], indices[j])

            # if vertex is a root of a strongly connected component
            if low_index[vertex] == indices[vertex]:
                strong_component = []   # store the nodes in the current SCC
                j = -1
                # pop the stack until we reach the current vertex
                while j != vertex:
                    j = stack.pop()
                    on_stack.remove(j)
                    strong_component.append(j)
                strong_components.append(sorted(strong_component))

        # call strong_connect for all nodes
        for i in range(self.num_vertices):
            if i not in indices:
                strong_connect(i)

        return strong_components

    def biconnected_components(self):
        time = [0]  # global timer wrapped in a list
        disc = {}  # discovery times of nodes
        low = {}  # lowest discovery time reachable from the node
        parent = {}  # parent of each node in DFS tree
        stack = []  # stack to keep track of edges in the current DFS path
        biconnected_components = []  # final list of biconnected components

        def dfs(u):
            children = 0
            disc[u] = low[u] = time[0]  # set discovery and low time
            time[0] += 1

            # iterate through all neighbors
            for v in set(self.out_edges[u]) | set(self.in_edges[u]):
                if v not in disc:
                    parent[v] = u
                    stack.append((u, v))  # add edge to stack
                    children += 1
                    dfs(v)

                    # after recursion, update low time of current node
                    low[u] = min(low[u], low[v])

                    # articulation point check
                    if (parent.get(u) is None and children > 1) or (parent.get(u) is not None and low[v] >= disc[u]):
                        component = []
                        while True:
                            e = stack.pop()
                            component.append(e)
                            if e == (u, v) or e == (v, u):  # edge found that triggered articulation
                                break
                        biconnected_components.append(component)

                elif v != parent.get(u) and disc[v] < disc[u]:
                    # back edge found
                    low[u] = min(low[u], disc[v])
                    stack.append((u, v))  # add back edge to stack

        # run DFS on each component
        for vertex in self.out_edges:
            if vertex not in disc:
                dfs(vertex)
                if stack:  # any remaining edges form a component
                    biconnected_components.append(stack[:])
                    stack.clear()

        return biconnected_components

    def floyd_warshall_with_path(self):
        n = self.get_num_vertices()
        INF = float('inf')

        # initialize the distance (dist) and path (prev) matrices
        dist = [[INF] * n for _ in range(n)]
        prev = [[-1] * n for _ in range(n)]  # f[i][j] will store the next vertex to go from i to j

        # initialize distances and paths based on the graph's edges
        for i in range(n):
            for j in range(n):
                if i == j:
                    dist[i][j] = 0  # the distance from a vertex to itself is 0
                    prev[i][j] = j
                elif (i, j) in self.edge_costs:  # if there is an edge from i to j
                    dist[i][j] = self.edge_costs[(i, j)]  # set the edge's cost
                    prev[i][j] = i  # the next vertex on the shortest path is j

        # perform the standard Floyd-Warshall algorithm to compute the shortest paths
        for k in range(n):
            # consider k as the intermediate vertex
            for i in range(n):
                for j in range(n):
                    # check if a shorter path exists using the intermediate vertex k
                    if dist[i][j] > dist[i][k] + dist[k][j]:
                        dist[i][j] = dist[i][k] + dist[k][j]
                        prev[i][j] = prev[k][j]  # update the path to go through vertex k


        return dist, prev

    def reconstruct_path(self, u, v,prev):
        # if there is no path from u to v
        if prev[u][v] == -1:
            return []

        # reconstruct the path from u to v using the f matrix
        path = [v]
        while u != v:
            v = prev[u][v]
            path.append(v)

        return path

    def find_lowest_cost_walk(self, start, end):
        # run Floyd-Warshall to get the distance and path matrices
        w, f = self.floyd_warshall_with_path()

        INF = float('inf')

        # Check if there's no path
        if w[start][end] == INF:
            return False, "NO_PATH"

        path = self.reconstruct_path(start, end, f)

        # return the result along with the minimum cost
        min_cost = w[start][end]
        return True, (path, min_cost)

    ###################################################
    #bonus problem 1
    #Dijkstra shortest path
    def bonus1(self, start, end):
        from heapq import heappop, heappush # for the priority queue to manage the minimum costs
        from collections import defaultdict # for default dictionary for path count management

        # initialize the priority queue with the start vertex and cost 0
        priority_queue = []
        heappush(priority_queue, (0, start))

        # default distance for each vertex is infinity, except for the start vertex
        distances = defaultdict(lambda: float('inf'))
        distances[start] = 0

        # initialize path count for each vertex, starting with 1 path to the start
        path_count = defaultdict(int)
        path_count[start] = 1

        while priority_queue:
            current_cost, current_vertex = heappop(priority_queue) # get the vertex with the smallest cost
            # if the current vertex is the destination, skip further processing
            if current_vertex == end:
                continue

            # explore all the neighbors of the current vertex
            for neighbor, _ in self.get_out_edges(current_vertex):
                edge_cost = self.edge_costs[(current_vertex, neighbor)]
                new_cost = current_cost + edge_cost # calculate the new cost to reach this neighbor

                # if we found a cheaper way to reach this neighbor, update its distance and path count
                if new_cost < distances[neighbor]:
                    distances[neighbor] = new_cost
                    path_count[neighbor] = path_count[current_vertex]   # inherit the number of paths to the current vertex
                    heappush(priority_queue, (new_cost, neighbor))
                # if we found an equally cheap way, increase the number of paths to this neighbor
                elif new_cost == distances[neighbor]:
                    path_count[neighbor] += path_count[current_vertex]

        return distances[end], path_count[end] if end in path_count else 0

    #bonus 2
    # performs a topological sort on the graph (for DAG)
    #Topological Path Counting or DP on DAG for Path Counting

    def topological_sorting(self):
        from collections import deque
        # initialize in-degree dictionary to keep track of how many edges point to each vertex
        inbound_degree = {i: 0 for i in range(self.num_vertices)}
        # update in-degree of each vertex by iterating over its outgoing edges
        for vertex in self.get_vertices():
            for neighbor,_ in self.get_out_edges(vertex):
                inbound_degree[neighbor] += 1  # increase in-degree for each neighbor
        # initialize the queue with all vertices that have no incoming edges
        queue = deque([v for v in inbound_degree if inbound_degree[v] == 0])
        topological_order = []
        # process the queue to generate the topological order
        while queue:
            vertex = queue.popleft()    # get the vertex with no incoming edges
            topological_order.append(vertex)    # add it to the topological order
            # decrease the in-degree of all its neighbors, and if any neighbor has no incoming edges, add it to the queue
            for neighbor,_ in self.get_out_edges(vertex):
                inbound_degree[neighbor] -= 1
                if inbound_degree[neighbor] == 0:
                    queue.append(neighbor)

        if len(topological_order) != self.num_vertices:
            return None
        return topological_order

    def count_paths(self, start, end):
        topological_order = self.topological_sorting()
        if topological_order is None:
            return 0    # if the graph has a cycle, return 0 paths
        # initialize an array to store the number of paths to each vertex, starting with 1 path to the start vertex
        path_count = [0] * self.num_vertices
        path_count[start] = 1

        for vertex in topological_order:
            if path_count[vertex] > 0:
                # update the path count for all its neighbors
                for neighbor,_ in self.get_out_edges(vertex):
                    path_count[neighbor] += path_count[vertex]  # add the paths from this vertex to its neighbors

        return path_count[end]



    #practical work nr 4

    #Write a program that, given an undirected connected graph, constructs a minimal spanning tree using the Prim's algorithm
    def prims_algorithm(self, start_node):
        dad = [-1] * self.get_num_vertices()    # dad[i] = parent of node i in MST
        dad[start_node] = start_node    # root's parent is itself
        from queue import PriorityQueue
        q = PriorityQueue()
        q.put((0, start_node, start_node))  # (cost, node, parent)

        minimum_cost = 0

        for i in range(self.get_num_vertices()):
            current_pair = ()
            while not q.empty():
                current_pair = q.get()      # get the edge with the minimum cost
                if dad[current_pair[1]] == -1:      # destination node not in MST
                    break
            current_node = current_pair[1]
            dad[current_node] = current_pair[2]     # add node to MST
            minimum_cost += current_pair[0]         # add cost to total
            neighbors = set()
            # get all unique neighbors (for undirected graph)
            neighbors.update([nbr for nbr, _ in self.get_out_edges(current_node)])
            neighbors.update([nbr for nbr, _ in self.get_in_edges(current_node)])
            for neighbour in neighbors:
                if dad[neighbour] == -1:    # if neighbor not yet in MST
                    # get both directions since it's undirected
                    cost1 = self.get_edge_cost((current_node, neighbour)) or float('inf')
                    cost2 = self.get_edge_cost((neighbour, current_node)) or float('inf')
                    cost = min(cost1, cost2)     # choose the lower cost
                    q.put((cost, neighbour, current_node))      # add to priority queue

        return minimum_cost, dad

    #bonus 2
    def is_dag(self):
        return self.topological_sorting() is not None

    # count all paths from `start` to `end` in a DAG
    def count_paths_bonus_2(self, start, end):
        top_order = self.topological_sorting()
        if top_order is None:
            return 0  # cycle detected

        path_count = [0] * self.num_vertices
        path_count[start] = 1   # one way to reach start node

        for vertex in top_order:
            if path_count[vertex] > 0:
                for neighbor,_ in self.get_out_edges(vertex):
                    path_count[neighbor] += path_count[vertex]  # accumulate paths

        return path_count[end]

    #bonus 3 Find number of shortest paths from `start` to `end` in a DAG
    def find_lowest_cost_paths(self, start, end):

        top_order = self.topological_sorting()
        if top_order is None:
            return 0, 0

        distances = {vertex: float('inf') for vertex in self.get_vertices()}    # min cost
        path_count = {vertex: 0 for vertex in self.get_vertices()}               # num paths
        distances[start] = 0
        path_count[start] = 1

        for vertex in top_order:
            for neighbor,_ in self.get_out_edges(vertex):
                edge_cost = self.edge_costs[(vertex, neighbor)]
                new_cost = distances[vertex] + edge_cost
                if new_cost < distances[neighbor]:
                    distances[neighbor] = new_cost
                    path_count[neighbor] = path_count[vertex]   # new best path
                elif new_cost == distances[neighbor]:
                    path_count[neighbor] += path_count[vertex]  # another shortest path

        return distances[end], path_count[end]

    #homework 5
    def first_version(self, start, end):
        #floyd - warshall
        from typing import List, Optional
        vertices = list(self.get_vertices())
        n = len(vertices)
        index_map = {v: i for i, v in enumerate(vertices)}
        rev_index = {i: v for v, i in index_map.items()}

        INF = float('inf')
        dist = [[INF] * n for _ in range(n)]
        next_node: List[List[Optional[int]]] = [[None for _ in range(n)] for _ in range(n)]

        for v in vertices:
            i = index_map[v]
            dist[i][i] = 0
            next_node[i][i] = v

        for (u, v), cost in self.edge_costs.items():
            if u in index_map and v in index_map:
                i, j = index_map[u], index_map[v]
                dist[i][j] = cost
                next_node[i][j] = v

        for k in range(n):
            for i in range(n):
                for j in range(n):
                    if dist[i][k] + dist[k][j] < dist[i][j]:
                        dist[i][j] = dist[i][k] + dist[k][j]
                        next_node[i][j] = next_node[i][k]

        for i in range(n):
            if dist[i][i] < 0:
                raise ValueError("Graph contains a negative weight cycle")

        if next_node[index_map[start]][index_map[end]] is None:
            return None, INF  # No path

        path = [start]
        i, j = index_map[start], index_map[end]
        while start != end:
            start = next_node[i][j]
            path.append(start)
            i = index_map[start]

        return path, dist[index_map[path[0]]][index_map[path[-1]]]

    # another version
    def bellman_ford(self, src, dest):
        dist = {v: float('inf') for v in self.in_edges}
        prev = {v: None for v in self.in_edges}
        
        dist[src] = 0

        for _ in range(len(self.in_edges) - 1):
            for (u, v), cost in self.edge_costs.items():
                if dist[u] + cost < dist[v]:
                    dist[v] = dist[u] + cost
                    prev[v] = u

        # Check for negative cost cycles
        for (u, v), cost in self.edge_costs.items():
            if dist[u] + cost < dist[v]:
                return None, []  # Negative cycle detected

        if dist[dest] == float('inf'):
            return float('inf'), []

        # Reconstruct path
        path = []
        current = dest
        while current is not None:
            path.append(current)
            current = prev[current]
        path.reverse()
        return dist[dest], path


    @staticmethod
    def version3(graph, costs, src, dest, max_depth=20):
        best_cost = float('inf')
        best_path = None
        negative_cycle_detected = False

        min_cost_to_node = {src: 0}  # minimum cost to get to that vertex
        path_set = set([src])  # to see if a node is already in the path

        # depth-first search-like backtracking function
        def backtrack(current, cost_so_far, path):
            nonlocal best_cost, best_path, negative_cycle_detected
            #negative cycle was detected => stop further processing
            if negative_cycle_detected:
                return
            # stop exploration if path is too deep || cost is already worse than best found
            if len(path) > max_depth or cost_so_far >= best_cost:
                return
            # already reached this node with a cheaper cost => no need to continue this path
            if current in min_cost_to_node and cost_so_far > min_cost_to_node[current]:
                return
            else:
                # update minimum cost for this node
                min_cost_to_node[current] = cost_so_far

            for neighbor in graph.get(current, []):
                edge_cost = costs.get((current, neighbor), float('inf'))    # cost to neighbor
                new_cost = cost_so_far + edge_cost  # total cost for this path
                #check if neighbor is already in the current path => cycle detection
                if neighbor in path_set:
                    # can get to neighbor with a smaller cost than before => negative cycle detected
                    if new_cost < min_cost_to_node.get(neighbor, float('inf')):
                        negative_cycle_detected = True
                        return
                    else:
                        # not improving cost => skip this neighbor to avoid infinite loops
                        continue
                # add neighbor to path and set, then recurse
                path.append(neighbor)
                path_set.add(neighbor)
                # backtrack => remove neighbor after recursion returns
                backtrack(neighbor, new_cost, path)
                path.pop()
                path_set.remove(neighbor)
            #current node is the destination and cost is better => update best
            if current == dest:
                if cost_so_far < best_cost:
                    best_cost = cost_so_far
                    best_path = path[:]

        # start backtracking from source
        backtrack(src, 0, [src])

        if negative_cycle_detected:
            return None, None, True

        return best_cost, best_path, False









