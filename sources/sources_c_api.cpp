

#include "sources_c_api.h"
#include "sources.h"

#include "iostream"
#include "memory"


namespace {
    std::shared_ptr<Sources> sources;
}


void init_sources() {
    sources->init_sources();
}

/*!
* функция возвращает наличие задержки
* \return наличие задержки
*/
int getLagState() {
    return (sources->getLagType() == lagType::DISABLED) ? 0 : 1;
}


int getInfluenceCount() {
    return sources->getInfluencesCount();
}

int getFortInflNumber(int particleNumber) {
    return sources->getInfluenceByParticleNumber(particleNumber)->influenceNumber;
}

double getFortAmplitude(int influenceNumber) {
    return sources->getInfluenceByInfluenceNumber(influenceNumber)->amplitude;
}


int getFortVolumeSpectre(int influenceNumber, int particleNumber, int layNumber){
    if (influenceNumber == 0) return -1;

    auto influence = sources->getInfluenceByInfluenceNumber(influenceNumber);

    for (auto it = influence->VolumeSources.cbegin(); it < influence->VolumeSources.cend(); it++) {

        if ((*it)->layerIndex == layNumber &&
            (*it)->particleIndex == particleNumber &&
            (*it)->sourceName == "Volume") {
            return sources->getSpectreNumber((*it)->spNames[0]);
        }
    }

    return -1;
}

int getFortVolume78Spectre(int influenceNumber, int particleNumber, int layNumber){
    if (influenceNumber == 0) return -1;

    auto influence = sources->getInfluenceByInfluenceNumber(influenceNumber);

    for (auto it = influence->Volume78Sources.cbegin(); it < influence->Volume78Sources.cend(); it++) {

        if ((*it)->layerIndex == layNumber &&
            (*it)->particleIndex == particleNumber &&
            (*it)->sourceName == "Volume78") {
            return sources->getSpectreNumber((*it)->spNames[0]);
        }
    }

    return -1;
}

int getFortVolume78Distribution(int influenceNumber, int particleNumber, int layNumber){
    if (influenceNumber == 0) return -1;

    auto influence = sources->getInfluenceByInfluenceNumber(influenceNumber);

    for (auto it = influence->Volume78Sources.cbegin(); it < influence->Volume78Sources.cend(); it++) {

        if ((*it)->layerIndex == layNumber &&
            (*it)->particleIndex == particleNumber &&
            (*it)->sourceName == "Volume78") {
            return sources->getSpectreNumber((*it)->spNames[0]);
        }
    }

    return -1;
}

int getFortBoundSpectre(int influenceNumber, int particleNumber, int direction){
    if (influenceNumber == 0) return -1;

    auto influence = sources->getInfluenceByInfluenceNumber(influenceNumber);

    for (auto it = influence->BoundariesSources.cbegin(); it < influence->BoundariesSources.cend(); it++) {

        if ((*it)->direction == direction &&
            (*it)->particleIndex == particleNumber &&
            (*it)->sourceName == "Boundaries") {
            return sources->getSpectreNumber((*it)->spNames[0]);
        }
    }

    return -1;
}

int getFortFluxSpectre(int influenceNumber, int particleNumber, int layNumberFrom, int layNumberTo, int direction){
    if (influenceNumber == 0) return -1;

    auto influence = sources->getInfluenceByInfluenceNumber(influenceNumber);

    for (auto it = influence->SurfaceSources.cbegin(); it < influence->SurfaceSources.cend(); it++) {

        if ((*it)->layerIndexFrom == layNumberFrom &&
            (*it)->layerIndexTo == layNumberTo &&
            (*it)->particleIndex == particleNumber &&
            (*it)->sourceName == "Boundaries") {
            return sources->findFluxSpectre((*it)->direction, (*it)->spNames, direction);
        }
    }

    return -1;
}















