#include <iostream>
using namespace std;
#include <cstring>
int main()
{
	string palavra= " ";
	bool palindrome=true;
	cout<<"Palavra?"<<endl;
	getline(cin, palavra);
	for(unsigned i=0, j=palavra.size()-1; i<palavra.size()/2; i++, j--) {
		if(toupper(palavra[i])!=toupper(palavra[j])){
			palindrome=false;
		break;
		}
	}
	if(palindrome)
		cout<<"Palavra e palindrome."<<endl;
	else
		cout<<"Palavra nao e palindrome"<<endl;
	return 0;
}
