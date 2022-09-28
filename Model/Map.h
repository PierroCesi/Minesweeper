//
// Created by Pierre Forques on 19/09/2022.
//

#ifndef MINESWEEPER_MAP_H
#define MINESWEEPER_MAP_H


#include "Tile.h"

class Map {
private:
    const int MINE_AMOUNT = (20*(BOARD_X*BOARD_Y)/100);
    std::vector<std::vector<Tile>> m_Tiles;

public:
    const int PLAYABLE_WINDOW_X = BOARD_X * 80;
    const int PLAYABLE_WINDOW_Y = BOARD_Y * 80;
    static const int BOARD_X = 16;
    static const int BOARD_Y = 8;
    int m_TileSize;

    Map();
    void initGrid();
    int checkMineNeighbors(int x, int y);
    std::vector<std::array<int, 2>> checkTileNeighbors(int x, int y);
    std::vector<std::array<int, 2>> checkNeighbors(int x, int y);

    std::vector<std::vector<Tile>> &getMTiles() {
        return m_Tiles;
    }

    void setMTiles(std::vector<std::vector<Tile>> &mTiles) {
        m_Tiles = mTiles;
    }

    int getMTileSize() {
        return m_TileSize;
    }

    void setMTileSize(int mTileSize) {
        m_TileSize = mTileSize;
    }
};


#endif //MINESWEEPER_MAP_H
