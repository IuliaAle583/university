from graph import DirectedGraph

from itertools import combinations

class BridgeGraph(DirectedGraph):
    def __init__(self, crossing_times):
        # initializes the graph with the number of people as vertices
        super().__init__(len(crossing_times))
        self.cross_time = crossing_times
        self.vertices = []

    def generate_all_states(self):
        # generates all possible states of people on one side and the position of the torch
        people = set(range(len(self.cross_time)))
        for count in range(len(self.cross_time) + 1):
            for people in combinations(people, count):
                # append states for both torch positions (True for original side, False for the other side)
                self.vertices.append((frozenset(people), True))
                self.vertices.append((frozenset(people), False))

    def get_neighbors(self, state):
        # given a state, returns all possible next states (neighbors) and the cost of moving to those states
        current_side, torch_pos = state
        opposite_side = set(range(len(self.cross_time))) - current_side

        neighbors = []
        if torch_pos:
            # if the torch is on the original side, combinations of 2 people can cross
            moves = combinations(current_side, 2) if len(current_side) > 1 else [(p,) for p in current_side]
        else:
            # if the torch is on the other side, only one person can return with the torch
            moves = combinations(opposite_side, 1)

        # iterate over all possible moves
        for move in moves:
            # calculate the new state after the move
            new_side = set(current_side).symmetric_difference(move)
            # the cost of the move is determined by the slowest person
            move_cost = max(self.cross_time[p] for p in move)
            # add the new state to the neighbors list with the corresponding move cost
            new_state = (frozenset(new_side), not torch_pos)   # switch the torch position
            neighbors.append((new_state, move_cost))

        return neighbors

    #Dijkstra's algorithm
    def solution(self):
        from heapq import heappush, heappop
        priority_queue = []
        start_state = (frozenset(range(len(self.cross_time))), True)
        heappush(priority_queue, (0, start_state))
        visited = {}
        while priority_queue:
            # get the state with the lowest cost
            cost, state = heappop(priority_queue)
            # check if we have reached the solution
            if state[0] == frozenset() and not state[1]:
                print(f"Solution found with cost {cost}")
                return cost
            # skip processing if this state has been visited with a lower cost
            if state in visited and visited[state] <= cost:
                continue
            visited[state] = cost
            # find all neighboring states and their move costs
            for neighbor, move_cost in self.get_neighbors(state):
                next_cost = cost + move_cost
                # if this new state is not visited, or there is a cheaper way to get to it, add it to the queue
                if neighbor not in visited or visited[neighbor] > next_cost:
                    heappush(priority_queue, (next_cost, neighbor))
        return float('inf')