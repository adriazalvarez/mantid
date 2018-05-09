#include "MantidAPI/AlgorithmManager.h"

#include "MantidCurveFitting/Algorithms/IqtFit.h"
#include "MantidCurveFitting/Algorithms/QENSFitSequential.h"
#include "MantidCurveFitting/Algorithms/QENSFitSimultaneous.h"

#include "MantidKernel/Logger.h"

using namespace Mantid::API;

namespace {
Mantid::Kernel::Logger g_log("IqtFit");

MatrixWorkspace_sptr cropWorkspace(MatrixWorkspace_sptr workspace,
                                   double startX, double endX) {
  auto cropper = AlgorithmManager::Instance().create("CropWorkspace");
  cropper->setLogging(false);
  cropper->setAlwaysStoreInADS(false);
  cropper->setProperty("InputWorkspace", workspace);
  cropper->setProperty("OutputWorkspace", "__cropped");
  cropper->setProperty("XMin", startX);
  cropper->setProperty("XMax", endX);
  cropper->execute();
  return cropper->getProperty("OutputWorkspace");
}

MatrixWorkspace_sptr convertToHistogram(MatrixWorkspace_sptr workspace) {
  auto converter = AlgorithmManager::Instance().create("ConvertToHistogram");
  converter->setLogging(false);
  converter->setAlwaysStoreInADS(false);
  converter->setProperty("InputWorkspace", workspace);
  converter->setProperty("OutputWorkspace", "__converted");
  converter->execute();
  return converter->getProperty("OutputWorkspace");
}
} // namespace

namespace Mantid {
namespace CurveFitting {
namespace Algorithms {

using namespace API;

/// Algorithms name for identification. @see Algorithm::name
template <> const std::string IqtFit<QENSFitSequential>::name() const {
  return "IqtFitSequential";
}

template <> const std::string IqtFit<QENSFitSimultaneous>::name() const {
  return "IqtFitSimultaneous";
}

template <typename Base> const std::string IqtFit<Base>::name() const {
  return "IqtFit";
}

/// Algorithm's version for identification. @see Algorithm::version
template <typename Base> int IqtFit<Base>::version() const { return 1; }

/// Algorithm's category for identification. @see Algorithm::category
template <typename Base> const std::string IqtFit<Base>::category() const {
  return "Workflow\\MIDAS";
}

/// Algorithm's summary for use in the GUI and help. @see Algorithm::summary
template <> const std::string IqtFit<QENSFitSequential>::summary() const {
  return "Fits data files (\\*\\_iqt) generated by I(Q, t) sequentially.";
}

template <> const std::string IqtFit<QENSFitSimultaneous>::summary() const {
  return "Fits data files (\\*\\_iqt) generated by I(Q, t) simultaneously.";
}

template <typename Base> const std::string IqtFit<Base>::summary() const {
  return "Fits an \\*\\_iqt file generated by I(Q, t) sequentially.";
}

/// Algorithm's see also for related algorithms. @see Algorithm::seeAlso
template <>
const std::vector<std::string> IqtFit<QENSFitSequential>::seeAlso() const {
  return {"QENSFitSequential"};
}

template <>
const std::vector<std::string> IqtFit<QENSFitSimultaneous>::seeAlso() const {
  return {"QENSFitSimultaneous"};
}

template <typename Base>
const std::vector<std::string> IqtFit<Base>::seeAlso() const {
  return {};
}

template <typename Base>
std::map<std::string, std::string> IqtFit<Base>::validateInputs() {
  auto errors = Base::validateInputs();
  double startX = Base::getProperty("StartX");
  if (startX < 0)
    errors["StartX"] = "StartX must be greater than or equal to 0.";
  return errors;
}

template <typename Base>
bool IqtFit<Base>::isFitParameter(const std::string &name) const {
  return name.rfind("A0") != std::string::npos ||
         name.rfind("Height") != std::string::npos ||
         name.rfind("Stretching") != std::string::npos ||
         name.rfind("Lifetime") != std::string::npos;
}

template <typename Base>
bool IqtFit<Base>::throwIfElasticQConversionFails() const {
  return true;
}

template <typename Base>
std::vector<API::MatrixWorkspace_sptr> IqtFit<Base>::getWorkspaces() const {
  auto workspaces = Base::getWorkspaces();
  const double startX = Base::getProperty("StartX");
  const double endX = Base::getProperty("EndX");

  for (auto i = 0u; i < workspaces.size(); ++i)
    workspaces[i] =
        convertToHistogram(cropWorkspace(workspaces[i], startX, endX));
  return workspaces;
}

// Register the algorithms into the AlgorithmFactory
template class IqtFit<QENSFitSequential>;
template class IqtFit<QENSFitSimultaneous>;

using IqtFitSequential = IqtFit<QENSFitSequential>;
using IqtFitSimultaneous = IqtFit<QENSFitSimultaneous>;

DECLARE_ALGORITHM(IqtFitSequential)
DECLARE_ALGORITHM(IqtFitSimultaneous)

} // namespace Algorithms
} // namespace CurveFitting
} // namespace Mantid
