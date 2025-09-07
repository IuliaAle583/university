from collections import deque

class WolfGoatCabbage:
    def __init__(self):
        self.start = (0, 0, 0, 0)
        self.goal = (1, 1, 1, 1)

    def is_valid(self, state):
        man, wolf, goat, cabbage = state
        if goat == wolf and man != goat:
            return False
        if goat == cabbage and man != goat:
            return False
        return True

    # get all valid next states by trying possible moves
    def get_next_states(self, state):
        man, wolf, goat, cabbage = state
        next_states = []
        possible_moves = [(), ('wolf',), ('goat',), ('cabbage',)]

        # try each move
        for move in possible_moves:
            new_state = [man, wolf, goat, cabbage]      # copy the current state
            new_state[0] = 1 - man      # # the man moves to the opposite bank

            # if the man is taking an item, change that item's state
            for item in move:
                idx = {'wolf': 1, 'goat': 2, 'cabbage': 3}[item]
                if new_state[idx] == man:
                    new_state[idx] = 1 - new_state[idx]
                else:
                    break
            else:
                # if no invalid move occurred, create a new state tuple
                new_tuple = tuple(new_state)
                if self.is_valid(new_tuple):    # if the new state is valid, add it to the next states list
                    next_states.append(new_tuple)
        return next_states

    # perform a BFS to find the solution path
    def solve(self):
        queue = deque()
        queue.append((self.start, [self.start]))
        visited = set()
        visited.add(self.start)

        while queue:
            current_state, path = queue.popleft()
            if current_state == self.goal:
                return path
            for next_state in self.get_next_states(current_state):
                if next_state not in visited:
                    visited.add(next_state)
                    queue.append((next_state, path + [next_state]))
        return None
