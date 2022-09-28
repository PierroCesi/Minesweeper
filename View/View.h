//
// Created by Pierre Forques on 19/09/2022.
//

#ifndef MINESWEEPER_VIEW_H
#define MINESWEEPER_VIEW_H


#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "../Model/Map.h"
#include "../Model/Scoreboard.h"

class View {
private:
    static const int THICKNESS = 5;

    Scoreboard *m_Scoreboard;
    Map *m_MapModel;

    sf::Texture texture;
    sf::Sprite m_TileSprite;
    sf::Sprite m_TimerSprite;
    sf::Sprite m_ButtonSprite;

public:

    sf::RenderWindow *m_Window;
    void renderGrid();
    void renderScoreBoard();
    View(Map *mapModel, Scoreboard *scoreboard);

    Scoreboard *getMScoreboard() const;
    void setMScoreboard(Scoreboard *mScoreboard);
    Map *getMMapModel() const;
    void setMMapModel(Map *mMapModel);

};


#endif //MINESWEEPER_VIEW_H
