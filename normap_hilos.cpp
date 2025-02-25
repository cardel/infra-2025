/**
 * Carlos A Delgado S
 * 25 de Febrero de 2025
 * Ejemplo con hilos para resolver norma p
 */

#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <cmath>

using namespace std;
using namespace std::chrono;

const int SIZE = 100000000;
vector<long long> v(SIZE);

void llenar(int start, int end) {
    for (int i = start; i < end; i++) {
        v[i] = 10LL;
    }
}

void elevar_p(int start, int end, int p) {
    for (int i = start; i < end; i++) {
        v[i] = pow(v[i], p);
    }
}

void sumar(int start, int end, long long &sum) {
    for (int i = start; i < end; i++) {
        sum += v[i];
    }
}

int main() {
    //Tiempo secuencial
    auto start = system_clock::now();
    llenar(0, SIZE);
    elevar_p(0, SIZE, 4);
    long long sum = 0;
    sumar(0, SIZE, sum);
    auto end = system_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Tiempo secuencial: " << duration.count() << " ms" << endl;
    cout << "Norma 1: " << pow(sum, 1/4) << endl;

    //4 hilos
    start = system_clock::now();
    thread t1(llenar, 0, SIZE/4);
    thread t2(llenar, SIZE/4, SIZE/2);
    thread t3(llenar, SIZE/2, 3*SIZE/4);
    thread t4(llenar, 3*SIZE/4, SIZE);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    thread t5(elevar_p, 0, SIZE/4, 4);
    thread t6(elevar_p, SIZE/4, SIZE/2, 4);
    thread t7(elevar_p, SIZE/2, 3*SIZE/4, 4);
    thread t8(elevar_p, 3*SIZE/4, SIZE, 4);

    t5.join();
    t6.join();
    t7.join();
    t8.join();

    long long sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0;
    thread t9(sumar, 0, SIZE/4, ref(sum1));
    thread t10(sumar, SIZE/4, SIZE/2, ref(sum2));
    thread t11(sumar, SIZE/2, 3*SIZE/4, ref(sum3));
    thread t12(sumar, 3*SIZE/4, SIZE, ref(sum4));

    t9.join();
    t10.join();
    t11.join();
    t12.join();

    end = system_clock::now();
    duration = duration_cast<milliseconds>(end - start);
    cout << "Tiempo con 4 hilos: " << duration.count() << " ms" << endl;
    cout << "Norma 1: " << pow(sum1 + sum2 + sum3 + sum4, 1/4) << endl;

}