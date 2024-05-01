import ctypes

search = ctypes.cdll.LoadLibrary('build/graph_search.so')
search.A_star.restype = ctypes.POINTER(ctypes.c_char)
BOARD_SIZE = 9


def a_star_search(py_start_pos:list):
    int_array = ctypes.c_int*BOARD_SIZE
    start_position = int_array(0)

    index = 0
    for row in py_start_pos:
        for num in row:
            start_position[index] = num
            index += 1
    
    a = ctypes.POINTER(ctypes.c_char)
    a = search.A_star(start_position)
    print(list(a))


if __name__ == '__main__':
    a_star_search([[2, 8, 3],
                   [1, 6, 4],
                   [7, 0, 5]])
