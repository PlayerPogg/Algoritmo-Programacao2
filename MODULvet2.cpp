#include <iostream>
using namespace std;
#define TMAX 15
void Tmax(string, int &n);
void somaVet(int, float [], float [], float []);
void multiVet(int, float [], float [], float []);
float prodEscalarVet(int, float [], float []);
void leitorVets(int, float []);
void mostraResultados(int, float[], float[], float[], float[], float);
int main()
{
    int n;
    Tmax("Insira o numero maximo dos vetores (1..15): ", n);
    float V[n], W[n], soma[n]={0}, multi[n]={1}, prodEscalar=0;
    leitorVets(n, V);
    leitorVets(n, W);
    somaVet(n, V, W, soma);
    multiVet(n, V, W, multi);
    prodEscalar=prodEscalarVet(n, V, W);
    mostraResultados(n, V, W, soma, multi, prodEscalar);
    return 0;
}
void Tmax(string msg, int &n){
    do{
        cout<<msg;
        cin>>n;
    }while(n<1 or n>TMAX);
}
void somaVet(int n, float V[], float W[], float soma[]){
    for(int i=0; i<n; i++)
        soma[i]=V[i]+W[i];
}
void multiVet(int n, float V[], float W[], float multi[]){
    for(int i=0; i<n; i++)
        multi[i]=V[i]*W[i];
}
float prodEscalarVet(int n, float V[], float W[]){
    float prodEscalar=0;
    for(int i=0; i<n; i++)
        prodEscalar+=V[i]*W[i];
    return prodEscalar;
}
void leitorVets(int n, float vetor[]){
    for(int i=0; i<n; i++){
        cout<<"Insira o "<< i+1<< "elemento do vetor:"; cin>>vetor[i];
    }
}
void mostraResultados(int n, float V[], float W[], float soma[], float multi[], float prodEscalar){
    cout<<"Soma dos vetores V e W:"<<endl;
    for(int i=0; i<n; i++){
        cout<<soma[i]<<endl;
    }
    cout<<"Multiplicacao dos vetores V e W:"<<endl;
    for(int i=0; i<n; i++){
        cout<<multi[i]<<endl;
    }
    cout<<"Prod Escalar de V e W:"<<endl;
    if(prodEscalar==0)
        cout<<"Vetores V e W são ORTOGONAIS."<<endl;
    else
        cout<<prodEscalar;
}
