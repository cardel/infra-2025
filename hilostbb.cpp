/**
 * Carlos Andres Delgado S
 * 25 de Febrero de 2025
 * Ejemplo con tbb
 */

#include <iostream>
#include <tbb/parallel_for.h>
#include <tbb/blocked_range.h>
#include <tbb/parallel_reduce.h>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;


const int SIZE = 100000000;
vector<long> v(SIZE);

void fill(int start, int end) {
    for (int i = start; i < end; i++) {
        v[i] = i;
    }
}

void filltbb(int start, int end) {
    tbb::parallel_for(tbb::blocked_range<int>(start, end), [&](tbb::blocked_range<int> r) {
        for (int i = r.begin(); i < r.end(); i++) {
            v[i] = i;
        }
    });
}

void sumaSec(int start, int end, long &sum) {
    for (int i = start; i < end; i++) {
        sum += v[i];
    }
}

void sumaTBB(int start, int end, long &sum) {
    sum = tbb::parallel_reduce(tbb::blocked_range<int>(start, end), 0L, [&](tbb::blocked_range<int> r, long init) {
        long sum = init;
        for (int i = r.begin(); i < r.end(); i++) {
            sum += v[i];
        }
        return sum;
    },std::plus<long>());
}
/*
,
        [](long x, long y) -> long {
            return x + y;
        });
*/

int main() {
    //Tiempo llenado de ejecución secuencial
    auto start = chrono::system_clock::now();
    filltbb(0, SIZE);
    auto stop = chrono::system_clock::now();
    //Duración en milisegundos
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    printf("Tiempo llenado de ejecución secuencial: %ldms\n", duration.count());

    //Tiempo llenado de ejecución paralela
    start = chrono::system_clock::now();
    filltbb(0, SIZE);
    stop = chrono::system_clock::now();
    //Duración en milisegundos
    duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    printf("Tiempo llenado de ejecución paralela: %ldms\n", duration.count());

    //Tiempo de suma secuencial
    start = chrono::system_clock::now();
    long sum = 0;
    sumaSec(0, SIZE, ref(sum));
    stop = chrono::system_clock::now();
    //Duración en milisegundos
    duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    printf("Tiempo de suma secuencial: %ldms\n", duration.count());
    printf("Suma: %ld\n", sum);

    //Tiempo de suma paralela
    sum = 0;
    start = chrono::system_clock::now();
    sumaTBB(0, SIZE, ref(sum));
    stop = chrono::system_clock::now();
    //Duración en milisegundos 
    duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    printf("Tiempo de suma paralela: %ldms\n", duration.count());
    printf("Suma: %ld\n", sum);
    

}
