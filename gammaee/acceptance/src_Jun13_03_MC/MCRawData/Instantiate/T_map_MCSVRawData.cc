// -*- C++ -*-
//
// Package:     MCRawData
// Module:      T_mapMCSVRawData
// 
// Description: instantiate map<int,float>
//
// Implementation:
//
// Author:      Brian K. Heltsley
// Created:     Tue Jun 08 15:07:04 EDT 1999
// $Id: T_map_MCSVRawData.cc,v 1.1 1999/11/16 20:55:44 pg Exp $
//
// Revision history
//
// $Log: T_map_MCSVRawData.cc,v $
// Revision 1.1  1999/11/16 20:55:44  pg
// Added Si simulation
//
// Revision 1.1  1999/06/10 20:22:33  bkh
// Better stab at CC simulation
//
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
#include <map>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
//#include "Experiment/report.h"

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
#include <map>

typedef int  _map_key_ ;
typedef float _map_contents_;
typedef less< _map_key_ > _map_compare_ ;

#include "STLUtility/instantiate_map.h"
