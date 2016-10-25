#include<iostream>
#include<string>
#include<cstring>
#include<stdio.h>
using namespace std;
void cortar(char *cad, char *cad2);
main()
{
	char cadena[20]="hola majo";
	char cadena2[20];
	cortar(cadena,cadena2);
	cout<<cadena2<<"\n";
/*int qa;
	char buffer[250]="vocal aaa";
					qa = strncmp(buffer, "vocal", 4);
					if(qa>0)
					{
						cout<<"1\n";
					}
					if(qa<0)
					{
			cout<<"2\n";
					}
					if(qa==0)
					{
cout<<"3\n";
					}*/


}
void cortar(char *cad, char *cad2)
{
	int i=0;
	int j=0;
	while(cad[i]!='\0')
	{
		if(cad[i]==' ')
		{
			cad2[j]=cad[i];
			j++;
		}
				i++;
	}
}
