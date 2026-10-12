#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;
// 1. Reserva Jerárquica en Dos Pasos
int** crearMatriz(int filas, int cols) {
	// Paso A: Reservar arreglo dinámico de punteros (filas)
	int** mat = new int*[filas];
	// Paso B: Reservar cada arreglo de enteros (columnas) por fila
	for (int i = 0; i < filas; ++i) {
		mat[i] = new int[cols];
 	}
 	return mat;
}
// 2. Liberación Jerárquica Estructurada (Prevención de Memory Leaks)
void destruirMatriz(int** mat, int filas) {
 	if (mat == nullptr) return;
 	// Paso A: Liberar cada arreglo de columna individual
 	for (int i = 0; i < filas; ++i) {
 		delete[] mat[i];
 	}
 	// Paso B: Liberar el arreglo maestro de punteros
 	delete[] mat;
}
// 3. Inicialización de Píxeles de Prueba
void llenarImagenSimulada(int** mat, int filas, int cols) {
 	for (int i = 0; i < filas; ++i) {
 		for (int j = 0; j < cols; ++j) {
 			mat[i][j] = (i * 30 + j * 25) % 256; // Gradiente simulado
 		}
 	}
}
// 4. Algoritmo de Ajuste de Brillo (con truncamiento 0-255)
void ajustarBrillo(int** mat, int filas, int cols, int delta) {
 	for (int i = 0; i < filas; ++i) {
 		for (int j = 0; j < cols; ++j) {
 			int nuevoVal = mat[i][j] + delta;
 			mat[i][j] = max(0, min(255, nuevoVal));
 		}
 	}
}
// 5. Algoritmo de Umbralización Binarizada
void aplicarUmbral(int** mat, int filas, int cols, int umbral) {
	for (int i = 0; i < filas; ++i) {
 		for (int j = 0; j < cols; ++j) {
 			mat[i][j] = (mat[i][j] >= umbral) ? 255 : 0;
 		}
 	}
}
// 6. Visualización de Matriz en Consola
void imprimirMatriz(int** mat, int filas, int cols) {
 	for (int i = 0; i < filas; ++i) {
 		for (int j = 0; j < cols; ++j) {
 			cout << setw(4) << mat[i][j];
 		}
 		cout << "\n";
 	}
 	cout << endl;
}

int main() {
	int filas = 4, cols = 5;
	cout << "=== MÓDULO DE PROCESAMIENTO DIGITAL DE IMÁGENES 2D ===\n\n";
	// Asignación Dinámica en el Heap
	int** imagen = crearMatriz(filas, cols);
	llenarImagenSimulada(imagen, filas, cols);
	std::cout << "1. Imagen Original en Escala de Grises (0-255):\n";
	imprimirMatriz(imagen, filas, cols);
	std::cout << "2. Aplicando Ajuste de Brillo (+40):\n";
	ajustarBrillo(imagen, filas, cols, 40);
	imprimirMatriz(imagen, filas, cols);
	std::cout << "3. Aplicando Filtro de Umbral Binarizado (Umbral = 128):\n";
	aplicarUmbral(imagen, filas, cols, 128);
	imprimirMatriz(imagen, filas, cols);
	// Liberación Segura de Memoria
	destruirMatriz(imagen, filas);
	imagen = nullptr; // Eliminación de puntero colgado
	std::cout << "Memoria liberada exitosamente sin fugas (Memory Leaks).\n";
	return 0;
}