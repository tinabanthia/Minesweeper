#pragma once

#include <cinder/gl/Texture.h>

namespace minesweeper {

using cinder::gl::TextureRef;
/**
 * A class that represents an individual cell within a Board
 */
class Tile {
    public:
/**
     * Describes the real state of the Tile
     */
    enum RealState {
        kMine,
        kEmpty
    };

    /**
     * Describes the current state of the Tile
     */
    enum CurrentState {
        kEmptyTile = 0, // a tile that is not surrounded by bombs
        kOne = 1, // a tile that is surrounded by one bomb
        kTwo = 2, // a tile that is surrounded by two bombs
        kThree = 3, // a tile that is surrounded by three bombs
        kFour = 4, // a tile that is surrounded by four bombs
        kFive = 5, // a tile that is surrounded by five bombs
        kSix = 6, // a tile that is surrounded by six bombs
        kSeven = 7, // a tile that is surrounded by seven bombs
        kEight = 8, // a tile that is surrounded by eight bombs
        kFlagged = 9, // a tile that is not uncovered due to the possibility of storing a bomb
        kUnexposed = 10, // a tile that has yet to be either flagged as a bomb or uncovered
        kExposedMine = 11 // a tile that is uncovered to be a mine

    };

    /**
     * Empty constructor that initializes class values
     */
    Tile();

    /**
     * Constructor that initializes class values
     *
     * @param location the position of the Tile within the Board
     */
    Tile(const std::pair<int, int>& location);

    /**
     * Constructor that initializes class values
     *
     * @param real_state Describes the real state of the Tile
     * @param current_state Describes the current state of the Tile
     * @param location the position of the Tile within the Board
     */
    Tile(RealState real_state, CurrentState current_state, const std::pair<int, int>& location);

    /**
     * Copy constructor
     *
     * @param source original object
     * @return new copy
     */
    Tile& operator=(const Tile source);

    CurrentState current_state_;
    RealState real_state_;
    std::pair<int, int> location_;
};
} // namespace minesweeper