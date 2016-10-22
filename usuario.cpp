#include"usuario.hpp"

void Usuario::sumarPuntos(int p)
{
	setPuntos(getPuntos()+p);

}
void Usuario::comprarVocal()
{
	if(getPuntos()>50)
	{
		setPuntos(getPuntos()-50);
	}
}

