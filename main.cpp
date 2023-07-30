#include <iostream>
#include "crudCitasInterface.h"
using namespace std;


int main() {
	vector <Estructura::Cita> citas;
	citas = Leer();
	imprimirVector(citas);
	//CrearConsola();//Para pruebas en consola
	Crear(1,1,1,1,30,7,2023);
	Crear(2,2,2,2,30,7,2023);
	Crear(3,3,3,3,30,7,2023);
	cout<<"Se termino de ingresar"<<endl;
	citas = Leer();
	imprimirVector(citas);
	Actualizar(2,4,4,4,1,8,2023);
	citas=Leer();
	imprimirVector(citas);
	Borrar(2);
	citas=Leer();
	imprimirVector(citas);
	return 0;
}
