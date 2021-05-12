#include "simulation.h"
#include "../util/util.h"
#include <iostream>

using wikigraph::util::RNG;

namespace wikigraph {
namespace core {

Simulation::Simulation(const vector<double>& masses, double width, double height, double forceRange)
    : _maxX(width / 2), _maxY(height / 2), _forceRange(forceRange) {
    for (double mass : masses)
        _particles.emplace_back(mass);
}

void Simulation::addForceBetween(size_t p1, size_t p2, const Force& force) {
    pair<size_t, size_t> particles = {p1, p2};
    if (_forces.count(particles))
        _forces[particles] += force;
    else
        _forces[particles] = force;
}

void Simulation::addRangedForceBetween(size_t p1, size_t p2, const Force& force) {
    pair<size_t, size_t> particles = {p1, p2};
    if (_rangedForces.count(particles))
        _rangedForces[particles] += force;
    else
        _rangedForces[particles] = force;
}

void Simulation::run(size_t iterations, double dt) {
    // distribute particles randomly
    RNG random(-1, 1);

    for (Particle& p : _particles) {
        p.position.setX(random() * _maxX / 1.3);
        p.position.setY(random() * _maxY / 1.3);
        p.velocity = {0, 0};
        p.acceleration = {0, 0};
    }

    // run the simulation
    for (size_t n = 0; n < iterations; n++) {
        update(dt);
        if (n % 100 == 0) {
            std::cout << "Iteration " << n << '\n';
        }
    }
}

void applyForce(Particle& p1, Particle& p2, const Force& force) {
    QVector2D forceVec = force(p1, p2);
    p1.addForce(forceVec);
    p2.addForce(-forceVec);
}

void Simulation::update(double dt) {
    // non-ranged forces
    for (auto const& kvp : _forces) {
        applyForce(_particles[kvp.first.first], _particles[kvp.first.second], kvp.second);
    }
    // KD tree culling for ranged forces
    KDTree<2, size_t> kdTree = getKDTree();
    for (size_t i = 0; i < _particles.size(); i++) {
        Point<2, size_t> p(_particles[i].position.x(), _particles[i].position.y(), i);
        for (size_t j : kdTree.rangeQuery(p, _forceRange)) {
            pair<size_t, size_t> particlePair = {i, j};
            if (_rangedForces.count(particlePair)) {
                applyForce(_particles[i], _particles[j], _rangedForces[particlePair]);
            }
        }
    }
    // update particles
    for (Particle& p : _particles) {
        p.update(dt);
        p.clamp(_maxX, _maxY);
    }
}

vector<pair<QVector2D, double>> Simulation::getParticleInfo() const {
    vector<pair<QVector2D, double>> particleInfo;
    for (const Particle& particle : _particles) {
        particleInfo.emplace_back(particle.position, particle.mass);
    }
    return particleInfo;
}

KDTree<2, size_t> Simulation::getKDTree() {
    vector<Point<2, size_t>> points(_particles.size());
    for (size_t i = 0; i < _particles.size(); i++) {
        points.emplace_back(_particles[i].position.x(), _particles[i].position.y(), i);
    }
    return KDTree<2, size_t>(points);
}

} // namespace core
} // namespace wikigraph