// Mantid Repository : https://github.com/mantidproject/mantid
//
// Copyright &copy; 2018 ISIS Rutherford Appleton Laboratory UKRI,
//   NScD Oak Ridge National Laboratory, European Spallation Source,
//   Institut Laue - Langevin & CSNS, Institute of High Energy Physics, CAS
// SPDX - License - Identifier: GPL - 3.0 +
#pragma once

#include "DllConfig.h"
#include "MantidAPI/IFunction_fwd.h"
#include "MantidAPI/ITableWorkspace_fwd.h"
#include "MantidQtWidgets/Common/EditLocalParameterDialog.h"
#include "MantidQtWidgets/Common/FunctionModelDataset.h"
#include "MantidQtWidgets/Common/IndexTypes.h"
#include "ParameterEstimation.h"

#include <QList>
#include <QPair>
#include <QString>
#include <QWidget>

class QtBoolPropertyManager;
class QtIntPropertyManager;
class QtDoublePropertyManager;
class QtStringPropertyManager;
class QtEnumPropertyManager;
class QtGroupPropertyManager;
class ParameterPropertyManager;
class QtTreePropertyBrowser;
class QtProperty;

namespace MantidQt {
namespace CustomInterfaces {
namespace IDA {

using namespace Mantid::API;
using namespace MantidWidgets;

class ITemplatePresenter;

/**
 * Class FunctionTemplateBrowser implements QtPropertyBrowser to display
 * and set properties that can be used to generate a fit function.
 *
 */
class MANTIDQT_INELASTIC_DLL FunctionTemplateBrowser : public QWidget {
  Q_OBJECT
public:
  FunctionTemplateBrowser(QWidget *parent = nullptr);
  virtual ~FunctionTemplateBrowser();
  void init();
  void subscribePresenter(ITemplatePresenter *presenter);

  void setEnumSilent(QtProperty *prop, int fitType);
  void setIntSilent(QtProperty *prop, int value);
  void setBoolSilent(QtProperty *prop, bool value);
  void setParameterSilent(QtProperty *prop, double value, double error);
  void setErrorsEnabled(bool enabled);

  void setFunction(std::string const &funStr);
  IFunction_sptr getGlobalFunction() const;
  IFunction_sptr getFunction() const;

  int getCurrentDataset();
  void setCurrentDataset(int i);
  void setNumberOfDatasets(int);
  int getNumberOfDatasets() const;
  void setDatasets(const QList<MantidWidgets::FunctionModelDataset> &datasets);

  std::vector<std::string> getGlobalParameters() const;
  std::vector<std::string> getLocalParameters() const;
  void setGlobalParameters(std::vector<std::string> const &globals);

  void updateMultiDatasetParameters(const IFunction &fun);
  virtual void updateMultiDatasetParameters(const ITableWorkspace &paramTable) = 0;
  virtual void updateParameters(const IFunction &fun) = 0;
  virtual void updateParameterNames(const QMap<int, std::string> &parameterNames) = 0;

  virtual void clear() = 0;
  virtual EstimationDataSelector getEstimationDataSelector() const = 0;
  virtual void updateParameterEstimationData(DataForParameterEstimationCollection &&data) = 0;
  virtual void estimateFunctionParameters() = 0;
  virtual void setBackgroundA0(double value) = 0;
  virtual void setResolution(const std::vector<std::pair<std::string, size_t>> &fitResolutions) = 0;
  virtual void setQValues(const std::vector<double> &qValues) = 0;

  void emitFunctionStructureChanged() { emit functionStructureChanged(); }

  void openEditLocalParameterDialog(std::string const &parameterName, QStringList const &datasetNames,
                                    QStringList const &domainNames, QList<double> const &values,
                                    QList<bool> const &fixes, QStringList const &ties, QStringList const &constraints);

signals:
  void functionStructureChanged();

protected slots:
  virtual void intChanged(QtProperty *) {}
  virtual void boolChanged(QtProperty *) {}
  virtual void enumChanged(QtProperty *) {}
  virtual void popupMenu(const QPoint &) = 0;
  virtual void globalChanged(QtProperty *, const QString &, bool) = 0;
  virtual void parameterChanged(QtProperty *) = 0;
  void parameterButtonClicked(QtProperty *);
  void editLocalParameterFinished(int result);

private:
  void createBrowser();
  virtual void createProperties() = 0;

protected:
  bool m_emitParameterValueChange = true;
  bool m_emitBoolChange = true;
  bool m_emitEnumChange = true;
  bool m_emitIntChange = true;

  QtBoolPropertyManager *m_boolManager;
  QtIntPropertyManager *m_intManager;
  QtDoublePropertyManager *m_doubleManager;
  QtStringPropertyManager *m_stringManager;
  QtEnumPropertyManager *m_enumManager;
  QtGroupPropertyManager *m_groupManager;
  ParameterPropertyManager *m_parameterManager;

  QMap<QtProperty *, std::string> m_parameterNames;

  /// Qt property browser which displays properties
  QtTreePropertyBrowser *m_browser;

  /// Precision of doubles in m_doubleManager
  const int m_decimals;

  /// The corresponding template presenter
  ITemplatePresenter *m_presenter;

  /// The Edit local parameter dialog
  EditLocalParameterDialog *m_editLocalParameterDialog;
};

} // namespace IDA
} // namespace CustomInterfaces
} // namespace MantidQt
