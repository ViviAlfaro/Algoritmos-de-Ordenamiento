#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <fstream>

template <typename T>
class TreeNode {
public:
    T data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(T value) : data(value), left(nullptr), right(nullptr) {}
};

template <typename T>
class BinarySearchTree {
public:
    BinarySearchTree() : root(nullptr) {}

    // Insertar un valor en el árbol
    void insert(T value) {
        root = insertRecursive(root, value);
    }

    // Función para medir el rendimiento de la inserción
    void measureInsertPerformance(size_t size, std::ofstream& file) {
        std::vector<T> data;
        generateAscendingData(data, size);

        auto start = std::chrono::high_resolution_clock::now();
        for (const T& value : data) {
            insert(value);
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;

        file << size << "," << duration.count() << "\n";
    }

    ~BinarySearchTree() {
        destroyTree(root);
    }

private:
    TreeNode<T>* root;

    TreeNode<T>* insertRecursive(TreeNode<T>* node, T value) {
        if (!node) {
            return new TreeNode<T>(value);
        }
        if (value < node->data) {
            node->left = insertRecursive(node->left, value);
        } else {
            node->right = insertRecursive(node->right, value);
        }
        return node;
    }

    void destroyTree(TreeNode<T>* node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

    void generateAscendingData(std::vector<T>& data, size_t size) {
        data.resize(size);
        for (size_t i = 0; i < size; ++i) {
            data[i] = i;
        }
    }
};

int main() {
    std::vector<size_t> sizes = {100, 500, 1000, 5000, 10000};
    std::ofstream file("binary_search_tree_performance.csv");
    file << "Size, InsertTime\n";

    BinarySearchTree<int> bst;

    for (size_t size : sizes) {
        bst.measureInsertPerformance(size, file);
    }

    file.close();
    return 0;
}
