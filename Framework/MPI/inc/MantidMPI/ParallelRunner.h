#ifndef MANTID_MPI_PARALLELRUNNER_H_
#define MANTID_MPI_PARALLELRUNNER_H_

#include "MantidMPI/CommunicatorBackend.h"
#include "MantidMPI/Communicator.h"
#include "MantidMPI/DllConfig.h"

#include <functional>
#include <thread>

namespace Mantid {
namespace MPI {

/** Runs a callable in parallel. This is mainly a helper for testing code with
  MPI calls. ParallelRunner passes a Communicator as first argument to the
  callable. In a non-MPI build the callable is executed in threads ot mimic MPI
  ranks.

  Copyright &copy; 2017 ISIS Rutherford Appleton Laboratory, NScD Oak Ridge
  National Laboratory & European Spallation Source

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

  File change history is stored at: <https://github.com/mantidproject/mantid>
  Code Documentation is available at: <http://doxygen.mantidproject.org>
*/
class MANTID_MPI_DLL ParallelRunner {
public:
  ParallelRunner();
  ParallelRunner(const int threads);

  int size() const;

  template <class Function, class... Args>
  void run(Function &&f, Args &&... args);

private:
#ifndef MPI_EXPERIMENTAL
  boost::shared_ptr<CommunicatorBackend> m_backend;
#endif
};

template <class Function, class... Args>
void ParallelRunner::run(Function &&f, Args &&... args) {
#ifdef MPI_EXPERIMENTAL
  Communicator comm;
  f(comm, std::forward<Args>(args)...);
#else
  std::vector<std::thread> threads;
  for (int t = 0; t < m_backend->size(); ++t) {
    Communicator comm(m_backend, t);
    threads.emplace_back(std::forward<Function>(f), comm,
                         std::forward<Args>(args)...);
  }
  for (auto &t : threads) {
    t.join();
  }
#endif
}

template <class... Args> void runParallel(Args &&... args) {
  ParallelRunner runner;
  runner.run(std::forward<Args>(args)...);
}

} // namespace MPI
} // namespace Mantid

#endif /* MANTID_MPI_PARALLELRUNNER_H_ */
