//
// Created by Pierre Forques on 20/09/2022.
//

#ifndef MINESWEEPER_MAINCONTROLLER_H
#define MINESWEEPER_MAINCONTROLLER_H


#include "../View/View.h"

class MainController {
private:
    View *m_View;
    Map *m_MapModel;
    Scoreboard *m_Scoreboard;
    sf::RenderWindow *m_Window;

    bool m_win;
    bool m_lose;
public:
    MainController(View *view, Map *mapModel, Scoreboard *scoreboard);
    MainController();

    int leftClickUser(sf::Vector2i position);
    void rightClickUser(sf::Vector2i position);

    void recursiveTileClick(std::vector<std::array<int, 2>> &tilesToCheck);
    bool checkWiningCondition();
    bool isClickedOnButton(int x, int y);
    void lose();

    void run();
};


#endif //MINESWEEPER_MAINCONTROLLER_H
