#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Paciente
{
private:
    string nombre;
    int edad;
    string expedienteMedico;

public:

    // Constructor por defecto
    Paciente()
        : nombre("Habitacion Vacia"),
          edad(0),
          expedienteMedico("No asignado")
    {
    }

    // Constructor parametrizado
    Paciente(string nombre, int edad, string expediente)
        : nombre(nombre),
          edad(edad),
          expedienteMedico(expediente)
    {
    }

    // Constructor de copia
    Paciente(const Paciente& otro)
        : nombre(otro.nombre),
          edad(otro.edad),
          expedienteMedico(otro.expedienteMedico)
    {
    }

    bool habitacionVacia() const
    {
        return nombre == "Habitacion Vacia";
    }

    void limpiarHabitacion()
    {
        nombre = "Habitacion Vacia";
        edad = 0;
        expedienteMedico = "No asignado";
    }

    void mostrarInformacion() const
    {
        cout << "Nombre: " << nombre << endl;
        cout << "Edad: " << edad << endl;
        cout << "Expediente: " << expedienteMedico << endl;
    }
};

void mostrarHabitaciones(const vector<Paciente>& habitaciones)
{
    cout << "\n===== ESTADO DE HABITACIONES =====\n";

    for (size_t i = 0; i < habitaciones.size(); i++)
    {
        cout << "\nHabitacion " << i + 1 << endl;
        cout << "------------------------" << endl;

        habitaciones[i].mostrarInformacion();

        cout << endl;
    }
}

int main()
{
    vector<Paciente> habitaciones(5);

    int opcion;

    do
    {
        cout << "\n====================================";
        cout << "\n SISTEMA DE ADMISION DE CLINICA";
        cout << "\n====================================";
        cout << "\n1. Ver habitaciones";
        cout << "\n2. Admitir paciente";
        cout << "\n3. Transferir paciente";
        cout << "\n4. Salir";
        cout << "\n\nSeleccione una opcion: ";
        cin >> opcion;

        switch(opcion)
        {
            case 1:
            {
                mostrarHabitaciones(habitaciones);
                break;
            }

            case 2:
            {
                int numHabitacion;
                string nombre;
                string expediente;
                int edad;

                cout << "\nHabitacion (1-5): ";
                cin >> numHabitacion;

                if(numHabitacion < 1 || numHabitacion > 5)
                {
                    cout << "\nHabitacion invalida.\n";
                    break;
                }

                cin.ignore();

                cout << "Nombre del paciente: ";
                getline(cin, nombre);

                cout << "Edad: ";
                cin >> edad;

                cin.ignore();

                cout << "Expediente medico: ";
                getline(cin, expediente);

                habitaciones[numHabitacion - 1] =
                    Paciente(nombre, edad, expediente);

                cout << "\nPaciente admitido correctamente.\n";

                break;
            }

            case 3:
            {
                int origen;
                int destino;

                cout << "\nHabitacion origen (1-5): ";
                cin >> origen;

                cout << "Habitacion destino (1-5): ";
                cin >> destino;

                if(origen < 1 || origen > 5 ||
                   destino < 1 || destino > 5)
                {
                    cout << "\nNumero de habitacion invalido.\n";
                    break;
                }

                if(origen == destino)
                {
                    cout << "\nLa habitacion origen y destino no pueden ser la misma.\n";
                    break;
                }

                if(habitaciones[origen - 1].habitacionVacia())
                {
                    cout << "\nLa habitacion origen esta vacia.\n";
                    break;
                }

                if(!habitaciones[destino - 1].habitacionVacia())
                {
                    cout << "\nLa habitacion destino ya esta ocupada.\n";
                    break;
                }

                // Constructor de copia
                Paciente copia(habitaciones[origen - 1]);

                // Mover al paciente a la nueva habitación
                habitaciones[destino - 1] = copia;

                // Liberar la habitación anterior
                habitaciones[origen - 1].limpiarHabitacion();

                cout << "\nTransferencia realizada correctamente." << endl;
                cout << "Se utilizo el constructor de copia para crear el nuevo registro." << endl;

                break;
            }

            case 4:
            {
                cout << "\nSaliendo del sistema...\n";
                break;
            }

            default:
            {
                cout << "\nOpcion invalida.\n";
            }
        }

    } while(opcion != 4);

    return 0;
}