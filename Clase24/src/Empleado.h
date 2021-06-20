/*
 * Empleado.h
 *
 *  Created on: May 11, 2021
 *      Author: Mauro
 */

#ifndef EMPLEADO_H_
#define EMPLEADO_H_
#define LONG_STRING 255
typedef struct
{
	char nombre[50];
	char apellido[50];
	char dni[20];
	int idEmpleado;
}Empleado;

Empleado* empleado_new(void);
Empleado* empleado_newParam(char* nombre,char* apellido,char* dni,int idEmpleado);

int empleado_delete(Empleado* this);

int empleado_setNombre(Empleado* this, char* nombre);
char* empleado_getNombre(Empleado* this,int* flagError);
int isValidNombre(char*);

int empleado_setApellido(Empleado* this,char* apellido);
char* empleado_getApellido(Empleado* this,int* flagError);
int isValidApellido(char*);

int empleado_setDni(Empleado* this,char* dni);
char* empleado_getDni(Empleado* this,int* flagError);
int isValidDni(char*);

int empleado_setId(Empleado* this,int idEmpleado);
int empleado_getId(Empleado* this,int* flagError);
int isValidId(int);
int emp_generarId(void);
void emp_setearValorInicialDeId(int id);

#include "collections/Dictionary.h"

int emp_alta(Dictionary* empleados);
int emp_modificar(Dictionary* empleados);
int emp_borrar(Dictionary* empleados);
int emp_parser(char nombreArchivo[],Dictionary* empleados,int* pIdMaxEncontrado);
int emp_imprimirLista(Dictionary* empleados);
int emp_dump(char nombreArchivo[],Dictionary* empleados);

#endif /* EMPLEADO_H_ */
