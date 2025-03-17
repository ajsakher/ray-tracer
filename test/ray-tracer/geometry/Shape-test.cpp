#include <vector>

#include "gtest/gtest.h"

#include <ray-tracer/geometry/Shape.hpp>
#include <ray-tracer/geometry/Sphere.hpp>
#include <ray-tracer/ray-cast/Intersection.hpp>

namespace RayTracer {

TEST(Shape, hit) {
    Geometry::Sphere s;
    EXPECT_EQ(Geometry::hit(std::vector<RayCast::Intersection>({
        RayCast::Intersection(s, 1),
        RayCast::Intersection(s, 2),
    }))->get_t(), 1);
    EXPECT_EQ(Geometry::hit(std::vector<RayCast::Intersection>({
        RayCast::Intersection(s, -1),
        RayCast::Intersection(s, 1),
    }))->get_t(), 1);
    EXPECT_EQ(Geometry::hit(std::vector<RayCast::Intersection>({
        RayCast::Intersection(s, -1),
        RayCast::Intersection(s, -2),
    })), nullptr);
    EXPECT_EQ(Geometry::hit(std::vector<RayCast::Intersection>({
        RayCast::Intersection(s, 5),
        RayCast::Intersection(s, 7),
        RayCast::Intersection(s, -3),
        RayCast::Intersection(s, 2),
    }))->get_t(), 2);
}

}
