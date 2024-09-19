#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <fstream>

// Definición del nodo de la lista enlazada
template <typename T>
class Node {
public:
    T data;
    Node* next;

    Node(T value) : data(value), next(nullptr) {}
};

// Definición de la lista enlazada ordenada
template <typename T>
class SortedLinkedList {
public:
    SortedLinkedList() : head(nullptr) {}

    // Insertar en la lista manteniendo el orden
    void insert(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (!head || head->data >= value) {
            newNode->next = head;
            head = newNode;
        } else {
            Node<T>* current = head;
            while (current->next && current->next->data < value) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
    }

    // Buscar un valor en la lista
    bool search(T value) {
        Node<T>* current = head;
        while (current) {
            if (current->data == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    ~SortedLinkedList() {
        Node<T>* current = head;
        while (current) {
            Node<T>* next = current->next;
            delete current;
            current = next;
        }
    }

private:
    Node<T>* head;
};

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

// Función para medir el rendimiento de la búsqueda
void measureSearchPerformance(size_t size, std::ofstream& file) {
    SortedLinkedList<int> list;
    std::vector<int> data;

    // Insertar datos en la lista
    generateAscendingData(data, size);
    for (int val : data) {
        list.insert(val);
    }

    // Mejor caso: Buscar un valor al principio
    auto start = std::chrono::high_resolution_clock::now();
    list.search(data[0]);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> best_case_duration = end - start;

    // Peor caso: Buscar un valor que no está en la lista
    start = std::chrono::high_resolution_clock::now();
    list.search(size + 1);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> worst_case_duration = end - start;

    // Caso promedio: Buscar un valor aleatorio
    start = std::chrono::high_resolution_clock::now();
    list.search(data[size / 2]);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> average_case_duration = end - start;

    file << size << ","
         << best_case_duration.count() << ","
         << worst_case_duration.count() << ","
         << average_case_duration.count() << "\n";
}

int main() {
    std::vector<size_t> sizes = {100, 500, 1000, 5000, 10000};
    std::ofstream file("sorted_linked_list_performance.csv");
    file << "Size, BestCaseTime, WorstCaseTime, AverageCaseTime\n";

    for (size_t size : sizes) {
        measureSearchPerformance(size, file);
    }

    file.close();
    return 0;
}
