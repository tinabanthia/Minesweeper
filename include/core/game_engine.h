#include "tile.h"
#include "board.h"

namespace minesweeper {

/**
 * A class that contains functions that represent the rules of the Minesweeper game
 */
class GameEngine {
public:
    /**
     * Empty constructor that initializes class values
     */
    GameEngine();

    /**
     * Constructor that takes in values of board dimensions and number of mines
     *
     * @param width the horizontal size of the board
     * @param height the vertical size of the board
     * @param num_mines total number of mines planted in a board
     */
    GameEngine(size_t width, size_t height, size_t mines);

    /**
     * Reveals the tile to the user
     */
    void UncoverTile(glm::vec2);

    /**
     * Changes a tile from unexposed to flagged
     *
     * @param position the location of the tile on the display screen
     */
    void FlagTile(glm::vec2 position);

    /**
     * Reveals all the mines once the user has clicked on a mine
     */
    void UncoverRealBoardState();

    /**
     * Copy constructor
     *
     * @param source original object
     * @return new copy
     */
    GameEngine& operator=(const GameEngine& source);

    /**
     * Check if the board is in a state with a winner
     */
    bool IsWinner();

    Board board_;
};
} // namespace minesweeper


