#include "Drone.h"
#include <iostream>
using namespace std;
// ============================================================================
// FUNCIONES EXTERNAS PARA EVALUAR PASO DE PARÁMETROS (1.3)
// ============================================================================
// 1. Paso por Referencia Constante (const Tipo&):
// Alta eficiencia (sin copias del dron) + Seguridad (prohibido modificar)
void auditarTelemetria(const DroneEntrega& drone) {
	cout << "\n--- [AUDITORIA EN TIEMPO REAL] ---" << endl;
	cout << " Dron ID: " << drone.obtenerID() << endl;
	cout << " Estado Actual: " << drone.obtenerEstado() << endl;
	cout << " Nivel Bateria: " << drone.obtenerNivelBateria() << "%" << endl;
	// TRAMPA PEDAGÓGICA (Si descomentas, el compilador bloquea por ser const):
	// drone.despegar(); // Error: no se pueden llamar métodos modificadores
}
// 2. Paso por Referencia (Tipo&):
// Modifica directamente el objeto original sin invocar constructor de copia
void ejecutarMisionEntrega(DroneEntrega& drone, float distanciaKm) {
	cout << "\n=== INICIANDO MISION DE ENTREGA DE PAQUETE ===" << endl;
	drone.despegar();
	drone.realizarVuelo(distanciaKm);
	drone.aterrizar();
}
// 3. Paso por Valor (Tipo): Demostración de aislamiento e ineficiencia
void simularMisionIlegal(DroneEntrega copiaDrone) {
	cout << "\n... Simulando mision en COPIA temporal ..." << endl;
	copiaDrone.despegar();
	copiaDrone.realizarVuelo(15.0f);
	cout << " Bateria en copia temporal: " << copiaDrone.obtenerNivelBateria() << "%" << endl;
}
int main() {
	cout << "==================================================" << endl;
	cout << " SISTEMA DE TELEMETRIA Y CONTROL DE DRONES" << endl;
	cout << "==================================================" << endl;
	// Instanciación con constructor parametrizado (1.1 y 1.2)
	DroneEntrega droneAlpha("DRONE-ALPHA-01", 5000, 100.0f);
	// Auditoría inicial (Paso por referencia constante)
	auditarTelemetria(droneAlpha);
	// Ejecución de misión real (Paso por referencia - Modifica original)
	ejecutarMisionEntrega(droneAlpha, 8.5f);
	// Auditoría post-misión (Comprueba cambios persistentes)
	auditarTelemetria(droneAlpha);
	// Demostración de paso por valor (No afecta al original)
	simularMisionIlegal(droneAlpha);
	cout << "\nVerificacion en main(): Bateria real tras simulacion = " << droneAlpha.obtenerNivelBateria() << "%" << endl;
	return 0;
}