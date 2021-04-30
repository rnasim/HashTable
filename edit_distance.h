//
//  edit_distance.h
//  Edit Distance
//
//  Created by Armand Sarkani on 2/28/20.
//  Copyright © 2020 Armand Sarkani. All rights reserved.
//
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#ifndef edit_distance_h
#define edit_distance_h


class Stack
{
int stack_size;
public :
    int top_index;
    char *array;
    Stack()
    {
        
    }
    Stack(int size)
    {
        stack_size = 0;
        array = new char[size];
        top_index = -1;
    }
    void push(char x)
    {
        top_index++;
        array[top_index] = x;
        stack_size++;
    }
    void pop()
    {
        top_index--;
        char c = array[top_index];
        stack_size--;
    }
    char top()
    {
        return array[top_index];
    }
    int size()
    {
        return stack_size;
    }
    bool empty()
    {
        if(stack_size == 0)
        {
            return true;
        }
        return false;
    }
    string StacktoString()
    {
        string str;
        int s = stack_size;
        for(int i = 0; i < s; i++)
        {
            str += top();
            pop();
        }
        return str;
    }
};




#endif /* edit_distance_h */
