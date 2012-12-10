#ifndef REF_MATRIX_WS_IMAGE_VIEW_H
#define REF_MATRIX_WS_IMAGE_VIEW_H

#include "MantidQtRefDetectorViewer/DllOptionIV.h"
#include "MantidAPI/MatrixWorkspace.h"
#include "MantidAPI/Algorithm.h"
#include "MantidQtRefDetectorViewer/RefImageView.h"

/**
    @class RefMatrixWSImageView 
  
       This is the top level class for showing a matrix workspace
    using an ImageViewer.
 
    @author Dennis Mikkelson 
    @date   2012-05-08 
     
    Copyright © 2012 ORNL, STFC Rutherford Appleton Laboratories
  
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
    
    Code Documentation is available at 
                 <http://doxygen.mantidproject.org>
 */

namespace MantidQt
{
namespace RefDetectorViewer
{

  class RefIVConnections;
   class EXPORT_OPT_MANTIDQT_IMAGEVIEWER RefMatrixWSImageView
{
  public:

    /// Construct an image viewer for the specifed MatrixWorkspace
    RefMatrixWSImageView ( Mantid::API::MatrixWorkspace_sptr mat_ws );

    RefMatrixWSImageView( QString wps_name, double peak_min, double peak_max, double back_min, double back_max, double tof_min, double tof_max);
    RefIVConnections* getConnections();

    ~RefMatrixWSImageView();

private:
    
    RefImageView *image_view;
    
};

} // namespace MantidQt 
} // namespace ImageView 

#endif // REF_MATRIX_WS_IMAGE_VIEW_H
