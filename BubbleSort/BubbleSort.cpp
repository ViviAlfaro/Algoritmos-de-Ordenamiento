#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include <fstream>

template <typename T>
void bubbleSort(std::vector<T>& data) {
    bool swapped;
    for (size_t i = 0; i < data.size(); ++i) {
        swapped = false;
        for (size_t j = 0; j < data.size() - i - 1; ++j) {
            if (data[j] > data[j + 1]) {
                std::swap(data[j], data[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

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

void measureSortPerformance(size_t size, std::ofstream& file) {
    std::vector<int> data;

    // Mejor caso: Datos ordenados
    generateAscendingData(data, size);
    auto start = std::chrono::high_resolution_clock::now();
    bubbleSort(data);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> best_case_duration = end - start;

    // Peor caso: Datos ordenados en orden inverso
    generateDescendingData(data, size);
    start = std::chrono::high_resolution_clock::now();
    bubbleSort(data);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> worst_case_duration = end - start;

    // Caso promedio: Datos aleatorios
    generateRandomData(data, size);
    start = std::chrono::high_resolution_clock::now();
    bubbleSort(data);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> average_case_duration = end - start;

    file << size << ","
         << best_case_duration.count() << ","
         << worst_case_duration.count() << ","
         << average_case_duration.count() << "\n";
}

int main() {
    std::vector<size_t> sizes = {100, 500, 1000, 5000, 10000};
    std::ofstream file("bubble_sort_performance.csv");
    file << "Size, BestCaseTime, WorstCaseTime, AverageCaseTime\n";

    for (size_t size : sizes) {
        measureSortPerformance(size, file);
    }

    file.close();
    return 0;
}
