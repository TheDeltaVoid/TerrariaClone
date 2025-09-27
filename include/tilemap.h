#ifndef TILEMAP_H
#define TILEMAP_H

#include <vector>
#include <array>
#include <string>
#include "raylib.h"
#include <iostream>
#include <algorithm>

#include "entities.h"

struct IntRectangle {
    int row;
    int col;
    int width;
    int height;

    std::vector<std::array<int, 2>> includet_tiles;
    
    IntRectangle(int r, int c, int w, int h, std::vector<std::array<int, 2>> it) : row(r), col(c), width(w), height(h), includet_tiles(it) {}
};

struct Tile {
    int type;
    int collider_index;
};

class TileCollider : public PhysicsEntity {
    private:
    std::vector<std::array<int, 2>> includet_tiles;

    public:
    TileCollider(Vector2 pos, Vector2 size);

    void update() override;
    void debugRender() override;

    void setTiles(std::vector<std::array<int, 2>> includet_tiles);
};

class Tilemap {
    private:
    int tile_size = 1;
    int world_size[2];

    std::vector<std::vector<Tile>> world;

    std::vector<TileCollider*> entities;

    void generatePhyscisEntities();

    public:
    Tilemap();

    void loadFromFile(std::string path);
    std::vector<TileCollider*> getEntities();
    std::vector<TileCollider*> getEntitiesRange(Rectangle rect);

    void debugRender();
};

#endif