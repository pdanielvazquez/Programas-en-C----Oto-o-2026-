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

    void mostrarInformacion() const
    {
        cout << "\nNombre: " << nombre;
        cout << "\nEdad: " << edad;
        cout << "\nExpediente: " << expedienteMedico;
        cout << "\n------------------------------\n";
    }

    bool habitacionVacia() const
    {
        return nombre == "Habitacion Vacia";
    }
};

void mostrarHabitaciones(const vector<Paciente>& habitaciones)
{
    cout << "\n===== ESTADO DE HABITACIONES =====\n";

    for(size_t i = 0; i < habitaciones.size(); i++)
    {
        cout << "\nHabitacion " << i + 1 << ":\n";
        habitaciones[i].mostrarInformacion();
    }
}

int main()
{
    vector<Paciente> habitaciones(5);
    vector<Paciente> pacientesTransferidos;

    int opcion;

    do
    {
        cout << "\n\n===== SISTEMA DE ADMISION DE CLINICA =====";
        cout << "\n1. Ver habitaciones";
        cout << "\n2. Admitir paciente";
        cout << "\n3. Transferir paciente";
        cout << "\n4. Ver pacientes transferidos";
        cout << "\n5. Salir";
        cout << "\nSeleccione una opcion: ";
        cin >> opcion;

        switch(opcion)
        {
            case 1:
                mostrarHabitaciones(habitaciones);
                break;

            case 2:
            {
                int numHabitacion;
                string nombre;
                string expediente;
                int edad;

                cout << "\nNumero de habitacion (1-5): ";
                cin >> numHabitacion;

                if(numHabitacion < 1 || numHabitacion > 5)
                {
                    cout << "\nHabitacion invalida.";
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

                habitaciones[numHabitacion - 1] = Paciente(nombre, edad, expediente);

                cout << "\nPaciente admitido correctamente.";
                break;
            }

            case 3:
            {
                int numHabitacion;

                cout << "\nHabitacion a transferir (1-5): ";
                cin >> numHabitacion;

                if(numHabitacion < 1 || numHabitacion > 5)
                {
                    cout << "\nHabitacion invalida.";
                    break;
                }

                Paciente copia(habitaciones[numHabitacion - 1]);
                pacientesTransferidos.push_back(copia);

                cout << "\nTransferencia realizada usando el constructor de copia.";
                break;
            }

            case 4:
            {
                cout << "\n===== PACIENTES TRANSFERIDOS =====\n";

                if(pacientesTransferidos.empty())
                {
                    cout << "\nNo hay pacientes transferidos.\n";
                }
                else
                {
                    for(const auto& paciente : pacientesTransferidos)
                    {
                        paciente.mostrarInformacion();
                    }
                }
                break;
            }

            case 5:
                cout << "\nSaliendo del sistema...\n";
                break;

            default:
                cout << "\nOpcion invalida.";
        }

    } while(opcion != 5);

    return 0;
}
