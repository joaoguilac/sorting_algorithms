/*!
 * This is a template code to demonstrate how to measure runtime of part of your code.
 * I'm using the chrono C++ library.
 * @date September 8th, 2020.
 * @author Selan
 */

#include <iostream>
#include <chrono>
#include <vector>
#include <fstream>
#include <locale.h>
#include <random>

#include "sorting.h"

//=== ALIASES
    
/// Data type we are working with.
using value_type = long int;
/// Size type.
using size_type = long int;
/// Alias for duration measure.
using duration_t = std::chrono::duration<double>;


//=== FUNCTION IMPLEMENTATION.

/// Print time different in an humam readable form.
void print_diff( const std::chrono::time_point<std::chrono::steady_clock> &start,
                 const std::chrono::time_point<std::chrono::steady_clock> &end ){
    auto diff = end - start;
    // Milliseconds (10^-3)
    std::cout << "\t\t>>> " << std::chrono::duration <double, std::milli> (diff).count() << " ms" << std::endl;
    // Nanoseconds (10^-9)
    std::cout << "\t\t>>> " << std::chrono::duration <double, std::nano> (diff).count() << " ns" << std::endl;
    // Seconds
    auto diff_sec = std::chrono::duration_cast<std::chrono::seconds>(diff);
    std::cout << "\t\t>>> " << diff_sec.count() << " s" << std::endl;
}

/// Comparison function for the test experiment.
constexpr bool compare( const int&a, const int &b ){
    return ( a < b );
}

//=== CONSTANT DEFINITIONS.

/// Number of runs we need to calculate the average runtime for a single algorithm.
constexpr short N_RUNS = 5;

//=== The main function, entry point.
int main( void )
{
    setlocale(LC_ALL, "Portuguese");
    int cycle{25};
    int current{1000};
    int max{100000};
    
    double sum{0};
    double average, super{0};
    std::vector<value_type> v;
    std::vector<value_type> vBackup;
    
    //===========================CALCULATE===================================================================
    std::ofstream file( "times/all_random.txt" );
    int stoped=0;
    while(current<=max){
        sum = 0;
        v.resize(current);

        //std::fill(v.begin(), v.end(), 0);
        
        for(value_type i{stoped};i<current;i++){
            v.push_back(i);
        }

        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();  
        shuffle (v.begin(),v.end(), std::default_random_engine(seed));

        for(int i{0};i<cycle;i++){
            //CALCULANDO TEMPO DO ALGORITMO
            auto start = std::chrono::steady_clock::now();
            sa::quick(v.begin(), v.end(), compare);
            auto end = std::chrono::steady_clock::now();
            std::chrono::duration<double> time = end - start;
            sum += std::chrono::duration <double, std::milli> (time).count();
        }

        average = sum/cycle;
        super += average;

        file << current << "\t" << average << std::endl;
        current += 4162;
    }
    //super /= 500;
    super /= cycle;

    file.close();
    //===========================BINARY SEARCH RECURSIVE=========================================================
    /*std::ofstream binaryRecT( "TimeBinaryRec.txt" );
    atual = 10000;
    while(atual<max){
        sum = 0;
        v.resize(atual);
        std::fill(v.begin(), v.end(), 0);
        for(int i{0};i<ciclo;i++){
            auto start = std::chrono::steady_clock::now();
            auto ptr = sa::binaryRec(&(v[0]),&v.back(),-2);
            auto end = std::chrono::steady_clock::now();
            //double time = double (std::chrono::duration_cast <std::chrono::milliseconds>(end-start).count());
            std::chrono::duration<double> time = end - start;
            sum += std::chrono::duration <double, std::milli> (time).count();
        }

        average = sum/ciclo;
        binaryRecT << atual << "\t" << average << std::endl;
        atual += 20000;
    }
    //===========================================================================================================
    binaria.close();
    binaryInt.close();
    binaryRecT.close();*/
}
