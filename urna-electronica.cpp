#include <iostream>
#include <string>
using namespace std;

class UrnaElectronica {
private:
    string municipio;
    int votosCandidatoA;
    int votosCandidatoB;

public:
    // Constructor parametrizado utilizando listas de inicialización para eficiencia
    UrnaElectronica(string mun, int votosA, int votosB)
        : municipio(mun), votosCandidatoA(votosA), votosCandidatoB(votosB) {}

    // getters ordinarios (¡TRAMPA PEDAGÓGICA: No están declarados como const!)
    string obtenerMunicipio() const { 
        return municipio; 
    }

    int obtenerVotosCandidatoA() const { 
        return votosCandidatoA; 
    }

    int obtenerVotosCandidatoB() const { 
        return votosCandidatoB; 
    }

    // Método modificador (No constante)
    void registrarVotoA() {
        votosCandidatoA++;
    }

    void registrarVotoB() {
        votosCandidatoB++;
    }
};

// ============================================================================
// FUNCIÓN DE AUDITORÍA EXTERNA (PASO POR REFERENCIA CONSTANTE)
// ============================================================================
void auditarVotacion(const UrnaElectronica& urna) {
    cout << "\n--- INICIANDO AUDITORIA ELECTORAL ---" << endl;
    
    // PASO 1: Los alumnos intentarán compilar estas líneas.
    // El compilador bloqueará las llamadas porque los métodos no tienen el calificador 'const'.
    cout << "Municipio: " << urna.obtenerMunicipio() << endl;
    cout << "Votos Candidato A: " << urna.obtenerVotosCandidatoA() << endl;
    cout << "Votos Candidato B: " << urna.obtenerVotosCandidatoB() << endl;
    
    // PASO 2: Intentar una modificación ilegal sobre un parámetro const (Debe fallar)
    // urna.registrarVotoA(); // Error de compilación directo
}

int main() {
    cout << "=== Inicializando Urna Regional ===" << endl;
    UrnaElectronica urnaCholula("San Andres Cholula", 15420, 14890);

    cout << "\nSimulando jornada electoral..." << endl;
    urnaCholula.registrarVotoA(); // Permitido sobre objetos modificables

    // Llamada a la función de auditoría defensiva
    auditarVotacion(urnaCholula);

    return 0;
}