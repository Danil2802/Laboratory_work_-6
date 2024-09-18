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
