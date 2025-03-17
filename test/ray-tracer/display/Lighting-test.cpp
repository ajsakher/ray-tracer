#include <iostream>

#include "gtest/gtest.h"

#include <ray-tracer/display/Color.hpp>
#include <ray-tracer/display/Lighting.hpp>
#include <ray-tracer/display/Material.hpp>
#include <ray-tracer/display/PointLight.hpp>
#include <ray-tracer/spatial/Point.hpp>
#include <ray-tracer/spatial/Vector.hpp>

namespace RayTracer {

TEST(Lighting, correct_result) {
    Display::Material m;
    Spatial::Point p;

    Display::PointLight pl(Spatial::Point(0, 0, -10), Display::Color(1, 1, 1));
    Spatial::Vector eyev(0, 0, -1);
    Spatial::Vector normalv(0, 0, -1);
    EXPECT_EQ(Display::lighting(m, pl, p, eyev, normalv), Display::Color(1.9, 1.9, 1.9));

    eyev = Spatial::Vector(0, std::sqrt(2) / 2, -std::sqrt(2) / 2);
    EXPECT_EQ(Display::lighting(m, pl, p, eyev, normalv), Display::Color(1.0, 1.0, 1.0));

    eyev = Spatial::Vector(0, 0, -1);
    pl = Display::PointLight(Spatial::Point(0, 10, -10), Display::Color(1, 1, 1));
    Display::Color v = Display::lighting(m, pl, p, eyev, normalv);
    std::cout << "(" << v.get_red() << ", " << v.get_green() << ", " << v.get_blue() << ")\n";
    EXPECT_EQ(Display::lighting(m, pl, p, eyev, normalv), Display::Color(0.7364, 0.7364, 0.7364));

    eyev = Spatial::Vector(0, -std::sqrt(2) / 2, -std::sqrt(2) / 2);
    EXPECT_EQ(Display::lighting(m, pl, p, eyev, normalv), Display::Color(1.6364, 1.6364, 1.6364));

    eyev = Spatial::Vector(0, 0, -1);
    pl = Display::PointLight(Spatial::Point(0, 0, 10), Display::Color(1, 1, 1));
    EXPECT_EQ(Display::lighting(m, pl, p, eyev, normalv), Display::Color(0.1, 0.1, 0.1));
}

}
