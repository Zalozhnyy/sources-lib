

#include "sources_api.h"
#include "sources.h"

#include "iostream"

#ifdef __cplusplus

namespace SourcesAPI {
    Sources* sources = nullptr;

    void init_sources() {
        sources = new Sources();
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






