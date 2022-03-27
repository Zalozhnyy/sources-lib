//
// Created by nick on 27.03.2022.
//

#ifndef MAIN_PROJECT_FARADAY_DATATYPES_H
#define MAIN_PROJECT_FARADAY_DATATYPES_H

/*!
* \brief Структура для хранения данных сетки.
*/
typedef struct
{
    int nx;/*!< число разбиения по времени x. */
    int ny;/*!< число разбиения по времени y. */
    int nz;/*!< число разбиения по времени z. */
    int nt;/*!< число разбиения по времени. */
    double* xi;/*!< целая сетка по x. */
    double* xi05;/*!< полуцелая сетка по x. */
    double* dxi;/*!< целый шаг по x. */
    double* dxi05;/*!< полуцелый шаг по x. */
    double* yi;/*!< целая сетка по y. */
    double* yi05;/*!< полуцелая сетка по y. */
    double* dyi;/*!< целый шаг по y. */
    double* dyi05;/*!< полуцелый шаг по y. */
    double* zi;/*!< целая сетка по z. */
    double* zi05;/*!< полуцелая сетка по z. */
    double* dzi;/*!< целый шаг по z. */
    double* dzi05;/*!< полуцелый шаг по z. */
    double* ti;/*!< сетка по времени. */
} _grid;
/*! создание имени для ссылки*/
typedef _grid* grid;


#endif //MAIN_PROJECT_FARADAY_DATATYPES_H
