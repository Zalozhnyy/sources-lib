
#ifndef R_SOURCES_H
#define R_SOURCES_H


#include "sources_datatypes.h"
#include "faraday_datatypes.h"

#include "map"
#include "unordered_map"
#include "unordered_set"
#include "memory"
#include "vector"

#include "json/json.h"



class Sources
{
public:

    void init_sources();

    std::shared_ptr<Influence> getInfluenceByParticleNumber(int particleNumber);
    std::shared_ptr<Influence> getInfluenceByInfluenceNumber(int influenceNumber);
    std::vector<int> getInfluenceNumbers();


    int getInfluencesCount() {return (int)m_influences.size();}


    std::shared_ptr<Lag> m_lag;


private:

    std::shared_ptr<MarpleData> m_marpleData;
    std::unordered_map<std::string, int> m_specters;
    std::vector<std::shared_ptr<Influence>> m_influences;


    std::map<int, std::shared_ptr<Influence>> m_partInfluenceMap;
    std::map<int, std::shared_ptr<Influence>> m_InflNumber_InfluenceMap;

    std::vector<double> ptsX;
    std::vector<double> ptsY;
    std::vector<double> ptsZ;


    void createPartInfluenceMap();

    void calcPlaneLagParameters();

};

#endif //R_SOURCES_H