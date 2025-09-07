from logging import exception
from unittest import enterModuleContext

from WolfGoatCabbage import WolfGoatCabbage
from external_functions import *
import puzzle
from hw3_bonus3 import *
from hw4_bonus1 import *


class GraphUI:
    def __init__(self,graph_class):
        self.graph = None
        self.copied_graph = None
        self.filename = None
        self.graph_class = graph_class
        self.bridge_graph = None

    def connected_components(self):
        components=self.graph.connected_components()
        print(f'Found {len(components)} connected components')
        for i, component in enumerate(components):
            print(f'Component {i+1} : {component}')

    def strongly_connected(self):
        print("Finding strongly connected components of the current graph...")
        strongly_connected_components = self.graph.tarjan_strongly_connected_components()
        print(f"Found {len(strongly_connected_components)} strongly connected component(s).")
        for i, component in enumerate(strongly_connected_components):
            print(f"Component {i + 1}: {component}")

    def biconnected_components(self):
        print("Finding biconnected components of the current graph...")
        bcc = self.graph.biconnected_components()
        for i, comp in enumerate(bcc):
            print(f"Biconnected component {i + 1}: {comp}")

    @staticmethod
    def wolf_goat_cabbage():
        problem = WolfGoatCabbage()
        solution = problem.solve()
        if solution:
            print("Found solution:")
            for i, state in enumerate(solution):
                sides = lambda x: "Left bank" if x else "Right bank"
                print(
                    f"Step {i}: Human: {sides(state[0])}, Wolf: {sides(state[1])}, Goat: {sides(state[2])}, Cabbage: {sides(state[3])}")
        else:
            print("No found solution.")

    @staticmethod
    def solve_15_puzzle():

        initial_list = ["1", "0", "2", "4", "5", "7", "3",
                       "8", "9", "6", "11", "12", "13", "10", "14", "15"]

        solution = puzzle.solve(initial_list)
        if solution is None:
            print("There is no solution!")
            return
        print("The solution is: ")
        for state in solution:
            if state.action == 'r':
                print("Move Right")
            elif state.action == 'l':
                print("Move Left")
            elif state.action == 'u':
                print("Move Up")
            elif state.action == 'd':
                print("Move Down")
            print()
            print(state)

    def min_cost_path_25(self):
        source = int(input("Enter the source vertex: "))
        destination = int(input("Enter the destination vertex: "))
        min_cost, count_paths = self.graph.bonus1(source, destination)
        if count_paths == 0:
            print(f"No paths available from {source} to {destination}.")
        else:
            print(f"Minimum cost from {source} to {destination} is {min_cost} with {count_paths} distinct path(s).")

    def count_paths(self):
        source = int(input("Enter the source vertex: "))
        destination = int(input("Enter the destination vertex: "))
        num_paths = self.graph.count_paths(source, destination)
        print(f"The number of distinct walks from vertex {source} to vertex {destination} is {num_paths}.")

    def cross_time(self):
        n = int(input("Enter the number of people crossing the bridge (up to 20): "))
        cross_time = []
        for i in range(n):
            time = int(input(f"Enter the crossing time for person {i + 1}: "))
            cross_time.append(time)
        self.bridge_graph = BridgeGraph(cross_time)
        self.bridge_graph.generate_all_states()
        print("Bridge problem initialized.")

    def bridge_and_torch(self):
        if not self.bridge_graph:
            print("Please initialize the bridge problem first.")
            return
        result = self.bridge_graph.solution()
        print(f"The minimal time for all to cross the bridge is {result} minutes.")


    def minimum_cost_spanning_tree(self):
        start_node = int(input("Please enter the starting node: "))
        minimum_cost_spanning_tree = self.graph.prims_algorithm(
            start_node)
        print("The cost of minimum spanning tree is " +
              str(minimum_cost_spanning_tree[0]))
        print("The edges of the minimum spanning tree are: ")
        edges = minimum_cost_spanning_tree[1]
        for i in range(len(edges)):
            if i != edges[i]:
                print(str(i) + " " + str(edges[i]))

    #bonus 1, hw 4
    @staticmethod
    def print_edges(node):
        if node is None:
            return
        if node.left is not None:
            print(f"{node.data} -> {node.left.data}")
        if node.right is not None:
            print(f"{node.data} -> {node.right.data}")
        GraphUI.print_edges(node.left)
        GraphUI.print_edges(node.right)

    #bonus 2
    def check_if_dag(self):
        if self.graph is None:
            print("There is no graph.")
            return
        graph=self.graph
        if self.graph.is_dag():
            top=self.graph.topological_sorting()
            print("the graph is a DAG. Topological order is: ")
            print(top)
        else:
            print("The graph is not a DAG.")

    def count_paths_two_vertices(self):
        if self.graph is None:
            print("There is no graph.")
            return
        graph=self.graph
        if not graph.is_dag():
            print("The graph is not a DAG.")
            return
        start = int(input("Enter the start vertex: "))
        end = int(input("Enter the end vertex: "))
        num_paths = graph.count_paths_bonus_2(start, end)
        print(f"The number of distinct paths from vertex {start} to vertex {end} is {num_paths}.")

    def count_lowest_paths_two_vertices(self):
        if self.graph is None:
            print("No graph selected.")
            return

        graph = self.graph
        if not graph.is_dag():
            print("The graph is not a DAG. Cannot find paths.")
            return

        start = int(input("Enter the start vertex: "))
        end = int(input("Enter the end vertex: "))
        min_cost, count_paths = graph.find_lowest_cost_paths(start, end)
        if count_paths == 0:
            print(f"No paths available from {start} to {end}.")
        else:
            print(f"Minimum cost from {start} to {end} is {min_cost} with {count_paths} distinct path(s).")

    def practical_work5(self):
        if self.graph is None:
            print("No graph loaded.")
            return
        try:
            start = int(input("Enter start vertex: "))
            end = int(input("Enter end vertex: "))
        except ValueError:
            print("Invalid input. Please enter integer vertices.")
            return
        try:
            result = self.graph.first_version(start, end)
        except ValueError as e:
            print(e)
            return

        if result is None:
            print(f"No path found from {start} to {end}.")
            return
        path, cost = result
        if path is None or cost == float('inf'):
            print(f"No path found from {start} to {end}.")
        else:
            print(f"Minimum cost path from {path[0]} to {path[-1]}:")
            print(" -> ".join(map(str, path)))
            print(f"Total cost: {cost}")

    def bellman_ford_ui(self):
        if self.graph is None:
            print("No graph loaded.")
            return
        try:
            src = int(input("Enter source vertex: "))
            dest = int(input("Enter destination vertex: "))
        except ValueError:
            print("Invalid input. Please enter integers.")
            return
        if not (src in self.graph.get_vertices() and dest in self.graph.get_vertices()):
            print("Source or destination vertex does not exist in the graph.")
            return
        cost, path = self.graph.bellman_ford(src, dest)
        if cost is None:
            print("The graph contains a negative cost cycle. No shortest path.")
        elif cost == float('inf'):
            print(f"No path exists from {src} to {dest}.")
        else:
            print(f"Minimum cost from {src} to {dest} is: {cost}")
            print("Path: " + " -> ".join(map(str, path)))

    def version3ui(self):
        if self.graph is None:
            print("No graph loaded.")
            return

        try:
            src = int(input("Enter the source vertex: "))
            dest = int(input("Enter the destination vertex: "))
        except ValueError:
            print("Please enter valid integer vertices.")
            return

        graph_dict = {}
        costs_dict = {}

        for v in self.graph.get_vertices():
            neighbors = [target for target, _ in self.graph.get_out_edges(v)]
            graph_dict[v] = neighbors
            for neighbor in neighbors:
                cost = self.graph.get_edge_cost((v, neighbor))
                costs_dict[(v, neighbor)] = cost

        best_cost, best_path, negative_cycle = self.graph.version3(graph_dict, costs_dict, src, dest)

        if negative_cycle:
            print("Negative cost cycle detected!")
            pass
        else:
            if best_path is None:
                print(f"No path found from {src} to {dest}.")
            else:
                print(f"Minimum cost path from {src} to {dest} is:")
                print(" -> ".join(map(str, best_path)))
                print(f"With total cost: {best_cost}")

    def display_menu(self):
        ok=0
        while True:
            print("\033[1;36m Menu \033[0m")
            print("1. Load graph from file")
            print("2. Display number of vertices")
            print("3. Display vertices")
            print("4. Check if an edge exists")
            print("5. Get in-degree of a vertex")
            print("6. Get out-degree of a vertex")
            print("7. Get outbound edges of a vertex")
            print("8. Get inbound edges of a vertex")
            print("9. Get edge cost")
            print("10. Set edge cost")
            print("11. Copy graph")
            print("12. Save graph to file")
            print("13. Generate random graph")
            print("14. Add edge")
            print("15. Remove edge")
            print("16. Add vertex")
            print("17. Remove vertex")
            print("18. Display Original and Copied Graph")
            print("19. Find connected components")
            print("20. Find the strongly connected components")
            print("21. Find biconnected components")
            print("22. Wolf, goat, cabbage")
            print("23. Fifteen puzzle")
            print("24. Lowest cost walk")
            print("25. BONUS 1: find the number of distinct walks of minimum cost between the given vertices")
            print("26. BONUS 2: find the number of distinct walks between the given vertices in a DAG")
            print("BRIDGE AND TORCH")
            print("27. Input crossing times")
            print("28. Solve Bridge and Torch problem and display minimal crossing time")
            print("PRACTICAL WORK 4")
            print("29. Using Prim's algorithm, find the minimum cost spanning tree of the graph, from a starting vertex")
            print("30. BONUS 1: reconstruct a tree given in pre and post order")
            print("31. BONUS 1: reconstruct a tree given in pre and in order")
            print("32. BONUS 1: reconstruct a tree given in post and in order")
            print("33. BONUS 2. Check if the graph is a DAG")
            print("34. BONUS 2. Find the number of distinct paths between the given vertices")
            print("35. BONUS 3. Find the number of distinct lowest cost paths between two vertices ")
            print("PRACTICAL WORK 5")
            print("Given a digraph with costs and two vertices, find a minimum cost path between them")
            print("     36. Folyd-Warshall")
            print("     37. Bellman-Ford ")
            print("     38. Exponential time")
            print("0. Exit")
            choice = input("Choose an option: ")

            if choice == "1":
                filename = input("Enter filename: ")
                try:
                    self.graph = read_graph_from_file(filename)
                    ok=1
                    print("Graph loaded successfully.")
                except FileNotFoundError:
                    print(f"Error: The file '{filename}' was not found. Please check the filename and try again.")
                except Exception as e:
                    print(f"An error occurred: {e}")

            elif choice == "2" and self.graph:
                print("Number of vertices:", self.graph.get_num_vertices())

            elif choice == "3" and self.graph:
                print("Vertices:", list(self.graph.get_vertices()))

            elif choice == "4" and self.graph:
                try:
                    values = input("Enter two vertices (x y): ").split()
                    if len(values) < 2:
                        print("Not enough values entered. Please enter two integers.")
                        continue
                    x, y = map(int, values)
                    if not self.graph.has_edge(x, y):
                        print("Edge does not exist or one of the vertices is invalid.")
                    else:
                        print("Edge exists.")
                except ValueError:
                    print("Invalid input. Please enter two integers.")

            elif choice == "5" and self.graph:
                try:
                    v = int(input("Enter vertex: "))
                    in_degree = self.graph.get_in_degree(v)
                    if in_degree is None:
                        print("Vertex does not exist.")
                    else:
                        print("In-degree:", in_degree)
                except ValueError:
                    print("Invalid input. Please enter an integer.")

            elif choice == "6" and self.graph:
                v = int(input("Enter vertex: "))
                out_degree = self.graph.get_out_degree(v)
                if out_degree is None:
                    print("Vertex does not exist.")
                else:
                    print("Out-degree:", out_degree)

            elif choice == "7" and self.graph:
                v = int(input("Enter vertex: "))
                print("Outbound edges:", list(self.graph.get_out_edges(v)))

            elif choice == "8" and self.graph:
                v = int(input("Enter vertex: "))
                print("Inbound edges:", list(self.graph.get_in_edges(v)))

            elif choice == "9" and self.graph:
                try:
                    values = input("Enter edge (x y): ").split()
                    if len(values) < 2:
                        print("Not enough values entered. Please enter two integers.")
                        continue
                    x, y = map(int, values)
                    cost = self.graph.get_edge_cost((x, y))
                    if cost is None:
                        print("Edge does not exist.")
                    else:
                        print("Edge cost:", cost)
                except ValueError:
                    print("Invalid input. Please enter two integers.")

            elif choice == "10" and self.graph:
                try:
                    values = input("Enter edge and new cost (x y cost): ").split()
                    if len(values) < 3:
                        print("Not enough values entered. Please enter three integers.")
                        continue
                    x, y, c = map(int, values)
                    if not self.graph.set_edge_cost((x, y), c):
                        print("Edge does not exist.")
                    else:
                        print("Edge cost updated.")
                except ValueError:
                    print("Invalid input. Please enter three integers.")

            elif choice == "11" and self.graph:
                self.copied_graph = self.graph.copy_graph()
                print("Graph copied successfully.")

            elif choice == "12" and self.graph:
                self.filename=input("Enter filename: ")
                if self.filename:
                    # graph.write_graph_to_file(filename)
                    write_graph_to_file(self.graph, self.filename)
                    print("Graph saved to file.")
                else:
                    print("No file specified to save.")

            elif choice == "13":
                num_vertices, num_edges = map(int, input("Enter number of vertices and edges: ").split())
                self.filename = input("Enter filename for the random graph: ")
                # graph = DirectedGraph.generate_random_graph(num_vertices, num_edges)
                self.graph = generate_random_graph(self.filename, num_vertices, num_edges)
                if self.graph==0:
                    print("Graph could not be generated")
                    continue
                # graph = graph
                print("Random graph generated.")

            elif choice == "14" and self.graph:
                values = input("Enter edge and new cost (x y cost): ").split()
                if len(values) < 3:
                    print("Not enough values entered. Please enter three integers.")
                    continue
                x, y, c = map(int, values)
                if not self.graph.add_edge(x, y, c):
                    print("Vertices do not exist or the edge already exists.")
                else:
                    print("Edge added.")

            elif choice == "15" and self.graph:
                values = input("Enter edge (x y): ").split()
                if len(values) < 2:
                    print("Not enough values entered. Please enter two integers.")
                    continue
                x, y = map(int, values)
                #x, y = map(int, input("Enter edge (x y): ").split())
                if not self.graph.remove_edge(x, y):
                    print("Edge does not exist.")
                else:
                    print("Edge removed.")

            elif choice == "16" and self.graph:
                self.graph.add_vertex()
                print("Vertex added.")

            elif choice == "17" and self.graph:
                v = int(input("Enter vertex: "))
                if not self.graph.remove_vertex(v):
                    print("Vertex does not exist.")
                else:
                    print("Vertex removed.")

            elif choice == "18":
                print("\nDisplaying the Original Graph:")
                display_graph(self.graph)
                print("\nDisplaying the Copied Graph:")
                display_graph(self.copied_graph)
            elif choice == "19":
                if ok==1:
                    self.connected_components()
                else:
                    continue
            elif choice=="20":
                if ok==1:
                    self.strongly_connected()
                else:
                    continue
            elif choice=="21":
                if ok==1:
                    self.biconnected_components()
                else:
                    continue
            elif choice=="22":
                self.wolf_goat_cabbage()
            elif choice=="23":
                self.solve_15_puzzle()
            elif choice=="24":
                if ok == 1:
                    try:
                        start = int(input("Enter start vertex: "))
                        end = int(input("Enter end vertex: "))


                        success, data = self.graph.find_lowest_cost_walk(start, end)

                        if success:
                            path, min_cost = data
                            path.reverse()
                            print(f"Path: {' -> '.join(map(str, path))}")
                            print(f"Minimum cost: {min_cost}")
                        else:
                            if data == "NO_PATH":
                                print("Error: No path exists between the vertices.")
                            elif data == "NEGATIVE_CYCLE":
                                print("Error: The graph contains a negative cycle.")
                    except ValueError:
                        print("Invalid input. Please enter integer values for vertices.")
                else:
                    print("No graph loaded.")
            elif choice=="25":
                self.min_cost_path_25()
            elif choice=="26":
                self.count_paths()
            elif choice=="27":
                self.cross_time()
            elif choice=="28":
                self.bridge_and_torch()
            elif choice=="29":
                if self.graph:
                    self.minimum_cost_spanning_tree()
                else:
                    print("No graph loaded.")
            elif choice=="30":
                pre = list(map(int, input("Enter the pre-oder list, separated by spaces: ").split()))
                post = list(map(int, input("Enter the post-oder list, separated by spaces: ").split()))
                root = final_tree(pre, post)
                GraphUI.print_edges(root)
                print()
            elif choice=="31":
                pre=list(map(int, input("Enter pre-order list, separated by spaces: ").split()))
                ino=list(map(int, input("Enter in-order list, separated by spaces: ").split()))
                root=build_tree_pre(ino, pre)
                GraphUI.print_edges(root)
                print()
            elif choice=="32":
                post= list(map(int, input("Enter the post-order list, separated by spaces: ").split()))
                ino=list(map(int, input("Enter in-order list, separated by spaces: ").split()))
                root=build_tree_post(ino, post)
                GraphUI.print_edges(root)
                print()
            elif choice=="33":
                    self.check_if_dag()
            elif choice=="34":
                    self.count_paths_two_vertices()
            elif choice=="35":
                self.count_lowest_paths_two_vertices()
            elif choice=="36":
                self.practical_work5()
            elif choice == "37":
                self.bellman_ford_ui()
            elif choice == "38":
                self.version3ui()

            elif choice == "0":
                print("Exiting program.")
                break
            else:
                print("Invalid option. Please try again.")


def display_graph(graph):
    if graph is None:
        print("No graph to display.")
        return
    print("Vertices and their outgoing edges:")
    for vertex in graph.get_vertices():
        print(f"Vertex {vertex}:")
        out_edges = list(graph.get_out_edges(vertex))
        if out_edges:
            for target, edge_id in out_edges:
                print(f"  -> {target} (Edge ID: {edge_id})")
        else:
            print("  No outgoing edges.")
    print()