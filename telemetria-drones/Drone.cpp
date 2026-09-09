#include "Drone.h"
#include <string>
#include <iostream>
using namespace std;
// ============================================================================
// IMPLEMENTACIÓN DE LA CLASE Bateria (1.5)
// ============================================================================
Bateria::Bateria() : capacidadmAh(3000), porcentajeCarga(100.0f) {}
Bateria::Bateria(int capacidad, float cargaInicial): capacidadmAh(capacidad), porcentajeCarga(cargaInicial) {}
float Bateria::obtenerPorcentaje() const { return porcentajeCarga; }
int Bateria::obtenerCapacidad() const { return capacidadmAh; }
void Bateria::consumirEnergia(float porcentaje) {
	porcentajeCarga -= porcentaje;
	if (porcentajeCarga < 0.0f) porcentajeCarga = 0.0f;
}
// ============================================================================
// IMPLEMENTACIÓN DE LA CLASE DroneEntrega (1.2, 1.4 y 1.5)
// ============================================================================
// Delegación directa al constructor del subobjeto mediante lista de inicialización
DroneEntrega::DroneEntrega(std::string id, int capBat, float cargaBat) : 
	idDrone(id), 
	estadoVuelo("En Base"), 
	bateria(capBat, cargaBat) {}
string DroneEntrega::obtenerID() const { return idDrone; }
string DroneEntrega::obtenerEstado() const { return estadoVuelo; }
float DroneEntrega::obtenerNivelBateria() const { return bateria.obtenerPorcentaje(); }
void DroneEntrega::despegar() {
	if (bateria.obtenerPorcentaje() >= 20.0f) {
		estadoVuelo = "En Misión";
		bateria.consumirEnergia(5.0f); // Despegue consume 5%
		cout << " -> [" << idDrone << "] Despegue exitoso. Estado: En Mision." << endl;
	} else {
		estadoVuelo = "Emergencia";
		cout << " -> [" << idDrone << "] Bateria insuficiente para despegar!" << endl;
	}
}
void DroneEntrega::realizarVuelo(float kilometros) {
	if (estadoVuelo == "En Misión") {
		float consumo = kilometros * 4.0f; // 4% de batería por km
		bateria.consumirEnergia(consumo);
		cout << " -> [" << idDrone << "] Recorridos " << kilometros << " km. Bateria restante: " << bateria.obtenerPorcentaje() << "%" << endl;
		if (bateria.obtenerPorcentaje() <= 10.0f) {
			estadoVuelo = "Emergencia";
			cout << " -> [" << idDrone << "] ALERTA: Nivel critico de energia!" << endl;
		}
	}
}
void DroneEntrega::aterrizar() {
	if (estadoVuelo != "En Base") {
		estadoVuelo = "En Base";
		cout << " -> [" << idDrone << "] Aterrizaje completado de forma segura." << endl;
	}
}