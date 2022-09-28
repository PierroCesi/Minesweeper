//
// Created by Pierre Forques on 19/09/2022.
//

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <iostream>
#include "View.h"
#include "../Model/Scoreboard.h"

View::View(Map *mapModel, Scoreboard *scoreboard){
    m_MapModel = mapModel;
    m_Scoreboard = scoreboard;

    m_Window = new sf::RenderWindow(sf::VideoMode(mapModel->PLAYABLE_WINDOW_X + Scoreboard::SCOREBOARD, mapModel->PLAYABLE_WINDOW_Y), "minesweeper");
    if (!texture.loadFromFile("../ressources/sprite.png"))
    {
        //TODO : handle error
    }
    m_TileSprite.setTexture(texture);
    m_TileSprite.setTextureRect(sf::IntRect(0, 0, Tile::SPRITE_SIZE, Tile::SPRITE_SIZE));
    m_TileSprite.setScale(sf::Vector2f(mapModel->m_TileSize/Tile::SPRITE_SIZE, mapModel->m_TileSize/Tile::SPRITE_SIZE));

    m_TimerSprite.setTexture(texture);
    m_TimerSprite.setTextureRect(sf::IntRect(128, 0, Scoreboard::SPRITE_TIMER_X, Scoreboard::SPRITE_TIMER_Y));
    m_TimerSprite.setScale(sf::Vector2f(m_Scoreboard->getMScaleTimerPixel(), m_Scoreboard->getMScaleTimerPixel() * (Scoreboard::SPRITE_TIMER_Y / Scoreboard::SPRITE_TIMER_X)));

    m_ButtonSprite.setTexture(texture);
    m_ButtonSprite.setTextureRect(sf::IntRect(232, 24, Scoreboard::SPRITE_BUTTON, Scoreboard::SPRITE_BUTTON));
    m_ButtonSprite.setScale(sf::Vector2f(m_Scoreboard->m_ScaleButtonPixel, m_Scoreboard->m_ScaleButtonPixel));
}

void View::renderGrid() {
    sf::Text text;
    sf::Font font;
    font.loadFromFile("../ressources/arial.ttf");
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);

    for(auto &tile1 : m_MapModel->getMTiles())
    {
        for(auto &tile2: tile1){
            m_TileSprite.setTextureRect(sf::IntRect(0, 0, Tile::SPRITE_SIZE, Tile::SPRITE_SIZE));

            if(tile2.isMDiscover()){
                if(tile2.getNeighbor() == 0){
                    text.setString(std::to_string(tile2.getNeighbor()));
                    m_TileSprite.setTextureRect(sf::IntRect(0, 656, Tile::SPRITE_SIZE, Tile::SPRITE_SIZE));
                //TODO : refactor ez
                } else if(tile2.getNeighbor() == 1){
                    m_TileSprite.setTextureRect(sf::IntRect(0, 656 - Tile::SPRITE_SIZE, Tile::SPRITE_SIZE, Tile::SPRITE_SIZE));
                } else if(tile2.getNeighbor() == 2){
                    m_TileSprite.setTextureRect(sf::IntRect(0, 656 - Tile::SPRITE_SIZE * 2, Tile::SPRITE_SIZE, Tile::SPRITE_SIZE));
                } else if(tile2.getNeighbor() == 3){
                    m_TileSprite.setTextureRect(sf::IntRect(0, 656 - Tile::SPRITE_SIZE * 3, Tile::SPRITE_SIZE, Tile::SPRITE_SIZE));
                } else if(tile2.getNeighbor() == 4){
                    m_TileSprite.setTextureRect(sf::IntRect(0, 656 - Tile::SPRITE_SIZE * 4, Tile::SPRITE_SIZE, Tile::SPRITE_SIZE));
                } else if(tile2.getNeighbor() == 5){
                    m_TileSprite.setTextureRect(sf::IntRect(0, 656 - Tile::SPRITE_SIZE * 5, Tile::SPRITE_SIZE, Tile::SPRITE_SIZE));
                } else if(tile2.getNeighbor() == 6){
                    m_TileSprite.setTextureRect(sf::IntRect(0, 656 - Tile::SPRITE_SIZE * 6, Tile::SPRITE_SIZE, Tile::SPRITE_SIZE));
                } else if(tile2.getNeighbor() == 7){
                    m_TileSprite.setTextureRect(sf::IntRect(0, 656 - Tile::SPRITE_SIZE * 7, Tile::SPRITE_SIZE, Tile::SPRITE_SIZE));
                } else if(tile2.getNeighbor() == 8){
                    m_TileSprite.setTextureRect(sf::IntRect(0, 656 - Tile::SPRITE_SIZE * 8, Tile::SPRITE_SIZE, Tile::SPRITE_SIZE));
                }
            }
            if(tile2.isMFlag()){
                m_TileSprite.setTextureRect(sf::IntRect(128, 624, Tile::SPRITE_SIZE, Tile::SPRITE_SIZE));
            }
            if(tile2.isMine()){
                if(tile2.isMDiscover()){
                    m_TileSprite.setTextureRect(sf::IntRect(128, 656, Tile::SPRITE_SIZE, Tile::SPRITE_SIZE));
                }
                if(tile2.isMLosingMine()){
                    m_TileSprite.setTextureRect(sf::IntRect(128, 640, Tile::SPRITE_SIZE, Tile::SPRITE_SIZE));
                }
            }

            if(tile2.isMine()){
                text.setString("mine");
            } else {
                text.setString(std::to_string(tile2.getNeighbor()));
            }

            text.setPosition(sf::Vector2f(tile2.m_PixelX, tile2.m_PixelY));
            m_TileSprite.setPosition(sf::Vector2f(tile2.m_PixelX, tile2.m_PixelY));

            m_Window->draw(m_TileSprite);
            m_Window->draw(text);
        }
    }
}

void View::renderScoreBoard() {
    sf::RectangleShape rectangle(sf::Vector2f(0, 0));
    rectangle.setSize(sf::Vector2f(Scoreboard::SCOREBOARD, m_MapModel->PLAYABLE_WINDOW_Y));
    rectangle.setOutlineThickness(THICKNESS);
    rectangle.setOutlineColor(sf::Color(10, 10, 10));
    rectangle.setPosition(sf::Vector2f(m_MapModel->PLAYABLE_WINDOW_X, 0));
    rectangle.setFillColor(sf::Color(198, 198, 198));

    int intTime = m_Scoreboard->getMTimer().asSeconds();

    std::array<int, 3> digits = m_Scoreboard->getThreeDigit(intTime);
    for(int i=0; i<3; i++){
        if(i == 0){
            m_ButtonSprite.setTextureRect(sf::IntRect(128, 253 - digits[2] * Scoreboard::SPRITE_TIMER_Y, Scoreboard::SPRITE_TIMER_X, Scoreboard::SPRITE_TIMER_Y));
        } else if (i == 1){
            m_ButtonSprite.setTextureRect(sf::IntRect(128, 253 - digits[1] * Scoreboard::SPRITE_TIMER_Y, Scoreboard::SPRITE_TIMER_X, Scoreboard::SPRITE_TIMER_Y));
        } else if (i == 2){
            m_ButtonSprite.setTextureRect(sf::IntRect(128, 253 - digits[0] * Scoreboard::SPRITE_TIMER_Y, Scoreboard::SPRITE_TIMER_X, Scoreboard::SPRITE_TIMER_Y));
        }
        m_ButtonSprite.setPosition(sf::Vector2f(m_MapModel->PLAYABLE_WINDOW_X + i * Scoreboard::SCOREBOARD / 3, 0));
        m_Window->draw(m_ButtonSprite);
    }

    //Button
    if(m_Scoreboard->isButtonClicked()){
        m_ButtonSprite.setTextureRect(sf::IntRect(232, 0, Scoreboard::SPRITE_BUTTON, Scoreboard::SPRITE_BUTTON));
    } else {
        m_ButtonSprite.setTextureRect(sf::IntRect(232, 24, Scoreboard::SPRITE_BUTTON, Scoreboard::SPRITE_BUTTON));
    }
    m_ButtonSprite.setPosition(sf::Vector2f(m_Scoreboard->getButtonX(), m_Scoreboard->getButtonY()));

    //m_Window->draw(m_ButtonSprite);
}

Scoreboard *View::getMScoreboard() const {
    return m_Scoreboard;
}

void View::setMScoreboard(Scoreboard *mScoreboard) {
    m_Scoreboard = mScoreboard;
}

Map *View::getMMapModel() const {
    return m_MapModel;
}

void View::setMMapModel(Map *mMapModel) {
    m_MapModel = mMapModel;
}

