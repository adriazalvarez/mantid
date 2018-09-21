#ifndef MANTID_PARALLEL_EVENTSLISTSSHMEMMANAGER_H_
#define MANTID_PARALLEL_EVENTSLISTSSHMEMMANAGER_H_

#include "boost/interprocess/containers/vector.hpp"
#include "boost/interprocess/managed_shared_memory.hpp"
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/offset_ptr.hpp>
#include <ostream>

#include "MantidParallel/DllConfig.h"

namespace ip = boost::interprocess;

namespace Mantid {
namespace Types {
namespace Event {
class TofEvent;
}
} // namespace Types

namespace Parallel {
namespace IO {

/** EventsListsShmemManager : Operates with event list in shared memory in
 * multiprocess environment; NOT an !!!OWNER of shared memory!!!
 * base class for EventsListsShmemStorage, that is the owner.
 * Structure of storage:
 *    chunk_0 |pixel_0|   chunk_1 |pixel_0| ... chunk_N |pixel_0|
 *            |pixel_1|           |pixel_1|      ...    |pixel_1|
 *            ... ... ... ... ... ... ... ... ... ... ... ... ...
 *            |pixel_M|           |pixel_M|      ...    |pixel_M|

  @author Igor Gudich
  @date 2018

  Copyright &copy; 2018 ISIS Rutherford Appleton Laboratory, NScD Oak Ridge
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

using SegmentManager = ip::managed_shared_memory::segment_manager;
using VoidAllocator = ip::allocator<void, SegmentManager>;
using TofEventAllocator = ip::allocator<Types::Event::TofEvent, SegmentManager>;
using EventList = ip::vector<Types::Event::TofEvent, TofEventAllocator>;
using EventListAllocator = ip::allocator<EventList, SegmentManager>;
using EventLists = ip::vector<EventList, EventListAllocator>;
using EventListsAllocator = ip::allocator<EventLists, SegmentManager>;
using Chunks = ip::vector<EventLists, EventListsAllocator>;

class MANTID_PARALLEL_DLL EventsListsShmemManager {
public:
  // Constructor for client usage: "sets" Manager to the piece of shared memory
  // with existed GuardedEventLists in it
  EventsListsShmemManager(const std::string &segmentName,
                          const std::string &elName);

  virtual ~EventsListsShmemManager();

  void AppendEvent(std::size_t chunkN, std::size_t listN,
                   const Types::Event::TofEvent &event);
  template<typename InIter>
  void AppendEvent(std::size_t chunkN, std::size_t listN, InIter from,
                   InIter to);

  std::size_t pixelCount() {
    return m_chunks && !m_chunks->empty() ? m_chunks->at(0).size() : 0;
  }

  MANTID_PARALLEL_DLL friend std::ostream &
  operator<<(std::ostream &os, const EventsListsShmemManager &manager);

protected:
  // Constructor for internal usage in  that just sets up the names, instance
  // for m_eventLists is defined later in derivated class constructor.
  EventsListsShmemManager(const std::string &segmentName,
                          const std::string &elName, int);

  const VoidAllocator &alloc() const;

  /// The name of shared memory segment to save the list of event
  const std::string m_segmentName;

  /// Allocator to mange shared memory
  std::shared_ptr<VoidAllocator> m_allocatorInstance;

  /// Event list shared storage name
  const std::string m_chunksName;

  /// Memory segment to store data
  std::shared_ptr<ip::managed_shared_memory> m_segment;

  /// Event list shared storage
  Chunks *m_chunks;
};

/// Appends the range of ToF events (from other container for example)
template<typename InIter>
void EventsListsShmemManager::AppendEvent(std::size_t chunkN, std::size_t listN,
                                          InIter from, InIter to) {
  if (!m_chunks)
    throw ("No event lists found.");
  auto &list = m_chunks->at(chunkN).at(listN);
  list.insert(list.end(), from, to);
}

} // namespace IO
} // namespace Parallel
} // namespace Mantid

#endif /* MANTID_PARALLEL_EVENTSLISTSSHMEMMANAGER_H_ */