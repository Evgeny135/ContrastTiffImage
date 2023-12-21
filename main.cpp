#include <iostream>
#include <tiffio.h>
#include <vector>
#include "Spectrum.h"
#include <chrono>


int main() {

    auto start = std::chrono::steady_clock::now();

    TIFF *inputTiff = TIFFOpen("C:\\Users\\trish\\Desktop\\iso.tiff", "r");
    if (!inputTiff) {
        std::cerr << "Ошибка открытия входного файла" << std::endl;
        return 1;
    }

    int width, height;
    int bitsPerSample, samplesPerPixel, photoMetric;
    TIFFGetField(inputTiff, TIFFTAG_IMAGEWIDTH, &width);
    TIFFGetField(inputTiff, TIFFTAG_IMAGELENGTH, &height);
    TIFFGetField(inputTiff, TIFFTAG_BITSPERSAMPLE, &bitsPerSample);
    TIFFGetField(inputTiff, TIFFTAG_SAMPLESPERPIXEL, &samplesPerPixel);
    TIFFGetField(inputTiff, TIFFTAG_PHOTOMETRIC, &photoMetric);


    TIFF *outputTiff = TIFFOpen("C:\\Users\\trish\\Desktop\\NIIFOTON\\save.tiff", "w");

    TIFFSetField(outputTiff, TIFFTAG_IMAGEWIDTH, width);
    TIFFSetField(outputTiff, TIFFTAG_IMAGELENGTH, height);
    TIFFSetField(outputTiff, TIFFTAG_BITSPERSAMPLE, 8);
    TIFFSetField(outputTiff, TIFFTAG_SAMPLESPERPIXEL, samplesPerPixel);
    TIFFSetField(outputTiff, TIFFTAG_PHOTOMETRIC, photoMetric);
    TIFFSetField(outputTiff, TIFFTAG_COMPRESSION, COMPRESSION_NONE);


    uint16_t *scanlineData = (uint16_t *) _TIFFmalloc(TIFFScanlineSize(inputTiff));


    Spectrum spectrum(0.1);
    for (uint32_t row = 0; row < height; row++) {
        TIFFReadScanline(inputTiff, scanlineData, row);

        for (uint32_t col = 0; col < width; col++) {
            for (uint16_t channel = 0; channel < samplesPerPixel; channel++) {
                uint16_t sample = scanlineData[col * samplesPerPixel + channel];
                spectrum.createSpectrum(sample);
            }
        }
    }

    spectrum.findMaxSearchablePixel();
    spectrum.findMaxAndMin();

    int max = spectrum.getMax();
    int min =spectrum.getMin();

    double coeffScale = 255.0/(max-min);

    for (uint32_t row = 0; row < height; row++) {
        TIFFReadScanline(inputTiff, scanlineData, row);

        uint8_t *outputScanlineData = new uint8_t[width * samplesPerPixel];
        for (uint32_t col = 0; col < width; col++) {
            for (uint16_t channel = 0; channel < samplesPerPixel; channel++) {
                uint16_t sample = scanlineData[col * samplesPerPixel + channel];

                outputScanlineData[col * samplesPerPixel + channel] = static_cast<uint8_t>(sample *coeffScale);

            }
        }

        TIFFWriteScanline(outputTiff, outputScanlineData, row);

        delete[] outputScanlineData;
    }

    _TIFFfree(scanlineData);
    TIFFClose(inputTiff);
    TIFFClose(outputTiff);

    auto end = std::chrono::steady_clock::now();

    auto diff = end - start;

    std::cout << std::chrono::duration <double, std::milli> (diff).count() << " ms" << std::endl;


    return 0;
}
