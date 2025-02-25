/**
 * Carlos Andres Delgado S
 * 25 de Febrero de 2025
 * Ejemplo con thread
 */
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

using namespace std;
using namespace std::chrono;

const int SIZE = 100000000;

vector<long> v(SIZE);

void fill(int start, int end) {
    for (int i = start; i < end; i++) {
        v[i] = i;
    }
}

long suma(int start, int end) {
    long sum = 0;
    for (int i = start; i < end; i++) {
        sum += v[i];
    }
    return sum;
}

void sumaPro(int start, int end, long &sum) {
    for (int i = start; i < end; i++) {
        sum += v[i];
    }
}

int main() {
    fill(0, SIZE);
    
    auto start = chrono::system_clock::now();
    long sum = suma(0, SIZE);
    auto stop = chrono::system_clock::now();
    //Duración en milisegundos
    auto duration = duration_cast<milliseconds>(stop - start);
    printf("Tiempo de ejecución: %ldms\n", duration.count());
    printf("Suma: %ld\n", sum);

    //>Vamos a hacerlo con hilo suma
    start = chrono::system_clock::now();
    long sum1 = 0, sum2 = 0;
    thread t1([&sum1](){sum1 = suma(0, SIZE/2);});  
    thread t2([&sum2](){sum2 = suma(SIZE/2, SIZE);});
    t1.join();
    t2.join();
    stop = chrono::system_clock::now();
    //Duración en milisegundos
    duration = duration_cast<milliseconds>(stop - start);
    printf("Tiempo de ejecución: %ldms\n", duration.count());
    printf("Suma: %ld\n", sum1 + sum2);

    //Vamos a hacerlo con 4 hilos
    start = chrono::system_clock::now();
    long sum3 = 0, sum4 = 0, sum5 = 0, sum6 = 0;
    thread t3([&sum3](){sum3 = suma(0, SIZE/4);});
    thread t4([&sum4](){sum4 = suma(SIZE/4, SIZE/2);});
    thread t5([&sum5](){sum5 = suma(SIZE/2, 3*SIZE/4);});
    thread t6([&sum6](){sum6 = suma(3*SIZE/4, SIZE);});
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    stop = chrono::system_clock::now();
    //Duración en milisegundos
    duration = duration_cast<milliseconds>(stop - start);
    printf("Tiempo de ejecución: %ldms\n", duration.count());
    printf("Suma: %ld\n", sum3 + sum4 + sum5 + sum6);

    //Dos hilos para sumaPro
    start = chrono::system_clock::now();
    long sum7 = 0, sum8 = 0;
    thread t7(sumaPro, 0, SIZE/2, ref(sum7));
    thread t8(sumaPro, SIZE/2, SIZE, ref(sum8));
    t7.join();
    t8.join();
    stop = chrono::system_clock::now();
    //Duración en milisegundos
    duration = duration_cast<milliseconds>(stop - start);
    printf("Tiempo de ejecución: %ldms\n", duration.count());
    printf("Suma: %ld\n", sum7 + sum8);
    

}