import random

width = 61  # Muss ungerade sein für ein sauberes Labyrinth
height = 35  # Muss ungerade sein

# Initialisiere das Raster: 1 = Wand, 0 = Weg
tilemap = [[1 for _ in range(width)] for _ in range(height)]

def carve_maze(x, y):
    directions = [(2, 0), (-2, 0), (0, 2), (0, -2)]
    random.shuffle(directions)
    for dx, dy in directions:
        nx, ny = x + dx, y + dy
        if 0 < nx < width and 0 < ny < height and tilemap[ny][nx] == 1:
            # Wand zwischen den Zellen entfernen
            tilemap[y + dy // 2][x + dx // 2] = 0
            tilemap[ny][nx] = 0
            carve_maze(nx, ny)

# Startpunkt (ungerade Koordinaten)
start_x, start_y = 1, 1
tilemap[start_y][start_x] = 0
carve_maze(start_x, start_y)

# Schreibe Labyrinth in Datei
with open(r"C:\Users\Simon\Desktop\coding\CPP\Terraria Clone\res\world", "w") as f:
    for row in tilemap:
        f.write("".join(str(tile) for tile in row) + "\n")
