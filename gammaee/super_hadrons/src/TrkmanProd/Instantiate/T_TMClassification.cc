// -*- C++ -*-
//
// Package:     package
// Module:      T_TMClassification
// 
// Description: Instantiate Classes for TMClassification
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Nadia Adam
// Created:     Tue Oct 22 14:49:20 EDT 2002
// $Id: T_TMClassification.cc,v 1.1 2002/11/04 18:38:02 nea9 Exp $
//
// Revision history
//
// $Log: T_TMClassification.cc,v $
// Revision 1.1  2002/11/04 18:38:02  nea9
// New CleoIII Trkman
//
//

#include "Experiment/Experiment.h"

// user include files
#include "Trkman/TMClassification.h"

#include "FrameAccess/instantiate_macros.h"
INSTANTIATE_ONE( TMClassification )
//Use the following if 'TMClassification' contains a ','
// also make sure there are no blank spaces within 'TMClassification'
/* INSTANTIATE_ONE_1_COMMA( TMClassification ) */
#include "FrameAccess/instantiate_one.h"

