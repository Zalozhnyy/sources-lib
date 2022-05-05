
#include "catch2/catch_all.hpp"
#include "sources_c_api.h"
#include "test_data_source.h"

#include "string"


TEST_CASE("volume test", "[sources]")
{
    API_init_sources(READING_SOURCE_1, SPECTERS);


    REQUIRE(getFortVolumeSpectre(1, 1, 1) == -1); //not exist
    REQUIRE(getFortVolumeSpectre(1, 1, 0) == 0);
    REQUIRE(getSpectreName(getFortVolumeSpectre(1, 1, 0)) == "SP1");

}

TEST_CASE("surface test", "[sources]")
{
    API_init_sources(BIG_RS, BIG_RS_SPECTRES);

    REQUIRE(getSpectreName(
            getFortFluxSpectre(2, 2, 1, 0, 0)
            ) == "1_0_0_2.spc");
    REQUIRE(getSpectreName(
            getFortFluxSpectre(2, 2, 1, 0, 1)
            ) == "1_0_1_2.spc");
    REQUIRE(getSpectreName(
            getFortFluxSpectre(2, 2, 1, 0, 2)
            ) == "1_0_2_2.spc");
    REQUIRE(getSpectreName(
            getFortFluxSpectre(2, 2, 1, 0, 3)
            ) == "1_0_3_2.spc");
    REQUIRE(getSpectreName(
            getFortFluxSpectre(2, 2, 1, 0, 4)
            ) == "1_0_4_2.spc");
    REQUIRE(getSpectreName(
            getFortFluxSpectre(2, 2, 1, 0, 5)
            ) == "1_0_5_2.spc");

    REQUIRE(getSpectreName(getFortFluxSpectre(1, 1, 1, 0, -1)) == "SP1");

}

TEST_CASE("boundaries test", "[sources]")
{
    API_init_sources(BIG_RS, BIG_RS_SPECTRES);

    REQUIRE(getSpectreName(getFortBoundSpectre(1, 1, 1)) == "xmax_part1");
    REQUIRE(getSpectreName(getFortBoundSpectre(1, 1, 3)) == "ymax_part1");
    REQUIRE(getSpectreName(getFortBoundSpectre(1, 1, 5)) == "zmax_part1");
    REQUIRE(getSpectreName(getFortBoundSpectre(1, 1, 0)) == "xmin_part1");
    REQUIRE(getSpectreName(getFortBoundSpectre(1, 1, 2)) == "ymin_part1");
    REQUIRE(getSpectreName(getFortBoundSpectre(1, 1, 4)) == "zmin_part1");

}