
#include "sources.h"

#include "iostream"

int main() {

    Sources s = Sources();
    s.init_sources();

    auto numbers = s.getInfluenceNumbers();

    for (auto& n : numbers){
        std::cout << s.getInfluenceByInfluenceNumber(n)->influenceName << std::endl ;
    }


    return 0;
}
