// Mantid Repository : https://github.com/mantidproject/mantid
//
// Copyright &copy; 2018 ISIS Rutherford Appleton Laboratory UKRI,
//   NScD Oak Ridge National Laboratory, European Spallation Source,
//   Institut Laue - Langevin & CSNS, Institute of High Energy Physics, CAS
// SPDX - License - Identifier: GPL - 3.0 +
#include "IndirectDataAnalysisConvFitTab.h"
#include "ConvFitAddWorkspaceDialog.h"
#include "ConvFitDataPresenter.h"
#include "IndirectFitPlotView.h"
#include "IndirectFunctionBrowser/ConvTemplateBrowser.h"

#include "MantidAPI/FunctionFactory.h"

using namespace Mantid;
using namespace Mantid::API;

namespace {
Mantid::Kernel::Logger g_log("ConvFit");

std::vector<std::string> CONVFIT_HIDDEN_PROPS = std::vector<std::string>(
    {"CreateOutput", "LogValue", "PassWSIndexToFunction", "OutputWorkspace", "Output", "PeakRadius", "PlotParameter"});
} // namespace

namespace MantidQt::CustomInterfaces::IDA {

IndirectDataAnalysisConvFitTab::IndirectDataAnalysisConvFitTab(QWidget *parent)
    : IndirectDataAnalysisTab(new ConvFitModel, parent), m_uiForm(new Ui::IndirectFitTab) {
  m_uiForm->setupUi(parent);
  setOutputOptionsView(m_uiForm->ovOutputOptionsView);
  m_uiForm->dockArea->m_fitPropertyBrowser->setFunctionTemplateBrowser(new ConvTemplateBrowser);
  setFitPropertyBrowser(m_uiForm->dockArea->m_fitPropertyBrowser);
  m_uiForm->dockArea->m_fitPropertyBrowser->setHiddenProperties(CONVFIT_HIDDEN_PROPS);

  m_uiForm->dockArea->setFitDataView(new ConvFitDataView(m_uiForm->dockArea));
  auto dataPresenter =
      std::make_unique<ConvFitDataPresenter>(m_fittingModel->getFitDataModel(), m_uiForm->dockArea->m_fitDataView);
  setFitDataPresenter(std::move(dataPresenter));
  setPlotView(m_uiForm->dockArea->m_fitPlotView);
  setRunButton(m_uiForm->pbRun);

  setEditResultVisible(true);
  setConvolveMembers(true);

  // Initialise fitTypeStrings
  m_fitStrings["Lorentzian"] = "L";
  m_fitStrings["StretchedExpFT"] = "SFT";
  m_fitStrings["TeixeiraWaterSQE"] = "TxWater";
  m_fitStrings["FickDiffusionSQE"] = "FickDiff";
  m_fitStrings["ChudleyElliotSQE"] = "ChudElliot";
  m_fitStrings["HallRossSQE"] = "HallRoss";
  m_fitStrings["DiffRotDiscreteCircle"] = "DC";
  m_fitStrings["ElasticDiffRotDiscreteCircle"] = "EDC";
  m_fitStrings["InelasticDiffRotDiscreteCircle"] = "IDC";
  m_fitStrings["DiffSphere"] = "DS";
  m_fitStrings["ElasticDiffSphere"] = "EDS";
  m_fitStrings["InelasticDiffSphere"] = "IDS";
  m_fitStrings["IsoRotDiff"] = "IRD";
  m_fitStrings["ElasticIsoRotDiff"] = "EIRD";
  m_fitStrings["InelasticIsoRotDiff"] = "IIRD";
}

EstimationDataSelector IndirectDataAnalysisConvFitTab::getEstimationDataSelector() const {
  return [](const MantidVec &, const MantidVec &, const std::pair<double, double>) -> DataForParameterEstimation {
    return DataForParameterEstimation{};
  };
}

void IndirectDataAnalysisConvFitTab::addDataToModel(IAddWorkspaceDialog const *dialog) {
  if (const auto convDialog = dynamic_cast<ConvFitAddWorkspaceDialog const *>(dialog)) {
    m_dataPresenter->addWorkspace(convDialog->workspaceName(), convDialog->workspaceIndices());
    m_dataPresenter->setResolution(convDialog->resolutionName());
    m_fittingModel->addDefaultParameters();
  }
}

/**
 * Generate a string to describe the fit type selected by the user.
 * Used when naming the resultant workspaces.
 *
 * Assertions used to guard against any future changes that don't take
 * workspace naming into account.
 *
 * @returns the generated string.
 */
std::string IndirectDataAnalysisConvFitTab::getFitTypeString() const {
  std::string fitType;
  for (auto fitFunctionName : m_fitStrings) {
    auto occurances = getNumberOfCustomFunctions(fitFunctionName.first);
    if (occurances > 0) {
      fitType += std::to_string(occurances) + fitFunctionName.second;
    }
  }

  if (getNumberOfCustomFunctions("DeltaFunction") > 0) {
    fitType += "Delta";
  }

  return fitType;
}

} // namespace MantidQt::CustomInterfaces::IDA
