#ifndef SOURCES_UTILITY_H
#define SOURCES_UTILITY_H

#include <vector>
#include <string>
#include <iostream>
#include <sstream>

#include "json/json.h"

#define _cl 2.99792458E+10 /*!< скорость света [см/с]. */


const float SOURCES_VERSION = 1.0; /*!< необходимая версия файла remp_sources.json */

void check_sources_version(Json::Value& root);


template <typename T>
std::vector<T> convertVectorDtype(const std::vector<std::string>& arr);

template <>
std::vector<int> convertVectorDtype(const std::vector<std::string>& arr);

template <>
std::vector<double> convertVectorDtype(const std::vector<std::string>& arr);

std::vector<std::string> stringToVector(std::string str);
void removeEOL(std::string& str);

double interpolation(std::vector<double>& time_vec, std::vector<double>& e_min_vec, double time);

#endif //SOURCES_UTILITY_H