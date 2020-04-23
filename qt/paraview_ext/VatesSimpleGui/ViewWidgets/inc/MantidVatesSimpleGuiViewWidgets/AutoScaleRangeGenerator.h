// Mantid Repository : https://github.com/mantidproject/mantid
//
// Copyright &copy; 2007 ISIS Rutherford Appleton Laboratory UKRI,
//   NScD Oak Ridge National Laboratory, European Spallation Source,
//   Institut Laue - Langevin & CSNS, Institute of High Energy Physics, CAS
// SPDX - License - Identifier: GPL - 3.0 +
#pragma once

/**
    Generates information for the color scale, e.g. minimum level, maximum
   level,
    log scale.

    @date 18/11/2014

*/
#include "MantidQtWidgets/Common/MdConstants.h"
#include "MantidQtWidgets/Common/MdSettings.h"
#include "MantidVatesSimpleGuiViewWidgets/WidgetDllOption.h"
#include <QList>

class pqPipelineSource;
class pqDataRepresentation;

namespace Mantid {
namespace Vates {
namespace SimpleGui {

typedef struct VsiColorScale {
  double maxValue;

  double minValue;

  bool useLogScale;
} VsiColorScale;

class EXPORT_OPT_MANTIDVATES_SIMPLEGUI_VIEWWIDGETS AutoScaleRangeGenerator {
public:
  AutoScaleRangeGenerator();

  virtual ~AutoScaleRangeGenerator(){};

  /// Creates a color scale entity.
  VsiColorScale getColorScale();

  /// Enum for different modes
  typedef enum COLORSCALEMODE {
    STANDARD,
    TECHNIQUEDEPENDENT,
    OFFSET
  } COLORSCALEMODE;

  /// Initialize the color scale
  void initializeColorScale();

  /// Update log scale setting
  void updateLogScaleSetting(bool logScale);

private:
  /// Selected color scale mode.
  COLORSCALEMODE mode;

  /// Default value for the color scale
  double defaultValue;

  /// Get the color scale for the standard selection.
  VsiColorScale getStandardColorScale();

  /// Get all ParaView sources from the active server.
  QList<pqPipelineSource *> getAllPVSources();

  /// Make sure that the color scale is valid.
  void sanityCheck(VsiColorScale &colorscale);

  /// Gets the log scale setting for the mode
  bool getLogScale();

  /// Md constants
  MantidQt::API::MdConstants m_mdConstants;

  /// Md Settings
  MantidQt::API::MdSettings m_mdSettings;
};
} // namespace SimpleGui
} // namespace Vates
} // namespace Mantid