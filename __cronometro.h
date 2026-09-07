// Fichero: cronometro.h
// ATENCION: Omitir intencionalmente las guardias de preprocesador en este paso
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