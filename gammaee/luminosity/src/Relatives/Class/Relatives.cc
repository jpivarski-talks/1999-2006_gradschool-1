// -*- C++ -*-
//
// Package:     Relatives
// Module:      Relatives
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Tue Apr  5 12:25:35 EDT 2005
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "Relatives/Relatives.h"
#include "Experiment/report.h"
#include "Experiment/units.h"  // for converting to/from standard CLEO units

#include "DataHandler/Record.h"
#include "DataHandler/Frame.h"
#include "FrameAccess/extract.h"
#include "FrameAccess/FAItem.h"
#include "FrameAccess/FATable.h"

#include "Navigation/NavTrack.h"
#include "TrackRoot/TRHelixFit.h"
#include "TrackRoot/TRTrackFitQuality.h"
#include "TrackDelivery/TDKinematicFit.h"
#include "Navigation/NavShower.h"
#include "C3cc/CcShowerAttributes.h"
#include "TriggerL1Data/TriggerL1Data.h"
#include "EventProperties/EventProperties.h"
#include "Level4Proc/Level4Decision.h"
#include "BeamEnergy/BeamEnergy.h"
#include "BeamSpot/BeamSpot.h"
#include "CleoDB/DBEventHeader.h"
#include "RandomModule/RandomGenerator.h"

// STL classes
// You may have to uncomment some of these or other stl headers 
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "Processor.Relatives" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.33 2002/12/18 01:45:06 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
Relatives::Relatives( void )               // anal1
   : Processor( "Relatives" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &Relatives::event,    Stream::kEvent );
   //bind( &Relatives::beginRun, Stream::kBeginRun );
   //bind( &Relatives::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)

   m_run = 0;
   m_event = 0;
   m_nuncorrected = 0;
   m_neetrackless = 0;
   m_neenom = 0;
   for (int i = 0;  i < 138;  i++) {
      m_histogram[i] = 0;
      m_histogram_energyup[i] = 0;
      m_eenom_numer[i] = 0;
      m_eenom_denom[i] = 0;
      m_eephiup_numer[i] = 0;
      m_eephiup_denom[i] = 0;
      m_eephidown_numer[i] = 0;
      m_eephidown_denom[i] = 0;
      m_eethetaup_numer[i] = 0;
      m_eethetaup_denom[i] = 0;
      m_eethetadown_numer[i] = 0;
      m_eethetadown_denom[i] = 0;
      m_eeenergyup_numer[i] = 0;
      m_eeenergyup_denom[i] = 0;
      m_eenom_correct[i] = -1000.;
      m_eenom_error[i] = -1000.;
      m_eephiup_correct[i] = -1000.;
      m_eephiup_error[i] = -1000.;
      m_eephidown_correct[i] = -1000.;
      m_eephidown_error[i] = -1000.;
      m_eethetaup_correct[i] = -1000.;
      m_eethetaup_error[i] = -1000.;
      m_eethetadown_correct[i] = -1000.;
      m_eethetadown_error[i] = -1000.;
      m_eeenergyup_correct[i] = -1000.;
      m_eeenergyup_error[i] = -1000.;
   }
   m_eenom_int = -1000.;
   m_eenom_err = -1000.;
   m_eephiup_int = -1000.;
   m_eephiup_err = -1000.;
   m_eephidown_int = -1000.;
   m_eephidown_err = -1000.;
   m_eethetaup_int = -1000.;
   m_eethetaup_err = -1000.;
   m_eethetadown_int = -1000.;
   m_eethetadown_err = -1000.;
   m_eeenergyup_int = -1000.;
   m_eeenergyup_err = -1000.;
}

Relatives::~Relatives()                    // anal5
{
   report( DEBUG, kFacilityString ) << "here in dtor()" << endl;
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}

//
// member functions
//

// ------------ methods for beginning/end "Interactive" ------------
// --------------------------- init method -------------------------
void
Relatives::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
Relatives::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
   print();
}


// ---------------- standard place to book histograms ---------------
void
Relatives::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
Relatives::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   FAItem<TriggerL1Data> l1trig;
   extract(iFrame.record(Stream::kEvent), l1trig);

   FATable<NavShower> showers;
   extract(iFrame.record(Stream::kEvent), showers);

   FAItem<EventProperties> props;
   extract(iFrame.record(Stream::kEvent), props);

   FAItem<BeamEnergy> eBeam;
   extract(iFrame.record(Stream::kStartRun), eBeam);

   FAItem<BeamSpot> spot;
   extract(iFrame.record(Stream::kBeginRun), spot);

   FAItem<Level4Decision> l4dec;
   extract(iFrame.record(Stream::kEvent), l4dec);

   FAItem<DBEventHeader> head;
   extract(iFrame.record(Stream::kEvent), head);

   if (!head->monteCarlo()) {
      if (m_run == 0) m_run = head->run();
      if (head->run() != m_run) {
	 print();

	 m_run = head->run();
	 m_event = 0;
	 m_nuncorrected = 0;
	 m_neetrackless = 0;
	 m_neenom = 0;
	 for (int i = 0;  i < 138;  i++) {
	    m_histogram[i] = 0;
	    m_histogram_energyup[i] = 0;
	    m_eenom_numer[i] = 0;
	    m_eenom_denom[i] = 0;
	    m_eephiup_numer[i] = 0;
	    m_eephiup_denom[i] = 0;
	    m_eephidown_numer[i] = 0;
	    m_eephidown_denom[i] = 0;
	    m_eethetaup_numer[i] = 0;
	    m_eethetaup_denom[i] = 0;
	    m_eethetadown_numer[i] = 0;
	    m_eethetadown_denom[i] = 0;
	    m_eeenergyup_numer[i] = 0;
	    m_eeenergyup_denom[i] = 0;
	    m_eenom_correct[i] = -1000.;
	    m_eenom_error[i] = -1000.;
	    m_eephiup_correct[i] = -1000.;
	    m_eephiup_error[i] = -1000.;
	    m_eephidown_correct[i] = -1000.;
	    m_eephidown_error[i] = -1000.;
	    m_eethetaup_correct[i] = -1000.;
	    m_eethetaup_error[i] = -1000.;
	    m_eethetadown_correct[i] = -1000.;
	    m_eethetadown_error[i] = -1000.;
	    m_eeenergyup_correct[i] = -1000.;
	    m_eeenergyup_error[i] = -1000.;
	 }
	 m_eenom_int = -1000.;
	 m_eenom_err = -1000.;
	 m_eephiup_int = -1000.;
	 m_eephiup_err = -1000.;
	 m_eephidown_int = -1000.;
	 m_eephidown_err = -1000.;
	 m_eethetaup_int = -1000.;
	 m_eethetaup_err = -1000.;
	 m_eethetadown_int = -1000.;
	 m_eethetadown_err = -1000.;
	 m_eeenergyup_int = -1000.;
	 m_eeenergyup_err = -1000.;
      }
   }

   m_event++;
   HepVector3D bs = spot->center();
   if (head->monteCarlo()) {
      RandomGenerator& random(RandomGenerator::instance());
      bs.setX(random.gauss(0., 0.000325));
      bs.setY(random.gauss(0., 0.000006));
      if (random.flat() > 0.237)
	 bs.setZ(random.gauss(0., 0.671*M_SQRT2*0.01273));
      else
	 bs.setZ(random.gauss(0., 0.469*M_SQRT2*0.01273));
   }

   FATable<NavShower>::const_iterator showers_end, one, two;
   showers_end = one = two = showers.end();
   for (FATable<NavShower>::const_iterator shower_iter = showers.begin();  shower_iter != showers_end;  ++shower_iter) {
      if (!shower_iter->attributes().hot()  &&  shower_iter->attributes().status()) {
	 if (one == showers_end  ||  shower_iter->attributes().energy() > one->attributes().energy()) {
	    two = one;
	    one = shower_iter;
	 }
	 else if (two == showers_end  ||  shower_iter->attributes().energy() > two->attributes().energy()) {
	    two = shower_iter;
	 }
      }
   }
   
   if (one == showers_end  ||  two == showers_end  || 
       cos(one->attributes().theta())*cos(two->attributes().theta()) > 0.)
      return ActionBase::kFailed;
   FATable<NavShower>::const_iterator west = (cos(one->attributes().theta()) > 0. ? one : two);
   FATable<NavShower>::const_iterator east = (cos(one->attributes().theta()) > 0. ? two : one);
   
   double westphi, eastphi, westcotT, eastcotT;
   if (true) {
      double d = west->attributes().distance();
      double th = west->attributes().theta();
      double ph = west->attributes().phi();
      westphi = atan2(d*sin(th)*sin(ph) - bs.y(),
		      d*sin(th)*cos(ph) - bs.x());
      westcotT = (d*cos(th) - bs.z()) /
	 sqrt(sqr(d*sin(th)*cos(ph) - bs.x()) +
	      sqr(d*sin(th)*sin(ph) - bs.y()));
   }
   if (true) {
      double d = east->attributes().distance();
      double th = east->attributes().theta();
      double ph = east->attributes().phi();
      eastphi = atan2(d*sin(th)*sin(ph) - bs.y(),
		      d*sin(th)*cos(ph) - bs.x());
      eastcotT = (d*cos(th) - bs.z()) /
	 sqrt(sqr(d*sin(th)*cos(ph) - bs.x()) +
	      sqr(d*sin(th)*sin(ph) - bs.y()));
   }
   double cotT = (westcotT - eastcotT)/2.;
   int bin = int(floor(cotT*100.));

   double westphiup = westphi + 3.25/64.0*M_PI;
   double eastphiup = eastphi + 3.25/64.0*M_PI;
   double westphidown = westphi - 3.25/64.0*M_PI;
   double eastphidown = eastphi - 3.25/64.0*M_PI;

   double cotTup = cotT + 0.1;
   double cotTdown = cotT - 0.1;

   // if it's a gamgam
   if (l1trig->isBarrelBhabha()                              &&
       l4dec->decision() > 0                                 &&
       two->attributes().energy() / eBeam->value() > 0.9     &&
       props->nbChargedTracks() == 0                         &&
       excludeBlockA(westphi, cotT)                          &&
       excludeBlockBC(westphi, cotT)                         &&
       (0.05 < fabs(cotT) && fabs(cotT) < 1.38)              &&
       safeb2b(westcotT, eastcotT)                           &&
       ggacop(westphi, eastphi)                                ) {
      m_nuncorrected++;
      m_histogram[bin]++;
   }

   // if it's an energyup gamgam
   if (l1trig->isBarrelBhabha()                              &&
       l4dec->decision() > 0                                 &&
       two->attributes().energy() / eBeam->value() > 0.95    &&
       props->nbChargedTracks() == 0                         &&
       excludeBlockA(westphi, cotT)                          &&
       excludeBlockBC(westphi, cotT)                         &&
       (0.05 < fabs(cotT) && fabs(cotT) < 1.38)              &&
       safeb2b(westcotT, eastcotT)                           &&
       ggacop(westphi, eastphi)                                ) {
      m_histogram_energyup[bin]++;
   }

   // if it's a trackless bhabha
   if (l1trig->isBarrelBhabha()                              &&
       l4dec->decision() > 0                                 &&
       two->attributes().energy() / eBeam->value() > 0.9     &&
       props->nbChargedTracks() == 0                         &&
       excludeBlockA(westphi, cotT)                          &&
       excludeBlockBC(westphi, cotT)                         &&
       (0.15 < fabs(cotT) && fabs(cotT) < 1.28)              &&
       safeb2b(westcotT, eastcotT)                           &&
       bbacop(westphi, eastphi)                                ) {
      m_neetrackless++;
   }
   
   // if it's a nominal e+e-
   if (l1trig->isElTrack()                                   &&
       l4dec->decision() > 0                                 &&
       two->attributes().energy() / eBeam->value() > 0.9     &&
       props->secondLargestPTrack() / eBeam->value() > 0.9   &&
       props->nbChargedTracks() == 2                         &&
       excludeBlockA(westphi, cotT)                          &&
       excludeBlockBC(westphi, cotT)                         &&
       (0.15 < fabs(cotT) && fabs(cotT) < 1.28)              &&
       safeb2b(westcotT, eastcotT)                           &&
       bbacop(westphi, eastphi)                                ) {
      m_neenom++;
      m_eenom_denom[bin]++;
      if (l1trig->isBarrelBhabha()) m_eenom_numer[bin]++;
   }
   
   // if it's a phiup e+e-
   if (l1trig->isElTrack()                                   &&
       l4dec->decision() > 0                                 &&
       two->attributes().energy() / eBeam->value() > 0.9     &&
       props->secondLargestPTrack() / eBeam->value() > 0.9   &&
       props->nbChargedTracks() == 2                         &&
       excludeBlockA(westphiup, cotT)                          &&
       excludeBlockBC(westphiup, cotT)                         &&
       (0.15 < fabs(cotT) && fabs(cotT) < 1.28)              &&
       safeb2b(westcotT, eastcotT)                           &&
       bbacop(westphiup, eastphiup)                                ) {
      m_eephiup_denom[bin]++;
      if (l1trig->isBarrelBhabha()) m_eephiup_numer[bin]++;
   }
   
   // if it's a phidown e+e-
   if (l1trig->isElTrack()                                   &&
       l4dec->decision() > 0                                 &&
       two->attributes().energy() / eBeam->value() > 0.9     &&
       props->secondLargestPTrack() / eBeam->value() > 0.9   &&
       props->nbChargedTracks() == 2                         &&
       excludeBlockA(westphidown, cotT)                          &&
       excludeBlockBC(westphidown, cotT)                         &&
       (0.15 < fabs(cotT) && fabs(cotT) < 1.28)              &&
       safeb2b(westcotT, eastcotT)                           &&
       bbacop(westphidown, eastphidown)                                ) {
      m_eephidown_denom[bin]++;
      if (l1trig->isBarrelBhabha()) m_eephidown_numer[bin]++;
   }
   
   // if it's a thetaup e+e-
   if (l1trig->isElTrack()                                   &&
       l4dec->decision() > 0                                 &&
       two->attributes().energy() / eBeam->value() > 0.9     &&
       props->secondLargestPTrack() / eBeam->value() > 0.9   &&
       props->nbChargedTracks() == 2                         &&
       excludeBlockA(westphi, cotTup)                          &&
       excludeBlockBC(westphi, cotTup)                         &&
       (0.15 < fabs(cotTup) && fabs(cotTup) < 1.28)          &&
       safeb2b(westcotT, eastcotT)                           &&
       bbacop(westphi, eastphi)                                ) {
      // bin number does NOT change because we are sliding windows,
      // not values.
      m_eethetaup_denom[bin]++;
      if (l1trig->isBarrelBhabha()) m_eethetaup_numer[bin]++;
   }
   
   // if it's a thetadown e+e-
   if (l1trig->isElTrack()                                   &&
       l4dec->decision() > 0                                 &&
       two->attributes().energy() / eBeam->value() > 0.9     &&
       props->secondLargestPTrack() / eBeam->value() > 0.9   &&
       props->nbChargedTracks() == 2                         &&
       excludeBlockA(westphi, cotTdown)                          &&
       excludeBlockBC(westphi, cotTdown)                         &&
       (0.15 < fabs(cotTdown) && fabs(cotTdown) < 1.28)          &&
       safeb2b(westcotT, eastcotT)                           &&
       bbacop(westphi, eastphi)                                ) {
      // bin number does NOT change because we are sliding windows,
      // not values.
      m_eethetadown_denom[bin]++;
      if (l1trig->isBarrelBhabha()) m_eethetadown_numer[bin]++;
   }

   // if it's an energyup e+e-
   if (l1trig->isElTrack()                                   &&
       l4dec->decision() > 0                                 &&
       two->attributes().energy() / eBeam->value() > 0.95    &&
       props->secondLargestPTrack() / eBeam->value() > 0.95  &&
       props->nbChargedTracks() == 2                         &&
       excludeBlockA(westphi, cotT)                          &&
       excludeBlockBC(westphi, cotT)                         &&
       (0.15 < fabs(cotT) && fabs(cotT) < 1.28)              &&
       safeb2b(westcotT, eastcotT)                           &&
       bbacop(westphi, eastphi)                                ) {
      m_eeenergyup_denom[bin]++;
      if (l1trig->isBarrelBhabha()) m_eeenergyup_numer[bin]++;
   }
   
   return ActionBase::kPassed;
}

bool Relatives::excludeBlockA(double westphi, double cotTheta)
{
   // This will return true if you're OUTSIDE of block A
   return !(-14.0/64.0*M_PI < westphi  &&
	    westphi < 9.0/64.0*M_PI    &&
	    fabs(cotTheta) < 0.54);
}

bool Relatives::excludeBlockBC(double westphi, double cotTheta)
{
   // This will return true if you're OUTSIDE of blocks B and C
   return !(-53.0/64.0*M_PI < westphi  &&
	    westphi < -14.0/64.0*M_PI    &&
	    fabs(cotTheta) > 0.95);
}

bool Relatives::safeb2b(double cotTheta1, double cotTheta2)
{
   return (fabs(cotTheta1 + cotTheta2) < 0.1);
}

bool Relatives::ggacop(double phi1, double phi2)
{
   return (fabs(sin(phi1 - phi2)) < 0.04);
}

bool Relatives::bbacop(double phi1, double phi2)
{
   return (0.04 < fabs(sin(phi1 - phi2))  &&
	   fabs(sin(phi1 - phi2)) < 0.25);
}

void Relatives::print()
{
   for (int i = 0;  i < 138;  i++) {
      if (m_histogram[i] == 0  ||  m_eenom_denom[i] == 0) {
	 m_eenom_correct[i] = 0.;
	 m_eenom_error[i] = 0.;
      }
      else {
	 m_eenom_correct[i] = double(m_histogram[i] * m_eenom_denom[i]) / double(m_eenom_numer[i]);
	 m_eenom_error[i] = m_eenom_correct[i] * sqrt(1./double(m_histogram[i]) + (1. - double(m_eenom_numer[i])/double(m_eenom_denom[i]))/double(m_eenom_numer[i]));
      }
      
      if (m_histogram[i] == 0  ||  m_eephiup_denom[i] == 0) {
	 m_eephiup_correct[i] = 0.;
	 m_eephiup_error[i] = 0.;
      }
      else {
	 m_eephiup_correct[i] = double(m_histogram[i] * m_eephiup_denom[i]) / double(m_eephiup_numer[i]);
	 m_eephiup_error[i] = m_eephiup_correct[i] * sqrt(1./double(m_histogram[i]) + (1. - double(m_eephiup_numer[i])/double(m_eephiup_denom[i]))/double(m_eephiup_numer[i]));
      }
      
      if (m_histogram[i] == 0  ||  m_eephidown_denom[i] == 0) {
	 m_eephidown_correct[i] = 0.;
	 m_eephidown_error[i] = 0.;
      }
      else {
	 m_eephidown_correct[i] = double(m_histogram[i] * m_eephidown_denom[i]) / double(m_eephidown_numer[i]);
	 m_eephidown_error[i] = m_eephidown_correct[i] * sqrt(1./double(m_histogram[i]) + (1. - double(m_eephidown_numer[i])/double(m_eephidown_denom[i]))/double(m_eephidown_numer[i]));
      }
      
      if (m_histogram[i] == 0  ||  m_eethetaup_denom[i] == 0) {
	 m_eethetaup_correct[i] = 0.;
	 m_eethetaup_error[i] = 0.;
      }
      else {
	 m_eethetaup_correct[i] = double(m_histogram[i] * m_eethetaup_denom[i]) / double(m_eethetaup_numer[i]);
	 m_eethetaup_error[i] = m_eethetaup_correct[i] * sqrt(1./double(m_histogram[i]) + (1. - double(m_eethetaup_numer[i])/double(m_eethetaup_denom[i]))/double(m_eethetaup_numer[i]));
      }
      
      if (m_histogram[i] == 0  ||  m_eethetadown_denom[i] == 0) {
	 m_eethetadown_correct[i] = 0.;
	 m_eethetadown_error[i] = 0.;
      }
      else {
	 m_eethetadown_correct[i] = double(m_histogram[i] * m_eethetadown_denom[i]) / double(m_eethetadown_numer[i]);
	 m_eethetadown_error[i] = m_eethetadown_correct[i] * sqrt(1./double(m_histogram[i]) + (1. - double(m_eethetadown_numer[i])/double(m_eethetadown_denom[i]))/double(m_eethetadown_numer[i]));
      }

      if (m_histogram_energyup[i] == 0  ||  m_eeenergyup_denom[i] == 0) {
	 m_eeenergyup_correct[i] = 0.;
	 m_eeenergyup_error[i] = 0.;
      }
      else {
	 m_eeenergyup_correct[i] = double(m_histogram_energyup[i] * m_eeenergyup_denom[i]) / double(m_eeenergyup_numer[i]);
	 m_eeenergyup_error[i] = m_eeenergyup_correct[i] * sqrt(1./double(m_histogram_energyup[i]) + (1. - double(m_eeenergyup_numer[i])/double(m_eeenergyup_denom[i]))/double(m_eeenergyup_numer[i]));
      }
   }      

   m_eenom_int = 0.;
   m_eenom_err = 0.;
   m_eephiup_int = 0.;
   m_eephiup_err = 0.;
   m_eephidown_int = 0.;
   m_eephidown_err = 0.;
   m_eethetaup_int = 0.;
   m_eethetaup_err = 0.;
   m_eethetadown_int = 0.;
   m_eethetadown_err = 0.;
   m_eeenergyup_int = 0.;
   m_eeenergyup_err = 0.;
   for (int i = 15;  i < 128;  i++) {
      m_eenom_int += m_eenom_correct[i];
      m_eenom_err += sqr(m_eenom_error[i]);

      m_eephiup_int += m_eephiup_correct[i];
      m_eephiup_err += sqr(m_eephiup_error[i]);

      m_eephidown_int += m_eephidown_correct[i];
      m_eephidown_err += sqr(m_eephidown_error[i]);

      m_eeenergyup_int += m_eeenergyup_correct[i];
      m_eeenergyup_err += sqr(m_eeenergyup_error[i]);
   }
   for (int i = 05;  i < 118;  i++) {
      m_eethetaup_int += m_eethetaup_correct[i];
      m_eethetaup_err += sqr(m_eethetaup_error[i]);
   }
   for (int i = 25;  i < 138;  i++) {
      m_eethetadown_int += m_eethetadown_correct[i];
      m_eethetadown_err += sqr(m_eethetadown_error[i]);
   }
   m_eenom_err = sqrt(m_eenom_err);
   m_eephiup_err = sqrt(m_eephiup_err);
   m_eephidown_err = sqrt(m_eephidown_err);
   m_eethetaup_err = sqrt(m_eethetaup_err);
   m_eethetadown_err = sqrt(m_eethetadown_err);
   m_eeenergyup_err = sqrt(m_eeenergyup_err);

   report(SYSTEM, kFacilityString) << "commencing python..." << endl;
   cout << "PYTHON run[" << m_run << "] = RunRecord()" << endl;
   cout << "PYTHON run[" << m_run << "].event = " << m_event << endl;
   cout << "PYTHON run[" << m_run << "].nuncorrected = " << m_nuncorrected << endl;
   cout << "PYTHON run[" << m_run << "].neetrackless = " << m_neetrackless << endl;
   cout << "PYTHON run[" << m_run << "].neenom = " << m_neenom << endl;
   cout << "PYTHON run[" << m_run << "].histogram = (";
   for (int i = 0;  i < 138;  i++) cout << m_histogram[i] << ", "; cout << ")" << endl;
   cout << "PYTHON run[" << m_run << "].histogram_energyup = (";
   for (int i = 0;  i < 138;  i++) cout << m_histogram_energyup[i] << ", "; cout << ")" << endl;
   cout << "PYTHON run[" << m_run << "].eenom_numer = (";
   for (int i = 0;  i < 138;  i++) cout << m_eenom_numer[i] << ", "; cout << ")" << endl;
   cout << "PYTHON run[" << m_run << "].eenom_denom = (";
   for (int i = 0;  i < 138;  i++) cout << m_eenom_denom[i] << ", "; cout << ")" << endl;
   cout << "PYTHON run[" << m_run << "].eethetaup_numer = (";
   for (int i = 0;  i < 138;  i++) cout << m_eethetaup_numer[i] << ", "; cout << ")" << endl;
   cout << "PYTHON run[" << m_run << "].eethetaup_denom = (";
   for (int i = 0;  i < 138;  i++) cout << m_eethetaup_denom[i] << ", "; cout << ")" << endl;
   cout << "PYTHON run[" << m_run << "].eethetadown_numer = (";
   for (int i = 0;  i < 138;  i++) cout << m_eethetadown_numer[i] << ", "; cout << ")" << endl;
   cout << "PYTHON run[" << m_run << "].eethetadown_denom = (";
   for (int i = 0;  i < 138;  i++) cout << m_eethetadown_denom[i] << ", "; cout << ")" << endl;
   cout << "PYTHON run[" << m_run << "].eeenergyup_numer = (";
   for (int i = 0;  i < 138;  i++) cout << m_eeenergyup_numer[i] << ", "; cout << ")" << endl;
   cout << "PYTHON run[" << m_run << "].eeenergyup_denom = (";
   for (int i = 0;  i < 138;  i++) cout << m_eeenergyup_denom[i] << ", "; cout << ")" << endl;
   cout << "PYTHON run[" << m_run << "].eenom_int = (" << m_eenom_int << ", " << m_eenom_err << ")" << endl;
   cout << "PYTHON run[" << m_run << "].eephiup_int = (" << m_eephiup_int << ", " << m_eephiup_err << ")" << endl;
   cout << "PYTHON run[" << m_run << "].eephidown_int = (" << m_eephidown_int << ", " << m_eephidown_err << ")" << endl;
   cout << "PYTHON run[" << m_run << "].eethetaup_int = (" << m_eethetaup_int << ", " << m_eethetaup_err << ")" << endl;
   cout << "PYTHON run[" << m_run << "].eethetadown_int = (" << m_eethetadown_int << ", " << m_eethetadown_err << ")" << endl;
   cout << "PYTHON run[" << m_run << "].eeenergyup_int = (" << m_eeenergyup_int << ", " << m_eeenergyup_err << ")" << endl;
}

/*
ActionBase::ActionResult
Relatives::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
Relatives::endRun( Frame& iFrame )         // anal4 equiv.
{
   report( DEBUG, kFacilityString ) << "here in endRun()" << endl;

   return ActionBase::kPassed;
}
*/

//
// const member functions
//

//
// static member functions
//
