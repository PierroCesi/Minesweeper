//
// Created by Pierre Forques on 20/09/2022.
//

#include "Tile.h"

Tile::Tile(bool mine, int cooX, int cooY, int pixelX, int pixelY){
    m_CooX = cooX;
    m_CooY = cooY;
    m_PixelX = pixelX;
    m_PixelY = pixelY;
    m_Mine = mine;
    m_Discover = false;
    m_LosingMine = false;
    m_Flag = false;
}














