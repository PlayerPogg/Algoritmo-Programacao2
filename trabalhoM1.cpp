#include<iostream>
#include<string>
#include<stdlib.h>
#define TMAX 20
using namespace std;


bool ehDigito(char c);
bool validarFloat(string num);
bool validarInteiro(string num);
string toLowerString(string str);


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
    if (c>='0' and c<='9'){
        return true;
    } 
    else{
        return false;
    }
}

bool validarFloat(string num){
    if(num.size() == 0) return false;
    
    if(num=="-0" or num=="-0.0") return false;

    bool result = true;
    
    if(not ehDigito(num[0]) and num[0] not_eq '-'){
        return false;
    }
    
    unsigned short ponto=0;
    
    for(unsigned x = 1; x<num.size(); x++){
        if(not ehDigito(num[x])){
            if(num[x]=='.' and ponto==0){
                ponto++;
            } 
            else{
                return false;
            }
        }
    }

    if(num=="-") return false;

    return result;
}

bool validarInteiro(string num)
{
    if(num.size()==0) return false;
    
    if(not ehDigito(num[0]) and num[0] not_eq '-')
        return false;
    
    
    for(unsigned x = 1; x<num.size(); x++){
        if(not ehDigito(num[x])){
            return false;
        }
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




void menu(int &n, string vetor[], float matriz[TMAX][TMAX]){
    int resp;
    int matrizPreenchida=0;
    string inputResp;
    
    do{
        cout<<"\n------PRE-CADASTRO INICIAL------"<<endl;
        cout<<"1-Inserir lista de cidades."<<endl;
        cout<<"2-Sair do Programa."<<endl;
        
        getline(cin, inputResp);
        
        if (validarInteiro(inputResp)) {
            resp=atoi(inputResp.c_str());
        } 
        else{
            resp=0;
        }
        
    }while(resp!=1 and resp!=2);
    
    if(resp==1){
        lerNcidades(n, vetor);
        
        do{
            cout<<"\nPROTOTIPO DE CALCULADORA GEOGRAFICA."<<endl;
            cout<<"\n------MENU PRINCIPAL------"<<endl;
            cout<<"1-Informar todas as distancias entre duas cidades vizinhas."<<endl;
            cout<<"2-Mostras todos os nomes das cidades e todas as respectivas distancias."<<endl;
            cout<<"3-Mostrar a distancia entre duas cidades."<<endl;
            cout<<"4-Calcular e apresentar distancia total de um percurso."<<endl;
            cout<<"5-Sair do programa."<<endl;
            
            getline(cin, inputResp);
            
            if (validarInteiro(inputResp)) {
                resp=atoi(inputResp.c_str());
            } 
            else{
                resp=0;
            }
            
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
    
    do {
        cout<<"Quantas cidades? (Maximo: "<<TMAX<<")"<<endl;
        getline(cin, inputN);
        
        if (not validarInteiro(inputN)){
            cout<<"Entrada inválida. Digite um número inteiro positivo."<<endl;
        }
    }while(not validarInteiro(inputN) or n<4 or n>TMAX)

    n=atoi(inputN.c_str());

    if(n<=0){
        cout<<"O número de cidades deve ser positivo. Usando n=1."<<endl;
        n=1;
    }
    
    if (n>TMAX){
        n=TMAX;
        cout<<"Limite excedido. O numero de cidades sera limitado a "<<TMAX<<endl;
    }
    
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
            
            bool achou=false;
            auxI1=0;
            for(int i=0; i<n; i++){
                if(toLowerString(vetor[i])==toLowerString(cidade1)){
                    auxI1=i;
                    achou=true;
                    break; 
                }
            }
            if(not achou){
                cout<<"Cidade '"<<cidade1<<"' nao encontrada no cadastro. Tente novamente."<<endl;
            }else{
                break;
            }
        }while(true);

        do{
            cout<<"E da segunda cidade."<<endl;
            getline(cin, cidade2);
            
            bool achou=false;
            auxI2=0;
            for(int i=0; i<n; i++){
                if(toLowerString(vetor[i])==toLowerString(cidade2)){
                    auxI2=i;
                    achou=true;
                    break;
                }
            }
            if(not achou){
                cout<<"Cidade '"<<cidade2<<"' nao encontrada no cadastro. Tente novamente."<<endl;
            }else{
                break;
            }
        }while(true);

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
            
            auxI1=-1;
            bool achou=false;
            for(int i=0; i<n; i++){
                if(toLowerString(vetor[i])==toLowerString(cidade1)){
                    auxI1=i;
                    achou=true;
                    break;
                }
            }
            if(not achou){
                cout<<"Cidade '"<<cidade1<<"' nao encontrada no cadastro. Tente novamente."<<endl;
            } 
            else{
                break;
            }
        } while(true);
        
        
        do {
            cout<<"E da segunda cidade."<<endl;
            getline(cin, cidade2);
            
            auxI2 = -1;
            bool achou = false;
            for(int i=0; i<n; i++){
                if(toLowerString(vetor[i])==toLowerString(cidade2)){
                    auxI2=i;
                    achou=true;
                    break;
                }
            }
            if(not achou) {
                cout<<"Cidade '"<<cidade2<<"' nao encontrada no cadastro. Tente novamente."<<endl;
            }
            else{
                break;
            }
        }while(true);

        
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
    if(matriz[i][j]>0) 
        return true;
    else
        return false;
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

            bool achou = false;
            for(int j = 0; j < n; j++){
                if(toLowerString(vetor[j])==toLowerString(cidadeLida)){
                    achou=true;
                    break;
                }
            }
            
            if(not achou){
                cout<<"Cidade '"<<cidadeLida<<"' nao encontrada no cadastro. Tente novamente."<<endl;
            }
            
            cidades[i]=cidadeLida;
            
            if(achou)break;
        } while(true);
    }

    float total=0.0;
    bool valido=true;

    for(int i=0; i<nCidades-1; i++){
        int auxI1=-1, auxI2=-1;

        for(int j=0; j<n; j++){
            if(toLowerString(vetor[j])==toLowerString(cidades[i])){
                auxI1=j;
            }
            if(toLowerString(vetor[j])==toLowerString(cidades[i+1])){
                auxI2=j;
            }
        }

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
