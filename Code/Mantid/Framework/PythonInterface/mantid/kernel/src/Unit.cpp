#include "MantidKernel/Unit.h"
#include <boost/python/class.hpp>
#include <boost/python/register_ptr_to_python.hpp>

using Mantid::Kernel::Unit;
using Mantid::Kernel::Unit_sptr;
using namespace boost::python;

void export_Unit()
{
  register_ptr_to_python<Unit_sptr>();

  class_<Unit,boost::noncopyable>("Unit", no_init)
    .def("caption", &Unit::caption, "Return the full name of the unit")
    .def("label", &Unit::label, "Returns a label to be printed on the axis")
    .def("unitID", &Unit::unitID, "Returns the string ID of the unit. This may/may not match its name")
  ;

}

