#include <iostream>
#include <string>
#include <omp.h>    // para las hebras
#include <fstream>  // leer archivo
#include <vector>   // para vector con las ip
#include <cctype>   // isdigit
#include "LlamarComando.h" // clase que manipula el comando ping

// estructura
struct Nodo
{
    std::string ip;
    std::string estado;
    int paquetesTransmitidos;
    int paquetesRecibidos;
    int paquetesPerdidos;
    Nodo *siguiente;
};

// prototipos
void agregarPila(Nodo *&, std::string ip, int paquetesTransmitidos, int paquetesRecibidos, int paquetesPerdidos);
void imprimirPila(Nodo *);
bool esNumero(const std::string &str);

// main
int main(int argc, char *argv[])
{
    // comprobar  argumentos pasados
    if (argc != 3 || esNumero(argv[2]) == false)
    {
        std::cout << "Error: Argumentos invalidos" << std::endl;
        return 1;
    }

    // declaracion de variables
    Nodo *pila = NULL;
    int cantidadIp = 0;
    int paquetesRecibidos;
    int paquetesTransmitidos;
    int cantidadElementos = 0;
    std::string linea;
    std::string archivoEntrada = argv[1];
    std::string cantidadPaquetes = argv[2];
    std::vector<std::string> ips;
    std::ifstream archivo(archivoEntrada);


    // comprobar que se pudo abrir el archivo
    if (!archivo.is_open())
    {
        std::cout << "Error: No se pudo abrir el archivo < " << archivoEntrada << " >" << std::endl;
        return 1;
    }

    // recorrer archivo con las ips para almacenarlas en un vector
    while (std::getline(archivo, linea))
    {
        if (linea != "")
        {
            ips.push_back(linea);
        }
    }
    // cierro archivo
    archivo.close();

    // cuenta las cantidades de ip
    cantidadIp = ips.size();

    // hebras segun la cantidad de ip encontradas
    #pragma omp parallel num_threads (cantidadIp)
    {
        #pragma omp for
        for (auto x : ips)
        {
            // objeto de la clase creada
            LlamarComando obj(x, cantidadPaquetes);
            obj.ejecutarComando();

            // protege la pila
            #pragma omp critical
            {
                //agrego elemento a la pila
                agregarPila(pila, obj.ip, obj.getCantidadPaquetesTransmitidos(), obj.getCantidadPaquetesRecibidos(), obj.getCantidadPaquetesPerdidos());
            }
        }
    }
    // mostrar los elementos de la pila
    imprimirPila(pila);
}

// comprueba si un string es solo numeros
bool esNumero(const std::string &str)
{
    for (char const &val : str)
    {
        if (std::isdigit(val) == 0){
            return false;
        }
    }
    return true;
}

// agregar elementos a la pila
void agregarPila(Nodo *&pila, std::string ip, int paquetesTransmitidos, int paquetesRecibidos, int paquetesPerdidos)
{
    Nodo *nuevoNodo = new Nodo();
    nuevoNodo->ip = ip;
    nuevoNodo->estado = (paquetesRecibidos > 0) ? "UP" : "DOWN";
    nuevoNodo->paquetesTransmitidos = paquetesTransmitidos;
    nuevoNodo->paquetesRecibidos = paquetesRecibidos;
    nuevoNodo->paquetesPerdidos = paquetesPerdidos;
    nuevoNodo->siguiente = pila;
    pila = nuevoNodo;
}

// imprimir los elementos de la pila
void imprimirPila(Nodo *pila)
{
    std::cout << "IP\t\tESTADO\tTRANS.\tRECIB.\tPERD." << std::endl;
    Nodo *aux = pila;
    while (aux != NULL)
    {
        std::cout << aux->ip << "\t";
        std::cout << aux->estado << "\t";
        std::cout << aux->paquetesTransmitidos << "\t";
        std::cout << aux->paquetesRecibidos << "\t";
        std::cout << aux->paquetesPerdidos << std::endl;
        aux = aux->siguiente;
    }
}