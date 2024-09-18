# Лабораторная работа №6
## «Обработка двумерных массивов и контейнеров»
## по дисциплине: «Программирование»
### Цели и задачи работы: изучение алгоритмов формирования и обработки двумерных массивов, программирование и отладка программ формирования и обработки массивов (статических и динамических) и контейнеров STL. 
### Задание к работе: Самостоятельно решить задачи в соответствии с индивидуальным вариантом. 
### Методика выполнения работы: 
#### 1. Разработать алгоритм решения задачи по индивидуальному заданию. 
#### 2. Написать и отладить программу решения задачи на двух языках (С++ и второй, по выбору). 
#### 3. Протестировать работу программы на различных исходных данных.
### Задания:
### Задание №1 Обработка двумерных массивов.
#### Вариант 15 
#### 1.Определите и инициализируйте матрицу размера M × N случайными вещественными числами в диапазоне [-50, 50]. Перезапишите строки в матрице в обратном порядке (дополнительный массив не используйте). Найдите в матрице второй минимальный и максимальный элементы. 
#### 2.Напишите программу, инициализирующую матрицу, как в примере. Количество строк матрицы задаётся с клавиатуры. 
#### Пример: N = 5 
#### 100 
#### 105 110 
#### 115 120 125 
#### 105 110 
#### 100 
#### 3.Реализуйте клеточный автомат Джона Конвея на ограниченной плоскости по классическим и оригинальным (своим) правилам. Продемонстрируйте работу клеточного автомата на примере устойчивой фигуры (фигуры, которые остаются неизменными), а затем на этой же фигуре с измененными правилами, и на развитии колоний клеток, сгенерированных в случайном порядке. Понаблюдайте за изменениями в эволюции. Реализовать работу графического отображения клеточного автомата можно таким образом, чтобы живые клетки изображались единицами, а мёртвые – нулями, либо живые – нулями, а мёртвые пробелами, либо другим возможным вариантом. Каждое новое поколение выводится на очищенное окно консоли через некоторый промежуток времени, например, 250 мс. Таким образом, получается непрерывная анимация.
### Задание №2 Многоалфавитное шифрование с использованием алгоритма AES. Дешифрование текста.
#### Вариант 1 
#### а) систему шифрования AES128 (CFB) для преобразования исходного текста; 
#### б) систему шифрования AES128 (CFB) для преобразования зашифрованного текста в исходный.
#### Для всех вариантов, вывести все сгенерированные ключи, промежуточные результаты State, а также вектор инициализации, добавить генерацию случайного ключа и запись ключа в файл. Реализация должна работать с любым языком, как русским, так и английским.
### Задание №3 Методы решения систем линейных алгебраических уравнений
#### Выбрать данные для системы линейных уравнений. Найти решение этой системы прямым и приближенным методами с точностью до ε=10-3. Решить систему уравнений методом Гаусса с выбором главного элемента. Исходная система линейных уравнений:  
#### 0.89x1 – 0.04x2 + 0.21x3 − 18x4 = −1.24 
#### 0.25x1 – 1.23x2 + 0.12x3 – 0.09x4 = −1.15 
#### −0.21x1 + 0.12x2 + 0.8x3 – 0.13x4 = 2.56 
#### 0.15x1 – 1.31x2 + 0.06x3 – 1.15x4 = 0.89

### 1.1 Задание на языке С++ в mainq.cpp
```C++
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <algorithm>
#include <sstream>
#include <string>

using namespace std;

// Функция для генерации случайных вещественных чисел в диапазоне [-50, 50]
double randomDouble(double min, double max) {
    return min + (max - min) * (rand() / static_cast<double>(RAND_MAX));
}

// Функция для вывода матрицы
void printMatrix(const vector<vector<double>>& matrix) {
    for (const auto& row : matrix) {
        for (const auto& elem : row) {
            cout << elem << " ";
        }
        cout << endl;
    }
}

void reverseRows(vector<vector<double>>& matrix) {
    for (auto& row : matrix) {
        reverse(row.begin(), row.end());
    }
}

// Функция для нахождения второго минимального и максимального элементов в матрице
void findSecondMinMax(const vector<vector<double>>& matrix, double& secondMin, double& secondMax) {
    double minVal = numeric_limits<double>::max();
    double maxVal = numeric_limits<double>::lowest();
    secondMin = numeric_limits<double>::max();
    secondMax = numeric_limits<double>::lowest();

    for (const auto& row : matrix) {
        for (const auto& elem : row) {
            if (elem < minVal) {
                secondMin = minVal;
                minVal = elem;
            }
            else if (elem > minVal && elem < secondMin) {
                secondMin = elem;
            }

            if (elem > maxVal) {
                secondMax = maxVal;
                maxVal = elem;
            }
            else if (elem < maxVal && elem > secondMax) {
                secondMax = elem;
            }
        }
    }
}

bool isNumber(const string& str) {
    for (char c : str) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(nullptr));

    int M, N;
    string input;
    bool validInput = false;

    while (!validInput) {
        cout << "Введите размеры матрицы M и N: ";
        getline(cin, input);

        stringstream ss(input);
        vector<string> tokens;
        string token;

        while (ss >> token) {
            tokens.push_back(token);
        }

        if (tokens.size() != 2) {
            cout << "Некорректное количество слов. Пожалуйста, введите два целых числа." << endl;
            continue;
        }

        if (!isNumber(tokens[0]) || !isNumber(tokens[1])) {
            cout << "Пожалуйста, введите два целых числа." << endl;
            continue;
        }

        M = stoi(tokens[0]);
        N = stoi(tokens[1]);

        if (M < 1 || M > 50 || N < 1 || N > 50) {
            cout << "Недопустимые условия. Пожалуйста, введите числа в диапазоне [1, 50]." << endl;
            continue;
        }

        if (M == 1 && N == 1) {
            cout << "Некорректные числа. Пожалуйста, введите числа, не равные оба 1." << endl;
            continue;
        }
        validInput = true;
    }

    vector<vector<double>> matrix(M, vector<double>(N));

    // Инициализация матрицы случайными вещественными числами
    for (auto& row : matrix) {
        for (auto& elem : row) {
            elem = randomDouble(-50, 50);
        }
    }

    cout << "Исходная матрица:" << endl;
    printMatrix(matrix);

    // Перезапись строк матрицы в обратном порядке
    reverseRows(matrix);

    cout << "Матрица после перезаписи строк в обратном порядке:" << endl;
    printMatrix(matrix);

    // Нахождение второго минимального и максимального элементов
    double secondMin, secondMax;
    findSecondMinMax(matrix, secondMin, secondMax);

    cout << "Второй минимальный элемент: " << secondMin << endl;
    cout << "Второй максимальный элемент: " << secondMax << endl;

    return 0;
}
```
#### 1.1 задача на языке Java в mainw.txt
 
### 1.2 задача на языке С++ в maine.cpp
```C++
#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <sstream>

using namespace std;

void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (const auto& elem : row) {
            cout << elem << " ";
        }
        cout << endl;
    }
}

vector<vector<int>> generateMatrix(int N) {
    vector<vector<int>> matrix;
    int startValue = 100;
    int step = 5;
    int s = 0;

    // Верхняя часть матрицы
    for (int i = 0; i < N / 2; i++) {
        vector<int> row;
        int currentValue = startValue + s * step;
        for (int j = 0; j <= i; j++) {
            row.push_back(currentValue);
            currentValue += step;
        }
        s = s + i + 1;
        matrix.push_back(row);
    }

    // Центральная строка для нечетных N
    if (N % 2 != 0) {
        vector<int> row;
        int currentValue = startValue + s * step;
        for (int j = 0; j <= N / 2; j++) {
            row.push_back(currentValue);
            currentValue += step;
        }
        matrix.push_back(row);
    }

    // Нижняя часть матрицы
    for (int i = N / 2 - 1; i >= 0; i--) {
        s = s - i - 1;
        vector<int> row;
        int currentValue = startValue + s * step;
        for (int j = 0; j <= i; j++) {
            row.push_back(currentValue);
            currentValue += step;
        }
        matrix.push_back(row);
    }
    return matrix;
}

bool isValidNumber(const string& input) {
    if (input.empty()) return false;
    for (char c : input) {
        if (!isdigit(c)) return false;
    }
    int number = stoi(input);
    return number >= 1 && number <= 100;
}

int main() {
    setlocale(LC_ALL, "Russian");
    string input;
    int N;

    while (true) {
        cout << "Введите количество строк матрицы: ";
        getline(cin, input);

        istringstream iss(input);
        string word;
        iss >> word;

        if (iss >> word) {
            cout << "Некорректный ввод. Пожалуйста, введите только одно число." << endl;
        }
        else if (isValidNumber(input)) {
            N = stoi(input);
            break;
        }
        else {
            cout << "Некорректный ввод. Пожалуйста, введите число от 1 до 100." << endl;
        }
    }

    vector<vector<int>> matrix = generateMatrix(N);

    printMatrix(matrix);

    return 0;
}
```
#### 1.2 задача на языке Java в mainr.txt

### 1.3.1.1 задача на языке С++ в maint.cpp
```C++
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
```
#### 1.3.1.1 задача на языке Java в mainy.cpp

### 1.3.1.2 задача на языке С++ в mainu.cpp
```C++
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
```
#### 1.3.1.2 на языке Java в mains.txt

### 1.3.2.1 на языке С++ в maind.cpp
```C++
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
```
#### 1.3.2.1 задача на языке Java в mainf.txt

### 1.3.2.2 задача на языке С++ в maing.cpp
```C++
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
const double LIVE_CELL_PROBABILITY = 0.01; // Вероятность, что клетка будет живой 

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
```
#### 1.3.2.2 задача на языке Java в mainh.txt

### 2 задача на языке С++ в mainz.cpp
```C++
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iomanip>
#include <cstring>

using namespace std;

// Таблица S-Box
const uint8_t sbox[256] = {
0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5,
0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0,
0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc,
0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a,
0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0,
0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b,
0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85,
0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5,
0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17,
0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88,
0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c,
0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9,
0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6,
0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e,
0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94,
0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68,
0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};

// Таблица обратного S-Box (InvS-Box)
const uint8_t rsbox[256] = {
0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38,
0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87,
0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d,
0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2,
0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16,
0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda,
0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a,
0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02,
0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea,
0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85,
0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89,
0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20,
0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31,
0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d,
0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0,
0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26,
0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d
};

// Вектор инициализации (IV)
uint8_t IV[16];

// Умножение на 2 в GF(2^8)
uint8_t mul2(uint8_t x) {
    return (x << 1) ^ ((x & 0x80) ? 0x1B : 0x00);
}

// Умножение на 3 в GF(2^8)
uint8_t mul3(uint8_t x) {
    return mul2(x) ^ x;
}

// Умножение на 9 в GF(2^8)
uint8_t mul9(uint8_t x) {
    return mul2(mul2(mul2(x))) ^ x;
}

// Умножение на 11 в GF(2^8)
uint8_t mul11(uint8_t x) {
    return mul2(mul2(mul2(x)) ^ x) ^ x;
}

// Умножение на 13 в GF(2^8)
uint8_t mul13(uint8_t x) {
    return mul2(mul2(mul2(x) ^ x)) ^ x;
}

// Умножение на 14 в GF(2^8)
uint8_t mul14(uint8_t x) {
    return mul2(mul2(mul2(x) ^ x) ^ x);
}

// MixColumns
void MixColumns(uint8_t* state) {
    uint8_t temp[4];
    for (int i = 0; i < 4; ++i) {
        temp[0] = mul2(state[i * 4]) ^ mul3(state[i * 4 + 1]) ^ state[i * 4 + 2] ^ state[i * 4 + 3];
        temp[1] = state[i * 4] ^ mul2(state[i * 4 + 1]) ^ mul3(state[i * 4 + 2]) ^ state[i * 4 + 3];
        temp[2] = state[i * 4] ^ state[i * 4 + 1] ^ mul2(state[i * 4 + 2]) ^ mul3(state[i * 4 + 3]);
        temp[3] = mul3(state[i * 4]) ^ state[i * 4 + 1] ^ state[i * 4 + 2] ^ mul2(state[i * 4 + 3]);
        for (int j = 0; j < 4; ++j) {
            state[i * 4 + j] = temp[j];
        }
    }
}

// InvMixColumns
void InvMixColumns(uint8_t* state) {
    uint8_t temp[4];
    for (int i = 0; i < 4; ++i) {
        temp[0] = mul14(state[i * 4]) ^ mul11(state[i * 4 + 1]) ^ mul13(state[i * 4 + 2]) ^ mul9(state[i * 4 + 3]);
        temp[1] = mul9(state[i * 4]) ^ mul14(state[i * 4 + 1]) ^ mul11(state[i * 4 + 2]) ^ mul13(state[i * 4 + 3]);
        temp[2] = mul13(state[i * 4]) ^ mul9(state[i * 4 + 1]) ^ mul14(state[i * 4 + 2]) ^ mul11(state[i * 4 + 3]);
        temp[3] = mul11(state[i * 4]) ^ mul13(state[i * 4 + 1]) ^ mul9(state[i * 4 + 2]) ^ mul14(state[i * 4 + 3]);
        for (int j = 0; j < 4; ++j) {
            state[i * 4 + j] = temp[j];
        }
    }
}

// Функция для генерации случайного ключа и IV
void generateRandomKeyAndIV(uint8_t* key, uint8_t* iv) {
    srand(time(0));
    for (int i = 0; i < 16; ++i) {
        key[i] = rand() % 256;
        iv[i] = rand() % 256;
    }
}

// Функция для подстановки байтов через S-box
void SubBytes(uint8_t* state) {
    for (int i = 0; i < 16; ++i) {
        state[i] = sbox[state[i]];
    }
}

// Функция обратной подстановки байтов через S-box
void InvSubBytes(uint8_t* state) {
    for (int i = 0; i < 16; ++i) {
        state[i] = rsbox[state[i]];
    }
}

// Сдвиг строк (ShiftRows)
void ShiftRows(uint8_t* state) {
    uint8_t temp;

    // Строка 1: сдвиг на 1 байт влево
    temp = state[1];
    state[1] = state[5];
    state[5] = state[9];
    state[9] = state[13];
    state[13] = temp;

    // Строка 2: сдвиг на 2 байта влево
    temp = state[2];
    state[2] = state[10];
    state[10] = temp;
    temp = state[6];
    state[6] = state[14];
    state[14] = temp;

    // Строка 3: сдвиг на 3 байта влево
    temp = state[3];
    state[3] = state[15];
    state[15] = state[11];
    state[11] = state[7];
    state[7] = temp;
}

// Обратный сдвиг строк (InvShiftRows)
void InvShiftRows(uint8_t* state) {
    uint8_t temp;

    // Строка 1: сдвиг на 1 байт вправо
    temp = state[13];
    state[13] = state[9];
    state[9] = state[5];
    state[5] = state[1];
    state[1] = temp;

    // Строка 2: сдвиг на 2 байта вправо
    temp = state[2];
    state[2] = state[10];
    state[10] = temp;
    temp = state[6];
    state[6] = state[14];
    state[14] = temp;

    // Строка 3: сдвиг на 3 байта вправо
    temp = state[7];
    state[7] = state[11];
    state[11] = state[15];
    state[15] = state[3];
    state[3] = temp;
}

// Таблицы Rcon
const uint8_t Rcon[10] = {
0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36
};

// Генерация раундовых ключей
void KeyExpansion(const uint8_t* key, uint8_t* roundKeys) {
    uint8_t temp[16];
    memcpy(roundKeys, key, 16);

    for (int i = 16; i < 176; i += 16) {
        memcpy(temp, roundKeys + i - 16, 16);

        if (i % 16 == 0) {
            // Rotate, apply S-box and XOR with Rcon
            uint8_t k = temp[0];
            memmove(temp, temp + 1, 15);
            temp[15] = k;

            for (int j = 0; j < 16; ++j) {
                temp[j] = sbox[temp[j]];
            }

            temp[0] ^= Rcon[i / 16 - 1];
        }

        for (int j = 0; j < 16; ++j) {
            roundKeys[i + j] = roundKeys[i + j - 16] ^ temp[j];
        }
    }
}

// Применение раундового ключа
void AddRoundKey(uint8_t* state, const uint8_t* roundKey) {
    for (int i = 0; i < 16; ++i) {
        state[i] ^= roundKey[i];
    }
}

// Шифрование блока данных AES-128
void AES128_Encrypt(uint8_t* input, const uint8_t* roundKeys) {
    uint8_t state[16];
    memcpy(state, input, 16);

    AddRoundKey(state, roundKeys);

    for (int round = 1; round <= 9; ++round) {
        SubBytes(state);
        ShiftRows(state);
        MixColumns(state); 
        AddRoundKey(state, roundKeys + round * 16);
    }

    SubBytes(state);
    ShiftRows(state);
    AddRoundKey(state, roundKeys + 160);

    memcpy(input, state, 16);
}

// Расшифрование блока данных AES-128
void AES128_Decrypt(uint8_t* input, const uint8_t* roundKeys) {
    uint8_t state[16];
    memcpy(state, input, 16);

    AddRoundKey(state, roundKeys + 160);

    for (int round = 9; round >= 1; --round) {
        InvShiftRows(state);
        InvSubBytes(state);
        AddRoundKey(state, roundKeys + round * 16);
        InvMixColumns(state);
    }

    InvShiftRows(state);
    InvSubBytes(state);
    AddRoundKey(state, roundKeys);

    memcpy(input, state, 16);
}

// Функция для форматированного вывода байтов в виде hex
void printHex(const uint8_t* data, size_t length, const string& label) {
    cout << label;
    for (size_t i = 0; i < length; ++i) {
        cout << hex << setw(2) << setfill('0') << (int)data[i] << " ";
    }
    cout << endl;
}

// Функция для вывода состояния (state)
void printState(const uint8_t* state, const string& label) {
    printHex(state, 16, label);
}

// Функция для вывода ключей
void printRoundKeys(const uint8_t* roundKeys, int count) {
    for (int i = 0; i < count; ++i) {
        printHex(roundKeys + i * 16, 16, "Round Key " + to_string(i) + ": ");
    }
}

// Функция для вывода вектора инициализации (IV)
void printIV(const uint8_t* iv, const string& label) {
    printHex(iv, 16, label);
}

// Функция AES128_CFB_Encrypt с выводом
void AES128_CFB_Encrypt(uint8_t* plaintext, uint8_t* ciphertext, int length, uint8_t* key) {
    uint8_t roundKeys[176];
    KeyExpansion(key, roundKeys);
    printRoundKeys(roundKeys, 11); // Выводим все раундовые ключи

    uint8_t iv[16];
    memcpy(iv, IV, 16);
    printIV(iv, "Initial IV: ");

    for (int i = 0; i < length; i += 16) {
        AES128_Encrypt(iv, roundKeys);
        printState(iv, "State after encryption with IV: "); // Вывод промежуточного состояния
        for (int j = 0; j < 16; ++j) {
            ciphertext[i + j] = plaintext[i + j] ^ iv[j];
            iv[j] = ciphertext[i + j];
        }
        printIV(iv, "IV for next block: ");
    }
}

// Функция AES128_CFB_Decrypt с выводом
void AES128_CFB_Decrypt(uint8_t* ciphertext, uint8_t* plaintext, int length, uint8_t* key) {
    uint8_t roundKeys[176];
    KeyExpansion(key, roundKeys);
    printRoundKeys(roundKeys, 11); // Выводим все раундовые ключи

    uint8_t iv[16];
    memcpy(iv, IV, 16);
    printIV(iv, "Initial IV: ");

    for (int i = 0; i < length; i += 16) {
        uint8_t temp[16];
        memcpy(temp, iv, 16);

        AES128_Encrypt(iv, roundKeys);
        printState(iv, "State after encryption with IV: "); // Вывод промежуточного состояния

        for (int j = 0; j < 16; ++j) {
            plaintext[i + j] = ciphertext[i + j] ^ iv[j];
            iv[j] = ciphertext[i + j];
        }
        printIV(iv, "IV for next block: ");
    }
}

// Функция для PKCS7 заполнения
void PKCS7Padding(vector<uint8_t>& plaintext) {
    int paddingValue = 16 - (plaintext.size() % 16);
    plaintext.insert(plaintext.end(), paddingValue, paddingValue);
}

// Функция для удаления PKCS7 padding
void PKCS7Unpadding(vector<uint8_t>& plaintext) {
    uint8_t paddingValue = plaintext.back();
    plaintext.resize(plaintext.size() - paddingValue);
}

int main() {
    setlocale(LC_ALL, "Russian");
    uint8_t key[16];
    generateRandomKeyAndIV(key, IV);

    // Ввод текста пользователем
    string input;
    cout << "Введите текст для шифрования: ";
    getline(cin, input);

    // Преобразование введённого текста в массив байтов (UTF-8)
    vector<uint8_t> plaintext(input.begin(), input.end());
    PKCS7Padding(plaintext);  // Применяем PKCS7 заполнение

    vector<uint8_t> ciphertext(plaintext.size());
    vector<uint8_t> decryptedtext(plaintext.size());

    // Выводим сгенерированный ключ и вектор инициализации
    printHex(key, 16, "Generated Key: ");
    printIV(IV, "Generated IV: ");

    AES128_CFB_Encrypt(plaintext.data(), ciphertext.data(), plaintext.size(), key);
    AES128_CFB_Decrypt(ciphertext.data(), decryptedtext.data(), plaintext.size(), key);

    PKCS7Unpadding(decryptedtext);  // Убираем PKCS7 заполнение

    cout << "Ciphertext: ";
    for (size_t i = 0; i < ciphertext.size(); ++i) {
        printf("%02x", ciphertext[i]);
    }
    cout << endl;

    cout << "Decrypted: " << string(decryptedtext.begin(), decryptedtext.end()) << endl;

    return 0;
}
```
#### 2 задача на языке Java в mainx.txt

### 3 задача на языке С++ в mainc.cpp
```C++
#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

const int MAX_ITER = 1000;
const double EPSILON = 1e-3;

void printMatrix(const vector<vector<double>>& a, const vector<double>& b) {
    int n = a.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(10) << fixed << setprecision(3) << a[i][j] << " ";
        }
        cout << "| " << setw(10) << fixed << setprecision(3) << b[i] << endl;
    }
    cout << endl;
}

void printCanonicalForm(const vector<vector<double>>& a, const vector<double>& b) {
    int n = a.size();
    cout << "\nКаноническая форма системы уравнений:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(10) << fixed << setprecision(3) << a[i][j] << " ";
        }
        cout << "| " << setw(10) << fixed << setprecision(3) << b[i] << endl;
    }
    cout << endl;
}

void printEquationForm(const vector<vector<double>>& a, const vector<double>& b) {
    int n = a.size();
    cout << "Форма уравнений системы:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "   x" << i + 1 << " = (";
        bool firstTerm = true;
        for (int j = 0; j < n; j++) {
            if (i != j) {
                if (!firstTerm) {
                    cout << " ";
                }
                else {
                    firstTerm = false;
                }
                double coeff = -a[i][j]; // Change sign for the equation form
                if (coeff >= 0) {
                    cout << "+" << setw(5) << fixed << setprecision(2) << coeff << " * x" << j + 1;
                }
                else {
                    cout << "-" << setw(5) << fixed << setprecision(2) << abs(coeff) << " * x" << j + 1;
                }
            }
        }
        cout << " + " << setw(5) << fixed << setprecision(2) << b[i] << ") / " << setw(5) << fixed << setprecision(2) << a[i][i] << endl;
    }
    cout << endl;
}

void gaussElimination(vector<vector<double>>& a, vector<double>& b, vector<double>& x, int& operations) {
    int n = a.size();
    cout << "Решение прямым методом (методом Гаусса):" << endl;
    cout << "Прямой ход метода Гаусса:" << endl;
    for (int i = 0; i < n; i++) {
        // Partial pivoting
        int maxRow = i;
        for (int k = i + 1; k < n; k++) {
            if (abs(a[k][i]) > abs(a[maxRow][i])) {
                maxRow = k;
            }
        }

        // Swap rows
        swap(a[maxRow], a[i]);
        swap(b[maxRow], b[i]);

        // Make upper triangular
        for (int k = i + 1; k < n; k++) {
            double factor = a[k][i] / a[i][i];
            for (int j = i; j < n; j++) {
                a[k][j] -= factor * a[i][j];
                operations++;
            }
            b[k] -= factor * b[i];
            operations++;
        }
        printMatrix(a, b);
    }

    // Back substitution
    cout << "Обратный ход метода Гаусса:" << endl;
    for (int i = n - 1; i >= 0; i--) {
        x[i] = b[i];
        for (int j = i + 1; j < n; j++) {
            x[i] -= a[i][j] * x[j];
            operations++;
        }
        x[i] /= a[i][i];
        operations++;
        printMatrix(a, b);
    }
}

void printSolutionGauss(const vector<double>& x, int operations) {
    cout << "Ответы методом Гаусса:" << endl;
    cout << setw(5) << "N";
    for (int i = 0; i < x.size(); i++) {
        cout << setw(9) << "x" << i + 1;
    }
    cout << setw(10) << "en" << endl;

    cout << setw(5) << operations;
    for (int i = 0; i < x.size(); i++) {
        cout << setw(10) << fixed << setprecision(3) << x[i];
    }
    cout << setw(10) << "0.000" << endl; // For Gauss elimination, assuming zero final error
}

bool checkDiagonalDominance(const vector<vector<double>>& a) {
    int n = a.size();
    for (int i = 0; i < n; i++) {
        double diagonal = abs(a[i][i]);
        double sum = 0;
        for (int j = 0; j < n; j++) {
            if (i != j) {
                sum += abs(a[i][j]);
            }
        }
        if (diagonal <= sum) {
            cout << "\nСтрока " << i + 1 << " не удовлетворяет условию строгого диагонального доминирования." << endl;
            return false; // Not strictly diagonally dominant
        }
    }
    return true; // Diagonally dominant
}

void gaussSeidel(const vector<vector<double>>& a, const vector<double>& b, vector<double>& x, int& iterations) {
    int n = a.size();
    vector<double> x_old(n, 0.0);
    double error = 0;

    cout << "\nРешение методом Гаусса-Зейделя:" << endl;
    cout << setw(5) << "N";
    for (int i = 0; i < n; i++) {
        cout << setw(9) << "x" << i + 1;
    }
    cout << setw(10) << "en" << endl;

    do {
        error = 0;
        for (int i = 0; i < n; i++) {
            double sum = b[i];
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    sum -= a[i][j] * x[j];
                }
            }
            x_old[i] = x[i]; // Save the old value for error calculation
            x[i] = sum / a[i][i];

            error = max(error, abs(x[i] - x_old[i]));
        }
        iterations++;

        cout << setw(5) << iterations;
        for (int i = 0; i < n; i++) {
            cout << setw(10) << fixed << setprecision(3) << x[i];
        }
        cout << setw(10) << fixed << setprecision(3) << error << endl;
    } while (error > EPSILON && iterations < MAX_ITER);
}

int main() {
    setlocale(LC_ALL, "Russian");

    vector<vector<double>> a = {
        {0.89, -0.04, 0.21, -0.18},
        {0.25, -1.23, 0.12, -0.09},
        {-0.21, 0.12, 0.8, -0.13},
        {0.15, -1.31, 0.06, -1.55}
    };

    vector<double> b = { -1.24, -1.15, 2.56, 0.89 };

    // Создаем копию матрицы и вектора b для проверки на диагональное доминирование
    vector<vector<double>> originalA = a;
    vector<double> originalB = b;

    vector<double> x(a.size(), 0.0);
    int operations = 0;

    gaussElimination(a, b, x, operations);
    printSolutionGauss(x, operations);

    // Проверка диагонального доминирования на исходной матрице
    if (!checkDiagonalDominance(originalA)) {
        cout << "Матрица не является строго диагонально доминирующей. Решение методом Гаусса-Зейделя невозможно." << endl;
        return 1;
    }

    // Вывод канонической формы матрицы и формы системы уравнений
    printCanonicalForm(originalA, originalB);
    printEquationForm(originalA, originalB);

    // Gauss-Seidel Method
    vector<double> x_seidel(a.size(), 0.0);
    int iterations = 0;

    gaussSeidel(originalA, originalB, x_seidel, iterations);

    return 0;
}
```
#### 3 задача на языке Java в mainv.txt
