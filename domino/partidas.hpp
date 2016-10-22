#ifndef __PARTIDAS_HPP__
#define __PARTIDAS_HPP__


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

namespace redes
{
	class partidas
	{

	private:
		int numero_usuarios;
		int iniciada;
		int turno;
		int numero_fichas;
		fichas _mesa[28];


	public:
		partidas()
		{
			for (int i = 0; i < 28; ++i)
			{
				_mesa[i].derecha=-1;
				_mesa[i].izquierda=-1;
			}
			numero_usuarios=0;
			iniciada=0;
			turno=0;
			numero_fichas=0;

		}
		~partidas()
		{

		}

		const int getTurno()
		{
			return turno;
		}

		void aumentarTurno()
		{

			turno=(turno+1)%5;

			if (turno==0)
			{
				turno=1;
			}

		}
		const int getIniciada()
		{
			return iniciada;
		}

		void setIniciada(int dato)
		{
			iniciada=dato;
		}
		const int getNfichas()
		{
			return numero_fichas;
		}

		
		const int getNumeroUsuarios()
		{
			return numero_usuarios;
		}


		void setNfichas(int d)
		{
			numero_fichas=d;
		}

		void aumentarFichas()
		{
			numero_fichas++;
		}

		void aumentarUsuarios()
		{
			numero_usuarios++;
		}

		void  setNumeroUsuarios(int d)
		{
			numero_usuarios=d;
		}

		void insertarFicha(fichas p,int numero)
		{
			cout<<"INSERTAR FICHA TABLERO"<<p.derecha<<p.izquierda<<endl;
			if (numero==1)
			{
				fichas naux;
				fichas mesa[getNfichas()];

				if (getNfichas()>0)
				{
					for (int i = 1; i <= getNfichas(); ++i)
					{
						naux.derecha=_mesa[i-1].derecha;
						naux.izquierda=_mesa[i-1].izquierda;
						mesa[i].derecha=naux.derecha;
						mesa[i].izquierda=naux.izquierda;
					
					}
					for (int i = 1; i <= getNfichas(); ++i)
					{
						
						_mesa[i].derecha=mesa[i].derecha;
						_mesa[i].izquierda=mesa[i].izquierda;
					
					}


				}

				_mesa[0].derecha=p.derecha;
				_mesa[0].izquierda=p.izquierda;

				

				
				aumentarFichas();
			}
			else
			{
				_mesa[numero_fichas].derecha=p.derecha;
				_mesa[numero_fichas].izquierda=p.izquierda;
				aumentarFichas();
			}
		}

		int comprobarEmpezar()
		{
			if(numero_usuarios==4 && iniciada==0)
			{
				return 1;
			}
				

			else 
				return 0;
		}

		fichas  getMesa(int n)
		{
			return _mesa[n];

		}

		void quitarFichas()
		{
			fichas n;
			n.derecha=-1;
			n.izquierda=-1;
			for (int i = 0; i < numero_fichas; ++i)
			{
				_mesa[i]=n;
			}
		}




		


		



	
		/* data */
	};

}

#endif