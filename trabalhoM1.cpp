#include<iostream>
#include<string>
#include<stdlib.h>
#define TMAX 20
using namespace std;

bool ehDigito(char);
bool ehAlpha(char);
bool ehStringNomeCidade(string);
bool validarFloat(string num);
bool validarInteiro(string);
string toLowerString(string);
int indiceCidadeExistente(int, string vetor[], string);
int lerInteiro(string msg);
int lerIndiceCidade(int, string vetor[], string msg);

void menu(int&, string[], float[][TMAX]);
void pausarLerContinuar(string);
void lerNcidades(int&, string[]);
void lerFormarMatrizDistancias(int, string[], float[][TMAX]);
void relatorio(int, string[], float[][TMAX]);
void apresentacaoDistancias(int, string[], float[][TMAX]);
bool ehCidadeVizinha(int, int, int, float[][TMAX]);
void leitorCalculadoraPercurso(int, string[], float[][TMAX]);

int main(){
    int n=0;
    string vetorCidades[TMAX];
    float distanciaCidades[TMAX][TMAX]={0};

    menu(n,vetorCidades,distanciaCidades);

    return 0;
}

bool ehDigito(char c){
    return (c>='0' and c<='9');
}
bool ehAlpha(char c){
    if((c>='a' and c<='z') or (c>='A' and c<='Z'))
        return true;
    return false;
}

bool ehStringNomeCidade(string nome){
    for(unsigned i=0;i<nome.size();i++){
        if(ehAlpha(nome[i]))
            return true;
    }
    return false;
}

bool validarFloat(string num){
    if(num.empty())return false;
    if(num=="-0" or num=="-0.0")return false;
    if(not ehDigito(num[0]) and num[0]!='-')return false;
    unsigned short ponto=0;
    for(unsigned x=1;x<num.size();x++){
        if(not ehDigito(num[x])){
            if(num[x]=='.' and ponto==0)ponto++;
            else return false;
        }
    }
    if(num=="-")return false;
    return true;
}

bool validarInteiro(string num){
    if(num.size()==0)return false;
    if(not ehDigito(num[0]) and num[0]!='-')return false;
    for(unsigned x=1;x<num.size();x++){
        if(not ehDigito(num[x]))return false;
    }
    if(num=="-")return false;
    return true;
}

string toLowerString(string str){
    string lowerStr=str;
    for(unsigned i=0;i<lowerStr.size();i++){
        if(lowerStr[i]>='A' and lowerStr[i]<='Z'){
            lowerStr[i]=lowerStr[i]+('a'-'A');
        }
    }
    return lowerStr;
}

int indiceCidadeExistente(int n, string vetor[], string nome){
    for(int i=0;i<n;i++){
        if(toLowerString(vetor[i])==toLowerString(nome)){
            return i;
        }
    }
    return -1;
}

int lerInteiro(string msg){
    string entrada;
    do{
        cout<<msg;
        getline(cin, entrada);
    }while(!validarInteiro(entrada));
    return atoi(entrada.c_str());
}

void pausarLerContinuar(string msg){
    string entrada;
    cout<<msg;
    getline(cin, entrada);
}

int lerIndiceCidade(int n, string vetor[], string msg){
    string cidadeLida;
    int encontrado;
    do{
        cout<<msg;
        getline(cin, cidadeLida);
        encontrado=indiceCidadeExistente(n, vetor, cidadeLida);

        if(encontrado==-1){
            cout<<"Cidade '"<<cidadeLida<<"' nao encontrada no cadastro. Tente novamente."<<endl;
        }
    }while(encontrado==-1);

    return encontrado;
}

void menu(int &n, string vetor[], float matriz[TMAX][TMAX]){
    int resp;
    do{
        system("cls");
        cout<<"\n------PRE-CADASTRO INICIAL------"<<endl;
        cout<<"1-Inserir lista de cidades."<<endl;
        cout<<"2-Sair do Programa."<<endl;

        resp=lerInteiro("");

        if(resp!=1 and resp!=2){
            pausarLerContinuar("Pressione Enter para continuar...");
        }

    }while(resp!=1 and resp!=2);

    if(resp==1){
        lerNcidades(n, vetor);
    pausarLerContinuar("Cidades gravadas, digite qualquer tecla para ir ao menu inicial.");
        do{
            system("cls");
            cout<<"\nPROTOTIPO DE CALCULADORA GEOGRAFICA."<<endl;
            cout<<"\n------MENU PRINCIPAL------"<<endl;
            cout<<"1-Informar todas as distancias entre duas cidades vizinhas."<<endl;
            cout<<"2-Mostras todos os nomes das cidades e todas as respectivas distancias."<<endl;
            cout<<"3-Mostrar a distancia entre duas cidades."<<endl;
            cout<<"4-Calcular e apresentar distancia total de um percurso."<<endl;
            cout<<"5-Sair do programa."<<endl;

            resp=lerInteiro("");
            if(resp>0 and resp<6){
                switch(resp){
                    case 1:
                        lerFormarMatrizDistancias(n, vetor, matriz);
                        break;
                    case 2:
                        relatorio(n, vetor, matriz);
                        pausarLerContinuar("Digite qualquer tecla para voltar ao menu principal: ");
                        break;
                    case 3:
                        apresentacaoDistancias(n, vetor, matriz);
                        break;
                    case 4:
                        leitorCalculadoraPercurso(n, vetor, matriz);
                        pausarLerContinuar("Digite qualquer tecla para voltar ao menu principal: ");
                        break;
                    case 5:
                        cout<<"Programa finalizado."<<endl;
                        break;
                }
            }
            else{
                cout<<"Opcao invalida. Digite novamente."<<endl;
            }
        }while(resp!=5);
    }
    else{
        cout<<"Programa finalizado."<<endl;
    }
}

void lerNcidades(int &n, string vetor[]){
    string inputN;
    do{
        system("cls");
        cout<<"Quantas cidades? (Minimo: 4. Maximo: "<<TMAX<<")"<<endl;
        getline(cin, inputN);
        if(not validarInteiro(inputN)){
            cout<<"Entrada invalida. Digite um numero inteiro positivo."<<endl;
            pausarLerContinuar("Pressione Enter para continuar...");
        }
        n=atoi(inputN.c_str());
    }while(not validarInteiro(inputN) or n<4 or n>TMAX);

    system("cls");
    cout<<"Digite seus nomes: "<<endl;
    for(int i=0;i<n;i++){
        string cidadeLida;
        int duplicado;

        do{
            cout<<i+1<<" - ";
            getline(cin, cidadeLida);

            duplicado=indiceCidadeExistente(i, vetor, cidadeLida);

            if(duplicado!=-1){
                cout<<"Erro: Cidade '"<<cidadeLida<<"' ja foi cadastrada. Digite um nome diferente."<<endl;
            } else if(cidadeLida.empty()){
                cout<<"Erro: O nome da cidade nao pode ser vazio. Digite novamente."<<endl;
            } else if(not ehStringNomeCidade(cidadeLida)){
                cout<<"Erro: O nome da cidade deve conter pelo menos uma letra (nao pode ser apenas um numero)."<<endl;
            }
        }while(duplicado!=-1 or cidadeLida.empty() or not ehStringNomeCidade(cidadeLida));

        vetor[i]=cidadeLida;
    }
}

void lerFormarMatrizDistancias(int n, string vetor[], float matriz[TMAX][TMAX]){
    string cidade1, cidade2;
    int auxI1, auxI2;
    float distancia;
    char resp='s';
    string inputDistancia;

    cout<<"As distancias serao requesitadas para cidades vizinhas (portanto, uma distancia entre duas cidades implicara que sao vizinhas e se nao for informado a distancia entre duas cidades, sera tratado como se nao fossem vizinhas)."<<endl;

    do{
        system("cls");
        cout<<"As distancias serao requesitadas para cidades vizinhas (portanto, uma distancia entre duas cidades implicara que sao vizinhas e se nao for informado a distancia entre duas cidades, sera tratado como se nao fossem vizinhas)."<<endl;

            auxI1=lerIndiceCidade(n, vetor, "Qual o nome da primeira cidade?\n");
            cidade1=vetor[auxI1];

            auxI2=lerIndiceCidade(n, vetor, "E da segunda cidade.\n");
            cidade2=vetor[auxI2];

            do{
                cout<<"Qual a distancia entre "<<cidade1<<" e "<<cidade2<<"?"<<endl;
                getline(cin, inputDistancia);
                if(not validarFloat(inputDistancia)){
                    cout<<"Distancia invalida. Digite um numero real positivo."<<endl;
                }
            }while(not validarFloat(inputDistancia));

            distancia=atof(inputDistancia.c_str());
            if(distancia<0.1){
                cout<<"Distancia invalida. Deve ser maior que zero."<<endl;
        }
        else{
            matriz[auxI1][auxI2]=distancia;
            matriz[auxI2][auxI1]=distancia;
            cout<<"Distancia registrada/atualizada com sucesso!"<<endl;
        }

        cout<<"Informar nova distancia? Sim(S) ou nao(N ou qualquer outra tecla)."<<endl;
        cin>>resp;
        cin.ignore();
    }while(resp=='s' or resp=='S');
}

void relatorio(int n, string vetor[], float matriz[TMAX][TMAX]){
    cout<<"Vetor dos Nomes das Cidades:"<<endl;
    for(int i=0;i<n;i++){
        cout<<"["<<i+1<<"]:"<<vetor[i]<<"      ";
    }
    cout<<endl;

    cout<<"\nMatriz das distancias em KM"<<endl;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i==j)
                cout<<"["<<i+1<<"]["<<j+1<<"]:"<<"      ";
            else
                cout<<"["<<i+1<<"]["<<j+1<<"]:"<<matriz[i][j]<<"      ";
        }
        cout<<endl;
    }
}

void apresentacaoDistancias(int n, string vetor[], float matriz[TMAX][TMAX]){
    string cidade1, cidade2;
    int auxI1=0, auxI2=0;
    char resp='s';

    do{
        system("cls");
            auxI1=lerIndiceCidade(n, vetor, "Qual o nome da primeira cidade?\n");
            cidade1=vetor[auxI1];

            auxI2=lerIndiceCidade(n, vetor, "E da segunda cidade.\n");
            cidade2=vetor[auxI2];

            if(ehCidadeVizinha(n, auxI1, auxI2, matriz)){
                cout<<"A distancia entre "<<cidade1<<" e "<<cidade2<<" eh de "<<matriz[auxI1][auxI2]<<"KM."<<endl;
            }
            else{
                cout<<"Estas cidades nao sao vizinhas (distancia nao informada)."<<endl;
            }

            cout<<"Apresentar nova distancia entre duas cidades? Sim(S) ou nao(N ou qualquer outra tecla)."<<endl;
            cin>>resp;
            cin.ignore();
    }while(resp=='s' or resp=='S');
}

bool ehCidadeVizinha(int n, int i, int j, float matriz[TMAX][TMAX]){
    if(matriz[i][j]>0)
        return true;
    return false;
}

void leitorCalculadoraPercurso(int n, string vetor[], float matriz[TMAX][TMAX]){
    int nCidades;
    string inputNCidades;

    do{
        system("cls");
        do{
            cout<<"Quantas cidades tem o percurso? ";
            getline(cin, inputNCidades);
            if(not validarInteiro(inputNCidades)){
                cout<<"Entrada invalida. Digite um numero inteiro."<<endl;
                pausarLerContinuar("Pressione Enter para tentar novamente...");
            }
        }while(not validarInteiro(inputNCidades));

        nCidades=atoi(inputNCidades.c_str());
        if(nCidades<2)
            cout<<"Um percurso deve ter pelo menos duas cidades."<<endl;
        if(nCidades>n)
            cout<<"Trajeto excede quantidade de cidades informadas."<<endl;
    }while(nCidades<2 or nCidades>n);

    system("cls");
    string cidades[TMAX];

    cout<<"Digite os nomes das cidades na ordem do percurso:"<<endl;
    for(int i=0;i<nCidades;i++){
        string cidadeLida;
        int encontrado;
        bool trajetoCidadeConsecutiva=false;
        bool ehVizinha=false;

        do{
            trajetoCidadeConsecutiva=false;
            ehVizinha=true;

            encontrado=lerIndiceCidade(n, vetor, "Cidade "+to_string(i+1)+": ");
            cidadeLida=vetor[encontrado];

            if(i>0){
                int indiceAnterior=indiceCidadeExistente(n, vetor, cidades[i-1]);
                int indiceAtual=encontrado;

                if(toLowerString(cidadeLida)==toLowerString(cidades[i-1])){
                    cout<<"Trajeto redundante(0km). A cidade deve ser diferente da anterior. Tente novamente."<<endl;
                    pausarLerContinuar("Pressione Enter para tentar novamente...");
                    system("cls");
                    cout<<"Digite os nomes das cidades na ordem do percurso:"<<endl;
                    for(int j=0;j<i;j++){
                        cout<<"Cidade "<<j+1<<": "<<cidades[j]<<endl;
                    }
                    trajetoCidadeConsecutiva=true;
                }
                else if(matriz[indiceAnterior][indiceAtual]==0.0){
                    cout<<"Erro! A cidade '"<<cidades[i-1]<<"' nao se conecta com a cidade '"<<cidadeLida<<"' (distancia nao informada). Tente outra cidade."<<endl;
                    pausarLerContinuar("Pressione Enter para tentar novamente...");
                    system("cls");
                    cout<<"Digite os nomes das cidades na ordem do percurso:"<<endl;
                    for(int j=0;j<i;j++){
                        cout<<"Cidade "<<j+1<<": "<<cidades[j]<<endl;
                    }
                    ehVizinha=false;
                }
            }

        }while(trajetoCidadeConsecutiva or !ehVizinha);

        cidades[i]=cidadeLida;
    }

    float total=0.0;

    for(int i=0;i<nCidades-1;i++){
        int auxI1=indiceCidadeExistente(n, vetor, cidades[i]);
        int auxI2=indiceCidadeExistente(n, vetor, cidades[i+1]);

        total+=matriz[auxI1][auxI2];
    }

    cout<<"Distancia total do percurso: "<<total<<" KM"<<endl;
}
