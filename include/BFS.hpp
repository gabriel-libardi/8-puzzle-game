#ifndef __BFS_HPP__
#define __PFS_HPP__

#include <cstddef>

#define BOARD_SIZE 9
typedef int* path;


class Board {
    private:
        int num_map[BOARD_SIZE];
    
    public:
        int& operator[](const std::size_t& index);

        void up();
        void down();
        void left();
        void right();
}

path bfs_search(const Board& init_position);

#endif