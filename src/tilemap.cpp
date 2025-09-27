#include "tilemap.h"

TileCollider::TileCollider(Vector2 pos, Vector2 size) {
    setPos(pos);
    setSize(size);

    setMass(1.0f);
    setDamp(1.0f);
}

void TileCollider::debugRender() {
    DrawRectangleV(getPos(), getSize(), BLUE);
    //DrawRectangleLines((int)getPos().x, (int)getPos().y, (int)getSize().x, (int)getSize().y, WHITE);
};

void TileCollider::update() {};

void TileCollider::setTiles(std::vector<std::array<int, 2>> includet_tiles) { this->includet_tiles = includet_tiles; };

Tilemap::Tilemap() {};

std::vector<TileCollider*> Tilemap::getEntitiesRange(Rectangle rect) {
    std::vector<TileCollider*> entities;

    int tile_start_x = (int)(rect.x / tile_size);
    int tile_start_y = (int)(rect.y / tile_size);

    int tile_end_x = (int)((rect.x + rect.width + tile_size) / tile_size);
    int tile_end_y = (int)((rect.y + rect.height + tile_size) / tile_size);

    for (int x = tile_start_x; x < tile_end_x; x++) {
        for (int y = tile_start_y; y < tile_end_y; y++) {
            if ((x < world_size[0] && x >= 0) && (y < world_size[1] && y >= 0)) {
                //printf("| %d, %d, %d, %d, %d |", x, y, (int)world.size(), (int)world[y].size(), (int)this->entities.size());
                TileCollider *test = this->entities[world[y][x].collider_index];

                entities.push_back(test);
            } else {
                continue;
            }
        }
    }

    return entities;
}

std::vector<IntRectangle> greedyIntRectangleMerging(std::vector<std::vector<Tile>>& world) {
    if (world.empty() || world[0].empty()) {
        return {};
    }
    
    int rows = world.size();
    int cols = world[0].size();
    std::vector<std::vector<Tile>> processedGrid = world; // Create a copy to mark processed cells
    std::vector<IntRectangle> rectangles;
    
    int collider_index = 0;
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            // Only consider cells that are solid (not 0) and not yet processed
            if (processedGrid[r][c].type != 0) {
                // Find maximum width starting from this cell
                int maxWidth = 0;
                while (c + maxWidth < cols && processedGrid[r][c + maxWidth].type != 0) {
                    maxWidth++;
                }
                
                // Find maximum height for the found width
                int maxHeight = 0;
                bool canExtend = true;
                
                while (canExtend && r + maxHeight < rows) {
                    for (int w = 0; w < maxWidth; w++) {
                        if (c + w < cols) {
                            //printf("| %d, %d, %d, %d |", c + w, r + maxHeight, cols, rows);
                            if (processedGrid[r + maxHeight][c + w].type == 0) {
                                canExtend = false;
                                break;
                            }
                        }
                    }
                    if (canExtend) {
                        maxHeight++;
                    }

                }
                
                // Mark all cells in this rectangle as processed (set to 0)
                std::vector<std::array<int, 2>> tiles;
                for (int rr = r; rr < r + maxHeight; rr++) {
                    for (int cc = c; cc < c + maxWidth; cc++) {
                        processedGrid[rr][cc].type = 0;
                        tiles.push_back({rr, cc});
                        world[rr][cc].collider_index = collider_index;
                    }
                }

                // Create the rectangle
                rectangles.emplace_back(r, c, maxWidth, maxHeight, tiles);
                collider_index++;
                
                // Skip the processed cells in the inner loop
                c += maxWidth - 1;

            }
        }
    }
    
    return rectangles;
}

void Tilemap::generatePhyscisEntities() {
    std::vector<IntRectangle> rects = greedyIntRectangleMerging(world);

    for (IntRectangle rect : rects) {
        Vector2 pos = {(float)(rect.col * tile_size), (float)(rect.row * tile_size)};
        Vector2 size = {(float)(rect.width * tile_size), (float)(rect.height * tile_size)};

        int index = (int)entities.size();

        entities.push_back(new TileCollider(pos, size));
        entities.back()->setTiles(rect.includet_tiles);
    }

    printf("size1: %d ", (int)entities.size());
}

void Tilemap::loadFromFile(std::string path) {
    std::string text = LoadFileText(path.c_str());

    int max_x = 0;
    int x_counter = 0;

    for (int i = 0; i < text.size(); i++) {
        if (text[i] == '\n') {
            world.push_back(std::vector<Tile>());
            x_counter = 0;
        } else {
            if (world.size() == 0) {
                world.push_back(std::vector<Tile>());
            }

            x_counter ++;
            if (x_counter > max_x) { max_x = x_counter; };

            world.back().push_back(Tile({text[i] - '0'}));
        }
    }

    world.pop_back();

    world_size[0] = max_x;
    world_size[1] = (int)world.size();

    generatePhyscisEntities();

    //printf("size2: %d ", (int)entities.size());
}

std::vector<TileCollider*> Tilemap::getEntities() { return entities; };

void Tilemap::debugRender() {
    for (int i = 0; i < entities.size(); i++) {
        entities.at(i)->debugRender();
    }
}
