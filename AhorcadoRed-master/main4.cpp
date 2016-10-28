#include<iostream>
#include<string>
#include<cstring>
#include<stdio.h>
using namespace std;
void cortar(char *cad, char *cad2);
main()
{
	char cadena[250]="resolver en abril aguas mil";
	char cadena2[20];
	cortar(cadena,cadena2);
	printf("%s\n",cadena2);
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
	string cadena="en abril aguas mil";
	bool senal=false;
	while(cad[i]!='\0')
	{
		if(cad[i]==' ')
		{
			senal=true;
			
		}
		i++;
		if(senal==true)
		{
			cad2[j]=cad[i];
			j++;
		}
		
	}
	cad2[j]='\0';
	cout<<strlen(cadena.c_str())<<" "<<strlen(cad2)<<"\n"<<strncmp(cad2, cadena.c_str(),strlen(cadena.c_str()));;
}
