#include <numbers>
#include <vector>

#include "gtest/gtest.h"

#include <ray-tracer/geometry/Shape.hpp>
#include <ray-tracer/geometry/Sphere.hpp>
#include <ray-tracer/ray-cast/Intersection.hpp>
#include <ray-tracer/ray-cast/Ray.hpp>
#include <ray-tracer/spatial/Point.hpp>
#include <ray-tracer/spatial/Matrix.hpp>
#include <ray-tracer/spatial/Transform.hpp>
#include <ray-tracer/spatial/Vector.hpp>

namespace RayTracer {

TEST(Sphere, intersect) {
    Geometry::Sphere s;

    EXPECT_EQ(s.intersect(RayCast::Ray({0, 0, -5}, {0, 0, 1})), std::vector<double>({4.0, 6.0}));
    EXPECT_EQ(s.intersect(RayCast::Ray({0, 1, -5}, {0, 0, 1})), std::vector<double>({5.0, 5.0}));
    EXPECT_EQ(s.intersect(RayCast::Ray({0, 2, -5}, {0, 0, 1})), std::vector<double>({}));
    EXPECT_EQ(s.intersect(RayCast::Ray({0, 0, 0}, {0, 0, 1})), std::vector<double>({-1.0, 1}));
    EXPECT_EQ(s.intersect(RayCast::Ray({0, 0, 5}, {0, 0, 1})), std::vector<double>({-6.0, -4.}));
}

TEST(Sphere, set_transform) {
    Geometry::Sphere s;
    EXPECT_EQ(s.get_transform(), Spatial::Matrix::get_identity(4));
    s.set_transform(Spatial::translate(2, 3, 4));
    EXPECT_EQ(s.get_transform(), Spatial::translate(2, 3, 4));
}

TEST(Sphere, intersect_translated) {
    Geometry::Sphere s;
    s.set_transform(Spatial::scale(2, 2, 2));
    EXPECT_EQ(s.intersect(RayCast::Ray({0, 0, -5}, {0, 0, 1})), std::vector<double>({3.0, 7.0}));
    s.set_transform(Spatial::translate(5, 0, 0));
    EXPECT_EQ(s.intersect(RayCast::Ray({0, 0, -5}, {0, 0, 1})), std::vector<double>({}));
}

TEST(Sphere, normal_at) {
    Geometry::Sphere s;
    EXPECT_EQ(s.normal_at(Spatial::Point(1, 0, 0)), Spatial::Vector(1, 0, 0));
    EXPECT_EQ(s.normal_at(Spatial::Point(0, 1, 0)), Spatial::Vector(0, 1, 0));
    EXPECT_EQ(s.normal_at(Spatial::Point(0, 0, 1)), Spatial::Vector(0, 0, 1));
    EXPECT_EQ(s.normal_at(Spatial::Point(std::sqrt(3) / 3, std::sqrt(3) / 3, std::sqrt(3) / 3)), Spatial::Vector(std::sqrt(3) / 3, std::sqrt(3) / 3, std::sqrt(3) / 3).normalize());

    s.set_transform(Spatial::translate(0, 1, 0));
    EXPECT_EQ(s.normal_at(Spatial::Point(0, 1.70711, -0.70711)), Spatial::Vector(0, 0.70711, -0.70711));
    s.set_transform(Spatial::scale(1, 0.5, 1) * Spatial::rotate_z(std::numbers::pi / 5));
    EXPECT_EQ(s.normal_at(Spatial::Point(0, std::sqrt(2) / 2, -std::sqrt(2) / 2)), Spatial::Vector(0, 0.97014, -0.24254));
}

TEST(Sphere, get_name_inherit) {
    Geometry::Sphere s;
    Geometry::Shape* shape = &s;
    EXPECT_EQ(shape->get_name(), "sphere");
}

}
