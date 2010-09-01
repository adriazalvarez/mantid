#ifndef DATAHANDING_LOADGSS_H_
#define DATAHANDING_LOADGSS_H_

//---------------------------------------------------
// Includes
//---------------------------------------------------
#include "MantidAPI/Algorithm.h"

namespace Mantid
{
namespace DataHandling
{
/**
     Loads a file as saved by SaveGSS

     @author Michael Whitty, ISIS Facility, Rutherford Appleton Laboratory
     @date 01/09/2010

     Copyright &copy; 2010 ISIS Rutherford Appleton Laboratory & NScD Oak Ridge National Laboratory

     This file is part of Mantid.

     Mantid is free software; you can redistribute it and/or modify
     it under the terms of the GNU General Public License as published by
     the Free Software Foundation; either version 3 of the License, or
     (at your option) any later version.

     Mantid is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
     GNU General Public License for more details.

     You should have received a copy of the GNU General Public License
     along with this program.  If not, see <http://www.gnu.org/licenses/>.

     File change history is stored at: <https://svn.mantidproject.org/mantid/trunk/Code/Mantid>
     Code Documentation is available at: <http://doxygen.mantidproject.org>
  */
class DLLExport LoadGSS : public Mantid::API::Algorithm
{
public:
  /// (Empty) Constructor
  LoadGSS() : Mantid::API::Algorithm(){}
  /// Virtual destructor
  virtual ~LoadGSS() {}
  /// Algorithm's name
  virtual const std::string name() const { return "LoadGSS"; }
  /// Algorithm's version
  virtual int version() const { return (1); }
  /// Algorithm's category for identification
  virtual const std::string category() const { return "Diffraction"; }

private:
  /// Initialisation code
  void init();
  ///Execution code
  void exec();
};
}
}
#endif //DATAHANDING_LOADGSS_H_
