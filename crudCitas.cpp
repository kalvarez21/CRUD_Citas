#include "crudCitasInterface.h"
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;
//archivo exclusivo para Pacientes en archivo.dat
const char* nombre_archivo = "listaCita.dat";


//La funcion Leer() devuevel un vector<Cita> de las citas que hay en
//el fichero de listaCita
std::vector<Estructura::Cita> Leer() {
	//FILE es un tipo de estructura de la biblioteca estandar
	//Soporta funciones de fopen,fwrite,fread,fclose
	FILE* archivo = fopen(nombre_archivo, "rb");
	if (!archivo) {
		cout << "No existe tal archivo" << endl;
	}
	std::vector<Estructura::Cita> citas;
	Estructura::Cita cita;
	// indice o pocision del registro(fila) dentro del archivo
	//Almaceno en cita, el dato  que se lee desde archivo
	while (fread(&cita, sizeof(Estructura::Cita), 1, archivo) == 1) {
		citas.push_back(cita);
	}
	fclose(archivo);
	return citas;
}

void Crear(int cod, int med, int hor, int pac, int dia, int mes, int agno) {

	FILE* archivo = fopen(nombre_archivo, "a+b");
	char res;
	Estructura::Cita cita;
	fflush(stdin);//limpia buffer de entrada y salida
	cita.CitCod = cod;
	cita.MedCod = med;
	cita.HorCod = hor;
	cita.PacCod = pac;
	cita.FecDia = dia;
	cita.FecMes = mes;
	cita.FecAgno = agno;
	fwrite(&cita, sizeof(Estructura::Cita), 1, archivo);
	fclose(archivo);
}
/*Los registros tienen que coincidir su numero de registro con el numero de id*/
void Actualizar(int id, int med, int hor, int pac, int dia, int mes, int agno) {

	id--;//Cuento desde 0
	FILE* archivo = fopen(nombre_archivo, "r+b");
	Estructura::Cita cita;
	//Los id tienen que ser secuenciales
	//Me ubico en el id correcto
	fseek(archivo, id * sizeof(Estructura::Cita), SEEK_SET);
	cita.CitCod = ++id;
	cita.MedCod = med;
	cita.HorCod = hor;
	cita.PacCod = pac;
	cita.FecDia = dia;
	cita.FecMes = mes;
	cita.FecAgno = agno;
	fwrite(&cita, sizeof(Estructura::Cita), 1, archivo);
	fclose(archivo);
	Leer();
}

void Borrar(int id) {
	const char* nombre_archivo_temp = "archivo_temp.dat";
	FILE* archivo_temp = fopen(nombre_archivo_temp, "w+b");
	FILE* archivo = fopen(nombre_archivo, "rb");
	Estructura::Cita cita;
	int id_n = 0;
	//Escribo en un archivo temporal los que no coinciden con el indice
	id--;
	while (fread(&cita, sizeof(Estructura::Cita), 1, archivo)) {
		if (id_n != id) {
			fwrite(&cita, sizeof(Estructura::Cita), 1, archivo_temp);
		}
		id_n++;
	}
	fclose(archivo);
	fclose(archivo_temp);

	archivo_temp = fopen(nombre_archivo_temp, "rb");
	archivo = fopen(nombre_archivo, "wb");
	//Regreso todos los registros en archivo_temp a archivo
	while (fread(&cita, sizeof(Estructura::Cita), 1, archivo_temp)) {
		fwrite(&cita, sizeof(Estructura::Cita), 1, archivo);

	}
	fclose(archivo);
	fclose(archivo_temp);
	Leer();
}

/*


   Otros ejemplos para busqueda por medio de PacCod indice etc


*/
Cita buscar_CitCod(int cod) {
	FILE* archivo = fopen(nombre_archivo, "rb");
	Estructura::Cita cita;
	fread(&cita, sizeof(Estructura::Cita), 1, archivo);
	do {
		if (cita.CitCod == cod) {
			break;
		}
		fread(&cita, sizeof(Estructura::Cita), 1, archivo);
	} while (feof(archivo) == 0);
	fclose(archivo);
	return cita;
}
/*
void buscar_indice() {
	FILE* archivo = fopen(nombre_archivo, "rb");

	int pos = 0;
	cout << "Que registro desea ver: ";
	cin >> pos;
	cout << "------------------ " << pos << " ------------------" << endl;
	fseek(archivo, pos * sizeof(Estructura::Paciente), SEEK_SET);

	Estructura::Paciente paciente;

	fread(&paciente, sizeof(Estructura::Paciente), 1, archivo);

	cout << "PacCod: " << paciente.PacCod << endl;
	cout << "Nombre: " << paciente.nombres << endl;
	cout << "Apellido: " << paciente.apellidos << endl;
	cout << "Telefono: " << paciente.telefono << endl;
	cout << endl;

	fclose(archivo);


}
*/
void imprimirVector(vector<Estructura::Cita> datos) {
	cout << "mostrando todos los registros de citas actuales: " << endl;
	cout << "tamagno " << datos.size() << endl;
	for (Estructura::Cita dato : datos) {
		cout << dato.CitCod << "," << dato.MedCod <<
			"," << dato.HorCod << "..." << endl;
	}
}