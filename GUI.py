import tkinter as tk
import time
import random
import heapq
import numpy as np


class Node:
    def __init__(self, state, parent=None, move=None, cost=0):
        self.state = state
        self.parent = parent
        self.move = move
        self.cost = cost
        self.depth = 0
        if parent:
            self.depth = parent.depth + 1

    def __lt__(self, other):
        return (self.cost + self.depth) < (other.cost + other.depth)

class PriorityQueue:
    def __init__(self):
        self.elements = []

    def empty(self):
        return len(self.elements) == 0

    def put(self, item, priority):
        heapq.heappush(self.elements, (priority, item))

    def get(self):
        return heapq.heappop(self.elements)[1]

def find_blank(state):
    for i in range(len(state)):
        for j in range(len(state[i])):
            if state[i][j] == 0:
                return i, j

def actions(state):
    i, j = find_blank(state)
    possible_actions = []
    if i > 0:
        possible_actions.append('up')
    if i < len(state) - 1:
        possible_actions.append('down')
    if j > 0:
        possible_actions.append('left')
    if j < len(state[i]) - 1:
        possible_actions.append('right')
    return possible_actions

def result(state, action):
    i, j = find_blank(state)
    new_state = [row[:] for row in state]
    if action == 'up':
        new_state[i][j], new_state[i-1][j] = new_state[i-1][j], new_state[i][j]
    elif action == 'down':
        new_state[i][j], new_state[i+1][j] = new_state[i+1][j], new_state[i][j]
    elif action == 'left':
        new_state[i][j], new_state[i][j-1] = new_state[i][j-1], new_state[i][j]
    elif action == 'right':
        new_state[i][j], new_state[i][j+1] = new_state[i][j+1], new_state[i][j]
    return new_state

def heuristic(state, goal_state):
    return np.sum(state != goal_state)

def astar_search(start_state, goal_state):
    start_node = Node(start_state)
    frontier = PriorityQueue()
    frontier.put(start_node, 0)
    explored = set()

    while not frontier.empty():
        current_node = frontier.get()
        current_state = current_node.state

        if np.array_equal(current_state, goal_state):
            path = []
            while current_node.parent:
                path.append(current_node.move)
                current_node = current_node.parent
            return path[::-1]

        explored.add(tuple(map(tuple, current_state)))

        for action in actions(current_state):
            new_state = result(current_state, action)
            if tuple(map(tuple, new_state)) not in explored:
                child_node = Node(new_state, current_node, action, current_node.cost + 1)
                frontier.put(child_node, child_node.cost + heuristic(new_state, goal_state))

    return None  # If no solution found

def dfs_search(start_state, goal_state, max_depth=float('inf')):
    stack = [(start_state, [])]
    visited = set()
    while stack:
        state, path = stack.pop()
        if state == goal_state:
            return path
        if len(path) < max_depth:
            visited.add(tuple(map(tuple, state)))
            for action in actions(state):
                new_state = result(state, action)
                if tuple(map(tuple, new_state)) not in visited:
                    stack.append((new_state, path + [action]))
    return None  # If no solution found within max_depth

def generate_random_state(size=3):
    numbers = list(range(size*size))
    random.shuffle(numbers)
    return [numbers[i:i+size] for i in range(0, size*size, size)]

class EightPuzzleGUI:
    def __init__(self, master, start_state, goal_state, solution):
        self.master = master
        self.master.title("8-Puzzle Solver")
        self.start_state = start_state
        self.goal_state = goal_state
        self.solution = solution

        self.frame = tk.Frame(self.master)
        self.frame.pack()

        self.tiles = [[None] * len(self.start_state) for _ in range(len(self.start_state))]

        self.create_board()

    def create_board(self):
        for i in range(len(self.start_state)):
            for j in range(len(self.start_state[i])):
                if self.start_state[i][j] != 0:
                    bg_color = "light blue"
                    font_color = "blue"
                    tile_font = ("Arial", 2, 'bold')
                else:
                    bg_color = "dark blue"
                    font_color = "dark blue"
                    tile_font = ("Arial", 2, 'bold')

                self.tiles[i][j] = tk.Label(
                    self.frame, text=str(self.start_state[i][j]), font=("Arial", 24, "bold"), width=40, height=20,
                    bg=bg_color, fg=font_color, borderwidth=2, relief="solid",
                )
                self.tiles[i][j].grid(row=i, column=j, padx=3, pady=3)

    def update_board(self, new_state):
        for i in range(len(new_state)):
            for j in range(len(new_state[i])):
                if new_state[i][j] != 0:
                    bg_color = "light blue"
                    font_color = "blue"
                    self.tiles[i][j].config(text=str(new_state[i][j]), bg=bg_color, fg=font_color)
                else:
                    bg_color = "dark blue"
                    font_color = "dark blue"
                    self.tiles[i][j].config(text="", bg=bg_color, fg=font_color)
                self.tiles[i][j].update()

    def solve_puzzle(self):
        if not self.solution:
            return

        time.sleep(1)
        for move in self.solution:
            new_state = result(self.start_state, move)
            self.update_board(new_state)
            time.sleep(0.5)
            self.start_state = new_state

def main():
    algorithm_choice = input("Enter 'A' to solve using A* algorithm or 'D' to solve using DFS algorithm: ").upper()

    start_state = [[8, 6, 7],
                   [2, 5, 4],
                   [3, 0, 1]]

    goal_state = [[1, 2, 3], [4, 5, 6], [7, 8, 0]]

    start = time.time()

    if algorithm_choice == 'A':
        solution = astar_search(start_state, goal_state)
    elif algorithm_choice == 'D':
        solution = dfs_search(start_state, goal_state)
    else:
        print("Invalid choice. Exiting.")
        return

    end = time.time()
    print(end - start)

    if solution:
        print(solution)
        print(len(solution))
        root = tk.Tk()
        gui = EightPuzzleGUI(root, start_state, goal_state, solution)
        root.after(10, gui.solve_puzzle)
        root.mainloop()
    else:
        print("No solution found.")

if __name__ == "__main__":
    main()
