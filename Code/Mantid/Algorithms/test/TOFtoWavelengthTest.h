#ifndef TOFTOWAVELENGTHTEST_H_
#define TOFTOWAVELENGTHTEST_H_

#include <cxxtest/TestSuite.h>

#include "MantidAlgorithms/TOFtoWavelength.h"
#include "MantidAPI/AnalysisDataService.h"
#include "MantidAPI/WorkspaceFactory.h"
#include "MantidDataObjects/Workspace2D.h"
#include "MantidDataHandling/LoadInstrument.h"

using namespace Mantid::API;
using namespace Mantid::Algorithms;
using namespace Mantid::DataObjects;

class TOFtoWavelengthTest : public CxxTest::TestSuite
{
public:
  
  TOFtoWavelengthTest()
  {
    WorkspaceFactory *factory = WorkspaceFactory::Instance();
    
    // Set up a small workspace for testing
    Workspace_sptr space = factory->create("Workspace2D",2584,11,10);
    Workspace2D_sptr space2D = boost::dynamic_pointer_cast<Workspace2D>(space);
    std::vector<double> x(11);
    for (int i = 0; i < 11; ++i) 
    {
      x[i]=i*1000;
    }
    std::vector<double> a(10);
    std::vector<double> e(10);
    for (int i = 0; i < 10; ++i)
    {
      a[i]=i;
      e[i]=sqrt(double(i));
    }
    for (int j = 0; j < 2584; ++j) {
      space2D->setX(j, x);
      space2D->setData(j, a, e);
    }
    
    // Register the workspace in the data service
    AnalysisDataService *data = AnalysisDataService::Instance();
    inputSpace = "testWorkspace";
    data->add(inputSpace, space);

    // Load the instrument data
    Mantid::DataHandling::LoadInstrument loader;
    loader.initialize();
    // Path to test input file assumes Test directory checked out from SVN
    std::string inputFile = "../../../../Test/Instrument/HET_Definition.txt";
    loader.setPropertyValue("Filename", inputFile);
    loader.setPropertyValue("Workspace", inputSpace);
    loader.execute();
    
  }
  
  void testInit()
  {
    TS_ASSERT_THROWS_NOTHING(alg.initialize());    
    TS_ASSERT( alg.isInitialized() );    
    
    // Set the properties
    alg.setPropertyValue("InputWorkspace",inputSpace);
    outputSpace = "outWorkspace";
    alg.setPropertyValue("OutputWorkspace",outputSpace);
  }
  
  void testExec()
  {
    if ( !alg.isInitialized() ) alg.initialize();
    TS_ASSERT_THROWS_NOTHING( alg.execute());
    TS_ASSERT( alg.isExecuted() );

    // Get back the saved workspace
    AnalysisDataService *data = AnalysisDataService::Instance();
    Workspace_sptr output;
    TS_ASSERT_THROWS_NOTHING(output = data->retrieve(outputSpace));
    Workspace_sptr input;
    TS_ASSERT_THROWS_NOTHING(input = data->retrieve(inputSpace));
    
    Workspace2D_sptr output2D = boost::dynamic_pointer_cast<Workspace2D>(output);
    Workspace2D_sptr input2D = boost::dynamic_pointer_cast<Workspace2D>(input);
    // Test that y & e data is unchanged
    std::vector<double> y = output2D->dataY(777);
    std::vector<double> e = output2D->dataE(777);
    unsigned int ten = 10;
    TS_ASSERT_EQUALS( y.size(), ten );
    TS_ASSERT_EQUALS( e.size(), ten );
    std::vector<double> yIn = input2D->dataY(777);
    std::vector<double> eIn = input2D->dataE(777);
    TS_ASSERT_EQUALS( y[0], yIn[0] );
    TS_ASSERT_EQUALS( y[4], yIn[4] );
    TS_ASSERT_EQUALS( e[1], eIn[1] );
    // Test that spectra that should have been zeroed have been
    std::vector<double> x = output2D->dataX(1);
    y = output2D->dataY(134);
    e = output2D->dataE(382);
    TS_ASSERT_EQUALS( x[7], 0 );
    TS_ASSERT_EQUALS( y[1], 0 );
    TS_ASSERT_EQUALS( e[9], 0 );
    // Check that the data has truly been copied (i.e. isn't a reference to the same
    //    vector in both workspaces)
    double test[10] = {11, 22, 33, 44, 55, 66, 77, 88, 99, 1010};
    std::vector<double> tester(test, test+10);
    output2D->setData(1837, tester);
    y = output2D->dataY(1837);
    TS_ASSERT_EQUALS( y[3], 44.0);
    yIn = input2D->dataY(1837);
    TS_ASSERT_EQUALS( yIn[3], 3.0);
    
    // Check that a couple of x bin boundaries have been correctly converted
    x = output2D->dataX(500);
    TS_ASSERT_DELTA( x[5], 0.914, 0.001 );
    TS_ASSERT_DELTA( x[10], 1.828, 0.001 );
    // Just check that an input bin boundary is unchanged
    std::vector<double> xIn = input2D->dataX(2066);
    TS_ASSERT_EQUALS( xIn[4], 4000.0 );
  }
  
  
private:
  TOFtoWavelength alg;
  std::string inputSpace;
  std::string outputSpace;
};

#endif /*TOFTOWAVELENGTHTEST_H_*/
