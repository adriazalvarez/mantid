// Mantid Repository : https://github.com/mantidproject/mantid
//
// Copyright &copy; 2018 ISIS Rutherford Appleton Laboratory UKRI,
//   NScD Oak Ridge National Laboratory, European Spallation Source,
//   Institut Laue - Langevin & CSNS, Institute of High Energy Physics, CAS
// SPDX - License - Identifier: GPL - 3.0 +
#pragma once

#include "ConvFunctionModel.h"
#include "DllConfig.h"
#include "FunctionTemplatePresenter.h"

#include <QMap>

class QtProperty;

namespace MantidQt {
namespace MantidWidgets {
class EditLocalParameterDialog;
}
namespace CustomInterfaces {
namespace IDA {

class ConvTemplateBrowser;

class MANTIDQT_INELASTIC_DLL ConvTemplatePresenter : public FunctionTemplatePresenter {
public:
  explicit ConvTemplatePresenter(ConvTemplateBrowser *view, std::unique_ptr<ConvFunctionModel> model);

  ConvTemplateBrowser *view() const;
  ConvFunctionModel *model() const;

  void setSubType(size_t subTypeIndex, int typeIndex) override;
  void setDeltaFunction(bool) override;
  void setTempCorrection(bool) override;

  void setFunction(std::string const &funStr) override;

  void updateMultiDatasetParameters(const Mantid::API::ITableWorkspace &table) override;

  void setResolution(const std::vector<std::pair<std::string, size_t>> &fitResolutions) override;
  void setBackgroundA0(double value) override;
  void setQValues(const std::vector<double> &qValues) override;

  EstimationDataSelector getEstimationDataSelector() const override;
  void updateParameterEstimationData(DataForParameterEstimationCollection &&data) override;
  void estimateFunctionParameters() override;

protected:
  void updateView() override;

private:
  void updateViewParameters();
  void updateViewParameterNames();
};

} // namespace IDA
} // namespace CustomInterfaces
} // namespace MantidQt
