#ifndef SOURCES_C_API_H
#define SOURCES_C_API_H

//#ifdef __cplusplus
//extern "C" {
//#endif

void init_sources();
int getLagState();
int getInfluenceCount();
double getCNoLagValue(int inflIndex, double time);
double getCLagValue(int inflIndex, double x, double y, double z, double time);
int getFortInflNumber(int particleNumber);
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


#endif //SOURCES_C_API_H