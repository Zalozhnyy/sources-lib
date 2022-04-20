
#include "sources.h"

#include "iostream"

int main() {

    Sources s = Sources();
    s.init_sources();

    auto influence = s.getInfluenceByInfluenceNumber(1);


    for (auto it = influence->VolumeSources.cbegin(); it < influence->VolumeSources.cend(); it++){
        std::cout << (*it)->layerIndex;

    }


    return 0;
}
