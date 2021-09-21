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

#include "insertionDecision.h"

int main( void )
{
    setlocale(LC_ALL, "Portuguese");
    int ciclo{25};
    //int atual{10000};
    int atual{2500};
    //int max{10000000};
    int max{50000};

    
    double soma1 = 0;
    double soma2 = 0;
    double media1,media2,super1=0,super2=0;
    std::vector<int> v1;
    std::vector<int> v2;
    //===========================PAULO===================================================================
    std::ofstream arquivo( "insertionDecision2.txt" );
    int parou=0;
    while(atual<=max){
        soma1 = 0;
        soma2 = 0;
        v1.resize(atual);
        v2.resize(atual);

        //std::fill(v.begin(), v.end(), 0);
        
        for(int i{parou};i<atual;i++){
            v1.push_back(i);
            v2.push_back(i);
            parou++;
        }

        unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();  

        shuffle (v1.begin(),v1.end(), std::default_random_engine(seed1));  
        shuffle (v2.begin(),v2.end(), std::default_random_engine(seed1));  


        for(int i{0};i<ciclo;i++){
            //CALCULANDO TEMPO PARA O DE PAULO
            auto start1 = std::chrono::steady_clock::now();
            int * ptr1 = quick(&v1[0],&v1[v1.size()]);
            auto end1 = std::chrono::steady_clock::now();
            std::chrono::duration<double> time1 = end1 - start1;
            soma1 += std::chrono::duration <double, std::milli> (time1).count();

            //CALCULANDO TEMPO PARA O DE GUILAC
            auto start2 = std::chrono::steady_clock::now();
            int * ptr2 = bubble(&v2[0],&v2[v2.size()-1]);
            auto end2 = std::chrono::steady_clock::now();
            std::chrono::duration<double> time2 = end2 - start2;
            soma2 += std::chrono::duration <double, std::milli> (time2).count();
        }

        media1 = soma1/ciclo;
        super1 += media1;

        media2 = soma2/ciclo;
        super2 += media2;

        arquivo << atual << "\t" << media1;
        arquivo << "\t\t\t"<< atual << "\t" << media2 << std::endl;

        atual += 2500;
        //atual += 20000;
    }
    //super1 /= 500;
    super1 /= 19;

    //super2 /= 500;
    super2 /= 19;
    if(super1<super2){
        arquivo << "O Algoritmo de Paulo está sendo mais rápido\n\n";
    }else if(super2<super1){
        arquivo << "O Algoritmo de Guilac está sendo mais rápido\n\n";
    }else{
        arquivo << "Os Dois Algoritmos Têm a Mesma Méida de Tempo de Execução\n\n";
    }
    arquivo << "Média de Paulo: " << super1 << "\t\t Média de Guilac: "<< super2 << std::endl;

    //===========================================================================================================

    arquivo.close();
    //===========================GUILAC=========================================================
    /*
    std::ofstream binaria( "insertionGuilac.txt" );
    atual = 10000;
    while(atual<max){
        soma = 0;
        v.resize(atual);
        std::fill(v.begin(), v.end(), 0);
        for(int i{0};i<ciclo;i++){
            auto start = std::chrono::steady_clock::now();
            int * ptr = insertionGuilac(&(v[0]),&(++v[v.size()-1]));
            auto end = std::chrono::steady_clock::now();
            std::chrono::duration<double> time = end - start;
            soma += std::chrono::duration <double, std::milli> (time).count();
        }

        media = soma/ciclo;
        binaria << atual << "\t" << media << std::endl;
        atual += 20000;
    }
    */
    //===========================================================================================================

    /*
    //===========================BINARY SEARCH RECURSIVE=========================================================
    std::ofstream binaryRecT( "TimeBinaryRec.txt" );
    atual = 10000;
    while(atual<max){
        soma = 0;
        v.resize(atual);
        std::fill(v.begin(), v.end(), 0);
        for(int i{0};i<ciclo;i++){
            auto start = std::chrono::steady_clock::now();
            auto ptr = sa::binaryRec(&(v[0]),&v.back(),-2);
            auto end = std::chrono::steady_clock::now();
            //double time = double (std::chrono::duration_cast <std::chrono::milliseconds>(end-start).count());
            std::chrono::duration<double> time = end - start;
            soma += std::chrono::duration <double, std::milli> (time).count();
        }

        media = soma/ciclo;
        binaryRecT << atual << "\t" << media << std::endl;
        atual += 20000;
    }
    //===========================================================================================================
    */
    //binaria.close();
    //binaryInt.close();
    //binaryRecT.close();
}
