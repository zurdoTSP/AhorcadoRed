#include <iostream>
#include <cstring>
#include <string>
#include <vector>
using namespace std;
//clase para controlar los jugadores individuales
class JIndividual
{
	private:
		vector<string> frases;
		string espacio;  
		int contador; 
		int id; 
		int pos; 
		int puntos;
	public:
		JIndividual(int d)
		{
			frases.push_back("en abril aguas mil"); //incluimos las frases
			frases.push_back("no por mucho madrugar amanece antes");

			setID(d);//cogemos el id del jugador
			setContador(0);//ponemos el contador de intentos a 0
			setPos(0); //ponemos la posición de la frase a 0
			setEspacios(); //transformamos los espacios
			setPuntos(0);//ponemos los puntos a 0
		}
		inline int getContador() const
		{
			return contador;
		}
		inline int getID() const
		{
			return id;
		}
		inline int getPos() const
		{
			return pos;
		}
		inline int getPuntos() const
		{
			return puntos;
		}
		inline string getFrases()
		{
			return frases[getPos()];
		}
		inline string getEspacio() const
		{
			return espacio;
		}
		inline void setID(const int &d)
		{
			id=d;
		}
		inline void setPuntos(const int &d)
		{
			puntos=d;
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
		inline void setEspacios() //recorremos la cadena y ponemos - o ' ' según sea letra o espacio.
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

		void controlPuntos();


};
