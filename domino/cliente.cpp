
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>

#include <unistd.h>
#include <string.h>
#include <iostream.h>
#include <arpa/inet.h>

using namespace std;
int main ( )
{
  
	/*---------------------------------------------------- 
		Descriptor del socket y buffer de datos                
	-----------------------------------------------------*/
	int sd;
	struct sockaddr_in sockname;
	
	char buffer[500];
	socklen_t len_sockname;
	fd_set lectura;
	

	
	/* --------------------------------------------------
		Se abre el socket 
	---------------------------------------------------*/
  	sd = socket (AF_INET, SOCK_STREAM, 0);
	if (sd == -1)
	{
		perror("No se puede abrir el socket cliente\n");
    		exit (1);	
	}

	

	/* ------------------------------------------------------------------
		Se rellenan los campos de la estructura con la IP del 
		servidor y el puerto del servicio que solicitamos
	-------------------------------------------------------------------*/
	sockname.sin_family = AF_INET;
	sockname.sin_port = htons(2000);
	sockname.sin_addr.s_addr =  inet_addr("127.0.0.1");

	/* ------------------------------------------------------------------
		Se solicita la conexión con el servidor
	-------------------------------------------------------------------*/
	len_sockname = sizeof(sockname);
	
	if (connect(sd, (struct sockaddr *)&sockname, len_sockname) == -1)
	{
		perror ("Error de conexión");
		exit(1);
	}
		
		int bandera=0;
		int salida;
		FD_SET(sd,&lectura);
	/* ------------------------------------------------------------------
		Se transmite la información
	-------------------------------------------------------------------*/

	cout<<"Atencion las fichas |-1|-1| ocupan el espacio de una usada no deben colocarse en el tablero "<<endl;
	do
	{
			
			string auxa="ESPERANDO JUGADORES\n";
			string auxb="GANADOR";
			string auxc="PERDEDOR";

			if (bandera==1)
			{
				salida=select(sd+1,&lectura,NULL,NULL,NULL);
				if(salida==-1)
				{
					printf("Error en el select\n");
				}

				else
				{
					if(recv(sd, buffer, 500, 0) == -1)
						perror("Error en la operación de recv");
					printf("el mensaje recibido fue: \n%s\n", buffer );
					string aux(buffer);
					if (aux==auxb)
					{
						bandera=0;
					}
					if (aux==auxc)
					{
						bandera=0;
					}
					
					}					

			}
			puts("Teclee el mensaje a transmitir");
			gets(buffer);
			if(send(sd,buffer,500,0) == -1)
				perror("Error enviando datos");

			if(recv(sd, buffer, 500, 0) == -1)
				perror("Error en la operación de recv");
			printf("el mensaje recibido fue: \n%s\n", buffer );
			string aux(buffer);
			if(aux==auxa)
			{
					bandera=1;
					
			}	
		}while(strcmp(buffer, "FIN") != 0);
		
		close(sd);
}
		