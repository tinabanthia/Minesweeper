#include "../../include/core/tile.h"

namespace minesweeper {

Tile::Tile(){

}

Tile::Tile(const std::pair<int, int>& location) {
    real_state_ = kEmpty;
    current_state_ = kUnexposed;
    location_ = location;
}

Tile::Tile(RealState real_state, CurrentState current_state, const std::pair<int, int>& location) {
    real_state_ = real_state;
    current_state_ = current_state;
    location_ = location;
}

Tile &Tile::operator=(const Tile source) {
    current_state_ = source.current_state_;
    real_state_ = source.real_state_;
    location_ = source.location_;
    return *this;
}

} // namespace minesweeper