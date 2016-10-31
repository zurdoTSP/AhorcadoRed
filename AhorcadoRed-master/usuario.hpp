#include<iostream>
using namespace std;
class Usuario
{
	private:
		string nombre;
		int nFallos;
		int Puntos;
		int id;
		string name;
		string pass;
		bool asignado;
		bool log;
	public:
		Usuario(string nomb, int _id)
		{
			setNombre(nomb);
			setNFallos(0);
			setPuntos(0);
			id=_id;
			name="";
			pass="";
			asignado=false;
			log=false;
		}
		inline string getNombre()const
		{
			return nombre;
		}
		inline int getnFallos() const
		{
			return nFallos;
		}
		inline int getPuntos()const
		{
			return Puntos;
		}
		inline void setNombre(const string &nombr)
		{
			nombre=nombr;
		}
		inline void setNFallos(const int &fallos)
		{
			nFallos=fallos;
		}
		inline void setPuntos(const int &puntos)
		{
			Puntos=puntos;
		}
		inline void setLog()
		{
			log=true;
		}
		inline void setAsignado()
		{
			asignado=false;
		}
		inline string getName()
		{
			return name;
		}
		inline string getPass()
		{
			return pass;
		}
		inline int getID() const
		{
			return id;
		}
		inline bool getAsignado()
		{
			return asignado;
		}
		inline bool getLog()
		{
			return log;
		}
		inline void setName(string nam)
		{
			name=nam;
		}
		inline void setPass(string pas)
		{
			pass=pas;
		}
		void sumarPuntos(int p);
		void comprarVocal();
		
};
