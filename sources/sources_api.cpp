

#include "sources_api.h"
#include "sources.h"

#include "iostream"

#ifdef __cplusplus

namespace SourcesAPI {
    Sources* sources = nullptr;

    void init_sources() {
        sources = new Sources();
        sources->init_sources();
    }


}

#endif

void init_sources(){
    SourcesAPI::init_sources();
}







