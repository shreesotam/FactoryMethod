#pragma once
#include "fft.h"
#include <cmath>

// Recursive FFT function (Cooley-Tukey algorithm)
void RecursiveFFT::compute(vector<complex<double>>& x) {
    int N = x.size();
    if (N <= 1) return; // Base case: if the signal is of size 1, return

    vector<complex<double>> even(N / 2), odd(N / 2);
    for (int i = 0; i < N / 2; i++) {
        even[i] = x[2 * i]; // Even indexed elements
        odd[i] = x[2 * i + 1]; // Odd indexed elements
    }

    // Recursively apply FFT to even and odd parts
    compute(even);
    compute(odd);

    // Combine the results
    for (int k = 0; k < N / 2; k++) {
        complex<double> twiddle_factor = exp(complex<double>(0, -2 * PI * k / N)) * odd[k];
        x[k] = even[k] + twiddle_factor;
        x[k + N / 2] = even[k] - twiddle_factor;
    }
}

// FFT with zero-padding (for non-power-of-2 length)
void ZeroPaddingFFT::compute(vector<complex<double>>& x) {
    int N = x.size();
    int powerOfTwo = 1;
    while (powerOfTwo < N) {
        powerOfTwo *= 2;
    }

    // Zero padding
    x.resize(powerOfTwo, complex<double>(0, 0));

    // Perform FFT on the padded signal
    RecursiveFFT recursiveFFT;
    recursiveFFT.compute(x);
}

// FFT Factory class
unique_ptr<FFT> FFTFactory::createFFT(vector<complex<double>>& signal) {
    int N = signal.size();
    int powerOfTwo = 1;
    while (powerOfTwo < N) {
        powerOfTwo *= 2;
    }

    if (powerOfTwo == N) {
        // If the size is already a power of 2, use RecursiveFFT
        return make_unique<RecursiveFFT>();
    } else {
        // If the size is not a power of 2, use ZeroPaddingFFT
        return make_unique<ZeroPaddingFFT>();
    }
}
