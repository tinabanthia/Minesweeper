#include <visualizer/minesweeper_app.h>

using minesweeper::visualizer::MinesweeperApp;

void prepareSettings(MinesweeperApp::Settings* settings) {
    settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(MinesweeperApp, ci::app::RendererGl, prepareSettings);