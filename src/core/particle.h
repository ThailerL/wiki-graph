#pragma once

#include <Qt/qvector2d.h>
#include <string>
#include <vector>

using std::string;
using std::vector;

namespace wikigraph {
namespace core {

/**
 * Represents a particle with mass.
 */
class Particle {
public:
    QVector2D position;
    QVector2D velocity;
    QVector2D acceleration;
    const double mass;
    Particle(const QVector2D& position, const QVector2D& velocity, const QVector2D& acceleration, double mass);
    explicit Particle(double mass);
    /**
     * Adds a force to the particle for the current timestep (not persistent).
     *
     * @param forceVector vector representing the force
     */
    void addForce(const QVector2D& forceVector);

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
QVector2D towards(const Particle& p1, const Particle& p2);

} // namespace core
} // namespace wikigraph