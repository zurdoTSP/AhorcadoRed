#include"jgrupo.hpp"
#include<iostream>
#include <string>
#include<stdio.h>
using namespace std;
//funciones para comprobar la resolución de la frase y saber que usuario tiene más puntos
bool JGrupo::comprobar(char *p)
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


bool JGrupo::resolver(char *cad)//resolver la frase, devuelve false si no se hizo bien y true si se gano.
{
	bool sol=false;
	int qa = strcmp(cad,getFrases().c_str());			
	if(qa==0)
	{
		sol=true;
	}
	return sol;
}

int JGrupo::maxPuntos() //en el caso de resolver mal la frase nos dirá quien gano.
{
	int max=0;
	int mas;
	for(int i=0;i<puntos.size();i++)
	{
		if(puntos[i]>max)
		{
			max=puntos[i];
			mas=i;
		}
	}
	return mas;
}



