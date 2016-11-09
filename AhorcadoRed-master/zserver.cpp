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
#include"lescribe.hpp"
#include"jgrupo.hpp"
#include <vector>
#define MSG_SIZE 350
#define MAX_CLIENTS 50
vector<string> dividir(char *cad);
void cortar(char *cad, char *cad2);
int buscarJ(vector<JIndividual> &j,int id);
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
	LesCribe log;
	bool primera=false;
	log.leerFichero();
	socklen_t from_len;
    fd_set readfds, auxfds;
    int salida;
	int ga;
    std::vector<int> arrayClientes(MAX_CLIENTS);
    std::vector<JIndividual> jugador;
    JGrupo jugadorG;
	    std::vector<string> comodin;
    int numClientes = 0;
    //contadores
    int i,j,k;
	bool terminado=false;
	bool senal=false;
	int recibidos;
    char identificador[MSG_SIZE];

    int on, ret;
	vector<Usuario> user;
///////////CADENA QUE GUARDA LA OTRA
char tab2[25];
char cad2[250]="";
int qa;
	bool turno=false;
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
					//jugador.push_back(JIndividual(new_sd));
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
					user.erase(user.begin()+i);
					qa=buscarJ(jugador,i);
					if(qa!=500)
					{
						jugador.erase(jugador.begin()+qa);
					}

                                }
			
				
                                else{
					for(int l=0;l<user.size();l++)
					{
						
						if(user[l].getID()==i)
						{
							
							if(user[l].getLog()==false)
							{
								if(strncmp(buffer, "REGISTRO", 7)==0)
								{
									buffer[strlen(buffer)-1]='\0';
									comodin=dividir(buffer);
									log.cargarEnFichero(comodin[2],comodin[4]);
								}
//REGISTRO –u usuario –p password
								qa = strncmp(buffer, "USUARIO", 6);
								cortar(buffer,cad2);
								if(qa==0)
								{
									printf("usuario metido\n");
									cad2[strlen(cad2)-1]='\0';
									sprintf(identificador,"id semi logeado:\n %d",i);
									bzero(buffer,sizeof(buffer));
									strcpy(buffer,identificador);
									user[l].setName(string(cad2));
								}
								else
								{
									qa = strncmp(buffer, "PASSWORD", 7);
									bzero(cad2,sizeof(cad2));
									cortar(buffer,cad2);
									if(qa==0)
									{
										cad2[strlen(cad2)-1]='\0';
										printf("clave metido\n");
										user[l].setPass(string(cad2));
										if(log.buscar(user[l].getName(),user[l].getPass()))
										{
											user[l].setLog();
										sprintf(identificador,"+0k. Usuario conectado:\n %d\n",i);
										bzero(buffer,sizeof(buffer));
										strcpy(buffer,identificador);
										}
										else
										{
											sprintf(identificador,"Err. Error en la validación\n%d\n",i);
											bzero(buffer,sizeof(buffer));
											strcpy(buffer,identificador);
										}

									}
								
								}

							}
							else
							{
								
								bzero(cad2,sizeof(cad2));
								cortar(buffer,cad2);
								if(qa = strncmp(buffer, "PARTIDA-INDIVIDUAL", 17)==0)
								{
									jugador.push_back(JIndividual(user[l].getID()));
									sprintf(identificador,"bien venido:\n %s\n%s",user[l].getName().c_str(),jugador[jugador.size()-1].getEspacio().c_str());
									bzero(buffer,sizeof(buffer));
									strcpy(buffer,identificador);
									//user[l].setPass(string(cad2));
										
								}
								if(qa = strncmp(buffer, "PARTIDA-GRUPO",13)==0)
								{
									jugadorG.anadirID(user[l].getID());
									jugadorG.setNombre(user[l].getName());
									if(senal==false)
									{
										jugadorG.setIDActual(user[l].getID());
										senal=true;
									}

									bzero(buffer,sizeof(buffer));
									//strcpy(buffer,"hoassa\n");
									//user[l].setPass(string(cad2));
										
								}
								

							}
							send(user[l].getID(),buffer,strlen(buffer),0);
						}
					
					}
					// = strncmp(buffer, "vocal", 4);
					cortar(buffer,cad2);
					for(int z=0;z<jugador.size();z++)
					{
						if(jugador[z].getID()==i)
						{
							
							if(strncmp(buffer, "vocal", 4)==0 || strncmp(buffer, "consonante", 10)==0)
							{

							 	if(jugador[z].comprobar(cad2)==true)
								{

			  						//TERMINAR CON MAINCUARTO
									strcpy(tab2, jugador[z].getEspacio().c_str());
									sprintf(identificador,"+++++++++++++++++\nCORRECTO:\n+++++++++++++++++\n %s",tab2);
									bzero(buffer,sizeof(buffer));
									strcpy(buffer,identificador);
								}
								else
								{

									sprintf(identificador,"+++++++++++++++++\nINCORRECTO:\n+++++++++++++++++\n %s",buffer);
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
												jugador[z].setPos(jugador[z].getPos()+1);
												jugador[z].setEspacios();
												jugador[z].controlPuntos();					
										sprintf(identificador,"RESUELTO GANASTE\n%s\nPuntos:%d",jugador[z].getEspacio().c_str(),jugador[z].getPuntos());
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
                                            		send(arrayClientes[z],buffer,strlen(buffer),0);
					}


///////////////////////////////////////////////////////////////GRUPAL/////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////AQUÍ////////////////////////////////////////////////////////////////// 
					
					for(int z=0;z<jugadorG.getNID();z++)
					{
						
						if(jugadorG.getID(z)==i)
						{
							cout<<jugadorG.getIDActual()<<"  iddddddd\n";

								if(jugadorG.getNID()>1)
								{
									if(primera==false)
									{
										primera=true;
										for(int pru=0;pru<jugadorG.getNID();pru++)
										{
											strcpy(tab2, jugadorG.getEspacio().c_str());
											sprintf(identificador,"¡EMPIEZA!\n %s",tab2);
											bzero(buffer,sizeof(buffer));
											strcpy(buffer,identificador);
											send(jugadorG.getID(pru),buffer,strlen(buffer),0);
											bzero(tab2,sizeof(tab2));
											
										}
									}
								if(jugadorG.getIDActual()==i)
								{
									jugadorG.setIDActual();
									bzero(cad2,sizeof(cad2));
									cortar(buffer,cad2);
									cad2[strlen(cad2)-1]='\0';
									if(strncmp(buffer, "vocal", 4)==0)
									{
									
										if(jugadorG.getPuntos(z)>50)
										{
								
											jugadorG.setPuntos(z,0,50);
										 	if(jugadorG.comprobar(cad2)==true)
											{
											
						  						//TERMINAR CON MAINCUARTO
												strcpy(tab2, jugadorG.getEspacio().c_str());
												sprintf(identificador,"+++++++++++++++++\nCORRECTO:\n+++++++++++++++++\n %s el jugaodor %s tiene\n puntos: %d",tab2, jugadorG.getNombre(z).c_str(),jugadorG.getPuntos(z));
												bzero(buffer,sizeof(buffer));
												strcpy(buffer,identificador);
											}
											else
											{

												sprintf(identificador,"+++++++++++++++++FALLASTE:\n+++++++++++++++++\n %s el jugaodor %s tiene\n puntos: %d",tab2, jugadorG.getNombre(z).c_str(),jugadorG.getPuntos(z));
												bzero(buffer,sizeof(buffer));
												strcpy(buffer,identificador);
											}
										}
									//	else

									}
									if(strncmp(buffer, "consonante", 10)==0)
									{
										 	if(jugadorG.comprobar(cad2)==true)
											{
												jugadorG.setPuntos(z,1,50);
												strcpy(tab2, jugadorG.getEspacio().c_str());
						  						//TERMINAR CON MAINCUARTO
											
												sprintf(identificador,"+++++++++++++++++\nCORRECTO:\n+++++++++++++++++\n %s el jugaodor %s tiene\n puntos: %d",tab2, jugadorG.getNombre(z).c_str(),jugadorG.getPuntos(z));
												bzero(buffer,sizeof(buffer));
												strcpy(buffer,identificador);
											}
											else
											{

												sprintf(identificador,"+++++++++++++++++FALLASTE:\n+++++++++++++++++\n %s el jugaodor %s tiene\n puntos: %d",tab2, jugadorG.getNombre(z).c_str(),jugadorG.getPuntos(z));
												bzero(buffer,sizeof(buffer));
												strcpy(buffer,identificador);
											}

									}
									else
									{

										if(qa==0)
										{

											if(jugadorG.resolver(cad2)==true)
											{
								
				
												sprintf(identificador,"RESUELTO GANO:%s\n",jugadorG.getNombre(z).c_str());
										bzero(buffer,sizeof(buffer));
												strcpy(buffer,identificador);
											}
											else
											{
											
												ga=jugadorG.maxPuntos();
												
												sprintf(identificador,"HA GANADO:%s CON %d PUNOTS",jugadorG.getNombre(ga).c_str(),jugadorG.getPuntos(ga));
												bzero(buffer,sizeof(buffer));
												strcpy(buffer,identificador);
											}
							
											terminado=true;
											senal=false;
											primera=false;
											jugadorG.setPos(jugadorG.getPos()+1);
											jugadorG.setEspacios();
											cout<<"estoy acá?\n";
										}
									}
									for(int w=0;w<jugadorG.getNID();w++)
									{

										send(jugadorG.getID(w),buffer,strlen(buffer),0);
									}
									if(terminado==true)
									{
										terminado=false;
										jugadorG.borrar();
											
									}
								
								}
								else
								{
									bzero(buffer,sizeof(buffer));
									strcpy(buffer,"\nErr. Debe esperar su turno");
									send(jugadorG.getID(z),buffer,strlen(buffer),0);
								}
							}
							else
							{

								bzero(buffer,sizeof(buffer));
								strcpy(buffer,"\nErr. no hay suficientes jugadores");
								send(jugadorG.getID(z),buffer,strlen(buffer),0);
							}
								
						}

					}
					
					bzero(cad2,sizeof(cad2));




                                }


                            }
                            //Si el cliente introdujo ctrl+c
                            if(recibidos== 0)
                            {
                                printf("El socket %d, ha introducido ctrl+c\n", i);
                                //Eliminar ese socket
				//jugador.erase(jugador.begin()+i);
				user.erase(user.begin()+i);
				qa=buscarJ(jugador,i);
				if(qa!=500)
				{
					jugador.erase(jugador.begin()+qa);
				}
				//BUSCAR SI EXISTE JUGADOR Y SI NO, te kill YOU la vie
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
vector<string> dividir(char *cad)
{
	vector<string> a;
	string x;
	for(int i=0;i<strlen(cad);i++)
	{
		cout<<cad[i]<<"\n";
		if(cad[i]!=' ')
		{
			x=x+cad[i];
		}
		else
		{
			a.push_back(x);
			x="";
		}

	}
	a.push_back(x);
	cout<<cad;
	return a;
}
int buscarJ(vector<JIndividual> &j,int id)
{
	int v=500;
	for(int i=0;i<j.size();i++)
	{
		if(j[i].getID()==id)
		{
			v=i;
		}
	}
	return v;
}
