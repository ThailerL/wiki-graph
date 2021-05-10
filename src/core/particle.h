#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>

using std::vector;
using std::string;
using glm::dvec2;

namespace wikigraph {
namespace core {

/**
 * Represents a particle with mass.
 */
class Particle {
public:
    dvec2 position;
    dvec2 velocity;
    dvec2 acceleration;
    const double mass;
    Particle(const dvec2& position, const dvec2& velocity, const dvec2& acceleration, double mass);
    explicit Particle(double mass);
    /**
     * Adds a force to the particle for the current timestep (not persistent).
     *
     * @param forceVector vector representing the force
     */
    void addForce(const dvec2& forceVector);

    /**
     * Updates the position and velocity of the particle, resets the acceleration.
     *
     * @param dt the timestep
     */
    void update(double dt);

    /**
     * Clamps the position of the particle.
     *
     * @parama maxX max x-value for the particle
     * @param maxY max y-value for the particle
     */
    void clamp(double maxX, double maxY);
};

/**
 * Helper function to compute distance between two particles.
 */
double distance(const Particle& p1, const Particle& p2);

/**
 * Helper function to compute square distance between two particles.
 */
double distance2(const Particle& p1, const Particle& p2);

/**
 * Helper function to compute the unit vector pointing from p1 to p2.
 */
dvec2 towards(const Particle& p1, const Particle& p2);

}
}