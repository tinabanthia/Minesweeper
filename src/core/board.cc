#include "../../include/core/board.h"

namespace minesweeper {

Board::Board() {
    InitializeBoard();
}

Board::Board(size_t width, size_t height, size_t num_mines) {
    width_ = width;
    height_ = height;
    number_mines_ = num_mines;
    InitializeBoard();
}

void Board::InitializeBoard() {
    for (size_t row = 0; row < width_; ++row) {
        for (size_t column = 0; column < height_; ++column) {
            std::pair<int, int> position = std::make_pair(row, column);
            all_tiles_[position] = Tile(Tile::kEmpty, Tile::kUnexposed, position);
        }
    }

    GenerateMines();
}

void Board::GenerateMines() {
    for (size_t idx = 0; idx < number_mines_; ++idx) {
        std::pair<int, int> location = std::make_pair(rand() % (height_ - 1), rand() % (width_ - 1));

        while (IsMine(location)) {
            location = std::make_pair(rand() % (height_ - 1), rand() % (width_ - 1));
        }

        mines_[location] = Tile(Tile::kMine, Tile::kUnexposed, location);
        all_tiles_[location] = Tile(Tile::kMine, Tile::kUnexposed, location);
    }
}

bool Board::IsMine(std::pair<int, int> location) {
    return all_tiles_[location].real_state_ == Tile::kMine;
}

void Board::SetTileCurrentState(Tile tile) {
    std::pair<size_t, size_t> current_pos = tile.location_;
    size_t num_mines = CountNumSurroundingMines(all_tiles_[current_pos]);

    Tile::CurrentState curr_tile_state = Tile::kEmptyTile;

    if (num_mines == Tile::kOne) {
        curr_tile_state = Tile::kOne;
    } else if (num_mines == Tile::kTwo) {
        curr_tile_state = Tile::kTwo;
    } else if (num_mines == Tile::kThree) {
        curr_tile_state = Tile::kThree;
    } else if (num_mines == Tile::kFour) {
        curr_tile_state = Tile::kFour;
    } else if (num_mines == Tile::kFive) {
        curr_tile_state = Tile::kFive;
    } else if (num_mines == Tile::kSix) {
        curr_tile_state = Tile::kSix;
    } else if (num_mines == Tile::kSeven) {
        curr_tile_state = Tile::kSeven;
    } else if (num_mines == Tile::kEight) {
        curr_tile_state = Tile::kEight;
    }
    all_tiles_[current_pos].current_state_ = curr_tile_state;
}

void Board::SetTileFlagged(Tile tile) {
    all_tiles_[tile.location_].current_state_ = Tile::kFlagged;
}

size_t Board::CountNumSurroundingMines(Tile tile) {
    std::vector<std::pair<size_t, size_t>> locations = GetNeighboringTileLocations(tile);
    size_t num_mines = 0;

    for (const std::pair<size_t, size_t>& location : locations) {
        if (all_tiles_[location].real_state_ == Tile::kMine) {
            ++num_mines;
        }
    }
    return num_mines;
}

std::vector<std::pair<size_t, size_t>> Board::GetNeighboringTileLocations(Tile tile) {
    std::vector<std::pair<size_t, size_t>> locations;
    size_t x_pos = tile.location_.first;
    size_t y_pos = tile.location_.second;

    bool is_right = tile.location_.first + 1 < width_;
    bool is_left = tile.location_.first - 1 >= 0;
    bool is_up = tile.location_.second + 1 < height_;
    bool is_down = tile.location_.second - 1 >= 0;

    if (is_right) {
        locations.push_back(std::make_pair(x_pos + 1, y_pos));
    }
    if (is_up) {
        locations.push_back(std::make_pair(x_pos, y_pos + 1));
    }
    if (is_left) {
        locations.push_back(std::make_pair(x_pos - 1, y_pos));
    }
    if (is_down) {
        locations.push_back(std::make_pair(x_pos, y_pos - 1));
    }
    if (is_right && is_up) {
        locations.push_back(std::make_pair(x_pos + 1, y_pos + 1));
    }
    if (is_right && is_down) {
        locations.push_back(std::make_pair(x_pos + 1, y_pos - 1));
    }
    if (is_left && is_up) {
        locations.push_back(std::make_pair(x_pos - 1, y_pos + 1));
    }
    if (is_left && is_down){
        locations.push_back(std::make_pair(x_pos - 1, y_pos - 1));
    }
    return locations;
}

Board& Board::operator=(const Board source) {
    ClearBoard();
    all_tiles_ = source.all_tiles_;
    mines_ = source.mines_;
    height_ = source.height_;
    width_ = source.width_;
    number_mines_ = source.number_mines_;
    return *this;
}

void Board::ClearBoard() {
    all_tiles_.clear();
    mines_.clear();
}

} // namespace minesweeper