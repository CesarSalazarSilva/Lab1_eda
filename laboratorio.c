#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Laboratorio 1 EDA, César Antonio Salazar Silva.

typedef struct rgb rgb;
struct rgb{
	int fila;
	int columna;
	int R;
	int G;
	int B;
};
int cont = 0;
//Valores Globales
int r0 = 0;
int r90 = 0;
int r180 = 0;
int r270 = 0;

//Funcion que lee a partir de un txt y almacena en una matriz
rgb ** Matriz(){
	//Se abre el archivo
	char nombre[50];
	scanf("%s", nombre);
	FILE * archivo;
	archivo=fopen(nombre,"r");
	int fila = 0;
	int columna = 0;
	//Control de error para archivo nulo
	if (archivo == NULL){
		printf("\n No hay ningun archivo con el nombre indicado. \n");		
	}

	//Se extrae la cantidad de filas y columnas
	fscanf(archivo, "%d %d", &columna, &fila );

	//Asignamos espacio de memoria para la matriz
	rgb ** matriz= (rgb**)malloc(sizeof(rgb*)*fila);
	for (int i=0;i<fila;i++){
		matriz[i]=(rgb*)malloc(sizeof(rgb)*columna);
	}
	rgb nuevoRGB;
	for(int i=0;i<fila;i++){
		for (int j = 0; j < columna; ++j){
			fscanf(archivo, "%d,%d,%d", &nuevoRGB.R ,&nuevoRGB.G,&nuevoRGB.B);
			nuevoRGB.fila = fila;
			nuevoRGB.columna = columna;
			matriz[i][j] = nuevoRGB; 
		}
	}

	//Cerramos el archivo y entregamos la matriz
	fclose(archivo);
	return matriz;
}

//Verificar contenida.
void verificar(rgb ** imagen, rgb ** buscar, int posX, int posY){
	
	cont = cont+1;
	//printf("%d    %d,%d,%d,%d\n",cont ,r0,r90,r180,r270);

	int cero = 0;
	int noventa = 0;
	int cientoOchenta = 0;
	int doscientoSetenta = 0;

	if(buscar[1][1].columna-1 + posX <= imagen[1][1].columna-1 && buscar[1][1].fila -1 + posY <= imagen[1][1].fila-1){
		//0 grados
		for (int i = 0; i < buscar[1][1].fila; ++i){
			for (int j = 0; j < buscar[1][1].columna; ++j){
				printf("%d , %d +++\n", posX+i,posY+j);
				if(imagen[posX+i][posY+j].R == buscar[i][j].R && imagen[posX+i][posY+j].G == buscar[i][j].G && imagen[posX+i][posY+j].B == buscar[i][j].B ){
					cero = cero+1;		
				}
			}
		}
		
		if (cero == buscar[1][1].fila * buscar[1][1].columna){
			r0 = r0 + 1;
		}
	
		//180 grados
		for (int i = 0; i < buscar[1][1].fila; ++i){
			for (int j = 0; j < buscar[1][1].columna; ++j){
				if(buscar[buscar[1][1].fila-1-i][buscar[1][1].columna-1-j].R == imagen[posX+i][posY+j].R && buscar[buscar[1][1].fila-i-1][buscar[1][1].columna-j-1].G == imagen[posX+i][posY+j].G && buscar[buscar[1][1].fila-1-i][buscar[1][1].columna-j-1].B == imagen[posX+i][posY+j].B){
					cientoOchenta = cientoOchenta +1;
				}
			}
		}
		if (cientoOchenta == buscar[1][1].fila*buscar[1][1].columna){
			r180 = r180+1;
		}
	}
	
	if(buscar[1][1].fila + posX <= imagen[1][1].columna && buscar[1][1].columna + posY <= imagen[1][1].fila){
		//90 grados
		for (int j = 0; j < buscar[1][1].columna; ++j){
			for (int i = 0; i < buscar[1][1].fila; ++i){
				if(buscar[buscar[1][1].fila-1-i][j].R == imagen[posX+i][posY+j].R && buscar[buscar[1][1].fila-1-i][j].G == imagen[posX+i][posY+j].G && buscar[buscar[1][1].fila-1-i][j].B == imagen[posX+i][posY+j].B){
					noventa = noventa+1;
				}
			}
		}
		if (noventa == buscar[1][1].fila*buscar[1][1].columna){
			r90 = r90+1;
		}

		//270 grados
		for (int i = 0; i < buscar[1][1].fila; ++i){
			for (int j = 0; j < buscar[1][1].columna; ++j){
				if(buscar[i][buscar[1][1].columna-1-j].R == imagen[posX+i][posY+j].R && buscar[i][buscar[1][1].columna-1-j].G == imagen[posX+i][posY+j].G && buscar[i][buscar[1][1].columna-j-1].B == imagen[posX+i][posY+j].B){
					doscientoSetenta = doscientoSetenta+1;
				}
			}
		}
		if (doscientoSetenta == buscar[1][1].fila*buscar[1][1].columna){
			r270 = r270+1;
		}
	}
}

//Itera a lo largo de toda la imagen.
void vecesContenida(rgb ** imagen, rgb ** buscar){
	//Iteramos por la matriz mas grande
	for (int i = 0; i < imagen[1][1].fila; ++i){
		for (int j = 0; j < imagen[1][1].columna; ++j){
			//Verificar por posicion.
			verificar(imagen,buscar,j,i);
		}
	}
}

//funcion que itera buscando la cantidad presente en la matriz

//Main 
int main ( int argc, const char* argv[]){
	int opcion = 0;
	do{
		//Menu para ordenar
		printf("\n Menu Experiencia 1, ");
		printf("\n 1) Cargar archivos.\n  - Ingrese una opcion valida : ");
		//Variable escoger menu
		scanf("%d", &opcion);

		switch(opcion){
			case 1:
				r0 = 0;
				r90 = 0;
				r180 = 0;
				r270 = 0;
				//Solicitamos la matriz de la imagen 
				printf("\n Introduzca el nombre del archivo que contiene la imagen (con extencion): ");
				rgb ** matriz = Matriz();
				printf("\n Introduzca el nombre del archivo a buscar (con extencion): ");
				rgb ** matrizbuscar = Matriz();
				vecesContenida(matriz,matrizbuscar);
				printf("\n RESULTADO , %d , %d , %d , %d \n",r0,r90,r180,r270);
				break;
			default:
            	printf("Porfavor ingresa una opcion valida \n");
            	break;

		}

	}while(opcion>=1 && opcion<=5);
	return 0;
}