#include <iostream>
#include <cstring>
#include <string>
#include <vector>
using namespace std;
//clase para el control del juego grupal, tiene una frase común y distintos vectores para los distintos jugadores
class JGrupo
{
	private:
		vector<string> frases;//get frase
		string espacio;  //get set Cambiar
		int contador; // set
		int idActual;
		int x=0;
		vector<int> puntos;
		vector<string> nombre;
		vector<int> id; // set
		int pos; //set(aumento)
	public:
		JGrupo()
		{
			frases.push_back("en abril aguas mil");
			frases.push_back("no por mucho madrugar amanece antes");
			setContador(0); 
			setPos(0); //empezamos por la frase 0
			setEspacios(); //y la transformamos en -
		}
		inline int getContador() const
		{
			return contador;
		}
		inline int getIDActual() const
		{
			return idActual;
		}
		inline int getPos() const
		{
			return pos;
		}
		inline string getFrases()
		{
			return frases[getPos()];
		}
		inline string getEspacio() const
		{
			return espacio;
		}
		inline void setPos(const int &d)
		{
			if(d<frases.size())
			{
				pos=d;
			}
			else
			{
				pos=0;
			}

		}
		inline void setContador(const int &d)
		{
			contador=d;
		}
		inline void setIDActual()//controla el id del jugador al que le toca jugar
		{
			if((x+1)==id.size())
			{
				idActual=id[0];
				x=0;
			}
			else
			{
				x=x+1;
				idActual=id[x];
			}

		}
		inline void setIDActual(const int &d)
		{
			idActual=d;
		}
		inline void anadirID(const int &d)
		{
			id.push_back(d);
			puntos.push_back(0);
		}
		inline void setNombre(const string &n)
		{
			nombre.push_back(n);
		}
		inline int getNID()const
		{
			return id.size();
		}
		inline int getID(const int &d)const
		{
			return id[d];
		}
		inline int getPuntos(const int &d)const
		{
			return puntos[d];
		}
		inline string getNombre(const int &d)const
		{
			return nombre[d];
		}
		inline void setPuntos(const int &d,const int &d2,const int &d3)//suma o resta puntos según se compre vocal o se encuentre consonante
		{
			if(d2==0)
			{
				puntos[d]=puntos[d]-d3;
			}
			else
			{
				puntos[d]=puntos[d]+d3;
			}
		}
		inline void setPuntos0(const int &d)//suma o resta puntos según se compre vocal o se encuentre consonante
		{

				puntos[d]=0;
			

		}
		inline void borrar()
		{
			puntos.clear();
			nombre.clear();
			id.clear(); 
		}


		inline void setEspacios()
		{
			espacio="";
			for(int i=0;i<frases[getPos()].length();i++)
			{
				if(frases[getPos()][i]==' ')
				{
					espacio=espacio+' ';
				}
				else
				{
					espacio=espacio+'-';
				}
			}
		}
		inline void cambiar(int n,char letra)
		{
			espacio[n]=letra;
		}

		bool comprobar(char *p);

		bool resolver(char *cad);

		int maxPuntos();


};
