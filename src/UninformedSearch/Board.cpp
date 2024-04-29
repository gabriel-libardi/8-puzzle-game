#include "BFS.cpp"
#include <cstddef>
#include <stdexcept>


int& Board::operator[](const std::size_t& index) {
    if (index < BOARD_SIZE) {
        return this.num_map[index];

    } else {
        throw out_of_range("Index should be within the board size\n");
    }
}


void Board::up() {
    
}