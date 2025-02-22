#include <cmath>
#include <numbers>

#include "gtest/gtest.h"

#include <ray-tracer/spatial/Matrix.hpp>
#include <ray-tracer/spatial/Point.hpp>
#include <ray-tracer/spatial/Transform.hpp>
#include <ray-tracer/spatial/Vector.hpp>

namespace RayTracer {

TEST(Transform, translate_point) {
    Spatial::Point p(1, 2, 3);
    EXPECT_EQ(Spatial::translate(4, 7, 9) * p, Spatial::Point({5, 9, 12}));

    EXPECT_EQ(
        Spatial::translate(4, 7, 9).invert() * Spatial::Point({5, 9, 12}),
        p
    );
}

TEST(Transform, translate_vector) {
    Spatial::Vector v(1, 2, 3);
    EXPECT_EQ(Spatial::translate(4, 7, 9) * v, v);
}

TEST(Transform, scale) {
    Spatial::Point p(1, 2, 3);
    EXPECT_EQ(Spatial::scale(4, 7, 9) * p, Spatial::Point({4, 14, 27}));

    EXPECT_EQ(
        Spatial::scale(4, 7, 9).invert() * Spatial::Point({4, 14, 27}),
        p
    );

    Spatial::Vector v(1, 2, 3);
    EXPECT_EQ(Spatial::scale(4, 7, 9) * v, Spatial::Vector({4, 14, 27}));

    EXPECT_EQ(
        Spatial::scale(4, 7, 9).invert() * Spatial::Vector({4, 14, 27}),
        v
    );

    Spatial::Point p_reflect(1, 2, 3);
    EXPECT_EQ(Spatial::scale(-1, 1, 1) * p_reflect, Spatial::Point({-1, 2, 3}));
}

TEST(Transform, rotate_x) {
    EXPECT_EQ(
        Spatial::rotate_x(std::numbers::pi / 4) * Spatial::Point(0, 1, 0),
        Spatial::Point(0, std::sqrt(2) / 2, std::sqrt(2) / 2)
    );

    EXPECT_EQ(
        Spatial::rotate_x(std::numbers::pi / 2) * Spatial::Point(0, 1, 0),
        Spatial::Point(0, 0, 1)
    );
}

TEST(Transform, rotate_y) {
    EXPECT_EQ(
        Spatial::rotate_y(std::numbers::pi / 4) * Spatial::Point(0, 0, 1),
        Spatial::Point(std::sqrt(2) / 2, 0, std::sqrt(2) / 2)
    );

    EXPECT_EQ(
        Spatial::rotate_y(std::numbers::pi / 2) * Spatial::Point(0, 0, 1),
        Spatial::Point(1, 0, 0)
    );
}

TEST(Transform, rotate_z) {
    EXPECT_EQ(
        Spatial::rotate_z(std::numbers::pi / 4) * Spatial::Point(0, 1, 0),
        Spatial::Point(-std::sqrt(2) / 2, std::sqrt(2) / 2, 0)
    );

    EXPECT_EQ(
        Spatial::rotate_z(std::numbers::pi / 2) * Spatial::Point(0, 1, 0),
        Spatial::Point(-1, 0, 0)
    );
}

TEST(Transform, shear) {
    EXPECT_EQ(
        Spatial::shear(1, 0, 0, 0, 0, 0) * Spatial::Point({2, 3, 4}),
        Spatial::Point({5, 3, 4})
    );
    EXPECT_EQ(
        Spatial::shear(0, 1, 0, 0, 0, 0) * Spatial::Point({2, 3, 4}),
        Spatial::Point({6, 3, 4})
    );
    EXPECT_EQ(
        Spatial::shear(0, 0, 1, 0, 0, 0) * Spatial::Point({2, 3, 4}),
        Spatial::Point({2, 5, 4})
    );
    EXPECT_EQ(
        Spatial::shear(0, 0, 0, 1, 0, 0) * Spatial::Point({2, 3, 4}),
        Spatial::Point({2, 7, 4})
    );
    EXPECT_EQ(
        Spatial::shear(0, 0, 0, 0, 1, 0) * Spatial::Point({2, 3, 4}),
        Spatial::Point({2, 3, 6})
    );
    EXPECT_EQ(
        Spatial::shear(0, 0, 0, 0, 0, 1) * Spatial::Point({2, 3, 4}),
        Spatial::Point({2, 3, 7})
    );
}

TEST(Transform, chain) {
    Spatial::Matrix a = Spatial::rotate_x(std::numbers::pi / 2);
    Spatial::Matrix b = Spatial::scale(5, 5, 5);
    Spatial::Matrix c = Spatial::translate(10, 5, 7);
    EXPECT_EQ(c * b * a * Spatial::Point({ 1, 0, 1}), Spatial::Point({ 15, 0, 7}));
}

}
