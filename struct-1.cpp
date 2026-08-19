#include <iostream>
#include <string>
using namespace std;

// Definición de la estructura
struct Persona {
    string nombre;
    int edad;

    // Función dentro del struct para mostrar datos
    void mostrarDatos() {
        cout << "Nombre: " << nombre << ", Edad: " << edad << " años" << endl;
    }

    // Función que modifica un valor interno
    void cumplirAnios() {
        edad++;
        cout << "¡Feliz cumpleaños, " << nombre << "!" << endl;
    }
};

int main() {
    // Crear una instancia de la estructura
    Persona p1;
    p1.nombre = "Carlos";
    p1.edad = 29;

    // Llamar a las funciones del struct usando el punto (.)
    p1.mostrarDatos();
    p1.cumplirAnios();
    p1.mostrarDatos();

    return 0;
}
