#include <iostream>
#include <string>

using namespace std;

class Paciente
{
	private:
	    string nombre;
	    int edad;
	    string expedienteMedico;
	
	public:
	
	    Paciente()
	        : nombre("Habitacion Vacia"),
	          edad(0),
	          expedienteMedico("No asignado")
	    {
	    }
	
	    Paciente(string n, int e, string exp)
	        : nombre(n),
	          edad(e),
	          expedienteMedico(exp)
	    {
	    }
	
	    Paciente(const Paciente& otro)
	        : nombre(otro.nombre),
	          edad(otro.edad),
	          expedienteMedico(otro.expedienteMedico)
	    {
	    }
	
	    void mostrarInformacion() const
	    {
	        cout << "\nNombre: " << nombre;
	        cout << "\nEdad: " << edad;
	        cout << "\nExpediente: " << expedienteMedico;
	        cout << "\n------------------------";
	    }
};

int main(){
	int opcion;
	do
	{
	    cout << "\n===== CLINICA =====";
	    cout << "\n1. Ver habitaciones";
	    cout << "\n2. Admitir paciente";
	    cout << "\n3. Transferir paciente";
	    cout << "\n4. Salir";
	
	    cin >> opcion;
	
	    switch(opcion)
	    {
	        case 1:
	            // mostrar habitaciones
	            break;
	
	        case 2:
	            // admitir paciente
	            break;
	
	        case 3:
	            // transferir paciente
	            break;
	
	        case 4:
	            cout << "\nFin del sistema";
	            break;
	
	        default:
	            cout << "\nOpcion invalida";
	    }
	
	} while(opcion != 4);
	return 0;
}