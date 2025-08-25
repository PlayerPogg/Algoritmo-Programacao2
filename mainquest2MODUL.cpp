#include<iostream>
using namespace std;
float faparacel(float);
int main()
{
    float fahrenheit;
    cout<<"Informe temperatura em Fahrenheit: ";
    cin>>fahrenheit;
    cout<<faparacel(fahrenheit)<<" graus Celsius"<<endl;
    return 0;
}
float faparacel (float fahrenheit){
    float celsius;
    celsius = 5/9*(fahrenheit-32);
    return celsius;
}
