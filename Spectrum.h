#include <cstdint>
#include "map"

#ifndef CONTRASTTIFFIMAGE_SPECTRUM_H
#define CONTRASTTIFFIMAGE_SPECTRUM_H


class Spectrum {
public:
    Spectrum();
    Spectrum(double percent);
    ~Spectrum();
    void createSpectrum(int sample);

    int getMax() const;

    int getMin() const;
    void findMaxAndMin();
    void findMaxSearchablePixel();

private:
    int array[65536];
    int maxSearchable = 0;
    int max = 0;
    int min = 65536;
    double percent = 0.1;

};


#endif //CONTRASTTIFFIMAGE_SPECTRUM_H
