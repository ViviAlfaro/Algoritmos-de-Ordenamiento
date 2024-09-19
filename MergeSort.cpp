#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <fstream>

// Función auxiliar para fusionar dos subarreglos
template <typename T>
void merge(std::vector<T>& data, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<T> L(n1);
    std::vector<T> R(n2);

    for (int i = 0; i < n1; ++i)
        L[i] = data[left + i];
    for (int j = 0; j < n2; ++j)
        R[j] = data[mid + 1 + j];

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            data[k] = L[i];
            ++i;
        } else {
            data[k] = R[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        data[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        data[k] = R[j];
        ++j;
        ++k;
    }
}

// Función recursiva de MergeSort
template <typename T>
void mergeSort(std::vector<T>& data, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(data, left, mid);
        mergeSort(data, mid + 1, right);
        merge(data, left, mid, right);
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
    mergeSort(data, 0, data.size() - 1);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> best_case_duration = end - start;

    // Peor caso: Datos ordenados en orden inverso
    generateDescendingData(data, size);
    start = std::chrono::high_resolution_clock::now();
    mergeSort(data, 0, data.size() - 1);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> worst_case_duration = end - start;

    // Caso promedio: Datos aleatorios
    generateRandomData(data, size);
    start = std::chrono::high_resolution_clock::now();
    mergeSort(data, 0, data.size() - 1);
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
    std::ofstream file("merge_sort_performance.csv");
    file << "Size, BestCaseTime, WorstCaseTime, AverageCaseTime\n";

    for (size_t size : sizes) {
        measureSortPerformance(size, file);
    }

    file.close();
    return 0;
}

