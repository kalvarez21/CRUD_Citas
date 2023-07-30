#pragma once
#ifndef CRUD_CITAS_H
#define CRUD_CITAS_H
#include <vector>

namespace Estructura{
    struct Cita {
        int CitCod;
        int MedCod;
        int HorCod;
        int PacCod;
        int FecDia, FecMes, FecAgno;

        Cita() = default;
    };
}


std::vector<Estructura::Cita> Leer();
void Crear(int cod, int med, int hor, int pac, int dia, int mes, int agno);
void Actualizar(int id, int med, int hor, int pac, int dia, int mes, int agno);
void Borrar(int id);
void imprimirVector(std::vector<Estructura::Cita>);

#endif // CRUD_CITAS_H