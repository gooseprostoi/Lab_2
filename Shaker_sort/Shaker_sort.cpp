#include <iostream>
#include <random>
using namespace std;
// #define NDEBUG;
#include <cassert>

using U = unsigned;

// функция проверки упорядоченности массива
template <typename T>
bool is_sorted(T arr[], U const begin_idx, U const end_idx) {
    bool sorted = true;
    for (U idx = begin_idx; idx != end_idx; idx++) {
        if (arr[idx] > arr[idx + 1]) {
            sorted = false;
        }
    }
    return sorted;
}


// прямой проход
bool forward_step(U arr[], U const begin_idx, U const end_idx) {
    bool sorted = true;
    for (U idx = begin_idx; idx != end_idx; ++idx) {
        if (arr[idx] > arr[idx + 1]) {
            auto tmp = arr[idx];
            arr[idx] = arr[idx + 1];
            arr[idx + 1] = tmp;
            sorted = false;
        }
    }
    return sorted;
}


// обратный проход
bool backward_step(U arr[], U const begin_idx, U const end_idx) {
    bool sorted = true;
    for (U idx = end_idx - 1; idx != begin_idx - 1; --idx) {
        if (arr[idx] > arr[idx + 1]) {
            auto tmp = arr[idx];
            arr[idx] = arr[idx + 1];
            arr[idx + 1] = tmp;
            sorted = false;
        }
    }
    return sorted;
}


// шейкерская сортировки с использованием прямого и обратного проходов
void shaker_sort(U arr[], U const begin_idx, U const end_idx) {
    bool sorted = false;
    while (!sorted) {
        sorted = forward_step(arr, begin_idx, end_idx);
        sorted = backward_step(arr, begin_idx, end_idx);
    }
    assert(is_sorted(arr, begin_idx, end_idx));
}



int main()
{
    // проверка шейкерской сортировки на различных случайно сгенерированных массивах
    for (int N = 1000; N < 10000; N += 1000) {
        // создаём массив из N случайных чисел от 0 до MAX_RAND
        U* A = new U[N];
        unsigned int seed = rand();
        default_random_engine rng(seed);
        U const MAX_RAND = 1000000;
        uniform_int_distribution<unsigned> dstr(0, MAX_RAND);
        for (int i = 0; i < N; i++) {
            A[i] = dstr(rng);
        }

        // сортируем шейкерской сортировкой, если сортировка неудачная, то программа выдаст ошибку
        shaker_sort(A, 0, N - 1);

        delete[] A;
    }
}