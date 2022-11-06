#include <iostream>
#include <string>
#include <sstream>  // stringstream

// Clase para manipular comando ping
class LlamarComando
{
    public:
        std::string ip;
        std::string cantidadPaquetes;
        std::string getIp();
        void ejecutarComando();
        int getCantidadPaquetesPerdidos();
        int getCantidadPaquetesRecibidos();
        int getCantidadPaquetesTransmitidos();
        LlamarComando(std::string ip, std::string cantidadPaquetes);

    private:
        std::string respuesta;
        int paquetesPerdidos;
        int paquetesRecibidos;
        int paquetesTransmitidos;
        void separarRespuesta();
};

// constructor
LlamarComando::LlamarComando(std::string ip, std::string cantidadPaquetes)
{
    this->ip = ip;
    this->cantidadPaquetes = cantidadPaquetes;
}

// limpia aun mas la respuesta obtenida de ping y las almacena en variables
void LlamarComando::separarRespuesta()
{
    std::stringstream inputStringstream(this->respuesta);
    std::string aux;
    getline(inputStringstream, aux, '\n');
    this->paquetesTransmitidos = std::stoi(aux);
    getline(inputStringstream, aux, '\n');
    this->paquetesRecibidos = std::stoi(aux);
    this->paquetesPerdidos = this->paquetesTransmitidos - this->paquetesRecibidos;
}

// ejecuta el comando ping y separa los paquetes transmitidos con los paquetes recibidos
void LlamarComando::ejecutarComando()
{
    // pipe para simplificar la lectura de la respuesta
    std::string grep = " | grep -oP '[\\d+.,]+(?= packets transmitted)'\\|'[\\d+.,]+(?= received)'";

    // comando ping a ejecutar
    std::string comando = "ping -q -c " + this->cantidadPaquetes + " " + this->ip + grep;

    // ejecuta el comando guardando la respuesta de la terminal en variable respuesta
    char buffer[256];
    FILE *pipe = popen(comando.c_str(), "r");
    if (!pipe)
    {
        return;
    }
    while (!feof(pipe))
    {
        if (fgets(buffer, 256, pipe) != NULL)
            this->respuesta += buffer;
    }
    pclose(pipe);
    this->separarRespuesta();
}

// retorna la cantidad de paquetes recibidos
int LlamarComando::getCantidadPaquetesRecibidos()
{
    return this->paquetesRecibidos;
}

// retorna la cantidad de paquetes transmitidos
int LlamarComando::getCantidadPaquetesTransmitidos()
{
    return this->paquetesTransmitidos;
}

// retorna la cantidad de paquetes perdidos
int LlamarComando::getCantidadPaquetesPerdidos()
{
    return this->paquetesPerdidos;
}
