//
// Created by Pierre Forques on 25/09/2022.
//

#include <SFML/System/Vector2.hpp>
#include "Scoreboard.h"

std::array<int, 3> Scoreboard::getThreeDigit(int number){
    std::array<int, 3> digits = {0, 0, 0};
    int i = 0;
    if(number == 0){
        digits = {0, 0, 0};
    } else {
        while(number > 0 && i < 3){
            int digit = number%10;
            digits[i] = digit;
            number/= 10;
            ++i;
        }
    }
    return digits;
}

Scoreboard::Scoreboard(int playableWindowX, int playableWindowY){
    m_ButtonClicked = false;
    m_ScaleButtonPixel = 5;
    m_ScaleTimerPixel = 7;
    buttonX = playableWindowX+((SCOREBOARD/2)-(SPRITE_BUTTON*m_ScaleButtonPixel)/2);
    buttonY = playableWindowY-playableWindowY/1.2;
    buttonY = SPRITE_TIMER_Y*m_ScaleTimerPixel;
}