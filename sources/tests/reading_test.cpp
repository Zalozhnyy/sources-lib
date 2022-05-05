
#include "catch2/catch_all.hpp"
#include "sources_reader.h"
#include "test_data_source.h"

#include "string"
#include "memory"
#include "iostream"



TEST_CASE("reading test", "[sources]")
{
    std::shared_ptr<MarpleData> m_marpleData;
    std::vector<std::shared_ptr<Influence>> m_influences;
    std::unordered_map<std::string, int> m_specters;
    std::shared_ptr<Lag> m_lag = std::make_shared<Lag>();
    auto reader = SourceReader(m_influences, m_lag, m_marpleData, m_specters);


    reader.startReadRempSourcesJson(READING_SOURCE_1);



    REQUIRE(m_influences.size() == 1);
    REQUIRE(m_influences[0]->influenceName == "1");
    REQUIRE(m_influences[0]->influenceNumber == 1);
    REQUIRE(m_influences[0]->amplitude == 100.);

}