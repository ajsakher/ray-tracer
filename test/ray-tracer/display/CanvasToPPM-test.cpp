#include <string>

#include "gtest/gtest.h"

#include <ray-tracer/display/Canvas.hpp>
#include <ray-tracer/display/CanvasToPPM.hpp>
#include <ray-tracer/display/Color.hpp>

TEST(canvasToPPM, correct_format) {
    RayTracer::Display::Canvas c(5, 3);
    RayTracer::Display::Color c1(1.5, 0, 0);
    RayTracer::Display::Color c2(0, 0.5, 0);
    RayTracer::Display::Color c3(-0.5, 0, 1);
    c.write_pixel(0, 0, c1);
    c.write_pixel(2, 1, c2);
    c.write_pixel(4, 2, c3);
    std::string ppm = RayTracer::Display::canvasToPPM(c);
    const std::string expected =
        "P3\n"
        "5 3\n"
        "255\n"
        "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255\n\n";
    EXPECT_EQ(expected, ppm);
}
