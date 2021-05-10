#include <boost/algorithm/clamp.hpp>

#include "particle.h"

namespace wikigraph {
namespace core {

Particle::Particle(const dvec2& position, const dvec2& velocity, const dvec2& acceleration, double mass) : position(
    position), velocity(velocity), acceleration(acceleration), mass(mass) {}

Particle::Particle(double mass) : position(), velocity(), acceleration(), mass(mass) {}

void Particle::addForce(const dvec2& forceVector) {
    acceleration += forceVector / mass;
}

void Particle::update(double dt) {
    velocity += acceleration * dt;
    position += velocity * dt;
    acceleration = {0, 0};
}

void Particle::clamp(double maxX, double maxY) {
    boost::algorithm::clamp(position.x, -maxX, maxX);
    boost::algorithm::clamp(position.y, -maxY, maxY);
}

double distance(const Particle& p1, const Particle& p2) {
    return glm::distance(p1.position, p2.position);
}

double distance2(const Particle& p1, const Particle& p2) {
    return glm::distance2(p1.position, p2.position);
}

dvec2 towards(const Particle& p1, const Particle& p2) {
    return glm::normalize(p2.position - p1.position);
}

}
}