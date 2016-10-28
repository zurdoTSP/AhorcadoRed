#include<iostream>
#include"jindividual.hpp"
using namespace std;
main()
{
  string b="a";
  JIndividual a(5);
  cout<<a.getContador()<<"\n";
  cout<<a.getFrases()<<"\n";
  cout<<a.getEspacio()<<"\n";
  a.comprobar("a");
  cout<<"RESPUESTA:\n";
    cout<<a.getEspacio()<<"\n";
  if(a.resolver("en abril aguas mil"))
  {
    cout<<"has ganado!\n";
  }
  else
  {
    cout<<"has perdido\n";
  }

}
