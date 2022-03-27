
#include "sources.h"
#include "sources_reader.h"
#include "sources_datatypes.h"
#include "utility.h"


#include "json/json.h"

#include <fstream>
#include <iostream>
#include "memory"
#include "math.h"


void Sources::init_sources(){
    auto r = new SourceReader();

    r->startReadRempSourcesJson();
    r->readSpectresFile();

    m_influences = r->getInfluences();
    m_lag = r->getLag();
    m_marpleData = r->getMarpleData();
    m_specters = r->getSpecters();

    std::cout << m_influences[0].use_count() << std::endl;
    delete r;
    std::cout << m_influences[0].use_count() << std::endl;

    createPartInfluenceMap();

    std::cout << m_influences[0].use_count() << std::endl;


    std::cout << "end" << std::endl;

}

void Sources::createPartInfluenceMap() {

    for (auto &m_influence: m_influences) {

        for (auto source:
                m_influence->VolumeSources)
            m_partInfluenceMap[source->particleIndex] = m_influence;
        for (auto source:
                m_influence->Volume78Sources)
            m_partInfluenceMap[source->particleIndex] = m_influence;
        for (auto source:
                m_influence->SurfaceSources)
            m_partInfluenceMap[source->particleIndex] = m_influence;
        for (auto source:
                m_influence->BoundariesSources)
            m_partInfluenceMap[source->particleIndex] = m_influence;

    }

}

void Sources::calcPlaneLagParameters(const grid& _grd) {
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
        m_lag->plane_param[0] = n1 > 0 ? _grd->xi[0] : _grd->xi[_grd->nx];
        m_lag->plane_param[1] = n2 > 0 ? _grd->yi[0] : _grd->yi[_grd->ny];
        m_lag->plane_param[2] = n3 > 0 ? _grd->zi[0] : _grd->zi[_grd->nz];
    }
}


