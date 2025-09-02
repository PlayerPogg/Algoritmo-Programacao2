/*
4.Dado um conjunto de n (1 n 10) números reais, faça um programa que escreva a
localização (índice) do primeiro elemento negativo, caso exista. Desenvolva uma função para
retornar a referida localização. Na hipótese de não existir elemento negativo, retornar -1
(considerando que este índice não existe em um vetor). 
*/
#define TMAX 10
#include<iostream>
using namespace std;
void Tmax(string, int &n);
int localizaNegativo(int, float []);
void leitorVets(int, float []);

int main()
{
    int n, indice;
    Tmax("Insira o numero maximo dos vetores (1..10): ", n);
    float conjunto[n];
    leitorVets(n, conjunto);
    indice=localizaNegativo(n, conjunto);
    cout<<"O primeiro numero negativo foi encontrado no indice "<<indice;
    return 0;
}
void Tmax(string msg, int &n){
    do{
        cout<<msg;
        cin>>n;
    }while(n<1 or n>TMAX);
}
int localizaNegativo(int n, float conjunto[]){
bool encontrado=false;
    for(int i=0; i<n; i++){
        if(conjunto[i]<0)
        return i;
    }
    return -1;
}
void leitorVets(int n, float vetor[]){
    for(int i=0; i<n; i++){
        cout<<"Insira o "<< i+1<< "elemento do vetor:"; cin>>vetor[i];
    }
}
