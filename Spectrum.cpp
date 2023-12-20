#include "Spectrum.h"

#include "map"

Spectrum::Spectrum()= default;
Spectrum::~Spectrum() = default;

void Spectrum::createSpectrum(int sample) {
    array[sample]+=1;
}

void Spectrum::findMaxSearchablePixel(){
    for (int i = 0; i < 65536; ++i) {
        if (array[i]>maxSearchable) maxSearchable=array[i];
    }
}

void Spectrum::findMaxAndMin(){
    for (int i = 0; i < 65536; ++i) {
        if (array[i]>=percent*maxSearchable){
            if (array[i]>=max) max = array[i];
            if (array[i]<=min) min = array[i];
        }
    }
}

int Spectrum::getMax() const {
    return max;
}

int Spectrum::getMin() const {
    return min;
}

Spectrum::Spectrum(double percent) {
    this->percent = percent;
}
