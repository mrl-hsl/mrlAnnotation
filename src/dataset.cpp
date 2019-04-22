#include "dataset.h"

dataSet::dataSet(){

}

void dataSet::addSample(Sample _sample){
  samples.push_back(_sample);
}

Sample dataSet::getSample(int id){
  return samples[id];
}
void dataSet::setSample(int id,Sample _sample){
  samples[id] = _sample;
}

int dataSet::getSize()
{
  return samples.size();
}

