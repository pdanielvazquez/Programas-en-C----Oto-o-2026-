#include <iostream>
#include <string>
#include <vector>
// ============================================================================
// CLASE BASE ABSTRACTA: EmpleadoBase (Tema 2.2)
// ============================================================================
class EmpleadoBase {
	private:
		std::string numSeguroSocial; // Estrictamente privado (Máxima seguridad)
	protected:
		std::string nombre;
		std::string idEmpleado;
		double salarioBase;
		// Protected Helper Method: Algoritmo interno protegido contra el exterior
		double calcularDeduccionesLey(double ingresoBruto) const {
			double isr = ingresoBruto * 0.16; // 16% Impuesto sobre la renta
			double imss = ingresoBruto * 0.04; // 4% Seguridad social
			return isr + imss;
		}
	public:
		EmpleadoBase(std::string id, std::string nom, double sal, std::string nss)
		: idEmpleado(id), nombre(nom), salarioBase(sal), numSeguroSocial(nss) {}
		virtual ~EmpleadoBase() {}
		virtual void calcularNomina() const = 0; // Método virtual puro
};

// ============================================================================
// CLASES DERIVADAS: EmpleadoComision y Gerente
// ============================================================================
class EmpleadoComision : public EmpleadoBase {
	private:
		double ventasRealizadas;
		double porcentajeComision;
	public:
		EmpleadoComision(std::string id, std::string nom, double sal, std::string nss, double ventas, double
		pct)
		: EmpleadoBase(id, nom, sal, nss), ventasRealizadas(ventas), porcentajeComision(pct) {}
		void calcularNomina() const override {
			double comision = ventasRealizadas * (porcentajeComision / 100.0);
			double ingresoBruto = salarioBase + comision; // Acceso a atributo protected
			double deducciones = calcularDeduccionesLey(ingresoBruto); // Acceso a protected helper
			double ingresoNeto = ingresoBruto - deducciones;
			std::cout << "[COMISIÓN] ID: " << idEmpleado << " | " << nombre
			<< " | Bruto: $" << ingresoBruto << " | Deducciones: $" << deducciones
			<< " | Neto: $" << ingresoNeto << std::endl;
		}
};

class Gerente : public EmpleadoBase {
	private:
		double bonoDesempeno;
	public:
		Gerente(std::string id, std::string nom, double sal, std::string nss, double bono)
		: EmpleadoBase(id, nom, sal, nss), bonoDesempeno(bono) {}
		void calcularNomina() const override {
			double ingresoBruto = salarioBase + bonoDesempeno;
			double deducciones = calcularDeduccionesLey(ingresoBruto);
			double ingresoNeto = ingresoBruto - deducciones;
			std::cout << "[GERENTE] ID: " << idEmpleado << " | " << nombre
			<< " | Bruto: $" << ingresoBruto << " | Deducciones: $" << deducciones
			<< " | Neto: $" << ingresoNeto << std::endl;
		}
};

// ============================================================================
// PROGRAMA PRINCIPAL (Demostración y Trampa Pedagógica)
// ============================================================================
int main() {
	std::cout << "==========================================================" << std::endl;
	std::cout << " SISTEMA DE NÓMINA Y SEGURIDAD DE EMPLEADOS (TEMA 2.2) " << std::endl;
	std::cout << "==========================================================" << std::endl;
	std::vector<EmpleadoBase*> nomina;
	nomina.push_back(new EmpleadoComision("E-101", "Ana Gomez", 12000, "NSS-111", 80000, 5.0));
	nomina.push_back(new Gerente("G-501", "Carlos Ruiz", 35000, "NSS-999", 10000));
	std::cout << "\n--- PROCESAMIENTO AUTOMÁTICO DE NÓMINA ---" << std::endl;
	for (const EmpleadoBase* emp : nomina) {
	emp->calcularNomina(); // Invocación a través de la interfaz pública
	}
	// TRAMPA PEDAGÓGICA (Al descomentar, el compilador bloquea por acceso no autorizado):
	// double ded = nomina[0]->calcularDeduccionesLey(15000); // Error: protected method
	// nomina[0]->salarioBase = 50000; // Error: protected attribute
	for (EmpleadoBase* emp : nomina) delete emp;
	return 0;
}