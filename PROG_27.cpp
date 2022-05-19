/*Autor: oscar vivaldi partido ramirez   fecha: 05/05/2022
UTILIZANDO ARCHIVOS BINARIOS
Hacer un programa que utilice la estructura de Alumno y almacene los datos de 100 alumnos
Debe tener el siguiente menú:
0. Salir
1. Agregar alumnos
2. Imprimir
3. Alumnos Aprobados
4. Alumnos Reprobados
5. Promedio del grupo
6. Porcentaje de alumnos Aprobados
7. guardar datos 
8. cargar datos 
9.ordenar por edad
NOTA: Para hacer operaciones con las calificaciones de los alumnos(Opciones 3,4,5 y 6 del menú) se siguen las siguientes reglas
Si el numero de faltas es <=6, la calificación es la que esta almacenada en el dato promedio de la estructura
 Pero si no, la calificación que se toma es 5
*/
#include<stdio.h>
#include<stdlib.h>
#include "milibreria.h"
#include <string.h>

//declaraciones globales 
#define MAX 100
struct alumno{
	char nombre[30];
	float promedio;
	int faltas;
};
int n=0;

//prototipos
int menu();
void agregar(struct alumno x[]);
void imprimir(struct alumno x[], int tipo);
void guardar(struct alumno x[]);
void cargar(struct alumno x[]);
void ordenarNombre(struct alumno x[]);


//principal
int main(){
	int op;
	struct alumno grupo[MAX];
	float cal[MAX];
	do{
		op=menu();
		switch(op){
			case 0:	printf("Adios...\n");
					break;
			case 1: agregar(grupo);
					break; 
			case 2: imprimir(grupo,0);
					break; 
			case 3: imprimir(grupo,1);
					break; 
			case 4: imprimir(grupo,2);
					break; 
			case 5: //promedio
			
					break; 
			case 6: //porcentaje
					break; 
			case 7: guardar(grupo);
					break;
			case 8: cargar(grupo);
					break;
			case 9: ordenarNombre(grupo);
					break;		
		
		}
	}while(op!=0);
	return 0;
}
//menu de inicio 
int menu(){
	int opcion;
	printf("------MENU-----	\n");
	printf("0. SALIR	\n");
	printf("1. AGREGAR ALUMNOS	\n");
	printf("2. IMPRIMIR	\n");
	printf("3. ALUMNOS APROBADOS	\n");
	printf("4. ALUMNOS REPROBADOS	\n");
	printf("5. PROMEDIO DEL GRUPO	\n");
	printf("6. PORCENTAJE DE ALUMNOS APROBADOS	\n");
	printf("7. GUARDAR DATOS	\n");
	printf("8. CARGAR DATOS	\n");
	printf("9.ORDENAR POR NOMBRE\n");

	opcion=leerd("selecciona una opcion: ",0,9);
	return opcion;
}

//GUARDAR LOS DATOS DEL ARREGLO DE ESTRUCTURAS 

void guardar(struct alumno x[]){
	FILE *f;
	f=fopen("alumnos.dat","w");
	if(f==NULL){
		printf("error al intentar guardar los datos!!!! \n");
	}
	else{
		for(int i=0; i<n; i++){
			fwrite(&x[i],sizeof(x[i]),1,f);
			fprintf(f,"%s\t%f\t%d\n",x[i].nombre,x[i].promedio,x[i].faltas);
		}
		fclose(f);
		printf("---->se guardaron %d registros \n",n);
		system("PAUSE");
	}
	
}
//leer el archivo binario y cargar al arreglo de estructuras
void cargar(struct alumno x[]){
	FILE*f;
	f=fopen("alumnos.dat","r");
	n=0;
	if(f==NULL){
		printf("Error al intentar cargar los datos!!!! \n");
	}
	else{
		printf("LEYENDO.....\n");
		while(fread(&x[n], sizeof(x[n]),1,f)==1){
			
			n++;
			printf("%3d\t%-30s\t%4.1f\t%2d\n",n,x[n-1].nombre,x[n-1].promedio,x[n-1].faltas);
		}
		fclose(f);
		printf("---%d registros leidos\n",n);
		system("PAUSE");
	}
}

//se agregan alumnos 
void agregar(struct alumno x[]){
	int pregunta;

	// ciclo para agregar nombre, promedio y faltas, hasta max
	while(n<MAX){
		leers("nombre: ",x[n].nombre,30);
		x[n].promedio=leerf("promedio: ",0,10);
		x[n].faltas=leerd("Faltas: ",0,32);	
		n++;	
		pregunta=leerd("agregar a otro alumno? (1-si, 0-no):",0,1);
		//si NO se desea agregar otro alumno, se rompe el while
		if(pregunta==0){
			break;
		}
	}
	//si el contador es igual que MAX nos manda mensaje de arreglo lleno
	if(n==MAX){
		printf("Arreglo lleno!!\n");
		system("PAUSE");
		}
}
//la funcion imprimir en el parametro tipo se le indica que va a imprimir
//0 a todos, 1 aaprobados, 2 reprobados
void imprimir(struct alumno x[], int tipo){
	char mensaje[20];
	switch(tipo){
		case 0:	strcpy(mensaje,"TOTALES");
				break;
		case 1:	strcpy(mensaje,"APROBADOS");
				break;
		case 2:	strcpy(mensaje,"REPROBADOS");
				break;
				
	}
	printf("---------------------------ALUMNOS %s-------------------------------\n",mensaje);
	printf("No.\tNOMBRE\t\t	FALTAS\t\t\tPROMEDIO\n");
	printf("--------------------------------------------------------------------------\n");
	for(int i=0; i<n; i++){
		switch(tipo){
			case 0:	printf("%2d\t%-30s\t%2d\t%4.1f\n", i+1,x[i].nombre,x[i].faltas,x[i].promedio);	
					break;
			case 1: if(x[i].promedio>=7){
				printf("%2d\t%-30s\t%2d\t%4.1f\n", i+1,x[i].nombre,x[i].faltas,x[i].promedio);
				}
					break;
			case 2: if(x[i].promedio<7){
				printf("%2d\t%-30s\t%2d\t%4.1f\n", i+1,x[i].nombre,x[i].faltas,x[i].promedio);
				}
					break;
			
		}
		
	}
	printf("-----------------------------------------------------------------\n");
	system("PAUSE");

}
void ordenarNombre(struct alumno x[]){
	//ordenamiento del arreglo por el metodo de la burbuja 
	for(int z = 1; z<n; ++z){
		struct alumno aux;
		for(int v=0; v<(n-z); v++){
			//edades[v]>edades [v+1]
			if(strcmp(x[v].nombre,x[v+1].nombre)>0){
				aux=x[v];
				x[v]=x[v+1];
				x[v+1]=aux;
			}
		}
	}
imprimir(x,0);
}

