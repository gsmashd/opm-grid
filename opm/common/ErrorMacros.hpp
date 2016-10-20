/*
  Copyright 2013 Andreas Lauser
  Copyright 2009, 2010 SINTEF ICT, Applied Mathematics.
  Copyright 2009, 2010 Statoil ASA.

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
#ifndef OPM_ERRORMACROS_HPP
#define OPM_ERRORMACROS_HPP

#if ! HAVE_OPM_COMMON
#define OPM_THROW(Exception, message) std::abort();
// DUNE_THROW((Exception), (message))

#define OPM_MESSAGE(message)

#define OPM_ERROR_IF(condition, message)
#endif

#endif
