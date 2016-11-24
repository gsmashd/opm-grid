//===========================================================================
//
// File: entity_test.cpp
//
// Created: Fri May 29 14:04:50 2009
//
// Author(s): Atgeirr F Rasmussen <atgeirr@sintef.no>
//            B�rd Skaflestad     <bard.skaflestad@sintef.no>
//
// $Date$
//
// $Revision$
//
//===========================================================================

/*
  Copyright 2009, 2010 SINTEF ICT, Applied Mathematics.
  Copyright 2009, 2010 Statoil ASA.

  This file is part of The Open Porous Media project  (OPM).

  OPM is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  OPM is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with OPM.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <config.h>

#if HAVE_DYNAMIC_BOOST_TEST
#define BOOST_TEST_DYN_LINK
#endif
#define NVERBOSE // to suppress our messages when throwing


#define BOOST_TEST_MODULE EntityTests
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>
#include <sstream>

#include "config.h"
#include <dune/grid/cpgrid/Intersection.hpp>
#include <dune/grid/cpgrid/Entity.hpp>
#include <dune/grid/CpGrid.hpp>

using namespace Dune;



BOOST_AUTO_TEST_CASE(entity)
{
    int m_argc = boost::unit_test::framework::master_test_suite().argc;
    char** m_argv = boost::unit_test::framework::master_test_suite().argv;
    Dune::MPIHelper::instance(m_argc, m_argv);
    cpgrid::CpGridData g;
    cpgrid::Entity<0> e1(g, 0, true);
    cpgrid::Entity<0> e2(g, 0, false);
    cpgrid::Entity<0> e3(g, 1, true);
    cpgrid::Entity<0> e4(g, 1, false);
    BOOST_CHECK(e1 != e2);
    BOOST_CHECK(e1 != e3);
    BOOST_CHECK(e1 != e4);
    BOOST_CHECK(e2 != e3);
    BOOST_CHECK(e2 != e4);
    BOOST_CHECK(e3 != e4);
    BOOST_CHECK_EQUAL(e1.level(), 0);
    // BOOST_CHECK(e1.type().isSingular()); // Our new type
    BOOST_CHECK(e1.type().isCube());
    BOOST_CHECK_EQUAL(e1.partitionType(), InteriorEntity);
    cpgrid::Entity<3> e5(g, 0, true);
    BOOST_CHECK(e5.type().isCube());

    // Cannot check other members without a real grid.
    // Put in more checks when it is possible to construct
    // test grids easily.
    //   geometry()
    //   count()
    //   ileafbegin()
    //   ileafend()
}


BOOST_AUTO_TEST_CASE(entity_ptr)
{
    cpgrid::CpGridData g;
    cpgrid::EntityPointer<0> p1(g, 5, true);
    const cpgrid::EntityPointer<0> p2(g, 42, true);
//     cpgrid::Entity<0, CpGrid>& e1 = *p1;
//     const cpgrid::Entity<0, CpGrid>& e2 = *p2;
//     cpgrid::Entity<0, CpGrid> ee1(g, ~5);
//     cpgrid::Entity<0, CpGrid> ee2(g, 42);
//     BOOST_CHECK(e1 == ee1);
//     BOOST_CHECK(e2 == ee2);
}


bool
init_unit_test_func()
{
    return true;
}

int main(int argc, char** argv)
{
    Dune::MPIHelper::instance(argc, argv);
    boost::unit_test::unit_test_main(&init_unit_test_func,
                                     argc, argv);
}
