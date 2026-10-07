#include "Figura.h"
#include <windows.h>
#if defined(_WIN32) || defined(_WIN64)
	#define EXPORT __declspec(dllexport)
#else
	#define EXPORT __attribute__((visibility("default")))
#endif

BOOL APIENTRY DllMain(HINSTANCE hInst, DWORD reason, LPVOID reserved) {
    switch (reason) {
        case DLL_PROCESS_ATTACH:
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;
}

extern "C" {
	// Funciones Fábrica (Instanciación en el Heap de C++)
	EXPORT Figura* crearCirculo(double radio) { 
		return new Circulo(radio); 
		}
	EXPORT Figura* crearCuadro(double lado) { 
		return new Cuadro(lado); 
	}
	EXPORT Figura* crearTriangulo(double base, double altura, double l1, double l2, double l3) { 
		return new Triangulo(base, altura, l1, l2, l3); 
	} 
	EXPORT Figura* crearPoligono(int numLados, double longitudLado, double apotema) { 
		return new Poligono(numLados, longitudLado, apotema); 
	}
	// Métodos Polimórficos Invoca la vtable
	EXPORT double calcularPerimetro(Figura* fig) { 
		return fig ? fig->calcularPerimetro() : 0.0; 
	}
	EXPORT double calcularArea(Figura* fig) { 
		return fig ? fig->calcularArea() : 0.0; 
	}
	EXPORT double calcularVolumen(Figura* fig) { 
		return fig ? fig->calcularVolumen() : 0.0; 
	}
	// Destrucción Segura de Memoria
	EXPORT void destruirFigura(Figura* fig) {
		if (fig) { 
			delete fig; // Invoca destructor virtual en cascada 
		}
	}
}
