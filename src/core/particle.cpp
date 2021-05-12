#include <boost/algorithm/clamp.hpp>

#include "particle.h"

namespace wikigraph {
namespace core {

Particle::Particle(const QVector2D& position, const QVector2D& velocity, const QVector2D& acceleration, double mass) : position(
    position), velocity(velocity), acceleration(acceleration), mass(mass) {}

Particle::Particle(double mass) : position(), velocity(), acceleration(), mass(mass) {}

void Particle::addForce(const QVector2D& forceVector) {
    acceleration += forceVector / mass;
}

void Particle::update(double dt) {
    velocity += acceleration * dt;
    position += velocity * dt;
    acceleration = {0, 0};
}

void Particle::clamp(double maxX, double maxY) {
    position.setX(boost::algorithm::clamp(position.x(), -maxX, maxX));
    position.setY(boost::algorithm::clamp(position.y(), -maxY, maxY));
}

double distance(const Particle& p1, const Particle& p2) {
    return (p1.position - p2.position).length();
}

double distance2(const Particle& p1, const Particle& p2) {
    return (p1.position - p2.position).lengthSquared();
}

QVector2D towards(const Particle& p1, const Particle& p2) {
    return (p2.position - p1.position).normalized();
}

}
}