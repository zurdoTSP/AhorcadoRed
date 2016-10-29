#include<iostream>
using namespace std;
class Usuario
{
	private:
		string nombre;
		int nFallos;
		int Puntos;
		int id;
		bool name;
		bool pass;
	public:
		Usuario(string nomb, int _id)
		{
			setNombre(nomb);
			setNFallos(0);
			setPuntos(0);
			id=_id;
			name=false;
			pass=false;
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
		inline bool getName()
		{
			return name;
		}
		inline bool getPass()
		{
			return pass;
		}
		inline void setName()
		{
			name=true;
		}
		inline void setPass()
		{
			name=true;
		}
		void sumarPuntos(int p);
		void comprarVocal();
		
};
