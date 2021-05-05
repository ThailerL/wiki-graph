#include "force.h"

namespace wikigraph {
namespace core {

Force coulombicForce(double k) {
    return [k](const Particle& p1, const Particle& p2) {
      return towards(p1, p2) * k * p1.mass * p2.mass / distance2(p1, p2);
    };
}

Force elasticForce(double k) {
    return [k](const Particle& p1, const Particle& p2) {
      return towards(p1, p2) * k * glm::log(distance(p1, p2));
    };
}

Force operator+(const Force& f1, const Force& f2) {
    return [f1, f2](const Particle& p1, const Particle& p2) {
      return f1(p1, p2) + f2(p1, p2);
    };
}

Force& operator+=(Force& lhs, const Force& rhs) {
    lhs = lhs + rhs;
    return lhs;
}

}
}
