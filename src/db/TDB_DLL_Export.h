/**
	@File : TDB_DLL_Export.h
	@Language : c++
	@Authors :	Fillières Gauthier,
				Aguilar Axel,
				Gaillard Christophe


	@Licence : GNU General Public License

				This file is part of TechmedDB.

				TechmedDB is free software: you can redistribute it and/or modify
				it under the terms of the GNU General Public License as published by
				the Free Software Foundation, either version 3 of the License, or
				(at your option) any later version.

				TechmedDB is distributed in the hope that it will be useful,
				but WITHOUT ANY WARRANTY; without even the implied warranty of
				MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
				See the GNU General Public License for more details.

				You should have received a copy of the GNU General Public License
				along with TechmedDB ("gpl_3_0.txt"). If not, see <http://www.gnu.org/licenses/>.
**/

#ifndef TDB_DLL_EXPORT
#define TDB_DLL_EXPORT

#if TDB_DLL
	#if TDB_DLL_BUILD
		#define DLLEXPORT __declspec(dllexport)
	#else
		#define DLLEXPORT __declspec(dllimport)
	#endif
#endif


#endif // DLL_EXPORT