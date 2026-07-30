#include "bitVector.h"

int bitVector::bsrch(int rank){
    int left = 0;
    int right = size - 1;
    int mid;
    while(left <= right){
        mid = (left + right) / 2;
        if(acc[mid] == rank){
            while(mid > 0 && acc[mid - 1] == rank){
                mid--;
            }
            return mid;
        } else if(acc[mid] < rank){
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

int bitVector::bsrch0(int rank){
    int left = 0;
    int right = size - 1;
    int mid;
    while(left <= right){
        mid = (left + right) / 2;
        int r0 = (mid + 1) - acc[mid];
        if(r0 == rank){
            while(mid > 0 && (mid - acc[mid - 1]) == rank){
                mid--;
            }
            return mid;
        } else if(r0 < rank){
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

bitVector::bitVector() : size(0) {}

bitVector::bitVector(int s){
    size = s;
    bits.resize(size, false);
    acc.resize(size, 0);
}

void bitVector::setBit(int index){
    if(index >= size) return;
    if(index < 0) return;
    bits[index] = true;
}

void bitVector::clearBit(int index){
    if(index >= size) return;
    if(index < 0) return;
    bits[index] = false;
}

void bitVector::finishSetUp(){
    int count = 0;
    for(int i=0; i<size; i++){
        if(bits[i]){
            count++;
        }
        acc[i] = count;
    }
}

bool bitVector::access(int index){
    if(index < 0 || index >= size){
        return false;
    }
    return bits[index];
}

int bitVector::rank0(int index){
    if(index < 0 || index >= size){
        return 0;
    }
    return (index + 1) - acc[index];
}

int bitVector::rank1(int index){
    if(index < 0 || index >= size){
        return 0;
    }
    return acc[index];
}

int bitVector::select1(int rank){
    if(rank < 0) return 0;
    if(rank > acc[size - 1]) return this->size + 1;
    return bsrch(rank);
}

int bitVector::select0(int rank){
    if(rank < 0) return 0;
    int totalZeros = size - acc[size - 1];
    if(rank > totalZeros) return this->size + 1;
    return bsrch0(rank);
}

int bitVector::length(){
    return size;
}

int bitVector::pred0(int index){
    if (index < 0 || index >= size) return -1;
    return select0(rank0(index));
}

int bitVector::pred1(int index){
    if (index < 0 || index >= size) return -1;
    return select1(rank1(index));
}

int bitVector::succ0(int index){
    if (index < 0 || index >= size) return -1;
    return select0(rank0(index - 1) + 1);
}

int bitVector::succ1(int index){
    if (index < 0 || index >= size) return -1;
    return select1(rank1(index - 1) + 1);
}