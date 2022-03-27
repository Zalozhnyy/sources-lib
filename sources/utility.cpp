

#include "utility.h"
#include "json/json.h"

#include <vector>
#include <algorithm>


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

