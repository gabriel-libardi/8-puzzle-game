import ctypes

search = ctypes.cdll.LoadLibrary('build/graph_search.so')
BOARD_SIZE = 9


def a_star_search(start:list):
    int_array = ctypes.c_int*BOARD_SIZE
    start_position = int_array(0)

    index = 0
    for row in matrix:
        for num in row:
            start_position[index] = num
            index += 1
    
    a = search.a_star_search(start_position)
