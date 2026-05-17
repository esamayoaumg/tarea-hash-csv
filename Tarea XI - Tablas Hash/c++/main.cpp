#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct Student {
    int student_id;
    string full_name;
    string career;
    int semester;
    float gpa;
    int skill_score;
};

struct Nodo {
    Student dato;
    Nodo* siguiente;
};

class TablaHash {
private:
    Nodo** tabla;
    int tamanio;

public:
    int cantidad;
    int colisiones;

    // Constructor: Inicializa la tabla con punteros en NULL
    TablaHash(int t) {
        tamanio = t;
        cantidad = 0;
        colisiones = 0;
        tabla = new Nodo*[tamanio];
        for (int i = 0; i < tamanio; i++) {
            tabla[i] = NULL;
        }
    }

    // Destructor: Libera de forma limpia toda la memoria reservada dinámicamente
    ~TablaHash() {
        for (int i = 0; i < tamanio; i++) {
            Nodo* aux = tabla[i];
            while (aux != NULL) {
                Nodo* temp = aux;
                aux = aux->siguiente;
                delete temp;
            }
        }
        delete[] tabla;
    }

    int funcionHash(int id) {
        return id % tamanio;
    }

    bool existe(int id) {
        int indice = funcionHash(id);
        Nodo* aux = tabla[indice];
        while (aux != NULL) {
            if (aux->dato.student_id == id) return true;
            aux = aux->siguiente;
        }
        return false;
    }

    void insertar(Student e) {
        if (existe(e.student_id)) {
            cout << "[-] Error: Estudiante con ID " << e.student_id << " ya duplicado.\n";
            return;
        }

        int indice = funcionHash(e.student_id);
        Nodo* nuevo = new Nodo;
        nuevo->dato = e;
        nuevo->siguiente = NULL;

        // Si la posición ya tiene datos, se contabiliza una colisión
        if (tabla[indice] != NULL) {
            colisiones++;
        }

        // Inserción al inicio de la lista del bucket (Separate Chaining)
        nuevo->siguiente = tabla[indice];
        tabla[indice] = nuevo;
        cantidad++;
        cout << "[+] Estudiante " << e.student_id << " insertado en Bucket " << indice << ".\n";
    }

    void buscar(int id) {
        int indice = funcionHash(id);
        Nodo* aux = tabla[indice];

        while (aux != NULL) {
            if (aux->dato.student_id == id) {

                cout << "         ESTUDIANTE ENCONTRADO          \n";
                cout << "-------------------------------------------\n";
                cout << "ID:          " << aux->dato.student_id << "\n";
                cout << "Nombre:      " << aux->dato.full_name << "\n";
                cout << "Carrera:     " << aux->dato.career << "\n";
                cout << "Semestre:    " << aux->dato.semester << "\n";
                cout << "GPA:         " << aux->dato.gpa << "\n";
                cout << "Skill Score: " << aux->dato.skill_score << "\n";
                cout << "========================================\n";
                return;
            }
            aux = aux->siguiente;
        }
        cout << "[-] Error: Estudiante no encontrado.\n";
    }

    void eliminar(int id) {
        int indice = funcionHash(id);
        Nodo* aux = tabla[indice];
        Nodo* anterior = NULL;

        while (aux != NULL) {
            if (aux->dato.student_id == id) {
                if (anterior == NULL) {
                    tabla[indice] = aux->siguiente;
                } else {
                    anterior->siguiente = aux->siguiente;
                }
                delete aux;
                cantidad--;
                cout << "[+] Estudiante con ID " << id << " eliminado correctamente.\n";
                return;
            }
            anterior = aux;
            aux = aux->siguiente;
        }
        cout << "[-] Error: Estudiante no encontrado para eliminar.\n";
    }

    void mostrarTabla() {
        cout << "\n===== ESTRUCTURA DE LA TABLA POR BUCKETS =====\n";
        for (int i = 0; i < tamanio; i++) {
            cout << "Bucket [" << i << "]: ";
            Nodo* aux = tabla[i];
            if (aux == NULL) {
                cout << "vacio";
            }
            while (aux != NULL) {
                cout << "(" << aux->dato.student_id << ", " << aux->dato.full_name << ") -> ";
                aux = aux->siguiente;
            }
            cout << "NULL\n";
        }
    }

    void mostrarEstadisticas() {
        cout << "\n========== METRICAS HASH ==========\n";
        cout << "Cantidad de estudiantes: " << cantidad << endl;
        cout << "Colisiones generadas:    " << colisiones << endl;
        float factor = (float)cantidad / tamanio;
        cout << "Factor de carga:         " << factor << endl;
        cout << "===================================\n";
    }

    void cargarCSV(string nombreArchivo) {
        ifstream archivo(nombreArchivo);
        if (!archivo) {
            cout << "[-] Error: No se pudo abrir el archivo " << nombreArchivo << "\n";
            return;
        }

        string linea;
        getline(archivo, linea); // Omitir la fila de encabezados

        int iniciales = cantidad;
        while (getline(archivo, linea)) {
            if (linea.empty()) continue;
            
            stringstream ss(linea);
            string dato;
            Student e;

            getline(ss, dato, ',');      e.student_id = stoi(dato);
            getline(ss, e.full_name, ',');
            getline(ss, e.career, ',');
            getline(ss, dato, ',');      e.semester = stoi(dato);
            getline(ss, dato, ',');      e.gpa = stof(dato);
            getline(ss, dato, ',');      e.skill_score = stoi(dato);

            insertar(e);
        }
        archivo.close();
        cout << "\n[!] Proceso finalizado. Registros nuevos: " << (cantidad - iniciales) << "\n";
    }
};

int main() {
    // Definición de tamaño inicial de la tabla (10 buckets)
    TablaHash tabla(10);
    int opcion;

    cout << "  Nombre: Elder Geovani Samayoa Esquivel             \n";
    cout << "  Carnet: 9941 24 10076                         \n";
    cout << "================================================\n";

    do {
        cout << "\n      MENU GENERAL     \n";
        cout << "1. Cargar archivo CSV\n";
        cout << "2. Buscar estudiante por ID\n";
        cout << "3. Eliminar estudiante por ID\n";
        cout << "4. Mostrar contenido de tabla\n";
        cout << "5. Mostrar estadisticas\n";
        cout << "6. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1: {
                string archivo;
                cout << "Ingrese el nombre del archivo (ej: estudiantes.csv): ";
                cin >> archivo;
                tabla.cargarCSV(archivo);
                break;
            }
            case 2: {
                int id;
                cout << "ID del estudiante a buscar: ";
                cin >> id;
                tabla.buscar(id);
                break;
            }
            case 3: {
                int id;
                cout << "ID del estudiante a eliminar: ";
                cin >> id;
                tabla.eliminar(id);
                break;
            }
            case 4:
                tabla.mostrarTabla();
                break;
            case 5:
                tabla.mostrarEstadisticas();
                break;
            case 6:
                cout << "Cerrando aplicacion C++...\n";
                break;
            default:
                cout << "Opcion no valida.\n";
        }
    } while (opcion != 6);

    return 0;
}