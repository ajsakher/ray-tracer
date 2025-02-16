#include "gtest/gtest.h"

#include <ray-tracer/display/Color.hpp>

TEST(Color, constructor) {
    RayTracer::Display::Color c;

    EXPECT_EQ(c.get_red(), 0);
    EXPECT_EQ(c.get_green(), 0);
    EXPECT_EQ(c.get_blue(), 0);

    RayTracer::Display::Color c2(1, 2, 3);

    EXPECT_EQ(c2.get_red(), 1);
    EXPECT_EQ(c2.get_green(), 2);
    EXPECT_EQ(c2.get_blue(), 3);
}

TEST(Color, addition) {
    RayTracer::Display::Color c1(4, 5, 6);
    RayTracer::Display::Color c2(1, 2, 3);

    EXPECT_EQ(c1 + c2, RayTracer::Display::Color(5, 7, 9));

    EXPECT_EQ(c1, RayTracer::Display::Color(4, 5, 6));
    c1 += c2;
    EXPECT_EQ(c1, RayTracer::Display::Color(5, 7, 9));
}

TEST(Color, subtration) {
    RayTracer::Display::Color c1(5, 10, 15);
    RayTracer::Display::Color c2(1, 2, 3);

    EXPECT_EQ(c1 - c2, RayTracer::Display::Color(4, 8, 12));

    EXPECT_EQ(c1, RayTracer::Display::Color(5, 10, 15));
    c1 -= c2;
    EXPECT_EQ(c1, RayTracer::Display::Color(4, 8, 12));
}

TEST(Color, scalar_multiplication) {
    RayTracer::Display::Color c1(2, 15, 50);
    EXPECT_EQ(c1 * 5, RayTracer::Display::Color(10, 75, 250));

    EXPECT_EQ(c1, RayTracer::Display::Color(2, 15, 50));
    c1 *= 5;
    EXPECT_EQ(c1, RayTracer::Display::Color(10, 75, 250));
}

TEST(Color, color_multiplication) {
    RayTracer::Display::Color c1(2, 20, 50);
    RayTracer::Display::Color c2(0.1, 0.2, 0.5);
    EXPECT_EQ(c1 * c2, RayTracer::Display::Color(0.2, 4, 25));

    EXPECT_EQ(c1, RayTracer::Display::Color(2, 20, 50));
    c1 *= c2;
    EXPECT_EQ(c1, RayTracer::Display::Color(0.2, 4, 25));
}

TEST(Color, equivalency) {
    RayTracer::Display::Color c1(2, 20, 50);
    RayTracer::Display::Color c2(0.1, 0.2, 0.5);
    EXPECT_FALSE(c1 == c2);

    EXPECT_TRUE(c1 ==  RayTracer::Display::Color(2, 20, 50));
}
