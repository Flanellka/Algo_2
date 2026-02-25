#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <thread>
#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;

// Функция создания случайной матрицы 
vector<double> generateMatrix(int N) {
    vector<double> matrix(N * N);
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 10.0);

    for (int i = 0; i < N * N; ++i) {
        matrix[i] = dis(gen);
    }
    return matrix;
}

// Обычное умножение матриц
void multiplySequential(const vector<double>& A, const vector<double>& B, vector<double>& C, int N) {
    for (int i = 0; i < N; ++i) {      
        for (int k = 0; k < N; ++k) {      
            for (int j = 0; j < N; ++j) {  
                C[i * N + j] += A[i * N + k] * B[k * N + j];
            }
        }
    }
}

// Функция для работы одного потока
void worker(const vector<double>& A, const vector<double>& B, vector<double>& C, int N, int startRow, int endRow) {
    for (int i = startRow; i < endRow; ++i) {
        for (int k = 0; k < N; ++k) {
            for (int j = 0; j < N; ++j) {
                C[i * N + j] += A[i * N + k] * B[k * N + j];
            }
        }
    }
}

// Параллельное умножение матриц
void multiplyParallel(const vector<double>& A, const vector<double>& B, vector<double>& C, int N, int numThreads) {
    vector<thread> threads; 
    int rowsPerThread = N / numThreads; 

    for (int i = 0; i < numThreads; ++i) {
        int startRow = i * rowsPerThread;
        int endRow = (i == numThreads - 1) ? N : (i + 1) * rowsPerThread; 

        threads.emplace_back(worker, ref(A), ref(B), ref(C), N, startRow, endRow);
    }

    for (auto& t : threads) {
        t.join();
    }
}

int main() {
    system("chcp 1251 > nul");
    setlocale(LC_ALL, "Russian");

    vector<int> sizes = { 64, 256, 1024, 4096 }; 
    int iterations = 10;
    int numThreads = 5; 

    ofstream file("results.csv");
    file << "MatrixSize(N),Type,Time(seconds)\n";

    cout << "Начало тестирования\n";

    for (int N : sizes) {
        cout << "Размер матрицы: " << N << "x" << N << "..." << endl;

        // Создаем матрицы
        auto A = generateMatrix(N);
        auto B = generateMatrix(N);

        // Тест обычного умножения 
        for (int i = 0; i < iterations; ++i) {
            vector<double> C(N * N, 0.0); 

            auto start = chrono::high_resolution_clock::now();
            multiplySequential(A, B, C, N);
            auto end = chrono::high_resolution_clock::now();

            chrono::duration<double> duration = end - start;
            file << N << ",Sequential," << duration.count() << "\n";
        }

        // Тест параллельного умножения
        for (int i = 0; i < iterations; ++i) {
            vector<double> C(N * N, 0.0);

            auto start = chrono::high_resolution_clock::now();
            multiplyParallel(A, B, C, N, numThreads);
            auto end = chrono::high_resolution_clock::now();

            chrono::duration<double> duration = end - start;
            file << N << ",Parallel," << duration.count() << "\n";
        }
    }

    cout << "Готово, результат сохранен в results.csv" << endl;
    file.close();
    return 0;
}
