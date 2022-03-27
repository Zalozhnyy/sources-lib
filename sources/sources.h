
#ifndef R_SOURCES_H
#define R_SOURCES_H


#include "sources_datatypes.h"
#include "faraday_datatypes.h"

#include "map"
#include "unordered_map"
#include "unordered_set"
#include "memory"

#include "json/json.h"



class Sources
{
public:

    void init_sources();

private:

    std::vector<std::shared_ptr<Influence>> m_influences;
    std::shared_ptr<Lag> m_lag;
    std::shared_ptr<MarpleData> m_marpleData;
    std::unordered_map<std::string, int> m_specters;

    std::map<int, std::shared_ptr<Influence>> m_partInfluenceMap;


    void createPartInfluenceMap();

    void calcPlaneLagParameters(const grid& _grd);
};

#endif //R_SOURCES_H