
#include "sources.h"
#include "sources_reader.h"
#include "sources_datatypes.h"
#include "utility.h"


#include "json/json.h"

#include <fstream>
#include <iostream>
#include "memory"
#include <cmath>
#include <stdexcept>
#include <algorithm>



void Sources::init_sources() {
    auto r = new SourceReader();

    r->startReadRempSourcesJson();
    r->readSpectresFile();

    m_influences = r->getInfluences();
    m_lag = r->getLag();
    m_marpleData = r->getMarpleData();
    m_specters = r->getSpecters();

    if (m_lag->type == lagType::PLANE) {
        auto grd = r->getGrd();
        ptsX = GridData::getAxePoints(grd.axes[0]);;
        ptsY = GridData::getAxePoints(grd.axes[1]);;
        ptsZ = GridData::getAxePoints(grd.axes[2]);;
        calcPlaneLagParameters();
    }

    createPartInfluenceMap();


    delete r;
}

void Sources::createPartInfluenceMap() {

    for (auto& influence: m_influences) {

        m_InflNumber_InfluenceMap[influence->influenceNumber] = influence;

        for (auto source: influence->VolumeSources)
            m_partInfluenceMap[source->particleIndex] = influence;

        for (auto source: influence->Volume78Sources)
            m_partInfluenceMap[source->particleIndex] = influence;

        for (auto source: influence->SurfaceSources)
            m_partInfluenceMap[source->particleIndex] = influence;

        for (auto source:influence->BoundariesSources)
            m_partInfluenceMap[source->particleIndex] = influence;

    }

}

void Sources::calcPlaneLagParameters() {
    if (m_lag->type == lagType::PLANE) {
        double n1, n2, n3, n;

        n1 = m_lag->param[0]; // направление распространения фронта
        n2 = m_lag->param[1];
        n3 = m_lag->param[2];
        n = sqrt(n1 * n1 + n2 * n2 + n3 * n3);
        if (n < 1.e-5) {
            fprintf(stderr, "Source front direction vector must be non-zero, it is (%e, %e, %e)\n", n1, n2, n3);
            exit(1);
        }
        m_lag->param[0] = n1 / n;
        m_lag->param[1] = n2 / n;
        m_lag->param[2] = n3 / n;

        // точка расчетной области, первой попадающаяся на пути плоского фронта
        // какой-то из углов
        m_lag->plane_param[0] = n1 > 0 ? ptsX[0] : ptsX[ptsX.size() - 1];
        m_lag->plane_param[1] = n2 > 0 ? ptsY[0] : ptsY[ptsY.size() - 1];
        m_lag->plane_param[2] = n3 > 0 ? ptsZ[0] : ptsZ[ptsZ.size() - 1];
    }
}


std::shared_ptr<Influence> Sources::getInfluenceByParticleNumber(int particleNumber) {

    if (m_partInfluenceMap.count(particleNumber)) {
        return m_partInfluenceMap[particleNumber];
    } else {
        return nullptr;
    }
}

std::shared_ptr<Influence> Sources::getInfluenceByInfluenceNumber(int influenceNumber) {
    if (m_InflNumber_InfluenceMap[influenceNumber]) {
        return m_InflNumber_InfluenceMap[influenceNumber];
    } else {
        return nullptr;
    }
}

std::vector<int> Sources::getInfluenceNumbers() {
    std::vector<int> numbers;

    for (auto it = m_InflNumber_InfluenceMap.cbegin(); it != m_InflNumber_InfluenceMap.cend(); it++) {
        numbers.push_back(it->first);
    }


    return numbers;
}

int Sources::getSpectreNumber(std::string& spectreName) {

    if (m_specters.count(spectreName))
    {
        return m_specters[spectreName];
    }

    else
    {
        throw std::invalid_argument("unknown spectre name");
    }

}

/*!
* \brief функция проверяет тип спектра и ищет один из заданных спектров с нужным направлением.
* \param spNames - имена спектров.
* \param direction - направление.
* \return индекс спектра в массиве spectres
*/
int Sources::findFluxSpectre(const std::vector<int>& directions, const std::vector<std::string>& spNames, int direction)
{
    if (directions.size() == 1 && directions[0] == -1) { // не .spc спектр
        auto sp = spNames[0];
        return getSpectreNumber(sp);
    }

    auto it = std::find(directions.begin(), directions.end(), direction);

    if (it != directions.end()) {
        auto index = std::distance(directions.begin(), it);

        auto sp = spNames[0];
        return getSpectreNumber(sp);
    }

    return -1;
}



