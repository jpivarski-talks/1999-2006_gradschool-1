// -*- C++ -*-
//
// Package:     <ToolBox>
// Module:      T_map_int_int
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Sat Apr  8 13:02:14 EDT 2000
// $Id: T_map_int_int.cc,v 1.1 2002/06/20 15:55:14 ajm36 Exp $
//
// Revision history
//
// $Log: T_map_int_int.cc,v $
// Revision 1.1  2002/06/20 15:55:14  ajm36
// add instantiation file for map<int,int>
//
// Revision 1.1  2000/04/21 17:53:08  cdj
// added instantion of map files needed for new FAPtrTable implementation
//

#include "Experiment/Experiment.h"
#include "Experiment/types.h"

//
// instantiate
//

#include <map>

typedef int _map_key_ ;
typedef int _map_contents_ ;
typedef less< _map_key_ > _map_compare_ ;

#include "STLUtility/instantiate_map.h"

