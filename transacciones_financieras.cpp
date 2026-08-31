#include <iostream>
#include <string>
using namespace std;

class Cuenta {
private:
    string titular;
    string numeroCuenta;
    double saldo;

public:
    // Constructor parametrizado con lista de inicialización
    Cuenta(string titular_val, string num_val, double saldo_val): 
		titular(titular_val), 
		numeroCuenta(num_val), 
		saldo(saldo_val) {}

    // Constructor de copia explícito para evidenciar la reserva de memoria
    Cuenta(const Cuenta& otra): 
		titular(otra.titular), 
		numeroCuenta(otra.numeroCuenta), 
		saldo(otra.saldo) 
		{
        	cout << ">>> [ALERTA DE RENDIMIENTO] Constructor de copia invocado para la cuenta de " << titular << endl;
    	}

    // Métodos constantes de acceso (Solo lectura)
    string obtenerTitular() const { return titular; }
    string obtenerNumero() const { return numeroCuenta; }
    double obtenerSaldo() const { return saldo; }

    // Métodos modificadores
    void retirar(double monto) { saldo -= monto; }
    void depositar(double monto) { saldo += monto; }
};

// ============================================================================
// SECCIÓN DE ESTUDIO: TIPOS DE PASO DE PARÁMETROS
// ============================================================================

// 1. PASO POR VALOR (Demuestra el aislamiento de datos y costo de copia)
void calcularProyeccionInteres(Cuenta c, float tasa) {
    cout << "\n[Funcion Proyeccion] Iniciando calculo..." << endl;
    double interes = c.obtenerSaldo() * tasa;
    c.depositar(interes);
    cout << "[Funcion Proyeccion] Saldo proyectado en COPIA temporal: $" << c.obtenerSaldo() << endl;
    cout << "[Funcion Proyeccion] Finalizando funcion (la copia temporal se destruye)." << endl;
}

// 2. PASO POR REFERENCIA (Demuestra la persistencia de efectos secundarios)
void procesarTransferencia(Cuenta& origen, Cuenta& destino, double monto) {
    cout << "\n[Funcion Transferencia] Procesando transaccion de $" << monto << "..." << endl;
    if (origen.obtenerSaldo() >= monto) {
        origen.retirar(monto);
        destino.depositar(monto);
        cout << "[Funcion Transferencia] Exito. Fondos transferidos de manera real." << endl;
    } else {
        cout << "[Funcion Transferencia] Error: Fondos insuficientes." << endl;
    }
}

// 3. PASO POR REFERENCIA CONSTANTE (Demuestra eficiencia extrema + seguridad)
void imprimirAuditoria(const Cuenta& c) {
    cout << "\n[Funcion Auditoria] Impresion de seguridad de la cuenta:" << endl;
    cout << "  - Titular: " << c.obtenerTitular() << endl;
    cout << "  - Numero de Cuenta: " << c.obtenerNumero() << endl;
    cout << "  - Saldo Auditado: $" << c.obtenerSaldo() << endl;
    
    // TRAMPA PEDAGÓGICA (Pida a sus alumnos descomentar la línea de abajo):
    // c.depositar(100); // Provoca un Error de compilación porque el objeto es const
}

// ============================================================================
// PROGRAMA PRINCIPAL
// ============================================================================
int main() {
    cout << "=== Inicializando cuentas bancarias ===" << endl;
    Cuenta cuentaJuan("Juan Perez", "123-456", 1000.0);
    Cuenta cuentaMaria("Maria Gomez", "789-012", 500.0);

    // CASO 1: Demostración de Paso por Valor
    cout << "\n--- Ejecutando Caso 1 (Paso por Valor) ---" << endl;
    calcularProyeccionInteres(cuentaJuan, 0.05f);
    cout << "Saldo final de Juan en main(): $" << cuentaJuan.obtenerSaldo() << endl;

    // CASO 2: Demostración de Paso por Referencia
    cout << "\n--- Ejecutando Caso 2 (Paso por Referencia) ---" << endl;
    procesarTransferencia(cuentaJuan, cuentaMaria, 300.0);
    cout << "Saldo de Juan en main(): $" << cuentaJuan.obtenerSaldo() << endl;
    cout << "Saldo de Maria en main(): $" << cuentaMaria.obtenerSaldo() << endl;

    // CASO 3: Demostración de Paso por Referencia Constante
    cout << "\n--- Ejecutando Caso 3 (Paso por Referencia Constante) ---" << endl;
    imprimirAuditoria(cuentaJuan);

    return 0;
}