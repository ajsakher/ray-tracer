#include "gtest/gtest.h"

#include <ray-tracer/ray-cast/Ray.hpp>
#include <ray-tracer/spatial/Point.hpp>
#include <ray-tracer/spatial/Transform.hpp>
#include <ray-tracer/spatial/Vector.hpp>

namespace RayTracer {

TEST(Ray, position) {
    RayCast::Ray r(Spatial::Point(2, 3, 4), Spatial::Vector(1, 0, 0));
    EXPECT_EQ(RayCast::position(r, 1), Spatial::Point(3, 3, 4));
    EXPECT_EQ(RayCast::position(r, -1), Spatial::Point(1, 3, 4));
    EXPECT_EQ(RayCast::position(r, 2.5), Spatial::Point(4.5, 3, 4));
}

TEST(Ray, transform) {
    EXPECT_EQ(
        RayCast::transform(
            RayCast::Ray(Spatial::Point(1, 2, 3), Spatial::Vector(0, 1, 0)),
            Spatial::Matrix(Spatial::translate(3, 4, 5))
        ),
        RayCast::Ray(Spatial::Point(4, 6, 8), Spatial::Vector(0, 1, 0))
    );
    EXPECT_EQ(
        RayCast::transform(
            RayCast::Ray(Spatial::Point(1, 2, 3), Spatial::Vector(0, 1, 0)),
            Spatial::Matrix(Spatial::scale(2, 3, 4))
        ),
        RayCast::Ray(Spatial::Point(2, 6, 12), Spatial::Vector(0, 3, 0))
    );
}

}
