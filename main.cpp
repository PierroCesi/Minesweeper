#include <iostream>
#include <SFML/Window/Event.hpp>
#include "View/View.h"
#include "Model/Map.h"
#include "Controller/MainController.h"
#include "Model/Scoreboard.h"

int main() {
    Map *mapModel = new Map();
    mapModel->initGrid();
    Scoreboard *scoreboard = new Scoreboard(mapModel->PLAYABLE_WINDOW_X, mapModel->PLAYABLE_WINDOW_Y);

    View *view = new View(mapModel, scoreboard);

    MainController *motomoto = new MainController(view, mapModel, scoreboard);
    motomoto->run();

    return 0;
}
