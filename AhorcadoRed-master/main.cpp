#include<iostream>
#include"lescribe.hpp"
using namespace std;
main()
{
	LesCribe a;
	a.leerFichero();
	a.cargarEnFichero("antonio","Javier");
	a.cargarEnFichero("pepe","Javier");
	a.cargarEnFichero("demensio","ortegi");
	
}
