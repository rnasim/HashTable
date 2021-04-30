#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "edit_distance.h"
#include <algorithm>

using namespace std;

int ** cost_table;
char ** operation_table;
int cost, ptr_index = 0;
Stack r, l;
string z;

int min(int q, int x, int y)
{
    return min(min(q, x), y);
}

void print_head()
{
  cout.setf(ios::left);
  cout << setw(16) << "Operation"
       << setw(32) << "z"
       << setw(8) << "Cost"
       << setw(8) << "Total" << endl;

  for (int i=0; i<64; ++i) cout << "-";
  cout << endl;
}
void Traverse(int i, int j, string x, string y)
{
    int i0 = i;
    int j0 = j;
    if(i == 0 && j == 0)
    {
        return;
    }
    
    if(operation_table[i][j] == 'r' || operation_table[i][j] == 'x')
    {
        i--;
        j--;
    }
    else if(operation_table[i][j] == 'd')
    {
        i--;
    }
    else if(operation_table[i][j] == 'i')
    {
        j--;
    }

    Traverse(i, j, x, y);

    if(operation_table[i0][j0] == 'r') // replace
    {
        cost += 4;
        string str = "replace by ";
        if(!(r.empty()))
        {
            r.pop();
            l.push(y[j0-1]);
        }
        ptr_index++;
        Stack r_temp = r, l_temp = l;
        string zr = r_temp.StacktoString();
        string zl = l_temp.StacktoString();
        reverse(zl.begin(), zl.end());
        z = zl + zr;
        string new_z = z;
        new_z.insert(ptr_index, "*");
        str += y[j0-1];
        reverse(z.begin(), z.end());
        cout << setw(16) << str << setw(32) << new_z << setw(8) << "4" << setw(8) << cost << endl;
    }
    else if(operation_table[i0][j0] == 'x') // right
    {
        ptr_index++;
        if(!(r.empty()))
         {
             l.push(r.top());
             r.pop();
         }
        Stack r_temp = r, l_temp = l;
        string zr = r_temp.StacktoString();
        string zl = l_temp.StacktoString();
        reverse(zl.begin(), zl.end());
        z = zl + zr;
        string new_z = z;
        new_z.insert(ptr_index, "*");
        cout << setw(16) << "right" << setw(32) << new_z << setw(8) << "0" << setw(8) << cost << endl;
    }
    else if(operation_table[i0][j0] == 'd') // delete
    {
        cost += 2;
        string str = "delete";
        if(!(r.empty()))
        {
            r.pop();
        }
        Stack r_temp = r, l_temp = l;
        string zr = r_temp.StacktoString();
        string zl = l_temp.StacktoString();
        reverse(zl.begin(), zl.end());
        z = zl + zr;
        string new_z = z;
        new_z.insert(ptr_index, "*");
        cout << setw(16) << str << setw(32) << new_z << setw(8) << "2" << setw(8) << cost << endl;
    }
    else if(operation_table[i0][j0] == 'i') // insert
    {
        cost +=3;
        ptr_index++;
        string str = "insert ";
        l.push(y[j0-1]);
        Stack r_temp = r, l_temp = l;
        string zr = r_temp.StacktoString();
        string zl = l_temp.StacktoString();
        reverse(zl.begin(), zl.end());
        z = zl + zr;
        string new_z = z;
        new_z.insert(ptr_index, "*");
        str += y[j0-1];
        cout << setw(16) << str << setw(32) << new_z << setw(8) << "3" << setw(8) << cost << endl;
    }
    
}

int EditDistance(string s1, string s2, int x, int y)
{
    // fill table 2D array
    for(int i = 0; i <= x; i++)
    {
        for(int j = 0; j <= y; j++)
        {
            if(i == 0 && j == 0)
            {
                cost_table[0][0] = 0;
                operation_table[0][0] = '0';
            }
            else if(i == 0)
            {
                cost_table[0][j] = 3 + cost_table[0][j-1];
                operation_table[0][j] = 'i';
                
            }
            else if(j == 0)
            {
                cost_table[i][0] =  2 + cost_table[i-1][0];
                operation_table[i][0] = 'd';
            }
            else if (s1[i - 1] == s2[j - 1])
            {
                cost_table[i][j] = cost_table[i - 1][j - 1];
                operation_table[i][j] = 'x'; // right (x)
            }
            else
            {
                cost_table[i][j] =  min(
                                   3 + cost_table[i][j-1], // insert
                                   2 + cost_table[i-1][j], // delete
                                   4 + cost_table[i-1][j-1]); // replace
                if(cost_table[i][j] == 3 + cost_table[i][j-1])
                {
                    operation_table[i][j] = 'i'; // insert (i)
                }
                else if(cost_table[i][j] ==  2 + cost_table[i-1][j])
                {
                    operation_table[i][j] = 'd'; // delete (d)
                }
                else if(cost_table[i][j] == 4 + cost_table[i-1][j-1])
                {
                    operation_table[i][j] = 'r'; // replace (r)
                }
            }

        }
    }
    return cost_table[x][y];
  
}

void PrintCostTable(string x, string y, int x_size, int y_size)
{
    cout << setw(6) << " ";
    for(int i = 0; i <= y_size; i++)
     {
         cout << setw(6) << y[i];
     }
     cout << endl;
    for(int i = 0; i <= x_size; i++)
    {
        for(int j = 0; j <= y_size; j++)
        {
            cout << setw(6) << cost_table[i][j];
        }
        cout << endl;
    }
}
void PrintOperationTable(string x, string y, int x_size, int y_size)
{
    for(int i = 0; i <= x_size; i++)
    {
        for(int j = 0; j <= y_size; j++)
        {
            cout << setw(6) << operation_table[i][j];
        }
        cout << endl;
    }
}
int main(int argc, char* argv[])
{
    string x, y;
    unsigned long int x_size = 0, y_size = 0;
    if(argc == 1)
    {
        cout << "Error: Please provide either two strings in the following format: string1 to string2, or provide an input file, such as input.txt as a command line argument" << '\n';
        return 1;
    }
    else if(argc == 2)
    {
        ifstream file;
        file.open(argv[1]);
        string x_size_s, y_size_s;
        if(file.is_open())
        {
               getline(file, x_size_s);
               getline(file, x);
               getline(file, y_size_s);
               getline(file, y);
        }
        x_size = atoi(x_size_s.c_str());
        y_size = atoi(y_size_s.c_str());
        file.close();
    }
    else if(argc > 2)
    {
        int middle = 0;
        for(int i = 1; i < argc; i++)
        {
            string current = argv[i];
            if(current == "to" && i != 1)
            {
                middle = i;
                break;
            }
        }
        if(middle == 0)
        {
             cout << "Error: Please provide either two strings in the following format: string1 to string2, or provide an input file, such as input.txt as a command line argument" << '\n';
            return 1;
        }
        for(int i = 1; i < middle; i++)
        {
            x += argv[i];
            if(i != middle - 1)
            {
                x += " ";
            }
        }
        for(int i = middle + 1; i < argc; i++)
        {
            y += argv[i];
            if(i != argc - 1)
            {
                y += " ";
            }
        }
        x_size = x.length();
        y_size = y.length();
    }
    r = Stack(x_size + y_size);
    l = Stack(x_size + y_size);
   // z = x;

    for(int i = x_size-1; i >= 0; i--)
    {
        r.push(x[i]);
    }
    cost_table = new int*[x_size + 1];
    operation_table = new char*[x_size + 1];
    for(int i = 0; i < x_size + 1 ; i++)
    {
        cost_table[i] = new int[y_size + 1];
        operation_table[i] = new char[y_size + 1];
    }
    int edit_distance = EditDistance(x, y, x_size, y_size);
    cout << "Edit distance: " << edit_distance << endl;
    if(argc > 2)
    {
        print_head();
        cout << setw(16) << "initial string" << setw(32) << "*" + x << setw(8) << "0" << setw(8) << "0" << endl;
        Traverse(x_size, y_size, x, y);
    }
   // free memory
    for(int i = 0; i < x_size + 1; i++)
    {
        delete [] cost_table[i];
        delete [] operation_table[i];
    }
    delete [] cost_table;
    delete [] operation_table;
    return 0;
}





