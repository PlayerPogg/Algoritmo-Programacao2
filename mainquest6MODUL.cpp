#include<iostream>
using namespace std;
void cabecalho(string);
int main (){
    string nome;
    cout<<"Qual o seu nome?"<<endl;
    getline(cin,nome);
    cabecalho(nome);
    return 0;
}
void cabecalho(string nome){
    cout<<"\n============================================="<<endl;
    cout<< "UNIVALI - POLITECNICA - Ciencia da Computacao"<<endl;
    cout<<"Disciplina Algoritmo e Programacao 2 per"<<endl;
    cout<<"Nome: "<<nome<<endl;
    cout<<"============================================="<<endl;
}
