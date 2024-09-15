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
const double LIVE_CELL_PROBABILITY = 0.2; // Вероятность, что клетка будет живой 

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

// Применение классических правил клеточного автомата
void applyRules(const vector<vector<bool>>& grid, vector<vector<bool>>& newGrid) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            int neighbors = countNeighbors(grid, i, j);
            if (grid[i][j]) { // Живая клетка
                if (neighbors < 2 || neighbors > 3) {
                    newGrid[i][j] = false; // Умирает от одиночества или перенаселённости
                }
                else {
                    newGrid[i][j] = true; // Остаётся живой
                }
            }
            else { // Мёртвая клетка
                if (neighbors == 3) {
                    newGrid[i][j] = true; // Воскрешается
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
    srand(time(0)); // Инициализация генератора случайных чисел

    vector<vector<bool>> grid(ROWS, vector<bool>(COLS, false));
    vector<vector<bool>> newGrid(ROWS, vector<bool>(COLS, false));

    // Инициализация случайных живых клеток с заданной вероятностью
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (static_cast<double>(rand()) / RAND_MAX < LIVE_CELL_PROBABILITY) {
                grid[i][j] = true;
            }
        }
    }

    // Демонстрация работы клеточного автомата
    for (int generation = 0; generation < 500; ++generation) {
        printGrid(grid);
        applyRules(grid, newGrid);
        grid.swap(newGrid);
        this_thread::sleep_for(chrono::milliseconds(DELAY));
    }

    return 0;
}
