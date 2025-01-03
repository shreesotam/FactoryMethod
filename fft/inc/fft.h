#include <vector>
#include <complex>
#include <memory>

using namespace std;

// Define a constant for PI
const double PI = 3.14159265358979323846;

// Abstract FFT class
class FFT {
public:
    virtual void compute(vector<complex<double>>& x) = 0; // Pure virtual function for FFT computation
    virtual ~FFT() {}
};

// Recursive FFT function (Cooley-Tukey algorithm)
class RecursiveFFT : public FFT {
public:
    void compute(vector<complex<double>>& x) override;
};

// FFT with zero-padding (for non-power-of-2 length)
class ZeroPaddingFFT : public FFT {
public:
    void compute(vector<complex<double>>& x) override;
};

// FFT Factory class
class FFTFactory {
public:
    static unique_ptr<FFT> createFFT(vector<complex<double>>& signal);
};

