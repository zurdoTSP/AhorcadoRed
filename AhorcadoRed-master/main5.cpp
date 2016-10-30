#include<iostream>
#include <vector>
using namespace std;
vector<string> dividir(string cad);
main()
{
vector<string> a;
	
	string cad="hola -p adios -h jiji";
	a=dividir(cad);
	for(int i=0;i<a.size();i++)
	{
		cout<<a[i]<<"\n";
	}
	a.erase(a.begin());
	for(int i=0;i<a.size();i++)
	{
		cout<<a[i]<<"\n";
	}
	
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
	a.push_back(x);
	return a;
}
