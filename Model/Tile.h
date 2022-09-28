//
// Created by Pierre Forques on 20/09/2022.
//

#ifndef MINESWEEPER_TILE_H
#define MINESWEEPER_TILE_H


#include <vector>

class Tile {
private:

public:
    Tile(bool mine, int cooX, int cooY, int pixelX, int pixelY);
    int m_CooX;
    int m_CooY;
    int m_PixelX;
    int m_PixelY;
    bool m_Mine;
    int m_Neighbor;
    bool m_Discover;
    bool m_LosingMine;
    bool m_Flag;
    const static int SPRITE_SIZE = 16;

    bool isMLosingMine() const {
        return m_LosingMine;
    }

    void setMLosingMine(bool mLosingMine) {
        m_LosingMine = mLosingMine;
    }

    bool isMFlag() const {
        return m_Flag;
    }

    void setMFlag(bool mFlag) {
        m_Flag = mFlag;
    }


    bool isMine() {
        return m_Mine;
    }

    void setMine(bool mine) {
        m_Mine = mine;
    }

    int getNeighbor() {
        return m_Neighbor;
    }

    void setNeighbor(int neighbor) {
        m_Neighbor = neighbor;
    }

    bool isMDiscover() {
        return m_Discover;
    }

    void setMDiscover(bool mDiscover) {
        m_Discover = mDiscover;
    }

    int getMCooX() const {
        return m_CooX;
    }

    void setMCooX(int mCooX) {
        m_CooX = mCooX;
    }

    int getMCooY() const {
        return m_CooY;
    }

    void setMCooY(int mCooY) {
        m_CooY = mCooY;
    }

    int getMPixelX() const {
        return m_PixelX;
    }

    void setMPixelX(int mPixelX) {
        m_PixelX = mPixelX;
    }

    int getMPixelY() const {
        return m_PixelY;
    }

    void setMPixelY(int mPixelY) {
        m_PixelY = mPixelY;
    }
};


#endif //MINESWEEPER_TILE_H
