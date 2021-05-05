#pragma once

#include "particle.h"
#include "force.h"
#include <vector>
#include <map>
#include <functional>

using std::vector;
using std::map;
using std::pair;
using std::function;
using glm::dvec2;

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
     * @param particles vector of Particle objects.
     */
    Simulation(const vector<Particle>& particles, double width, double height);

    /**
     * Adds a force between two particles.
     *
     * @param p1 index of the first particle
     * @param p2 index of the second particle
     * @param force to apply to the two particles
     */
    void addForceBetween(size_t p1, size_t p2, const Force& force);

    /**
     * Runs the simulation given a timestep and a number of iterations.
     *
     * @param iterations number of iterations to run the simulation
     * @param dt timestep of the simulation
     */
    void run(size_t iterations, double dt);

private:
    vector<Particle> _particles;
    map<pair<size_t, size_t>, Force> _forces;
    const double _maxX;
    const double _maxY;
    /**
     * Updates simulation by a single timestep.
     *
     * @param dt the length of the timestep
     */
    void update(double dt);
};

}
}