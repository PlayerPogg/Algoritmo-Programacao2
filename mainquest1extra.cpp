#include<iostream>
#include<cstring>
using namespace std;
int main()
{
    string frase;
    char invAux;
    cout<<"Palavra:"; getline(cin, frase);
    for(unsigned i=0, j=frase.size()-1; i<frase.size()/2; i++, j--){
        invAux=frase[i];
        frase[i]=frase[j];
        frase[j]=invAux;
    }
    cout<<frase;
    return 0;
}
