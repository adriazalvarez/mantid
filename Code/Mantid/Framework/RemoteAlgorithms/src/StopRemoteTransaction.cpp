/*WIKI*

Stop a job transaction on a remote compute resource.

For more details, see the [[Remote_Job_Submission_API|remote job submission API docs]].

*WIKI*/

#include "MantidRemoteAlgorithms/StopRemoteTransaction.h"
#include "MantidRemoteAlgorithms/SimpleJSON.h"
#include "MantidKernel/MandatoryValidator.h"
#include "MantidKernel/FacilityInfo.h"
#include "MantidKernel/ListValidator.h"

#include "MantidKernel/RemoteJobManager.h"

#include "boost/make_shared.hpp"

namespace Mantid
{
namespace RemoteAlgorithms
{
    
// Register the algorithm into the AlgorithmFactory
DECLARE_ALGORITHM(StopRemoteTransaction)

using namespace Mantid::Kernel;

// A reference to the logger is provided by the base class, it is called g_log.
// It is used to print out information, warning and error messages

void StopRemoteTransaction::initDocs()
{
  this->setWikiSummary("Stop a job transaction on a remote compute resource.");
  this->setOptionalMessage("Stop a job transaction on a remote compute resource.");
}

void StopRemoteTransaction::init()
{
  auto requireValue = boost::make_shared<Mantid::Kernel::MandatoryValidator<std::string> >();

  // Compute Resources
  std::vector<std::string> computes = Mantid::Kernel::ConfigService::Instance().getFacility().computeResources();
  declareProperty( "ComputeResource", "", boost::make_shared<StringListValidator>(computes), "", Direction::Input);

  // The transaction ID comes from the StartRemoteTransaction algortithm
  declareProperty( "TransactionID", "", requireValue, "", Mantid::Kernel::Direction::Input);
}

void StopRemoteTransaction::exec()
{
  boost::shared_ptr<RemoteJobManager> jobManager = Mantid::Kernel::ConfigService::Instance().getFacility().getRemoteJobManager( getPropertyValue("ComputeResource"));

  // jobManager is a boost::shared_ptr...
  if (! jobManager)
  {
    // Requested compute resource doesn't exist
    // TODO: should we create our own exception class for this??
    throw( std::runtime_error( std::string("Unable to create a compute resource named " + getPropertyValue("ComputeResource"))));
  }

  std::string transId = getPropertyValue( "TransactionID");
  std::istream &respStream = jobManager->httpGet( "/transaction", std::string("Action=Stop&TransID=") + transId);
  if ( jobManager->lastStatus() == Poco::Net::HTTPResponse::HTTP_OK)
  {
    g_log.information() << "Transaction ID " << transId << " stopped." << std::endl;
  }
  else
  {
    JSONObject resp;
    initFromStream( resp, respStream);
    std::string errMsg;
    resp["Err_Msg"].getValue( errMsg);
    throw( std::runtime_error( errMsg));
  }


}

} // end namespace RemoteAlgorithms
} // end namespace Mantid
