// Mantid Repository : https://github.com/mantidproject/mantid
//
// Copyright &copy; 2021 ISIS Rutherford Appleton Laboratory UKRI,
//   NScD Oak Ridge National Laboratory, European Spallation Source,
//   Institut Laue - Langevin & CSNS, Institute of High Energy Physics, CAS
// SPDX - License - Identifier: GPL - 3.0 +
#pragma once

#include "Common/DllConfig.h"
#include "IPreviewModel.h"
#include "MantidAPI/MatrixWorkspace_fwd.h"
#include "Reduction/PreviewRow.h"

#include <memory>
#include <string>

namespace MantidQt::CustomInterfaces::ISISReflectometry {
class IJobManager;

class MANTIDQT_ISISREFLECTOMETRY_DLL PreviewModel : public IPreviewModel {
public:
  virtual ~PreviewModel() = default;
  void loadWorkspace(std::string const &workspaceName, IJobManager &jobManager) override;
  Mantid::API::MatrixWorkspace_sptr getLoadedWs() const override;

private:
  std::optional<PreviewRow> m_runDetails;

  void createRunDetails(std::string const &workspaceName);
  Mantid::API::MatrixWorkspace_sptr loadFromAds(std::string const &workspaceName) const;
};
} // namespace MantidQt::CustomInterfaces::ISISReflectometry
