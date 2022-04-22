
#include "sources.h"
#include "sources_c_api.h"

#include "iostream"

int main() {

    API_init_sources();
    std::cout << getFortFluxSpectre(2, 2, 1, 0, 5) << std::endl;
    std::cout << getFortVolumeSpectre(2, 2, 0) << std::endl;
    std::cout << getFortBoundSpectre(1, 1, 3) << std::endl;



    return 0;
}
