// Fichero: registrador.h
#include "cronometro.h" // Se requiere para declarar un miembro Cronometro
#include <string>
using namespace std;
class RegistradorEventos {
	private:
		string nombreProceso;
		Cronometro reloj; // Relacion de composicion ('tiene un')
	public:
		RegistradorEventos(string np) :
			nombreProceso(np), 
			reloj(np) {}
		void ejecutarEvento() {
			reloj.iniciar();
			// Lógica del evento simulado
			reloj.detener();
			reloj.obtenerTiempo();
		}
};