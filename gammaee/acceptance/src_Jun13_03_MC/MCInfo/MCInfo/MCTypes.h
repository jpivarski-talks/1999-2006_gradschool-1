#if !defined(MCINFO_MCTYPES_H)
#define MCINFO_MCTYPES_H
// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      MCTypes
// 
// Description: Standard typedefs for use in simulating particle decays
//
// Author:      Lawrence Gibbons
// Created:     Mon Mar  8 20:52:14 EST 1999
// $Id: MCTypes.h,v 1.2 1999/07/06 21:20:51 lkg Exp $
//
// Revision history
//
// $Log: MCTypes.h,v $
// Revision 1.2  1999/07/06 21:20:51  lkg
// Change Helicity: int -> double
//
// Revision 1.1  1999/06/22 21:29:45  lkg
// First real version of MCInfo in repository
//

//
// physics-related typedefs
//
typedef Double Helicity;

//
// Particle labelling typedefs
typedef Integer QQ_id;
typedef Integer Stable_id;
typedef Integer PDG_id;
typedef Integer Geant_id;

#endif /* MCINFO_MCTYPES_H */
