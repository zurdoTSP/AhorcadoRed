#include<iostream>
using namespace std;
class Usuario
{
	private:
		string nombre;
		int id;
		string name;
		string pass;
		//bool asignado;
		bool log;
	public:
		Usuario(string nomb, int _id)
		{
			setNombre(nomb);
			id=_id;
			name="";
			pass="";
			//asignado=false;
			log=false;
		}
		inline string getNombre()const
		{
			return nombre;
		}


		inline void setNombre(const string &nombr)
		{
			nombre=nombr;
		}

		inline void setLog()
		{
			log=true;
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

		
};
