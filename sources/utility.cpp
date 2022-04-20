

#include "utility.h"
#include "json/json.h"

#include <vector>
#include <algorithm>
#include <functional>


/*!
* Функция проверяет версию файла источников и кидает ошибку при её несоответствии.
* \param root - Считанный json файл
* \return void
*/
void check_sources_version(Json::Value& root)
{
    float version;

    version = root.get("Version", 0.0).asFloat();

    if (version < SOURCES_VERSION) {
        char s[255];

        sprintf(s, "Found old remp_sources.json version. Actual version is %3.2f .", SOURCES_VERSION);
        //print_log_message(s);

        fprintf(stderr, "Found old remp_sources.json version. Actual version is %3.2f", SOURCES_VERSION);
        exit(1);

    }
}

template <typename T>
std::vector<T> convertVectorDtype(const std::vector<std::string>& arr) {  // шаблон конвертации массива строк в нужный тип данных
    std::vector<T> out;

    if (!arr.empty()) {
        out.reserve(arr.size());
        for (auto& it : arr) {
            out.push_back(it);
        }
    }

    return out;
}

template <>
std::vector<int> convertVectorDtype(const std::vector<std::string>& arr) {  // шаблон конвертации массива строк в нужный тип данных для int
    std::vector<int> out;

    if (!arr.empty()) {
        out.reserve(arr.size());
        for (auto& it : arr) {
            out.push_back(std::stoi(it));
        }
    }

    return out;
}

template <>
std::vector<double> convertVectorDtype(const std::vector<std::string>& arr) {  // шаблон конвертации массива строк в нужный тип данных для double
    std::vector<double> out;

    if (!arr.empty()) {
        out.reserve(arr.size());
        for (auto& it : arr) {
            out.push_back(std::stod(it));
        }
    }

    return out;
}

/*!
* Функция удаления символов новой строки и возврата каретки из строки.
* \param str - строка.
*/
void removeEOL(std::string& str)
{
    str.erase(std::remove(str.begin(), str.end(), '\r'), str.end());
    str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
}

/*!
* Функция разбиения строки на массив.
* \param str - строка для разбиения.
* \return массив строк
*/
std::vector<std::string> stringToVector(std::string str) { // split строки
    std::vector<std::string> out;

    std::istringstream f(str);
    std::string s;
    while (getline(f, s, ' ')) {
        out.push_back(s);
    }
    return out;
}


/*!
* Функция интерполяции временной функции.
* \param time_vec - массив времён
* \param e_min_vec - массив значений временной функции
* \param time - значение времени, в котором необходимо получить временную функцию
* \return значение временной функции при заданном времени
*/
double interpolation(std::vector<double>& time_vec, std::vector<double>& e_min_vec, double time)
{
    if (time_vec.empty()) {
        return 0.0;
    }

    size_t first = 0;
    size_t last = time_vec.size() - 1;
    size_t med;
    double kof, val = 0.0;
    double e_min;

    e_min = e_min_vec[0];

    if (time >= time_vec[last]) {
        e_min = e_min_vec[last];
    } else if (time <= time_vec[first]) {
        e_min = e_min_vec[first];
    } else {
        while ((last - first) > 1) {
            med = (last - first) / 2 + first;

            if (time <= time_vec[med]) {
                last = med;
            } else {
                first = med;
            }
        }

        kof = (time - time_vec[first]) / (time_vec[last] - time_vec[first]);
        e_min = (e_min_vec[last] - e_min_vec[first]) * kof + e_min_vec[first];
    }
    return e_min;
}

