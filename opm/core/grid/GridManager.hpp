/*
  Copyright 2012 SINTEF ICT, Applied Mathematics.

  This file is part of the Open Porous Media project (OPM).

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

#ifndef OPM_GRIDMANAGER_HEADER_INCLUDED
#define OPM_GRIDMANAGER_HEADER_INCLUDED

#if HAVE_OPM_PARSER
#include <opm/parser/eclipse/Deck/Deck.hpp>
#include <opm/parser/eclipse/EclipseState/Grid/EclipseGrid.hpp>
#endif

#include <string>
#include <vector>

struct UnstructuredGrid;
struct grdecl;

namespace Opm
{
    /// This class manages an Opm::UnstructuredGrid in the sense that it
    /// encapsulates creation and destruction of the grid.
    /// The following grid types can be constructed:
    ///   - 3d corner-point grids (from deck input)
    ///   - 3d tensor grids (from deck input)
    ///   - 2d cartesian grids
    ///   - 3d cartesian grids
    /// The resulting UnstructuredGrid is available through the c_grid() method.
    class GridManager
    {
#if HAVE_OPM_PARSER
        typedef Opm::EclipseGridConstPtr  EclipseGridConstPtr;
#else
        typedef void* EclipseGridConstPtr;
        typedef void* DeckConstPtr;
#endif
    public:
        /// Construct a grid from an EclipseState::EclipseGrid instance.
        explicit GridManager(EclipseGridConstPtr eclipseGrid);

        /// Construct a grid from an EclipseState::EclipseGrid instance,
        /// giving an explicit set of pore volumes to be used for MINPV
        /// considerations.
        /// \input[in] eclipseGrid    encapsulates a corner-point grid given from a deck
        /// \input[in] poreVolumes    one element per logical cartesian grid element
        GridManager(EclipseGridConstPtr eclipseGrid,
                    const std::vector<double>& poreVolumes);

        /// Construct a 2d cartesian grid with cells of unit size.
        GridManager(int nx, int ny);

        /// Construct a 2d cartesian grid with cells of size [dx, dy].
        GridManager(int nx, int ny, double dx, double dy);

        /// Construct a 3d cartesian grid with cells of unit size.
        GridManager(int nx, int ny, int nz);

        /// Construct a 3d cartesian grid with cells of size [dx, dy, dz].
        GridManager(int nx, int ny, int nz,
                    double dx, double dy, double dz);

        /// Construct a grid from an input file.
        /// The file format used is currently undocumented,
        /// and is therefore only suited for internal use.
        explicit GridManager(const std::string& input_filename);

        /// Destructor.
        ~GridManager();

        /// Access the managed UnstructuredGrid.
        /// The method is named similarly to c_str() in std::string,
        /// to make it clear that we are returning a C-compatible struct.
        const UnstructuredGrid* c_grid() const;

        static void createGrdecl(DeckConstPtr deck, struct grdecl &grdecl);

    private:
        // Disable copying and assignment.
        GridManager(const GridManager& other);
        GridManager& operator=(const GridManager& other);

        // Construct corner-point grid from EclipseGrid.
        void initFromEclipseGrid(EclipseGridConstPtr eclipseGrid,
                                 const std::vector<double>& poreVolumes);

        // The managed UnstructuredGrid.
        UnstructuredGrid* ug_;
    };

} // namespace Opm

#endif // OPM_GRIDMANAGER_HEADER_INCLUDED
