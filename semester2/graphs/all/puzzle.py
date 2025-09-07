import random
import math
from collections import deque


class Board:
    def __init__(self, cells):
        self.size = 4
        self.cells = cells

    def __str__(self):
        string = ""
        for i in range(self.size):
            for j in range(self.size):
                string += self.cells[i * self.size + j] + " "
            string += "\n"
        string = string[:-1]
        return string

    # simulate a move of the empty tile in a given direction
    def run(self, action):
        new_tiles = self.cells[:]   # copy of the board
        empty = new_tiles.index("0")    # index of the empty tile
        if action == 'l':   # move l
            if empty % self.size > 0:
                new_tiles[empty - 1], new_tiles[empty] = new_tiles[empty], new_tiles[empty - 1]
        elif action == 'r': # move r
            if empty % self.size < (self.size - 1):
                new_tiles[empty + 1], new_tiles[empty] = new_tiles[empty], new_tiles[empty + 1]

        elif action == 'u':     # move up
            if empty - self.size >= 0:
                new_tiles[empty - self.size], new_tiles[empty] = new_tiles[empty], new_tiles[empty - self.size]

        elif action == 'd':     # move down
            if empty + self.size < self.size * self.size:
                new_tiles[empty+self.size], new_tiles[empty] = new_tiles[empty], new_tiles[empty+self.size]

        return Board(new_tiles)     # new board state after the move


class Node:
    def __init__(self, state, parent, action):
        self.state = state      # # current board state
        self.parent = parent
        self.action = action

    def __str__(self):
        return str(self.state)

    def __eq__(self, other):
        return self.state.cells == other.state.cells


def check_is_solution_possible(initial_list):
    if len(initial_list) != 16:
        return False
    for i in range(16):
        if str(i) not in initial_list:
            return False
    inv = 0     # count of inversions
    empty = initial_list.index("0")
    for i in range(len(initial_list)):
        for j in range(i+1, len(initial_list)):
            if initial_list[i] > initial_list[j]:
                inv += 1
    # a puzzle is solvable if the number of inversions + row of empty tile is even
    return (empty // 4 + inv) % 2 == 0


def test_sol(cells):
    return cells == ['1', '2', '3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '0']

# generate all possible children of the current node by applying all valid moves
def get_children(parent_node):

    children = []
    actions = ['l', 'r', 'u', 'd']
    for action in actions:
        child_state = parent_node.state.run(action)
        child_node = Node(child_state, parent_node, action)
        children.append(child_node)
    return children

# backtrack from a node to the root to find the full path
def find_path(node):
    path = []
    while (node.parent is not None):
        path.append(node)
        node = node.parent
    return path


def run_bfs(node):
    queue = deque()
    queue.append(node)
    visited = set()
    visited.add(tuple(node.state.cells))    # track visited states
    while queue:
        current_node = queue.popleft()

        if test_sol(current_node.state.cells):      #  if goal state is reached
            path = find_path(current_node)
            path.append(node)       # add starting node
            path.reverse()
            return path

        for child in get_children(current_node):
            key = tuple(child.state.cells)
            if key not in visited:
                visited.add(key)
                queue.append(child)

    return None

# wrapper function to start the BFS if puzzle is solvable
def solve(initial_list):
    if not check_is_solution_possible(initial_list):
        return None
    root = Node(Board(initial_list), None, None)
    return run_bfs(root)