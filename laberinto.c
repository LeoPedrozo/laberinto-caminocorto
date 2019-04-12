#include <stdio.h>
#include <string.h>

//Tamanho M x N
#define M 20
#define N 20

#define TRUE 1
#define FALSE 0
#define INT_MAX 99999 //numero grande para indicar que es el primer mayor

#define PARED 1 //lugar por donde no se puede mover
#define CAMINO 0 //lugar por donde se puede mover

#define VISITADO 1 //Ya fue visitado
#define LIMPIAR 0 //resetear el lugar a 0

#define SALIDA 'S'
#define ENTRADA 'E'
 //imprimir la matriz
 void imprimirMatriz(int m[M][N]) {
    for(int i = 0 ; i<M; i++){
        for(int j = 0; j<N; j++){
          if(m[i][j] == 'E' || m[i][j] == 'S'){
            printf("%c ", *(*(m+i)+j));
          }else{
            printf("%d ", *(*(m+i)+j));
          }
        }
        putchar('\n');
    }

}

//	copiara los valores que indiquen el camino a la matriz copia
//	colocando 3 en sus respectivos lugares validos
void reflejar(int m[M][N], int copia[M][N]){
    for(int i = 0 ; i < M; i++){
        for (int j = 0; j < N; j++){
          if(m[i][j] == 1){
            copia[i][j] = 3;
          }else{
              copia[i][j] = 0;
          }
        }
    }
}

//Grabara el camino a la matriz original
void grabar(int mat[M][N], int camino[M][N]){
    for(int i = 0 ; i < M; i++){
        for (int j = 0; j < N; j++){
          if(camino[i][j] == 3){
            mat[i][j] = 3;
          }
        }
    }
}
// Revisar si es posible ir a (x, y) desde la posicion actual. La
// funcion retorna FALSE si el espacio tiene valor de PARED o ya fue visitado
char esSeguro(int mat[M][N], int visitados[M][N], int x, int y){
	if (mat[x][y] == PARED || visitados[x][y] == VISITADO)
		return FALSE;

	return TRUE;
}

// Si no es una posicion valida, retorna FALSE
//Para ser valido debe estar dentro de la matriz
char esValido(int x, int y){
	if (x < M && y < N && x >= 0 && y >= 0)
		return TRUE;

	return FALSE;
}

// Encontrar la ruta mas corta posible en la Matriz mat desde la posicion inicial (0, 0)
// a la casilla de destino (x, y)

// distanciaMinima es pasado por referencia y guarda la longitud del camino mas largo (inicialmente)
// desde el origen al destino conocido hasta ahora, dist mantiene la distancia del camino
// desde el origen hasta la casilla actual (i, j)

void encontrarCaminoCorto(int mat[M][N], int visitados[M][N],int camino[M][N], int i, int j,int x, int y, int *distanciaMinima, int dist){

	// Si el destino es encontrado, actualizar la distancia Minima
	if (i == x && j == y)
	{
		if(dist < *distanciaMinima){
		    *distanciaMinima = dist;
		    reflejar(visitados, camino);
		}
		return;
	}

	// marcar la casilla (i, j) como visitado visitado
	visitados[i][j] = VISITADO;

	// ir a la casilla de abajo
	if (esValido(i + 1, j) && esSeguro(mat, visitados, i + 1, j))
		encontrarCaminoCorto(mat, visitados,camino, i + 1, j, x, y, distanciaMinima, dist + 1);

	// ir a la casilla de la derecha
	if (esValido(i, j + 1) && esSeguro(mat, visitados, i, j + 1))
		encontrarCaminoCorto(mat, visitados,camino, i, j + 1, x, y, distanciaMinima, dist + 1);

	// ir a la casilla de arriba
	if (esValido(i - 1, j) && esSeguro(mat, visitados, i - 1, j))
		encontrarCaminoCorto(mat, visitados,camino, i - 1, j, x, y, distanciaMinima, dist + 1);

	// ir a la casilla de la izquierda
	if (esValido(i, j - 1) && esSeguro(mat, visitados, i, j - 1))
		encontrarCaminoCorto(mat, visitados,camino, i, j - 1, x, y, distanciaMinima, dist + 1);

	// Backtrack - remover (i, j) de los visitados en la matriz

	visitados[i][j] = LIMPIAR;
}


// Encontrar el camino mas corto del laberinto
int main(void){
  //Para el ejercicio la matriz debe ser de tamanho 20x20 paredes son 1
  //los caminos son 0
	int mat[M][N] =
	{
		{ 1, 1, 1, 1, 1, 0, 0, 1, 1, 1 },
		{ 0, 1, 1, 1, 1, 1, 0, 1, 0, 1 },
		{ 0, 0, 1, 0, 1, 1, 1, 0, 0, 1 },
		{ 1, 0, 1, 1, 1, 0, 1, 1, 0, 1 },
		{ 0, 0, 0, 1, 0, 0, 0, 1, 0, 1 },
		{ 1, 0, 1, 1, 1, 0, 0, 1, 1, 0 },
		{ 0, 0, 0, 0, 1, 0, 0, 1, 0, 1 },
		{ 0, 1, 1, 1, 1, 1, 1, 1, 0, 0 },
		{ 1, 1, 1, 1, 1, 0, 0, 1, 1, 1 },
		{ 0, 0, 1, 0, 0, 1, 1, 0, 0, 1 },
	};

	// matriz para hacer seguimiento de los caminos que va tomando
	int visitados[M][N];
    //camino
  int camino[M][N];
	// Inicialmente todas las casillas estan sin visitar (cerar todo)
	memset(visitados, 0, sizeof visitados);
  memset(camino, 0, sizeof camino);

	int distanciaMinima = INT_MAX;
  int posInicial_X = 5;
  int posInicial_Y = 1;
  int posFinal_X = 7;
  int posFinal_Y = 0;
  //convertir en camino en caso que sea una pared
  mat[posInicial_X][posInicial_Y] = CAMINO;
  mat[posFinal_X][posFinal_Y] = CAMINO;

	encontrarCaminoCorto(mat, visitados,camino, posInicial_X, posInicial_Y, posFinal_X, posFinal_Y, &distanciaMinima, 0);

	if(distanciaMinima != INT_MAX){
    imprimirMatriz(mat);
	  printf( "\nEl camino mas corto del origen al destino tiene longitud %d\n", distanciaMinima);
    putchar('\n');
    grabar(mat, camino);
    mat[5][1] = ENTRADA ;//LUGAR DE ENTRADA
    mat[7][0] = SALIDA;//LUGAR DONDE DEBE TERMINAR
    imprimirMatriz(mat);
	}else{
		printf("No se pudo llegar desde el origen al destino\n");
  }
	return 0;
}
