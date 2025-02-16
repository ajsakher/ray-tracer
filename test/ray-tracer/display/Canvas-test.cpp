#include <stdexcept>

#include "gtest/gtest.h"

#include <ray-tracer/display/Color.hpp>
#include <ray-tracer/display/Canvas.hpp>

TEST(Canvas, constructor) {
    RayTracer::Display::Canvas c(10, 20);
    for (size_t i = 0; i < 10; ++i) {
        for (size_t j = 0; j < 20; ++j) {
            EXPECT_EQ(c.pixel_at(i, j), RayTracer::Display::Color(0, 0, 0));
        }
    }
}

TEST(Canvas, write_pixel) {
    RayTracer::Display::Canvas c(10, 20);
    c.write_pixel(5, 5, RayTracer::Display::Color(0.5, 0.5, 0.5));
    for (size_t i = 0; i < 10; ++i) {
        for (size_t j = 0; j < 20; ++j) {
            if (i == 5 && j == 5) {
                EXPECT_EQ(c.pixel_at(i, j), RayTracer::Display::Color(0.5, 0.5, 0.5));
            } else {
                EXPECT_EQ(c.pixel_at(i, j), RayTracer::Display::Color(0, 0, 0));
            }
        }
    }
}

TEST(Canvas, write_pixel_error) {
    RayTracer::Display::Canvas c(10, 20);
    EXPECT_THROW(c.write_pixel(10, 20, RayTracer::Display::Color(0.5, 0.5, 0.5)), std::invalid_argument);
}

TEST(Canvas, pixel_at_error) {
    RayTracer::Display::Canvas c(10, 20);
    EXPECT_THROW(c.pixel_at(10, 20), std::invalid_argument);
}
