// Fichero: cronometro.h (VERSION REFACTORIZADA Y SEGURA)
#ifndef __CRONOMETRO_H__
#define __CRONOMETRO_H__
#include <string>
using namespace std;
class Cronometro {
	private:
		string nombre;
		double tiempoInicio;
		double tiempoTotal;
		bool corriendo;
		double obtenerTiempoActual() const;
	public:
		Cronometro(string nom);
		void iniciar();
		void detener();
		double obtenerTiempo() const;
};
#endif // __CRONOMETRO_H__