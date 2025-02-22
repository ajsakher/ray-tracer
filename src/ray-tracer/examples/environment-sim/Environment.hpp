#ifndef RAYTRACER_ENVIRONMENTSIM_ENVIRONMENT_HPP
#define RAYTRACER_ENVIRONMENTSIM_ENVIRONMENT_HPP

#include <ray-tracer/examples/environment-sim/Projectile.hpp>
#include <ray-tracer/spatial/Vector.hpp>

namespace RayTracer {
namespace EnvironmentSim {

class Environment {
private:
    Spatial::Vector gravity;
    Spatial::Vector wind;

public:
    Environment(const Spatial::Vector& g, const Spatial::Vector& w) :
        gravity(g), wind(w) {}
    const Spatial::Vector& get_gravity() const { return gravity; }
    const Spatial::Vector& get_wind() const { return wind; }
};

}
}

#endif
