package java_hashmap;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashMap;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        HashMap<Integer, Estudiante> mapa = new HashMap<>();
        Scanner scanner = new Scanner(System.in);
        int opcion;


        System.out.println("  Nombre: Elder Geovani Samayoa Esquivel                   ");
        System.out.println("  Carnet: 9941 24 10076                                 ");
        System.out.println("___________________________________________________________");

        do {
            System.out.println("\n          MENU GENERAL            ");
            System.out.println("1. Cargar archivo CSV");
            System.out.println("2. Buscar estudiante por ID");
            System.out.println("3. Eliminar estudiante por ID");
            System.out.println("4. Mostrar evidencia de HashMap y total");
            System.out.println("5. Salir");
            System.out.print("Seleccione una opcion: ");
            opcion = scanner.nextInt();
            scanner.nextLine();

            switch (opcion) {
                case 1:
                    System.out.print("Ingrese el nombre del archivo (ej: estudiantes.csv): ");
                    String rutaArchivo = scanner.nextLine();

                    int iniciales = mapa.size();
                    int duplicados = 0;

                    try (BufferedReader br = new BufferedReader(new FileReader(rutaArchivo))) {
                        String linea = br.readLine();

                        while ((linea = br.readLine()) != null) {
                            if (linea.trim().isEmpty()) continue;

                            String[] datos = linea.split(",");
                            if (datos.length >= 6) {
                                int id = Integer.parseInt(datos[0].trim());
                                String nombre = datos[1].trim();
                                String carrera = datos[2].trim();
                                int semestre = Integer.parseInt(datos[3].trim());
                                double gpa = Double.parseDouble(datos[4].trim());
                                int skill = Integer.parseInt(datos[5].trim());

                                Estudiante est = new Estudiante(id, nombre, carrera, semestre, gpa, skill);

                                if (!mapa.containsKey(id)) {
                                    mapa.put(id, est);
                                    System.out.println("[+] Estudiante " + id + " insertado.");
                                } else {
                                    System.out.println("[-] Duplicado omitido: ID " + id);
                                    duplicados++;
                                }
                            }
                        }
                        System.out.println("\n[!] Carga finalizada.");
                        System.out.println("Nuevos registros: " + (mapa.size() - iniciales));
                        System.out.println("Duplicados omitidos: " + duplicados);

                    } catch (IOException | NumberFormatException e) {
                        System.out.println("[-] Error al abrir o leer el archivo: " + e.getMessage());
                    }
                    break;

                case 2:
                    System.out.print("ID a buscar: ");
                    int idBuscar = scanner.nextInt();
                    if (mapa.containsKey(idBuscar)) {
                        System.out.println("\n_________________________________________");
                        System.out.println(mapa.get(idBuscar));
                        System.out.println("____________________________________________");
                    } else {
                        System.out.println("[-] Estudiante no encontrado.");
                    }
                    break;

                case 3:
                    System.out.print("ID a eliminar: ");
                    int idEliminar = scanner.nextInt();
                    if (mapa.containsKey(idEliminar)) {
                        mapa.remove(idEliminar);
                        System.out.println("[+] Eliminado correctamente.");
                    } else {
                        System.out.println("[-] No se encontro ese ID.");
                    }
                    break;

                case 4:
                    System.out.println("\n             METRICAS HASH MAP           ");
                    System.out.println("Estructura:           " + mapa.getClass().getName());
                    System.out.println("Total estudiantes:    " + mapa.size());
                    System.out.println("IDs almacenados:      " + mapa.keySet());
                    System.out.println("___________________________________________________");
                    break;

                case 5:
                    System.out.println("Saliendo...");
                    break;

                default:
                    System.out.println("Opcion invalida.");
            }
        } while (opcion != 5);

        scanner.close();
    }
}