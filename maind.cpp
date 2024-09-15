#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>

using namespace std;

// Размеры поля
const int ROWS = 25;
const int COLS = 40;
const int DELAY = 250; // Задержка в миллисекундах

// Функция для очистки экрана консоли 
void clearScreen() {
    cout << "\033[2J\033[H";
    cout.flush();
}

// Функция для вывода состояния поля на консоль
void printGrid(const vector<vector<bool>>& grid) {
    clearScreen();
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (grid[i][j]) {
                cout << "0"; // Живая клетка
            }
            else {
                cout << " "; // Мёртвая клетка
            }
        }
        cout << endl;
    }
}

// Подсчет живых соседей клетки
int countNeighbors(const vector<vector<bool>>& grid, int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue;
            int ni = x + i;
            int nj = y + j;
            if (ni >= 0 && ni < ROWS && nj >= 0 && nj < COLS) {
                count += grid[ni][nj];
            }
        }
    }
    return count;
}

// Применение моих правил (Живет если четное, умирает если нечетное)
void applyRules(const vector<vector<bool>>& grid, vector<vector<bool>>& newGrid) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            int neighbors = countNeighbors(grid, i, j);
            if (grid[i][j]) { // Живая клетка
                if (neighbors % 2 == 0) {
                    newGrid[i][j] = true; // Остаётся живой, если количество соседей чётное
                }
                else {
                    newGrid[i][j] = false; // Умирает, если количество соседей нечётное
                }
            }
            else { // Мёртвая клетка
                if (neighbors % 2 != 0) {
                    newGrid[i][j] = true; // Воскрешается, если количество соседей нечётное
                }
                else {
                    newGrid[i][j] = false; // Остаётся мёртвой
                }
            }
        }
    }
}

// Основная функция
int main() {
    vector<vector<bool>> grid(ROWS, vector<bool>(COLS, false));
    vector<vector<bool>> newGrid(ROWS, vector<bool>(COLS, false));

    // Статичные фигуры
     // 1. Блок (Block)
    grid[1][1] = true;
    grid[1][2] = true;
    grid[2][1] = true;
    grid[2][2] = true;

    // 2. Лодка (Boat)
    grid[3][8] = true;
    grid[1][7] = true;
    grid[2][6] = true;
    grid[2][8] = true;
    grid[3][7] = true;

    // 3. Корабль (Ship)
    grid[1][12] = true;
    grid[1][13] = true;
    grid[2][12] = true;
    grid[2][14] = true;
    grid[3][13] = true;
    grid[3][14] = true;

    // 4. Длинная Лодка (Long Boat)
    grid[3][19] = true;
    grid[1][19] = true;
    grid[2][18] = true;
    grid[2][20] = true;
    grid[3][21] = true;
    grid[4][20] = true;
    grid[4][21] = true;

    // 5. Каравай (Loaf)
    grid[7][1] = true;
    grid[7][2] = true;
    grid[8][0] = true;
    grid[8][3] = true;
    grid[9][1] = true;
    grid[9][3] = true;
    grid[10][2] = true;

    // 6. Улей (Beehive)
    grid[10][8] = true;
    grid[7][8] = true;
    grid[8][7] = true;
    grid[8][9] = true;
    grid[9][7] = true;
    grid[9][9] = true;

    // 7. Ящик (Tub)
    grid[7][14] = true;
    grid[8][13] = true;
    grid[8][15] = true;
    grid[9][14] = true;

    // 8. Змея (Snake)
    grid[7][19] = true;
    grid[7][21] = true;
    grid[8][19] = true;
    grid[7][22] = true;
    grid[8][20] = true;
    grid[8][22] = true;

    // 9. Баржа (Canoe)
    grid[13][1] = true;
    grid[14][2] = true;
    grid[14][0] = true;
    grid[15][1] = true;
    grid[15][3] = true;
    grid[16][2] = true;

    // 10. Пруд (Pond)
    grid[13][8] = true;
    grid[13][9] = true;
    grid[14][7] = true;
    grid[14][10] = true;
    grid[15][7] = true;
    grid[15][10] = true;
    grid[16][8] = true;
    grid[16][9] = true;

    // 11. Длинная баржа (Long Canoe)
    grid[13][15] = true;
    grid[14][16] = true;
    grid[16][18] = true;
    grid[16][16] = true;
    grid[14][14] = true;
    grid[15][17] = true;
    grid[15][15] = true;
    grid[17][17] = true;

    // 12. Длинный корабль (Long Shipl)
    grid[13][22] = true;
    grid[14][23] = true;
    grid[14][21] = true;
    grid[15][24] = true;
    grid[13][21] = true;
    grid[15][22] = true;
    grid[16][23] = true;
    grid[16][24] = true;
   



    // Демонстрация работы клеточного автомата
    for (int generation = 0; generation < 500; ++generation) {
        printGrid(grid);
        applyRules(grid, newGrid);
        grid.swap(newGrid);
        this_thread::sleep_for(chrono::milliseconds(DELAY));
    }

    return 0;
}
