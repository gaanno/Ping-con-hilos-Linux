#include <iostream>
#include <string>
#include <sstream>

class LlamarComando
{
    public:
        std::string ip;
        std::string cantidadPaquetes;
        std::string getIp();
        void ejecutarComando();
        int getCantidadPaquetesRecibidos();
        int getCantidadPaquetesPerdidos();
        int getCantidadPaquetesTransmitidos();
        LlamarComando(std::string ip, std::string cantidadPaquetes);

    private:
        std::string respuesta;
        int paquetesTransmitidos;
        int paquetesRecibidos;
        int paquetesPerdidos;
        void separarRespuesta();
};

// constructor
LlamarComando::LlamarComando(std::string ip, std::string cantidadPaquetes)
{
    this->ip = ip;
    this->cantidadPaquetes = cantidadPaquetes;
}

// limpia aun mas la respuesta obtenida de ping
void LlamarComando::separarRespuesta()
{
    std::stringstream input_stringstream(this->respuesta);
    std::string aux;
    getline(input_stringstream, aux, '\n');
    this->paquetesTransmitidos = std::stoi(aux);
    getline(input_stringstream, aux, '\n');
    this->paquetesRecibidos = std::stoi(aux);
    this->paquetesPerdidos = this->paquetesTransmitidos - this->paquetesRecibidos;
}

// ejecuta el comando ping y separa los paquetes transmitidos con los paquetes recividos
void LlamarComando::ejecutarComando()
{
    std::string comando = "ping -q -c " + this->cantidadPaquetes + " " + this->ip + " | grep -oP '[\\d+.,]+(?= packets transmitted)'\\|'[\\d+.,]+(?= received)'";
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

// retorna la ip
std::string LlamarComando::getIp()
{
    return this->ip;
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
