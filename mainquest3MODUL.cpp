#include<iostream>
#include<cstring>
using namespace std;
bool ehAlpha(char);

int main(){
    char charc;
    do{
    cout<<"Insira letra: "; cin>>charc;
    if(not ehAlpha(charc)) cout<<"Não é letra."<<endl;
    }while(not ehAlpha(charc));
    cout<<"Letra do alfabeto confirmada.";
    return 0;
}
bool ehAlpha(char charc){
    string alfabeto="ABCDEFGHIJKLMNOPQRSTUVWXYZ"; bool encontrado=false;
    for(unsigned i=0;i<alfabeto.size();i++){
        if(toupper(charc)==alfabeto[i]){
            encontrado=true;
            break;
        }
    }
    return encontrado;
}
