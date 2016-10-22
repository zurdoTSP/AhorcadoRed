#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <iostream.h>
#include <fstream>   // Biblioteca para el manejo de ficheros
#include <iostream>  // Biblioteca para la entrada-salida estándar
#include <cstdlib>   // Biblioteca estándar de C
#include <sstream>
#include <time.h>
#include <sys/time.h>


#include "jugadores.hpp"
#include "partidas.hpp"
#include "funciones.hpp"

/*
 * El servidor ofrece el servicio de incrementar un número recibido de un cliente
 */
using namespace redes;
using namespace std;


int main ( )
{
  
	/*---------------------------------------------------- 
		Descriptor del socket y buffer de datos                
	-----------------------------------------------------*/
	int sd, new_sd;
	struct sockaddr_in sockname, from;
	char buffer[500];
	fd_set lectura;
	fd_set auxlectura;
	FD_ZERO(&lectura);
	FD_ZERO(&auxlectura);
	socklen_t from_len;
	jugadores clientes[40];
	partidas mesas[10];
	int opcion;
	int numero_conectados=0;
	int encontrar;
	int posicion;
	int comprobar;
	int bandera=0;
	fichas todas[28];
	int m=0;
	int contador=0;
	int v[28];
	int variable=29;
	
	int j=0;

				j=0;
				for (int a = 0; a < 7; ++a)
				{
					todas[j].derecha=0;
					todas[j].izquierda=a;
					j++;
				}

				for (int b = 1;b < 7; ++b)
				{
					todas[j].derecha=1;
					todas[j].izquierda=b;
					j++;
				}

				for (int c= 2; c < 7; ++c)
				{
					todas[j].derecha=2;
					todas[j].izquierda=c;
					j++;
				}

				for (int d = 3; d < 7; ++d)
				{
					todas[j].derecha=3;
					todas[j].izquierda=d;
					j++;
				}

				for (int e = 4; e < 7; ++e)
				{
					todas[j].derecha=4;
					todas[j].izquierda=e;
					j++;
				}

				for (int f = 5; f < 7; ++f)
				{
					todas[j].derecha=5;
					todas[j].izquierda=f;
					j++;
				}

				todas[j].derecha=6;
				todas[j].izquierda=6;


	srand(time(0));
	struct hostent * host;

		/*---------------------------------------------------- 
		Abrir fichero              
	-----------------------------------------------------*/
	ofstream fichout;  
  
  	fichout.open("basedatos.txt");  
  	if (fichout.bad())
  	{
   		cout << "\n Incapaz de crear este o abrir el fichero \n";
  	}
 


	/* --------------------------------------------------
		Se abre el socket 
	---------------------------------------------------*/
  	sd = socket (AF_INET, SOCK_STREAM, 0);
	if (sd == -1)
	{
		perror("No se puede abrir el socket cliente\n");
    		exit (1);	
	}


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
   	
	/*-----------------------------------------------------------------------
		El servidor acepta una petición
	------------------------------------------------------------------------ */
		FD_SET(sd,&lectura);


		while(1){

			auxlectura=lectura;

			do
			{
				auxlectura=lectura;
				int Salida=select(FD_SETSIZE,&auxlectura,NULL,NULL,NULL);
					if(FD_ISSET(sd,&auxlectura))
					{
						/***************************************
							Nueva Conexion
						***************************************/
							if((new_sd = accept(sd, (struct sockaddr *)&from, &from_len)) == -1)
							{
								perror("Error aceptando peticiones");
								exit(1);
							}

							FD_SET(new_sd,&lectura);

					}

					else
					{
						/***************************************
							Antigua Conexion
						****************************************/
							for (int i = 0; i < FD_SETSIZE; ++i)
							{
								if(FD_ISSET(i,&auxlectura))
								{

									

									if(recv(i, buffer, 500, 0) == -1)
										perror("Error en la operación de recv");
									printf("el mensaje recibido fue: \n%s\n", buffer );
									opcion=comparador(buffer);
									encontrar=BuscarSocket(clientes,i,posicion,numero_conectados);
									if (encontrar==0)
									{
										posicion=numero_conectados;
										clientes[numero_conectados].setSocket(i);
										numero_conectados++;
										clientes[posicion].setOpc(0);
										clientes[posicion].setBan(0);

	
									}

								

									

									if(mesas[clientes[posicion].getPartida()].getTurno()==clientes[posicion].getTurno())
									{
										if(mesas[clientes[posicion].getPartida()].getIniciada()==1 )
										{
											if(clientes[posicion].getBan()==0)
											{
												clientes[posicion].setBan(1);
		
										string bufferaux1;
										
														
										bufferaux1=transformarCadena1(mesas[clientes[posicion].getPartida()],mesas[clientes[posicion].getPartida()].getNfichas());
										strcpy(buffer,bufferaux1.c_str());
										if(send(clientes[posicion].getSocket(),buffer,500,0) == -1)
											perror("Error enviando datos");
									}
										}
									}
								



									if (opcion==1)
									{
										char * nombre;
										int encontrado;
										nombre=(char *)malloc(20*sizeof(char));
										cortarUsuario(buffer,nombre);
										string nombre1(nombre) ;
										delete nombre;
										encontrado=BuscarJuagador(clientes,nombre1,numero_conectados);

										if (encontrado==1)
										{
											clientes[posicion].setEstado(1);
											if(send(clientes[posicion].getSocket(),"ESPERANDO PASS",500,0) == -1)
												perror("Error enviando datos");

										}

										else
										{
											if(send(clientes[posicion].getSocket(),"ERROR USUARIO",500,0) == -1)
												perror("Error enviando datos");
										}
											

									}

									if (opcion==2 && clientes[posicion].getEstado()==1)
									{
										char * contrasena;
										contrasena=(char *)malloc(20*sizeof(char));
										cortarContrasena(buffer,contrasena);
										string contrasena1(contrasena);
										delete contrasena;
										if(contrasena1==clientes[posicion].getContrasena())
										{
											clientes[posicion].setEstado(2);
											if(send(clientes[posicion].getSocket(),"OK\n",500,0) == -1)
												perror("Error enviando datos");
												

										}

										else 
										{
											if(send(clientes[posicion].getSocket(),"ERROR CONTRASEÑA",500,0) == -1)
												perror("Error enviando datos");
										}
										
									}

									if (opcion==3)
									{
										char * nombre;
										char * contrasena;
										nombre=(char *)malloc(20*sizeof(char));
										contrasena=(char *)malloc(20*sizeof(char));
										cortarUsuarioContrasena(buffer,nombre,contrasena);
										string nombre2(nombre);
										string contrasena2(contrasena);
										delete nombre;
										delete contrasena;
										clientes[posicion].setNombre(nombre2);
										clientes[posicion].setContrasena(contrasena2);
										if(send(clientes[posicion].getSocket(),"USUARIO REGISTRADO OK\n",500,0) == -1)
											perror("Error enviando datos");

									}

									if (opcion==4 && mesas[clientes[posicion].getPartida()].getTurno()==clientes[posicion].getTurno())
									{
										
										mesas[clientes[posicion].getPartida()].aumentarTurno();
										clientes[posicion].setOpc(0);
										clientes[posicion].setBan(0);
										
										if(send(clientes[posicion].getSocket(),"TURNO PASADO OK\n",500,0) == -1)
											perror("Error enviando datos");
										
										
									}
										
									
									if (opcion==5 && clientes[posicion].getEstado()==2)
									{
										buscarMesa(mesas,clientes[posicion]);
										mesas[clientes[posicion].getPartida()].aumentarUsuarios();
										mesas[clientes[posicion].getPartida()].aumentarTurno();
										clientes[posicion].setTurno(mesas[clientes[posicion].getPartida()].getTurno());
										if(send(clientes[posicion].getSocket(),"ESPERANDO JUGADORES\n",500,0) == -1)
											perror("Error enviando datos");
									}


									if (opcion==6 && mesas[clientes[posicion].getPartida()].getTurno()==clientes[posicion].getTurno())
									{
										fichas n;
										int direccion;
										cortarFichas(n,buffer,direccion);
										int comprobacion=comprobarFichas(n,clientes[posicion]);
										if (comprobacion==0)
										{
											
											if(send(clientes[posicion].getSocket(),"ERR ESA FICHA NO ES SUYA\n",500,0) == -1)
												perror("Error enviando datos");
										}
										else
										{
												mesas[clientes[posicion].getPartida()].insertarFicha(n,direccion);
												clientes[posicion].quitarFicha(n);
												mesas[clientes[posicion].getPartida()].aumentarTurno();
												clientes[posicion].setOpc(0);
												clientes[posicion].setBan(0);
												if(send(clientes[posicion].getSocket(),"COLOCADA\n",500,0) == -1)
												perror("Error enviando datos");
										}
										
									}

									if (opcion==7 && mesas[clientes[posicion].getPartida()].getTurno()==clientes[posicion].getTurno()) 
									{
										for (int u = 0; u < numero_conectados ; ++u)
										{
											if (clientes[u].getPartida()==clientes[posicion].getPartida())
											{
												clientes[u].setOpc(0);
												clientes[u].setBan(0);
												clientes[u].setEstado(2);
												mesas[clientes[u].getPartida()].setNumeroUsuarios(0);
												mesas[clientes[u].getPartida()].setNfichas(0);
												mesas[clientes[u].getPartida()].setIniciada(0);
												clientes[u].quitarFichas();
												mesas[clientes[u].getPartida()].quitarFichas();
												clientes[u].setPartida(98);
												if(send(clientes[u].getSocket(),"LA PARTIDA SE CERRO",500,0) == -1)
													perror("Error enviando datos");
												
												


											}
										}
									}

									if (opcion==8 && mesas[clientes[posicion].getPartida()].getIniciada()==1)
									{
										mesas[clientes[posicion].getPartida()].aumentarTurno();
										clientes[posicion].setOpc(0);
										clientes[posicion].setBan(0);
										
										if(send(clientes[posicion].getSocket(),"TURNO PASADO OK\n",500,0) == -1)
											perror("Error enviando datos");
									}

									if(opcion==9 && mesas[clientes[posicion].getPartida()].getIniciada()==1)
									{
										string bufferaux2;
										bufferaux2=transformarCadena(clientes[posicion],7);
										strcpy(buffer,bufferaux2.c_str());
										if(send(clientes[posicion].getSocket(),buffer,500,0) == -1)
														perror("Error enviando datos");
									}
								

									if(opcion==0)
									{
										
										if(send(clientes[posicion].getSocket(),"ERR",500,0) == -1)
													perror("Error enviando datos");
									}

									for (int z = 0; z < 10; ++z)
									{
										comprobar=mesas[z].comprobarEmpezar();
										
										
										if (comprobar==1)
										{
											mesas[z].setIniciada(1);
											mesas[z].setNfichas(0);
											contador=0;
											bandera=0;
											m=0;
											
											
											
											for (int j = 0; j < numero_conectados; ++j)
											{
												
												if (clientes[j].getPartida()==z)
												{

													for (int k = 0; k < 7; ++k)
													{
														
														do
														{
															bandera=0;
															m= rand()% 28;
															cout<<m<<endl;
															
															for (int xc = 0; xc < contador; ++xc)
															{
																if (m==v[xc])
																{
																	bandera=1;
																	
																}
															}

															if(bandera==0)
															{
																v[contador]=m;
																contador++;
															}
															
															
														} while (bandera==1);
														clientes[j].insertarFicha(todas[m]);
														//m++;
														
															

													}

													
													
													

												}
													
											}
																						
										}
										

									}
										for (int h = 0; h < numero_conectados; ++h)
										{
													if(mesas[clientes[h].getPartida()].getTurno()==clientes[h].getTurno())
													{
														if(mesas[clientes[h].getPartida()].getIniciada()==1)
														{
															if (clientes[h].getOpc()==0)
															{
																clientes[h].setOpc(1);
																if(send(clientes[h].getSocket(),"SU TURNO",500,0) == -1)
																perror("Error enviando datos");
																
															}
														}
													}
												}

											

												for (int x= 0; x < numero_conectados; ++x)
												{
													if (clientes[x].getNfichas()==0)
													{
														if (mesas[clientes[x].getPartida()].getIniciada()==1)
														{
															variable=clientes[x].getPartida();
															clientes[x].setOpc(0);
															clientes[x].setBan(0);
															
															clientes[x].setEstado(2);
															clientes[x].quitarFichas();
															mesas[clientes[x].getPartida()].setNumeroUsuarios(0);
															mesas[clientes[x].getPartida()].setNfichas(0);
															mesas[clientes[x].getPartida()].setIniciada(0);
															
															mesas[clientes[x].getPartida()].quitarFichas();
															clientes[x].setPartida(98);
															if(send(clientes[x].getSocket(),"GANADOR",500,0) == -1)
																perror("Error enviando datos");
														}
													}
												}
												for(int as=0; as < numero_conectados; ++as)
												{
													if (clientes[as].getPartida()==variable)
													{
															clientes[as].setOpc(0);
															clientes[as].setBan(0);
															clientes[as].setPartida(98);
															clientes[as].setEstado(2);
															clientes[as].quitarFichas();
															if(send(clientes[as].getSocket(),"PERDEDOR",500,0) == -1)
																perror("Error enviando datos");

													}
												}
												

									
									
								}
							}
						}
					}while(strcmp(buffer, "FIN")!=0);
			close(new_sd);
		}

		close(sd);
}

