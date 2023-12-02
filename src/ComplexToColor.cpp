#include "../include/ComplexToColor.hpp"

#include <cmath>

namespace ComplexToColor
{
    inline RGB hsbToRGB(double hue, double brightness) 
    {
        RGB rgb {};
        hue = fmod(hue, 1.0) * 6.0;
        int i = static_cast<int>(floor(hue));
        double f = hue - i;
        double q = brightness * (1.0 - f);
        double t = brightness * f;

        switch (i) 
        {
            case 0:
                rgb.r = static_cast<int>(brightness * 255.0);
                rgb.g = static_cast<int>(t * 255.0);
                break;
            case 1:
                rgb.r = static_cast<int>(q * 255.0);
                rgb.g = static_cast<int>(brightness * 255.0);
                break;
            case 2:
                rgb.g = static_cast<int>(brightness * 255.0);
                rgb.b = static_cast<int>(t * 255.0);
                break;
            case 3:
                rgb.g = static_cast<int>(q * 255.0);
                rgb.b = static_cast<int>(brightness * 255.0);
                break;
            case 4:
                rgb.r = static_cast<int>(t * 255.0);
                rgb.b = static_cast<int>(brightness * 255.0);
                break;
            case 5:
                rgb.r = static_cast<int>(brightness * 255.0);
                rgb.b = static_cast<int>(q * 255.0);
                break;
            }
        return rgb;
    }

    RGB complexToRGB(std::complex<double> z) 
    {
        double hue = arg(z) / (2 * M_PI) + 0.5; // Normalize to [0, 1]
        double mag { abs(2056.0 * z) / 2056 };
        double brightness { };
        const double k {1.0};
        const double s {1.15051};

        if (mag < k)
            brightness = mag / s;
        else
        {
            brightness = (k + std::fmod(mag - k, s - k)) / s;
        }
        
        return ComplexToColor::hsbToRGB(hue, brightness);
    }
}