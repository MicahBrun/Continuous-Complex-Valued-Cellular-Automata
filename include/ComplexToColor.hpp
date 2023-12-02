#pragma once

#include <complex>

namespace ComplexToColor
{

    struct RGB {
        int r, g, b;
    };

    RGB complexToRGB(std::complex<double> z);
}