// Mantid Repository : https://github.com/mantidproject/mantid
//
// Copyright &copy; 2019 ISIS Rutherford Appleton Laboratory UKRI,
//     NScD Oak Ridge National Laboratory, European Spallation Source
//     & Institut Laue - Langevin
// SPDX - License - Identifier: GPL - 3.0 +
#ifndef ALGORITHMPROGRESSMODEL_H
#define ALGORITHMPROGRESSMODEL_H

#include "MantidAPI/AlgorithmObserver.h"
#include "MantidQtWidgets/Common/AlgorithmProgress/AlgorithmProgressObserver.h"
#include "MantidQtWidgets/Common/AlgorithmProgress/AlgorithmProgressPresenterBase.h"

#include <memory>
#include <string>
#include <vector>

namespace MantidQt {
namespace MantidWidgets {
    class AlgorithmProgressModel : public Mantid::API::AlgorithmObserver {
    public:
        using RunningAlgorithmData = std::tuple<std::string, Mantid::API::IAlgorithm_sptr,
            const std::vector<Mantid::Kernel::Property*>&>;

        AlgorithmProgressModel();

        /// Add a new presenter that is displaying a progress bar
        void addPresenter(AlgorithmProgressPresenterBase* presenter);
        void removePresenter(const AlgorithmProgressPresenterBase* presenter);
        /// Update the progress bar in all live presenters
        void updatePresenters();

        /// Remove a currently active observer
        void removeObserver(ProgressObserver* observer);
        /// Update the progress using data from the observer
        void updateProgress(Mantid::API::IAlgorithm_sptr alg, double progress,
            const std::string& msg);

        /// Start an observer that tracks the execution of the parameter algorithm
        void startingHandle(Mantid::API::IAlgorithm_sptr alg) override;

        // TODO figure out if this is necessary
        std::vector<Mantid::API::IAlgorithm_sptr> runningAlgorithms() const;
        Mantid::API::IAlgorithm_sptr latestRunningAlgorithm() const;

    private:
        std::vector<AlgorithmProgressPresenterBase*> presenters;
        std::vector<std::unique_ptr<ProgressObserver>> observers;
    };

} // namespace MantidWidgets
} // namespace MantidQt

#endif // ALGORITHMPROGRESSMODEL_H