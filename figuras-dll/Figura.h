#ifndef FIGURA_H
#define FIGURA_H
#include<cmath>
#include<iostream>
// Clase Base Abstracta
class Figura {
	public:
		virtual ~Figura() = default; // Destructor virtual imprescindible
		virtual double calcularPerimetro() const = 0;
		virtual double calcularArea() const = 0;
		virtual double calcularVolumen() const { return 0.0; }
};
// Subclases Circulo
class Circulo : public Figura {
	private:
		double radio;
		double M_PI = 3.1416;
	public:
		Circulo(double r) : radio(r) {}
		double calcularPerimetro() const override { return 2 * M_PI * radio; }
		double calcularArea() const override { return M_PI * radio * radio; }
};
// Subclase Cuadro
class Cuadro : public Figura {
	private:
		double lado;
	public:
		Cuadro(double l) : lado(l) {}
		double calcularPerimetro() const override { return 4 * lado; }
		double calcularArea() const override { return lado * lado; }
};
// Subclase Triángulo 
class Triangulo : public Figura { 
	private: 
		double base; 
		double altura; 
		double lado1, lado2, lado3; 
	public: 
		Triangulo(double b, double h, double l1, double l2, double l3) : 
			base(b), 
			altura(h), 
			lado1(l1), 
			lado2(l2), 
			lado3(l3) {} 
		double calcularPerimetro() const override { 
			return lado1 + lado2 + lado3; 
		} 
		double calcularArea() const override { 
			return (base * altura) / 2.0; 
		} 
}; 
// Subclase Polígono Regular (n lados) 
class Poligono : public Figura { 
	private: 
		int numLados; 
		double longitudLado; 
		double apotema; 
	public: 
		Poligono(int n, double l, double ap) : 
			numLados(n), 
			longitudLado(l), 
			apotema(ap) {} 
		double calcularPerimetro() const override { 
			return numLados * longitudLado; 
		} 
		double calcularArea() const override { 
			return (calcularPerimetro() * apotema) / 2.0; 
		} 
};
#endif