// Mantid Coding standars <http://www.mantidproject.org/Coding_Standards>
// Main Module Header
#include "MantidCurveFitting/Functions/ElasticDiffSphere.h"
// Mantid Headers from the same project
#include "MantidCurveFitting/Constraints/BoundaryConstraint.h"
// Mantid headers from other projects
#include "MantidAPI/FunctionFactory.h"
#include "MantidAPI/IFunction.h"
// third party library headers
#include <boost/math/special_functions/bessel.hpp>
// standard library headers
#include <cmath>
#include <limits>

using BConstraint = Mantid::CurveFitting::Constraints::BoundaryConstraint;

namespace {
Mantid::Kernel::Logger g_log("ElasticDiffSphere");
}

namespace Mantid {
namespace CurveFitting {
namespace Functions {

DECLARE_FUNCTION(ElasticDiffSphere)

/**
 * @brief Constructor where fitting parameters are declared
 */
ElasticDiffSphere::ElasticDiffSphere() {
  //parameter "Height" declared in parent DeltaFunction constructor
  // declareParameter("Height", 1.0);
  declareParameter("Radius", 2.0, "Sphere radius");
  declareAttribute("Q", API::IFunction::Attribute(1.0));
}

/**
 * @brief Set constraints on fitting parameters
 */
void ElasticDiffSphere::init() {
  // Ensure positive values for Height and Radius
  auto HeightConstraint = new BConstraint(
      this, "Height", std::numeric_limits<double>::epsilon(), true);
  this->addConstraint(HeightConstraint);

  auto RadiusConstraint = new BConstraint(
      this, "Radius", std::numeric_limits<double>::epsilon(), true);
  this->addConstraint(RadiusConstraint);
}

/**
 * @brief Calculate intensity of the elastic signal
 */
double ElasticDiffSphere::HeightPrefactor() const {
  const double R = this->getParameter("Radius");
  const double Q = this->getAttribute("Q").asDouble();

  // Penalize negative parameters
  if (R < std::numeric_limits<double>::epsilon()) {
    return std::numeric_limits<double>::infinity();
  }

  return pow(3 * boost::math::sph_bessel(1, Q * R) / (Q * R), 2);
}

}  // namespace Functions
}  // namespace CurveFitting
}  // namespace Mantid
