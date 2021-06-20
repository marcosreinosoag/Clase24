/*
 * Empleado.c
 *
 *  Created on: May 11, 2021
 *      Author: Mauro
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Empleado.h"
#include "utn.h"
#include "collections/LinkedList.h"

Empleado* empleado_new(void)
{
	return (Empleado*) malloc(sizeof(Empleado));
}

Empleado* empleado_newParam(char* nombre,char* apellido,char* dni,int idEmpleado)
{
	Empleado* auxEmpleado = empleado_new();
	if(auxEmpleado != NULL)
	{
		if  ( 	empleado_setNombre(auxEmpleado,nombre) < 0 ||
				empleado_setApellido(auxEmpleado,apellido) < 0 ||
				empleado_setDni(auxEmpleado,dni) < 0 ||
				empleado_setId(auxEmpleado,idEmpleado) < 0 )
		{
			empleado_delete(auxEmpleado);
			auxEmpleado = NULL;
		}
	}
	return auxEmpleado;;
}

int empleado_delete(Empleado* this)
{
	int retorno = -1;
	if(this != NULL)
	{
		free(this);
		retorno = 0;
	}
	return retorno;
}

int empleado_setNombre(Empleado* this, char* nombre)
{
	int retorno = -1;
	if(this != NULL && nombre != NULL && isValidNombre(nombre) )
	{
		strcpy(this->nombre,nombre);
		retorno = 0;
	}
	return retorno;
}

char* empleado_getNombre(Empleado* this,int* flagError)
{
	*flagError = -1;
	char* auxNombre= NULL;
	if(this != NULL && flagError != NULL )
	{
		auxNombre = this->nombre;
		*flagError = 0;
	}
	return auxNombre;
}

int isValidNombre(char* nombre)
{
	return 1;
}

int empleado_setApellido(Empleado* this, char* apellido)
{
	int retorno = -1;
	if(this != NULL && apellido != NULL && isValidApellido(apellido) )
	{
		strcpy(this->apellido,apellido);
		retorno = 0;
	}
	return retorno;
}

char* empleado_getApellido(Empleado* this,int* flagError)
{
	*flagError = -1;
	char* aux= NULL;
	if(this != NULL && flagError != NULL )
	{
		aux = this->apellido;
		*flagError = 0;
	}
	return aux;
}


int isValidApellido(char* apellido)
{
	return 1;
}


int empleado_setDni(Empleado* this, char* dni)
{
	int retorno = -1;
	if(this != NULL && dni != NULL && isValidDni(dni) )
	{
		strcpy(this->dni,dni);
		retorno = 0;
	}
	return retorno;
}

char* empleado_getDni(Empleado* this,int* flagError)
{
	*flagError = -1;
	char* aux= NULL;
	if(this != NULL && flagError != NULL )
	{
		aux = this->dni;
		*flagError = 0;
	}
	return aux;
}

int isValidDni(char* dni)
{
	return 1;
}

int empleado_setId(Empleado* this, int idEmpleado)
{
	int retorno = -1;
	if(this != NULL && isValidId(idEmpleado) )
	{
		this->idEmpleado = idEmpleado;
		retorno = 0;
	}
	return retorno;
}



int empleado_getId(Empleado* this,int* flagError)
{
	*flagError = -1;
	int auxId = -1;
	if(this != NULL && flagError != NULL )
	{
		auxId=this->idEmpleado;
		*flagError = 0;
	}
	return auxId;
}

int isValidId(int idEmpleado)
{
	return 1;
}

static int contador=0; // NO ES LOCAL DE LA FUNCION

void emp_setearValorInicialDeId(int id)
{
	contador = id;
}

int emp_generarId(void)
{
	contador++;
	return contador;
}


//************************************************************************
int emp_alta(Dictionary* empleados)
{
	int ret=-1;
	int idEmp;
	char auxNombre[255];
	char auxApellido[255];
	char auxDni[255];
	char auxId[255];
	Empleado* pE;
	if(utn_getNombre("Ingrese Nombre:","Error!!!! Reingrese Nombre:",auxNombre,3,255)==0 &&
	   utn_getNombre("Ingrese Apellido:","Error!!!! Reingrese Apellido:",auxApellido,3,255)==0 &&
	   utn_getTextoSoloNumeros("Ingrese Sueldo:","Error!!!! Reingrese Sueldo:",auxDni,3,255)==0)
	   {
			idEmp=emp_generarId();
			pE=empleado_newParam(auxNombre,auxApellido,auxDni,idEmp);
			sprintf(auxId,"%d",idEmp);
			if(pE!=NULL)
			{
				dict_insert(empleados, auxId, pE);
				ret=0;
				printf("-------------------------------------ALTA REALIZADA CORRECTAMENTE---------------------------------------\n");
			}
			else
			{
				empleado_delete(pE);
			}
	  }
	return ret;
}

int emp_modificar(Dictionary* empleados)
{
	char cadenaIdAModif[32];
	char auxNombre[LONG_STRING];
	char auxApellido[LONG_STRING];
	char auxDni[LONG_STRING];
	int ret=-1;
	if(utn_getTextoSoloNumeros("Ingrese id a modificar:","Error",cadenaIdAModif,3,sizeof(cadenaIdAModif))==0)
	{
		Empleado* pE;
		pE=dict_get(empleados,cadenaIdAModif);
		if(pE!=NULL)
		{
			if(utn_getNombre("Ingrese Nombre:","Error!!! Reingrese nombre: ",auxNombre,2,LONG_STRING)==0 &&///////ver funcion para simplificar cod
			   utn_getNombre("Ingrese Apellido:","Error!!! Reingrese Apellido: ",auxApellido,2,LONG_STRING)==0 &&
			   utn_getTextoSoloNumeros("Ingrese Sueldo:","Error!!! Reingrese Sueldo: ",auxDni,2,LONG_STRING)==0)
				{
					if(empleado_setNombre(pE,auxNombre)==0 &&
					   empleado_setApellido(pE,auxApellido)==0 &&
					   empleado_setDni(pE,auxDni)==0)
					   {
							printf("\n--------------------EL EMPLEADO FUE MODIFICADO CORRECTAMENTE---------------------");
							ret=0;
					   }
				}
		}
		else
		{
			printf("El Id no fue encontrado");
		}
	}
	return ret;
}



int emp_borrar(Dictionary* empleados)
{
	char cadenaIdABorrar[32];
	int ret=-1;
	if(utn_getTextoSoloNumeros("Ingrese id a borrar:","Error",cadenaIdABorrar,3,sizeof(cadenaIdABorrar))==0)
	{
		Empleado* pE;
		pE=dict_get(empleados,cadenaIdABorrar);
		if(pE!=NULL)
		{
			empleado_delete(pE);
			dict_remove(empleados, cadenaIdABorrar);
			ret=0;
		}
		else
		{
			printf("El Id no fue encontrado");
		}
	}
	return ret;
}


//*******************************************************************************************
int emp_imprimirLista(Dictionary* empleados)
{
	int ret=-1;
	int i;
	int flagError;
	LinkedList* listaEmpleados;
	Empleado* pE;
	// Obtengo empleados del diccionario e imprimo sus datos
	listaEmpleados=dict_getValues(empleados);
	for(i=0;i<ll_len(listaEmpleados);i++)
	{
		pE=(Empleado*)ll_get(listaEmpleados,i);
		printf("Id:[%d] Nombre:%s Apellido: %s Dni: %s\n",empleado_getId(pE,&flagError),empleado_getNombre(pE,&flagError),empleado_getApellido(pE, &flagError),empleado_getDni(pE,&flagError));
		ret=0;
	}
	ll_deleteLinkedList(listaEmpleados);
	return ret;
}


int emp_parser(char nombreArchivo[],Dictionary* empleados,int* pIdMaxEncontrado)
{
	FILE* pFile;
	char nombreAux[256];
	char apeAux[256];
	char dniAux[256];
	char idAux[256];
	int flagOnce=0;
	int idEmp;
	Empleado* pE;
	int indice=-1;
	int idMax;

	pFile = fopen(nombreArchivo,"r");
	if(pFile!=NULL)
	{
		indice=0;
		do
		{
			if(fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",nombreAux,apeAux,dniAux,idAux)==4)
			{
				if(flagOnce!=0)
				{
					//printf("%s %s %s %s\n",nombreAux,apeAux,dniAux,idAux);
					if(esNumerica(idAux)==0)
					{
						idEmp = atoi(idAux);
						pE = empleado_newParam(nombreAux,apeAux,dniAux,idEmp);
						// Guardo en diccionario el empleado construido
						if(pE!=NULL)
						dict_insert(empleados, idAux, pE);
						// busco maximo
						if(indice==0)
							idMax = idEmp; // me guardo el 1ero como MAX
						else
						{
							if(idEmp>idMax)
								idMax = idEmp;
						}
						indice++;
					}
				}
			}
			else
			{
			}
			flagOnce=1;
		}
		while(feof(pFile)==0 && indice<100);
		fclose(pFile);

		*pIdMaxEncontrado = idMax; // lo escribo en la var externa
	}

	return indice; // devuelve cantidad leidos
}

int emp_dump(char nombreArchivo[],Dictionary* empleados)
{
	// serializer
	FILE* pFile;
	LinkedList* listaEmpleados;
	Empleado* pE;
	int ret=-1;
	int len;
	int i;
	int flagError;
	char* pNombre;
	char* pApellido;
	char* pDni;
	int id;
	pFile = fopen(nombreArchivo,"w");
	if(pFile!=NULL)
	{
		fprintf(pFile,"Nombre,Apellido,DNI,idEmpleado\n");
		// Obtengo empleados del diccionario e imprimo sus datos
		listaEmpleados=dict_getValues(empleados);
		len=ll_len(listaEmpleados);
		//Escribo cada empleado en una linea del archivo
		for(i=0;i<len;i++)
		{
			pE=ll_get(listaEmpleados,i);
			if(pE!=NULL)
			{
				pNombre = empleado_getNombre(pE,&flagError);
				pApellido = empleado_getApellido(pE,&flagError);
				pDni = empleado_getDni(pE,&flagError);
				id = empleado_getId(pE,&flagError);
				fprintf(pFile,"%d,%s,%s,%s\n",id,pNombre,pApellido,pDni);
				ret=0;
			}
		}
		fclose(pFile);
	}
	return ret;
}





