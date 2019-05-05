//
// Copyright (C) 2019 by the adcc authors
//
// This file is part of adcc.
//
// adcc is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// adcc is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with adcc. If not, see <http://www.gnu.org/licenses/>.
//

#include <adcc/MoSpaces.hh>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace adcc {
namespace py_iface {

namespace py = pybind11;

void export_MoSpaces(py::module& m) {
  py::class_<MoSpaces, std::shared_ptr<MoSpaces>>(
        m, "MoSpaces",
        "Class setting up the molecular orbital index spaces and subspaces and exposing "
        "information about them.")
        .def(py::init<const HartreeFockSolution_i&, size_t, std::vector<size_t>,
                      std::vector<size_t>, std::vector<size_t>>(),
             "Construct an MoSpaces object from a HartreeFockSolution_i and a maximal "
             "block\n"
             "size to be used for the tensors and three list parameters:\n"
             "\n"
             "core_orbitals     List of orbitals indices (in the full fock space, "
             "original\n"
             "                  ordering of the hf object), which defines the orbitals "
             "to\n"
             "                  be put into the core space, if any. The same number\n"
             "                  of alpha and beta orbitals should be selected. These "
             "will\n"
             "                  be forcibly occupied.\n"
             "frozen_core_orbitals\n"
             "                  List of orbital indices, which define the frozen core,\n"
             "                  i.e. those occupied orbitals, which do not take part in\n"
             "                  the ADC calculation. The same number of alpha and beta\n"
             "                  orbitals has to be selected.\n"
             "frozen_virtuals    List of orbital indices, which the frozen virtuals,\n"
             "                  i.e. those virtual orbitals, which do not take part\n"
             "                  in the ADC calculation. The same number of alpha and "
             "beta\n"
             "                  orbitals has to be selected.\n")
        //
        .def("n_orbs", &MoSpaces::n_orbs,
             "The number of orbitals in a particular orbital subspace")
        .def("n_orbs_alpha", &MoSpaces::n_orbs_alpha,
             "The number of alpha orbitals in a particular orbital subspace")
        .def("n_orbs_beta", &MoSpaces::n_orbs_beta,
             "The number of beta orbitals in a particular orbital subspace")
        //
        .def_readonly("point_group", &MoSpaces::point_group,
                      "The name of the point group for which the data in this "
                      "class has been set up.")
        .def_readonly("irreps", &MoSpaces::irreps,
                      "The irreducible representations in the point group to "
                      "which this class has been set up.")
        .def_readonly("subspaces", &MoSpaces::subspaces,
                      "The list of all orbital subspaces known to this object.")
        .def_readonly("subspaces_occupied", &MoSpaces::subspaces_occupied,
                      "The list of occupied orbital subspaces known to this object.")
        .def_readonly("subspaces_virtual", &MoSpaces::subspaces_virtual,
                      "The list of virtual orbital subspaces known to this object.")
        //
        .def_readonly(
              "map_index_host_program", &MoSpaces::map_index_host_program,
              "Contains for each orbital space (e.g. f, o1) a mapping from the indices "
              "used inside\nthe respective space to the molecular orbital index "
              "convention used in the host\nprogram, i.e. to the ordering in which the "
              "molecular orbitals have been exposed\nin the HartreeFockSolution_i object "
              "passed on class construction.")
        .def_readonly(
              "map_block_start", &MoSpaces::map_block_start,
              "Contains for each orbital space the indices at which a new tensor block "
              "starts. Thus this list contains at least on index, namely 0.")
        .def_readonly(
              "map_block_irrep", &MoSpaces::map_block_irrep,
              "Contains for each orbital space the mapping from each *block* used inside "
              "the space to the irreducible representation it correspond to.")
        .def_readonly(
              "map_block_spin", &MoSpaces::map_block_spin,
              "Contains for each orbital space the mapping from each *block* used inside "
              "the space to the spin it correspond to ('a' is alpha and 'b' is beta)")
        //
        .def("to_ctx", &MoSpaces::to_ctx)
        //
        ;
}
}  // namespace py_iface
}  // namespace adcc

