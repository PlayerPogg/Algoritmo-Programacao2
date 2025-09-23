#include <iostream>
#define tmax 10
using namespace std;
double calcularProdEscalar(int, float[], float[]);
int main()
{
    float X[tmax]= {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, Y[tmax] = {1,2,3,4,5,6,7,8,9,10};
    int tamanho=10;
    cout<<calcularProdEscalar(tamanho, X,Y);
    return 0;
}
double calcularProdEscalar(int tamanho, float X[], float Y[]){
    if(tamanho==1)
        return X[0]*Y[0];
    else
        return X[tamanho-1]*Y[tamanho-1]+calcularProdEscalar(tamanho-1, X, Y);
}
