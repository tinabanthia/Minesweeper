#pragma once

#include <cinder/gl/Texture.h>
#include "tile.h"

namespace minesweeper {

using cinder::gl::TextureRef;
/**
 * A class that represents the n x n board of Tiles
 */
class Board {

public:
    /**
     * Empty constructor that initializes class values
     */
    Board();

    /**
     * Constructor that takes in values of board dimensions and number of mines
     *
     * @param width the horizontal size of the board
     * @param height the vertical size of the board
     * @param num_mines total number of mines planted in a board
     */
    Board(size_t width, size_t height, size_t num_mines);

    /**
     * Sets the Tiles within the board to default values
     */
    void InitializeBoard();

    /**
     * Create mines randomly for a board
     */
    void GenerateMines();

    /**
     * Find out if the a tile on the given location is a Tile
     *
     * @param location the location of the Tile
     * @return
     */
    bool IsMine(std::pair<int, int> location);

    /**
     * Alters the state of the tile from unexposed to its respective state
     *
     * @param tile the
     */
    void SetTileCurrentState(Tile tile);

    /**
     * Count the number of mines surrounding given tile
     *
     *  @param tile    the tile to count
     */
    size_t CountNumSurroundingMines(Tile tile);

    /**
     * Changes the state of a board from unexposed to flagged
     *
     * @param tile
     */
    void SetTileFlagged(Tile tile);

    /**
     * Copy constructor
     *
     * @param source original object
     * @return new copy
     */
    Board& operator=(const Board source);

    /**
     * Deletes the board class values
     */
    void ClearBoard();

    std::map<std::pair<int, int>, Tile> all_tiles_;
    std::map<std::pair<int, int>, Tile> mines_;

    int width_ = 10;
    int height_ = 10;
    int number_mines_ = 25;

private:
    std::vector<std::pair<size_t, size_t>> GetNeighboringTileLocations(Tile tile);

};
} // namespace minesweeper