//
// Created by Pierre Forques on 20/09/2022.
//

#include <SFML/Window/Event.hpp>
#include <iostream>
#include <math.h>
#include <array>
#include "MainController.h"

void MainController::run(){
    sf::Clock clock;
    bool timerStarted = false;
    while (m_Window->isOpen())
    {
        sf::Event event;
        while (m_Window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                m_Window->close();

            if (event.type == sf::Event::MouseButtonPressed){
                if(isClickedOnButton(event.mouseButton.x, event.mouseButton.y)){
                    m_Scoreboard->setButtonClicked(true);
                }
            }

            if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if(!timerStarted){
                        clock.restart();
                        timerStarted = true;
                    }
                    leftClickUser({event.mouseButton.x, event.mouseButton.y});
                } else if (event.mouseButton.button == sf::Mouse::Right) {
                    rightClickUser({event.mouseButton.x, event.mouseButton.y});
                }

                if(isClickedOnButton(event.mouseButton.x, event.mouseButton.y)){
                    m_Scoreboard->setButtonClicked(false);
                    m_View->renderScoreBoard();
                    m_Window->display();

                    delete m_MapModel;
                    m_MapModel = new Map();
                    m_MapModel->initGrid();
                    m_View->setMMapModel(m_MapModel);
                    m_win = false;
                    m_lose = false;
                    timerStarted = false;
                }

            }
        }
        m_Window->clear(sf::Color(123, 45, 90));
        if(timerStarted) m_Scoreboard->setMTimer(clock.getElapsedTime());

        m_View->renderGrid();
        m_View->renderScoreBoard();

        if(!m_win && checkWiningCondition()){
            m_win = true;
            timerStarted = false;
            float playerTime = clock.getElapsedTime().asSeconds();
            std::cout << "Temps : " << playerTime << std::endl;
        }

        if(m_lose) {
            lose(); //Lose of memory
            timerStarted = false;
            std::cout << "Perdu" << std::endl;
            //m_Window->setSize(sf::Vector2<unsigned int>(1000, 1000));
            //TODO Si perdu
        } else if(m_win){
            std::cout << "Gagné" << std::endl;
            //TODO Si gagné
        }

        m_Window->display();
    }

}

int MainController::leftClickUser(sf::Vector2i position){
    if(position.x < m_MapModel->PLAYABLE_WINDOW_X && position.y < m_MapModel->PLAYABLE_WINDOW_Y){
        int cooX = floor(position.x/m_MapModel->getMTileSize());
        int cooY = floor(position.y/m_MapModel->getMTileSize());

        //auto &tile = m_MapModel->getMTiles()[cooY][cooX];
        int flagCounter = 0;

        //If the player hit mine
        if(m_MapModel->getMTiles()[cooY][cooX].isMine()){
            m_lose = true;
            m_MapModel->getMTiles()[cooY][cooX].setMLosingMine(true);
            return 0;
        }
        //If the player hit a ZERO tile
        else if(m_MapModel->getMTiles()[cooY][cooX].getNeighbor() == 0){
            auto temp = m_MapModel->checkNeighbors(cooX, cooY);
            recursiveTileClick(temp);
        }
        // if the player click with flag close
        else if(m_MapModel->getMTiles()[cooY][cooX].isMDiscover()){
            for(auto cooTile: m_MapModel->checkNeighbors(cooX, cooY)){
                if(m_MapModel->getMTiles()[cooTile[1]][cooTile[0]].isMFlag()){
                    ++flagCounter;
                }
            }
            if(m_MapModel->getMTiles()[cooY][cooX].getNeighbor() == flagCounter){
                auto temp = m_MapModel->checkNeighbors(cooX, cooY);
                recursiveTileClick(temp);
            }
        }

        m_MapModel->getMTiles()[cooY][cooX].setMDiscover(true);
        return 1;
    } else {
        /*if(position.x >= m_Scoreboard->getButtonX() && position.x <= m_Scoreboard->getButtonX()+(m_Scoreboard->SPRITE_BUTTON*m_Scoreboard->m_ScaleButtonPixel)){
            if(position.y >= m_Scoreboard->getButtonY() && position.y <= m_Scoreboard->getButtonY()+(m_Scoreboard->SPRITE_BUTTON*m_Scoreboard->m_ScaleButtonPixel)){
                m_Scoreboard->setButtonClicked(true);
            }
        }*/
        return 1;
    }

}

void MainController::rightClickUser(sf::Vector2i position){
    int cooX = floor(position.x/m_MapModel->getMTileSize());
    int cooY = floor(position.y/m_MapModel->getMTileSize());
    if(!m_MapModel->getMTiles()[cooY][cooX].isMDiscover()){
        if(m_MapModel->getMTiles()[cooY][cooX].isMFlag()){
            m_MapModel->getMTiles()[cooY][cooX].setMFlag(false);
        } else {
            m_MapModel->getMTiles()[cooY][cooX].setMFlag(true);
        }
    }
}

void MainController::recursiveTileClick(std::vector<std::array<int, 2>> &tilesToCheck){
    for(auto &tile: tilesToCheck){
        if(!m_MapModel->getMTiles()[tile[1]][tile[0]].isMDiscover()){
            if(!m_MapModel->getMTiles()[tile[1]][tile[0]].isMine()){
                m_MapModel->getMTiles()[tile[1]][tile[0]].setMDiscover(true);

                m_MapModel->getMTiles()[tile[1]][tile[0]].setMFlag(false);
                auto tileOfTile = m_MapModel->checkNeighbors(tile[0], tile[1]);

                if(m_MapModel->getMTiles()[tile[1]][tile[0]].getNeighbor() == 0){
                    recursiveTileClick(tileOfTile);
                }
            } else {
                // && !m_MapModel->getMTiles()[tile[1]][tile[0]].isMFlag()
                if(!m_MapModel->getMTiles()[tile[1]][tile[0]].isMFlag() == true){
                   // m_MapModel->getMTiles()[tile[1]][tile[0]].setMDiscover(true);
                    m_lose = true;
                    m_MapModel->getMTiles()[tile[1]][tile[0]].setMLosingMine(true);

                }
                /*std::cout << "UWU" << std::endl;

                m_lose = true;
                m_MapModel->getMTiles()[tile[1]][tile[0]].setMLosingMine(true);
                break;*/
            }

        }
    }
}

bool MainController::checkWiningCondition(){
    for(auto &tiles : m_MapModel->getMTiles()){
        for(auto &tile : tiles){
            if(!tile.isMDiscover() && !tile.isMine()) return 0;
        }
    }
    std::cout << "gagné" << std::endl;
    return 1;
}

void MainController::lose(){
    for(auto &tiles : m_MapModel->getMTiles()){
        for(auto &tile : tiles){
            tile.setMDiscover(true);
            tile.setMFlag(false);
        }
    }
}

bool MainController::isClickedOnButton(int x, int y){
    if(x >= m_Scoreboard->getButtonX() && x <= m_Scoreboard->getButtonX()+(m_Scoreboard->SPRITE_BUTTON*m_Scoreboard->m_ScaleButtonPixel)){
        if(y >= m_Scoreboard->getButtonY() && y <= m_Scoreboard->getButtonY()+(m_Scoreboard->SPRITE_BUTTON*m_Scoreboard->m_ScaleButtonPixel)){
            return true;
        }
    }
    return false;
}

MainController::MainController(View *view, Map *mapModel, Scoreboard *scoreboard){
    m_View = view;
    m_MapModel = mapModel;
    m_Scoreboard = scoreboard;
    m_Window = view->m_Window;
    m_win = false;
    m_lose = false;
}

