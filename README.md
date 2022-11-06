# Tarea 2

Autor: Gabriel Antonio Norambuena Muñoz.

Asignatura: Sistemas Operativos.

Lenguaje: C++

## Tabla de contenidos
1. [Descripción](#descripción)
2. [Consideraciones](#consideraciones)
3. [Entrada](#entrada)
4. [Salida](#salida)
5. [Compilacion](#compilación)
6. [Ejemplo archivo](#ejemplo-archivo)
7. [Ejemplo uso](#ejemplo-uso)

## Descripción

La tarea consiste en la creación de un programa que sea capaz de monitorizar un grupo
de dispositivos de red (computadoras, routers, switchs, access points, etc.) mediante pruebas
de conectividad y determinar el estado en que se encuentran cada uno de ellos. El programa
deberá ser implementado obligatoriamente utilizando Hebras.


## Consideraciones

- El programa debe correr en equipos con sistema operativo Linux.
- Debe utilizar el lenguaje de programación C++.
- Debe utilizar el compilador g++.
- Debe utilizar un archivo Makefile para la compilación mediante el comando make.
- La información capturada por el comando ping de cada IP deberá almacenarse en una estructura de datos compartida, la que será modificada por cada
hebra una vez terminada su validación. Esta estructura debe ser utilizada para generar
el reporte final. Los datos que debe contener cada elemento de la estructura de datos
es la siguiente:
    - IP.
    - paquetes transmitidos.
    - paquetes recibidos.
    - paquetes perdidos.
    - estado.

## Entrada

- Cantidad de paquetes a enviar. 

- Cantidad de paquetes que enviará el comando ping a cada dirección IP para conocer sus estado.

## Salida

- El reporte de salida debe entregar la información de disponibilidad de cada IP monitorizada, con el siguiente formato por lı́nea:
    - Número IP
    - Paquetes Transmitidos
    - Paquetes Recibidos
    - Paquetes Perdidos
    - Estado (UP = Disponible, DOWN = NO disponible)

## Compilación
~~~
make tarea
~~~

## Ejemplo archivo

~~~
192.168.10.1
192.168.10.2
192.168.10.3
192.168.10.4
192.168.10.5
~~~

## Ejemplo uso

 ~~~
tarea ip.txt 10
 ~~~
