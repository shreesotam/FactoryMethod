#pragma once
#include <iostream>
#include <vector>
#include <complex>
#include "fft.h"
#include <memory>

using namespace std;

int main() {
    // Example input signal (length is 4 for simplicity)
    vector<complex<double>> signal = {1, 2, 3, 4};

    // Create the appropriate FFT algorithm using the factory
    unique_ptr<FFT> fftAlgorithm = FFTFactory::createFFT(signal);

    // Perform FFT on the signal
    fftAlgorithm->compute(signal);

    // Output the FFT results (frequency domain representation)
    cout << "FFT of the signal:" << endl;
    for (const auto& c : signal) {
        cout << c.real() << " + " << c.imag() << "i" << endl;
    }

    // Example input signal with non-power-of-2 length
    vector<complex<double>> signal2 = {1, 2, 3}; // Length is not a power of 2

    // Create the appropriate FFT algorithm using the factory
    fftAlgorithm = FFTFactory::createFFT(signal2);

    // Perform FFT with zero-padding
    fftAlgorithm->compute(signal2);

    // Output the FFT results (frequency domain representation)
    cout << "\nFFT of the signal with zero padding:" << endl;
    for (const auto& c : signal2) {
        cout << c.real() << " + " << c.imag() << "i" << endl;
    }

    return 0;
}
