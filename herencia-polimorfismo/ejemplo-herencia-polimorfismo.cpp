#include <iostream>
#include <string>
#include <vector>
// ============================================================================
// CLASE BASE: Vehiculo
// ============================================================================
class Vehiculo {
	protected:
		std::string marca;
		std::string modelo;
		double velocidadActual;
	public:
		Vehiculo(std::string m, std::string mod): 
			marca(m), 
			modelo(mod), 
			velocidadActual(0.0) {}
	// Destructor virtual imprescindible para evitar fugas de memoria
	virtual ~Vehiculo() {
		std::cout << " [Destructor Vehiculo] Liberando base para: " << marca << " " << modelo << std::endl;
	}
	// Método virtual para enlace dinámico
	virtual void mostrarInformacion() const {
		std::cout << "Marca: " << marca << " | Modelo: " << modelo << " | Velocidad: " << velocidadActual << " km/h";
	}
	virtual void acelerar(double incremento) {
		velocidadActual += incremento;
		std::cout << " -> [" << marca << "] Acelerando a " << velocidadActual << " km/h." << std::endl;
	}
};

// ============================================================================
// CLASE DERIVADA 1: Auto (Hereda de Vehiculo)
// ============================================================================
class Auto : public Vehiculo {
	private:
		int numeroPuertas;
		bool aireAcondicionadoActivo;
	public:
		Auto(std::string m, std::string mod, int puertas): 
			Vehiculo(m, mod), 
			numeroPuertas(puertas), 
			aireAcondicionadoActivo(false) {}
		~Auto() override {
			std::cout << " [Destructor Auto] Destruyendo partes del Auto " << marca << std::endl;
		}
		void encenderAire() {
			aireAcondicionadoActivo = true;
			std::cout << " -> [" << marca << " " << modelo << "] Aire acondicionado ENCENDIDO." << std::endl;
		}
		// Sobrescritura polimórfica (override)
		void mostrarInformacion() const override {
			Vehiculo::mostrarInformacion(); // Reutiliza código de la clase base
			std::cout << " | Puertas: " << numeroPuertas << " | A/C: " << (aireAcondicionadoActivo ? "SI" : "NO") << std::endl;
		}
		void acelerar(double incremento) override {
			velocidadActual += (incremento * 1.1); // Los autos aceleran con respuesta asistida
			std::cout << " -> [Auto " << marca << "] Aceleración asistida: " << velocidadActual << " km/h." << std::endl;
		}
};

// ============================================================================
// CLASE DERIVADA 2: Motocicleta (Hereda de Vehiculo)
// ============================================================================
class Motocicleta : public Vehiculo {
	private:
		int cilindradaCC;
		bool cascoPuesto;
	public:
		Motocicleta(std::string m, std::string mod, int cilindrada): 
			Vehiculo(m, mod), 
			cilindradaCC(cilindrada), 
			cascoPuesto(false) {}
		~Motocicleta() override {
			std::cout << " [Destructor Motocicleta] Destruyendo Motocicleta " << marca << std::endl;
		}
		void colocarCasco() {
			cascoPuesto = true;
			std::cout << " -> [" << marca << " " << modelo << "] Casco abrochado de forma segura." << std::endl;
		}
		void mostrarInformacion() const override {
			Vehiculo::mostrarInformacion();
			std::cout << " | Cilindrada: " << cilindradaCC << " cc" << " | Casco: " << (cascoPuesto ? "PUESTO" : "NO PUESTO") << std::endl;
		}
		void acelerar(double incremento) override {
			if (!cascoPuesto) {
				std::cout << " -> [ALERTA " << marca << "] ¡Peligro! Debe ponerse el casco antes de acelerar." << std::endl;
				return;
			}
			velocidadActual += (incremento * 1.35); // Respuesta deportiva
			std::cout << " -> [Moto " << marca << "] Aceleración rápida: " << velocidadActual << " km/h." << std::endl;
		}
};

// ============================================================================
// PROGRAMA PRINCIPAL CON DEMOSTRACIÓN POLIMÓRFICA
// ============================================================================
int main() {
	std::cout << "=== DEMOSTRACIÓN DE HERENCIA Y POLIMORFISMO (TEMA 2.1) ===" << std::endl;
	// Uso de un vector de punteros a la clase base (Vehiculo*)
	std::vector<Vehiculo*> flota;
	flota.push_back(new Auto("Toyota", "Corolla", 4));
	flota.push_back(new Motocicleta("Yamaha", "MT-07", 689));
	flota.push_back(new Auto("Ford", "Mustang", 2));
	std::cout << "\n1. --- ESTADO INICIAL DE LA FLOTA ---" << std::endl;
	for (const Vehiculo* v : flota) {
		v->mostrarInformacion(); // Invocación polimórfica (enlace dinámico)
	}
	std::cout << "\n2. --- OPERACIONES ESPECÍFICAS DE CADA TIPO ---" << std::endl;
	static_cast<Auto*>(flota[0])->encenderAire();
	static_cast<Motocicleta*>(flota[1])->colocarCasco();
	std::cout << "\n3. --- ACELERACIÓN POLIMÓRFICA EN BUCLE ---" << std::endl;
	for (Vehiculo* v : flota) {
		v->acelerar(50.0); // Cada tipo responde según su propia implementación
	}
	std::cout << "\n4. --- LIBERACIÓN POLIMÓRFICA DE MEMORIA ---" << std::endl;
	for (Vehiculo* v : flota) {
		delete v; // Invoca los destructores en cascada gracias a 'virtual ~Vehiculo()'
	}
	flota.clear();
	return 0;
}