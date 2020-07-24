// -*- C++ -*-
//
// Package:     Efficiency
// Module:      Efficiency
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Jim Pivarski
// Created:     Thu May 29 15:24:56 EDT 2003
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "Efficiency/Efficiency.h"
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
#include "TrackRoot/TRSeedTrackQuality.h"
#include "TrackDelivery/TDKinematicFit.h"

#include "Navigation/NavShower.h"
#include "C3cc/CcShowerAttributes.h"

#include "MCInfo/MCDecayTree/MCDecayTree.h"
#include "MCInfo/MCDecayTree/MCParticle.h"
#include "MCInfo/MCParticleProperty/MCParticleProperty.h"
#include "MCInfo/MCParticleProperty/MCParticlePropertyStore.h"

#include "TriggerData/TriggerData.h"
#include "TriggerL1Data/TriggerL1Data.h"
#include "Level3TagWord/Level3TagWord.h"
#include "Level4Proc/Level4Decision.h"
#include "EventProperties/EventProperties.h"
#include "EventType/EventType.h"
#include "BeamSpot/BeamSpot.h"
#include "BeamEnergy/BeamEnergy.h"
#include "CleoDB/DBEventHeader.h"

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
static const char* const kFacilityString = "Processor.Efficiency" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.33 2002/12/18 01:45:06 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//

//
// constructors and destructor
//
Efficiency::Efficiency( void )               // anal1
   : Processor( "Efficiency" )
   , m_isMC("isMC", this, true)
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &Efficiency::event,    Stream::kEvent );
   //bind( &Efficiency::beginRun, Stream::kBeginRun );
   //bind( &Efficiency::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

Efficiency::~Efficiency()                    // anal5
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
Efficiency::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
Efficiency::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
Efficiency::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   const char* label[kNumEntries] = {
      "run", "event",
      "decay3s", "decay2p", "decay2s", "decay1p", "decay1s",
      "ypperp", "ypphi", "ypz",
//      "l1tracks", "l1clusters",
      "l3showers", "l3totalcc", "l3biggest", "l3posz", "l3negz",
      "l4tracks",
      "l5tracks", "l5visen", "l5ccen", "l5biggest", "l5ebeam",
      "neuten", "charge", "pperp", "pphi", "pz", "bigtrack", "bigmatch",
      "show10", "show20", "show30", "show50", "show200", "show300", "show500", "show1000",
      "l6rphi", "l6z",
      "l1dec", "l3dec", "l3acc", "l3class", "l4dec", "l5dec", "l6dec"
   };
   m_ntuple = iHistoManager.ntuple(
      1, "vars", kNumEntries, 262144, label );

}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
Efficiency::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   float v[kNumEntries];  for (int i = 0;  i < kNumEntries;  i++) v[i] = 5000.;

   FAItem<DBEventHeader> header;
   extract(iFrame.record(Stream::kEvent), header);
   v[kRun] = header->run();
   v[kEvent] = header->number();

   if (m_isMC.value()) {
      v[kDecay3S] = 0.;
      v[kDecay2P] = 0.;
      v[kDecay2S] = 0.;
      v[kDecay1P] = 0.;
      v[kDecay1S] = 0.;

      FAItem<MCDecayTree> decay;
      extract(iFrame.record(Stream::kEvent), decay, "Generator");
      MCDecayTree::const_vIterator decay_end(decay->vEnd());
      const MCParticlePropertyStore& mcppstore = decay->topParticle().properties().store();
 
      int gamma(mcppstore.nameToQQId("GAMM"));
      int eplus(mcppstore.nameToQQId("E+"));
      int eminus(mcppstore.nameToQQId("E-"));
      int muplus(mcppstore.nameToQQId("MU+"));
      int muminus(mcppstore.nameToQQId("MU-"));
      int tauplus(mcppstore.nameToQQId("TAU+"));
      int tauminus(mcppstore.nameToQQId("TAU-"));
      int pizero(mcppstore.nameToQQId("PI0"));
      int piplus(mcppstore.nameToQQId("PI+"));
      int piminus(mcppstore.nameToQQId("PI-"));
      int ups1(mcppstore.nameToQQId("UPS1"));
      int ups2(mcppstore.nameToQQId("UPS2"));
      int ups3(mcppstore.nameToQQId("UPS3"));
      int chib0p1(mcppstore.nameToQQId("CHIB0"));
      int chib1p1(mcppstore.nameToQQId("CHIB1"));
      int chib2p1(mcppstore.nameToQQId("CHIB2"));
      int chib0p2(mcppstore.nameToQQId("CHBP0"));
      int chib1p2(mcppstore.nameToQQId("CHBP1"));
      int chib2p2(mcppstore.nameToQQId("CHBP2"));

      Hep3Vector ups3s_p(-1000., -1000., -1000.);
      Hep3Vector ups2s_p(-1000., -1000., -1000.);
      Hep3Vector ups1s_p(-1000., -1000., -1000.);

      for (MCDecayTree::const_vIterator decay_iter = decay->vBegin();
	   decay_iter != decay_end;
	   ++decay_iter) {
	 int parent(decay_iter->parentPtr()->properties().QQId());

	 int decayNumber(1);
	 if (decay_iter->size() == 2) {
	    int first(decay_iter->pBegin()->properties().QQId());
	    int second((++(decay_iter->pBegin()))->properties().QQId());

	    if ( (first == eplus   &&  second == eminus)  ||
		 (first == eminus  &&  second == eplus)      ) {
	       decayNumber = 4;
	    } else if ( (first == muplus   &&  second == muminus)  ||
			(first == muminus  &&  second == muplus)      ) {
	       decayNumber = 5;
	    } else if ( (first == tauplus   &&  second == tauminus)  ||
			(first == tauminus  &&  second == tauplus)      ) {
	       decayNumber = 6;
	    } else if ( (first == gamma    &&  second == chib0p1)  ||
			(first == chib0p1  &&  second == gamma)      ) {
	       decayNumber = 30;
	    } else if ( (first == gamma    &&  second == chib1p1)  ||
			(first == chib1p1  &&  second == gamma)      ) {
	       decayNumber = 31;
	    } else if ( (first == gamma    &&  second == chib2p1)  ||
			(first == chib2p1  &&  second == gamma)      ) {
	       decayNumber = 32;
	    } else if ( (first == gamma    &&  second == chib0p2)  ||
			(first == chib0p2  &&  second == gamma)      ) {
	       decayNumber = 40;
	    } else if ( (first == gamma    &&  second == chib1p2)  ||
			(first == chib1p2  &&  second == gamma)      ) {
	       decayNumber = 41;
	    } else if ( (first == gamma    &&  second == chib2p2)  ||
			(first == chib2p2  &&  second == gamma)      ) {
	       decayNumber = 42;
	    } else if ( (first == gamma  &&  second == ups1)  ||
			(first == ups1   &&  second == gamma)    ) {
	       decayNumber = 51;
	    } else if ( (first == gamma  &&  second == ups2)  ||
			(first == ups2   &&  second == gamma)    ) {
	       decayNumber = 52;
	    }
	 }
	 else if (decay_iter->size() == 3) {
	    int first(decay_iter->pBegin()->properties().QQId());
	    int second((++(decay_iter->pBegin()))->properties().QQId());
	    int third((++(++(decay_iter->pBegin())))->properties().QQId());

	    if ( (first == ups1  &&  second == pizero  &&  third == pizero)  ||
		 (first == pizero  &&  second == ups1  &&  third == pizero)  ||
		 (first == pizero  &&  second == pizero  &&  third == ups1)     ) {
	       decayNumber = 10;
	    } else if ( (first == ups1  &&  second == piplus  &&  third == piminus)  ||
			(first == ups1  &&  second == piminus  &&  third == piplus)  ||
			(first == piplus  &&  second == ups1  &&  third == piminus)  ||
			(first == piplus  &&  second == piminus  &&  third == ups1)  ||
			(first == piminus  &&  second == ups1  &&  third == piplus)  ||
			(first == piminus  &&  second == piplus  &&  third == ups1)     ) {
	       decayNumber = 11;
	    } else if ( (first == ups1  &&  second == gamma  &&  third == gamma)  ||
			(first == gamma  &&  second == ups1  &&  third == gamma)  ||
			(first == gamma  &&  second == gamma  &&  third == ups1)     ) {
	       decayNumber = 12;
	    } else if ( (first == ups2  &&  second == pizero  &&  third == pizero)  ||
			(first == pizero  &&  second == ups2  &&  third == pizero)  ||
			(first == pizero  &&  second == pizero  &&  third == ups2)     ) {
	       decayNumber = 20;
	    } else if ( (first == ups2  &&  second == piplus  &&  third == piminus)  ||
			(first == ups2  &&  second == piminus  &&  third == piplus)  ||
			(first == piplus  &&  second == ups2  &&  third == piminus)  ||
			(first == piplus  &&  second == piminus  &&  third == ups2)  ||
			(first == piminus  &&  second == ups2  &&  third == piplus)  ||
			(first == piminus  &&  second == piplus  &&  third == ups2)     ) {
	       decayNumber = 21;
	    } else if ( (first == ups2  &&  second == gamma  &&  third == gamma)  ||
			(first == gamma  &&  second == ups2  &&  third == gamma)  ||
			(first == gamma  &&  second == gamma  &&  third == ups2)     ) {
	       decayNumber = 22;
	    }
	 }

	 if (parent == ups3) {
	    if (v[kDecay3S] != 0) {
	       report(ERROR, kFacilityString) << "kDecay3S previously set!" << endl << *decay << endl;
	       return ActionBase::kFailed;
	    }
	    v[kDecay3S] = decayNumber;

	    ups3s_p = decay_iter->parentPtr()->momentum();
	 }
	 else if (parent == chib0p2  ||  parent == chib1p2  ||  parent == chib2p2) {
	    if (v[kDecay2P] != 0) {
	       report(ERROR, kFacilityString) << "kDecay2P previously set!" << endl << *decay << endl;
	       return ActionBase::kFailed;
	    }
	    v[kDecay2P] = decayNumber;
	 }
	 else if (parent == ups2) {
	    if (v[kDecay2S] != 0) {
	       report(ERROR, kFacilityString) << "kDecay2S previously set!" << endl << *decay << endl;
	       return ActionBase::kFailed;
	    }
	    v[kDecay2S] = decayNumber;

	    ups2s_p = decay_iter->parentPtr()->momentum();
	 }
	 else if (parent == chib0p1  ||  parent == chib1p1  ||  parent == chib2p1) {
	    if (v[kDecay1P] != 0) {
	       report(ERROR, kFacilityString) << "kDecay1P previously set!" << endl << *decay << endl;
	       return ActionBase::kFailed;
	    }
	    v[kDecay1P] = decayNumber;
	 }
	 else if (parent == ups1) {
	    if (v[kDecay1S] != 0) {
	       report(ERROR, kFacilityString) << "kDecay1S previously set!" << endl << *decay << endl;
	       return ActionBase::kFailed;
	    }
	    v[kDecay1S] = decayNumber;

	    ups1s_p = decay_iter->parentPtr()->momentum();
	 }

      } // end loop over vertices

      if ( ups1s_p.mag2() > 2.9e6  &&
	   ups2s_p.mag2() > 2.9e6     ) {
	 v[kLastUpsilonPPerp] = ups3s_p.perp();
	 v[kLastUpsilonPPhi] = ups3s_p.phi();
	 v[kLastUpsilonPZ] = ups3s_p.z();
      }
      else if ( ups1s_p.mag2() > 2.9e6 ) {
	 v[kLastUpsilonPPerp] = ups2s_p.perp();
	 v[kLastUpsilonPPhi] = ups2s_p.phi();
	 v[kLastUpsilonPZ] = ups2s_p.z();
      }
      else {
	 v[kLastUpsilonPPerp] = ups1s_p.perp();
	 v[kLastUpsilonPPhi] = ups1s_p.phi();
	 v[kLastUpsilonPZ] = ups1s_p.z();
      }
   } // end if Monte Carlo
  
//    FAItem<TriggerData> level1_data;
//    extract(iFrame.record(Stream::kEvent), level1_data);
//    int bucket(level1_data->getL1AcceptBucket());
//    if ( bucket == -1 ) {
//       v[kL1AxialTracks] = -1;
//       v[kL1LowClusters] = -1;
//    } else {
//       v[kL1AxialTracks] = level1_data->getAxTrackCount(bucket);
//       v[kL1LowClusters] = level1_data->getCBLoCount(bucket);
//    }

   FATable<NavShower> showers;
   extract(iFrame.record(Stream::kEvent), showers);
   FATable<NavShower>::const_iterator shower_end = showers.end();

   double totalCCEnergyL3(0.);
   int significantShowersL3(0);
   double biggestShowerL3(0.);
   double zPosCCEnergyL3(0.);
   double zNegCCEnergyL3(0.);

   int showersOver10(0);
   int showersOver20(0);
   int showersOver30(0);
   int showersOver50(0);
   int showersOver200(0);
   int showersOver300(0);
   int showersOver500(0);
   int showersOver1000(0);

   for ( FATable<NavShower>::const_iterator shower_iter = showers.begin();
	 shower_iter != shower_end;
	 ++shower_iter ) {
      totalCCEnergyL3 += shower_iter->attributes().energy();
      if ( shower_iter->attributes().energy() > 0.100 ) {
	 significantShowersL3++;
      }
      if ( shower_iter->attributes().energy() > biggestShowerL3 ) {
	 biggestShowerL3 += shower_iter->attributes().energy();
      }
      if ( shower_iter->attributes().theta() < 95.*M_PI/180. ) {
	 zPosCCEnergyL3 += shower_iter->attributes().energy();
      }
      if ( shower_iter->attributes().theta() > 85.*M_PI/180. ) {
	 zNegCCEnergyL3 += shower_iter->attributes().energy();
      }

      if ( shower_iter->attributes().energy() > 0.010 ) {
	 showersOver10++;
	 if ( shower_iter->attributes().energy() > 0.020 ) {
	    showersOver20++;
	    if ( shower_iter->attributes().energy() > 0.030 ) {
	       showersOver30++;
	       if ( shower_iter->attributes().energy() > 0.050 ) {
		  showersOver50++;
		  if ( shower_iter->attributes().energy() > 0.200 ) {
		     showersOver200++;
		     if ( shower_iter->attributes().energy() > 0.300 ) {
			showersOver300++;
			if ( shower_iter->attributes().energy() > 0.500 ) {
			   showersOver500++;
			   if ( shower_iter->attributes().energy() > 1.000 ) {
			      showersOver1000++;
			   }}}}}}}}

   } // end loop over showers

   v[kL3Showers] = significantShowersL3;
   v[kL3TotalCCEnergy] = totalCCEnergyL3;
   v[kL3BiggestShower] = biggestShowerL3;
   v[kL3zPosCCEnergy] = zPosCCEnergyL3;
   v[kL3zNegCCEnergy] = zNegCCEnergyL3;

   FATable<NavTrack> tracks;
   extract(iFrame.record(Stream::kEvent), tracks);
   FATable<NavTrack>::const_iterator track_end = tracks.end();
   FATable< NavTrack >::const_iterator track_iter;
   FATable< NavTrack >::const_iterator other_iter;

   int goodTracksL4(0);
//     int goodTracksL5(0);
//     int goodTracksL5_tight(0);
//     int goodTracksL5_tight_cull(0);
//     int goodTracksL5_tight_cull2(0);
   for ( track_iter = tracks.begin();  track_iter != track_end;  ++track_iter ) {
      FAItem<TRSeedTrack> seedTrack = track_iter->seedTrack();
      FAItem<TRSeedTrackQuality> seedQuality = track_iter->seedQuality();
      if ( !seedQuality->originUsed()                              &&
	   seedQuality->numberHitsExpected() > 0                   &&
	   (double(seedQuality->numberHits()) /
	    double(seedQuality->numberHitsExpected())) > 0.4       &&
	   sqrt(1. - 1./(1 + sqr(seedTrack->cotTheta()))) <= 0.93  &&
	   (seedQuality->chiSquare() /
	    double(seedQuality->degreesOfFreedom())) < 20.         &&
	   fabs(seedTrack->d0()) < 0.025                           &&
	   fabs(seedTrack->z0()) < 0.15                               ) {
	 goodTracksL4++;
      }

//        if ((navtrack_iter->pionQuality()->fit()                                      &&
//  	   !navtrack_iter->pionQuality()->fitAbort()   )                            &&
//  	  ((navtrack_iter->pionQuality()->degreesOfFreedom() < 0)           ||
//  	   (navtrack_iter->pionQuality()->chiSquare()
//  	    / double(navtrack_iter->pionQuality()->degreesOfFreedom()) < 100.))     &&
//  	  (navtrack_iter->seedQuality()->numberHitsExpected() > 0)                  &&
//  	  (double(navtrack_iter->seedQuality()->numberLayers())
//  	   / navtrack_iter->seedQuality()->numberHitsExpected() > 0.5)              &&
//  	  (double(navtrack_iter->seedQuality()->numberLayers())
//  	   / navtrack_iter->seedQuality()->numberHitsExpected() < 1.2)              &&
//  	  (fabs(navtrack_iter->pionHelix()->d0()) < 0.03)                           &&
//  	  (fabs(navtrack_iter->pionHelix()->z0()) < 0.18)                           &&
//  	  (navtrack_iter->pionFit()->momentum().mag() > 0.01*beam_energy->value())  &&
//  	  (navtrack_iter->pionFit()->momentum().mag() < 1.5*beam_energy->value())   &&
//  	  (fabs(navtrack_iter->pionHelix()->cotTheta()) < 3.0424)                   &&
//  	  (sqrt(fabs(navtrack_iter->pionHelix()->errorMatrix()(KTHelix::kCotTheta, KTHelix::kCotTheta))) < 0.5) &&
//  	  (sqrt(fabs(navtrack_iter->pionHelix()->errorMatrix()(KTHelix::kZ0, KTHelix::kZ0))) < 0.25)               ) {
//  	 goodTracksL5++;
//        }

   }

   v[kL4Tracks] = goodTracksL4;

   FAItem<EventProperties> level5_data;
   extract(iFrame.record(Stream::kEvent), level5_data);
   v[kL5Tracks] = level5_data->nbChargedTracks();
   v[kL5VisibleEnergy] = level5_data->eVis();
   v[kL5CCEnergy] = level5_data->ccTotalEnergy();
   v[kL5BiggestShower] = level5_data->firstLargestEShower();

   FAItem<BeamEnergy> beam_energy;
   extract(iFrame.record(Stream::kStartRun), beam_energy);
   v[kL5BeamEnergy] = beam_energy->value();

   v[kNeutralEnergy] = level5_data->neutralEnergy();
   v[kCharge] = level5_data->netCharge();
   v[kPperp] = level5_data->totalMomentumVect().perp();
   v[kPphi] = level5_data->totalMomentumVect().phi();
   v[kPz] = level5_data->totalMomentumVect().z();
   v[kBiggestTrack] = level5_data->firstLargestPTrack();
   v[kBiggestMatched] = level5_data->firstMatchedEnergy();

   v[kShowersOver10] = showersOver10;
   v[kShowersOver20] = showersOver20;
   v[kShowersOver30] = showersOver30;
   v[kShowersOver50] = showersOver50;
   v[kShowersOver200] = showersOver200;
   v[kShowersOver300] = showersOver300;
   v[kShowersOver500] = showersOver500;
   v[kShowersOver1000] = showersOver1000;

   FAItem<BeamSpot> beamspot;
   extract(iFrame.record(Stream::kBeginRun), beamspot);

   double ci_perp(1000.);
   double weighted_z(1000.);
   double znumer(0.);
   double zdenom(0.);

   for ( track_iter = tracks.begin();  track_iter != track_end;  track_iter++ ) {
      if ( ! track_iter->seedQuality()->originUsed()            &&
	   ! track_iter->pionQuality()->fitAbort()              &&
	   1./fabs(track_iter->pionHelix()->curvature()) > 0.42  &&
	   ! track_iter->pionHelix()->hasNullErrorMatrix()        
	 ) {
	 // Secondary track loop to calculate pairwise intersections
	 for ( other_iter = track_iter;  other_iter != track_end;  other_iter++ ) {
	    if ( other_iter != track_iter  &&
		 ! other_iter->seedQuality()->originUsed()            &&
		 ! other_iter->pionQuality()->fitAbort()              &&
		 1./fabs(other_iter->pionHelix()->curvature()) > 0.42  &&
		 ! other_iter->pionHelix()->hasNullErrorMatrix()        
	       ) { 
	       double tx(-1000.), ty(-1000.), tz(-1000.), tsig2z(-1000.), tzsep(-1000.);

	       KTHelix track( *track_iter->pionHelix() );
	       KTHelix other( *other_iter->pionHelix() );

	       if ( calc_intersection( tx, ty, tz, tsig2z, tzsep, track, other ) ) {

		  double perp( sqrt(sqr(tx - beamspot->center().x()) + sqr(ty - beamspot->center().y())) );
		  if ( perp < ci_perp ) ci_perp = perp;

		  // uncertainty in the z intersection + mismatch in z + mismatch in perp
		  double z_uncert2( tsig2z + sqr(tzsep) + sqr(tx - beamspot->center().x()) + sqr(ty - beamspot->center().y()) );
		  znumer += tz / z_uncert2;
		  zdenom += 1. / z_uncert2;

	       } // end if successful intersection
	    } // end if secondary track passes quality cuts
	 } // end loop over secondary track

      } // end if primary track passes quality cuts
   } // end loop over tracks

   if ( zdenom != 0. ) {
      weighted_z = znumer / zdenom;
      weighted_z -= beamspot->center().z();
   }

   v[kL6RPhi] = ci_perp;
   v[kL6Z] = weighted_z;

   FAItem<TriggerL1Data> level1_decision;
   extract(iFrame.record(Stream::kEvent), level1_decision);
   v[kL1Decision] = 0.;
   if (level1_decision->isHadron()) v[kL1Decision] += 1.;
   if (level1_decision->isMuPair()) v[kL1Decision] += 2.;
   if (level1_decision->isCBSingleHi()) v[kL1Decision] += 4.;
   if (level1_decision->isCESingleHi()) v[kL1Decision] += 8.;
   if (level1_decision->isBarrelBhabha()) v[kL1Decision] += 16.;
   if (level1_decision->isEndcapBhabha()) v[kL1Decision] += 32.;
   if (level1_decision->isElTrack()) v[kL1Decision] += 64.;
   if (level1_decision->isRadTau()) v[kL1Decision] += 128.;
   if (level1_decision->isPulser()) v[kL1Decision] += 256.;
   if (level1_decision->isRandom()) v[kL1Decision] += 512.;
   if (level1_decision->isTwoTrack()) v[kL1Decision] += 1024.;
   if (level1_decision->isMinBias()) v[kL1Decision] += 2048.;

   FAItem<Level3TagWord> level3_decision;
   extract(iFrame.record(Stream::kEvent), level3_decision);
   v[kL3Decision] = 0.;
   if (level3_decision->hadron()) v[kL3Decision] += 1.;
   if (level3_decision->bhaGam()) v[kL3Decision] += 2.;
   if (level3_decision->radBha()) v[kL3Decision] += 4.;
   if (level3_decision->muPair()) v[kL3Decision] += 8.;
   if (level3_decision->track3()) v[kL3Decision] += 16.;
   if (level3_decision->barrelBhabha()) v[kL3Decision] += 32.;
   v[kL3AcceptCode] = level3_decision->acceptCode();
   v[kL3ClassCode] = level3_decision->classCode();

   FAItem<Level4Decision> level4_decision;
   extract(iFrame.record(Stream::kEvent), level4_decision);
   v[kL4Decision] = level4_decision->decision();

   FAItem<EventType> level5_decision;
   extract(iFrame.record(Stream::kEvent), level5_decision);
   v[kL5Decision] = level5_decision->hadron();

   v[kL6Decision] = (ci_perp < 0.005  &&  fabs(weighted_z) < 0.05);

   m_ntuple->fill(v);

   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
Efficiency::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
Efficiency::endRun( Frame& iFrame )         // anal4 equiv.
{
   report( DEBUG, kFacilityString ) << "here in endRun()" << endl;

   return ActionBase::kPassed;
}
*/

DABoolean Efficiency::calc_intersection( double& x, double& y, double& z, double& sig2z, double& zsep,
					       KTHelix& a, KTHelix& b )
{
   x = y = z = sig2z = zsep = 1000.;  // To more easily find unchecked failures

   // Express the two helices in terms of (x - xa)^2 + (y - ya)^2 == ra^2
   double ra( 1./2./a.curvature() );
   double xa( -(a.d0() + ra) * sin(a.phi0()) );
   double ya( (a.d0() + ra) * cos(a.phi0()) );

   double rb( 1./2./b.curvature() );
   double xb( -(b.d0() + rb) * sin(b.phi0()) );
   double yb( (b.d0() + rb) * cos(b.phi0()) );

   // Zero or infinitely many solutions
   // I don't want to deal with either case
   if ( xa == xb  &&  ya == yb ) return false;

   double disc( (pow(4.*sqr(ra)*(xa - xb) - 
		     4.*(sqr(rb)*(xa - xb) + 
			(xa + xb)*(sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb)))
		     ,2.) - 16.*(sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb))*
		 (pow(xa,4.) - 2.*sqr(xa)*sqr(xb) + pow(xb,4.) + 
		  2.*sqr(xb)*(sqr(ra) - sqr(rb) + sqr(ya - yb)) + 
		  2.*sqr(xa)*(-sqr(ra) + sqr(rb) + sqr(ya - yb)) + 
		  pow(-sqr(ra) + sqr(rb) + sqr(ya - yb),2.) - 
		  4.*sqr(rb)*sqr(ya - yb)))/
		(64.*pow(sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb),2.)) );
   // no real solutions
   if ( disc < 0 ) return false;

   double pre( (sqr(rb)*(xa - xb) + sqr(ra)*(-xa + xb) + 
		(xa + xb)*(sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb)))/
	       (2.*(sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb))) );

   // The two x solutions
   double xsol1( pre + sqrt( disc ) );
   double xsol2( pre - sqrt( disc ) );

   // Two possibilities for the y solution to each x solution
   double ysol1a( yb + sqrt( sqr(rb) - sqr(xsol1 - xb) ) );
   double ysol1b( yb - sqrt( sqr(rb) - sqr(xsol1 - xb) ) );
   double ysol1;
   if ( fabs( sqr(xsol1 - xa) + sqr(ysol1a - ya) - sqr(ra) ) <
	fabs( sqr(xsol1 - xa) + sqr(ysol1b - ya) - sqr(ra) )   )
      ysol1 = ysol1a;
   else
      ysol1 = ysol1b;

   double ysol2a( yb + sqrt( sqr(rb) - sqr(xsol2 - xb) ) );
   double ysol2b( yb - sqrt( sqr(rb) - sqr(xsol2 - xb) ) );
   double ysol2;
   if ( fabs( sqr(xsol2 - xa) + sqr(ysol2a - ya) - sqr(ra) ) <
	fabs( sqr(xsol2 - xa) + sqr(ysol2b - ya) - sqr(ra) )   )
      ysol2 = ysol2a;
   else
      ysol2 = ysol2b;

   // Calculate the arclength of each solution along the two tracks.
   // Throw out a solution if the particle needs to travel (too far)
   // backward to get to it. If both solutions are okay, take the one
   // closest to the origin.
   DABoolean arclength1_ok( arclength_test( xsol1, ysol1, a, b ) );
   DABoolean arclength2_ok( arclength_test( xsol2, ysol2, a, b ) );
   
   if ( !arclength1_ok  &&  !arclength2_ok ) return false;

   else if ( arclength1_ok  &&  !arclength2_ok ) {
      x = xsol1;  y = ysol1;
   }

   else if ( !arclength1_ok  &&  arclength2_ok ) {
      x = xsol2;  y = ysol2;
   }

   else if ( sqr(xsol1) + sqr(ysol1) < sqr(xsol2) + sqr(ysol2) ) {
      x = xsol1;  y = ysol1;
   }

   else {
      x = xsol2;  y = ysol2;
   }      

   double asinphi1( 2. * a.curvature() * (x * cos(a.phi0()) + y * sin(a.phi0())) );
   double acosphi1( 2. * a.curvature() * (x * sin(a.phi0()) - y * cos(a.phi0())
					  + a.d0()) + 1. );
   double aarclength( atan2(asinphi1, acosphi1) / 2. / a.curvature() );

   double bsinphi1( 2. * b.curvature() * (x * cos(b.phi0()) + y * sin(b.phi0())) );
   double bcosphi1( 2. * b.curvature() * (x * sin(b.phi0()) - y * cos(b.phi0())
					  + b.d0()) + 1. );
   double barclength( atan2(bsinphi1, bcosphi1) / 2. / b.curvature() );

   double az( a.cotTheta() * aarclength + a.z0() );
   double bz( b.cotTheta() * barclength + b.z0() );
   double sig2_az( a.errorMatrix()(KTHelix::kCotTheta, KTHelix::kCotTheta) * sqr(aarclength)
		   + a.errorMatrix()(KTHelix::kZ0, KTHelix::kZ0)
		   + 2. * aarclength * a.errorMatrix()(KTHelix::kCotTheta, KTHelix::kZ0) );
   double sig2_bz( b.errorMatrix()(KTHelix::kCotTheta, KTHelix::kCotTheta) * sqr(barclength)
		   + b.errorMatrix()(KTHelix::kZ0, KTHelix::kZ0)
		   + 2. * barclength * b.errorMatrix()(KTHelix::kCotTheta, KTHelix::kZ0) );

   z = (az/sig2_az + bz/sig2_bz) / (1./sig2_az + 1./sig2_bz);
   sig2z = 1. / (1./sig2_az + 1./sig2_bz);
   zsep = az - bz;

   // Because it is not useful for the `closest_intersection'
   // algorithm, I had to throw out a great deal of lovely code that
   // calculates uncertanties in x and y.  If you want this, ask me
   // about it.
   return true;
}

DABoolean Efficiency::arclength_test( double x, double y, KTHelix& a, KTHelix& b )
{
   const double tailCut = 0.005;

   double asinphi1( 2. * a.curvature() * (x * cos(a.phi0()) + y * sin(a.phi0())) );
   double acosphi1( 2. * a.curvature() * (x * sin(a.phi0()) - y * cos(a.phi0())
					  + a.d0()) + 1. );
   double aarclength( atan2(asinphi1, acosphi1) / 2. / a.curvature() );

   double bsinphi1( 2. * b.curvature() * (x * cos(b.phi0()) + y * sin(b.phi0())) );
   double bcosphi1( 2. * b.curvature() * (x * sin(b.phi0()) - y * cos(b.phi0())
					  + b.d0()) + 1. );
   double barclength( atan2(bsinphi1, bcosphi1) / 2. / b.curvature() );

   return ( aarclength > -tailCut  &&  aarclength < M_PI/2./fabs(a.curvature()) )  &&
      ( barclength > -tailCut  &&  barclength < M_PI/2./fabs(b.curvature()) );
}

//
// const member functions
//

//
// static member functions
//
