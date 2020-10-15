

#include <stdio.h>      // libreria estandar
#include <stdlib.h>     // para usar exit y funciones de la libreria standard
#include <string.h>
#include <pthread.h>    // para usar threads
#include <semaphore.h>  // para usar semaforos
#include <unistd.h>


#define LIMITE 50

//creo sem mutex para salar,XXXXXXXXXXXXXXXXXXXXXXXXX 
pthread_mutex_t sem_salar;
pthread_mutex_t sem_hornear;
pthread_mutex_t sem_cocinar_medallones;
pthread_mutex_t sem_validar;


//creo estructura de semaforos 
struct semaforos {
    sem_t sem_mezclar;

	//poner demas semaforos aqui
	sem_t sem_salar;
	sem_t sem_hornear;
	sem_t sem_armar_medallones;
	sem_t sem_cocinar_medallones;
	sem_t sem_armar_hamburguesas;
	sem_t sem_validar;
};



//creo los pasos con los ingredientes
struct paso {
   char accion [LIMITE];
   char ingredientes[4][LIMITE];
   
};

//creo los parametros de los hilos 
struct parametro {
 int equipo_param;
 struct semaforos semaforos_param;
 struct paso pasos_param[8];
};

//funcion para imprimir las acciones y los ingredientes de la accion
void* imprimirAccion(void *data, char *accionIn) {
	FILE * LOG = fopen("log.txt","a");
	fseek (LOG, 0, SEEK_END);
	struct parametro *mydata = data;
	//calculo la longitud del array de pasos 
	int sizeArray = (int)( sizeof(mydata->pasos_param) / sizeof(mydata->pasos_param[0]));
	//indice para recorrer array de pasos 
	int i;
	for(i = 0; i < sizeArray; i ++){
		//pregunto si la accion del array es igual a la pasada por parametro (si es igual la funcion strcmp devuelve cero)
		if(strcmp(mydata->pasos_param[i].accion, accionIn) == 0){
		
		fprintf(LOG,"x--------------------------------------------------x\n");
		fprintf(LOG,"\tEquipo %d - accion %s \n " , mydata->equipo_param, mydata->pasos_param[i].accion);


		printf("x--------------------------------------------------x\n");
		printf("\tEquipo %d - accion %s \n " , mydata->equipo_param, mydata->pasos_param[i].accion);
		//calculo la longitud del array de ingredientes
		int sizeArrayIngredientes = (int)( sizeof(mydata->pasos_param[i].ingredientes) / sizeof(mydata->pasos_param[i].ingredientes[0]) );
		//indice para recorrer array de ingredientes
		int h;
		fprintf(LOG,"\tEquipo %d -----------ingredientes : ----------\n",mydata->equipo_param);
		printf("\tEquipo %d -----------ingredientes : ----------\n",mydata->equipo_param); 
			for(h = 0; h < sizeArrayIngredientes; h++) {
				//consulto si la posicion tiene valor porque no se cuantos ingredientes tengo por accion 
				if(strlen(mydata->pasos_param[i].ingredientes[h]) != 0) {
							fprintf(LOG,"\tEquipo %d ingrediente  %d : %s \n",mydata->equipo_param,h,mydata->pasos_param[i].ingredientes[h]);
							printf("\tEquipo %d ingrediente  %d : %s \n",mydata->equipo_param,h,mydata->pasos_param[i].ingredientes[h]);
				}
			}
		}
	}
	fprintf(LOG,"--------------------------------------------------\n");
	fclose(LOG);
	printf("--------------------------------------------------\n");
}

//funcion para tomar de ejemplo
void* cortar(void *data) {
	//creo el nombre de la accion de la funcion 
	char *accion = "cortar";
	//creo el puntero para pasarle la referencia de memoria (data) del struct pasado por parametro (la cual es un puntero). 
	struct parametro *mydata = data;
	//llamo a la funcion imprimir le paso el struct y la accion de la funcion
	imprimirAccion(mydata,accion);
	//uso sleep para simular que que pasa tiempo
	usleep( 20000 );
	//doy la señal a la siguiente accion (cortar me habilita mezclar)
    sem_post(&mydata->semaforos_param.sem_mezclar); //DESCOMENTAR PARA LUEGO CONTINUAR CON LA PROXIMA ACCION
	
    pthread_exit(NULL);
}

void* cortar2(void *data) {
	//creo el nombre de la accion de la funcion 
	char *accion = "cortar2";
	//creo el puntero para pasarle la referencia de memoria (data) del struct pasado por parametro (la cual es un puntero). 
	struct parametro *mydata = data;
	//llamo a la funcion imprimir le paso el struct y la accion de la funcion
	imprimirAccion(mydata,accion);
	//uso sleep para simular que que pasa tiempo
	usleep( 20000 );
	//doy la señal a la siguiente accion (cortar me habilita mezclar)
    
	
    pthread_exit(NULL);
}

void* mezclar(void *data){
	
	//genero nombre de la accion
	char *accion = "mezclar";
	//creo el puntero para pasarle la referencia de memoria (data) del struct pasado por parametro (la cual es un puntero). 
	
	struct parametro *mydata = data;

	sem_wait(&mydata->semaforos_param.sem_mezclar);
	//llamo funcion para imprimir, paso struct y accion
	imprimirAccion(mydata,accion);
	//tiempo de simulacion
	usleep( 20000 );
	//doy la señal a la siguiente accion (cortar me habilita mezclar)
	//AGREGAR 
	sem_post (&mydata->semaforos_param.sem_salar);
	
	pthread_exit(NULL);
	}
	
void* salar(void *data){
	
	//SECCION CRITICA BLOQUEO SEM MUTEX
	//printf("bloqueo seccion critica salar\n",equipo_param);
	
	pthread_mutex_lock(&sem_salar);
	

	//genero nombre de la accion
	char *accion = "salar";
	//creo el puntero para pasarle la referencia de memoria (data) del struct pasado por parametro (la cual es un puntero). 
	
	struct parametro *mydata = data;

	FILE * LOG = fopen("log.txt","a");
	fseek (LOG, 0, SEEK_END);
	fprintf(LOG,"\tEquipo %d toma el salero\n " , mydata->equipo_param);

	printf("\tEquipo %d toma el salero\n " , mydata->equipo_param);

	sem_wait(&mydata->semaforos_param.sem_salar);
	//llamo funcion para imprimir, paso struct y accion
	imprimirAccion(mydata,accion);
	//tiempo de simulacion
	usleep( 20000 );
	//doy la señal a la siguiente accion (cortar me habilita mezclar)
	//AGREGAR 
	sem_post (&mydata->semaforos_param.sem_armar_medallones);
	
	//LIBERO SEMAFORO MUTEX PARA SALAR
	fprintf(LOG,"\tEquipo %d devuelve el salero\n " , mydata->equipo_param);
	fclose(LOG);
	printf("\tEquipo %d devuelve el salero\n " , mydata->equipo_param);
	pthread_mutex_unlock(&sem_salar);
	

	pthread_exit(NULL);
	}
	
void* hornear(void *data){
	
	//SECCION CRITICA BLOQUEO SEM MUTEX
	//printf("bloqueo seccion critica hornear pan\n",equipo_param);
	
	pthread_mutex_lock(&sem_hornear);
	

	//genero nombre de la accion
	char *accion = "hornear";
	//creo el puntero para pasarle la referencia de memoria (data) del struct pasado por parametro (la cual es un puntero). 
	
	struct parametro *mydata = data;

	FILE * LOG = fopen("log.txt","a");
	fseek (LOG, 0, SEEK_END);
	fprintf(LOG,"\tEquipo %d empieza a usar el horno\n " , mydata->equipo_param);
	
	printf("\tEquipo %d empieza a usar el horno\n " , mydata->equipo_param);

	//sem_wait(&mydata->semaforos_param.sem_hornear);
	//llamo funcion para imprimir, paso struct y accion
	imprimirAccion(mydata,accion);
	//tiempo de simulacion
	usleep( 20000 );
	//doy la señal a la siguiente accion
	//AGREGAR 
	
	
	//LIBERO SEMAFORO MUTEX PARA SALAR
	fprintf(LOG,"\tEquipo %d deja de usar el horno\n " , mydata->equipo_param);
	fclose(LOG);
	printf("\tEquipo %d deja de usar el horno\n " , mydata->equipo_param);
	pthread_mutex_unlock(&sem_hornear);
	

	pthread_exit(NULL);
	}
	

void* armar_medallones(void *data){
	
	//genero nombre de la accion
	char *accion = "armar_medallones";
	//creo el puntero para pasarle la referencia de memoria (data) del struct pasado por parametro (la cual es un puntero). 
	
	struct parametro *mydata = data;

	sem_wait(&mydata->semaforos_param.sem_armar_medallones);
	//llamo funcion para imprimir, paso struct y accion
	imprimirAccion(mydata,accion);
	//tiempo de simulacion
	usleep( 20000 );
	//doy la señal a la siguiente accion (cortar me habilita mezclar)
	//AGREGAR 
	sem_post (&mydata->semaforos_param.sem_cocinar_medallones);
	
	pthread_exit(NULL);
	}


void* cocinar_medallones(void *data){
	
	//SECCION CRITICA BLOQUEO SEM MUTEX
	//printf("bloqueo seccion critica hornear pan\n",equipo_param);
	
	
	pthread_mutex_lock(&sem_cocinar_medallones);
	

	//genero nombre de la accion
	char *accion = "cocinar_medallones";
	//creo el puntero para pasarle la referencia de memoria (data) del struct pasado por parametro (la cual es un puntero). 
	
	struct parametro *mydata = data;
	

	sem_wait(&mydata->semaforos_param.sem_cocinar_medallones);

	FILE * LOG = fopen("log.txt","a");
	fseek (LOG, 0, SEEK_END);
	fprintf(LOG,"\tEquipo %d empieza a usar la plancha\n " , mydata->equipo_param);

	printf("\tEquipo %d empieza a usar la plancha\n " , mydata->equipo_param);

	//llamo funcion para imprimir, paso struct y accion
	imprimirAccion(mydata,accion);
	//tiempo de simulacion
	usleep( 20000 );
	//doy la señal a la siguiente accion (cortar me habilita mezclar)
	//AGREGAR 
	sem_post (&mydata->semaforos_param.sem_armar_hamburguesas);
	
	//LIBERO SEMAFORO MUTEX PARA SALAR
	fprintf(LOG,"\tEquipo %d deja de usar la plancha\n " , mydata->equipo_param);
	fclose(LOG);
	printf("\tEquipo %d deja de usar la plancha\n " , mydata->equipo_param);
	pthread_mutex_unlock(&sem_cocinar_medallones);
	

	pthread_exit(NULL);
	}


void* armar_hamburguesas(void *data){
	
	//genero nombre de la accion
	char *accion = "armar_hamburguesas";
	//creo el puntero para pasarle la referencia de memoria (data) del struct pasado por parametro (la cual es un puntero). 
	
	struct parametro *mydata = data;

	sem_wait(&mydata->semaforos_param.sem_armar_hamburguesas);
	//llamo funcion para imprimir, paso struct y accion
	imprimirAccion(mydata,accion);
	//tiempo de simulacion
	usleep( 20000 );
	//doy la señal a la siguiente accion (cortar me habilita mezclar)
	//AGREGAR 
	
	int ganador = printf("\t%d" , mydata->equipo_param);

	sem_post (&mydata->semaforos_param.sem_validar);

	pthread_exit(NULL);
	}

void* validar(void *data){
	
	//SECCION CRITICA BLOQUEO SEM MUTEX
	//printf("bloqueo seccion critica salar\n",equipo_param);
	
	//pthread_mutex_lock(&sem_validar);
	

	//genero nombre de la accion
	char *accion = "validar";
	//creo el puntero para pasarle la referencia de memoria (data) del struct pasado por parametro (la cual es un puntero). 
	
	struct parametro *mydata = data;
	
	sem_wait(&mydata->semaforos_param.sem_validar);
	//llamo funcion para imprimir, paso struct y accion
	//imprimirAccion(mydata,accion);
	//tiempo de simulacion
	//usleep( 20000 );
	//doy la señal a la siguiente accion (cortar me habilita mezclar)
	//AGREGAR 
		
	//LIBERO SEMAFORO MUTEX PARA SALAR
	FILE * LOG = fopen("log.txt","a");
	fseek (LOG, 0, SEEK_END);
	fprintf(LOG,"\t---------------EQUIPO %d ES EL GANADOR!!!-------------\n " , mydata->equipo_param);
	fclose(LOG);
	printf("\t---------------EQUIPO %d ES EL GANADOR!!!-------------\n " , mydata->equipo_param);
	exit(-1);
	//pthread_exit(NULL);
	}




//FUNCION PRINCIPAL/INICIAL
void* ejecutarReceta(void *i) {
	
	//variables semaforos
	sem_t sem_mezclar; //DESCOMENTAR PARA LUEGO SEGUIR CON LAS ACCIONES
	
	//crear variables semaforos aqui
	sem_t sem_salar;
	sem_t sem_hornear;
	sem_t sem_armar_medallones;
	sem_t sem_cocinar_medallones;
	sem_t sem_armar_hamburguesas;
	sem_t sem_validar;

	//variables hilos
	pthread_t p1; //cortar 
	
	//crear variables hilos aqui
	pthread_t p2; //mezclar
	pthread_t p3; //salar
	pthread_t p4; //cortar lecha y tomate
	pthread_t p5; //hornear
	pthread_t p6; //armar medallones
	pthread_t p7; //cocinar_medalloens
	pthread_t p8; //armar hamburguesas
	
	pthread_t p9; //validar ganador

	//numero del equipo (casteo el puntero a un int)
	int p = *((int *) i);

	FILE * LOG = fopen("log.txt","a");
	fseek (LOG, 0, SEEK_END);

	fprintf(LOG,"Ejecutando equipo %d \n", p);
	fclose(LOG);
	printf("Ejecutando equipo %d \n", p);
	
	//reservo memoria para el struct
	struct parametro *pthread_data = malloc(sizeof(struct parametro));

	//seteo los valores al struct
	
	//seteo numero de grupo
	pthread_data->equipo_param = p;

	//seteo semaforos
	pthread_data->semaforos_param.sem_mezclar = sem_mezclar;
	

	//setear demas semaforos al struct aqui
	pthread_data->semaforos_param.sem_salar = sem_salar;
	pthread_data->semaforos_param.sem_hornear = sem_hornear;
	pthread_data->semaforos_param.sem_armar_medallones = sem_armar_medallones;
	pthread_data->semaforos_param.sem_cocinar_medallones = sem_cocinar_medallones;
	pthread_data->semaforos_param.sem_armar_hamburguesas = sem_armar_hamburguesas;
	pthread_data->semaforos_param.sem_validar = sem_validar;
	
	//seteo las acciones y los ingredientes (Faltan acciones e ingredientes) ¿Se ve hardcodeado no? ¿Les parece bien?
    strcpy(pthread_data->pasos_param[0].accion, "cortar");
	strcpy(pthread_data->pasos_param[0].ingredientes[0], "ajo");
    strcpy(pthread_data->pasos_param[0].ingredientes[1], "perejil");
 	strcpy(pthread_data->pasos_param[0].ingredientes[2], "cebolla");

	strcpy(pthread_data->pasos_param[1].accion, "mezclar");
	strcpy(pthread_data->pasos_param[1].ingredientes[0], "ajo");
    strcpy(pthread_data->pasos_param[1].ingredientes[1], "perejil");
 	strcpy(pthread_data->pasos_param[1].ingredientes[2], "cebolla");
	strcpy(pthread_data->pasos_param[1].ingredientes[3], "carne picada");
	
	strcpy(pthread_data->pasos_param[2].accion, "salar");
	strcpy(pthread_data->pasos_param[2].ingredientes[0], "carne picada");
    
	strcpy(pthread_data->pasos_param[3].accion, "cortar2");
	strcpy(pthread_data->pasos_param[3].ingredientes[0], "lechuga");
    strcpy(pthread_data->pasos_param[3].ingredientes[1], "tomate");
 	
	strcpy(pthread_data->pasos_param[4].accion, "hornear");
	strcpy(pthread_data->pasos_param[4].ingredientes[0], "pan1");
    strcpy(pthread_data->pasos_param[4].ingredientes[1], "pan2");
 	
	strcpy(pthread_data->pasos_param[5].accion, "armar_medallones");

	strcpy(pthread_data->pasos_param[6].accion, "cocinar_medallones");
	
	strcpy(pthread_data->pasos_param[4].accion, "armar_hamburguesas");
	strcpy(pthread_data->pasos_param[4].ingredientes[0], "hamburguesa_1");
    strcpy(pthread_data->pasos_param[4].ingredientes[1], "hamburguesa_2");
 	

	//inicializo los semaforos

	sem_init(&(pthread_data->semaforos_param.sem_mezclar),0,0);
	

	//inicializar demas semaforos aqui
	sem_init(&(pthread_data->semaforos_param.sem_salar),0,0);

	sem_init(&(pthread_data->semaforos_param.sem_hornear),0,0);

	sem_init(&(pthread_data->semaforos_param.sem_cocinar_medallones),0,0);

	sem_init(&(pthread_data->semaforos_param.sem_armar_hamburguesas),0,0);

	sem_init(&(pthread_data->semaforos_param.sem_validar),0,0);

	//creo los hilos a todos les paso el struct creado (el mismo a todos los hilos) ya que todos comparten los semaforos 
    int rc;
    rc = pthread_create(&p1,                           //identificador unico
                            NULL,                      //atributos del thread
                                cortar,                //funcion a ejecutar
                                pthread_data);         //parametros de la funcion a ejecutar, pasado por referencia
	//crear demas hilos aqui

    rc = pthread_create(&p2,                           //identificador unico
                            NULL,                      //atributos del thread
                                mezclar,                //funcion a ejecutar
                                pthread_data);         //parametros de la funcion a ejecutar, pasado por referencia	
	
    rc = pthread_create(&p3,                           //identificador unico
                            NULL,                      //atributos del thread
                                salar,                //funcion a ejecutar
                                pthread_data);         //parametros de la funcion a ejecutar, pasado por referencia	
		
    rc = pthread_create(&p4,                           //identificador unico
                            NULL,                      //atributos del thread
                                cortar2,                //funcion a ejecutar
                                pthread_data);         //parametros de la funcion a ejecutar, pasado por referencia	
		
    rc = pthread_create(&p5,                           //identificador unico
                            NULL,                      //atributos del thread
                                hornear,                //funcion a ejecutar
                                pthread_data);         //parametros de la funcion a ejecutar, pasado por referencia	
		
	rc = pthread_create(&p6,                           //identificador unico
                            NULL,                      //atributos del thread
                                armar_medallones,                //funcion a ejecutar
                                pthread_data);         //parametros de la funcion a ejecutar, pasado por referencia	
		
	rc = pthread_create(&p7,                           //identificador unico
                            NULL,                      //atributos del thread
                                cocinar_medallones,                //funcion a ejecutar
                                pthread_data);         //parametros de la funcion a ejecutar, pasado por referencia	
	
	rc = pthread_create(&p8,                           //identificador unico
                            NULL,                      //atributos del thread
                                armar_hamburguesas,                //funcion a ejecutar
                                pthread_data);         //parametros de la funcion a ejecutar, pasado por referencia	
	
	rc = pthread_create(&p9,                           //identificador unico
                            NULL,                      //atributos del thread
                                validar,                //funcion a ejecutar
                                pthread_data);         //parametros de la funcion a ejecutar, pasado por referencia	
	

	//join de todos los hilos
	pthread_join (p1,NULL); //HILO DE P1 COTAR
	
	//crear join de demas hilos
	
	pthread_join (p2,NULL); //HILO DE P2 MEZCLAR
	pthread_join (p3,NULL); //HILO DE P3 SALAR
	pthread_join (p4,NULL); //HILO DE P4 CORTAR2
	pthread_join (p5,NULL); //HILO DE P5 HORNEAR
	pthread_join (p6,NULL); //HILO DE P6 ARMAR MEDALLONES
	pthread_join (p7,NULL); //HILO DE P7 COCINAR MEDALLONES
	pthread_join (p8,NULL); //HILO DE P8 ARMAR HAMBURGUESA
	pthread_join (p9,NULL); //HILO DE P9 VALIDAR


	//valido que el hilo se alla creado bien 
    if (rc){
       printf("Error:unable to create thread, %d \n", rc);
       exit(-1);
     }


	//destruccion de los semaforos 
	sem_destroy(&sem_mezclar);
	
	//destruir demas semaforos 
	sem_destroy(&sem_salar);
	sem_destroy(&sem_hornear);
	sem_destroy(&sem_cocinar_medallones);
	sem_destroy(&sem_armar_hamburguesas);
	sem_destroy(&sem_validar);

	//salida del hilo
	 pthread_exit(NULL);
}



int main ()
{	
	FILE * LOG;
	
	LOG = fopen("log.txt","a+");

	fseek (LOG, 0, SEEK_END);
	fclose(LOG);

	//inicializo sem mutex salar
	pthread_mutex_init (&sem_salar,NULL);
	//inicializo sem mutex hornear
	pthread_mutex_init (&sem_hornear,NULL);

	pthread_mutex_init (&sem_cocinar_medallones,NULL);

	pthread_mutex_init (&sem_validar,NULL);

	//creo los nombres de los equipos 
	int rc;
	
	int ganador;

	int *equipoNombre1 =malloc(sizeof(*equipoNombre1));
	int *equipoNombre2 =malloc(sizeof(*equipoNombre2));
	int *equipoNombre3 =malloc(sizeof(*equipoNombre3));
	*equipoNombre1 = 1;
	*equipoNombre2 = 2;
	*equipoNombre3 = 3;

	//creo las variables los hilos de los equipos
	pthread_t equipo1; 
	pthread_t equipo2;
	pthread_t equipo3;
 
	//inicializo los hilos de los equipos
    rc = pthread_create(&equipo1,                           //identificador unico
                            NULL,                          //atributos del thread
                                ejecutarReceta,             //funcion a ejecutar
                                equipoNombre1); 
///*
    rc = pthread_create(&equipo2,                           //identificador unico
                            NULL,                          //atributos del thread
                                ejecutarReceta,             //funcion a ejecutar
                                equipoNombre2);

    rc = pthread_create(&equipo3,                           //identificador unico
                            NULL,                          //atributos del thread
                                ejecutarReceta,             //funcion a ejecutar
                                equipoNombre3);
//*/
   if (rc){
       printf("Error:unable to create thread, %d \n", rc);
       printf("Salida por error \n");
       exit(-1);
     } 

	//join de todos los hilos
	pthread_join (equipo1,NULL);

	pthread_join (equipo2,NULL);
	pthread_join (equipo3,NULL);


    pthread_exit(NULL);
}


//Para compilar:   gcc HellsBurgers.c -o ejecutable -lpthread
//Para ejecutar:   ./ejecutable

