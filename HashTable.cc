#include "HashTable.h"
#include <math.h>
#include <stdio.h>
int HashTable::insert(int value)
{
    // h(k) = floor[m(kA mod1)]
    if(nSlot == nElem)
    {
        return -1; // table full
    }
    int hash = GetHash(value);
    int i = 1;
    while(array[hash] != -1)
    {
        hash = (GetHash(value) + i) % nSlot;
        i++;
    }
    array[hash] = value;
    nElem++;
    load = double(nElem)/double(nSlot);
    return i;
}
int HashTable::GetHash(int value)
{
    float kA_f = A * value;
    int kA_i = A * value;
    float kA = kA_f - kA_i; // kA mod 1
    int hash = nSlot * kA;
    return hash;

    
}
bool HashTable::find(int value, int& nProbes)
{
    int hash = GetHash(value);
    while(array[hash] != -1)
    {
        hash = (GetHash(value) + nProbes) % nSlot;
        if(array[hash] == value)
        {
            return true;
        }
        nProbes++;
    }
    return false;
}

