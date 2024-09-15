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
