#ifndef MANTID_ALGORITHMS_WIENERSMOOTHTEST_H_
#define MANTID_ALGORITHMS_WIENERSMOOTHTEST_H_

#include <cxxtest/TestSuite.h>

#include "MantidAlgorithms/WienerSmooth.h"
#include "MantidAPI/FrameworkManager.h"
#include "MantidAPI/MatrixWorkspace.h"
#include "MantidAPI/WorkspaceFactory.h"

#include <algorithm>

using Mantid::Algorithms::WienerSmooth;
using namespace Mantid::API;

class WienerSmoothTest : public CxxTest::TestSuite {
public:
  // This pair of boilerplate methods prevent the suite being created statically
  // This means the constructor isn't called when running other tests
  static WienerSmoothTest *createSuite() { return new WienerSmoothTest(); }
  static void destroySuite(WienerSmoothTest *suite) { delete suite; }

  WienerSmoothTest() { FrameworkManager::Instance(); }

  void test_Init() {
    WienerSmooth alg;
    TS_ASSERT_THROWS_NOTHING(alg.initialize())
    TS_ASSERT(alg.isInitialized())
  }

  void test_data_points_odd() {
    double x[] = {
        2.27988, 2.5079,  2.73593, 2.96398, 3.19203, 3.4201,  3.64818, 3.87627,
        4.10439, 4.33251, 4.56066, 4.78882, 5.017,   5.2452,  5.47342, 5.70167,
        5.92994, 6.15823, 6.38654, 6.61488, 6.84325, 7.07164, 7.30006, 7.52851,
        7.75699, 7.9855,  8.21405, 8.44262, 8.67123, 8.89988, 9.12856, 9.35727,
        9.58603, 9.81482, 10.0437, 10.2725, 10.5014, 10.7304, 10.9594, 11.1884,
        11.4175, 11.6466, 11.8758, 12.1051, 12.3343, 12.5637, 12.793,  13.0225,
        13.2519, 13.4815, 13.7111, 13.9407, 14.1704, 14.4001, 14.63,   14.8598,
        15.0898, 15.3198, 15.5498, 15.7799, 16.0101, 16.2404, 16.4707, 16.7011,
        16.9315, 17.162,  17.3926, 17.6233, 17.854,  18.0848, 18.3157, 18.5467,
        18.7777, 19.0088, 19.24,   19.4712, 19.7026, 19.934,  20.1655, 20.3971,
        20.6288, 20.8605, 21.0924, 21.3243, 21.5563, 21.7885, 22.0207, 22.2529,
        22.4853, 22.7178, 22.9504, 23.1831, 23.4158, 23.6487, 23.8817, 24.1147,
        24.3479, 24.5812, 24.8145, 25.048,  25.2816, 25.5153, 25.7491, 25.983,
        26.217,  26.4511, 26.6854, 26.9197, 27.1542, 27.3888, 27.6235, 27.8583,
        28.0932, 28.3283, 28.5635, 28.7988, 29.0342, 29.2698, 29.5054, 29.7413,
        29.9772, 30.2133, 30.4495, 30.6858, 30.9223, 31.1589, 31.3956, 31.6325,
        31.8695, 32.1066, 32.3439, 32.5814, 32.8189, 33.0567, 33.2945, 33.5326,
        33.7707, 34.009,  34.2475, 34.4861, 34.7249, 34.9639, 35.2029, 35.4422,
        35.6816, 35.9212, 36.1609, 36.4008, 36.6409, 36.8811, 37.1215, 37.3621,
        37.6028, 37.8437, 38.0848, 38.326,  38.5675, 38.8091, 39.0509, 39.2929,
        39.535,  39.7774, 40.0199, 40.2626, 40.5055, 40.7486, 40.9919, 41.2353,
        41.479,  41.7229, 41.9669, 42.2112, 42.4557, 42.7003, 42.9452, 43.1903,
        43.4356, 43.6811, 43.9268, 44.1727, 44.4188, 44.6652, 44.9118, 45.1585,
        45.4056, 45.6528, 45.9002, 46.1479, 46.3958, 46.644,  46.8923, 47.141,
        47.3898, 47.6389, 47.8882, 48.1378, 48.3876, 48.6376, 48.8879, 49.1384,
        49.3892, 49.6403, 49.8916, 50.1431, 50.395,  50.647,  50.8994, 51.152,
        51.4048, 51.658,  51.9114, 52.1651, 52.419,  52.6733, 52.9278, 53.1826,
        53.4377, 53.693,  53.9487, 54.2046, 54.4609, 54.7174, 54.9743, 55.2314,
        55.4888, 55.7466, 56.0046, 56.263,  56.5216, 56.7806, 57.0399, 57.2995,
        57.5595, 57.8197, 58.0803, 58.3412, 58.6025, 58.8641, 59.126,  59.3883,
        59.6509};
    double y[] = {
        0.1189,  0.14286, 0.15511, 0.20033, 0.24087, 0.2996,  0.3667,  0.45925,
        0.54581, 0.64787, 0.72139, 0.75917, 0.7592,  0.70437, 0.66543, 0.61568,
        0.57946, 0.56725, 0.54555, 0.54935, 0.55913, 0.57079, 0.59763, 0.62659,
        0.65637, 0.70992, 0.76924, 0.84962, 0.90275, 0.96503, 1.0212,  1.04499,
        1.02727, 0.98586, 0.94215, 0.89535, 0.85004, 0.82062, 0.77311, 0.75757,
        0.72619, 0.70849, 0.68867, 0.68672, 0.68862, 0.69738, 0.68253, 0.66519,
        0.68893, 0.69585, 0.7261,  0.76552, 0.82647, 0.91327, 0.9998,  1.12527,
        1.22703, 1.37864, 1.50838, 1.64859, 1.7446,  1.82841, 1.82272, 1.81786,
        1.7517,  1.64564, 1.53517, 1.43061, 1.30539, 1.20773, 1.13472, 1.05424,
        0.97878, 0.89599, 0.85828, 0.79429, 0.73088, 0.70002, 0.67398, 0.65064,
        0.59312, 0.61832, 0.60326, 0.59493, 0.61048, 0.62192, 0.65194, 0.67122,
        0.68651, 0.72684, 0.75618, 0.78981, 0.84201, 0.89634, 0.91493, 0.94592,
        0.99613, 1.02684, 1.0639,  1.09255, 1.13058, 1.14893, 1.1503,  1.18634,
        1.18879, 1.20033, 1.20279, 1.20045, 1.18814, 1.17842, 1.16808, 1.15407,
        1.12928, 1.11879, 1.1023,  1.07958, 1.05638, 1.0462,  1.04083, 1.03085,
        1.03033, 1.02903, 1.02619, 1.02792, 1.03886, 1.04313, 1.05231, 1.04534,
        1.06358, 1.05425, 1.05435, 1.0434,  1.02563, 1.01394, 0.98787, 0.96556,
        0.94457, 0.9051,  0.88604, 0.86141, 0.84185, 0.84891, 0.83551, 0.81485,
        0.84004, 0.83454, 0.8117,  0.83888, 0.84998, 0.874,   0.87528, 0.88786,
        0.92081, 0.93851, 0.95443, 0.97785, 0.99923, 1.02937, 1.04029, 1.05765,
        1.07661, 1.08395, 1.09994, 1.11099, 1.12797, 1.13621, 1.14869, 1.15218,
        1.15627, 1.15252, 1.1553,  1.14769, 1.13809, 1.11836, 1.116,   1.1029,
        1.08102, 1.06264, 1.04897, 1.02698, 1.00413, 0.98735, 0.97338, 0.9704,
        0.96175, 0.93567, 0.93158, 0.92161, 0.91366, 0.91242, 0.91492, 0.91012,
        0.91363, 0.91386, 0.91193, 0.92262, 0.92101, 0.92347, 0.92783, 0.92892,
        0.93323, 0.9285,  0.94434, 0.94073, 0.95938, 0.95013, 0.9697,  0.96185,
        0.97768, 0.99063, 1.00007, 1.00453, 1.01804, 1.02646, 1.02738, 1.03621,
        1.04134, 1.06078, 1.06342, 1.06341, 1.0653,  1.0678,  1.06715, 1.07105,
        1.0638,  1.06224, 1.06376, 1.06679, 1.06187, 1.06411, 1.05411, 1.04652,
        1.04076, 1.03172, 1.0255,  1.02284, 1.01324, 1.00444, 1.00077, 0.99847,
        0.98269};
    double e[] = {
        0.04306, 0.05999, 0.04333, 0.04134, 0.04024, 0.04153, 0.04734, 0.05491,
        0.04546, 0.04019, 0.03919, 0.03947, 0.05077, 0.05629, 0.04336, 0.04067,
        0.04076, 0.04336, 0.05906, 0.03617, 0.03875, 0.02772, 0.02843, 0.03264,
        0.03888, 0.03328, 0.02734, 0.02536, 0.02707, 0.03122, 0.0303,  0.02557,
        0.02234, 0.02146, 0.02234, 0.02462, 0.02666, 0.02109, 0.01672, 0.01538,
        0.01634, 0.01944, 0.02216, 0.01792, 0.01708, 0.01789, 0.01926, 0.02449,
        0.02792, 0.02203, 0.02044, 0.01906, 0.01968, 0.02428, 0.02771, 0.02898,
        0.0256,  0.02432, 0.02239, 0.02456, 0.02836, 0.02819, 0.0222,  0.02531,
        0.02621, 0.02977, 0.03856, 0.0322,  0.0313,  0.02681, 0.02502, 0.02521,
        0.04617, 0.04736, 0.04408, 0.03813, 0.03342, 0.03071, 0.03107, 0.0337,
        0.03596, 0.043,   0.03307, 0.0304,  0.02416, 0.03019, 0.02611, 0.02916,
        0.0353,  0.03024, 0.02706, 0.02964, 0.03262, 0.03533, 0.04161, 0.03895,
        0.03374, 0.0291,  0.03359, 0.03053, 0.03269, 0.02773, 0.03506, 0.02503,
        0.0229,  0.02088, 0.01967, 0.01941, 0.02053, 0.02489, 0.02607, 0.02021,
        0.02098, 0.01894, 0.01798, 0.01767, 0.01715, 0.0206,  0.02024, 0.02458,
        0.02048, 0.02021, 0.0202,  0.0179,  0.01829, 0.01982, 0.01909, 0.01999,
        0.02195, 0.02019, 0.02036, 0.02057, 0.02009, 0.02106, 0.02476, 0.02473,
        0.02957, 0.03164, 0.03068, 0.02894, 0.02685, 0.02684, 0.02714, 0.029,
        0.03087, 0.03901, 0.03279, 0.02733, 0.02219, 0.02775, 0.02265, 0.02202,
        0.022,   0.02211, 0.02168, 0.02739, 0.03042, 0.02999, 0.02711, 0.03,
        0.02325, 0.02459, 0.02342, 0.02207, 0.02149, 0.02135, 0.01932, 0.01802,
        0.01806, 0.01805, 0.01814, 0.01895, 0.01899, 0.01936, 0.02054, 0.02212,
        0.02178, 0.01983, 0.02211, 0.02087, 0.02193, 0.02155, 0.02467, 0.02282,
        0.02405, 0.01853, 0.01814, 0.01842, 0.01839, 0.02002, 0.02071, 0.02061,
        0.02047, 0.02057, 0.02164, 0.02491, 0.02371, 0.02035, 0.02759, 0.02022,
        0.03238, 0.03274, 0.02986, 0.02708, 0.02428, 0.03229, 0.02994, 0.02933,
        0.02563, 0.02142, 0.02133, 0.02193, 0.02093, 0.02061, 0.01954, 0.02149,
        0.02398, 0.024,   0.02216, 0.01969, 0.01981, 0.01982, 0.0202,  0.02001,
        0.02083, 0.02022, 0.02228, 0.01919, 0.01454, 0.01797, 0.02072, 0.02082,
        0.01926, 0.02009, 0.0186,  0.01869, 0.01973, 0.02004, 0.01693, 0.01896,
        0.01926};
    double ysmooth[] = {
        0.10759,  0.143251, 0.171589, 0.199732, 0.236917, 0.291331, 0.366582,
        0.459241, 0.558691, 0.649694, 0.717026, 0.750456, 0.748111, 0.716828,
        0.669429, 0.620179, 0.580393, 0.555871, 0.546833, 0.549841, 0.560536,
        0.575983, 0.59587,  0.622382, 0.65895,  0.708318, 0.770491, 0.841309,
        0.912356, 0.973826, 1.01656,  1.03354,  1.02365,  0.991779, 0.946698,
        0.897704, 0.85169,  0.811872, 0.778457, 0.750452, 0.72728,  0.709251,
        0.696869, 0.689744, 0.686162, 0.683859, 0.681506, 0.68013,  0.683295,
        0.696084, 0.723202, 0.767506, 0.829628, 0.908752, 1.00389,  1.11443,
        1.2395,   1.37496,  1.51285,  1.64188,  1.74784,  1.81689,  1.83964,
        1.81408,  1.74634,  1.64871,  1.53592,  1.42116,  1.31322,  1.2158,
        1.12859,  1.04948,  0.976509, 0.908902, 0.847008, 0.791577, 0.743056,
        0.701415, 0.666452, 0.638279, 0.617469, 0.604722, 0.600189, 0.603033,
        0.611557, 0.625455, 0.643837, 0.666154, 0.692705, 0.723941, 0.759658,
        0.798676, 0.839181, 0.879467, 0.918593, 0.956462, 0.993336, 1.02919,
        1.06336,  1.0947,   1.12219,  1.14538,  1.16443,  1.17971,  1.19127,
        1.19868,  1.20127,  1.19871,  1.19132,  1.18014,  1.16646,  1.15141,
        1.13508,  1.1169,   1.0977,   1.07879,  1.06169,  1.04779,  1.03777,
        1.03156,  1.02847,  1.02774,  1.02886,  1.03169,  1.03621,  1.0421,
        1.04849,  1.054,    1.05713,  1.05668,  1.052,    1.04293,  1.02955,
        1.01192,  0.990232, 0.96504,  0.937653, 0.91009,  0.884635, 0.863576,
        0.848612, 0.838996, 0.833117, 0.829432, 0.827287, 0.82711,  0.829988,
        0.836869, 0.847928, 0.86244,  0.879208, 0.897206, 0.916011, 0.935771,
        0.956769, 0.978891, 1.00138,  1.023,    1.04258,  1.0595,   1.07397,
        1.08688,  1.09928,  1.11191,  1.12485,  1.13748,  1.14775,  1.15429,
        1.1568,   1.15554,  1.15118,  1.1445,   1.13609,  1.12611,  1.11428,
        1.10015,  1.08346,  1.06456,  1.04448,  1.02473,  1.00668,  0.991032,
        0.977582, 0.965464, 0.953779, 0.942234, 0.931349, 0.922173, 0.915673,
        0.912145, 0.911036, 0.911148, 0.912427, 0.914533, 0.91682,  0.919042,
        0.921206, 0.923422, 0.925845, 0.92866,  0.932023, 0.935995, 0.9405,
        0.945371, 0.950503, 0.956003, 0.96222,  0.96957,  0.978253, 0.988023,
        0.998173, 1.00783,  1.01636,  1.02371,  1.03041,  1.03733,  1.04518,
        1.05362,  1.06071,  1.06583,  1.06859,  1.06904,  1.06785,  1.06607,
        1.06475,  1.06439,  1.06473,  1.06483,  1.06359,  1.06028,  1.05491,
        1.0481,   1.04066,  1.03315,  1.02581,  1.01875,  1.01226,  1.0068,
        1.00236,  0.997817, 0.990511};

    size_t nx = sizeof(x) / sizeof(double);
    size_t ny = sizeof(y) / sizeof(double);
    TS_ASSERT_EQUALS(nx, ny);

    do_test(nx, x, ny, y, e, ysmooth);
  }

  void test_data_points_even() {
    double x[] = {
        2.27988, 2.5079,  2.73593, 2.96398, 3.19203, 3.4201,  3.64818, 3.87627,
        4.10439, 4.33251, 4.56066, 4.78882, 5.017,   5.2452,  5.47342, 5.70167,
        5.92994, 6.15823, 6.38654, 6.61488, 6.84325, 7.07164, 7.30006, 7.52851,
        7.75699, 7.9855,  8.21405, 8.44262, 8.67123, 8.89988, 9.12856, 9.35727,
        9.58603, 9.81482, 10.0437, 10.2725, 10.5014, 10.7304, 10.9594, 11.1884,
        11.4175, 11.6466, 11.8758, 12.1051, 12.3343, 12.5637, 12.793,  13.0225,
        13.2519, 13.4815, 13.7111, 13.9407, 14.1704, 14.4001, 14.63,   14.8598,
        15.0898, 15.3198, 15.5498, 15.7799, 16.0101, 16.2404, 16.4707, 16.7011,
        16.9315, 17.162,  17.3926, 17.6233, 17.854,  18.0848, 18.3157, 18.5467,
        18.7777, 19.0088, 19.24,   19.4712, 19.7026, 19.934,  20.1655, 20.3971,
        20.6288, 20.8605, 21.0924, 21.3243, 21.5563, 21.7885, 22.0207, 22.2529,
        22.4853, 22.7178, 22.9504, 23.1831, 23.4158, 23.6487, 23.8817, 24.1147,
        24.3479, 24.5812, 24.8145, 25.048,  25.2816, 25.5153, 25.7491, 25.983,
        26.217,  26.4511, 26.6854, 26.9197, 27.1542, 27.3888, 27.6235, 27.8583,
        28.0932, 28.3283, 28.5635, 28.7988, 29.0342, 29.2698, 29.5054, 29.7413,
        29.9772, 30.2133, 30.4495, 30.6858, 30.9223, 31.1589, 31.3956, 31.6325,
        31.8695, 32.1066, 32.3439, 32.5814, 32.8189, 33.0567, 33.2945, 33.5326,
        33.7707, 34.009,  34.2475, 34.4861, 34.7249, 34.9639, 35.2029, 35.4422,
        35.6816, 35.9212, 36.1609, 36.4008, 36.6409, 36.8811, 37.1215, 37.3621,
        37.6028, 37.8437, 38.0848, 38.326,  38.5675, 38.8091, 39.0509, 39.2929,
        39.535,  39.7774, 40.0199, 40.2626, 40.5055, 40.7486, 40.9919, 41.2353,
        41.479,  41.7229, 41.9669, 42.2112, 42.4557, 42.7003, 42.9452, 43.1903,
        43.4356, 43.6811, 43.9268, 44.1727, 44.4188, 44.6652, 44.9118, 45.1585,
        45.4056, 45.6528, 45.9002, 46.1479, 46.3958, 46.644,  46.8923, 47.141,
        47.3898, 47.6389, 47.8882, 48.1378, 48.3876, 48.6376, 48.8879, 49.1384,
        49.3892, 49.6403, 49.8916, 50.1431, 50.395,  50.647,  50.8994, 51.152,
        51.4048, 51.658,  51.9114, 52.1651, 52.419,  52.6733, 52.9278, 53.1826,
        53.4377, 53.693,  53.9487, 54.2046, 54.4609, 54.7174, 54.9743, 55.2314,
        55.4888, 55.7466, 56.0046, 56.263,  56.5216, 56.7806, 57.0399, 57.2995,
        57.5595, 57.8197, 58.0803, 58.3412, 58.6025, 58.8641, 59.126,  59.3883};
    double y[] = {
        0.1189,  0.14286, 0.15511, 0.20033, 0.24087, 0.2996,  0.3667,  0.45925,
        0.54581, 0.64787, 0.72139, 0.75917, 0.7592,  0.70437, 0.66543, 0.61568,
        0.57946, 0.56725, 0.54555, 0.54935, 0.55913, 0.57079, 0.59763, 0.62659,
        0.65637, 0.70992, 0.76924, 0.84962, 0.90275, 0.96503, 1.0212,  1.04499,
        1.02727, 0.98586, 0.94215, 0.89535, 0.85004, 0.82062, 0.77311, 0.75757,
        0.72619, 0.70849, 0.68867, 0.68672, 0.68862, 0.69738, 0.68253, 0.66519,
        0.68893, 0.69585, 0.7261,  0.76552, 0.82647, 0.91327, 0.9998,  1.12527,
        1.22703, 1.37864, 1.50838, 1.64859, 1.7446,  1.82841, 1.82272, 1.81786,
        1.7517,  1.64564, 1.53517, 1.43061, 1.30539, 1.20773, 1.13472, 1.05424,
        0.97878, 0.89599, 0.85828, 0.79429, 0.73088, 0.70002, 0.67398, 0.65064,
        0.59312, 0.61832, 0.60326, 0.59493, 0.61048, 0.62192, 0.65194, 0.67122,
        0.68651, 0.72684, 0.75618, 0.78981, 0.84201, 0.89634, 0.91493, 0.94592,
        0.99613, 1.02684, 1.0639,  1.09255, 1.13058, 1.14893, 1.1503,  1.18634,
        1.18879, 1.20033, 1.20279, 1.20045, 1.18814, 1.17842, 1.16808, 1.15407,
        1.12928, 1.11879, 1.1023,  1.07958, 1.05638, 1.0462,  1.04083, 1.03085,
        1.03033, 1.02903, 1.02619, 1.02792, 1.03886, 1.04313, 1.05231, 1.04534,
        1.06358, 1.05425, 1.05435, 1.0434,  1.02563, 1.01394, 0.98787, 0.96556,
        0.94457, 0.9051,  0.88604, 0.86141, 0.84185, 0.84891, 0.83551, 0.81485,
        0.84004, 0.83454, 0.8117,  0.83888, 0.84998, 0.874,   0.87528, 0.88786,
        0.92081, 0.93851, 0.95443, 0.97785, 0.99923, 1.02937, 1.04029, 1.05765,
        1.07661, 1.08395, 1.09994, 1.11099, 1.12797, 1.13621, 1.14869, 1.15218,
        1.15627, 1.15252, 1.1553,  1.14769, 1.13809, 1.11836, 1.116,   1.1029,
        1.08102, 1.06264, 1.04897, 1.02698, 1.00413, 0.98735, 0.97338, 0.9704,
        0.96175, 0.93567, 0.93158, 0.92161, 0.91366, 0.91242, 0.91492, 0.91012,
        0.91363, 0.91386, 0.91193, 0.92262, 0.92101, 0.92347, 0.92783, 0.92892,
        0.93323, 0.9285,  0.94434, 0.94073, 0.95938, 0.95013, 0.9697,  0.96185,
        0.97768, 0.99063, 1.00007, 1.00453, 1.01804, 1.02646, 1.02738, 1.03621,
        1.04134, 1.06078, 1.06342, 1.06341, 1.0653,  1.0678,  1.06715, 1.07105,
        1.0638,  1.06224, 1.06376, 1.06679, 1.06187, 1.06411, 1.05411, 1.04652,
        1.04076, 1.03172, 1.0255,  1.02284, 1.01324, 1.00444, 1.00077, 0.99847};
    double e[] = {
        0.04306, 0.05999, 0.04333, 0.04134, 0.04024, 0.04153, 0.04734, 0.05491,
        0.04546, 0.04019, 0.03919, 0.03947, 0.05077, 0.05629, 0.04336, 0.04067,
        0.04076, 0.04336, 0.05906, 0.03617, 0.03875, 0.02772, 0.02843, 0.03264,
        0.03888, 0.03328, 0.02734, 0.02536, 0.02707, 0.03122, 0.0303,  0.02557,
        0.02234, 0.02146, 0.02234, 0.02462, 0.02666, 0.02109, 0.01672, 0.01538,
        0.01634, 0.01944, 0.02216, 0.01792, 0.01708, 0.01789, 0.01926, 0.02449,
        0.02792, 0.02203, 0.02044, 0.01906, 0.01968, 0.02428, 0.02771, 0.02898,
        0.0256,  0.02432, 0.02239, 0.02456, 0.02836, 0.02819, 0.0222,  0.02531,
        0.02621, 0.02977, 0.03856, 0.0322,  0.0313,  0.02681, 0.02502, 0.02521,
        0.04617, 0.04736, 0.04408, 0.03813, 0.03342, 0.03071, 0.03107, 0.0337,
        0.03596, 0.043,   0.03307, 0.0304,  0.02416, 0.03019, 0.02611, 0.02916,
        0.0353,  0.03024, 0.02706, 0.02964, 0.03262, 0.03533, 0.04161, 0.03895,
        0.03374, 0.0291,  0.03359, 0.03053, 0.03269, 0.02773, 0.03506, 0.02503,
        0.0229,  0.02088, 0.01967, 0.01941, 0.02053, 0.02489, 0.02607, 0.02021,
        0.02098, 0.01894, 0.01798, 0.01767, 0.01715, 0.0206,  0.02024, 0.02458,
        0.02048, 0.02021, 0.0202,  0.0179,  0.01829, 0.01982, 0.01909, 0.01999,
        0.02195, 0.02019, 0.02036, 0.02057, 0.02009, 0.02106, 0.02476, 0.02473,
        0.02957, 0.03164, 0.03068, 0.02894, 0.02685, 0.02684, 0.02714, 0.029,
        0.03087, 0.03901, 0.03279, 0.02733, 0.02219, 0.02775, 0.02265, 0.02202,
        0.022,   0.02211, 0.02168, 0.02739, 0.03042, 0.02999, 0.02711, 0.03,
        0.02325, 0.02459, 0.02342, 0.02207, 0.02149, 0.02135, 0.01932, 0.01802,
        0.01806, 0.01805, 0.01814, 0.01895, 0.01899, 0.01936, 0.02054, 0.02212,
        0.02178, 0.01983, 0.02211, 0.02087, 0.02193, 0.02155, 0.02467, 0.02282,
        0.02405, 0.01853, 0.01814, 0.01842, 0.01839, 0.02002, 0.02071, 0.02061,
        0.02047, 0.02057, 0.02164, 0.02491, 0.02371, 0.02035, 0.02759, 0.02022,
        0.03238, 0.03274, 0.02986, 0.02708, 0.02428, 0.03229, 0.02994, 0.02933,
        0.02563, 0.02142, 0.02133, 0.02193, 0.02093, 0.02061, 0.01954, 0.02149,
        0.02398, 0.024,   0.02216, 0.01969, 0.01981, 0.01982, 0.0202,  0.02001,
        0.02083, 0.02022, 0.02228, 0.01919, 0.01454, 0.01797, 0.02072, 0.02082,
        0.01926, 0.02009, 0.0186,  0.01869, 0.01973, 0.02004, 0.01693, 0.01896};
    double ysmooth[] = {
        0.10571,  0.14113,  0.170422, 0.200497, 0.239198, 0.293392, 0.366697,
        0.457178, 0.556025, 0.648596, 0.718482, 0.753394, 0.750224, 0.716433,
        0.666845, 0.617474, 0.57971,  0.557712, 0.549671, 0.551374, 0.559535,
        0.573258, 0.593607, 0.622393, 0.661243, 0.711095, 0.771562, 0.839774,
        0.909265, 0.971962, 1.01731,  1.03628,  1.02621,  0.992143, 0.944593,
        0.894828, 0.850347, 0.813122, 0.781275, 0.752565, 0.727006, 0.706837,
        0.694262, 0.689009, 0.687835, 0.686556, 0.683059, 0.679327, 0.680829,
        0.693973, 0.723165, 0.769591, 0.832162, 0.909674, 1.00243,  1.11185,
        1.23795,  1.37532,  1.51508,  1.64431,  1.74854,  1.81526,  1.83691,
        1.81237,  1.74696,  1.65114,  1.53824,  1.42157,  1.31148,  1.21335,
        1.12741,  1.05048,  0.978865, 0.910745, 0.846919, 0.789678, 0.740859,
        0.700616, 0.667622, 0.640477, 0.619021, 0.604505, 0.598366, 0.600683,
        0.610957, 0.627116, 0.646201, 0.667321, 0.691793, 0.72171,  0.757878,
        0.798734, 0.841012, 0.88164,  0.919466, 0.955461, 0.991354, 1.02781,
        1.06358,  1.0962,   1.12366,  1.14564,  1.16334,  1.17823,  1.19063,
        1.19938,  1.20271,  1.19967,  1.19099,  1.17879,  1.16542,  1.15147,
        1.1357,   1.11789,  1.09839,  1.07867,  1.06088,  1.04693,  1.03753,
        1.03208,  1.02932,  1.02826,  1.02866,  1.03092,  1.03541,  1.04178,
        1.04881,  1.05473,  1.05783,  1.05695,  1.05171,  1.04225,  1.02885,
        1.01163,  0.990588, 0.965894, 0.938441, 0.909963, 0.883834, 0.86308,
        0.848462, 0.839233, 0.833626, 0.829895, 0.827354, 0.826657, 0.829251,
        0.836315, 0.847938, 0.863033, 0.880003, 0.897678, 0.915863, 0.935151,
        0.956155, 0.97874,  1.00179,  1.02362,  1.0429,   1.05922,  1.07326,
        1.08624,  1.09925,  1.11277,  1.12627,  1.13771,  1.14663,  1.15282,
        1.15604,  1.15598,  1.15242,  1.14559,  1.13622,  1.12526,  1.11323,
        1.0998,   1.08412,  1.06567,  1.04509,  1.02428,  1.00551,  0.990114,
        0.977699, 0.966525, 0.954864, 0.942373, 0.930385, 0.920947, 0.915278,
        0.912759, 0.912023, 0.91237,  0.912668, 0.913178, 0.914857, 0.918109,
        0.922192, 0.925704, 0.927744, 0.92875,  0.930251, 0.933724, 0.939431,
        0.946216, 0.952447, 0.95739,  0.961909, 0.967867, 0.976659, 0.98799,
        0.999852, 1.00986,  1.01694,  1.02214,  1.02797,  1.03633,  1.04593,
        1.05531,  1.06259,  1.06658,  1.06761,  1.06711,  1.06649,  1.06632,
        1.06626,  1.06578,  1.06471,  1.06335,  1.06193,  1.06,     1.05648,
        1.05032,  1.04148,  1.03143,  1.0226,   1.01698,  1.0146,   1.01285,
        1.00723,  0.993213};

    size_t nx = sizeof(x) / sizeof(double);
    size_t ny = sizeof(y) / sizeof(double);
    TS_ASSERT_EQUALS(nx, ny);

    do_test(nx, x, ny, y, e, ysmooth);
  }

  void test_histogram_odd() {
    double x[] = {
        2.27988, 2.5079,  2.73593, 2.96398, 3.19203, 3.4201,  3.64818, 3.87627,
        4.10439, 4.33251, 4.56066, 4.78882, 5.017,   5.2452,  5.47342, 5.70167,
        5.92994, 6.15823, 6.38654, 6.61488, 6.84325, 7.07164, 7.30006, 7.52851,
        7.75699, 7.9855,  8.21405, 8.44262, 8.67123, 8.89988, 9.12856, 9.35727,
        9.58603, 9.81482, 10.0437, 10.2725, 10.5014, 10.7304, 10.9594, 11.1884,
        11.4175, 11.6466, 11.8758, 12.1051, 12.3343, 12.5637, 12.793,  13.0225,
        13.2519, 13.4815, 13.7111, 13.9407, 14.1704, 14.4001, 14.63,   14.8598,
        15.0898, 15.3198, 15.5498, 15.7799, 16.0101, 16.2404, 16.4707, 16.7011,
        16.9315, 17.162,  17.3926, 17.6233, 17.854,  18.0848, 18.3157, 18.5467,
        18.7777, 19.0088, 19.24,   19.4712, 19.7026, 19.934,  20.1655, 20.3971,
        20.6288, 20.8605, 21.0924, 21.3243, 21.5563, 21.7885, 22.0207, 22.2529,
        22.4853, 22.7178, 22.9504, 23.1831, 23.4158, 23.6487, 23.8817, 24.1147,
        24.3479, 24.5812, 24.8145, 25.048,  25.2816, 25.5153, 25.7491, 25.983,
        26.217,  26.4511, 26.6854, 26.9197, 27.1542, 27.3888, 27.6235, 27.8583,
        28.0932, 28.3283, 28.5635, 28.7988, 29.0342, 29.2698, 29.5054, 29.7413,
        29.9772, 30.2133, 30.4495, 30.6858, 30.9223, 31.1589, 31.3956, 31.6325,
        31.8695, 32.1066, 32.3439, 32.5814, 32.8189, 33.0567, 33.2945, 33.5326,
        33.7707, 34.009,  34.2475, 34.4861, 34.7249, 34.9639, 35.2029, 35.4422,
        35.6816, 35.9212, 36.1609, 36.4008, 36.6409, 36.8811, 37.1215, 37.3621,
        37.6028, 37.8437, 38.0848, 38.326,  38.5675, 38.8091, 39.0509, 39.2929,
        39.535,  39.7774, 40.0199, 40.2626, 40.5055, 40.7486, 40.9919, 41.2353,
        41.479,  41.7229, 41.9669, 42.2112, 42.4557, 42.7003, 42.9452, 43.1903,
        43.4356, 43.6811, 43.9268, 44.1727, 44.4188, 44.6652, 44.9118, 45.1585,
        45.4056, 45.6528, 45.9002, 46.1479, 46.3958, 46.644,  46.8923, 47.141,
        47.3898, 47.6389, 47.8882, 48.1378, 48.3876, 48.6376, 48.8879, 49.1384,
        49.3892, 49.6403, 49.8916, 50.1431, 50.395,  50.647,  50.8994, 51.152,
        51.4048, 51.658,  51.9114, 52.1651, 52.419,  52.6733, 52.9278, 53.1826,
        53.4377, 53.693,  53.9487, 54.2046, 54.4609, 54.7174, 54.9743, 55.2314,
        55.4888, 55.7466, 56.0046, 56.263,  56.5216, 56.7806, 57.0399, 57.2995,
        57.5595, 57.8197, 58.0803, 58.3412, 58.6025, 58.8641, 59.126,  59.3883,
        59.6509};
    double y[] = {
        0.1189,  0.14286, 0.15511, 0.20033, 0.24087, 0.2996,  0.3667,  0.45925,
        0.54581, 0.64787, 0.72139, 0.75917, 0.7592,  0.70437, 0.66543, 0.61568,
        0.57946, 0.56725, 0.54555, 0.54935, 0.55913, 0.57079, 0.59763, 0.62659,
        0.65637, 0.70992, 0.76924, 0.84962, 0.90275, 0.96503, 1.0212,  1.04499,
        1.02727, 0.98586, 0.94215, 0.89535, 0.85004, 0.82062, 0.77311, 0.75757,
        0.72619, 0.70849, 0.68867, 0.68672, 0.68862, 0.69738, 0.68253, 0.66519,
        0.68893, 0.69585, 0.7261,  0.76552, 0.82647, 0.91327, 0.9998,  1.12527,
        1.22703, 1.37864, 1.50838, 1.64859, 1.7446,  1.82841, 1.82272, 1.81786,
        1.7517,  1.64564, 1.53517, 1.43061, 1.30539, 1.20773, 1.13472, 1.05424,
        0.97878, 0.89599, 0.85828, 0.79429, 0.73088, 0.70002, 0.67398, 0.65064,
        0.59312, 0.61832, 0.60326, 0.59493, 0.61048, 0.62192, 0.65194, 0.67122,
        0.68651, 0.72684, 0.75618, 0.78981, 0.84201, 0.89634, 0.91493, 0.94592,
        0.99613, 1.02684, 1.0639,  1.09255, 1.13058, 1.14893, 1.1503,  1.18634,
        1.18879, 1.20033, 1.20279, 1.20045, 1.18814, 1.17842, 1.16808, 1.15407,
        1.12928, 1.11879, 1.1023,  1.07958, 1.05638, 1.0462,  1.04083, 1.03085,
        1.03033, 1.02903, 1.02619, 1.02792, 1.03886, 1.04313, 1.05231, 1.04534,
        1.06358, 1.05425, 1.05435, 1.0434,  1.02563, 1.01394, 0.98787, 0.96556,
        0.94457, 0.9051,  0.88604, 0.86141, 0.84185, 0.84891, 0.83551, 0.81485,
        0.84004, 0.83454, 0.8117,  0.83888, 0.84998, 0.874,   0.87528, 0.88786,
        0.92081, 0.93851, 0.95443, 0.97785, 0.99923, 1.02937, 1.04029, 1.05765,
        1.07661, 1.08395, 1.09994, 1.11099, 1.12797, 1.13621, 1.14869, 1.15218,
        1.15627, 1.15252, 1.1553,  1.14769, 1.13809, 1.11836, 1.116,   1.1029,
        1.08102, 1.06264, 1.04897, 1.02698, 1.00413, 0.98735, 0.97338, 0.9704,
        0.96175, 0.93567, 0.93158, 0.92161, 0.91366, 0.91242, 0.91492, 0.91012,
        0.91363, 0.91386, 0.91193, 0.92262, 0.92101, 0.92347, 0.92783, 0.92892,
        0.93323, 0.9285,  0.94434, 0.94073, 0.95938, 0.95013, 0.9697,  0.96185,
        0.97768, 0.99063, 1.00007, 1.00453, 1.01804, 1.02646, 1.02738, 1.03621,
        1.04134, 1.06078, 1.06342, 1.06341, 1.0653,  1.0678,  1.06715, 1.07105,
        1.0638,  1.06224, 1.06376, 1.06679, 1.06187, 1.06411, 1.05411, 1.04652,
        1.04076, 1.03172, 1.0255,  1.02284, 1.01324, 1.00444, 1.00077, 0.99847};
    double e[] = {
        0.04306, 0.05999, 0.04333, 0.04134, 0.04024, 0.04153, 0.04734, 0.05491,
        0.04546, 0.04019, 0.03919, 0.03947, 0.05077, 0.05629, 0.04336, 0.04067,
        0.04076, 0.04336, 0.05906, 0.03617, 0.03875, 0.02772, 0.02843, 0.03264,
        0.03888, 0.03328, 0.02734, 0.02536, 0.02707, 0.03122, 0.0303,  0.02557,
        0.02234, 0.02146, 0.02234, 0.02462, 0.02666, 0.02109, 0.01672, 0.01538,
        0.01634, 0.01944, 0.02216, 0.01792, 0.01708, 0.01789, 0.01926, 0.02449,
        0.02792, 0.02203, 0.02044, 0.01906, 0.01968, 0.02428, 0.02771, 0.02898,
        0.0256,  0.02432, 0.02239, 0.02456, 0.02836, 0.02819, 0.0222,  0.02531,
        0.02621, 0.02977, 0.03856, 0.0322,  0.0313,  0.02681, 0.02502, 0.02521,
        0.04617, 0.04736, 0.04408, 0.03813, 0.03342, 0.03071, 0.03107, 0.0337,
        0.03596, 0.043,   0.03307, 0.0304,  0.02416, 0.03019, 0.02611, 0.02916,
        0.0353,  0.03024, 0.02706, 0.02964, 0.03262, 0.03533, 0.04161, 0.03895,
        0.03374, 0.0291,  0.03359, 0.03053, 0.03269, 0.02773, 0.03506, 0.02503,
        0.0229,  0.02088, 0.01967, 0.01941, 0.02053, 0.02489, 0.02607, 0.02021,
        0.02098, 0.01894, 0.01798, 0.01767, 0.01715, 0.0206,  0.02024, 0.02458,
        0.02048, 0.02021, 0.0202,  0.0179,  0.01829, 0.01982, 0.01909, 0.01999,
        0.02195, 0.02019, 0.02036, 0.02057, 0.02009, 0.02106, 0.02476, 0.02473,
        0.02957, 0.03164, 0.03068, 0.02894, 0.02685, 0.02684, 0.02714, 0.029,
        0.03087, 0.03901, 0.03279, 0.02733, 0.02219, 0.02775, 0.02265, 0.02202,
        0.022,   0.02211, 0.02168, 0.02739, 0.03042, 0.02999, 0.02711, 0.03,
        0.02325, 0.02459, 0.02342, 0.02207, 0.02149, 0.02135, 0.01932, 0.01802,
        0.01806, 0.01805, 0.01814, 0.01895, 0.01899, 0.01936, 0.02054, 0.02212,
        0.02178, 0.01983, 0.02211, 0.02087, 0.02193, 0.02155, 0.02467, 0.02282,
        0.02405, 0.01853, 0.01814, 0.01842, 0.01839, 0.02002, 0.02071, 0.02061,
        0.02047, 0.02057, 0.02164, 0.02491, 0.02371, 0.02035, 0.02759, 0.02022,
        0.03238, 0.03274, 0.02986, 0.02708, 0.02428, 0.03229, 0.02994, 0.02933,
        0.02563, 0.02142, 0.02133, 0.02193, 0.02093, 0.02061, 0.01954, 0.02149,
        0.02398, 0.024,   0.02216, 0.01969, 0.01981, 0.01982, 0.0202,  0.02001,
        0.02083, 0.02022, 0.02228, 0.01919, 0.01454, 0.01797, 0.02072, 0.02082,
        0.01926, 0.02009, 0.0186,  0.01869, 0.01973, 0.02004, 0.01693, 0.01896};
    double ysmooth[] = {
        0.105725, 0.141127, 0.170416, 0.200494, 0.239199, 0.293395, 0.366699,
        0.457179, 0.556023, 0.648595, 0.718481, 0.753394, 0.750224, 0.716434,
        0.666845, 0.617474, 0.57971,  0.557711, 0.549671, 0.551373, 0.559534,
        0.573259, 0.593609, 0.622395, 0.661243, 0.711093, 0.771558, 0.839774,
        0.909271, 0.971963, 1.0173,   1.03627,  1.02621,  0.992143, 0.944593,
        0.894828, 0.850347, 0.813123, 0.781275, 0.752565, 0.727005, 0.706836,
        0.694262, 0.689006, 0.687838, 0.686555, 0.683062, 0.679325, 0.68083,
        0.693972, 0.723162, 0.76959,  0.832161, 0.909682, 1.00243,  1.11185,
        1.23795,  1.37532,  1.51509,  1.64432,  1.74854,  1.81525,  1.8369,
        1.81237,  1.74696,  1.65114,  1.53824,  1.42157,  1.31148,  1.21335,
        1.12741,  1.05048,  0.978866, 0.910744, 0.846918, 0.789675, 0.74086,
        0.700618, 0.667625, 0.640476, 0.619019, 0.604495, 0.598366, 0.6007,
        0.610954, 0.62711,  0.6462,   0.66732,  0.691794, 0.721711, 0.757878,
        0.798735, 0.84101,  0.881639, 0.919467, 0.955461, 0.991354, 1.02781,
        1.06358,  1.0962,   1.12366,  1.14564,  1.16334,  1.17823,  1.19063,
        1.19938,  1.20271,  1.19967,  1.19099,  1.17879,  1.1654,   1.15147,
        1.13571,  1.1179,   1.09839,  1.07866,  1.06088,  1.04693,  1.03753,
        1.03208,  1.02932,  1.02825,  1.02865,  1.03092,  1.03541,  1.04178,
        1.04882,  1.05473,  1.05782,  1.05695,  1.05171,  1.04225,  1.02885,
        1.01164,  0.990583, 0.96589,  0.938439, 0.909974, 0.883834, 0.863075,
        0.848458, 0.839235, 0.833627, 0.829897, 0.827354, 0.826656, 0.82925,
        0.836315, 0.84794,  0.863035, 0.880003, 0.897676, 0.915862, 0.93515,
        0.956156, 0.978743, 1.00179,  1.02362,  1.0429,   1.05922,  1.07326,
        1.08624,  1.09925,  1.11277,  1.12627,  1.13771,  1.14663,  1.15282,
        1.15604,  1.15598,  1.15242,  1.14559,  1.13622,  1.12526,  1.11322,
        1.0998,   1.08412,  1.06568,  1.04509,  1.02428,  1.0055,   0.990111,
        0.9777,   0.966526, 0.954868, 0.942376, 0.930383, 0.920943, 0.915273,
        0.912768, 0.912022, 0.912369, 0.912666, 0.913179, 0.914858, 0.91811,
        0.922192, 0.925703, 0.927744, 0.928751, 0.930253, 0.933725, 0.939431,
        0.946214, 0.952445, 0.95739,  0.96191,  0.967868, 0.976661, 0.987989,
        0.999851, 1.00986,  1.01694,  1.02215,  1.02797,  1.03633,  1.04593,
        1.05532,  1.06259,  1.06658,  1.06761,  1.06711,  1.06649,  1.06632,
        1.06626,  1.06578,  1.06471,  1.06335,  1.06193,  1.06,     1.05648,
        1.05032,  1.04148,  1.03143,  1.0226,   1.01698,  1.0146,   1.01285,
        1.00722,  0.993211};

    size_t nx = sizeof(x) / sizeof(double);
    size_t ny = sizeof(y) / sizeof(double);

    TS_ASSERT_EQUALS(nx, ny + 1);

    do_test(nx, x, ny, y, e, ysmooth);
  }

  void test_small_dataset_odd() {
    double x[] = {2.27988, 2.5079,  2.73593, 2.96398, 3.19203, 3.4201,
                  3.64818, 3.87627, 4.10439, 4.33251, 4.56066, 4.78882,
                  5.017,   5.2452,  5.47342, 5.70167, 5.92994, 6.15823,
                  6.38654, 6.61488, 6.84325};
    double y[] = {0.1189,  0.14286, 0.15511, 0.20033, 0.24087, 0.2996,
                  0.3667,  0.45925, 0.54581, 0.64787, 0.72139, 0.75917,
                  0.7592,  0.70437, 0.66543, 0.61568, 0.57946, 0.56725,
                  0.54555, 0.54935, 0.55913};
    double e[] = {0.04306, 0.05999, 0.04333, 0.04134, 0.04024, 0.04153,
                  0.04734, 0.05491, 0.04546, 0.04019, 0.03919, 0.03947,
                  0.05077, 0.05629, 0.04336, 0.04067, 0.04076, 0.04336,
                  0.05906, 0.03617, 0.03875};
    double ysmooth[] = {
        0.119953, 0.138392, 0.158673, 0.197465, 0.242644, 0.300178, 0.369039,
        0.456804, 0.550945, 0.646607, 0.721446, 0.760649, 0.755715, 0.712672,
        0.664265, 0.616398, 0.583482, 0.563747, 0.548997, 0.548158, 0.555918};

    size_t nx = sizeof(x) / sizeof(double);
    size_t ny = sizeof(y) / sizeof(double);

    do_test(nx, x, ny, y, e, ysmooth);
  }

  void test_small_dataset_even() {
    double x[] = {2.27988, 2.5079,  2.73593, 2.96398, 3.19203, 3.4201, 3.64818,
                  3.87627, 4.10439, 4.33251, 4.56066, 4.78882, 5.017,  5.2452,
                  5.47342, 5.70167, 5.92994, 6.15823, 6.38654, 6.61488};
    double y[] = {0.1189,  0.14286, 0.15511, 0.20033, 0.24087, 0.2996, 0.3667,
                  0.45925, 0.54581, 0.64787, 0.72139, 0.75917, 0.7592, 0.70437,
                  0.66543, 0.61568, 0.57946, 0.56725, 0.54555, 0.54935};
    double e[] = {0.04306, 0.05999, 0.04333, 0.04134, 0.04024, 0.04153, 0.04734,
                  0.05491, 0.04546, 0.04019, 0.03919, 0.03947, 0.05077, 0.05629,
                  0.04336, 0.04067, 0.04076, 0.04336, 0.05906, 0.03617};
    double ysmooth[] = {0.116583, 0.136542, 0.161394, 0.195961, 0.240597,
                        0.300037, 0.371905, 0.453996, 0.552692, 0.645688,
                        0.721389, 0.761067, 0.751442, 0.709996, 0.661161,
                        0.616885, 0.581682, 0.561372, 0.547726, 0.549986};

    size_t nx = sizeof(x) / sizeof(double);
    size_t ny = sizeof(y) / sizeof(double);

    do_test(nx, x, ny, y, e, ysmooth);
  }

  void test_very_small_dataset() {
    double x[] = {2.27988, 2.5079, 2.73593};
    double y[] = {0.1189, 0.14286, 0.15511};
    double e[] = {0.04306, 0.05999, 0.04333};
    double ysmooth[] = {0.1189, 0.14286, 0.15511};

    size_t nx = sizeof(x) / sizeof(double);
    size_t ny = sizeof(y) / sizeof(double);

    do_test(nx, x, ny, y, e, ysmooth);
  }

  void test_smooth_all_spectra() {
    std::vector<int> wsIndexList;
    do_multispectra_test(wsIndexList);
  }

  void test_smooth_some_spectra() {
    std::vector<int> wsIndexList(3);
    wsIndexList[0] = 2;
    wsIndexList[1] = 1;
    wsIndexList[2] = 4;
    do_multispectra_test(wsIndexList);
  }

private:
  void do_test(size_t nx, double *x, size_t ny, double *y, double *e,
               double *ysmooth) {

    auto dataWS = WorkspaceFactory::Instance().create("Workspace2D", 1, nx, ny);
    auto &X = dataWS->dataX(0);
    auto &Y = dataWS->dataY(0);
    auto &E = dataWS->dataE(0);
    X.assign(x, x + nx);
    Y.assign(y, y + ny);
    E.assign(e, e + ny);

    std::vector<int> wsIndexList(1, 0);
    auto outputWs = runWienerSmooth(dataWS, wsIndexList);

    auto &outY = outputWs->readY(0);

    for (size_t i = 0; i < outY.size(); ++i) {
      TS_ASSERT_DELTA(outY[i], ysmooth[i], 1e-5);
      // std::cerr << outY[i] << '\n';
    }

    AnalysisDataService::Instance().clear();
  }

  void do_multispectra_test(const std::vector<int> &wsIndexList) {
    auto inputWS = createWorkspace();
    auto outputWS = runWienerSmooth(inputWS, wsIndexList);

    size_t nSpec = outputWS->getNumberHistograms();
    TS_ASSERT_EQUALS(outputWS->blocksize(), inputWS->blocksize());
    TS_ASSERT_EQUALS(outputWS->isHistogramData(), inputWS->isHistogramData());
    if (wsIndexList.empty()) {
      TS_ASSERT_EQUALS(nSpec, inputWS->getNumberHistograms());
    } else {
      TS_ASSERT_EQUALS(nSpec, wsIndexList.size());
    }

    for (size_t outSpec = 0; outSpec < nSpec; ++outSpec) {
      size_t inSpec = wsIndexList.empty() ? outSpec : wsIndexList[outSpec];
      auto &inY = inputWS->readY(inSpec);
      auto &outY = outputWS->readY(outSpec);
      TS_ASSERT(!std::equal(outY.begin(), outY.end(), inY.begin()));

      std::vector<double> diff(inY.size());
      std::transform(inY.begin(), inY.end(), outY.begin(), diff.begin(),
                     std::minus<double>());

      auto countPos = std::count_if(diff.begin(), diff.end(),
                                    std::bind2nd(std::greater<double>(), 0.0));
      auto countNeg = std::count_if(diff.begin(), diff.end(),
                                    std::bind2nd(std::less<double>(), 0.0));

      // the delta here is just a guess
      TS_ASSERT_DELTA(double(countPos) / double(countNeg), 1.0, 1e-1);
    }
  }

  MatrixWorkspace_sptr runWienerSmooth(MatrixWorkspace_sptr inputWS,
                                       const std::vector<int> &wsIndexList) {
    // Name of the output workspace.
    std::string outWSName("WienerSmoothTest_OutputWS");

    WienerSmooth alg;
    alg.setRethrows(true);
    TS_ASSERT_THROWS_NOTHING(alg.initialize())
    TS_ASSERT(alg.isInitialized())
    TS_ASSERT_THROWS_NOTHING(alg.setProperty("InputWorkspace", inputWS));
    TS_ASSERT_THROWS_NOTHING(
        alg.setProperty("WorkspaceIndexList", wsIndexList));
    TS_ASSERT_THROWS_NOTHING(
        alg.setPropertyValue("OutputWorkspace", outWSName));
    TS_ASSERT_THROWS_NOTHING(alg.execute(););
    TS_ASSERT(alg.isExecuted());

    // Retrieve the workspace from data service.
    MatrixWorkspace_sptr ws;
    TS_ASSERT_THROWS_NOTHING(
        ws = AnalysisDataService::Instance().retrieveWS<MatrixWorkspace>(
            outWSName));
    TS_ASSERT(ws);

    auto &inX = inputWS->readX(0);
    auto &inE = inputWS->readE(0);

    for (size_t i = 0; i < ws->getNumberHistograms(); ++i) {

      auto outX = ws->readX(i);
      auto outE = ws->readE(i);

      TS_ASSERT(std::equal(outX.begin(), outX.end(), inX.begin()));
      TS_ASSERT(std::equal(outE.begin(), outE.end(), inE.begin()));
    }

    return ws;
  }

  MatrixWorkspace_sptr createWorkspace() {
    double x[] = {2.27988, 2.5079,  2.73593, 2.96398, 3.19203, 3.4201, 3.64818,
                  3.87627, 4.10439, 4.33251, 4.56066, 4.78882, 5.017,  5.2452,
                  5.47342, 5.70167, 5.92994, 6.15823, 6.38654, 6.61488};
    double y[] = {0.1189,  0.14286, 0.15511, 0.20033, 0.24087, 0.2996, 0.3667,
                  0.45925, 0.54581, 0.64787, 0.72139, 0.75917, 0.7592, 0.70437,
                  0.66543, 0.61568, 0.57946, 0.56725, 0.54555, 0.54935};
    double e[] = {0.04306, 0.05999, 0.04333, 0.04134, 0.04024, 0.04153, 0.04734,
                  0.05491, 0.04546, 0.04019, 0.03919, 0.03947, 0.05077, 0.05629,
                  0.04336, 0.04067, 0.04076, 0.04336, 0.05906, 0.03617};

    size_t nx = sizeof(x) / sizeof(double);
    size_t ny = sizeof(y) / sizeof(double);

    const size_t nSpec = 5;

    auto dataWS =
        WorkspaceFactory::Instance().create("Workspace2D", nSpec, nx, ny);

    for (size_t i = 0; i < nSpec; ++i) {
      auto &X = dataWS->dataX(i);
      auto &Y = dataWS->dataY(i);
      auto &E = dataWS->dataE(i);
      X.assign(x, x + nx);
      Y.assign(y, y + ny);
      E.assign(e, e + ny);

      std::transform(Y.begin(), Y.end(), Y.begin(),
                     std::bind2nd(std::multiplies<double>(), double(i + 1)));
    }

    return dataWS;
  }
};

#endif /* MANTID_ALGORITHMS_WIENERSMOOTHTEST_H_ */
