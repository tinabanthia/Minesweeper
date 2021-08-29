#include <core/board.h>
#include "../../include/visualizer/minesweeper_app.h"
#include <cinder/app/Window.h>
#include <cinder/Font.h>

namespace minesweeper{
minesweeper::visualizer::MinesweeperApp::MinesweeperApp() {
    app_state_ = AppState::kStartGame;
    SetTimerPosition();
}


void minesweeper::visualizer::MinesweeperApp::draw() {
    cinder::app::setFullScreen();
    AppBase::draw();
    cinder::gl::clear();

    if (game_engine_.IsWinner()) {
        app_state_ = kGameOverWin;
    }

    switch (app_state_) {
        case kPlayingTimer :
            DrawBoard();
            DrawTimer();
            break;

        case kGameOverLose :
            DrawGameOverScreen();
            break;

        case kPlayingGems:
            DrawBoard();
            break;

        case kStartGame:
            DrawStartGameScreen();
            break;

        case kGameOverWin:
            DrawGameOverScreen();
            break;
    }
}

void minesweeper::visualizer::MinesweeperApp::DrawTimer() {
    cinder::gl::draw(cinder::gl::Texture2d::create(loadImage
                                                           (loadAsset("label.png"))),
                     timer_label_position_);
    cinder::gl::drawString(std::to_string(timer_.getSeconds()), timer_position_,
                           ci::Color::black(),timer_font_);
}

void minesweeper::visualizer::MinesweeperApp::DrawBoard() {
    for (size_t row = 0; row < game_engine_.board_.height_; row++) {
        for (size_t column = 0; column < game_engine_.board_.width_; column++) {

            // Find position of each Tile
            cinder::Rectf rect(board_translation_.x + (column * tile_size_multiplier_), board_translation_.y +
                                                                                      (row * tile_size_multiplier_),
                               board_translation_.x + ((column + 1) * tile_size_multiplier_), board_translation_.y +
                                                                                            ((row + 1) * tile_size_multiplier_));

            Tile::CurrentState curr_tile_state = game_engine_.board_.all_tiles_
            [std::make_pair(row, column)].current_state_;
            std::string image = GetTileImage(curr_tile_state);

            cinder::gl::draw(cinder::gl::Texture2d::create(loadImage
                                                                   (loadAsset(image))), rect);
        }
    }
}

void minesweeper::visualizer::MinesweeperApp::DrawGameOverScreen() {
    cinder::gl::draw(cinder::gl::Texture2d::create(
            loadImage(loadAsset("startGameLogo.png"))), start_game_position_);
    std::string image = "endGameLose.png";

    if (app_state_ == kGameOverWin) {
        image = "endGameWin.jpeg";
    }
    cinder::gl::draw(cinder::gl::Texture2d::create(
            loadImage(loadAsset(image))), end_position_);
}

void minesweeper::visualizer::MinesweeperApp::DrawStartGameScreen() {
    cinder::gl::draw(cinder::gl::Texture2d::create(
            loadImage(loadAsset("startGameLogo.png"))), start_game_position_);

    cinder::gl::draw(cinder::gl::Texture2d::create(
            loadImage(loadAsset("normalButton.png"))), normal_button_position_);
    cinder::gl::drawString("NORMAL", normal_label_position_,
                           ci::Color::black(),start_font_);

    cinder::gl::draw(cinder::gl::Texture2d::create(
            loadImage(loadAsset("easyButton.png"))), easy_button_position_);
    cinder::gl::drawString("EASY", easy_label_position_,
                           ci::Color::black(),start_font_);

    cinder::gl::draw(cinder::gl::Texture2d::create(
            loadImage(loadAsset("hardButton.png"))), hard_button_position_);
    cinder::gl::drawString("HARD", hard_label_position_,
                           ci::Color::black(),start_font_);

    cinder::gl::draw(cinder::gl::Texture2d::create(
            loadImage(loadAsset("timerButton.png"))), timer_button_position_);
    cinder::gl::drawString("TIMER", start_timer_label_position_,
                           ci::Color::black(),start_font_);

}

void minesweeper::visualizer::MinesweeperApp::mouseDown(ci::app::MouseEvent event) {
    AppBase::mouseDown(event);
    if (app_state_ == kPlayingTimer || app_state_ == kPlayingGems) {
        if (event.isLeft()) {
            game_engine_.UncoverTile(glm::vec2((double)
                                                (event.getPos().y - board_translation_.y) / tile_size_multiplier_,
                                               (double)
                                               (event.getPos().x - board_translation_.x) / tile_size_multiplier_));
        }
        if (event.isRight()) {
            game_engine_.FlagTile(glm::vec2((double)
                                            (event.getPos().y - board_translation_.y) / tile_size_multiplier_,
                                            (double)
                                            (event.getPos().x - board_translation_.x) / tile_size_multiplier_));
        }
    } else if (app_state_ == kStartGame) {

        if (event.getPos().x >= easy_top_.x &&
            event.getPos().y >= easy_top_.y &&
            event.getPos().x <= easy_bottom_.x &&
            event.getPos().y <= easy_bottom_.y) {

            app_state_ = kPlayingGems;
            game_engine_= GameEngine(10, 10, 25);
            tile_size_multiplier_ = 75;
            board_translation_ = vec2(350, 75);

        } else if (event.getPos().x >= normal_top_.x &&
                   event.getPos().y >= normal_top_.y &&
                   event.getPos().x <= normal_bottom_.x &&
                   event.getPos().y <= normal_bottom_.y) {

            app_state_ = kPlayingGems;
            game_engine_= GameEngine(15, 15, 30);
            tile_size_multiplier_ = 50;
            board_translation_ = vec2(350, 75);

        } else if (event.getPos().x >= hard_top_.x &&
                   event.getPos().y >= hard_top_.y &&
                   event.getPos().x <= hard_bottom_.x &&
                   event.getPos().y <= hard_bottom_.y) {

            app_state_ = kPlayingGems;
            game_engine_.board_ = Board(18, 18, 100);
            board_translation_ = vec2(250, 0);

        } else if (event.getPos().x >= timer_top_.x &&
                   event.getPos().y >= timer_top_.y &&
                   event.getPos().x <= timer_bottom_.x &&
                   event.getPos().y <= timer_bottom_.y) {

            app_state_ = kPlayingTimer;
            timer_ = cinder::Timer();
            timer_.start();

            tile_size_multiplier_ = 62;
            game_engine_.board_ = Board(10, 10, 25);
        }
    }
}

std::string minesweeper::visualizer::MinesweeperApp::GetTileImage(Tile::CurrentState current_state) {
    std::string image;

    switch(current_state) {
        case Tile::kExposedMine :
            image = "bombTile.png";
            timer_.stop();
            app_state_ = kGameOverLose;
            break;

        case Tile::kEmptyTile :
            image = "emptyTile.png";
            break;

        case Tile::kFlagged :
            image = "flaggedTile.png";
            break;

        case Tile::kOne :
            image = "oneTile.png";
            break;

        case Tile::kTwo :
            image = "twoTile.png";
            break;

        case Tile::kThree :
            image = "threeTile.png";
            break;

        case Tile::kFour :
            image = "fourTile.png";
            break;

        case Tile::kFive :
            image = "fiveTile.png";
            break;

        case Tile::kSix :
            image = "sixTile.png";
            break;

        case Tile::kSeven :
            image = "sevenTile.png";
            break;

        case Tile::kEight :
            image = "eightTile.png";
            break;

        default :
            image = "unexposedTile.png";

    }
    return image;
}

void minesweeper::visualizer::MinesweeperApp::SetTimerPosition() {
    timer_position_ = glm::vec2(cinder::app::getWindowWidth() + board_translation_.y + (board_translation_.y / 2)
                                + board_translation_.y, board_translation_.y + board_translation_.y);
}

} // namespace minesweeper