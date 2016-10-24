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

bool JIndividual::resolver(string p)
{
  bool sol=false;
  if(p==getFrases())
  {
    sol=true;
  }
  return sol;
}
