#ifndef __DRONE_H__
#define __DRONE_H__
#include <string>
using namespace std;
// ============================================================================
// CLASE COMPONENTE: Bateria (1.1 y 1.4)
// ============================================================================
class Bateria {
	private:
		int capacidadmAh;
		float porcentajeCarga;
	public:
		// Constructores (1.2)
		Bateria();
		Bateria(int capacidad, float cargaInicial);
		// Métodos de acceso constantes
		float obtenerPorcentaje() const;
		int obtenerCapacidad() const;
		// Métodos modificadores
		void consumirEnergia(float porcentaje);
};
// ============================================================================
// CLASE CONTENEDORA: DroneEntrega (1.1, 1.2 y 1.4 Composición)
// ============================================================================
class DroneEntrega {
	private:
		string idDrone;
		string estadoVuelo; // "En Base", "En Misión", "Emergencia"
		Bateria bateria; // Subobjeto por composición (Tiene un)
	public:
		// Constructor compuesto con lista de inicialización (1.2 y 1.4)
		DroneEntrega(string id, int capBat, float cargaBat);
		// Métodos de consulta constantes
		string obtenerID() const;
		string obtenerEstado() const;
		float obtenerNivelBateria() const;
		// Métodos operativos
		void despegar();
		void realizarVuelo(float kilometros);
		void aterrizar();
};
#endif // __DRONE_H__