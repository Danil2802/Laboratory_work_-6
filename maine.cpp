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
