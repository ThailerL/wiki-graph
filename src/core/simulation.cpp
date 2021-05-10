#include "simulation.h"
#include "../util/util.h"

using wikigraph::util::RNG;

namespace wikigraph {
namespace core {

Simulation::Simulation(const vector<double>& masses, double width, double height)
    : _maxX(width / 2), _maxY(height / 2) {
    for (double mass : masses) _particles.emplace_back(mass);
}

void Simulation::addForceBetween(size_t p1, size_t p2, const Force& force) {
    pair<size_t, size_t> particles = {p1, p2};
    if (_forces.count(particles)) _forces[particles] += force;
    else _forces[particles] = force;
}

void Simulation::run(size_t iterations, double dt) {
    // distribute particles randomly
    RNG random_x(-_maxX, _maxX);
    RNG random_y(-_maxY, _maxY);

    for (Particle& p : _particles) {
        p.position.x = random_x();
        p.position.y = random_y();
        p.velocity = {0, 0};
        p.acceleration = {0, 0};
    }

    // run the simulation
    for (size_t n = 0; n < iterations; n++) {
        update(dt);
    }
}

void Simulation::update(double dt) {
    // TODO: use a k-d tree to only compute forces between close particles
    for (auto const& kvp : _forces) {
        const Force& force = kvp.second;
        Particle& p1 = _particles[kvp.first.first];
        Particle& p2 = _particles[kvp.first.second];
        dvec2 forceVec = force(p1, p2);
        p1.addForce(forceVec);
        p2.addForce(-forceVec);
    }
    for (Particle& p : _particles) {
        p.update(dt);
        p.clamp(_maxX, _maxY);
    }
}

vector<pair<dvec2, double>> Simulation::getParticleInfo() const {
    vector<pair<dvec2, double>> particleInfo(_particles.size());
    for (const Particle& particle : _particles) {
        particleInfo.emplace_back(particle.position, particle.mass);
    }
    return particleInfo;
}

}
}