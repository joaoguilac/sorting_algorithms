/*!
 * @file main.cpp
 * Benchmarking suit to compare sorting algorithms under verios situations.
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include <string>
#include <cassert>  
#include <algorithm>
#include <functional>
#include <string.h>
#include <random>

using std::function;

#include "lib/sorting.h"

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

/// The running options
struct RunningOpt{
    size_t min_sample_sz{1000};   //!< Default 10^3.
    size_t max_sample_sz{100000}; //!< The max sample size.
    int n_samples{25};            //!< The number of samples to collect.
    short which_algs{0};          //!< Bit code for the chosen algorithms to run.
    short which_scenarios{1};     //!< Bit code for the chosen scenarios to run.

    /// Returns the sample size step, based on the [min,max] sample sizes and # of samples.
    size_type sample_step(void){
        return static_cast<float>(max_sample_sz-min_sample_sz)/(n_samples-1);
    }
};

/// Comparison function for the test experiment.
constexpr bool compare( const int&a, const int &b ){
    return ( a < b );
}

//=== CONSTANT DEFINITIONS.

/// Number of runs we need to calculate the average runtime for a single algorithm.
constexpr short N_RUNS = 5;

//=== The main function, entry point.
int main( int argc, char * argv[] ){
    setlocale(LC_ALL, "Portuguese");
    int ciclo{5};
    int atual{400};
    int max{10000};
    
    // CENARIO 1
    std::ofstream arquivo1( "source/times/non_increasing.txt" );
    if (not arquivo1.is_open())
    {
        // Print an error and exit.
        std::cout << "NÃO ABRIU!\n";
        exit(1);
    }
    std::cout << ">>>>>>>>>>>>>>>>> COMEÇOU [NÃO CRESCENTE]\n\n";
    std::vector <int> sorting;
    std::vector <int> backup;
    std::vector<int> i;

    double sum[7];
    double average[7];
    double answer[7];
    
    int index = 1;
    while(atual<=max){
        std::cout << "============================ CICLO "<<index<<"/"<<(max/400)<<" =============================\n";
        for(int i{0};i<7;i++){
            sum[i] = 0;
            average[i] = 0;
        }

        sorting.resize(0);
        backup.resize(0);

        for(int i{atual};i>0;i--){
            sorting.push_back(i);
            backup.push_back(i);
        }
        
        
        std::cout << "Insertion: ";
        for(int i{0};i<ciclo;i++){
            //CALCULANDO TEMPO DO ALGORITMO
            std::cout << i << std::flush << " ";
            auto start1 = std::chrono::steady_clock::now();
            sa::insertion(sorting.begin(), sorting.end(), compare);
            auto end1 = std::chrono::steady_clock::now();
            std::chrono::duration<double> time1 = end1 - start1;
            sum[0] += std::chrono::duration <double, std::milli> (time1).count();
            sorting = backup;
        }

        std::cout << std::endl;

        std::cout << "Selection: ";
        for(int i{0};i<ciclo;i++){
            //CALCULANDO TEMPO DO ALGORITMO
            std::cout << i << std::flush << " ";
            auto start2 = std::chrono::steady_clock::now();
            sa::selection(sorting.begin(), sorting.end(), compare);
            auto end2 = std::chrono::steady_clock::now();
            std::chrono::duration<double> time2 = end2 - start2;
            sum[1] += std::chrono::duration <double, std::milli> (time2).count();
            sorting = backup;
        }
        std::cout << std::endl;

        std::cout << "Bubble: ";
        for(int i{0};i<ciclo;i++){
            //CALCULANDO TEMPO DO ALGORITMO
            std::cout << i << std::flush << " ";
            auto start3 = std::chrono::steady_clock::now();
            sa::bubble(sorting.begin(), sorting.end(), compare);
            auto end3 = std::chrono::steady_clock::now();
            std::chrono::duration<double> time3 = end3 - start3;
            sum[2] += std::chrono::duration <double, std::milli> (time3).count();
            sorting = backup;
        }
        std::cout << std::endl;

        std::cout << "Shell: ";
        for(int i{0};i<ciclo;i++){
            //CALCULANDO TEMPO DO ALGORITMO
            std::cout << i << std::flush << " ";
            auto start4 = std::chrono::steady_clock::now();
            sa::shell(sorting.begin(), sorting.end(), compare);
            auto end4 = std::chrono::steady_clock::now();
            std::chrono::duration<double> time4 = end4 - start4;
            sum[3] += std::chrono::duration <double, std::milli> (time4).count();
            sorting = backup;
        }
        std::cout << std::endl;

        std::cout << "Merge: ";
        for(int i{0};i<ciclo;i++){
            //CALCULANDO TEMPO DO ALGORITMO
            std::cout << i << std::flush << " ";
            auto start5 = std::chrono::steady_clock::now();
            sa::merge(sorting.begin(), sorting.end(), compare);
            auto end5 = std::chrono::steady_clock::now();
            std::chrono::duration<double> time5 = end5 - start5;
            sum[4] += std::chrono::duration <double, std::milli> (time5).count();
            sorting = backup;
        }
        std::cout << std::endl;
        
        std::cout << "Quick: ";
        for(int i{0};i<ciclo;i++){
            //CALCULANDO TEMPO DO ALGORITMO
            std::cout << i << std::flush << " ";
            auto start6 = std::chrono::steady_clock::now();
            sa::quick(sorting.begin(), sorting.end(), compare);
            auto end6 = std::chrono::steady_clock::now();
            std::chrono::duration<double> time6 = end6 - start6;
            sum[5] += std::chrono::duration <double, std::milli> (time6).count();
            sorting = backup;
        }
        std::cout << std::endl;

        std::cout << "Radix: ";
        for(int i{0};i<ciclo;i++){
            //CALCULANDO TEMPO DO ALGORITMO
            std::cout << i << std::flush << " ";
            auto start7 = std::chrono::steady_clock::now();
            sa::radix(sorting.begin(), sorting.end(), compare);
            auto end7 = std::chrono::steady_clock::now();
            std::chrono::duration<double> time7 = end7 - start7;
            sum[6] += std::chrono::duration <double, std::milli> (time7).count();
            sorting = backup;
        }
        std::cout << std::endl;

        for(int i{0};i<7;i++){
            average[i] = sum[i]/ciclo;
            answer[i] += average[i];
        }

        arquivo1 << atual;
        for(int i{0};i<7;i++){
            arquivo1 << "\t" << average[i] << "\t\t";
        }
        arquivo1 << std::endl;

        atual += 400;
        index++;
    }
    std::cout << "\n>>>>>>>>>>>>>>>>> TERMINOU\n\n";
    arquivo1.close();
    
    // CENARIO 2
    std::ofstream arquivo2( "source/times/non_decreasing.txt" );
    std::cout << ">>>>>>>>>>>>>>>>> COMEÇOU [NÃO DECRESCENTE]\n\n";
    index = 1;
    atual = 400;
    while(atual<=max){
        std::cout << "============================ CICLO "<<index<<"/"<<(max/400)<<" =============================\n";
        for(int i{0};i<7;i++){
            sum[i] = 0;
            average[i] = 0;
        }

        sorting.resize(0);
        backup.resize(0);

        for(int i{0};i<atual;i++){
            sorting.push_back(i);
            backup.push_back(i);
        }

        std::cout << "Insertion: ";
        for(int i{0};i<ciclo;i++){
            //CALCULANDO TEMPO DO ALGORITMO
            std::cout << i << std::flush << " ";
            auto start8 = std::chrono::steady_clock::now();
            sa::insertion(sorting.begin(), sorting.end(), compare);
            auto end8 = std::chrono::steady_clock::now();
            std::chrono::duration<double> time8 = end8 - start8;
            sum[0] += std::chrono::duration <double, std::milli> (time8).count();
            sorting = backup;
        }

        std::cout << std::endl;

        std::cout << "Selection: ";
        for(int i{0};i<ciclo;i++){
            //CALCULANDO TEMPO DO ALGORITMO
            std::cout << i << std::flush << " ";
            auto start9 = std::chrono::steady_clock::now();
            sa::selection(sorting.begin(), sorting.end(), compare);
            auto end9 = std::chrono::steady_clock::now();
            std::chrono::duration<double> time9 = end9 - start9;
            sum[1] += std::chrono::duration <double, std::milli> (time9).count();
            sorting = backup;
        }
        std::cout << std::endl;

        std::cout << "Bubble: ";
        for(int i{0};i<ciclo;i++){
            //CALCULANDO TEMPO DO ALGORITMO
            std::cout << i << std::flush << " ";
            auto start10 = std::chrono::steady_clock::now();
            sa::bubble(sorting.begin(), sorting.end(), compare);
            auto end10 = std::chrono::steady_clock::now();
            std::chrono::duration<double> time10 = end10 - start10;
            sum[2] += std::chrono::duration <double, std::milli> (time10).count();
            sorting = backup;
        }
        std::cout << std::endl;

        std::cout << "Shell: ";
        for(int i{0};i<ciclo;i++){
            //CALCULANDO TEMPO DO ALGORITMO
            std::cout << i << std::flush << " ";
            auto start11 = std::chrono::steady_clock::now();
            sa::shell(sorting.begin(), sorting.end(), compare);
            auto end11 = std::chrono::steady_clock::now();
            std::chrono::duration<double> time11 = end11 - start11;
            sum[3] += std::chrono::duration <double, std::milli> (time11).count();
            sorting = backup;
        }
        std::cout << std::endl;

        std::cout << "Merge: ";
        for(int i{0};i<ciclo;i++){
            //CALCULANDO TEMPO DO ALGORITMO
            std::cout << i << std::flush << " ";
            auto start12 = std::chrono::steady_clock::now();
            sa::merge(sorting.begin(), sorting.end(), compare);
            auto end12= std::chrono::steady_clock::now();
            std::chrono::duration<double> time12= end12 - start12;
            sum[4] += std::chrono::duration <double, std::milli> (time12).count();
            sorting = backup;
        }
        std::cout << std::endl;
        
        std::cout << "Quick: ";
        for(int i{0};i<ciclo;i++){
            //CALCULANDO TEMPO DO ALGORITMO
            std::cout << i << std::flush << " ";
            auto start13 = std::chrono::steady_clock::now();
            sa::quick(sorting.begin(), sorting.end(), compare);
            auto end13 = std::chrono::steady_clock::now();
            std::chrono::duration<double> time13 = end13- start13;
            sum[5] += std::chrono::duration <double, std::milli> (time13).count();
            sorting = backup;
        }
        std::cout << std::endl;

        std::cout << "Radix: ";
        for(int i{0};i<ciclo;i++){
            //CALCULANDO TEMPO DO ALGORITMO
            std::cout << i << std::flush << " ";
            auto start14= std::chrono::steady_clock::now();
            sa::radix(sorting.begin(), sorting.end(), compare);
            auto end14 = std::chrono::steady_clock::now();
            std::chrono::duration<double> time14 = end14 - start14;
            sum[6] += std::chrono::duration <double, std::milli> (time14).count();
            sorting = backup;
        }
        std::cout << std::endl;

        for(int i{0};i<7;i++){
            average[i] = sum[i]/ciclo;
            answer[i] += average[i];
        }

        arquivo2 << atual;
        for(int i{0};i<7;i++){
            arquivo2 << "\t" << average[i] << "\t\t";
        }
        arquivo2 << std::endl;

        atual += 400;
        index++;
    }
    std::cout << "\n>>>>>>>>>>>>>>>>> TERMINOU\n\n";
    arquivo2.close();
    
    // CENARIO 3
    std::ofstream arquivo3( "source/times/all_random.txt" );
    std::cout << ">>>>>>>>>>>>>>>>> COMEÇOU [100/100 ALEATÓRIO]\n\n";
    index = 1;
    atual = 400;
    while(atual<=max){
        std::cout << "============================ CICLO "<<index<<"/"<<(max/400)<<" =============================\n";
        for(int i{0};i<7;i++){
            sum[i] = 0;
            average[i] = 0;
        }

        sorting.resize(0);
        backup.resize(0);

        for(int i{0};i<atual;i++){
            sorting.push_back(i);
            backup.push_back(i);
        }
        
        unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();  
        shuffle(sorting.begin(),sorting.end(), std::default_random_engine(seed1));
        shuffle(backup.begin(),backup.end(), std::default_random_engine(seed1));

        std::cout << "Insertion: ";
        for(int i{0};i<ciclo;i++){
            //CALCULANDO TEMPO DO ALGORITMO
            std::cout << i << std::flush << " ";
            auto start8 = std::chrono::steady_clock::now();
            sa::insertion(sorting.begin(), sorting.end(), compare);
            auto end8 = std::chrono::steady_clock::now();
            std::chrono::duration<double> time8 = end8 - start8;
            sum[0] += std::chrono::duration <double, std::milli> (time8).count();
            sorting = backup;
        }

        std::cout << std::endl;

        std::cout << "Selection: ";
        for(int i{0};i<ciclo;i++){
            //CALCULANDO TEMPO DO ALGORITMO
            std::cout << i << std::flush << " ";
            auto start9 = std::chrono::steady_clock::now();
            sa::selection(sorting.begin(), sorting.end(), compare);
            auto end9 = std::chrono::steady_clock::now();
            std::chrono::duration<double> time9 = end9 - start9;
            sum[1] += std::chrono::duration <double, std::milli> (time9).count();
            sorting = backup;
        }
        std::cout << std::endl;

        std::cout << "Bubble: ";
        for(int i{0};i<ciclo;i++){
            //CALCULANDO TEMPO DO ALGORITMO
            std::cout << i << std::flush << " ";
            auto start10 = std::chrono::steady_clock::now();
            sa::bubble(sorting.begin(), sorting.end(), compare);
            auto end10 = std::chrono::steady_clock::now();
            std::chrono::duration<double> time10 = end10 - start10;
            sum[2] += std::chrono::duration <double, std::milli> (time10).count();
            sorting = backup;
        }
        std::cout << std::endl;

        std::cout << "Shell: ";
        for(int i{0};i<ciclo;i++){
            //CALCULANDO TEMPO DO ALGORITMO
            std::cout << i << std::flush << " ";
            auto start11 = std::chrono::steady_clock::now();
            sa::shell(sorting.begin(), sorting.end(), compare);
            auto end11 = std::chrono::steady_clock::now();
            std::chrono::duration<double> time11 = end11 - start11;
            sum[3] += std::chrono::duration <double, std::milli> (time11).count();
            sorting = backup;
        }
        std::cout << std::endl;

        std::cout << "Merge: ";
        for(int i{0};i<ciclo;i++){
            //CALCULANDO TEMPO DO ALGORITMO
            std::cout << i << std::flush << " ";
            auto start12 = std::chrono::steady_clock::now();
            sa::merge(sorting.begin(), sorting.end(), compare);
            auto end12= std::chrono::steady_clock::now();
            std::chrono::duration<double> time12= end12 - start12;
            sum[4] += std::chrono::duration <double, std::milli> (time12).count();
            sorting = backup;
        }
        std::cout << std::endl;
        
        std::cout << "Quick: ";
        for(int i{0};i<ciclo;i++){
            //CALCULANDO TEMPO DO ALGORITMO
            std::cout << i << std::flush << " ";
            auto start13 = std::chrono::steady_clock::now();
            sa::quick(sorting.begin(), sorting.end(), compare);
            auto end13 = std::chrono::steady_clock::now();
            std::chrono::duration<double> time13 = end13- start13;
            sum[5] += std::chrono::duration <double, std::milli> (time13).count();
            sorting = backup;
        }
        std::cout << std::endl;

        std::cout << "Radix: ";
        for(int i{0};i<ciclo;i++){
            //CALCULANDO TEMPO DO ALGORITMO
            std::cout << i << std::flush << " ";
            auto start14= std::chrono::steady_clock::now();
            sa::radix(sorting.begin(), sorting.end(), compare);
            auto end14 = std::chrono::steady_clock::now();
            std::chrono::duration<double> time14 = end14 - start14;
            sum[6] += std::chrono::duration <double, std::milli> (time14).count();
            sorting = backup;
        }
        std::cout << std::endl;

        for(int i{0};i<7;i++){
            average[i] = sum[i]/ciclo;
            answer[i] += average[i];
        }

        arquivo3 << atual;
        for(int i{0};i<7;i++){
            arquivo3 << "\t" << average[i] << "\t\t";
        }
        arquivo3 << std::endl;

        atual += 400;
        index++;
    }
    std::cout << "\n>>>>>>>>>>>>>>>>> TERMINOU\n\n";
    arquivo3.close();

    // CENARIO 4
    std::ofstream arquivo4( "source/times/sorted75.txt" );
    std::cout << ">>>>>>>>>>>>>>>>> COMEÇOU [75/100 ORDENADO]\n\n";
    index = 1;
    atual = 400;
    while(atual<=max){
        std::cout << "============================ CICLO "<<index<<"/"<<(max/400)<<" =============================\n";
        for(int j{0};j<7;j++){
            sum[j] = 0;
            average[j] = 0;
        }

        sorting.resize(0);
        backup.resize(0);
        i.resize(0);
        

        for(int j{0};j<atual;j++){
            sorting.push_back(j);
            backup.push_back(j);
        }

        
        for(int j{0};j<atual;j++){
            i.push_back(j);
        }

        unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count(); 

        shuffle(i.begin(),i.end(), std::default_random_engine(seed1));        

        //SWAP THREE TIMES
        for(int j{0};j<=(atual/4);j+=2){
            std::swap(sorting[i[j]],sorting[i[j+1]]);
            std::swap(backup[i[j]],backup[i[j+1]]);
        }

        std::cout << "Insertion: ";
        for(int i{0};i<ciclo;i++){
            //CALCULANDO TEMPO DO ALGORITMO
            std::cout << i << std::flush << " ";
            auto start8 = std::chrono::steady_clock::now();
            sa::insertion(sorting.begin(), sorting.end(), compare);
            auto end8 = std::chrono::steady_clock::now();
            std::chrono::duration<double> time8 = end8 - start8;
            sum[0] += std::chrono::duration <double, std::milli> (time8).count();
            sorting = backup;
        }

        std::cout << std::endl;

        std::cout << "Selection: ";
        for(int i{0};i<ciclo;i++){
            //CALCULANDO TEMPO DO ALGORITMO
            std::cout << i << std::flush << " ";
            auto start9 = std::chrono::steady_clock::now();
            sa::selection(sorting.begin(), sorting.end(), compare);
            auto end9 = std::chrono::steady_clock::now();
            std::chrono::duration<double> time9 = end9 - start9;
            sum[1] += std::chrono::duration <double, std::milli> (time9).count();
            sorting = backup;
        }
        std::cout << std::endl;

        std::cout << "Bubble: ";
        for(int i{0};i<ciclo;i++){
            //CALCULANDO TEMPO DO ALGORITMO
            std::cout << i << std::flush << " ";
            auto start10 = std::chrono::steady_clock::now();
            sa::bubble(sorting.begin(), sorting.end(), compare);
            auto end10 = std::chrono::steady_clock::now();
            std::chrono::duration<double> time10 = end10 - start10;
            sum[2] += std::chrono::duration <double, std::milli> (time10).count();
            sorting = backup;
        }
        std::cout << std::endl;

        std::cout << "Shell: ";
        for(int i{0};i<ciclo;i++){
            //CALCULANDO TEMPO DO ALGORITMO
            std::cout << i << std::flush << " ";
            auto start11 = std::chrono::steady_clock::now();
            sa::shell(sorting.begin(), sorting.end(), compare);
            auto end11 = std::chrono::steady_clock::now();
            std::chrono::duration<double> time11 = end11 - start11;
            sum[3] += std::chrono::duration <double, std::milli> (time11).count();
            sorting = backup;
        }
        std::cout << std::endl;

        std::cout << "Merge: ";
        for(int i{0};i<ciclo;i++){
            //CALCULANDO TEMPO DO ALGORITMO
            std::cout << i << std::flush << " ";
            auto start12 = std::chrono::steady_clock::now();
            sa::merge(sorting.begin(), sorting.end(), compare);
            auto end12= std::chrono::steady_clock::now();
            std::chrono::duration<double> time12= end12 - start12;
            sum[4] += std::chrono::duration <double, std::milli> (time12).count();
            sorting = backup;
        }
        std::cout << std::endl;
        
        std::cout << "Quick: ";
        for(int i{0};i<ciclo;i++){
            //CALCULANDO TEMPO DO ALGORITMO
            std::cout << i << std::flush << " ";
            auto start13 = std::chrono::steady_clock::now();
            sa::quick(sorting.begin(), sorting.end(), compare);
            auto end13 = std::chrono::steady_clock::now();
            std::chrono::duration<double> time13 = end13- start13;
            sum[5] += std::chrono::duration <double, std::milli> (time13).count();
            sorting = backup;
        }
        std::cout << std::endl;

        std::cout << "Radix: ";
        for(int i{0};i<ciclo;i++){
            //CALCULANDO TEMPO DO ALGORITMO
            std::cout << i << std::flush << " ";
            auto start14= std::chrono::steady_clock::now();
            sa::radix(sorting.begin(), sorting.end(), compare);
            auto end14 = std::chrono::steady_clock::now();
            std::chrono::duration<double> time14 = end14 - start14;
            sum[6] += std::chrono::duration <double, std::milli> (time14).count();
            sorting = backup;
        }
        std::cout << std::endl;

        for(int i{0};i<7;i++){
            average[i] = sum[i]/ciclo;
            answer[i] += average[i];
        }

        arquivo4 << atual;
        for(int i{0};i<7;i++){
            arquivo4 << "\t" << average[i] << "\t\t";
        }
        arquivo4 << std::endl;

        atual += 400;
        index++;
    }
    std::cout << "\n>>>>>>>>>>>>>>>>> TERMINOU\n\n";
    arquivo4.close();
    
    // CENARIO 5
    std::ofstream arquivo5( "source/times/sorted50.txt" );
    std::cout << ">>>>>>>>>>>>>>>>> COMEÇOU [50/100 ORDENADO]\n\n";
    index = 1;
    atual = 400;
    while(atual<=max){
        std::cout << "============================ CICLO "<<index<<"/"<<(max/400)<<" =============================\n";
        for(int j{0};j<7;j++){
            sum[j] = 0;
            average[j] = 0;
        }

        sorting.resize(0);
        backup.resize(0);
        i.resize(0);
        

        for(int j{0};j<atual;j++){
            sorting.push_back(j);
            backup.push_back(j);
        }

        
        for(int j{0};j<atual;j++){
            i.push_back(j);
        }

        unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count(); 

        shuffle(i.begin(),i.end(), std::default_random_engine(seed1));        

        for(int j{0};j<=(atual/2);j+=2){
            std::swap(sorting[i[j]],sorting[i[j+1]]);
            std::swap(backup[i[j]],backup[i[j+1]]);
        }

        std::cout << "Insertion: ";
        for(int i{0};i<ciclo;i++){
            //CALCULANDO TEMPO DO ALGORITMO
            std::cout << i << std::flush << " ";
            std::cout << "]\n\n";
            auto start8 = std::chrono::steady_clock::now();
            sa::insertion(sorting.begin(), sorting.end(), compare);
            auto end8 = std::chrono::steady_clock::now();
            std::chrono::duration<double> time8 = end8 - start8;
            sum[0] += std::chrono::duration <double, std::milli> (time8).count();
            sorting = backup;
        }

        std::cout << std::endl;

        std::cout << "Selection: ";
        for(int i{0};i<ciclo;i++){
            //CALCULANDO TEMPO DO ALGORITMO
            std::cout << i << std::flush << " ";
            auto start9 = std::chrono::steady_clock::now();
            sa::selection(sorting.begin(), sorting.end(), compare);
            auto end9 = std::chrono::steady_clock::now();
            std::chrono::duration<double> time9 = end9 - start9;
            sum[1] += std::chrono::duration <double, std::milli> (time9).count();
            sorting = backup;
        }
        std::cout << std::endl;

        std::cout << "Bubble: ";
        for(int i{0};i<ciclo;i++){
            //CALCULANDO TEMPO DO ALGORITMO
            std::cout << i << std::flush << " ";
            auto start10 = std::chrono::steady_clock::now();
            sa::bubble(sorting.begin(), sorting.end(), compare);
            auto end10 = std::chrono::steady_clock::now();
            std::chrono::duration<double> time10 = end10 - start10;
            sum[2] += std::chrono::duration <double, std::milli> (time10).count();
            sorting = backup;
        }
        std::cout << std::endl;

        std::cout << "Shell: ";
        for(int i{0};i<ciclo;i++){
            //CALCULANDO TEMPO DO ALGORITMO
            std::cout << i << std::flush << " ";
            auto start11 = std::chrono::steady_clock::now();
            sa::shell(sorting.begin(), sorting.end(), compare);
            auto end11 = std::chrono::steady_clock::now();
            std::chrono::duration<double> time11 = end11 - start11;
            sum[3] += std::chrono::duration <double, std::milli> (time11).count();
            sorting = backup;
        }
        std::cout << std::endl;

        std::cout << "Merge: ";
        for(int i{0};i<ciclo;i++){
            //CALCULANDO TEMPO DO ALGORITMO
            std::cout << i << std::flush << " ";
            auto start12 = std::chrono::steady_clock::now();
            sa::merge(sorting.begin(), sorting.end(), compare);
            auto end12= std::chrono::steady_clock::now();
            std::chrono::duration<double> time12= end12 - start12;
            sum[4] += std::chrono::duration <double, std::milli> (time12).count();
            sorting = backup;
        }
        std::cout << std::endl;
        
        std::cout << "Quick: ";
        for(int i{0};i<ciclo;i++){
            //CALCULANDO TEMPO DO ALGORITMO
            std::cout << i << std::flush << " ";
            auto start13 = std::chrono::steady_clock::now();
            sa::quick(sorting.begin(), sorting.end(), compare);
            auto end13 = std::chrono::steady_clock::now();
            std::chrono::duration<double> time13 = end13- start13;
            sum[5] += std::chrono::duration <double, std::milli> (time13).count();
            sorting = backup;
        }
        std::cout << std::endl;

        std::cout << "Radix: ";
        for(int i{0};i<ciclo;i++){
            //CALCULANDO TEMPO DO ALGORITMO
            std::cout << i << std::flush << " ";
            auto start14= std::chrono::steady_clock::now();
            sa::radix(sorting.begin(), sorting.end(), compare);
            auto end14 = std::chrono::steady_clock::now();
            std::chrono::duration<double> time14 = end14 - start14;
            sum[6] += std::chrono::duration <double, std::milli> (time14).count();
            sorting = backup;
        }
        std::cout << std::endl;

        for(int i{0};i<7;i++){
            average[i] = sum[i]/ciclo;
            answer[i] += average[i];
        }

        arquivo5 << atual;
        for(int i{0};i<7;i++){
            arquivo5 << "\t" << average[i] << "\t\t";
        }
        arquivo5 << std::endl;

        atual += 400;
        index++;
    }
    std::cout << "\n>>>>>>>>>>>>>>>>> TERMINOU\n\n";
    arquivo5.close();
    
    // CENARIO 6
    std::ofstream arquivo6( "source/times/sorted25.txt" );
    std::cout << ">>>>>>>>>>>>>>>>> COMEÇOU [25/100 ORDENADO]\n\n";
    index = 1;
    atual = 400;
    while(atual<=max){
        std::cout << "============================ CICLO "<<index<<"/"<<(max/400)<<" =============================\n";
        for(int j{0};j<7;j++){
            sum[j] = 0;
            average[j] = 0;
        }

        sorting.resize(0);
        backup.resize(0);
        i.resize(0);
        

        for(int j{0};j<atual;j++){
            sorting.push_back(j);
            backup.push_back(j);
        }

        
        for(int j{0};j<atual;j++){
            i.push_back(j);
        }

        unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count(); 

        shuffle(i.begin(),i.end(), std::default_random_engine(seed1));        

        for(int j{0};j<=((atual*3)/4);j+=2){
            std::swap(sorting[i[j]],sorting[i[j+1]]);
            std::swap(backup[i[j]],backup[i[j+1]]);
        }

        std::cout << "Insertion: ";
        for(int i{0};i<ciclo;i++){
            //CALCULANDO TEMPO DO ALGORITMO
            std::cout << i << std::flush << " ";
            auto start8 = std::chrono::steady_clock::now();
            sa::insertion(sorting.begin(), sorting.end(), compare);
            auto end8 = std::chrono::steady_clock::now();
            std::chrono::duration<double> time8 = end8 - start8;
            sum[0] += std::chrono::duration <double, std::milli> (time8).count();
            sorting = backup;
        }

        std::cout << std::endl;

        std::cout << "Selection: ";
        for(int i{0};i<ciclo;i++){
            //CALCULANDO TEMPO DO ALGORITMO
            std::cout << i << std::flush << " ";
            auto start9 = std::chrono::steady_clock::now();
            sa::selection(sorting.begin(), sorting.end(), compare);
            auto end9 = std::chrono::steady_clock::now();
            std::chrono::duration<double> time9 = end9 - start9;
            sum[1] += std::chrono::duration <double, std::milli> (time9).count();
            sorting = backup;
        }
        std::cout << std::endl;

        std::cout << "Bubble: ";
        for(int i{0};i<ciclo;i++){
            //CALCULANDO TEMPO DO ALGORITMO
            std::cout << i << std::flush << " ";
            auto start10 = std::chrono::steady_clock::now();
            sa::bubble(sorting.begin(), sorting.end(), compare);
            auto end10 = std::chrono::steady_clock::now();
            std::chrono::duration<double> time10 = end10 - start10;
            sum[2] += std::chrono::duration <double, std::milli> (time10).count();
            sorting = backup;
        }
        std::cout << std::endl;

        std::cout << "Shell: ";
        for(int i{0};i<ciclo;i++){
            //CALCULANDO TEMPO DO ALGORITMO
            std::cout << i << std::flush << " ";
            auto start11 = std::chrono::steady_clock::now();
            sa::shell(sorting.begin(), sorting.end(), compare);
            auto end11 = std::chrono::steady_clock::now();
            std::chrono::duration<double> time11 = end11 - start11;
            sum[3] += std::chrono::duration <double, std::milli> (time11).count();
            sorting = backup;
        }
        std::cout << std::endl;

        std::cout << "Merge: ";
        for(int i{0};i<ciclo;i++){
            //CALCULANDO TEMPO DO ALGORITMO
            std::cout << i << std::flush << " ";
            auto start12 = std::chrono::steady_clock::now();
            sa::merge(sorting.begin(), sorting.end(), compare);
            auto end12= std::chrono::steady_clock::now();
            std::chrono::duration<double> time12= end12 - start12;
            sum[4] += std::chrono::duration <double, std::milli> (time12).count();
            sorting = backup;
        }
        std::cout << std::endl;
        
        std::cout << "Quick: ";
        for(int i{0};i<ciclo;i++){
            //CALCULANDO TEMPO DO ALGORITMO
            std::cout << i << std::flush << " ";
            auto start13 = std::chrono::steady_clock::now();
            sa::quick(sorting.begin(), sorting.end(), compare);
            auto end13 = std::chrono::steady_clock::now();
            std::chrono::duration<double> time13 = end13- start13;
            sum[5] += std::chrono::duration <double, std::milli> (time13).count();
            sorting = backup;
        }
        std::cout << std::endl;

        std::cout << "Radix: ";
        for(int i{0};i<ciclo;i++){
            //CALCULANDO TEMPO DO ALGORITMO
            std::cout << i << std::flush << " ";
            auto start14= std::chrono::steady_clock::now();
            sa::radix(sorting.begin(), sorting.end(), compare);
            auto end14 = std::chrono::steady_clock::now();
            std::chrono::duration<double> time14 = end14 - start14;
            sum[6] += std::chrono::duration <double, std::milli> (time14).count();
            sorting = backup;
        }
        std::cout << std::endl;

        for(int i{0};i<7;i++){
            average[i] = sum[i]/ciclo;
            answer[i] += average[i];
        }

        arquivo6 << atual;
        for(int i{0};i<7;i++){
            arquivo6 << "\t" << average[i] << "\t\t";
        }
        arquivo6 << std::endl;

        atual += 400;
        index++;
    }
    std::cout << "\n>>>>>>>>>>>>>>>>> TERMINOU\n\n";
    arquivo6.close();
    
    return EXIT_SUCCESS;
}
