/**
 * Carlos A Delgado S
 * 25 de Febrero de 2025
 * Ejemplo con tbb para resolver norma p
 */

#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>
#include <tbb/tbb.h>
#include <tbb/parallel_for.h>
#include <tbb/blocked_range.h>

using namespace std;
using namespace std::chrono;
using namespace tbb;


const int SIZE = 100000000;
vector<long long> v(SIZE);

void llenar(int start, int end) {
    for (int i = start; i < end; i++) {
        v[i] = 10LL;
    }
}

void elevar_p(int start, int end, int p) {
    parallel_for(blocked_range<int>(start, end), [&](blocked_range<int> r) {
        for (int i = r.begin(); i < r.end(); i++) {
            v[i] = pow(v[i], p);
        }
    });
}

void sumar(int start, int end, long long &sum) {
     parallel_reduce(blocked_range<int>(start, end), 0LL, [&](blocked_range<int> r, long long init) -> long long {
        long long sum = init;
        for (int i = r.begin(); i < r.end(); i++) {
            sum += v[i];
        }
        return sum;
    }, std::plus<long long>());
}

int main() {
    auto start = chrono::system_clock::now();
    llenar(0, SIZE);

    // Elevar a la 4
    start = chrono::system_clock::now();
    elevar_p(0, SIZE, 4);

    long long sum = 0;
    sumar(0, SIZE, sum);

    auto end = chrono::system_clock::now();
    //Tiempo milisegundos
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Tiempo de ejecución: " << duration.count() << " ms" << endl;
    cout << "Norma p: " << sum << endl;

}

    