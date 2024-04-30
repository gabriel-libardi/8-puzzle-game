import tkinter as tk
import time
import random
import heapq
import os

import numpy as np
from PIL import Image, ImageTk

answer = "Mitocondria"

def clean():
    os.system('cls' if os.name == 'nt' else 'clear') # limpa o terminal

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

        self.black_img = tk.PhotoImage(file="black.png")

        self.tk_images = {}
        for i in range(len(self.start_state)):
            for j in range(len(self.start_state[i])):
                    if self.start_state[i][j] == 0:
                        self.tk_images[self.start_state[i][j]] = tk.PhotoImage(file=f"tile_9.png")
                    else:
                        self.tk_images[self.start_state[i][j]] = tk.PhotoImage(file=f"tile_{self.start_state[i][j]}.png")

        self.create_board()

    def create_board(self):
        for i in range(len(self.start_state)):
            for j in range(len(self.start_state[i])):
                if self.start_state[i][j] != 0:
                    curr_img = self.tk_images[self.start_state[i][j]]
                else:
                    curr_img = self.black_img

                self.tiles[i][j] = tk.Label(self.frame, width=100, height=100, relief="solid", image=curr_img)
                self.tiles[i][j].grid(row=i, column=j, padx=3, pady=3)

    def update_board(self, new_state):
        for i in range(len(new_state)):
            for j in range(len(new_state[i])):
                if new_state[i][j] != 0:
                    self.tiles[i][j].config(image=self.tk_images[new_state[i][j]])
                else:
                    self.tiles[i][j].config(image=self.black_img)
                self.tiles[i][j].update()

    def move_tile(self, move):
        new_state = result(self.start_state, move)
        self.update_board(new_state)
        time.sleep(0.5)
        self.start_state = new_state

    def solve_puzzle(self):
        if not self.solution:
            return

        time.sleep(1)
        for c in range(len(self.solution)):
            player_input = int(input("=== MENU ===\n[1] Avançar\n[2] Fazer um chute\n============\nEscolha uma opção: "))
            print(player_input)
            if player_input == 2:
                clean()
                guess = input("A resposta do puzzle é: ")
                if str(guess).upper() == answer.upper():
                    clean()
                    print("Voce ganhou!")
                    return
                else:
                    clean()
                    print("Resposta errada :(")
                    time.sleep(2)
                    clean()
                    continue
            clean()
            self.move_tile(self.solution[c])


def main():
    start_state = [[8, 6, 7],
                   [2, 5, 4],
                   [3, 0, 1]]

    goal_state = [[1, 2, 3], [4, 5, 6], [7, 8, 0]]

    solution_astar = astar_search(start_state, goal_state)
    solution_dfs = dfs_search(start_state, goal_state)

    if solution_dfs or solution_astar:
        clean()
        game_mode = int(input("=== Selecione o modo de jogo ===\n\t[1] Easy\n\t[2] Hard\nInsira um valor: "))
        clean()
        root = tk.Tk()
        if game_mode == 1:
            gui = EightPuzzleGUI(root, start_state, goal_state, solution_astar)
        elif game_mode == 2:
            gui = EightPuzzleGUI(root, start_state, goal_state, solution_dfs)
        root.after(10, gui.solve_puzzle)
        root.mainloop()
    else:
        print("No solution found.")

if __name__ == "__main__":
    main()
    