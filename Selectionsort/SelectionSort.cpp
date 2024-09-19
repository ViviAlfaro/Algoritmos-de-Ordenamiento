#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include <fstream>

// Algoritmo de SelectionSort
template <typename T>
void selectionSort(std::vector<T>& data) {
    for (size_t i = 0; i < data.size() - 1; ++i) {
        size_t minIndex = i;
        for (size_t j = i + 1; j < data.size(); ++j) {
            if (data[j] < data[minIndex]) {
                minIndex = j;
            }
        }
        std::swap(data[i], data[minIndex]);
    }
}

// Funciones para generar datos de prueba
void generateAscendingData(std::vector<int>& data, size_t size) {
    data.resize(size);
    for (size_t i = 0; i < size; ++i) {
        data[i] = i;
    }
}

void generateDescendingData(std::vector<int>& data, size_t size) {
    data.resize(size);
    for (size_t i = 0; i < size; ++i) {
        data[i] = size - i - 1;
    }
}

void generateRandomData(std::vector<int>& data, size_t size) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 10000);
    data.resize(size);
    for (auto& val : data) {
        val = dis(gen);
    }
}

// Función para medir el rendimiento del algoritmo
void measureSortPerformance(size_t size, std::ofstream& file) {
    std::vector<int> data;

    // Mejor caso: Datos ordenados
    generateAscendingData(data, size);
    auto start = std::chrono::high_resolution_clock::now();
    selectionSort(data);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> best_case_duration = end - start;

    // Peor caso: Datos ordenados en orden inverso
    generateDescendingData(data, size);
    start = std::chrono::high_resolution_clock::now();
    selectionSort(data);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> worst_case_duration = end - start;

    // Caso promedio: Datos aleatorios
    generateRandomData(data, size);
    start = std::chrono::high_resolution_clock::now();
    selectionSort(data);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> average_case_duration = end - start;

    // Guardar los resultados en el archivo CSV
    file << size << ","
         << best_case_duration.count() << ","
         << worst_case_duration.count() << ","
         << average_case_duration.count() << "\n";
}

int main() {
    std::vector<size_t> sizes = {100, 500, 1000, 5000, 10000};
    std::ofstream file("selection_sort_performance.csv");
    file << "Size, BestCaseTime, WorstCaseTime, AverageCaseTime\n";

    for (size_t size : sizes) {
        measureSortPerformance(size, file);
    }

    file.close();
    return 0;
}
