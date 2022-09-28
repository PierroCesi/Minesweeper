//
// Created by Pierre Forques on 19/09/2022.
//

#include <vector>
#include <stdlib.h>
#include <time.h>
#include <array>
#include "Map.h"
#include "Tile.h"

Map::Map(){
    srand (time(NULL));
};

void Map::initGrid(){
    m_TileSize = PLAYABLE_WINDOW_X / BOARD_X;

    std::vector<Tile> tilesX;

    for(int y=0; y<BOARD_Y; y++){//y
        for(int i=0; i<BOARD_X; i++){//x
            tilesX.push_back(Tile(false, i, y, i * m_TileSize, y * m_TileSize));
        }
        this->m_Tiles.push_back(tilesX);
        tilesX.clear();
    }

    //Set m_Mine
    for(int j=0; j<MINE_AMOUNT; j++){
        m_Tiles[rand() % BOARD_Y][rand() % BOARD_X].setMine(true);
    }

    for(int y=0; y<BOARD_Y; y++){//y
        for(int i=0; i<BOARD_X; i++){//x
            m_Tiles[y][i].setNeighbor(checkMineNeighbors(i, y));
        }
    }

}

int Map::checkMineNeighbors(int x, int y){
    int count = 0;

    std::vector<int> checkX = {-1, 0, +1, -1, +1, -1, 0, +1};
    std::vector<int> checkY = {-1, -1, -1, 0, 0, +1, +1, +1};

    for(int i=0; i<checkX.size(); ++i){
        if(x == 0 && checkX[i] == -1){
            continue;
        }
        if(x == BOARD_X-1 && checkX[i] == +1){
            continue;
        }

        if(y == 0 && checkY[i] == -1){
            continue;
        }
        if(y == BOARD_Y-1 && checkY[i] == +1){
            continue;
        }

        if(m_Tiles[y+checkY[i]][x+checkX[i]].isMine()){
            ++count;
        }
    }
    return count;
}

std::vector<std::array<int, 2>> Map::checkTileNeighbors(int x, int y){

    std::vector<int> checkX = {-1, 0, +1, -1, +1, -1, 0, +1};
    std::vector<int> checkY = {-1, -1, -1, 0, 0, +1, +1, +1};

    std::vector<std::array<int, 2>> cooTiles;
    for(int i=0; i<checkX.size(); ++i){
        if(x == 0 || x == BOARD_X-1){
            checkX[i] = 0;
        }
        if(y == 0 || y == BOARD_Y-1){
            checkY[i] = 0;
        }

        if(m_Tiles[y+checkY[i]][x+checkX[i]].getNeighbor() == 0){
            cooTiles.push_back({m_Tiles[y+checkY[i]][x+checkX[i]].getMCooX(), m_Tiles[y+checkY[i]][x+checkX[i]].getMCooY()});
        }
    }
    return cooTiles;
}

std::vector<std::array<int, 2>> Map::checkNeighbors(int x, int y){

    std::vector<int> checkX = {-1, 0, +1, -1, +1, -1, 0, +1};
    std::vector<int> checkY = {-1, -1, -1, 0, 0, +1, +1, +1};

    std::vector<std::array<int, 2>> cooTiles;
    for(int i=0; i<checkX.size(); ++i){
        if(x == 0 && checkX[i] == -1){
            continue;
        }
        if(x == BOARD_X-1 && checkX[i] == +1){
            continue;
        }
        if(y == 0 && checkY[i] == -1){
            continue;
        }
        if(y == BOARD_Y-1 && checkY[i] == +1){
            continue;
        }
        cooTiles.push_back({m_Tiles[y+checkY[i]][x+checkX[i]].getMCooX(), m_Tiles[y+checkY[i]][x+checkX[i]].getMCooY()});
    }
    return cooTiles;
}





