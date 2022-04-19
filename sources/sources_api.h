#ifndef SOURCES_C_API_H
#define SOURCES_C_API_H

#ifdef __cplusplus
extern "C" {
#endif

	void init_sources();
    int getInfluenceNumber(int particleNumber);
    double getAmplitude(int influenceNumber);
    int getInfluenceCount();
    int getLagState();
    double getCNoLagValue(int inflIndex, double time);






#ifdef __cplusplus
}
#endif


#endif //SOURCES_C_API_H