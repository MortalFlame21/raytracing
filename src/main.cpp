#include <iostream>

#include "Color.h"
#include "Vec3.h"

int main() {
    int img_w{256};
    int img_h{256};

    // header
    std::cout << "P3\n" << img_w << ' ' << img_w << "\n255\n";

    for (int j{}; j < img_h; ++j) {
        std::clog << "\rScanlines remaining: " << (img_h - j) << ' ' << std::flush;
        for (int i{}; i < img_w; ++i) {
            auto pixel_color{Color(static_cast<double>(i) / (img_w - 1),
                                   static_cast<double>(j) / (img_h - 1), 0.0)};

            write_color(pixel_color);
        }
    }
    std::clog << "\rDone.                 \n";
}