

#include "sources_c_api.h"
#include "sources.h"
#include "utility.h"

#include "iostream"
#include "memory"


namespace {
    Sources sources;
}


void API_init_sources() {
    sources.init_sources();
}

void API_init_sources(std::string& jsonString, std::string& spectres){
    sources.init_sources(jsonString, spectres);
}

/*!
* функция возвращает наличие задержки
* \return наличие задержки
*/
int getLagState() {
    return (sources.getLagType() == lagType::DISABLED) ? 0 : 1;
}


int getInfluenceCount() {
    return sources.getInfluencesCount();
}

int getFortInflNumber(int particleNumber) {
    return sources.getInfluenceByParticleNumber(particleNumber)->influenceNumber;
}

double getFortAmplitude(int influenceNumber) {
    return sources.getInfluenceByInfluenceNumber(influenceNumber)->amplitude;
}


int getFortVolumeSpectre(int influenceNumber, int particleNumber, int layNumber){
    if (influenceNumber == 0) return -1;

    auto influence = sources.getInfluenceByInfluenceNumber(influenceNumber);

    for (auto it = influence->VolumeSources.cbegin(); it < influence->VolumeSources.cend(); it++) {

        if ((*it)->layerIndex == layNumber &&
            (*it)->particleIndex == particleNumber &&
            (*it)->sType == "Volume") {
            return sources.getSpectreNumber((*it)->spNames[0]);
        }
    }

    return -1;
}

int getFortVolume78Spectre(int influenceNumber, int particleNumber, int layNumber){
    if (influenceNumber == 0) return -1;

    auto influence = sources.getInfluenceByInfluenceNumber(influenceNumber);

    for (auto it = influence->Volume78Sources.cbegin(); it < influence->Volume78Sources.cend(); it++) {

        if ((*it)->layerIndex == layNumber &&
            (*it)->particleIndex == particleNumber &&
            (*it)->sType == "Volume78") {
            return sources.getSpectreNumber((*it)->spNames[0]);
        }
    }

    return -1;
}

int getFortVolume78Distribution(int influenceNumber, int particleNumber, int layNumber){
    if (influenceNumber == 0) return -1;

    auto influence = sources.getInfluenceByInfluenceNumber(influenceNumber);

    for (auto it = influence->Volume78Sources.cbegin(); it < influence->Volume78Sources.cend(); it++) {

        if ((*it)->layerIndex == layNumber &&
            (*it)->particleIndex == particleNumber &&
            (*it)->sType == "Volume78") {
            return sources.getSpectreNumber((*it)->spNames[0]);
        }
    }

    return -1;
}

int getFortBoundSpectre(int influenceNumber, int particleNumber, int direction){
    if (influenceNumber == 0) return -1;

    auto influence = sources.getInfluenceByInfluenceNumber(influenceNumber);

    for (auto it = influence->BoundariesSources.cbegin(); it < influence->BoundariesSources.cend(); it++) {

        if ((*it)->direction == direction &&
            (*it)->particleIndex == particleNumber &&
            (*it)->sType == "Boundaries") {
            return sources.getSpectreNumber((*it)->spNames[0]);
        }
    }

    return -1;
}

int getFortFluxSpectre(int influenceNumber, int particleNumber, int layNumberFrom, int layNumberTo, int direction){
    if (influenceNumber == 0) return -1;

    auto influence = sources.getInfluenceByInfluenceNumber((const int)influenceNumber);

    for (auto it = influence->SurfaceSources.cbegin(); it < influence->SurfaceSources.cend(); it++) {

        if ((*it)->layerIndexFrom == layNumberFrom &&
            (*it)->layerIndexTo == layNumberTo &&
            (*it)->particleIndex == particleNumber &&
            (*it)->sType == "Flux") {
            return sources.findFluxSpectre((*it)->direction, (*it)->spNames, direction);
        }
    }

    return -1;
}

/*!
* функция возвращает значение временной функции в заданный момент времени без учета задержки
* \param influenceNumber
* \param time
* \return значение временной функции
*/
double getCNoLagValue(int influenceNumber, double time)
{
    if (influenceNumber == 0) return -1;
    auto influence = sources.getInfluenceByInfluenceNumber((const int)influenceNumber);


    return interpolation(influence->tfTime, influence->tfValue, time) * influence->amplitude;
}

/*!
* функция возвращает значение временной функции в заданный момент времени с учетом задержки
* \param influenceNumber
* \param x
* \param y
* \param z
* \param time
* \return значение временной функции
*/
double getCLagValue(int influenceNumber, double x, double y, double z, double time)
{
    if (influenceNumber == 0) return -1;
    auto influence = sources.getInfluenceByInfluenceNumber((const int)influenceNumber);

    auto t = sources.time_lag(x, y, z, time);
    if (t < 0) return 0.0;
    return interpolation(influence->tfTime, influence->tfValue, t) * influence->amplitude;
}


std::string getSpectreName(int spectreIndex){
    return sources.getSpectreName(spectreIndex);
}
















