#include <catch2/catch.hpp>
#include <core/board.h>

TEST_CASE("Check empty constructor") {
    minesweeper::Board* board = new minesweeper::Board();

    SECTION("Correct constant values"){
        REQUIRE(board->width_ == 10);
        REQUIRE(board->height_ == 10);
        REQUIRE(board->number_mines_ == 25);
    }
    delete board;
}

TEST_CASE("Check non-empty constructor") {
    minesweeper::Board* board = new minesweeper::Board(20, 20, 40);

    SECTION("Correct constant values"){
        REQUIRE(board->width_ == 20);
        REQUIRE(board->height_ == 20);
        REQUIRE(board->number_mines_ == 40);
    }
    delete board;
}

TEST_CASE("Check IsMine() function") {
    minesweeper::Board *board = new minesweeper::Board(10, 10, 40);
    board->all_tiles_[std::make_pair(3, 0)] = minesweeper::Tile(minesweeper::Tile::kEmpty,
                                                                minesweeper::Tile::kUnexposed,
                                                                std::make_pair(3, 0));
    board->all_tiles_[std::make_pair(0, 0)] = minesweeper::Tile(minesweeper::Tile::kMine,
                                                                minesweeper::Tile::kUnexposed,
                                                                std::make_pair(0, 0));

    SECTION("Not a mine") {
        REQUIRE(!board->IsMine(std::make_pair(3, 0)));
    }

    SECTION("A mine") {
        REQUIRE(board->IsMine(std::make_pair(0, 0)));
    }
    delete board;
}

TEST_CASE("Check if mines are generated") {
    minesweeper::Board* board = new minesweeper::Board(10, 10, 40);

    SECTION("Correct number of mines"){
        size_t num_mines = 0;
        for (size_t row = 0; row < 10; ++row) {
            for (size_t column = 0; column < 10; ++column) {
                if (board->IsMine(std::make_pair(row, column))){
                    ++num_mines;
                }
            }
        }

        REQUIRE(num_mines == 40);
    }

    SECTION("Correct initial state"){
        for (size_t row = 0; row < 10; ++row) {
            for (size_t column = 0; column < 10; ++column) {
                std::pair<int, int> location = std::make_pair(row, column);
                if (board->IsMine(location)){
                    REQUIRE(board->all_tiles_[location].current_state_ == minesweeper::Tile::kUnexposed);
                }
            }
        }

    }

    SECTION("Correct real state"){
        for (size_t row = 0; row < 10; ++row) {
            for (size_t column = 0; column < 10; ++column) {
                std::pair<int, int> location = std::make_pair(row, column);
                if (board->IsMine(location)){
                    REQUIRE(board->all_tiles_[location].real_state_ == minesweeper::Tile::kMine);
                }
            }
        }

    }

    delete board;
}

TEST_CASE("Check if non-mie tiles are generated") {
    minesweeper::Board* board = new minesweeper::Board(10, 10, 40);

    SECTION("Correct number of non-mines"){
        size_t num_empty_tiles = 0;
        for (size_t row = 0; row < 10; ++row) {
            for (size_t column = 0; column < 10; ++column) {
                if (!board->IsMine(std::make_pair(row, column))){
                    ++num_empty_tiles;
                }
            }
        }

        REQUIRE(num_empty_tiles == 60);
    }

    SECTION("Correct initial state"){
        for (size_t row = 0; row < 10; ++row) {
            for (size_t column = 0; column < 10; ++column) {
                std::pair<int, int> location = std::make_pair(row, column);
                if (board->IsMine(location)){
                    REQUIRE(board->all_tiles_[location].current_state_ == minesweeper::Tile::kUnexposed);
                }
            }
        }

    }

    SECTION("Correct real state"){
        for (size_t row = 0; row < 10; ++row) {
            for (size_t column = 0; column < 10; ++column) {
                std::pair<int, int> location = std::make_pair(row, column);
                if (!board->IsMine(location)){
                    REQUIRE(board->all_tiles_[location].real_state_ == minesweeper::Tile::kEmpty);
                }
            }
        }

    }

    delete board;
}

TEST_CASE("Check ClearBoard() function") {
    minesweeper::Board *board = new minesweeper::Board();
    board->ClearBoard();

    SECTION("No values in board"){
        REQUIRE(board->all_tiles_.size() == 0);
        REQUIRE(board->mines_.size() == 0);
    }
}

TEST_CASE("Check if tile state is changed correctly after user interaction") {
   minesweeper::Board *board = new minesweeper::Board(5, 5, 10);
    for (size_t row = 0; row < 10; ++row) {
        for (size_t column = 0; column < 10; ++column) {
            board->all_tiles_[std::make_pair(row, column)] = minesweeper::Tile(minesweeper::Tile::kEmpty,
                                                                        minesweeper::Tile::kUnexposed,
                                                                        std::make_pair(row, column));
        }
    }

    // Manually set all mines
    board->all_tiles_[std::make_pair(0, 0)] = minesweeper::Tile(minesweeper::Tile::kMine,
                                                                minesweeper::Tile::kUnexposed,
                                                                std::make_pair(0, 0));
    board->all_tiles_[std::make_pair(1, 1)] = minesweeper::Tile(minesweeper::Tile::kMine,
                                                                minesweeper::Tile::kUnexposed,
                                                                std::make_pair(1, 1));
    board->all_tiles_[std::make_pair(2, 2)] = minesweeper::Tile(minesweeper::Tile::kMine,
                                                                minesweeper::Tile::kUnexposed,
                                                                std::make_pair(2, 2));
    board->all_tiles_[std::make_pair(3, 3)] = minesweeper::Tile(minesweeper::Tile::kMine,
                                                                minesweeper::Tile::kUnexposed,
                                                                std::make_pair(3, 3));
    board->all_tiles_[std::make_pair(4, 4)] = minesweeper::Tile(minesweeper::Tile::kMine,
                                                                minesweeper::Tile::kUnexposed,
                                                                std::make_pair(4, 4));
    board->all_tiles_[std::make_pair(3, 0)] = minesweeper::Tile(minesweeper::Tile::kMine,
                                                                minesweeper::Tile::kUnexposed,
                                                                std::make_pair(3, 0));
    board->all_tiles_[std::make_pair(4, 0)] = minesweeper::Tile(minesweeper::Tile::kMine,
                                                                minesweeper::Tile::kUnexposed,
                                                                std::make_pair(4, 0));
    board->all_tiles_[std::make_pair(2, 1)] = minesweeper::Tile(minesweeper::Tile::kMine,
                                                                minesweeper::Tile::kUnexposed,
                                                                std::make_pair(2, 1));
    board->all_tiles_[std::make_pair(2, 3)] = minesweeper::Tile(minesweeper::Tile::kMine,
                                                                minesweeper::Tile::kUnexposed,
                                                                std::make_pair(2, 3));
    board->all_tiles_[std::make_pair(1, 3)] = minesweeper::Tile(minesweeper::Tile::kMine,
                                                                minesweeper::Tile::kUnexposed,
                                                                std::make_pair(1, 3));

    SECTION("Correct current state with one surrounding bomb"){
        board->SetTileCurrentState(std::make_pair(0, 3));
        REQUIRE(board->all_tiles_[std::make_pair(0, 3)].current_state_ == minesweeper::Tile::kOne);

        board->SetTileCurrentState(std::make_pair(0, 1));
        REQUIRE(board->all_tiles_[std::make_pair(0, 1)].current_state_ == minesweeper::Tile::kOne);


        board->SetTileCurrentState(std::make_pair(0, 4));
        REQUIRE(board->all_tiles_[std::make_pair(0, 4)].current_state_ == minesweeper::Tile::kOne);
    }

    SECTION("Correct current state with two surrounding bombs"){
        board->SetTileCurrentState(std::make_pair(4, 1));
        REQUIRE(board->all_tiles_[std::make_pair(4, 1)].current_state_ == minesweeper::Tile::kTwo);

        board->SetTileCurrentState(std::make_pair(0, 2));
        REQUIRE(board->all_tiles_[std::make_pair(0, 2)].current_state_ == minesweeper::Tile::kTwo);

        board->SetTileCurrentState(std::make_pair(1, 0));
        REQUIRE(board->all_tiles_[std::make_pair(1, 0)].current_state_ == minesweeper::Tile::kTwo);

        board->SetTileCurrentState(std::make_pair(3, 4));
        REQUIRE(board->all_tiles_[std::make_pair(3, 4)].current_state_ == minesweeper::Tile::kTwo);
    }

    SECTION("Correct current state with three surrounding bombs"){
        board->SetTileCurrentState(std::make_pair(2, 1));
        REQUIRE(board->all_tiles_[std::make_pair(2, 1)].current_state_ == minesweeper::Tile::kThree);

        board->SetTileCurrentState(std::make_pair(2, 4));
        REQUIRE(board->all_tiles_[std::make_pair(2, 4)].current_state_ == minesweeper::Tile::kThree);

    }

    SECTION("Correct current state with four surrounding bombs"){
        board->SetTileCurrentState(std::make_pair(3, 1));
        REQUIRE(board->all_tiles_[std::make_pair(3, 1)].current_state_ == minesweeper::Tile::kFour);
    }

    SECTION("Correct current state with five surrounding bombs"){
        board->SetTileCurrentState(std::make_pair(1, 2));
        REQUIRE(board->all_tiles_[std::make_pair(1, 2)].current_state_ == minesweeper::Tile::kFive);
    }

    SECTION("Correct current state with no surrounding bombs"){
        board->SetTileCurrentState(std::make_pair(0, 4));
        REQUIRE(board->all_tiles_[std::make_pair(0, 4)].current_state_ == minesweeper::Tile::kOne);
    }
}