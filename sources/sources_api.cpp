

#include "sources_api.h"
#include "sources.h"

#include "iostream"
#include "memory"

#ifdef __cplusplus

namespace SourcesAPI {
    std::shared_ptr<Sources> sources;

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


    void init_sources() {
        sources = std::make_shared<Sources>();
        sources->init_sources();
    }

    int getInfluenceNumber(int particleNumber) {
        auto inflNumber = sources->getInfluenceByParticleNumber(particleNumber);

        if (inflNumber == nullptr){
            //TODO LOG EXCEPTION
            return -1;
        }
        return inflNumber->influenceNumber;
    }

    double getAmplitude(int influenceNumber){
        if (influenceNumber == 0) return 0.0;

        auto infl = sources->getInfluenceByInfluenceNumber(influenceNumber);

        if (infl == nullptr){
            //TODO LOG EXCEPTION
            return 0.0;
        }

        return infl->amplitude;
    }

}

#endif

void init_sources(){
    SourcesAPI::init_sources();
}

/*!
* Функция возвращает номер воздействия, где есть данный номер частицы. Для частиц 78 может работать некорректно
* \param particleNumber - номер частицы.
* \return номер воздействия
*/
int getInfluenceNumber(int particleNumber) {
    return SourcesAPI::getInfluenceNumber(particleNumber);
}

/*!
* функция возвращает амплитуду воздействия
* \param influenceNumber номер воздействия
* \return амплитуда
*/
double getAmplitude(int influenceNumber){
    return SourcesAPI::getAmplitude(influenceNumber);
}

/*!
* функция возвращает наличие задержки
* \return наличие задержки
*/
int getLagState()
{
    return (SourcesAPI::sources->m_lag->type == lagType::DISABLED) ? 0 : 1;
}

/*!
* функция возвращает количество воздействий
* \return количество воздействий
*/
int getInfluenceCount()
{
    return (int)SourcesAPI::sources->getInfluenceSize();
}

/*!
* функция возвращает значение временной функции в заданный момент времени без учета задержки
* \param inflIndex
* \param time
* \return значение временной функции
*/
double getCNoLagValue(int inflIndex, double time){
    return SourcesAPI::interpolation(
            SourcesAPI::sources->getInfluenceByInfluenceNumber(inflIndex)->tfTime,
            SourcesAPI::sources->getInfluenceByInfluenceNumber(inflIndex)->tfValue,
            time
            );
}








