#include "gtest/gtest.h"

#include <ray-tracer/environment-sim/Projectile.hpp>
#include <ray-tracer/spatial/Point.hpp>
#include <ray-tracer/spatial/Vector.hpp>

TEST(Projectile, increment_position_default) {
    RayTracer::EnvironmentSim::Projectile p;
    p.increment_position();

    EXPECT_EQ(p.get_position(), RayTracer::Spatial::Point(0, 0, 0));
}

TEST(Projectile, increment_position_active_velocity_default_time) {
    RayTracer::EnvironmentSim::Projectile p(
        RayTracer::Spatial::Point(0, 0, 0),
        RayTracer::Spatial::Vector(1, 2, 3)
    );
    p.increment_position();

    EXPECT_EQ(p.get_position(), RayTracer::Spatial::Point(1, 2, 3));
}

TEST(Projectile, increment_position_active_velocity_set_time) {
    RayTracer::EnvironmentSim::Projectile p(
        RayTracer::Spatial::Point(0, 0, 0),
        RayTracer::Spatial::Vector(1, 2, 3)
    );
    p.increment_position(0.5);

    EXPECT_EQ(p.get_position(), RayTracer::Spatial::Point(0.5, 1, 1.5));
}

TEST(Projectile, increment_position_change_velocity) {
    RayTracer::EnvironmentSim::Projectile p(
        RayTracer::Spatial::Point(0, 0, 0),
        RayTracer::Spatial::Vector(1, 2, 3)
    );
    p.increment_position();

    EXPECT_EQ(p.get_position(), RayTracer::Spatial::Point(1, 2, 3));

    p.set_velocity(RayTracer::Spatial::Vector(4, 5, 6));
    p.increment_position();
    EXPECT_EQ(p.get_position(), RayTracer::Spatial::Point(5, 7, 9));
}
