#include "MantidGeometry/Crystal/PointGroup.h"
#include "MantidKernel/System.h"

#include <set>
#include <boost/make_shared.hpp>
#include <iostream>

#include "MantidGeometry/Crystal/PointGroupFactory.h"
#include "MantidGeometry/Crystal/SymmetryOperationFactory.h"

namespace Mantid {
namespace Geometry {
using Kernel::V3D;
using Kernel::IntMatrix;

/**
 * Returns all equivalent reflections for the supplied hkl.
 *
 * This method returns a vector containing all equivalent hkls for the supplied
 * one. It depends on the internal state of the pointgroup object (e.g. which
 * symmetry operations and therefore, which transformation matrices are
 * present). This internal state is unique for each concrete point group and
 * is set in the constructor.
 *
 * The returned vector always contains a set of unique hkls, so for special hkls
 * like (100), it has fewer entries than for a general hkl. See also
 * PointGroup::getEquivalentSet.
 *
 * @param hkl :: Arbitrary hkl
 * @return :: std::vector containing all equivalent hkls.
 */
std::vector<V3D> PointGroup::getEquivalents(const V3D &hkl) const {
  std::set<V3D> equivalents = getEquivalentSet(hkl);

  return std::vector<V3D>(equivalents.rbegin(), equivalents.rend());
}

/**
 * Returns the same V3D for all equivalent hkls.
 *
 * This method is closely related to PointGroup::getEquivalents. It returns the
 * same V3D for all hkls of one "family". For example in a cubic point group
 * it will return (100) for (001), (010), (0-10), etc.
 *
 * It can be used to generate a set of symmetry independent hkls, useful for
 * example in powder diffraction.
 *
 * @param hkl :: Arbitrary hkl
 * @return :: hkl specific to a family of index-triplets
 */
V3D PointGroup::getReflectionFamily(const Kernel::V3D &hkl) const {
  return *getEquivalentSet(hkl).rbegin();
}

bool PointGroup::groupHasNoTranslations(const Group &group) const {
  const std::vector<SymmetryOperation> &symOps = group.getSymmetryOperations();

  for (auto op = symOps.begin(); op != symOps.end(); ++op) {
    if ((*op).hasTranslation()) {
      return false;
    }
  }

  return true;
}

/// Protected constructor - can not be used directly.
PointGroup::PointGroup(const std::string &symbolHM, const Group &group,
                       const std::string &name)
    : Group(group), m_symbolHM(symbolHM), m_name(name) {}

PointGroup::PointGroup(const PointGroup &other)
    : Group(other), m_symbolHM(other.m_symbolHM), m_name(other.m_name) {}

PointGroup &PointGroup::operator=(const PointGroup &other) {
  Group::operator=(other);

  m_symbolHM = other.m_symbolHM;
  m_name = other.m_name;

  return *this;
}

/// Hermann-Mauguin symbol
std::string PointGroup::getSymbol() const { return m_symbolHM; }

bool PointGroup::isEquivalent(const Kernel::V3D &hkl,
                              const Kernel::V3D &hkl2) const {
  std::set<V3D> hklEquivalents = getEquivalentSet(hkl);

  return (hklEquivalents.find(hkl2) != hklEquivalents.end());
}

/**
 * Generates a set of hkls
 *
 * This method applies all transformation matrices to the supplied hkl and puts
 * it into a set, which is returned in the end. Using a set ensures that each
 * hkl occurs once and only once. This set is the set of equivalent hkls,
 * specific to a concrete point group.
 *
 * The symmetry operations need to be set prior to calling this method by a call
 * to PointGroup::setTransformationMatrices.
 *
 * @param hkl :: Arbitrary hkl
 * @return :: set of hkls.
 */
std::set<V3D> PointGroup::getEquivalentSet(const Kernel::V3D &hkl) const {
  std::set<V3D> equivalents;

  const std::vector<SymmetryOperation> &symmetryOperations =
      getSymmetryOperations();

  for (auto op = symmetryOperations.begin(); op != symmetryOperations.end();
       ++op) {
    equivalents.insert((*op) * hkl);
  }

  return equivalents;
}

/*
PointGroupLaue1::PointGroupLaue1() : PointGroup("-1") {}

std::string PointGroupLaue1::getName() const { return "-1 (Triclinic)"; }

bool PointGroupLaue1::isEquivalent(const V3D &hkl, const V3D &hkl2) const {
  double h = hkl[0];
  double k = hkl[1];
  double l = hkl[2];

  return (hkl2 == V3D(h, k, l)) || (hkl2 == V3D(-h, -k, -l));
}

PointGroup::CrystalSystem PointGroupLaue1::crystalSystem() const {
  return Triclinic;
}

void PointGroupLaue1::init() {
  std::vector<SymmetryOperation> generatingSymmetryOperations;
  generatingSymmetryOperations.push_back(
      SymmetryOperationFactory::Instance().createSymOp("-x,-y,-z"));

  setSymmetryOperations(generatingSymmetryOperations);
}

PointGroupLaue2::PointGroupLaue2() : PointGroup("2/m") {}

std::string PointGroupLaue2::getName() const {
  return "1 2/m 1 (Monoclinic, unique axis b)";
}

bool PointGroupLaue2::isEquivalent(const V3D &hkl, const V3D &hkl2) const {
  double h = hkl[0];
  double k = hkl[1];
  double l = hkl[2];

  return (hkl2 == V3D(h, k, l)) || (hkl2 == V3D(-h, -k, -l)) ||
         (hkl2 == V3D(-h, k, -l)) || (hkl2 == V3D(h, -k, l));
}

PointGroup::CrystalSystem PointGroupLaue2::crystalSystem() const {
  return Monoclinic;
}

void PointGroupLaue2::init() {
  std::vector<SymmetryOperation> generatingSymmetryOperations;
  generatingSymmetryOperations.push_back(
      SymmetryOperationFactory::Instance().createSymOp("-x,y,-z"));
  generatingSymmetryOperations.push_back(
      SymmetryOperationFactory::Instance().createSymOp("x,-y,z"));

  setSymmetryOperations(generatingSymmetryOperations);
}

PointGroupLaue3::PointGroupLaue3() : PointGroup("112/m") {}

std::string PointGroupLaue3::getName() const {
  return "1 1 2/m (Monoclinic, unique axis c)";
}

bool PointGroupLaue3::isEquivalent(const V3D &hkl, const V3D &hkl2) const {
  double h = hkl[0];
  double k = hkl[1];
  double l = hkl[2];

  return (hkl2 == V3D(h, k, l)) || (hkl2 == V3D(-h, -k, l)) ||
         (hkl2 == V3D(-h, -k, -l)) || (hkl2 == V3D(h, k, -l));
}

PointGroup::CrystalSystem PointGroupLaue3::crystalSystem() const {
  return Monoclinic;
}

void PointGroupLaue3::init() {
  std::vector<SymmetryOperation> generatingSymmetryOperations;
  generatingSymmetryOperations.push_back(
      SymmetryOperationFactory::Instance().createSymOp("-x,-y,z"));
  generatingSymmetryOperations.push_back(
      SymmetryOperationFactory::Instance().createSymOp("x,y,-z"));

  setSymmetryOperations(generatingSymmetryOperations);
}

PointGroupLaue4::PointGroupLaue4() : PointGroup("mmm") {}

std::string PointGroupLaue4::getName() const { return "mmm (Orthorombic)"; }

bool PointGroupLaue4::isEquivalent(const V3D &hkl, const V3D &hkl2) const {
  double h = hkl[0];
  double k = hkl[1];
  double l = hkl[2];

  return (hkl2 == V3D(h, k, l)) || (hkl2 == V3D(-h, -k, l)) ||
         (hkl2 == V3D(-h, k, -l)) || (hkl2 == V3D(h, -k, -l)) ||
         (hkl2 == V3D(-h, -k, -l)) || (hkl2 == V3D(h, k, -l)) ||
         (hkl2 == V3D(h, -k, l)) || (hkl2 == V3D(-h, k, l));
}

PointGroup::CrystalSystem PointGroupLaue4::crystalSystem() const {
  return Orthorhombic;
}

void PointGroupLaue4::init() {
  std::vector<SymmetryOperation> generatingSymmetryOperations;
  generatingSymmetryOperations.push_back(
      SymmetryOperationFactory::Instance().createSymOp("x,-y,-z"));
  generatingSymmetryOperations.push_back(
      SymmetryOperationFactory::Instance().createSymOp("-x,y,-z"));
  generatingSymmetryOperations.push_back(
      SymmetryOperationFactory::Instance().createSymOp("x,y,-z"));

  setSymmetryOperations(generatingSymmetryOperations);
}

PointGroupLaue5::PointGroupLaue5() : PointGroup("4/m") {}

std::string PointGroupLaue5::getName() const { return "4/m (Tetragonal)"; }

bool PointGroupLaue5::isEquivalent(const V3D &hkl, const V3D &hkl2) const {
  double h = hkl[0];
  double k = hkl[1];
  double l = hkl[2];

  return (hkl2 == V3D(h, k, l)) || (hkl2 == V3D(-h, -k, l)) ||
         (hkl2 == V3D(-k, h, l)) || (hkl2 == V3D(k, -h, l)) ||
         (hkl2 == V3D(-h, -k, -l)) || (hkl2 == V3D(h, k, -l)) ||
         (hkl2 == V3D(k, -h, -l)) || (hkl2 == V3D(-k, h, -l));
}

PointGroup::CrystalSystem PointGroupLaue5::crystalSystem() const {
  return Tetragonal;
}

void PointGroupLaue5::init() {
  std::vector<SymmetryOperation> generatingSymmetryOperations;
  generatingSymmetryOperations.push_back(
      SymmetryOperationFactory::Instance().createSymOp("-y,x,z"));
  generatingSymmetryOperations.push_back(
      SymmetryOperationFactory::Instance().createSymOp("x,y,-z"));

  setSymmetryOperations(generatingSymmetryOperations);
}

PointGroupLaue6::PointGroupLaue6() : PointGroup("4/mmm") {}

std::string PointGroupLaue6::getName() const { return "4/mmm (Tetragonal)"; }

bool PointGroupLaue6::isEquivalent(const V3D &hkl, const V3D &hkl2) const {
  double h = hkl[0];
  double k = hkl[1];
  double l = hkl[2];

  return (hkl2 == V3D(h, k, l)) || (hkl2 == V3D(-h, -k, l)) ||
         (hkl2 == V3D(-k, h, l)) || (hkl2 == V3D(k, -h, l)) ||
         (hkl2 == V3D(-h, k, -l)) || (hkl2 == V3D(h, -k, -l)) ||
         (hkl2 == V3D(k, h, -l)) || (hkl2 == V3D(-k, -h, -l)) ||
         (hkl2 == V3D(-h, -k, -l)) || (hkl2 == V3D(h, k, -l)) ||
         (hkl2 == V3D(k, -h, -l)) || (hkl2 == V3D(-k, h, -l)) ||
         (hkl2 == V3D(h, -k, l)) || (hkl2 == V3D(-h, k, l)) ||
         (hkl2 == V3D(-k, -h, l)) || (hkl2 == V3D(k, h, l));
}

PointGroup::CrystalSystem PointGroupLaue6::crystalSystem() const {
  return Tetragonal;
}

void PointGroupLaue6::init() {
  std::vector<SymmetryOperation> generatingSymmetryOperations;
  generatingSymmetryOperations.push_back(
      SymmetryOperationFactory::Instance().createSymOp("-y,x,z"));
  generatingSymmetryOperations.push_back(
      SymmetryOperationFactory::Instance().createSymOp("x,y,-z"));
  generatingSymmetryOperations.push_back(
      SymmetryOperationFactory::Instance().createSymOp("x,-y,-z"));

  setSymmetryOperations(generatingSymmetryOperations);
}

PointGroupLaue7::PointGroupLaue7() : PointGroup("-3") {}

std::string PointGroupLaue7::getName() const {
  return "-3 (Trigonal - Hexagonal)";
}

bool PointGroupLaue7::isEquivalent(const V3D &hkl, const V3D &hkl2) const {
  double h = hkl[0];
  double k = hkl[1];
  double l = hkl[2];

  return (hkl2 == V3D(h, k, l)) || (hkl2 == V3D(-k, h - k, l)) ||
         (hkl2 == V3D(-h + k, -h, l)) || (hkl2 == V3D(-h, -k, -l)) ||
         (hkl2 == V3D(k, -h + k, -l)) || (hkl2 == V3D(h - k, h, -l));
}

PointGroup::CrystalSystem PointGroupLaue7::crystalSystem() const {
  return Trigonal;
}

void PointGroupLaue7::init() {
  std::vector<SymmetryOperation> generatingSymmetryOperations;
  generatingSymmetryOperations.push_back(
      SymmetryOperationFactory::Instance().createSymOp("-y,x-y,z"));
  generatingSymmetryOperations.push_back(
      SymmetryOperationFactory::Instance().createSymOp("-x,-y,-z"));

  setSymmetryOperations(generatingSymmetryOperations);
}

PointGroupLaue8::PointGroupLaue8() : PointGroup("-3m1") {}

std::string PointGroupLaue8::getName() const {
  return "-3m1 (Trigonal - Rhombohedral)";
}

bool PointGroupLaue8::isEquivalent(const V3D &hkl, const V3D &hkl2) const {
  double h = hkl[0];
  double k = hkl[1];
  double l = hkl[2];

  return (hkl2 == V3D(h, k, l)) || (hkl2 == V3D(-k, h - k, l)) ||
         (hkl2 == V3D(-h + k, -h, l)) || (hkl2 == V3D(-k, -h, -l)) ||
         (hkl2 == V3D(-h + k, k, -l)) || (hkl2 == V3D(h, h - k, -l)) ||
         (hkl2 == V3D(-h, -k, -l)) || (hkl2 == V3D(k, -h + k, -l)) ||
         (hkl2 == V3D(h - k, h, -l)) || (hkl2 == V3D(k, h, l)) ||
         (hkl2 == V3D(h - k, -k, l)) || (hkl2 == V3D(-h, -h + k, l));
}

PointGroup::CrystalSystem PointGroupLaue8::crystalSystem() const {
  return Trigonal;
}

void PointGroupLaue8::init() {
  std::vector<SymmetryOperation> generatingSymmetryOperations;
  generatingSymmetryOperations.push_back(
      SymmetryOperationFactory::Instance().createSymOp("-y,x-y,z"));
  generatingSymmetryOperations.push_back(
      SymmetryOperationFactory::Instance().createSymOp("-x,-y,-z"));
  generatingSymmetryOperations.push_back(
      SymmetryOperationFactory::Instance().createSymOp("-x,y-x,z"));

  setSymmetryOperations(generatingSymmetryOperations);
}

PointGroupLaue9::PointGroupLaue9() : PointGroup("-31m") {}

std::string PointGroupLaue9::getName() const {
  return "-31m (Trigonal - Rhombohedral)";
}

bool PointGroupLaue9::isEquivalent(const V3D &hkl, const V3D &hkl2) const {
  double h = hkl[0];
  double k = hkl[1];
  double l = hkl[2];

  return (hkl2 == V3D(h, k, l)) || (hkl2 == V3D(-k, h - k, l)) ||
         (hkl2 == V3D(-h + k, -h, l)) || (hkl2 == V3D(-k, -h, -l)) ||
         (hkl2 == V3D(-h + k, k, -l)) || (hkl2 == V3D(h, h - k, -l)) ||
         (hkl2 == V3D(-h, -k, -l)) || (hkl2 == V3D(k, -h + k, -l)) ||
         (hkl2 == V3D(h - k, h, -l)) || (hkl2 == V3D(k, h, l)) ||
         (hkl2 == V3D(h - k, -k, l)) || (hkl2 == V3D(-h, -h + k, l));
}

PointGroup::CrystalSystem PointGroupLaue9::crystalSystem() const {
  return Trigonal;
}

void PointGroupLaue9::init() {
  std::vector<SymmetryOperation> generatingSymmetryOperations;
  generatingSymmetryOperations.push_back(
      SymmetryOperationFactory::Instance().createSymOp("-y,x-y,z"));
  generatingSymmetryOperations.push_back(
      SymmetryOperationFactory::Instance().createSymOp("-x,-y,-z"));
  generatingSymmetryOperations.push_back(
      SymmetryOperationFactory::Instance().createSymOp("-x,y-x,z"));

  setSymmetryOperations(generatingSymmetryOperations);
}

PointGroupLaue10::PointGroupLaue10() : PointGroup("6/m") {}

std::string PointGroupLaue10::getName() const { return "6/m (Hexagonal)"; }

bool PointGroupLaue10::isEquivalent(const V3D &hkl, const V3D &hkl2) const {
  double h = hkl[0];
  double k = hkl[1];
  double l = hkl[2];

  return (hkl2 == V3D(h, k, l)) || (hkl2 == V3D(-k, h - k, l)) ||
         (hkl2 == V3D(-h + k, -h, l)) || (hkl2 == V3D(-h, -k, l)) ||
         (hkl2 == V3D(k, -h + k, l)) || (hkl2 == V3D(h - k, h, l)) ||
         (hkl2 == V3D(-h, -k, -l)) || (hkl2 == V3D(k, -h + k, -l)) ||
         (hkl2 == V3D(h - k, h, -l)) || (hkl2 == V3D(h, k, -l)) ||
         (hkl2 == V3D(-k, h - k, -l)) || (hkl2 == V3D(-h + k, -h, -l));
}

PointGroup::CrystalSystem PointGroupLaue10::crystalSystem() const {
  return Hexagonal;
}

void PointGroupLaue10::init() {
  std::vector<SymmetryOperation> generatingSymmetryOperations;
  generatingSymmetryOperations.push_back(
      SymmetryOperationFactory::Instance().createSymOp("x-y,x,z"));
  generatingSymmetryOperations.push_back(
      SymmetryOperationFactory::Instance().createSymOp("-x,-y,-z"));

  setSymmetryOperations(generatingSymmetryOperations);
}

PointGroupLaue11::PointGroupLaue11() : PointGroup("6/mmm") {}

std::string PointGroupLaue11::getName() const { return "6/mmm (Hexagonal)"; }

bool PointGroupLaue11::isEquivalent(const V3D &hkl, const V3D &hkl2) const {
  double h = hkl[0];
  double k = hkl[1];
  double l = hkl[2];

  return (hkl2 == V3D(h, k, l)) || (hkl2 == V3D(-k, h - k, l)) ||
         (hkl2 == V3D(-h + k, -h, l)) || (hkl2 == V3D(-h, -k, l)) ||
         (hkl2 == V3D(k, -h + k, l)) || (hkl2 == V3D(h - k, h, l)) ||
         (hkl2 == V3D(k, h, -l)) || (hkl2 == V3D(h - k, -k, -l)) ||
         (hkl2 == V3D(-h, -h + k, -l)) || (hkl2 == V3D(-k, -h, -l)) ||
         (hkl2 == V3D(-h + k, k, -l)) || (hkl2 == V3D(h, h - k, -l)) ||
         (hkl2 == V3D(-h, -k, -l)) || (hkl2 == V3D(k, -h + k, -l)) ||
         (hkl2 == V3D(h - k, h, -l)) || (hkl2 == V3D(h, k, -l)) ||
         (hkl2 == V3D(-k, h - k, -l)) || (hkl2 == V3D(-h + k, -h, -l)) ||
         (hkl2 == V3D(-k, -h, l)) || (hkl2 == V3D(-h + k, k, l)) ||
         (hkl2 == V3D(h, h - k, l)) || (hkl2 == V3D(k, h, l)) ||
         (hkl2 == V3D(h - k, -k, l)) || (hkl2 == V3D(-h, -h + k, l));
}

PointGroup::CrystalSystem PointGroupLaue11::crystalSystem() const {
  return Hexagonal;
}

void PointGroupLaue11::init() {
  std::vector<SymmetryOperation> generatingSymmetryOperations;
  generatingSymmetryOperations.push_back(
      SymmetryOperationFactory::Instance().createSymOp("x-y,x,z"));
  generatingSymmetryOperations.push_back(
      SymmetryOperationFactory::Instance().createSymOp("x-y,-y,-z"));
  generatingSymmetryOperations.push_back(
      SymmetryOperationFactory::Instance().createSymOp("x,y,-z"));

  setSymmetryOperations(generatingSymmetryOperations);
}

PointGroupLaue12::PointGroupLaue12() : PointGroup("m-3") {}

std::string PointGroupLaue12::getName() const { return "m-3 (Cubic)"; }

bool PointGroupLaue12::isEquivalent(const V3D &hkl, const V3D &hkl2) const {
  double h = hkl[0];
  double k = hkl[1];
  double l = hkl[2];

  return (hkl2 == V3D(h, k, l)) || (hkl2 == V3D(-h, -k, l)) ||
         (hkl2 == V3D(-h, k, -l)) || (hkl2 == V3D(h, -k, -l)) ||
         (hkl2 == V3D(l, h, k)) || (hkl2 == V3D(l, -h, -k)) ||
         (hkl2 == V3D(-l, -h, k)) || (hkl2 == V3D(-l, h, -k)) ||
         (hkl2 == V3D(k, l, h)) || (hkl2 == V3D(-k, l, -h)) ||
         (hkl2 == V3D(k, -l, -h)) || (hkl2 == V3D(-k, -l, h)) ||
         (hkl2 == V3D(-h, -k, -l)) || (hkl2 == V3D(h, k, -l)) ||
         (hkl2 == V3D(h, -k, l)) || (hkl2 == V3D(-h, k, l)) ||
         (hkl2 == V3D(-l, -h, -k)) || (hkl2 == V3D(-l, h, k)) ||
         (hkl2 == V3D(l, h, -k)) || (hkl2 == V3D(l, -h, k)) ||
         (hkl2 == V3D(-k, -l, -h)) || (hkl2 == V3D(k, -l, h)) ||
         (hkl2 == V3D(-k, l, h)) || (hkl2 == V3D(k, l, -h));
}

PointGroup::CrystalSystem PointGroupLaue12::crystalSystem() const {
  return Cubic;
}

void PointGroupLaue12::init() {
  std::vector<SymmetryOperation> generatingSymmetryOperations;
  generatingSymmetryOperations.push_back(
      SymmetryOperationFactory::Instance().createSymOp("z,x,y"));
  generatingSymmetryOperations.push_back(
      SymmetryOperationFactory::Instance().createSymOp("-x,-y,z"));
  generatingSymmetryOperations.push_back(
      SymmetryOperationFactory::Instance().createSymOp("x,-y,z"));
  generatingSymmetryOperations.push_back(
      SymmetryOperationFactory::Instance().createSymOp("-x,-y,-z"));

  setSymmetryOperations(generatingSymmetryOperations);
}

PointGroupLaue13::PointGroupLaue13() : PointGroup("m-3m") {}

std::string PointGroupLaue13::getName() const { return "m-3m (Cubic)"; }

bool PointGroupLaue13::isEquivalent(const V3D &hkl, const V3D &hkl2) const {
  double h = hkl[0];
  double k = hkl[1];
  double l = hkl[2];

  return (hkl2 == V3D(h, k, l)) || (hkl2 == V3D(-h, -k, l)) ||
         (hkl2 == V3D(-h, k, -l)) || (hkl2 == V3D(h, -k, -l)) ||
         (hkl2 == V3D(l, h, k)) || (hkl2 == V3D(l, -h, -k)) ||
         (hkl2 == V3D(-l, -h, k)) || (hkl2 == V3D(-l, h, -k)) ||
         (hkl2 == V3D(k, l, h)) || (hkl2 == V3D(-k, l, -h)) ||
         (hkl2 == V3D(k, -l, -h)) || (hkl2 == V3D(-k, -l, h)) ||
         (hkl2 == V3D(k, h, -l)) || (hkl2 == V3D(-k, -h, -l)) ||
         (hkl2 == V3D(k, -h, l)) || (hkl2 == V3D(-k, h, l)) ||
         (hkl2 == V3D(h, l, -k)) || (hkl2 == V3D(-h, l, k)) ||
         (hkl2 == V3D(-h, -l, -k)) || (hkl2 == V3D(h, -l, k)) ||
         (hkl2 == V3D(l, k, -h)) || (hkl2 == V3D(l, -k, h)) ||
         (hkl2 == V3D(-l, k, h)) || (hkl2 == V3D(-l, -k, -h)) ||
         (hkl2 == V3D(-h, -k, -l)) || (hkl2 == V3D(h, k, -l)) ||
         (hkl2 == V3D(h, -k, l)) || (hkl2 == V3D(-h, k, l)) ||
         (hkl2 == V3D(-l, -h, -k)) || (hkl2 == V3D(-l, h, k)) ||
         (hkl2 == V3D(l, h, -k)) || (hkl2 == V3D(l, -h, k)) ||
         (hkl2 == V3D(-k, -l, -h)) || (hkl2 == V3D(k, -l, h)) ||
         (hkl2 == V3D(-k, l, h)) || (hkl2 == V3D(k, l, -h)) ||
         (hkl2 == V3D(-k, -h, l)) || (hkl2 == V3D(k, h, l)) ||
         (hkl2 == V3D(-k, h, -l)) || (hkl2 == V3D(k, -h, -l)) ||
         (hkl2 == V3D(-h, -l, k)) || (hkl2 == V3D(h, -l, -k)) ||
         (hkl2 == V3D(h, l, k)) || (hkl2 == V3D(-h, l, -k)) ||
         (hkl2 == V3D(-l, -k, h)) || (hkl2 == V3D(-l, k, -h)) ||
         (hkl2 == V3D(l, -k, -h)) || (hkl2 == V3D(l, k, h));
}

PointGroup::CrystalSystem PointGroupLaue13::crystalSystem() const {
  return Cubic;
}

void PointGroupLaue13::init() {
  std::vector<SymmetryOperation> generatingSymmetryOperations;
  generatingSymmetryOperations.push_back(
      SymmetryOperationFactory::Instance().createSymOp("z,x,y"));
  generatingSymmetryOperations.push_back(
      SymmetryOperationFactory::Instance().createSymOp("-y,x,z"));
  generatingSymmetryOperations.push_back(
      SymmetryOperationFactory::Instance().createSymOp("x,-y,z"));
  generatingSymmetryOperations.push_back(
      SymmetryOperationFactory::Instance().createSymOp("-x,-y,-z"));

  setSymmetryOperations(generatingSymmetryOperations);
}
*/
/** @return a vector with all possible PointGroup objects */
std::vector<PointGroup_sptr> getAllPointGroups() {
  std::vector<std::string> allSymbols =
      PointGroupFactory::Instance().getAllPointGroupSymbols();

  std::vector<PointGroup_sptr> out;
  for (auto it = allSymbols.begin(); it != allSymbols.end(); ++it) {
    out.push_back(PointGroupFactory::Instance().createPointGroup(*it));
  }

  return out;
}

PointGroupCrystalSystemMap getPointGroupsByCrystalSystem() {
  PointGroupCrystalSystemMap map;

  std::vector<PointGroup_sptr> pointGroups = getAllPointGroups();
  for (size_t i = 0; i < pointGroups.size(); ++i) {
    map.insert(std::make_pair(pointGroups[i]->crystalSystem(), pointGroups[i]));
  }

  return map;
}

/*
DECLARE_POINTGROUP(PointGroupLaue1)
DECLARE_POINTGROUP(PointGroupLaue2)
DECLARE_POINTGROUP(PointGroupLaue3)
DECLARE_POINTGROUP(PointGroupLaue4)
DECLARE_POINTGROUP(PointGroupLaue5)
DECLARE_POINTGROUP(PointGroupLaue6)
DECLARE_POINTGROUP(PointGroupLaue7)
DECLARE_POINTGROUP(PointGroupLaue8)
DECLARE_POINTGROUP(PointGroupLaue9)
DECLARE_POINTGROUP(PointGroupLaue10)
DECLARE_POINTGROUP(PointGroupLaue11)
DECLARE_POINTGROUP(PointGroupLaue12)
DECLARE_POINTGROUP(PointGroupLaue13)
*/
} // namespace Mantid
} // namespace Geometry
