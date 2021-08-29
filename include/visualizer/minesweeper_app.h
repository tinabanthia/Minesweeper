#pragma once

#include <core/game_engine.h>
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using glm::vec2;

namespace minesweeper {

namespace visualizer {

/**
 * The class that retrieves and displays data through user interaction and the game engine
 */
class MinesweeperApp : public ci::app::App {
public:

    /**
     * Describes the current state of the app
     */
    enum AppState {
        kPlayingTimer, // the game screen with the timer mode of the game
        kPlayingGems, // the game screen with the gems mode of the game
        kStartGame, // the starting screen with an option to choose between nodes
        kGameOverWin, // a screen with the winner message displaying the stats of the game
        kGameOverLose // a screen with the loser message displaying the stats of the game
    };

    const int kWindowSize = 750;
    const size_t kImageDimension = 28;

    /**
     * Empty constructor that initializes class values
     */
    MinesweeperApp();

    /**
     * Displays the game to the screen
     */
    void draw() override;

    /**
     * If a user clicks with their mouse, this event is passed on in this method
     * where there are calls to the game_engine.cc class
     *
     * @param event the interaction from a user
     */
    void mouseDown(ci::app::MouseEvent event) override;

    GameEngine game_engine_;
    cinder::Timer timer_;
    glm::vec2 board_translation_ = glm::vec2(100, 100);

    size_t tile_size_multiplier_ = 50;
    glm::vec2 timer_position_ = glm::vec2(470, 200);
    glm::vec2 timer_label_position_ = glm::vec2(800, 150);

    // Positions of images for the start screen
    glm::vec2 start_game_position_ = glm::vec2(30, 50);
    glm::vec2 easy_button_position_ = glm::vec2(280, 400);
    glm::vec2 normal_button_position_ = glm::vec2(350, 580);
    glm::vec2 hard_button_position_ = glm::vec2(270, 700);
    glm::vec2 timer_button_position_ = glm::vec2(650, 570);

    cinder::Font timer_font_ = cinder::Font("GB18030Bitmap", 80);
    cinder::Font start_font_ = cinder::Font("Futura-Bold", 50);

    // Positions of the labels for the start screen
    glm::vec2 easy_label_position_ = glm::vec2(450, 510);
    glm::vec2 normal_label_position_ = glm::vec2(400, 640);
    glm::vec2 hard_label_position_ = glm::vec2(440, 785);
    glm::vec2 start_timer_label_position_ = glm::vec2(770, 645);

    glm::vec2 easy_top_ = glm::vec2(374, 470);
    glm::vec2 normal_top_ = glm::vec2(374, 600);
    glm::vec2 hard_top_ = glm::vec2(372, 750);
    glm::vec2 timer_top_ = glm::vec2(715, 610);

    glm::vec2 easy_bottom_ = glm::vec2(672, 568);
    glm::vec2 normal_bottom_ = glm::vec2(670, 710);
    glm::vec2 hard_bottom_ = glm::vec2(672, 850);
    glm::vec2 timer_bottom_ = glm::vec2(1008, 700);

    glm::vec2 end_position_ = glm::vec2(430, 450);
    AppState app_state_;

private:
    void DrawBoard();

    void DrawTimer();

    void DrawStartGameScreen();

    void DrawGameOverScreen();

    std::string GetTileImage(Tile::CurrentState current_state);

    void SetTimerPosition();
};

}  // namespace visualizer

}  // namespace minesweeper