// Mantid Repository : https://github.com/mantidproject/mantid
//
// Copyright &copy; 2021 ISIS Rutherford Appleton Laboratory UKRI,
//   NScD Oak Ridge National Laboratory, European Spallation Source,
//   Institut Laue - Langevin & CSNS, Institute of High Energy Physics, CAS
// SPDX - License - Identifier: GPL - 3.0 +
#pragma once

#include "IReflAlgorithmFactory.h"
#include "MantidQtWidgets/Common/BatchAlgorithmRunner.h"

namespace MantidQt::CustomInterfaces::ISISReflectometry {

class Batch;

class ReflAlgorithmFactory : public IReflAlgorithmFactory {
public:
  explicit ReflAlgorithmFactory(Batch const &batch);
  MantidQt::API::IConfiguredAlgorithm_sptr makePreprocessingAlgorithm() const override;

private:
  Batch const &m_batch;
};
} // namespace MantidQt::CustomInterfaces::ISISReflectometry