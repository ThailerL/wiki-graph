#pragma once

#include "force.h"
#include "particle.h"
#include "kdtree.h"
#include <functional>
#include <map>
#include <vector>

using std::function;
using std::map;
using std::pair;
using std::vector;

namespace wikigraph {
namespace core {

/**
 * Class which represents a force-based particle simulation.
 */
class Simulation {
public:
    /**
     * Constructs a simulation from a vector of particles.
     *
     * @param masses vector of masses
     * @param width width of the simulation
     * @param height height of the simulation
     * @param forceRange the distance beyond which to stop applying the force between particles (only for ranged forces)
     */
    Simulation(const vector<double>& masses, double width, double height, double forceRange);

    /**
     * Adds a force between two particles.
     *
     * @param p1 index of the first particle
     * @param p2 index of the second particle
     * @param force to apply to the two particles
     */
    void addForceBetween(size_t p1, size_t p2, const Force& force);

    /**
     * Adds a force between two particles with limited range.
     *
     * @param p1 index of the first particle
     * @param p2 index of the second particle
     * @param force to apply to the two particles
     */
    void addRangedForceBetween(size_t p1, size_t p2, const Force& force);

    /**
     * Runs the simulation given a timestep and a number of iterations.
     *
     * @param iterations number of iterations to run the simulation
     * @param dt timestep of the simulation
     */
    void run(size_t iterations, double dt);

    /**
     * Gets (position, mass) pairs for all particles in the simulation.
     */
    vector<pair<QVector2D, double>> getParticleInfo() const;

private:
    /**
     * Helper method to build a KD tree from the particles in the simulation
     * @return KDTree where the values are indices of particles
     */
    KDTree<2, size_t> getKDTree();
    vector<Particle> _particles;
    map<pair<size_t, size_t>, Force> _forces;
    map<pair<size_t, size_t>, Force> _rangedForces;
    const double _maxX;
    const double _maxY;
    const double _forceRange;

    /**
     * Updates simulation by a single timestep.
     *
     * @param dt the length of the timestep
     */
    void update(double dt);
};

} // namespace core
} // namespace wikigraph