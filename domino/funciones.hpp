#ifndef __FUNCIONES_HPP__
#define __FUNCIONES_HPP__



#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <iostream.h>
#include <fstream>   // Biblioteca para el manejo de ficheros
#include <iostream>  // Biblioteca para la entrada-salida estándar
#include <cstdlib> 
#include <sstream>


#include "jugadores.hpp"
#include "partidas.hpp"
using namespace std;


namespace redes
{

	int comprobarFichas(fichas n,jugadores cliente)
	{
		int bandera=0;
		for (int i = 0; i < 7; ++i)
		{
				if (cliente.getFicha(i).derecha==n.derecha )
				{
					if (cliente.getFicha(i).izquierda==n.izquierda)
					{
						bandera=1;
					}
			}
			if (cliente.getFicha(i).derecha==n.izquierda )
						{
							if (cliente.getFicha(i).izquierda==n.derecha)
							{
								bandera=1;

							}
						}
		}
		return bandera;
	}


	int BuscarJuagador(jugadores clientes[40],string  nombre,int n)
	{
		int bandera=0;

		for (int i = 0; i < n; ++i)
		{
			if(clientes[i].getNombre()==nombre)
			{
				bandera=1;
				
				
			}
		}

		return bandera;

	}

	int BuscarSocket(jugadores clientes [40],int socket, int & posicion,int numero)
	{
		int bandera=0;

		for (int i = 0; i < numero; ++i)
		{
			if(clientes[i].getSocket()==socket)
			{
				bandera=1;
				posicion=i;
			}
		}

		return bandera;
	}	

	int buscarContrasena(jugadores clientes[40],string  nombre,int n,partidas mesas[10])
	{
		int bandera=0;

		for (int i = 0; i < n; ++i)
		{
			if(clientes[i].getContrasena()==nombre)
			{
				bandera=1;
				

				
			}
		}

		return bandera;

	}

	void buscarMesa(partidas mesas[10],jugadores& cliente)
	{
		int bandera=0;
		for (int i = 0; i < 10; ++i)
		{
			if (mesas[i].getNumeroUsuarios()<4)
			{
				if(bandera==0)
				{
				cliente.setPartida(i);
				cliente.setEstado(3);
				bandera=1;
				}
			}
		}
	}


	string transformarCadena(jugadores cliente,int n)
	{
		string aux=" ";
		string ab;
		string ac;

		for (int i = 0; i < n; ++i)
		{
			ostringstream  flujo; 
			flujo << cliente.getFicha(i).derecha;
			ostringstream  flujo1; 
			flujo1 << cliente.getFicha(i).izquierda;
			ab=flujo.str();
			ac=flujo1.str();
			
			aux=aux + ab + "|" + ac + " ";
		}
		cout<<"FICHAS->"<<aux<<endl;

		return aux;
	}


string transformarCadena1(partidas mesas,int n)
	{
		string aux=" ";
		string ab;
		string ac;
		
		for (int i = 0; i < n; ++i)
		{
			ostringstream flujo; 
			flujo << mesas.getMesa(i).derecha;
			ostringstream flujo1; 
			flujo1 << mesas.getMesa(i).izquierda;
			ab=flujo.str();
			ac=flujo1.str();
			aux=aux + ab + "|" + ac + " ";
		}

		cout<<"TABLERO->"<<aux<<endl;
		return aux;
	}


	int comparador(char buffer[100])
	{

		if(strncmp(buffer,"USUARIO ",7)==0)
			return 1;

		else if(strncmp(buffer,"PASSWORD",8)==0)
			return 2;

		else if(strncmp(buffer,"REGISTER",8)==0)
			return 3;

		else if(strncmp(buffer,"PASO-TURNO",10)==0)
			return 4;

		else if(strncmp(buffer,"INICIAR-PARTIDA",15)==0)
			return 5;


		else if(strncmp(buffer,"COLOCAR-FICHA",12)==0)
			return 6;

		else if(strncmp(buffer,"SALIR",5)==0)
			return 7;
		
		else if(strncmp(buffer,"\0",2)==0)
			return 8;
		else if(strncmp(buffer,"VER-FICHAS",10)==0)
			return 9;


		else
			return 0;

	}

	void cortarUsuario(char buffer[100],char * nombre)
	{
		int j=0;
		for (int i = 8; i < 28; ++i)
		{
			nombre[j]=buffer[i];
			j++;
		}

	}

	void cortarContrasena(char buffer[100],char * contrasena)
	{
		int j=0;
		for (int i = 9; i < 28 ; ++i)
		{
			contrasena[j]=buffer[i];
			j++;
		}
	}


	void cortarUsuarioContrasena(char buffer[100],char * nombre,char * contrasena)
	{
		int bandera=0;int numero;int j=0;int banderaaux=0;

		if(buffer[10]=='U')
		{
			for (int i = 12; i < 30 ; ++i)
			{
				

				if (buffer[i]==' ' && banderaaux==0)
				{
					bandera=1;
					banderaaux=1;
					numero=i;
				}

				if (bandera==0)
				{
					nombre[j]=buffer[i];
					j++;
				}
				
			}

			bandera=0;
			j=0;



			if (buffer[numero+2]=='P')
			{
				for (int i = numero+4; i < numero+2+20; ++i)
				{
					

					if (buffer[i]==' ')
					{
						bandera=1;
					}

					if (bandera==0)
					{
						contrasena[j]=buffer[i];
						j++;
					}
					
				}
			}
		}
	}

	void cortarFichas(fichas& n,char buffer[100],int& d)
	{

		n.derecha=buffer[15]-48;
		n.izquierda=buffer[17]-48;
		cout<<"|"<<n.derecha<<"|"<<n.izquierda<<endl;
		
		char nombre[10];
		int j=0;

		for (int i = 20; i < 30; ++i)
		{
			nombre[j]=buffer[i];
			j++;
		}
	
		if(strncmp(nombre,"DERECHA",7)==0)
			d=0;
		else
			d=1;
	}

	void CrearFichas(fichas * todas)
		{
				int j=0;

				for (int a = 0; a < 7; ++a)
				{
					todas[j].derecha=0;
					todas[j].izquierda=a;
					j++;
				}

				for (int b = 1;b < 7; ++b)
				{
					todas[j].derecha=1;
					todas[j].izquierda=b;
					j++;
				}

				for (int c= 2; c < 7; ++c)
				{
					todas[j].derecha=2;
					todas[j].izquierda=c;
					j++;
				}

				for (int d = 3; d < 7; ++d)
				{
					todas[j].derecha=3;
					todas[j].izquierda=d;
					j++;
				}

				for (int e = 4; e < 7; ++e)
				{
					todas[j].derecha=4;
					todas[j].izquierda=e;
					j++;
				}

				for (int f = 5; f < 7; ++f)
				{
					todas[j].derecha=5;
					todas[j].izquierda=f;
					j++;
				}

				todas[j].derecha=6;
				todas[j].izquierda=6;


			}


         


}
#endif


