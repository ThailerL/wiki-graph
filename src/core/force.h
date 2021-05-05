#pragma once

#include <vector>
#include <string>
#include <functional>
#include "particle.h"

using std::vector;
using std::function;
using glm::dvec2;

namespace wikigraph {
namespace core {

/**
 * A Force is a function which takes in two particles and returns the force vector to be applied to the first one.
 */
typedef function<dvec2(const Particle&, const Particle&)> Force;

/**
 * Builds a coloumbic force.
 *
 * @param k constant to multiply force by (positive for attractive, negative for repulsive)
 * @return a Force proportional to the mass of the two particle and k, and inversely proportional to distance squared
 */
Force coulombicForce(double k);

/**
 * Builds an elastic force.
 * @param k constant to multiply force by (positive for attractive, negative for repulsive)
 * @return a Force proportional to the log of the distance between two particles
 */
Force elasticForce(double k);

/**
 * Overloaded addition for forces. Adds returned force vectors together.
 */
Force operator+(const Force& f1, const Force& f2);

Force& operator+=(Force& lhs, const Force& rhs);

}
}