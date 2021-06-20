/*
1- EJERCICIO PARA COMPLETAR.

Realizar un programa que permita la administracion de empleados, utilizando un diccionario en
lugar de una lista enlazada.
El programa cuenta con las opciones de
1)Leer archivo CSV (debe leer el archivo y cargar un diccionario con los empleados
2)Listar empleados (debe imprimir por consola la lista de empleados con sus datos)
3)Alta empleado (debe pedirle los datos de un empleado al usuario y agregarlo a la lista de empleados)
4)Modificar (se debe ingresar el ID del empleado y se podra modificar sus datos)
5)Baja (se debe ingresar el ID del empleado y se podra eliminar)
6)Escribir archivo CSV (Escribe la lista de empleados de nuevo en el archivo)
7)Salir\n

Utilizar el diccionario de la siguiente manera:
clave : ID del empleado en formato texto (cadena de caracteres)
valor : puntero a variable del tipo "Empleado"

Preguntas para debatir:
1) Que debo hacer para imprimir los empleados
2) Que debo hacer para encontrar un empleadopor su ID
3) Que debo hacer para encontrar un empleadopor su DNI
4) Que ventajas observa al usar un diccionario en vez de una lista ordenada
5) Que desventajas observa al usar un diccionario en vez de una lista ordenada

2- EXTRAS
- Agregar al empleado el campo "Hora de entrada" del tipo int (de 0 a 23)
- Agregar una opcion en el menu para listar las horas a las que entra gente a trabajar (sin repetir)
- Agregar una opcion al menu para listar las diferentes horas de entrada junto con la cantidad de empleados que entra a cada hora.

*/

#include <stdio.h>
#include <stdlib.h>
#include "Empleado.h"
#include "utn.h"
#include "collections/LinkedList.h"

#define TXT_MENU "MENU\n1)Leer archivo CSV\n2)Listar empleados\n3)Alta empleado\n4)Modificar\n5)Baja\n6)Escribir archivo CSV\n7)Salir\n"

#define OP_LEER			1
#define OP_LISTAR		2
#define OP_ALTA			3
#define OP_MODIF		4
#define OP_BAJA			5
#define OP_ESCRIBIR		6
#define OP_SALIR		7


int main(void)
{
	setbuf(stdout,NULL);
	int opcion=0;
	Dictionary* empleados;
	int idMax=-1;
	empleados = dict_new(0);
	do{
		if(utn_getEntero(TXT_MENU,"Error",&opcion,3,7,0)==0)
		{
			switch(opcion)
			{
				case OP_LEER:
				{
					emp_parser("empleados.csv",empleados,&idMax);
					emp_setearValorInicialDeId(idMax);
					break;
				}
				case OP_LISTAR:
				{
					emp_imprimirLista(empleados);
					break;
				}
				case OP_ALTA:
				{
					emp_alta(empleados);
					break;
				}
				case OP_MODIF:
				{
					emp_modificar(empleados);
					break;
				}
				case OP_BAJA:
				{
					emp_borrar(empleados);
					break;
				}
				case OP_ESCRIBIR:
				{
					emp_dump("empleados_out.csv",empleados);
					break;
				}
			}
		}
	}while(opcion!=OP_SALIR);

	return EXIT_SUCCESS;
}

