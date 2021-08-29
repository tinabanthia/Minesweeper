#include "core/game_engine.h"

namespace minesweeper {

GameEngine::GameEngine() {
    board_ = Board();
}

GameEngine::GameEngine(size_t width, size_t height, size_t mines) {
    board_ = Board(width, height, mines);
}

GameEngine& GameEngine::operator=(const GameEngine& source) {
    board_.ClearBoard();
    board_ = source.board_;
    return *this;
}

void GameEngine::UncoverTile(glm::vec2 position) {
    Tile tile = board_.all_tiles_[std::make_pair(position.x, position.y)];
    if (tile.real_state_ == Tile::kMine) {
        UncoverRealBoardState();

    } else if (tile.current_state_ == Tile::kUnexposed || tile.current_state_ == Tile::kFlagged) {
        board_.SetTileCurrentState(tile);
    }
}

void GameEngine::FlagTile(glm::vec2 position) {
    Tile tile = board_.all_tiles_[std::make_pair(position.x, position.y)];
    if (tile.current_state_ == Tile::kUnexposed) {
        board_.SetTileFlagged(tile);
    }
}

void GameEngine::UncoverRealBoardState() {
    for (size_t row = 0; row < board_.height_; row++) {
        for (size_t column = 0; column < board_.width_; column++) {
            std::pair<int, int> location = std::make_pair(row, column);

            if (board_.IsMine(location)) {
                board_.all_tiles_[location].current_state_ = Tile::kExposedMine;
            }
        }
    }
}

bool GameEngine::IsWinner() {
    for (size_t row = 0; row < board_.height_; row++) {
        for (size_t column = 0; column < board_.width_; column++) {
            std::pair<int, int> location = std::make_pair(row, column);

            if (board_.IsMine(location)) {
                if (board_.all_tiles_[location].current_state_ != Tile::kFlagged) {
                    return false;
                }
            }
        }
    }

    return true;
}

} // namespace minesweeper