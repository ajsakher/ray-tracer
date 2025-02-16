#ifndef RAYTRACER_ENVIRONMENTSIM_ENVIRONMENTSIM_HPP
#define RAYTRACER_ENVIRONMENTSIM_ENVIRONMENTSIM_HPP

#include <ray-tracer/environment-sim/Environment.hpp>
#include <ray-tracer/environment-sim/Projectile.hpp>

namespace RayTracer {
namespace EnvironmentSim {

Projectile tick(const Environment&, const Projectile&);

}
}

#endif
