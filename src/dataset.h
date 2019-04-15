#ifndef DATASET_H
#define DATASET_H
#include "Sample.h"

class dataSet
{
public:
  dataSet(int estimatedSize){
      samples.reserve(estimatedSize);
  }
  dataSet();
  void addSample(Sample);
  void initDataSet(){current = samples.begin();}
  Sample getSample(int id);
  void setSample(int id,Sample);
  void saveSample(int id);
  int getSize();

  typedef std::vector<Sample>::iterator iterator;
  iterator current;
  void next(){if(current != samples.end()-1){current++;};}
  void prev(){if(current > samples.begin()){current--;};}

private:
  std::vector<Sample> samples;
};

#endif // DATASET_H
