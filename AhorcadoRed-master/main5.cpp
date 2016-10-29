#include<iostream>
#include <vector>
using namespace std;
vector<string> dividir(string cad);
main()
{
	string cad="hola -p adios -h jiji";
	cout<<dividir(cad);
}
vector<string> dividir(string cad)
{
	vector<string> a;
	string x;
	for(int i=0;i<cad.size();i++)
	{
		if(cad[i]!=' ')
		{
			x=x+cad[i];
		}
		else
		{
			a.push_back(x);
			x="";
		}
	}

	return a;
}
