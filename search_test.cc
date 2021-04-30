#include "HashTable.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
    HashTable h;
    srand((unsigned int)time(NULL));
    int num;
    // populate hash table
    while(h.load_factor() < 0.5)
    {
        num = rand() % 100001;
        h.insert(num);
    }
    // after 50% full
    int search_num;
    int nProbes = 0;
    int total_probes = 0;
    bool search_result;
    for(int i = 0; i < 10000; i++)
    {
        search_num = rand() % 100001;
        search_result = h.find(search_num, nProbes);
        total_probes += nProbes;
        nProbes = 0;
        
    }
    float average = float(total_probes)/10000.0;
    printf("50%% full: %f\n", average);
    while(h.load_factor() < 0.9)
    {
        num = rand() % 100001;
        h.insert(num);
    }
    // after 90% full
    nProbes = 0;
    for(int i = 0; i < 10000; i++)
    {
        search_num = rand() % 100001;
        search_result = h.find(search_num, nProbes);
        total_probes += nProbes;
        nProbes = 0;
        
    }
     average = float(total_probes)/10000.0;
     printf("90%% full: %f\n", average);
    return 0;
    
}
