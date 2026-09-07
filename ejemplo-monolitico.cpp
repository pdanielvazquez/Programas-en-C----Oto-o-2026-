#include <iostream>
#include <string>
#include <ctime>
using namespace std;
// Declaracion de la clase e Implementacion Monolitica
class Cronometro {
	private:
		string nombre;
		double tiempoInicio;
		double tiempoTotal;
		bool corriendo;
		double obtenerTiempoActual() const {
			return static_cast<double>(clock()) / CLOCKS_PER_SEC;
		}
	public:
		Cronometro(string nom): 
			nombre(nom), 
			tiempoInicio(0), 
			tiempoTotal(0), 
			corriendo(false) {}
		void iniciar() {
			if (!corriendo) {
				tiempoInicio = obtenerTiempoActual();
				corriendo = true;
				cout << "[" << nombre << "] Cronometro iniciado." << endl;
			}
		}
		void detener() {
			if (corriendo) {
				tiempoTotal += (obtenerTiempoActual() - tiempoInicio);
				corriendo = false;
				cout << "[" << nombre << "] Cronometro detenido." << endl;
			}
		}
		double obtenerTiempo() const {
			if (corriendo) {
				return tiempoTotal + (obtenerTiempoActual() - tiempoInicio);
			}
			return tiempoTotal;
		}
};

int main(){
	cout << "--- Simulando Tarea de Computo ---" << endl;
	Cronometro crono("Procesador de Datos");
	crono.iniciar();
	// Simulacion de una pausa de procesamiento mediante ciclo ineficiente
	double k = 0;
	for (long i = 0; i < 90000000; ++i) {
		k += 1.0;
	}
	crono.detener();
	cout << "Tiempo de CPU consumido: " << crono.obtenerTiempo()
	<< " segundos." << endl;
	return 0;
}