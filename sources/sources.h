
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
#include "sources_reader.h"


class Sources
{
public:

    void init_sources();
    void init_sources(std::string& jsonString, std::string& spectres);

    std::shared_ptr<Influence> getInfluenceByParticleNumber(int particleNumber);
    std::shared_ptr<Influence> getInfluenceByInfluenceNumber(int influenceNumber);
    std::vector<int> getInfluenceNumbers();

    int getSpectreNumber(std::string& spectreName);
    std::string getSpectreName(int spectreNumber);
    int findFluxSpectre(const std::vector<int>& directions, const std::vector<std::string>& spNames, int direction);

    lagType getLagType() {return m_lag->type;}

    int getInfluencesCount() {return (int)m_influences.size();}

    double time_lag(double x, double y, double z, double t);



private:

    std::shared_ptr<MarpleData> m_marpleData;
    std::vector<std::shared_ptr<Influence>> m_influences;
    std::unordered_map<std::string, int> m_specters;
    std::shared_ptr<Lag> m_lag = std::make_shared<Lag>();



    std::map<int, std::shared_ptr<Influence>> m_partInfluenceMap;
    std::map<int, std::shared_ptr<Influence>> m_InflNumber_InfluenceMap;

    std::vector<double> ptsX;
    std::vector<double> ptsY;
    std::vector<double> ptsZ;


    void createPartInfluenceMap();

    void calcPlaneLagParameters();


    SourceReader initReader();
    SourceReader initReader(std::string& jsonString, std::string& spectres);
    void initLag(SourceReader& r);


    };

#endif //R_SOURCES_H