#include <iostream>
#include <fstream>
#include <cstring>
#include <list>
#include <string>
#include<vector>
using namespace std;
struct tipoRegistro {
   string nombre;
	string pass;
	
};
class LesCribe
{
	private:
		list<tipoRegistro> usuarios;
		vector<string> conectado;
	public:
		LesCribe()
		{

		}
		inline void cargarEnFichero(string nomb,string pas)
		{
			
			tipoRegistro pepe;
			ofstream ficheroSalida;
			pepe.nombre=nomb;
			pepe.pass=pas;
			if(buscar(pepe)==false)
			{
				usuarios.push_back(pepe);
				ficheroSalida.open ("ficheroTexto.txt", ios::app );
				ficheroSalida << nomb+" "+pas+"\n";
				ficheroSalida.close();
			}
			
		}
		inline bool comCon(string name)
		{
			bool pal=false;
			for (int i=0;i<conectado.size();i++)
			{
				if(conectado[i]==name)
				{
					pal=true;
				}
				return pal;
			}
		}
		inline void leerFichero()
		{
			ifstream ficheroEntrada;
			string frase;
			int name=0;
			tipoRegistro pepe;
			string cad="";
			ficheroEntrada.open ( "ficheroTexto.txt" , ios::in);
			if (ficheroEntrada.is_open())
			{

				while (! ficheroEntrada.eof() )
				{
					getline (ficheroEntrada,frase);
					
					

					for(int i=0;i<frase.length();i++)
					{
						if(frase[i]==' ')
						{
							//std::cout<<frase<<"=\n";
							cout<<"\n";
							std::cout<<cad<<"\n";
							pepe.nombre=cad;
							cad="";
							
						}
						else
						{
							cad=cad+frase[i];
						}
						if(i==(frase.length()-1))
						{
							std::cout<<cad<<"\n";
							pepe.pass=cad;
							usuarios.push_back(pepe);
							cad="";
						}
					}
					//cout<<frase.length()<<"\n";
				}

				ficheroEntrada.close();
   			}
			
		}
		inline bool buscar(tipoRegistro usi)
		{
			bool busco=false;
			list<tipoRegistro>::iterator it = usuarios.begin();
			while( it != usuarios.end() )
			{
				if(it->nombre==usi.nombre)
				{
					if(it->pass==usi.pass)
					{
						busco=true;
					}
				}
				
				*it++;
			}
			return busco;
		}
		inline bool buscar(string nom,string pas)
		{
			bool busco=false;
			list<tipoRegistro>::iterator it = usuarios.begin();
			while( it != usuarios.end() )
			{
				if(it->nombre==nom)
				{
					if(it->pass==pas)
					{
						busco=true;
						conectado.push_back(nom);
					}
				}
				
				*it++;
			}
			return busco;
		}
		inline bool buscar(string nom)
		{
			bool busco=false;
			list<tipoRegistro>::iterator it = usuarios.begin();
			while( it != usuarios.end() )
			{
				if(it->nombre==nom)
				{
					busco=true;
					
				}
				
				*it++;
			}
			return busco;
		}
		

		
};

