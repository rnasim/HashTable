#include "HashTable.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
    HashTable h;
    srand((unsigned int)time(NULL));
    int num;
    int num_probes = 0;
    int counter = 0;
    while(h.load_factor() < 0.5)
    {
        num = rand() % 100001;
        num_probes += h.insert(num);
        counter++;
    }
    float average = float(num_probes)/float(counter);
    printf("50%% full: %f\n", average);
    while(h.load_factor() < 0.9)
    {
        num = rand() % 100001;
        num_probes += h.insert(num);
        counter++;
    }
    average = float(num_probes)/float(counter);
    printf("90%% full: %f\n", average);
    
    return 0;
    
}
