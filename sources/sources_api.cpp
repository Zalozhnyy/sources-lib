

#include "sources_api.h"
#include "sources.h"

#include "iostream"

void init_sources() {
    auto s = new Sources();
    s->init_sources();
    delete s;
}







