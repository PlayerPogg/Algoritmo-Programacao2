#include<iostream>
#include<string>
#include<stdlib.h>
#define TMAX 20
using namespace std;

bool ehDigito(char c);
bool validarFloat(string num);
bool validarInteiro(string num);
string toLowerString(string str);
int indiceCidade(int n, string vetor[], string nome);
int lerInteiro(string msg);

void menu(int&, string[], float[][TMAX]);
void lerNcidades(int&, string[]);
void lerFormarMatrizDistancias(int, string[], float[][TMAX]);
void relatorio(int, string[], float[][TMAX]);
void apresentacao(int, string[], float[][TMAX]);
bool ehCidadeVizinha(int, int, int, float[][TMAX]);
void calculadoraPercurso(int, string[], float[][TMAX]);

int main(){
    int n = 0;
    string vetorCidades[TMAX]; 
    float distanciaCidades[TMAX][TMAX]={0}; 
    
    menu(n,vetorCidades,distanciaCidades); 
    
    return 0;
}

bool ehDigito(char c){
    return (c>='0' and c<='9');
}

bool validarFloat(string num){
    if(num.empty()) return false;
    if(num=="-0" or num=="-0.0") return false;
    if(not ehDigito(num[0]) and num[0] not_eq '-') return false;
    unsigned short ponto=0;
    for(unsigned x=1; x<num.size(); x++){
        if(not ehDigito(num[x])){
            if(num[x]=='.' and ponto==0) ponto++;
            else return false;
        }
    }
    if(num=="-") return false;
    return true;
}

bool validarInteiro(string num){
    if(num.size()==0) return false;
    if(not ehDigito(num[0]) and num[0] not_eq '-') return false;
    for(unsigned x=1; x<num.size(); x++){
        if(not ehDigito(num[x])) return false;
    }
    if(num=="-") return false;
    return true;
}

string toLowerString(string str){
    string lowerStr = str;
    for (unsigned i=0; i<lowerStr.size(); i++){
        if (lowerStr[i]>='A' and lowerStr[i]<='Z'){
            lowerStr[i]=lowerStr[i]+('a'-'A');
        }
    }
    return lowerStr;
}

int indiceCidade(int n, string vetor[], string nome){
    for(int i=0; i<n; i++){
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

void menu(int &n, string vetor[], float matriz[TMAX][TMAX]){
    int resp;
    int matrizPreenchida=0;
    
    do{
        cout<<"\n------PRE-CADASTRO INICIAL------"<<endl;
        cout<<"1-Inserir lista de cidades."<<endl;
        cout<<"2-Sair do Programa."<<endl;
        
        resp = lerInteiro("");
        
    }while(resp!=1 and resp!=2);
    
    if(resp==1){
        lerNcidades(n, vetor);
        
        do{
            system("cls");
            cout<<"\nPROTOTIPO DE CALCULADORA GEOGRAFICA."<<endl;
            cout<<"\n------MENU PRINCIPAL------"<<endl;
            cout<<"1-Informar todas as distancias entre duas cidades vizinhas."<<endl;
            cout<<"2-Mostras todos os nomes das cidades e todas as respectivas distancias."<<endl;
            cout<<"3-Mostrar a distancia entre duas cidades."<<endl;
            cout<<"4-Calcular e apresentar distancia total de um percurso."<<endl;
            cout<<"5-Sair do programa."<<endl;
            
            resp = lerInteiro("");
            
            switch(resp){
                case 1:
                    if(matrizPreenchida==0){
                        lerFormarMatrizDistancias(n, vetor, matriz);
                        matrizPreenchida=1;
                    } else {
                        cout<<"Opcao 1 ja foi utilizada. Por favor, escolha outra opcao."<<endl;
                    }
                    break;          
                case 2:
                    relatorio(n, vetor, matriz);
                    break;
                case 3:
                    apresentacao(n, vetor, matriz);
                    break;
                case 4:
                    calculadoraPercurso(n, vetor, matriz);
                    break;
                case 5:
                    cout<<"Programa finalizado."<<endl;
                    break;
                default:
                    cout<<"Opcao invalida. Digite novamente."<<endl;
                    break;
            }
        }while(resp not_eq 5);
    } 
    else{
        cout<<"Programa finalizado."<<endl;
    }
}

void lerNcidades(int &n, string vetor[]){
    string inputN;
    do{
        cout<<"Quantas cidades? (Maximo: "<<TMAX<<")"<<endl;
        getline(cin, inputN);
        if(not validarInteiro(inputN)){
            cout<<"Entrada inválida. Digite um número inteiro positivo."<<endl;
        }
        n=atoi(inputN.c_str());
    }while(not validarInteiro(inputN) or n<4 or n>TMAX);

    cout<<"Digite seus nomes: "<<endl;
    for(int i=0; i<n; i++){
        cout<<i+1<<" - ";
        getline(cin, vetor[i]);
    }
}

void lerFormarMatrizDistancias(int n, string vetor[], float matriz[TMAX][TMAX]){
    string cidade1, cidade2;
    int auxI1, auxI2;
    float distancia;
    char resp='s';
    string inputDistancia;
    
    cout<<"As distancias serao requesitadas para cidades vizinhas (portanto, uma distancia entre duas cidades implicara que sao vizinhas e se nao for informado a distancia entre duas cidades, sera tratado como se nao fossem vizinhas)"<<endl;
    
    do{
        cin.ignore();
        do{
            cout<<"Qual o nome da primeira cidade?"<<endl;
            getline(cin, cidade1);
            auxI1 = indiceCidade(n, vetor, cidade1);
            if(auxI1==-1){
                cout<<"Cidade '"<<cidade1<<"' nao encontrada no cadastro. Tente novamente."<<endl;
            }
        }while(auxI1==-1);

        do{
            cout<<"E da segunda cidade."<<endl;
            getline(cin, cidade2);
            auxI2 = indiceCidade(n, vetor, cidade2);
            if(auxI2==-1){
                cout<<"Cidade '"<<cidade2<<"' nao encontrada no cadastro. Tente novamente."<<endl;
            }
        }while(auxI2==-1);

        do{
            cout<<"Qual a distancia entre "<<cidade1<<" e "<<cidade2<<"?"<<endl;
            getline(cin, inputDistancia);
            if(not validarFloat(inputDistancia)){
                cout<<"Distância inválida. Digite um número real positivo."<<endl;
            }
        }while(not validarFloat(inputDistancia));
        
        distancia=atof(inputDistancia.c_str());
        if(distancia<0){
            cout<<"Distancia invalida. Deve ser maior ou igual a zero."<<endl;
        }else{
            matriz[auxI1][auxI2]=distancia;
            matriz[auxI2][auxI1]=distancia;
            cout<<"Distancia registrada/atualizada com sucesso!"<<endl;
        }
        
        cout<<"Informar nova distancia? S(im) ou N(ao)"<<endl;
        cin>>resp; 
    
    }while(resp=='s' or resp=='S');
}

void relatorio(int n, string vetor[], float matriz[TMAX][TMAX]){
    cout<<"Vetor dos Nomes das Cidades:"<<endl;
    for(int i=0; i<n; i++){
        cout<<"["<<i+1<<"]:"<<vetor[i]<<"       "; 
    }
    cout<<endl;

    cout<<"\nMatriz das distancias"<<endl;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(i==j)
                cout<<"["<<i+1<<"]["<<j+1<<"]:"<<" ";
            else
                cout<<"["<<i+1<<"]["<<j+1<<"]:"<<matriz[i][j];
        }
        cout<<endl;
    }
}

void apresentacao(int n, string vetor[], float matriz[TMAX][TMAX]){
    string cidade1, cidade2;
    int auxI1=0, auxI2=0; 
    char resp='s'; 
    
    do{
        cin.ignore();
        do{
            cout<<"Qual o nome da primeira cidade?"<<endl;
            getline(cin, cidade1);
            auxI1 = indiceCidade(n, vetor, cidade1);
            if(auxI1==-1){
                cout<<"Cidade '"<<cidade1<<"' nao encontrada no cadastro. Tente novamente."<<endl;
            }
        } while(auxI1==-1);
        
        do {
            cout<<"E da segunda cidade."<<endl;
            getline(cin, cidade2);
            auxI2 = indiceCidade(n, vetor, cidade2);
            if(auxI2==-1){
                cout<<"Cidade '"<<cidade2<<"' nao encontrada no cadastro. Tente novamente."<<endl;
            }
        }while(auxI2==-1);

        if(ehCidadeVizinha(n, auxI1, auxI2, matriz)){
            cout<<"A distancia entre "<<cidade1<<" e "<<cidade2<<" eh de "<<matriz[auxI1][auxI2]<<"KM."<<endl; 
        }
        else{
            cout<<"Estas cidades nao sao vizinhas (distancia nao informada)."<<endl;
        }
        
        cout<<"Apresentar nova distancia entre duas cidades? S(im) ou N(ao)"<<endl;
        cin>>resp;
    }while(resp=='s' or resp=='S');
}

bool ehCidadeVizinha(int n, int i, int j, float matriz[TMAX][TMAX]){
    return (matriz[i][j]>0);
}

void calculadoraPercurso(int n, string vetor[], float matriz[TMAX][TMAX]){
    int nCidades;
    string inputNCidades;
    
    do{
        cout<<"Quantas cidades tem o percurso? ";
        getline(cin, inputNCidades);
        if(not validarInteiro(inputNCidades)){
            cout<<"Entrada inválida. Digite um número inteiro."<<endl;
        }
    }while(not validarInteiro(inputNCidades));
    
    nCidades=atoi(inputNCidades.c_str());
    if(nCidades<2){
        cout<<"Um percurso deve ter pelo menos duas cidades. Percurso cancelado."<<endl;
        return;
    }

    string cidades[TMAX];
    cout<<"Digite os nomes das cidades na ordem do percurso:"<<endl;
    for(int i=0; i<nCidades; i++){
        string cidadeLida;
        do{
            cout<<"Cidade "<<i+1<<": ";
            getline(cin, cidadeLida);
            if(indiceCidade(n, vetor, cidadeLida)==-1){
                cout<<"Cidade '"<<cidadeLida<<"' nao encontrada no cadastro. Tente novamente."<<endl;
            }
            else break;
        } while(true);
        cidades[i]=cidadeLida;
    }

    float total=0.0;
    bool valido=true;
    for(int i=0; i<nCidades-1; i++){
        int auxI1 = indiceCidade(n, vetor, cidades[i]);
        int auxI2 = indiceCidade(n, vetor, cidades[i+1]);
        if(matriz[auxI1][auxI2]==0.0){
            cout<<"Percurso inválido: "<<cidades[i]<<" e "<<cidades[i+1]<<" não são vizinhas (distancia nao informada)."<<endl;
            valido = false;
            break;
        } 
        else{
            total+=matriz[auxI1][auxI2];
        }
    }

    if(valido){
        cout<<"Distância total do percurso: "<<total<<" KM"<<endl;
    }
}
