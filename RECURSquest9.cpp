#include <iostream>
#define TMAX 10
using namespace std;
bool vetorEhIgual(int, float[], float[]);
int main()
{
    float X[TMAX]= {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, Y[TMAX] = {1,2,3,4,5,6,7,8,9,10};
    int tamanho=10;
    cout<<vetorEhIgual(tamanho, X,Y);
    return 0;
}
bool vetorEhIgual(int tamanho, float X[], float Y[]){
    if(tamanho==1){
        if(X[0]==Y[0])
            return true;
        else
            return false;
    }
    else{
        if(X[tamanho-1]==Y[tamanho-1])
            return vetorEhIgual(tamanho-1, X, Y);
        else
            return false;
    }
}
