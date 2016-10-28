#include <iostream>
#include <cstring>
#include <string>
#include <vector>
using namespace std;
class JGrupo
{
	private:
		vector<string> frases;//get frase
		string espacio;  //get set Cambiar
		int contador; // set
		int idActual;
		vector<int> id; // set
		int pos; //set(aumento)
	public:
		JGrupo()
		{
			frases.push_back("en abril aguas mil");
			frases.push_back("no por mucho madrugar amanece antes");
			setContador(0);
			setPos(0);
			setEspacios();
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
		inline void setIDActual(const int &d)
		{
			idActual=d;
		}
		inline void setPos(const int &d)
		{
			pos=d;
		}
		inline void setContador(const int &d)
		{
			contador=d;
		}
		inline void anadirID(const int &d)
		{
			id.push_back(d);
		}
		inline int getNID()const
		{
			id.size();
		}
		inline void setEspacios()
		{
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
		bool resolver(string p);


};
