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
void verificar0(rgb ** imagen, rgb ** buscar, int posX, int posY){
	int cero = 0;
	//0 grados
	for (int i = 0; i < buscar[1][1].fila; ++i){
		for (int j = 0; j < buscar[1][1].columna; ++j){
			if(imagen[posY+i][posX+j].R == buscar[i][j].R && imagen[posY+i][posX+j].G == buscar[i][j].G && imagen[posY+i][posX+j].B == buscar[i][j].B ){
				cero = cero+1;		
			}
		}
	}	
	if (cero == buscar[1][1].fila * buscar[1][1].columna){
		r0 += 1;
	}
}

void verificar90(rgb ** imagen, rgb ** buscar, int posX, int posY){
	//90 grados
	int noventa = 0;
	for (int i = 0; i < buscar[1][1].columna; ++i){
		for (int j = 0; j < buscar[1][1].fila; ++j){
			if(imagen[posY+i][posX+j].R == buscar[buscar[1][1].fila-1-j][i].R && buscar[buscar[1][1].fila-1-j][i].G == imagen[posY+i][posX+j].G && buscar[buscar[1][1].fila-1-j][i].B == imagen[posY+i][posX+j].B){
				noventa = noventa+1;
			}
		}
	}
	if (noventa == buscar[1][1].fila*buscar[1][1].columna){
		r90 = r90+1;
	}
}

void verificar180(rgb ** imagen, rgb ** buscar, int posX, int posY){
	//180 grados
	int cientoOchenta = 0;
	for (int i = 0; i < buscar[1][1].fila; ++i){
		for (int j = 0; j < buscar[1][1].columna; ++j){
			if(buscar[buscar[1][1].fila-1-i][buscar[1][1].columna-1-j].R == imagen[posY+i][posX+j].R && buscar[buscar[1][1].fila-i-1][buscar[1][1].columna-j-1].G == imagen[posY+i][posX+j].G && buscar[buscar[1][1].fila-1-i][buscar[1][1].columna-j-1].B == imagen[posY+i][posX+j].B){
				cientoOchenta = cientoOchenta +1;
			}
		}
	}
	if (cientoOchenta == buscar[1][1].fila*buscar[1][1].columna){
		r180 = r180+1;
	}
}

void verificar270(rgb ** imagen, rgb ** buscar, int posX, int posY){
	//270 grados
	int doscientoSetenta = 0;
	for (int i = 0; i < buscar[1][1].columna; ++i){
		for (int j = 0; j < buscar[1][1].fila; ++j){
			if(buscar[j][buscar[1][1].columna-1-i].R == imagen[posY+i][posX+j].R && buscar[j][buscar[1][1].columna-1-i].G == imagen[posY+i][posX+j].G && buscar[j][buscar[1][1].columna-1-i].B == imagen[posY+i][posX+j].B){
				doscientoSetenta = doscientoSetenta+1;
			}
		}
	}
	if (doscientoSetenta == buscar[1][1].fila*buscar[1][1].columna){
		r270 = r270+1;
	}	
}

//Itera a lo largo de toda la imagen.
void vecesContenida(rgb ** imagen, rgb ** buscar){
	//Iteramos por la matriz mas grande
	for (int i = 0; i < imagen[1][1].fila; ++i){
		for (int j = 0; j < imagen[1][1].columna; ++j){
			//Verificar por posicion.
			if(buscar[1][1].columna + j <= imagen[1][1].columna && buscar[1][1].fila + i <= imagen[1][1].fila){
				verificar0(imagen,buscar,j,i);
				verificar180(imagen,buscar,j,i);
			}
			if(buscar[1][1].columna + i <= imagen[1][1].fila && buscar[1][1].fila + j <= imagen[1][1].columna){
				verificar90(imagen,buscar,j,i);
				verificar270(imagen,buscar,j,i);
			}
			
		}
	}
	printf("\n Cantidad para rotacion 0: %d", r0);
	printf("\n Cantidad para rotacion 90: %d", r90);
	printf("\n Cantidad para rotacion 180: %d", r180);
	printf("\n Cantidad para rotacion 270: %d", r270);
}

//funcion que itera buscando la cantidad presente en la matriz

//Main 
int main ( int argc, const char* argv[]){
	do{
		//Menu para ordenar
		printf("\n Menu Experiencia 1 \n");
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
	}while(5 ==5);
	return 0;
}