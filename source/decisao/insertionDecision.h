#ifndef SORTING_G
#define SORTING_G

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

bool cmp(int &a, int &b){
    return (a<b);
}

int* insertionGuilac(int * first, int * last){
    int sz = last - first;
    for (int i{0}; i < sz-1; i++) {
        int j = i + 1;
        while (cmp(*(first+j), *(first+j-1))) {
            int aux{*(first+j)};
            *(first+j) = *(first+j-1);
            *(first+j-1) = aux;
            j--;
            if (j <= 0) {
                break;
            }
        }
    }
}

int* insertionPaulo(int * first, int * last){
    for(int i{0};i<last-first-1;i++){
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

int* bubble(int* first, int* last){
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
    int* partition(int* first, int* last, int* pivot){
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
        int* ind_partition{first};
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
    int* quick(int* first, int* last){
        size_t sz = last - first;
        int* pivot_index;
        int* pivot;
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
            pivot_index = partition(first, last, pivot);
            quick(first, pivot_index);
            quick(pivot_index+1, last);
            // std::cout << "Testando... [ ";
            // for (size_t i{0}; i < sz; i++) {
            //     std::cout << *(first+i) << " ";
            // }
            // std::cout << "]\n";
        }
    }
#endif