// Fichero: aplicacion.cpp
#include "cronometro.h"
#include "registrador.h" // Este archivo vuelve a incluir de forma indirecta "cronometro.h"
#include <iostream>
using namespace std;
int main() {
	cout << "--- Sistema de Registro de Procesos ---" << endl;
	RegistradorEventos sistema("Analisis Numerico");
	sistema.ejecutarEvento();
	return 0;
};