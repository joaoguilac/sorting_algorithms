/**
 * Several types of sorting algorithms that work on a data range.
 * @author 
 * @date July 5th, 2021
 * @file sorting.h
 */

#ifndef SORTING_H
#define SORTING_H

#include <sstream>
using std::ostringstream;
#include <iterator>
using std::next;
using std::ostream_iterator;
#include <functional>
using std::less;
using std::function;
#include <vector>
using std::vector;
#include <array>
using std::array;
#include <algorithm>
using std::max_element;
using std::for_each;
using std::copy;
#include <cmath>
using std::pow;
#include <string>
using std::string;
using std::to_string;

using size_type = long int;

namespace sa { // sa = sorting algorithms
    /// Prints out the range to a string and returns it to the client.
    template <typename FwrdIt>
    std::string to_string(FwrdIt first, FwrdIt last){
        std::ostringstream oss;
        oss << "[ ";
        while (first!=last)
            oss << *first++ << " ";
        oss << "]";
        return oss.str();
    }

    //{{{ RADIX SORT
    template <typename FwrdIt>
    //Function To Get The Max Number of a Array To Use in Radix Sort
    int getMax(FwrdIt first, FwrdIt last){
        int maxValue = *(first); // DECLARANDO O PRIMEIRO ELEMENTO COMO O MAIOR
        for(int i{1};i<last-first;i++) // PERCORRENDO TODO O VETOR E COMPARANDO PARA ACHAR O MAIOR TROCANDO A POSIÇÃO
            if(*(first+i)>maxValue)
                maxValue = *(first+i); 
        return maxValue; // RETORNANDO O VALOR PARA CALCULARMOS ATÉ QUAL ORDEM IREMOS
    }

    template <typename FwrdIt>
    void bucketDivider(FwrdIt first, FwrdIt last, int div){
        int sz = last-first; //TAMANHO DO VETOR
        int aux[sz]; //VETOR PARA SALVAR AS ORDENAÇÕES PARCIAIS
        int count[10]={0}; //VETOR PARA SABERMOS QUANTAS VEZES O DIGITO DE 0 A 9 APARECEU

        //ADICIONANDO A QUANTIDADE DE VEZES QUE UM NUMERO APARECEU NO VETOR COUNT QUE É UM AUXILIAR
        for(int i{0};i<sz;i++){
            //std::cout << "VALOR DO DIV: " << div;
            //std::cout << "\n VALOR DA CONTA: " << (*(first+i)/div)%10 << std::endl;
            count[(*(first+i)/div)%10]++; // FAZ O CALCULO PARA SABER EM QUAL POSIÇÃO DO COUNT INCREMENTAR
        }      

        //SOMANDO OS INDICES DA QTD DE VEZES Q O NUMERO APARECEU    
        for(int i{1};i<10;i++){ //COMEÇA DE UM PQ VOU SOMANDO DO ANTERIOR, LOGO TERIA POSIÇÃO INVALIDA
            count[i] += count[i-1];
        }   

        //CRIANDO SAIDA COLOCANDO O VALOR NA POSIÇÃO CORRETA E DIMINUINDO A SOMA FEITA NO PASSO ANTERIOR
        for(int i{sz-1};i>=0;i--){
            aux[count[(*(first+i)/div)%10]-1] = *(first+i); //PEGA O VALOR DO INDICE GUARDADO -1 PQ É A POSIÇÃO REAL
            //std::cout << "Valor: " << aux[count[(*(first+i)/div)%10]-1] << std::endl;
            count[(*(first+i)/div)%10]--; //DIMINUI PARA CASO TENHA REPETIDO NAO FICAR NO MESMO LOCAL
        }

        //COLOCANDO OS VALORES GERADOS NO ARRAY AUXILIAR NO MEU ORIGINAL PARA RETORNAR
        for(int i{0};i<sz;i++){
            *(first+i) = aux[i];
        }
    }


    /*!
     * This function implements the Radix Sorting Algorithm based on the **less significant digit** (LSD).
     * 
     * @note There is no need for a comparison function to be passed as argument.
     *
     * @param first Pointer/iterator to the beginning of the range we wish to sort.
     * @param last Pointer/iterator to the location just past the last valid value of the range we wish to sort.
     * @tparam FwrdIt A forward iterator to the range we need to sort.
     * @tparam Comparator A Comparator type function tha returns true if first argument is less than the second argument.
     */
    template < typename FwrdIt, typename Comparator, typename value_type=long >
    void radix( FwrdIt first, FwrdIt last, Comparator ){
        int maxValue = getMax(first,last);
        for(int divider = 1; maxValue/divider > 0 ; divider*=10){
            bucketDivider(first,last,divider);
        }
    }
    //}}} RADIX SORT

    //{{{ INSERTION SORT
    /// Implementation of the Insertion Sort algorithm.
    template< typename RandomIt, typename Compare >
    void insertion(RandomIt first, RandomIt last, Compare cmp){
        for(int i{0};i<last-first;i++){
            for(int j{i+1};j>0;j--){
                int aux;
                if(cmp(*(first+j),*(first+j-1))){
                    aux = *(first+j);
                    *(first+j) = *(first+j-1);
                    *(first+j-1) = aux;
                }else{
                    break;
                }
            }
        }
    }
    //}}} INSERTION SORT

    //{{{ SELECTION SORT 
    template< typename RandomIt, typename Compare >
    void selection(RandomIt first, RandomIt last, Compare cmp){
        size_t sz = last-first;
        for (size_t i{0}; i < sz-1; i++) {
            RandomIt min_itr = first+i;
            for (size_t j{i+1}; j < sz; j++) {
                if (cmp(*(first+j), *(min_itr))) {
                    min_itr = first+j;
                }
            }
            size_t aux = *(first+i);
            *(first+i) = *(min_itr);
            *(min_itr) = aux;
        }
    }
    //}}} SELECTION SORT

    //{{{ BUBBLE SORT
    template< typename RandomIt, typename Compare >
    void bubble(RandomIt first, RandomIt last, Compare cmp){
        size_t sz = last - first;
        bool changed{true};

        while (changed) {
            changed = false;
            for (size_t i{0}; i < sz-1; i++) {
                if (cmp(*(first+i+1), *(first+i))) {
                    size_t aux = *(first+i);
                    *(first+i) = *(first+i+1);
                    *(first+i+1) = aux;
                    changed = true;
                }
            }            
        }
    }
    //}}} BUBBLE SORT

    //{{{ SHELL SORT
    template< typename RandomIt, typename Compare >
    void shell(RandomIt first, RandomIt last, Compare cmp){
        // TODO
        int size = last-first;
        int increment = 1;
        while(increment < size){
            increment = 3*increment + 1;
        }
        for (/*empty*/; increment > 0; increment /= 3)
        {
            for (int i = increment; i < size; i += 1)
            {  
                int temp = *(first+i);
                int j;
                for (j = i; j >= increment;/*empty*/){
                    if(temp < *(first+j-increment)){
                        *(first+j)= *(first+j-increment);
                        j -= increment;
                    }else{
                        break;
                    }
                }
                *(first+j) = temp;
            }
        }
    }
    //}}} SHELL SORT

    //{{{ MERGE SORT
    template< typename RandomIt, typename Compare >
    void mergeAux(RandomIt L_first, RandomIt L_last, RandomIt R_first, RandomIt R_last, RandomIt first, Compare cmp){
        size_t L_sz = L_last - L_first;
        size_t R_sz = R_last - R_first;
        size_t L_i{0}, R_i{0}, A_i{0};

        while (L_i < L_sz and R_i < R_sz) {
            if (cmp(*(L_first+L_i), *(R_first+R_i)) || *(L_first+L_i) == *(R_first+R_i)) {
                *(first+A_i) = *(L_first+L_i);
                L_i++;
            }
            else {
                *(first+A_i) = *(R_first+R_i);
                R_i++;
            }
            A_i++;
        }
        while (L_i < L_sz) {
            *(first+A_i) = *(L_first+L_i);
            L_i++;
            A_i++;
        }
        while (R_i < R_sz) {
            *(first+A_i) = *(R_first+R_i);
            R_i++;
            A_i++;
        }
    }

    template< typename RandomIt, typename Compare >
    void merge(RandomIt first, RandomIt last, Compare cmp){
        size_t sz = last - first;
        if (sz > 1) {
            size_t middle = sz / 2;
            size_t L_sz = middle;
            size_t R_sz = last - (first+middle);

            auto temp = *first;
            using array_type = decltype(temp);
            std::vector<array_type> L (L_sz);
            std::vector<array_type> R (R_sz);

            std::copy(first, first+middle, L.begin());
            std::copy(first+middle, last, R.begin());

            // std::cout << "L contains:";
            // for (size_t i{0}; i < L_sz; i++)
            //     std::cout << ' ' << L[i];
            // std::cout << "\n";
            // std::cout << "R contains:";
            // for (size_t i{0}; i < R_sz; i++)
            //     std::cout << ' ' << R[i];
            // std::cout << "\n";

            merge(L.begin(), L.end(), cmp);
            merge(R.begin(), R.end(), cmp);
            mergeAux(L.begin(), L.end(), R.begin(), R.end(), first, cmp);
        }
    }
    //}}} MERGE SORT

    //{{{ QUICK SORT
    /*!
     * Partition reorders the elements in the range [first;last) in such a way that
     * all elements **less** than the pivot appear before the pivot, and all elements
     * equal or greater than the pivot appear after the pivot.
     *
     * Any relative order among elements of the array might not be preserved.
     *
     * By **less** we mean a _strict order_ binary relation among the elements we
     * wantt to partition.
     *
     * \note We assume the pivot is a valid iterator in [first; last).
     *
     * @param first The first element in the range we want to reorder.
     * @param last Past the last element in the range we want to reorder.
     * @param pivot Location of the pivot element we need to partition the array.
     * @param cmp A comparison function that returns true if the first parameter is **less** than the second.
     * @return An iterator to the new pivot location within the range.
     */
    template<class FwrdIt, class Compare>
    FwrdIt partition(FwrdIt first, FwrdIt last, FwrdIt pivot, Compare cmp){
        // Let us apply the Lamuto's median-of-three pivot selection strategy
        // to avoid segfault (stack overflow) in case the array is already
        // sorted.

        // Slow/fast approach: operating within the own range.

        // Traverse range, rearranging the elements
            // Move smallest to the front region of the array.
            // Advance frontier..

        // We need a final swap, so that the pivot end up in its final position
        // in the sorted array.
        size_t sz = last - first;
        // std::cout << "Tamanho dentro: " << sz << " e pivot: " << *(pivot) << "\n";
        FwrdIt ind_partition{first};
        for (size_t i{0}; i < sz; i++) {
            if (cmp(*(first+i), *(pivot))) {
                std::swap(*(first+i), *(ind_partition));
                ind_partition++;
            }
        }
        // std::cout << "ind_partition: " << *(ind_partition) << " Pivot: " << *(pivot) << "\n";
        std::swap(*(ind_partition), *(pivot));
        // std::cout << "ind_partition: " << *(ind_partition) << " Pivot: " << *(pivot) << "\n";
        return ind_partition;
    }
    /// Quick sort implementation.
    template<typename RandomIt, typename Compare>
    void quick(RandomIt first, RandomIt last, Compare comp){
        size_t sz = last - first;
        RandomIt pivot_index;
        RandomIt pivot;
        // std::cout << "Tamanho fora: " << sz << "\n";
        if (sz > 1) {
            size_t median = sz / 2;
            if (*(first) < *(first+median))
                std::swap(*(first), *(first+median));
            if (*(last-1) < *(first+median))
                std::swap(*(first+median), *(last-1));
            if (*(first) < *(last-1))
                std::swap(*(first), *(last-1));
            pivot = first+median;
            pivot_index = partition(first, last, pivot, comp);
            quick(first, pivot_index, comp);
            quick(pivot_index+1, last, comp);
            // std::cout << "Testando... [ ";
            // for (size_t i{0}; i < sz; i++) {
            //     std::cout << *(first+i) << " ";
            // }
            // std::cout << "]\n";
        }
    }
    //}}} QUICK SORT
};
#endif // SORTING_H
