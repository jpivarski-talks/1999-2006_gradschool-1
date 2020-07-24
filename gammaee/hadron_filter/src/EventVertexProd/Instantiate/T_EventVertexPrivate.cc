// -*- C++ -*-
//
// Package:     EventVertexProd
// Module:      T_EventVertexPrivate
// 
// Description: Instantiate Classes for EventVertexPrivate
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Guang-Pei Chen
// Created:     Mon Mar 18 23:06:31 EST 2002
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// user include files
#include "EventVertexProd/EventVertexPrivate.h"

#include "FrameAccess/instantiate_macros.h"
INSTANTIATE_ONE( EventVertexPrivate )
//Use the following if 'EventVertex' contains a ','
// also make sure there are no blank spaces within 'EventVertex'
/* INSTANTIATE_ONE_1_COMMA( EventVertexPrivate ) */
#include "FrameAccess/instantiate_one.h"

