#ifndef DATASET_H
#define DATASET_H
#include "sample.h"

class dataSet
{
public:
    dataSet(int estimatedSize){
        samples.reserve(estimatedSize);
    }
    dataSet();
    void addSample(sample);
    sample getSample(int id);
    void setSample(int id,sample);
    void saveSample(int id);
    int getSize();
private:
    std::vector<sample> samples;
};

#endif // DATASET_H
