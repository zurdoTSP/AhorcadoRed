#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include<signal.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>
#include"usuario.hpp"
#include"jindividual.hpp"
#include <list>

#include <vector>
#define MSG_SIZE 250
#define MAX_CLIENTS 50

void cortar(char *cad, char *cad2);
/*
 * El servidor ofrece el servicio de un chat
 */
using namespace std;
void manejador(int signum);
void salirCliente(int socket, fd_set * readfds, int * numClientes, vector<int> arrayClientes);



int main ( )
{


	/*----------------------------------------------------
		Descriptor del socket y buffer de datos
	-----------------------------------------------------*/
	int sd, new_sd;
	struct sockaddr_in sockname, from;
	char buffer[MSG_SIZE];
	char buffer2;
	socklen_t from_len;
    fd_set readfds, auxfds;
    int salida;
    std::vector<int> arrayClientes(MAX_CLIENTS);
    std::vector<JIndividual> jugador;
    int numClientes = 0;
    //contadores
    int i,j,k;
	int recibidos;
    char identificador[MSG_SIZE];

    int on, ret;
	list<Usuario> user;
///////////CADENA QUE GUARDA LA OTRA
char tab2[25];
char cad2[250]="";
int qa;
	/* --------------------------------------------------
		Se abre el socket
	---------------------------------------------------*/
  	sd = socket (AF_INET, SOCK_STREAM, 0);
	if (sd == -1)
	{
		perror("No se puede abrir el socket cliente\n");
    		exit (1);
	}

    // Activaremos una propiedad del socket que permitir· que otros
    // sockets puedan reutilizar cualquier puerto al que nos enlacemos.
    // Esto permitir· en protocolos como el TCP, poder ejecutar un
    // mismo programa varias veces seguidas y enlazarlo siempre al
    // mismo puerto. De lo contrario habrÌa que esperar a que el puerto
    // quedase disponible (TIME_WAIT en el caso de TCP)
    on=1;
    ret = setsockopt( sd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));



	sockname.sin_family = AF_INET;
	sockname.sin_port = htons(2000);
	sockname.sin_addr.s_addr =  INADDR_ANY;

	if (bind (sd, (struct sockaddr *) &sockname, sizeof (sockname)) == -1)
	{
		perror("Error en la operación bind");
		exit(1);
	}


   	/*---------------------------------------------------------------------
		Del las peticiones que vamos a aceptar sólo necesitamos el
		tamaño de su estructura, el resto de información (familia, puerto,
		ip), nos la proporcionará el método que recibe las peticiones.
   	----------------------------------------------------------------------*/
		from_len = sizeof (from);


		if(listen(sd,1) == -1){
			perror("Error en la operación de listen");
			exit(1);
		}

    //Inicializar los conjuntos fd_set
    FD_ZERO(&readfds);
    FD_ZERO(&auxfds);
    FD_SET(sd,&readfds);
    FD_SET(0,&readfds);


    //Capturamos la señal SIGINT (Ctrl+c)
    signal(SIGINT,manejador);

	/*-----------------------------------------------------------------------
		El servidor acepta una petición
	------------------------------------------------------------------------ */
		while(1){

            //Esperamos recibir mensajes de los clientes (nuevas conexiones o mensajes de los clientes ya conectados)

            auxfds = readfds;

            salida = select(FD_SETSIZE,&auxfds,NULL,NULL,NULL);

            if(salida > 0){


                for(i=0; i<FD_SETSIZE; i++){

                    //Buscamos el socket por el que se ha establecido la comunicación
                    if(FD_ISSET(i, &auxfds)) {

                        if( i == sd){

                            if((new_sd = accept(sd, (struct sockaddr *)&from, &from_len)) == -1){

                                perror("Error aceptando peticiones");
                            }
                            else// COGEMOS Y ENVIAMOS CON   send(new_sd,buffer,strlen(buffer),0); al que se conecto, y miramos a todos menos al último y le pasamos que se coencto
                            {
				///////////////////////////////////////USUARIO ENTRANDO//////////////////////////////////////////////////
                                if(numClientes < MAX_CLIENTS){
                                    arrayClientes[numClientes] = new_sd;//AQUí TENEMOS QUE REGISTRAR EL CLIENTE NEW
					//++++++++++++++++++++++++++
					

					user.push_back(Usuario("prueba",new_sd));
					jugador.push_back(JIndividual(new_sd));
                                    numClientes++;
                                    FD_SET(new_sd,&readfds);

                                    strcpy(buffer, "Bienvenido al chat\n");

                                    send(new_sd,buffer,strlen(buffer),0);

                                    for(j=0; j<(numClientes-1);j++){//aviso a todos menos al último

                                        bzero(buffer,sizeof(buffer));//PONEMOS CADENA a 0
                                        sprintf(buffer, "Nuevo Cliente conectado: %d\n",new_sd);
                                        send(arrayClientes[j],buffer,strlen(buffer),0);
                                    }
                                }
				/////////////////////////////////////////////////////////////////////////////////////////////////////////
                                else ///TOPE ALCANZADO
                                {
                                    bzero(buffer,sizeof(buffer));
                                    strcpy(buffer,"Demasiados clientes conectados\n");
                                    send(new_sd,buffer,strlen(buffer),0);
                                    close(new_sd);
                                }

                            }


                        }
                        else if (i == 0){
                            //Se ha introducido información de teclado
                            bzero(buffer, sizeof(buffer));
                            fgets(buffer, sizeof(buffer),stdin);
				//SE ESCRIBIO ALGO
                            //Controlar si se ha introducido "SALIR", cerrando todos los sockets y finalmente saliendo del servidor. (implementar)
                            if(strcmp(buffer,"SALIR\n") == 0){

                                for (j = 0; j < numClientes; j++){
                                    send(arrayClientes[j], "Desconexion servidor\n", strlen("Desconexion servidor\n"),0);
                                    close(arrayClientes[j]);
                                    FD_CLR(arrayClientes[j],&readfds);
                                }
                                    close(sd);
                                    exit(-1);


                            }
                            //Mensajes que se quieran mandar a los clientes (implementar)

                        }
                        else{
                            bzero(buffer,sizeof(buffer));

                            recibidos = recv(i,buffer,sizeof(buffer),0);


				//MENSAJE RECIVIDO AHORA ANALIZAMOS
                            if(recibidos > 0){

                                if(strcmp(buffer,"SALIR\n") == 0){

                                    salirCliente(i,&readfds,&numClientes,arrayClientes);

                                }


                                else{
					qa = strncmp(buffer, "vocal", 4);
					cortar(buffer,cad2);
					for(int z=0;z<jugador.size();z++)
					{
						if(jugador[z].getID()==i)
						{
							if(qa==0)
							{

							 	if(jugador[z].comprobar(cad2)==true)
								{

			  						//TERMINAR CON MAINCUARTO
									strcpy(tab2, jugador[z].getEspacio().c_str());
									sprintf(identificador,"CORRECTO:\n %s",tab2);
									bzero(buffer,sizeof(buffer));
									strcpy(buffer,identificador);
								}
								else
								{

									sprintf(identificador,"INCORRECTO:\n %s",buffer);
									bzero(buffer,sizeof(buffer));
									strcpy(buffer,identificador);
								}
							}
							else
							{
								qa = strncmp(buffer, "resolver", 6);
								if(qa==0)
								{
									cad2[strlen(cad2)-1]='\0';
									if(jugador[z].resolver(cad2)==true)
									{
								

				  						//TERMINAR CON MAINCUARTO
								
										sprintf(identificador,"RESUELTO GANASTE\n");
										bzero(buffer,sizeof(buffer));
										strcpy(buffer,identificador);
									}
									else
									{

										sprintf(identificador,"INCOMPETENTE! has fallado");
										for(int i=0;i<string(cad2).size();i++)
										{
											cout<<string(cad2)[i]<<"\n";
										}
										bzero(buffer,sizeof(buffer));
										strcpy(buffer,identificador);
									}
							
					
								}
							}
						}
					}
					bzero(cad2,sizeof(buffer));
                                 	for(j=0; j<numClientes; j++)
					{
                                        	if(arrayClientes[j] == i)
						{
                                            		send(arrayClientes[j],buffer,strlen(buffer),0);
						}
					}


                                }


                            }
                            //Si el cliente introdujo ctrl+c
                            if(recibidos== 0)
                            {
                                printf("El socket %d, ha introducido ctrl+c\n", i);
                                //Eliminar ese socket
                                salirCliente(i,&readfds,&numClientes,arrayClientes);
                            }
                        }
                    }
                }
            }
		}

	close(sd);
	return 0;

}

void salirCliente(int socket, fd_set * readfds, int * numClientes, vector<int> arrayClientes){

    char buffer[250];
    int j;

    close(socket);
    FD_CLR(socket,readfds);

    //Re-estructurar el array de clientes
    for (j = 0; j < (*numClientes) - 1; j++)
        if (arrayClientes[j] == socket)
            break;
    for (; j < (*numClientes) - 1; j++)
        (arrayClientes[j] = arrayClientes[j+1]);

    (*numClientes)--;

    bzero(buffer,sizeof(buffer));
    sprintf(buffer,"Desconexión del cliente: %d\n",socket);

    for(j=0; j<(*numClientes); j++)
        if(arrayClientes[j] != socket)
            send(arrayClientes[j],buffer,strlen(buffer),0);


}


void manejador (int signum){
    printf("\nSe ha recibido la señal sigint\n");
    signal(SIGINT,manejador);

    //Implementar lo que se desee realizar cuando ocurra la excepción de ctrl+c en el servidor
}


void cortar(char *cad, char *cad2)
{
	int i=0;
	int j=0;
	bool senal=false;
	while(cad[i]!='\0')
	{
		if(cad[i]==' ')
		{
			senal=true;
			
		}
		i++;
		if(senal==true)
		{
			cad2[j]=cad[i];
			j++;
		}
		
	}
	//cad2[j]='\0';
	cout<<cad2<<"\n";
}