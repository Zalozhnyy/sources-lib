//
// Created by nick on 26.03.2022.
//

#include "sources_reader.h"
#include "sources_datatypes.h"
#include "utility.h"

#include "json/json.h"

#include <fstream>



/*!
* функциия заполнения Энерговыделения воздействия
* \param sigmaSource - Итератор.
* \param s - ссылка структуру источника.
*/
void SourceReader::readDistributionSource(const Json::Value::const_iterator &sigmaSource, Distribution& s)
{
    std::string typeBuff, spBuff;
    int layerIndexBuff = -1;

    for (auto sigma = (*sigmaSource).begin(); sigma != (*sigmaSource).end(); ++sigma) {
        if (sigma.key() == "Type")              typeBuff = sigma->asString();
        if (sigma.key() == "Layer index")       layerIndexBuff = sigma->asInt();
        if (sigma.key() == "Distribution")      spBuff = sigma->asString();
    }

    s.sType = typeBuff;
    s.layerIndex = layerIndexBuff;
    s.spNames = stringToVector(spBuff);
}

/*!
* функциия заполнения поверхностного источника
* \param surfSource - Итератор.
* \param s - ссылка структуру источника.
*/
void SourceReader::readSurfaceSource(const Json::Value::const_iterator &surfSource, SurfaceSource& s)
{
    std::string typeBuff, spBuff, spNumberBuff, spDirectionBuff;
    int particleIndexBuff = -1, layerIndexFromBuff = -1, layerIndexToBuff = -1;

    for (auto surface = (*surfSource).begin(); surface != (*surfSource).end(); ++surface) {
        if (surface.key() == "Type")                typeBuff = surface->asString();
        if (surface.key() == "Layer index from")    layerIndexFromBuff = surface->asInt();
        if (surface.key() == "Layer index to")      layerIndexToBuff = surface->asInt();
        if (surface.key() == "Particle index")      particleIndexBuff = surface->asInt();
        if (surface.key() == "Spectre")             spBuff = surface->asString();
        if (surface.key() == "Spectre number")      spNumberBuff = surface->asString();
        if (surface.key() == "Direction")           spDirectionBuff = surface->asString();
    }

    s.layerIndexFrom = layerIndexFromBuff;
    s.layerIndexTo = layerIndexToBuff;
    s.particleIndex = particleIndexBuff;
    s.sType = typeBuff;
    s.spNames = stringToVector(spBuff);
    s.spNumbers = convertVectorDtype<int>(stringToVector(spNumberBuff));
    s.direction = convertVectorDtype<int>(stringToVector(spDirectionBuff));
}

/*!
* функциия заполнения граничного источника
* \param surfSource - Итератор.
* \param s - ссылка структуру источника.
*/
void SourceReader::readBoundSource(const Json::Value::const_iterator &surfSource, BoundariesSource& s)
{
    std::string typeBuff, spBuff, spNumberBuff;
    int particleIndexBuff = -1;
    int directionBuff = -1;

    for (auto bound = surfSource->begin(); bound != surfSource->end(); ++bound) {
        if (bound.key() == "Type")              typeBuff = bound->asString();
        if (bound.key() == "Particle index")    particleIndexBuff = bound->asInt();
        if (bound.key() == "Direction")         directionBuff = bound->asInt();
        if (bound.key() == "Spectre")           spBuff = bound->asString();
        if (bound.key() == "Spectre number")    spNumberBuff = bound->asString();
    }

    s.particleIndex = particleIndexBuff;
    s.sType = typeBuff;
    s.direction = directionBuff;
    s.spNames = stringToVector(spBuff);
    s.spNumbers = convertVectorDtype<int>(stringToVector(spNumberBuff));
}

/*!
* функция заполняет структуру Lag
* \param lagSource - итератор.
* \param lag - ссылка структуру задержки.
*/
void SourceReader::startReadLag(const Json::Value::const_iterator &lagSource)
{
    for (auto l = lagSource->begin(); l != lagSource->end(); ++l) {
        if (l.key() == "Type") {
            int type = l->asInt();
            switch (type)
            {
                case 0:
                    m_lag->type = lagType::DISABLED;
                    break;
                case 1:
                    m_lag->type = lagType::PLANE;
                    break;
                case 2:
                    m_lag->type = lagType::SPHERE;
                    break;
            }
        }
        if (l.key() == "X") m_lag->param[0] = l->asDouble();
        if (l.key() == "Y") m_lag->param[1] = l->asDouble();
        if (l.key() == "Z") m_lag->param[2] = l->asDouble();
    }
}

/*!
* функциия заполнения обхёмного источника
* \param volSource - Итератор.
* \param s - ссылка структуру источника.
*/
void SourceReader::readVolumeSource(const Json::Value::const_iterator &volSource, VolumeSource& s)
{
    std::string typeBuff, spBuff, spNumberBuff;
    int particleIndexBuff = -1;
    int layerIndexBuff = -1;

    for (auto volume = volSource->begin(); volume != volSource->end(); ++volume) {
        if (volume.key() == "Type")             typeBuff = volume->asString();
        if (volume.key() == "Layer index")      layerIndexBuff = volume->asInt();
        if (volume.key() == "Particle index")   particleIndexBuff = volume->asInt();
        if (volume.key() == "Spectre")          spBuff = volume->asString();
        if (volume.key() == "Spectre number")   spNumberBuff = volume->asString();
    }

    s.layerIndex = layerIndexBuff;
    s.particleIndex = particleIndexBuff;
    s.sType = typeBuff;
    s.spNames = stringToVector(spBuff);
    s.spNumbers = convertVectorDtype<int>(stringToVector(spNumberBuff));
}

/*!
* функциия заполнения обхёмного источника 78
* \param volSource - Итератор.
* \param s - ссылка структуру источника.
*/
void SourceReader::readVolume78Source(const Json::Value::const_iterator &volSource, Volume78Source& s) {
    std::string typeBuff, spBuff, spNumberBuff, distrubutionBuff;
    int particleIndexBuff = -1;
    int layerIndexBuff = -1;

    for (auto volume = volSource->begin(); volume != volSource->end(); ++volume) {
        if (volume.key() == "Type")             typeBuff = volume->asString();
        if (volume.key() == "Layer index")      layerIndexBuff = volume->asInt();
        if (volume.key() == "Particle index")   particleIndexBuff = volume->asInt();
        if (volume.key() == "Spectre")          spBuff = volume->asString();
        if (volume.key() == "Spectre number")   spNumberBuff = volume->asString();
        if (volume.key() == "Distribution")     distrubutionBuff = volume->asString();
    }

    s.layerIndex = layerIndexBuff;
    s.particleIndex = particleIndexBuff;
    s.sType = typeBuff;
    s.spNames = stringToVector(spBuff);
    s.spNumbers = convertVectorDtype<int>(stringToVector(spNumberBuff));
    s.distributionFileName = distrubutionBuff;
}

/*!
* функция, разделяющая потоки чтения разных источников
* \param influence - Итератор.
* \param influenceStruct - ссылка на массив структур воздействий.
*/
void SourceReader::readSources(const Json::Value::const_iterator &sourceTypes, Influence& influenceStruct)
{
    for (auto sType = sourceTypes->begin(); sType != sourceTypes->end(); ++sType) {

        if (sType.key() == "Currents") {
            for (auto s = (*sType).begin(); s != (*sType).end(); ++s) {
                Distribution* r = new Distribution(s.key().asString());
                readDistributionSource(s, *r);
                influenceStruct.Distributions.push_back(r);
            }
        }

        if (sType.key() == "Sigmas") {
            for (auto s = (*sType).begin(); s != (*sType).end(); ++s) {
                Distribution* r = new Distribution(s.key().asString());
                readDistributionSource(s, *r);
                influenceStruct.Distributions.push_back(r);
            }
        }

        if (sType.key() == "Surface") {
            for (auto s = (*sType).begin(); s != (*sType).end(); ++s) {
                SurfaceSource* r = new SurfaceSource(s.key().asString());
                readSurfaceSource(s, *r);
                influenceStruct.SurfaceSources.push_back(r);
            }
        }

        if (sType.key() == "Volume") {
            for (auto s = (*sType).begin(); s != (*sType).end(); ++s) {
                VolumeSource* r = new VolumeSource(s.key().asString());
                readVolumeSource(s, *r);
                influenceStruct.VolumeSources.push_back(r);
            }
        }

        if (sType.key() == "Volume78") {
            for (auto s = (*sType).begin(); s != (*sType).end(); ++s) {
                Volume78Source* r = new Volume78Source(s.key().asString());
                readVolume78Source(s, *r);
                influenceStruct.Volume78Sources.push_back(r);
            }
        }

        if (sType.key() == "From boundaries") {
            for (auto s = (*sType).begin(); s != (*sType).end(); ++s) {
                BoundariesSource* r = new BoundariesSource(s.key().asString());
                readBoundSource(s, *r);
                influenceStruct.BoundariesSources.push_back(r);
            }
        }
    }
}

/*!
* функция считывает общие параметры для воздействия и запускает считывание источников в данном воздействии.
* \param influence - Итератор.
* \param influenceStruct - ссылка на массив структур воздействий.
* \return void
*/
void SourceReader::readInfluence(const Json::Value::const_iterator &influence, Influence& influenceStruct)
{

    for (auto influence_keys = influence->begin(); influence_keys != influence->end(); ++influence_keys) {
        if (influence_keys.key() == "Sources") {
            readSources(influence_keys, influenceStruct);
        }
        if (influence_keys.key() == "Time function") {  // заход в блок Time function
            for (auto tf = (*influence_keys).begin(); tf != (*influence_keys).end(); ++tf) {
                if (tf.key() == "Count") influenceStruct.tfCount = tf->asInt();
                if (tf.key() == "Time") influenceStruct.tfTime = convertVectorDtype<double>(stringToVector(tf->asString()));
                if (tf.key() == "Value") influenceStruct.tfValue = convertVectorDtype<double>(stringToVector(tf->asString()));
            }
        }

        if (influence_keys.key() == "Influence number") influenceStruct.influenceNumber = influence_keys->asInt();
        if (influence_keys.key() == "Amplitude") influenceStruct.amplitude = influence_keys->asDouble();
    }
}

/*!
* Функция чтения файла spectres.
* \return массив названий спектров из файла spectres
*/
void SourceReader::readSpectresFile() {
    std::string fName = "spectres";
    std::ifstream in(fName);
    std::string line;

    int i = 0, j = 0;
    if (in.is_open()) {

        getline(in, line); //head
        getline(in, line); // spectres num
        int sp_count = std::stoi(line);
        for (int i = 0; i < sp_count; i++) {
            if (!getline(in, line)) return;

            // remove end-of-line endings
            removeEOL(line);

            m_spectres.insert(std::make_pair(line, i));
        }

        if (!getline(in, line)) return; //head volume distributions
        if (line.find("<Volume78 distributions>") == std::string::npos) return;
        getline(in, line); // distributions count
        int distr_count = std::stoi(line);

        for (int i = 0; i < distr_count; i++) {
            if (!getline(in, line)) return;

            // remove end-of-line endings
            removeEOL(line);

            m_spectres.insert(std::make_pair(line, i));

        }
    } else {
        char s[100] = "spectres";
        fprintf(stderr, "Cannot open file %s\n", s);
        exit(1);
    }
    in.close();
}

GridData::Data SourceReader::getGrd(){
    std::ifstream streamStart("START_N");
    ProjectData::StartData projectStartData;
    streamStart >> projectStartData;

    std::ifstream streamProject(projectStartData.project_name);
    ProjectData::Data projectData;
    streamProject >> projectData;


    std::ifstream streamGrd(projectData.grid_file_name);
    GridData::Data gridData;
    streamGrd >> gridData;

    return gridData;
}

/*!
* функциия запуска чтения потока remp_sources.json
* \param infl - ссылка на массив структур воздействий.
* \param lag - ссылка структуру задержки.
*/
void SourceReader::startReadRempSourcesJson()
{
    std::ifstream istrm(std::string("remp_sources.json"));
    if (istrm) {
        Json::Value root;
        istrm >> root;

        check_sources_version(root);

        for (auto it = root.begin(); it != root.end(); ++it) {  // цикл чтения первого уровня
            if (it.key() == "Influences")  // заход итератора в ключ Influences
                for (auto influence = it->begin(); influence != it->end(); ++influence) {  // итерация по воздействиям и задержке
                    if (influence.key() != "Lag") {
                        auto p_influence = std::make_unique<Influence>(influence.key().asString());
                        readInfluence(influence, *p_influence);
                        m_influences.push_back(std::move(p_influence));
                    }
                    else if (influence.key() == "Lag") { // чтение задержки
                        startReadLag(influence);
                    }
                }
            if (it.key() == "Marple") {
                for (auto marple = it->begin(); marple != it->end(); ++marple) {
                    if (marple.key() == "Sigma") m_marpleData->marpleSigmaFileName = marple->asString();
                    if (marple.key() == "Ionization") m_marpleData->marpleIonFileName = marple->asString();
                }
            }
        }

//        print_log_message("Influences has been initialized");
    }

    else {
        char s[100] = "remp_sources.json";
//        print_log_message("remp_sources.json not found\n");
        fprintf(stderr, "Cannot open file %s\n", s);
        exit(1);
    }
}

std::vector<std::shared_ptr<Influence>> SourceReader::getInfluences() {
    return std::move(m_influences);
}

std::shared_ptr<Lag> SourceReader::getLag() {
    return std::move(m_lag);
}

std::shared_ptr<MarpleData> SourceReader::getMarpleData() {
    return std::move(m_marpleData);
}

std::unordered_map<std::string, int> SourceReader::getSpecters() {
    return m_spectres;
}


