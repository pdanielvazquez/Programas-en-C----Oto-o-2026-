// Fichero: cronometro.cpp
#include "cronometro.h"
#include <iostream>
#include <ctime>

Cronometro::Cronometro(string nom): 
	nombre(nom), 
	tiempoInicio(0), 
	tiempoTotal(0), 
	corriendo(false) {}

double Cronometro::obtenerTiempoActual() const {
	return static_cast<double>(clock()) / CLOCKS_PER_SEC;
}

void Cronometro::iniciar() {
	if (!corriendo) {
		tiempoInicio = obtenerTiempoActual();
		corriendo = true;
		cout << "[" << nombre << "] Cronometro iniciado." << endl;
	}
}

void Cronometro::detener() {
	if (corriendo) {
		tiempoTotal += (obtenerTiempoActual() - tiempoInicio);
		corriendo = false;
		cout << "[" << nombre << "] Cronometro detenido." << endl;
	}
}

double Cronometro::obtenerTiempo() const {
	if (corriendo) {
		return tiempoTotal + (obtenerTiempoActual() - tiempoInicio);
	}
	return tiempoTotal;
}