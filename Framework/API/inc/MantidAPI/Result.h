// Mantid Repository : https://github.com/mantidproject/mantid
//
// Copyright &copy; 2023 ISIS Rutherford Appleton Laboratory UKRI,
//   NScD Oak Ridge National Laboratory, European Spallation Source,
//   Institut Laue - Langevin & CSNS, Institute of High Energy Physics, CAS
// SPDX - License - Identifier: GPL - 3.0 +
#pragma once

#include <string>

namespace Mantid {
namespace API {

template <typename T> class MANTID_API_DLL Result {
public:
  Result(T result, std::string errors = "") : m_result(result), m_errors(errors) {}

  // accessors
  inline const T &result() const { return m_result; }
  inline const std::string &errors() const { return m_errors; }

  // boolean conversion so you can use it directly in an if
  operator bool() const { return m_errors.empty(); }

private:
  T m_result;
  std::string m_errors;
};
} // namespace API
} // namespace Mantid
