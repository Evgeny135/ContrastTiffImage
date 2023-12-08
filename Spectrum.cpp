#include "Spectrum.h"

#include "map"

Spectrum::Spectrum()= default;
Spectrum::~Spectrum() = default;

void Spectrum::createSpectrum(int sample) {
    if (spectrumMap[sample] == 0){
        spectrumMap[sample] = 1;
    }else{
        spectrumMap[sample] += 1;
    }
}

void Spectrum::findMaxSearchablePixel(){
    for (const auto& el :spectrumMap) {
            if (el.second>maxSearchable) maxSearchable = el.second;
    }
}

void Spectrum::findMaxAndMin(){
    for (const auto& el :spectrumMap) {
        if (el.second>=0.7*maxSearchable){
            if (el.first>=max) max = el.first;
            if (el.second<=min) min = el.first;
        }
    }
}

int Spectrum::getMax() const {
    return max;
}

int Spectrum::getMin() const {
    return min;
}
