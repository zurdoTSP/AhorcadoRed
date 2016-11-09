#include"jindividual.hpp"
#include<iostream>
#include <string>
#include<stdio.h>
using namespace std;
bool JIndividual::comprobar(char *p)
{
  std::string f=frases[getPos()];
  bool e=false;
  char a[1];
  for(int i=0;i<getFrases().length();i++)
  {
    char compLetter = f[i];
  //  std::strcpy(a,f[i].c_str());
    if(p[0]==compLetter)
    {

      cambiar(i,f[i]);
      e=true;
    }
  }
  setContador(getContador()+1);
  return e;
}


bool JIndividual::resolver(char *cad)
{
	bool sol=false;
	int qa = strcmp(cad,getFrases().c_str());			
	if(qa==0)
	{
		sol=true;
	}
	return sol;
}
void JIndividual::controlPuntos()
{
	int t=getContador();
	if(t<5)
	{
		setPuntos(getPuntos()+150);
	}
	if(t>15)
	{
		setPuntos(getPuntos()+0);
	}
	if(t>=5 && t<=8)
	{
		setPuntos(getPuntos()+100);
	}
	if(t>=9 && t<=11)
	{
		setPuntos(getPuntos()+70);
	}
	if(t>=11 && t<=15)
	{
		setPuntos(getPuntos()+50);
	}


}
