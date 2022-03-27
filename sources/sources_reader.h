//
// Created by nick on 26.03.2022.
//

#ifndef MAIN_PROJECT_SOURCES_READER_H
#define MAIN_PROJECT_SOURCES_READER_H

#include "sources_datatypes.h"

#include "json/json.h"

#include "vector"
#include "memory"
#include "iostream"
#include "unordered_map"


class SourceReader {
public:
    ~SourceReader() {
        std::cout << "SourceReader deleted" << std::endl;
    }

    SourceReader() {
    }

    void startReadRempSourcesJson();
    void readSpectresFile();


    std::vector<std::shared_ptr<Influence>> getInfluences();

    std::shared_ptr<Lag> getLag();

    std::shared_ptr<MarpleData> getMarpleData();
    std::unordered_map<std::string, int> getSpecters();


private:

    std::vector<std::shared_ptr<Influence>> m_influences;
    std::shared_ptr<Lag> m_lag = std::make_shared<Lag>();
    std::shared_ptr<MarpleData> m_marpleData = std::make_shared<MarpleData>();
    std::unordered_map<std::string, int> m_spectres;


    void readInfluence(const Json::Value::const_iterator &influence, Influence &influenceStruct);

    void readBoundSource(const Json::Value::const_iterator &surfSource, BoundariesSource &s);

    void readVolumeSource(const Json::Value::const_iterator &volSource, VolumeSource &s);

    void readSurfaceSource(const Json::Value::const_iterator &surfSource, SurfaceSource &s);

    void readDistributionSource(const Json::Value::const_iterator &sigmaSource, Distribution &s);

    void readVolume78Source(const Json::Value::const_iterator &volSource, Volume78Source &s);

    void readSources(const Json::Value::const_iterator &sourceTypes, Influence &influenceStruct);

    void startReadLag(const Json::Value::const_iterator &lagSource);

};


#endif //MAIN_PROJECT_SOURCES_READER_H
