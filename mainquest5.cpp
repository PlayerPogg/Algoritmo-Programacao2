#include<iostream>
#include<cstring>
using namespace std;
int main()
{
    string senha;
    bool valido=true;
    cout<<"Insira a senha: "<<endl;
    getline(cin, senha);
    if(not isalpha(senha[0]))
    valido=false;
    else
    for(unsigned i=1; i<senha.size(); i++){
        if(not isalnum(senha[i]) and senha[i]!='_')
        valido=false;
        break;
    }
    if(valido)
    cout<<"Senha valida!"<<endl;
    else
    cout<<"Senha invalida!"<<endl;
    return 0;
}
