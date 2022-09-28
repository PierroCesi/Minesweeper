//
// Created by Pierre Forques on 25/09/2022.
//

#ifndef MINESWEEPER_SCOREBOARD_H
#define MINESWEEPER_SCOREBOARD_H

#include <SFML/System/Time.hpp>
#include <iostream>
#include <array>
#include "Map.h"

class Scoreboard {
private:
public:
    static const int SCOREBOARD = 200;
    static const int SPRITE_TIMER_X = 13;
    static const int SPRITE_TIMER_Y = 23;

    static const int SPRITE_BUTTON = 24;
    int buttonX;
    int buttonY;
    int m_buttonLvl1;
    int m_buttonLvl2;
    int m_buttonLvl3;
    int m_ScaleTimerPixel;
    int m_ScaleButtonPixel;

    sf::Time m_Timer;
    bool m_ButtonClicked;
    Scoreboard(int playableWindowX, int playableWindowY);
    std::array<int, 3> getThreeDigit(int number);

    const sf::Time &getMTimer() const {
        return m_Timer;
    }

    void setMTimer(const sf::Time &mTimer) {
        m_Timer = mTimer;
    }

    int getButtonX() const {
        return buttonX;
    }

    void setButtonX(int buttonX) {
        buttonX = buttonX;
    }

    int getButtonY() const {
        return buttonY;
    }

    void setButtonY(int buttonY) {
        buttonY = buttonY;
    }

    bool isButtonClicked() const {
        return m_ButtonClicked;
    }

    void setButtonClicked(bool buttonClicked) {
        m_ButtonClicked = buttonClicked;
    }

    int getMScaleTimerPixel() const {
        return m_ScaleTimerPixel;
    }

    void setMScaleTimerPixel(int mScaleTimerPixel) {
        m_ScaleTimerPixel = mScaleTimerPixel;
    }


};


#endif //MINESWEEPER_SCOREBOARD_H
