#include <cmath>

#include "gtest/gtest.h"

#include <ray-tracer/spatial/Vector.hpp>

TEST(Vector, correct_coordinates) {
    RayTracer::Spatial::Vector v(1.0, 2.0, 3.0);
    EXPECT_EQ (v.get_x(),  1.0);
    EXPECT_EQ (v.get_y(),  2.0);
    EXPECT_EQ (v.get_z(),  3.0);
    EXPECT_EQ (v.get_w(), 0.0);
}

TEST(Vector, addition) {
    RayTracer::Spatial::Vector v1(1.0, 2.0, 4.0);
    RayTracer::Spatial::Vector v2(1.0, 1.0, 1.0);

    RayTracer::Spatial::Vector result = v1 + v2;
    EXPECT_EQ (result.get_x(), 2.0);
    EXPECT_EQ (result.get_y(), 3.0);
    EXPECT_EQ (result.get_z(), 5.0);
}

TEST(Vector, subtraction) {
    RayTracer::Spatial::Vector v1(2.0, 4.0, 8.0);
    RayTracer::Spatial::Vector v2(0.5, 0.5, 0.5);

    RayTracer::Spatial::Vector result = v1 - v2;
    EXPECT_EQ (result.get_x(), 1.5);
    EXPECT_EQ (result.get_y(), 3.5);
    EXPECT_EQ (result.get_z(), 7.5);
}

TEST(Vector, plus_equals) {
    RayTracer::Spatial::Vector v1(1.0, 2.0, 4.0);
    RayTracer::Spatial::Vector v2(1.0, 1.0, 1.0);

    v1 += v2;
    EXPECT_EQ (v1.get_x(), 2.0);
    EXPECT_EQ (v1.get_y(), 3.0);
    EXPECT_EQ (v1.get_z(), 5.0);
}

TEST(Vector, minus_equals) {
    RayTracer::Spatial::Vector v1(2.0, 4.0, 8.0);
    RayTracer::Spatial::Vector v2(0.5, 0.5, 0.5);

    v1 -= v2;
    EXPECT_EQ (v1.get_x(), 1.5);
    EXPECT_EQ (v1.get_y(), 3.5);
    EXPECT_EQ (v1.get_z(), 7.5);
}

TEST(Vector, vector_negation) {
    RayTracer::Spatial::Vector v(1.0, 2.0, 3.0);
    v = -v;
    EXPECT_EQ (v.get_x(),  -1.0);
    EXPECT_EQ (v.get_y(),  -2.0);
    EXPECT_EQ (v.get_z(),  -3.0);
    EXPECT_EQ (v.get_w(), 0.0);
}

TEST(Vector, scalar_multiplication) {
    RayTracer::Spatial::Vector v(1.0, 2.0, 3.0);
    RayTracer::Spatial::Vector result = v * 5.0;
    EXPECT_EQ (result.get_x(),  5.0);
    EXPECT_EQ (result.get_y(),  10.0);
    EXPECT_EQ (result.get_z(),  15.0);
}

TEST(Vector, times_equal_scalar) {
    RayTracer::Spatial::Vector v(1.0, 2.0, 3.0);
    v *= 5.0;
    EXPECT_EQ (v.get_x(),  5.0);
    EXPECT_EQ (v.get_y(),  10.0);
    EXPECT_EQ (v.get_z(),  15.0);
}


TEST(Vector, scalar_division) {
    RayTracer::Spatial::Vector v(5.0, 10.0, 15.0);
    RayTracer::Spatial::Vector result = v / 5.0;
    EXPECT_EQ (result.get_x(),  1.0);
    EXPECT_EQ (result.get_y(),  2.0);
    EXPECT_EQ (result.get_z(),  3.0);
}

TEST(Vector, divide_equals_scalar) {
    RayTracer::Spatial::Vector v(5.0, 10.0, 15.0);
    v /= 5.0;
    EXPECT_EQ (v.get_x(),  1.0);
    EXPECT_EQ (v.get_y(),  2.0);
    EXPECT_EQ (v.get_z(),  3.0);
}

TEST(Vector, magnitude) {
    RayTracer::Spatial::Vector unit1(1.0, 0, 0);
    RayTracer::Spatial::Vector unit2(0, 1.0, 0);
    RayTracer::Spatial::Vector unit3(0, 0, 1.0);

    EXPECT_EQ(unit1.magnitude(), 1.0);
    EXPECT_EQ(unit2.magnitude(), 1.0);
    EXPECT_EQ(unit3.magnitude(), 1.0);

     RayTracer::Spatial::Vector v1(1.0, 2.0, 3.0);
     EXPECT_EQ(v1.magnitude(), std::sqrt(14.0));
}

TEST(Vector, normalize) {
    RayTracer::Spatial::Vector unit1(1.0, 0, 0);
    RayTracer::Spatial::Vector unit2(0, 1.0, 0);
    RayTracer::Spatial::Vector unit3(0, 0, 1.0);

    EXPECT_EQ(unit1.normalize() == unit1, true);
    EXPECT_EQ(unit2.normalize() == unit2, true);
    EXPECT_EQ(unit3.normalize() == unit3, true);

    RayTracer::Spatial::Vector v(1.0, 2.0, 3.0);
    RayTracer::Spatial::Vector v_norm = v.normalize();
    EXPECT_DOUBLE_EQ(v_norm.get_x(), 1.0 / std::sqrt(14.0));
    EXPECT_DOUBLE_EQ(v_norm.get_y(), 2.0 / std::sqrt(14.0));
    EXPECT_DOUBLE_EQ(v_norm.get_z(), 3.0 / std::sqrt(14.0));
}

TEST(Vector, dot) {
    RayTracer::Spatial::Vector v1(2, 3, 4);
    RayTracer::Spatial::Vector v2(5, 6, 7);

    EXPECT_EQ(v1.dot(v2), 56);
    EXPECT_EQ(RayTracer::Spatial::dot(v1, v2), 56);
}

TEST(Vector, cross) {
    RayTracer::Spatial::Vector v1(1, 2, 3);
    RayTracer::Spatial::Vector v2(2, 3, 4);

    EXPECT_EQ(v1.cross(v2), RayTracer::Spatial::Vector(-1, 2, -1));
    EXPECT_EQ(RayTracer::Spatial::cross(v1, v2), RayTracer::Spatial::Vector(-1, 2, -1));

    EXPECT_EQ(v2.cross(v1), RayTracer::Spatial::Vector(1, -2, 1));
    EXPECT_EQ(RayTracer::Spatial::cross(v2, v1), RayTracer::Spatial::Vector(1, -2, 1));

    RayTracer::Spatial::Vector x(1.0, 0, 0);
    RayTracer::Spatial::Vector y(0, 1.0, 0);
    RayTracer::Spatial::Vector z(0, 0, 1.0);
    EXPECT_EQ(x.cross(y), z);
    EXPECT_EQ(y.cross(z), x);
    EXPECT_EQ(z.cross(x), y);
}

TEST(Vector, reflect) {
    RayTracer::Spatial::Vector in(1, -1, 0);
    RayTracer::Spatial::Vector n(0, 1, 0);
    EXPECT_EQ(in.reflect(n), RayTracer::Spatial::Vector(1, 1, 0));
    EXPECT_EQ(
        RayTracer::Spatial::Vector(0, -1, 0).reflect(RayTracer::Spatial::Vector(std::sqrt(2) / 2, std::sqrt(2) / 2, 0)),
        RayTracer::Spatial::Vector(1, 0, 0)
    );
}
