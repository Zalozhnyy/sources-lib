#ifndef SOURCES_C_API_H
#define SOURCES_C_API_H

#include "string"
//#ifdef __cplusplus
//extern "C" {
//#endif

void API_init_sources(); //+
void API_init_sources(std::string &jsonString, std::string &spectres); //+
int getLagState(); //+
int getInfluenceCount(); //+
double getCNoLagValue(int influenceNumber, double time); //+
double getCLagValue(int influenceNumber, double x, double y, double z, double time); //+
int getFortInflNumber(int particleNumber); //+
double getFortAmplitude(int influenceNumber);

double getFortNoLagValue(int influenceNumber, double time);

double getFortLagValue(int influenceNumber, double x, double y, double z, double time);

int getFortVolume78Distribution(int influenceNumber, int particleNumber, int layNumber);

int getFortVolume78Spectre(int influenceNumber, int particleNumber, int layNumber);

int getFortVolumeSpectre(int influenceNumber, int particleNumber, int layNumber);

int getFortFluxSpectre(int influenceNumber, int particleNumber, int layNumberFrom, int layNumberTo, int direction);

int getFortBoundSpectre(int influenceNumber, int particleNumber, int direction);

double getFortLag(double x, double y, double z, double time);



//#ifdef __cplusplus
//}
//#endif

std::string getSpectreName(int spectreIndex);


#endif //SOURCES_C_API_H