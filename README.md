# Análisis de Algoritmos

Este repositorio contiene la implementación de cinco algoritmos comunes de ordenamiento y estructuras de datos, así como una interfaz gráfica que permite visualizar su rendimiento en términos de tiempo de ejecución (mejor caso, peor caso, y caso promedio). Los gráficos se generan utilizando las bibliotecas GTK+ y Cairo en C++.

## Algoritmos implementados:

    Bubble Sort (O(n), O(n²), O(n²))
    Selection Sort (O(n²), O(n²), O(n²))
    Merge Sort (O(n log n), O(n log n), O(n log n))
    Binary Search Tree (O(n), O(log n), O(log n))
    Sorted Linked List (O(n), O(1), O(n))

Cada algoritmo tiene su propio archivo .cpp en el repositorio, y genera un archivo CSV con los tiempos de ejecución para distintos tamaños de entrada.

## Requisitos del Sistema:

Para compilar y ejecutar el proyecto, se debe asegurar de tener las siguientes bibliotecas en el sistema:

    GTK+ 3
    Cairo
    C++

## Generación de CSVs

Cada algoritmo tiene su propio archivo .cpp que genera un archivo CSV con los tiempos de ejecución. Es importante asegurarse de ejecutar cada algoritmo para generar sus respectivos CSVs antes de intentar visualizar los gráficos.

### Ejemplo de ejecución de un algoritmo:

Para ejecutar el Bubble Sort y generar su CSV

    cd BubbleSort
    g++  BubbleSort.cpp -o BubbleSort
    ./BubbleSort
  
Este comando generará el archivo bubble_sort_performance.csv en la carpeta correspondiente. Estos mismos comandos se aplican con los demas algoritmos, cambiandoles el nombre correspondiente
una vez compilado, se ejecuta el programa para generar los gráficos de rendimiento y ejecutar el main.cpp, se pueden utilizar los siguientes comandos:

    g++ -std=c++17 main.cpp -o graph `pkg-config --cflags --libs gtkmm-3.0 cairomm-1.0`
    ./graph

O el siguiente: 

    LD_PRELOAD=/lib/x86_64-linux-gnu/libpthread.so.0 ./graph
    
