#include "gtest/gtest.h"
#include <ray-tracer/spatial/Point.hpp>
#include <ray-tracer/spatial/Vector.hpp>

TEST(Point, correct_coordinates) {
    RayTracer::Spatial::Point p(1.0, 2.0, 3.0);
    EXPECT_EQ (p.get_x(),  1.0);
    EXPECT_EQ (p.get_y(),  2.0);
    EXPECT_EQ (p.get_z(),  3.0);
    EXPECT_EQ (p.get_w(), 1.0);
}

TEST(Point, vector_addition) {
    RayTracer::Spatial::Point p(0.0, 0.0, 0.0);
    RayTracer::Spatial::Vector v(1.0, 2.0, 3.0);
    RayTracer::Spatial::Point result = p + v;
    EXPECT_EQ (result.get_x(),  1.0);
    EXPECT_EQ (result.get_y(),  2.0);
    EXPECT_EQ (result.get_z(),  3.0);
    EXPECT_EQ (result.get_w(), 1.0);
}

TEST(Point, vector_subtraction) {
    RayTracer::Spatial::Point p(0.0, 0.0, 0.0);
    RayTracer::Spatial::Vector v(1.0, 2.0, 3.0);
    RayTracer::Spatial::Point result = p - v;
    EXPECT_EQ (result.get_x(),  -1.0);
    EXPECT_EQ (result.get_y(),  -2.0);
    EXPECT_EQ (result.get_z(),  -3.0);
    EXPECT_EQ (result.get_w(), 1.0);
}

TEST(Point, point_subtraction) {
    RayTracer::Spatial::Point p(0.0, 0.0, 0.0);
    RayTracer::Spatial::Point v(1.0, 2.0, 3.0);
    RayTracer::Spatial::Vector result = p - v;
    EXPECT_EQ (result.get_x(),  -1.0);
    EXPECT_EQ (result.get_y(),  -2.0);
    EXPECT_EQ (result.get_z(),  -3.0);
    EXPECT_EQ (result.get_w(), 0.0);
}

TEST(Point, vector_plus_equals) {
    RayTracer::Spatial::Point p(0.0, 0.0, 0.0);
    RayTracer::Spatial::Vector v(1.0, 2.0, 3.0);
    p += v;
    EXPECT_EQ (p.get_x(),  1.0);
    EXPECT_EQ (p.get_y(),  2.0);
    EXPECT_EQ (p.get_z(),  3.0);
    EXPECT_EQ (p.get_w(), 1.0);
}

TEST(Point, vector_minus_equals) {
    RayTracer::Spatial::Point p(0.0, 0.0, 0.0);
    RayTracer::Spatial::Vector v(1.0, 2.0, 3.0);
    p -= v;
    EXPECT_EQ (p.get_x(),  -1.0);
    EXPECT_EQ (p.get_y(),  -2.0);
    EXPECT_EQ (p.get_z(),  -3.0);
    EXPECT_EQ (p.get_w(), 1.0);
}

TEST(Point, point_negation) {
    RayTracer::Spatial::Point p(1.0, 2.0, 3.0);
    p = -p;
    EXPECT_EQ (p.get_x(),  -1.0);
    EXPECT_EQ (p.get_y(),  -2.0);
    EXPECT_EQ (p.get_z(),  -3.0);
    EXPECT_EQ (p.get_w(), 1.0);
}
