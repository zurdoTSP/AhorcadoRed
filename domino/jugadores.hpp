#ifndef __JUGADORES_HPP__
#define __JUGADORES_HPP__


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

using namespace std;

namespace redes
{


	struct fichas
	{
		int derecha;
		int izquierda;
	}typedef fichas;

	class jugadores
	{
		private:
			int _socket;
			string _nombre;
			string _contrasena;
			int numero_fichas;
			fichas _fichas[7];
			int turno;
			int opc;
			int _partida;
			int _puntos;
			int _estado;
			int ban;


		public:
			jugadores(){
				for (int i = 0; i < 7; ++i)
				{
					_fichas[i].derecha=-1;
					_fichas[i].izquierda=-1;
				}
				turno=0;
				opc=0;
				numero_fichas=0;
				_partida=98;
				 _puntos=0;
				_estado=0;
				_socket=98;
				ban=0;
				
			 	
			
			}
			~jugadores(){}

			void disminuir()
			{
				numero_fichas--;
			}	
			void setNfichas(int d)
			{	
				numero_fichas=d;
			}

			const int getNfichas()
			{
				return numero_fichas;
			}
			void aumentarFichas()
			{	
				numero_fichas++;
			}

			const int getBan()
			{
				return ban;
			}

			void setBan(int h)
			{
				ban=h;
			}

			const int getOpc()
			{
				return opc;
			}

			void setOpc(int a)
			{
				opc=a;
			}

			const int getTurno()
			{
				return turno;
			}
			
			void setTurno(int turn)
			{
				turno=turn;
			}
			const int getSocket ()
			{
				return _socket;
			}

			fichas getFicha(const int &n)
			{
				return _fichas[n];
			}

			const int getPartida()
			{
				return _partida;
			}

			const int getPuntos()
			{
				return _puntos;
			}

			

			const int getEstado()
			{
				return _estado;
			}

			const string getNombre()
			{
				return _nombre;
			}

			const string getContrasena()
			{
				return _contrasena;
			}


			void setSocket(const int &socket)
			{
				_socket=socket;
			}

			void setNombre(const string nombre)
			{
				_nombre=nombre;
			}
				

			void setContrasena(const string  con)
			{
				_contrasena=con;
			}	

			void setPartida(const int &n)
			{
				_partida=n;
			}

			void setPuntos(const int &n)
			{
				_puntos=n;
			}

			
			void setEstado(const int &n)
			{
				_estado=n;
			}

			void insertarFicha(const fichas &a)
			{
				
				_fichas[numero_fichas].derecha=a.derecha;
				_fichas[numero_fichas].izquierda=a.izquierda;
				

				aumentarFichas();
			}

			void setFichaCero(const int &n1)
			{
				fichas n;
				n.derecha=-1;
				n.izquierda=-1;
				_fichas[n1]=n;
				setNfichas(getNfichas()-1);
			}

			int compararNombre(const string n)
			{
				if(_nombre==n)
					return 1;

				return 0;

			}

			int compararConstrasena(const string n)
			{
				if(_contrasena==n)
					return 1;
				return 0;

			}

			void quitarFichas()
			{
				fichas n;
				n.derecha=-1;
				n.izquierda=-1;
				for (int i = 0; i < 7; ++i)
				{
					_fichas[i]=n;
					disminuir();
				}
			}

			void quitarFicha(fichas m)
			{
				fichas n;
				n.derecha=-1;
				n.izquierda=-1;

				for (int i = 0; i < 7; ++i)
				{
					if (m.derecha == _fichas[i].derecha && m.izquierda == _fichas[i].izquierda)
					{
						_fichas[i]=n;
						disminuir();
					}

					if (m.izquierda == _fichas[i].derecha && m.derecha == _fichas[i].izquierda)
					{
						_fichas[i]=n;
						disminuir();
					}
				}

			}










			
	};

	
	
}

#endif