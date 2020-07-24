#if !defined(MCINFO_INTERACTION_TYPES_H)
#define MCINFO_INTERACTION_TYPES_H
// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      interaction_types
// 
// Description: <one line class summary>
//
// Usage:
//    <usage>
//
// Author:      Lawrence Gibbons
// Created:     Sun Jan 10 15:53:56 EST 1999
// $Id: interaction_types.h,v 1.5 2002/02/06 19:58:30 lkg Exp $
//
// Revision history
//
// $Log: interaction_types.h,v $
// Revision 1.5  2002/02/06 19:58:30  lkg
// add the interaction type kiNonQQDecay which will not enforce consistancy btw decay.dec and abserved modes
//
// Revision 1.4  2001/09/27 15:47:51  tom
// Added new 'interaction type' to represent decay vertices handled
//   by the CLEO II Geant implementation; usual conservation of
//   charge, momentum is NOT imposed at these vertices.
// To see the purpose of this type, look at the QQCommons classes
//   QQComsVertex and QQComsParticle.
//
// Revision 1.3  2000/01/26 16:48:12  lkg
// Add a new (nonfatal) interaction type: kiRadiativePairProduction.  This
// is a 4th order QED process in which an e+e- pair is radiated directly
// from a muon in a strong electric field
//
// Revision 1.2  1999/07/06 21:34:46  lkg
// Add kiProduction to the enum
//
// Revision 1.1  1999/06/22 21:30:03  lkg
// First real version of MCInfo in repository
//

// system include files

// user include files

// forward declarations

enum interaction {
   kiDecay                                =  1,
   kiNonQQDecay                           =  4,
   kiCleoIIGeantCompleteDecay             =  5,
   kiPairProduction                       =  6,
   kiComptonScattering                    =  7,
   kiPhotoelectric                        =  8,
   kiBremsstrahlung                       =  9,
   kiDeltaRay                             = 10,
   kiPositronAnnihilation                 = 11,
   kiHadronicInteraction                  = 12,
   kiHadronicElasticCoherentInteraction   = 13,
   kiNuclearEvaporation                   = 14,
   kiNuclearFission                       = 15,
   kiNuclearAbsorption                    = 16,
   kiAntiProtonAnnihilation               = 17,
   kiNeutronCapture                       = 18,
   kiHadronicElasticIncoherentInteraction = 19,
   kiHadronicInelasticScatter             = 20,
   kiMuonNucleusInteraction               = 21,
   kiLargeTimeOfFlight                    = 22,
   kiNuclearPhotoFission                  = 23,
   kiRayleighEffect                       = 25,
   kiRangeOut                             = 30,
   kiPathLengthTooLong                    = 31,
   kiTooManySteps                         = 32,
   kiTooManyPoints                        = 33,
   kiEscapedCleo                          = 34,
   kiRangeOutPlusDecay                    = 35,
   kiRadiativePairProduction              = 36,
   kiProduction                           = 50,
   kiAnyInteraction };

#endif /* !defined(MCINFO_INTERACTION_TYPES_H) */
