#include "MantidGeometry/Instrument/DetectorInfo.h"
#include "MantidKernel/Quat.h"
#include "MantidKernel/V3D.h"
#include <boost/python/class.hpp>
#include <boost/python/copy_const_reference.hpp>
#include <boost/python/return_value_policy.hpp>

using Mantid::Geometry::DetectorInfo;
using Mantid::Kernel::Quat;
using Mantid::Kernel::V3D;
using namespace boost::python;

void export_DetectorInfo() {

  // Function pointers to distinguish between overloaded versions
  bool (DetectorInfo::*isMonitor)(const size_t) const =
      &DetectorInfo::isMonitor;

  bool (DetectorInfo::*isMasked)(const size_t) const = &DetectorInfo::isMasked;

  double (DetectorInfo::*twoTheta)(const size_t) const =
      &DetectorInfo::twoTheta;

  double (DetectorInfo::*signedTwoTheta)(const size_t) const =
      &DetectorInfo::signedTwoTheta;

  Mantid::Kernel::V3D (DetectorInfo::*position)(const size_t) const =
      &DetectorInfo::position;

  Mantid::Kernel::Quat (DetectorInfo::*rotation)(const size_t) const =
      &DetectorInfo::rotation;

  void (DetectorInfo::*setMasked)(const size_t, bool) =
      &DetectorInfo::setMasked;

  void (DetectorInfo::*setPosition)(const size_t, const Mantid::Kernel::V3D &) =
      &DetectorInfo::setPosition;

  void (DetectorInfo::*setRotation)(
      const size_t, const Mantid::Kernel::Quat &) = &DetectorInfo::setRotation;

  // Export to Python
  class_<DetectorInfo, boost::noncopyable>("DetectorInfo", no_init)
      .def("__len__", &DetectorInfo::size, (arg("self")),
           "Returns the size of the DetectorInfo, i.e., the number of "
           "detectors in the instrument.")

      .def("size", &DetectorInfo::size, (arg("self")),
           "Returns the size of the DetectorInfo, i.e., the number of "
           "detectors in the instrument.")

      .def("isMonitor", isMonitor, (arg("self"), arg("index")),
           "Returns True if the detector is a monitor.")

      .def("isMasked", isMasked, (arg("self"), arg("index")),
           "Returns True if the detector is masked.")

      .def("isEquivalent", &DetectorInfo::isEquivalent,
           (arg("self"), arg("other")),
           "Returns true if the content of this is equivalent to the content "
           "of other.")

      .def("twoTheta", twoTheta, (arg("self"), arg("index")),
           "Returns 2 theta (scattering angle w.r.t.to beam direction).")

      .def("signedTwoTheta", signedTwoTheta, (arg("self"), arg("index")),
           "Returns signed 2 theta (signed scattering angle w.r.t. to beam "
           "direction).")

      .def("position", position, (arg("self"), arg("index")),
           "Returns the absolute position of the detector with given index.")

      .def("rotation", rotation, (arg("self"), arg("index")),
           "Returns the absolute rotation of the detector with given index.")

      .def("setMasked", setMasked, (arg("self"), arg("index"), arg("masked")),
           "Set the mask flag of the detector with given index.")

      .def("clearMaskFlags", &DetectorInfo::clearMaskFlags, (arg("self")),
           "Sets all mask flags to false (unmasked).")

      .def("setPosition", setPosition,
           (arg("self"), arg("index"), arg("position")),
           "Set the absolute position of the detector with given index.")

      .def("setRotation", setRotation,
           (arg("self"), arg("index"), arg("rotation")),
           "Set the absolute rotation of the detector with given index.");
}
