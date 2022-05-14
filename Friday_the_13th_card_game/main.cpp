#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstdio>

using namespace std;

int Add(int *a, int *b) 
{
    int sum = *a + *b;
    return sum;
};    
//Add two numbers and return the sum
void AddVal(int *a, int *b, int *result)
{
    *result = *a + *b;
    cout << *result << endl;
}; 
//Add two numbers and return the sum through the third pointer argument
void Swap(int *a, int *b)
{
    int * temp;
    *temp = *a;
    *a = *b;
    *b = * temp;
    cout << *a << endl << *b;
};
//Swap the value of two integers
void Factorial(int *a, int *result);      
 //Generate the factorial of a number and return that through the second pointer argument

int main () {
    int a=3;
    int b=4;
    int result = 0;

    cout << Add(&a, &b) << endl;

    AddVal(&a, &b, &result);
    
    Swap (&a, &b);

}


