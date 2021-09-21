#include <iostream>
#include <chrono>
#include <vector>
#include <fstream>
#include <locale.h>
#include <random>

#include "../lib/sorting.h"

/// Comparison function for the test experiment.
constexpr bool compare( const int&a, const int &b ){
    return ( a < b );
}

void print_unsorted(std::vector<size_type> &v) {
    std::cout << "Vetor desordenado: [ ";
    for (size_type i{0}; i < v.size(); i++) {
        std::cout << v[i] << " ";
    }
    std::cout << "]\n";
}

void print_sorted(std::vector<size_type> &v) {
    std::cout << "Vetor ordenado: [ ";
    for (size_type i{0}; i < v.size(); i++) {
        std::cout << v[i] << " ";
    }
    std::cout << "]\n";
    std::cout << "----------------------------------------------------------------------------------\n";
}

void sort_array(std::vector<size_type> &v) {
    //put your algorithm code here
    sa::quick(v.begin(), v.end(), compare);
}

int main(void) {
    size_type sz{20};
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(0, 1000);
    //std::vector<size_type> v1 = {7, 25, 47, 21, 4, 9, 3, 82, 1000, 200, 100};
    std::vector<size_type> v1 = {7, 25, 47, 21, 4, 25, 3, 82, 1000, 7, 100};
    std::vector<size_type> v2;
    std::vector<size_type> v3;
    std::vector<size_type> v4;

    for(size_type i{0}; i < sz; i++) {
        v2.push_back(distrib(gen));  //Generate number between 0 to 99
        v3.push_back(distrib(gen));
        v4.push_back(distrib(gen));
    }

    //put your algorithm name here
    std::cout << "Algoritmo Quick:\n";

    for (size_type i = 0; i < 4; i++) {
        if (i == 0) {
            print_unsorted(v1);
            sort_array(v1);
            print_sorted(v1);
        }
        else if (i == 1) {
            print_unsorted(v2);
            sort_array(v2);
            print_sorted(v2);
        }
        else if (i == 2) {
            print_unsorted(v3);
            sort_array(v3);
            print_sorted(v3);
        }
        else {
            print_unsorted(v4);
            sort_array(v4);
            print_sorted(v4);
        }
    }
    return 0;
}
