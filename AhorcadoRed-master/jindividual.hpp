#include <iostream>
#include <cstring>
#include <string>
#include <vector>
using namespace std;
class JIndividual
{
	private:
		vector<string> frases;//get frase
		string espacio;  //get set Cambiar
		int contador; // set
		int id; // set
		int pos; //set(aumento)
	public:
		JIndividual(int d)
		{
			frases.push_back("en abril aguas mil");
			frases.push_back("no por mucho madrugar amanece antes");

			setID(d);
			setContador(0);
			setPos(0);
			setEspacios();
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
		bool comprobarVocal(char *p);
		bool comprobarConsonante(char *p);
		bool resolver(char *cad);


};
