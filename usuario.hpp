#include<iostream>
using namespace std;
class Usuario
{
	private:
		string nombre;
		int nFallos;
		int Puntos;
		int id;
	public:
		Usuario(string nomb, int _id)
		{
			setNombre(nomb);
			setNFallos(0);
			setPuntos(0);
			id=_id;
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
		void sumarPuntos(int p);
		void comprarVocal();
		
};
