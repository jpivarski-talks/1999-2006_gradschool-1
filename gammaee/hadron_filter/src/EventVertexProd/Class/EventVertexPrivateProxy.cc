// -*- C++ -*-
//
// Package:     <EventVertexProd>
// Module:      EventVertexPrivateProxy
// 
// Description: Proxy to make event vertex
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Roy A. Briere, Michael Watkins
// Created:     Mon Mar 18 23:06:31 EST 2002
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files
#include <stdlib.h>   // for ::exit
#include <assert.h>

#include <memory>  //for auto_ptr

// user include files
#include "DAException/DAException.h"

#include "DataHandler/Record.h"
#include "DataHandler/Frame.h"

#include "EventVertexProd/EventVertexPrivateProxy.h"
#include "EventVertexProd/EventVertexProd.h"
#include "EventVertexProd/EventVertexHolder.h"

#include "Experiment/report.h"
#include "Experiment/units.h"  // for converting to/from standard CLEO units

#include "FrameAccess/extract.h"           
#include "FrameAccess/FATable.h"
#include "FrameAccess/FAItem.h"

#include "ProxyBind/ProxyBoundMethodAction.h" //need for PROXY_BIND_METHOD

//Tracking
#include "Navigation/NavTrack.h"
#include "TrackRoot/TRTrackCandidateFitQuality.h"
#include "TrackRoot/TRTrackFitQuality.h"
#include "TrackRoot/TRTrackQuality.h"

//vertexing
#include "VXFit/VXFitInterfaceVertex.h"
//#include "VXFit/VXFitVeeCandidate.h"
#include "VXFit/VXFittable.h"

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
#include <vector>
//#include <set>
#include <map>
//#include <algorithm>
//#include <utility>

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "EventVertexProd.EventVertexPrivateProxy";

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: proxyone.cc,v 1.12 2000/12/04 19:11:16 cdj Exp $";
static const char* const kTagString = "$Name: v03_06_00 $";

//
// static data member definitions
//

//
// constructors and destructor
//
EventVertexPrivateProxy::EventVertexPrivateProxy(EventVertexHolder* eventVertexHolder )
  : m_EventVertexPrivate( 0 ),
    m_eventVertexHolder (eventVertexHolder)
{
  //bind 'auxilliary' functions that you want called when a
  // new Record on the particular Stream appears
  //bind( &EventVertexPrivateProxy::boundMethod, Stream::kBeginRun );
}

// EventVertexPrivateProxy::EventVertexPrivateProxy( const EventVertexPrivateProxy& iproxy )
// {
//   *this = iproxy;
// }

EventVertexPrivateProxy::~EventVertexPrivateProxy()
{
  delete m_EventVertexPrivate;
}

//
// assignment operators
//
// const EventVertexPrivateProxy& EventVertexPrivateProxy::operator=( const EventVertexPrivateProxy& iproxy )
// {
//   if( this != &iproxy ) {
//      // do actual copying here, plus:
//      // "SuperClass"::operator=( iproxy );
//   }
//
//   return *this;
// }

//
// member functions
//
void
EventVertexPrivateProxy::invalidateCache()
{
  delete m_EventVertexPrivate;
  m_EventVertexPrivate = 0;
}

const EventVertexPrivateProxy::value_type*
EventVertexPrivateProxy::faultHandler(const Record& iRecord,
			       const DataKey& iKey)
{
  // be assertive: there should be no cached data at this point, else
  // it's a programming error
  assert(m_EventVertexPrivate == 0);

  //if an exception is thrown during this function, p_EventVertex will
  // automatically delete the object it is refering to
  auto_ptr<EventVertexPrivate> p_EventVertexPrivate;

  // ---------- create the new object --------------------

  report( DEBUG, kFacilityString ) << "here in EventVertexPrivateProxy, faultHandler" << endl; 
  //----------------------------------------------------------------------->
  //type define a NavTrack iterator for later convenance
  typedef FATable< NavTrack >::const_iterator trackItr;  
  //flags for event type
  Count goodEvent         = EventVertexPrivate::kGoodEvent ;
  Count tooFewInitial     = EventVertexPrivate::kTooFewInitial ;
  Count tooFewPassKinCuts = EventVertexPrivate::kTooFewPassKinCuts ;
  Count tooManyChi2Drop   = EventVertexPrivate::kTooManyChi2Drop;
  Count vertexingFails    = EventVertexPrivate::kVertexingFails;
  Count eventFlag         = goodEvent;
  double run   = iRecord.syncValue().runNumber();
  double event = iRecord.syncValue().eventNumber();

  // Create a table of tracks and fill it.
  FATable< NavTrack > trackTable;
  report( DEBUG, kFacilityString ) << "extract trackTable"<<endl;
  extract( iRecord, trackTable );
  // set up the begining and the end of the trackTable
  FATable< NavTrack >::const_iterator trackTableBegin = trackTable.begin();
  FATable< NavTrack >::const_iterator trackTableEnd = trackTable.end();

  //create a vector of pointers to NavTrack, initializing all entries to null pointers,
  const NavTrack* nullTrack = 0;
  STL_VECTOR(const NavTrack*) vectorTracks(
     trackTable.back().identifier()+1, nullTrack );

  
  //get the B-field
  FAItem< MagneticField > cleo3BField;
  report( DEBUG, kFacilityString ) << "extract cleo3BField"<<endl;
  extract( iRecord.frame().record(Stream::kStartRun) , cleo3BField );

  //Counter for total number dropped chi2s
  Count numTrackRemoved = 0;

  //get number of Tracks in event
  Count numTrackTotal = trackTable.size();
  //tracks passing kinematic cuts
  Count numTrackPassKinCuts = 0;
  //tracks in final vertex
  Count numTrackLeft = 0;
  //tracks in initial Vertex 
  Count initialNumTracksInVertex = 0;
  //   //null Hep3Vector
  Hep3Vector finalPosition( 0, 0, 0 );
  //   //null 7*7 HepSymMatrix
  HepSymMatrix finalErrorMatrix(7, 0);
  // null 3*3 HepSymMatrix
  HepSymMatrix smallFinalErrorMatrix(3, 0);
  // final vertex Chi2
  double finalVertexChi2  = 0;
  //STL_VECTOR of Track IDs in final vertex
  STL_VECTOR(NavTrack::Identifier) vecOfTrackIDs;
  //STL_VECTOR of Vertex Chi2
  STL_VECTOR(double) vecOfChiSquares;
  //STL_VECTOR of Removed track Chi2
  STL_VECTOR(double) vecOfRemovedTrackChi2;
  //Flag if removed chi2's normalized
  DABoolean cutNormFlag = (*m_eventVertexHolder).TrackCutNorm_Param();

  if(numTrackTotal<(*m_eventVertexHolder).MinTrk_Param())
  {
     eventFlag = tooFewInitial;
  }
  else
  {
     //loop over all tracks and place ids into the vector
     for( trackItr currentTrk = trackTableBegin;
          currentTrk != trackTableEnd ;
          currentTrk++ )
     {
        //check the following
        //    d0,z0,trkMomentum,and was the fit aborted
        //get the d0 and z0
        FAItem<TRHelixFit> currentHelix = (*currentTrk).pionHelix();
        double currentD0 = currentHelix->d0();
        double currentZ0 = currentHelix->z0();
        //get the momentum and postion of the track
        HepPoint3D currentPosition( currentHelix->position() ) ;
        double currentMom = 
           currentHelix->momentum( cleo3BField->BField( currentPosition ) ).mag();
        //put a pointer to the NavTrack in the slot given by the identifier
        if( (abs(currentD0) < (*m_eventVertexHolder).d0_Param()) &&
            (abs(currentZ0) < (*m_eventVertexHolder).z0_Param()) &&
            (currentMom     > (*m_eventVertexHolder).TMom_Param())   &&
            !( (*currentTrk).pionQuality()->fitAbort() ) )
        {
           // vectorTracks[(*currentTrk).identifier()] = &(*currentTrk);
           vectorTracks[(*currentTrk).identifier()] = &(*currentTrk);
           //Count number of tracks that pass cuts
           numTrackPassKinCuts++;
        }
     }
  }
  //check if cuts has removed too many tracks to vertex
  if( ( numTrackPassKinCuts<(*m_eventVertexHolder).MinTrk_Param() ) &&
      eventFlag==goodEvent )
  {
     eventFlag = tooFewPassKinCuts;
  }
  //set number of Tracks In Vertex 
  initialNumTracksInVertex=numTrackPassKinCuts;
 
//   //setup the 4momentum, 3position, and ErrorMatrix ready
//   //first time in loop variables
//   double initialX = 0;
//   double initialY = 0;
//   double initialZ = 0;
//   double initialXsig = 0;
//   double initialYsig = 0;
//   double initialZsig = 0;
//   double initialChi2 = 0;
//   double initialMaxChi2 = 0;
//   double finalMaxChi2 = 0;
//   //for delta Chi2 
//   double Chi2VertexStepCurrent = 0;
//   double Chi2VertexStepLast = 0;
//   double MaxChi2Last = 0;
//   double LargestChi2 = 0;
//   //first Delta chi2
//   double firstDeltaChi2 = 0;
//   //final Delta chi2
//   double finalDeltaChi2 = 0;
//   //instantaneous delta chi2
//   double DeltaChi2 = 0; 
  
  //check if the Event is still Vertexable
  if(eventFlag==goodEvent)
  {
     Count numberTracksInVertex = initialNumTracksInVertex;
     //counter for number of Chi2 >MaxChi2_Param();
     DABoolean areThereBadChi2 = false;
     DABoolean multiDropHappened = false;
     do
     {
        VXFitInterfaceVertex tempFit( *cleo3BField, VXFittable::propagateAsResonance );
        //vertex the good tracks
        //Check if at leasts as many tracks as MinTrk_Param()
        // passed the cuts
        if(numberTracksInVertex>=(*m_eventVertexHolder).MinTrk_Param() &&
           eventFlag==goodEvent )
        {
           //will recount number in Vertex
           numberTracksInVertex=0;
           //loop over tracks and add tracks to the vertex
           for( trackItr currentTrk = trackTableBegin;
                currentTrk != trackTableEnd ;
                currentTrk++ )
           {
              //  provided they are not null pointers
              if(vectorTracks[(*currentTrk).identifier()] != nullTrack)
              {
                 //add track to vertex
//                  //make initial guess for the beamspot
//                  //NOT implimented in VXFit
//                  HepPoint3D guessVertex( -0.002, 0.0, 0.0 );
                 report( DEBUG, kFacilityString ) << "adding track to vertex"<<endl;
                 KTKinematicFixedBz currentBz(
                    *(*currentTrk).pionFit(),
                    (*cleo3BField).BField().z() );
                 tempFit.addKTKinematicData(
                    currentBz, (*currentTrk).identifier() );
                 numberTracksInVertex++;
              }
           }
        }
        //go to next event if to few tracks
        if( numberTracksInVertex<(*m_eventVertexHolder).MinTrk_Param() &&
            eventFlag==goodEvent )
        {
           eventFlag = tooManyChi2Drop;
        }
        //fit the vertex
        if(eventFlag==goodEvent)
        {
           try
           {
              //blank the vector of track IDs
              vecOfTrackIDs.clear();
              report( DEBUG, kFacilityString ) << "fitting vertex"<<endl;
              tempFit.fitVertex();
              finalPosition = tempFit.fitResult().position();
              finalErrorMatrix = tempFit.fitResult().errorMatrix();
              finalVertexChi2 = tempFit.fitResult().fitChiSquare();
              vecOfChiSquares.push_back(finalVertexChi2);
//              Chi2VertexStepCurrent = tempFit.fitResult().fitChiSquare();
//               //add the current vertex Chi2 to the vector
//               vecOfChiSquares.push_back(Chi2VertexStepCurrent);
//               finalVertexChi2 = Chi2VertexStepCurrent;
//               if(numberTracksInVertex == initialNumTracksInVertex)
//               {
//                  initialX = finalPosition.x();
//                  initialY = finalPosition.y();
//                  initialZ = finalPosition.z();
//                  initialXsig = sqrt( finalErrorMatrix(KTKinematicData::kX,
//                                                       KTKinematicData::kX) );
//                  initialYsig = sqrt( finalErrorMatrix(KTKinematicData::kY,
//                                                       KTKinematicData::kY) );
//                  initialZsig = sqrt( finalErrorMatrix(KTKinematicData::kZ,
//                                                       KTKinematicData::kZ) );
//                  initialChi2 = finalVertexChi2;
//               }
//               //loop  over vertex and drop Tracks with Chi2>50
//               if( numberTracksInVertex > 5 &&
//                   !multiDropHappened )
//               {
//                  FAItem<NavTrack> trackToDrop;
//                  for(VXFittableInfoList::const_iterator
//                         currentItr = tempFit.fitParentInfoList().begin();
//                      currentItr != tempFit.fitParentInfoList().end();
//                      ++currentItr) 
//                  {
//                     multiDropHappened = true;
//                     double chi2 = (*currentItr).dChiSquare();
//                     report( DEBUG, kFacilityString) << "trackID = "
//                                                       << (*currentItr).index()
//                                                       << "     chi2 = " << chi2 <<endl;
//                     if( chi2 > 100 )
//                     {
//                        trackToDrop = vectorTracks[(*currentItr).index()];
//                        numTrackRemoved++;
//                        vectorTracks[trackToDrop->identifier()] = nullTrack;
//                        vecOfRemovedTrackChi2.push_back(chi2);
//                        report( DEBUG, kFacilityString) << "trackID = "
//                                                          << (*currentItr).index()
//                                                          << " dropped" <<  endl;
//                        areThereBadChi2 = true;
//                     }
//                  }
//               }
              //loop over the tracks in the vertex,
              //  finding the chi2 of the vertex and the largest
              //  contributer to the chi2
              areThereBadChi2 = false;
              double maxChi2 = 0;
              FAItem<NavTrack> maxTrack;
              double largestChi2 = 0;
              FAItem<NavTrack> largestTrack;
              for(VXFittableInfoList::const_iterator
                     parentItr = tempFit.fitParentInfoList().begin();
                  parentItr != tempFit.fitParentInfoList().end();
                  ++parentItr)
              {
                 if( vectorTracks[(*parentItr).index()] != nullTrack )
                 {
                    //get the trackChi2
                    double trackChi2 = (*parentItr).dChiSquare();
                    report( DEBUG, kFacilityString) << "tempTrackChi2 = "
                                                    << trackChi2
                                                    << "      trackID = "
                                                    << (*parentItr).index()
                                                    << endl;
                    if( trackChi2 > largestChi2 )
                    {
                       //find the larges track
                       largestChi2  = trackChi2;
                       largestTrack = vectorTracks[(*parentItr).index()] ;
                    }
                 }
              }
              //double for track chi2 to cut on
              double trackChi2ToCut = 0;
              //check if normalizing
              if(cutNormFlag)
              {
                 double norm = ((2.0*(double)numberTracksInVertex-3.0)/
                                (double)numberTracksInVertex ) ;
                 trackChi2ToCut = largestChi2*norm;
              }
              else
              {
                 trackChi2ToCut = largestChi2;
              }
              //remove the largest track from the vectorTracks
              if(trackChi2ToCut > (*m_eventVertexHolder).MaxChi2_Param() )
              {
                 maxChi2 = trackChi2ToCut;
                 //add the maxChi2 to the vector
                 // however, want to add it un-normalized always
                 vecOfRemovedTrackChi2.push_back(largestChi2);
//                 finalmaxChi2 = maxChi2;
                 // set maxTrack equal to the correct track in the vector
                 maxTrack = largestTrack;
                 //mark maxTrack in vector of Tracks
                 report( DEBUG, kFacilityString ) << "Track Dropped " << endl;
                 numTrackRemoved++;                 
                 vectorTracks[maxTrack->identifier()] = nullTrack;
                 //mark that a bad chi2 was found
                 areThereBadChi2 = true;
                 report( DEBUG, kFacilityString ) << "\n Max Chi2 = "
                                                  << maxChi2
                                                  << "     trackID = "
                                                  << maxTrack->identifier()
                                                  << endl;
              }
              report( DEBUG, kFacilityString ) << "Largest Chi2 = "
                                                 << largestChi2 << endl;
//               //Calculate DeltaChi2;
//               if(Chi2VertexStepLast!=0)
//               {
//                  DeltaChi2 = Chi2VertexStepLast - Chi2VertexStepCurrent -
//                     maxChi2Last;
//               }
//                //get the first maxChi2
//               if(initialNumTracksInVertex==numberTracksInVertex
//                  &&  maxChi2!= 0)
//               {
//                  //get initial maxChi2
//                  initialmaxChi2 = maxChi2;
//               }
//               //first delta Chi2 plots
//               if(initialNumTracksInVertex-numberTracksInVertex==1)
//               {
//                  //record first DeltaChi2
//                  firstDeltaChi2 = DeltaChi2;
//               }
//               //all delta Chi2 plots
//               if( numberTracksInVertex != initialNumTracksInVertex &&
//                   Chi2VertexStepLast   != 0 )
//               {
//               }
//               //finishes do loop
//               if(areThereBadChi2==false &&
//                  Chi2VertexStepLast != 0 &&
//                  numberTracksInVertex >= (*m_eventVertexHolder).MinTrk_Param())
//               {
//                  //record final delta
//                  finalDeltaChi2 = DeltaChi2;
//               }
//               //will not pass Track number cut
//               if(areThereBadChi2==true &&
//                  numberTracksInVertex <=
//                       (*m_eventVertexHolder).MinTrk_Param() )
//               {
//                  //record final delta                 
//                  finalDeltaChi2 = DeltaChi2;
//               }
//               //need to undo normalization for calculation of Delta chi2
//               if( !(cutNormFlag) )
//               {
//                  maxChi2Last = maxChi2;
//               }
//               else
//               {
//                  double norm = ((2.0*(double)numberTracksInVertex-3.0)/
//                                 (double)numberTracksInVertex ) ;
//                  maxChi2Last = maxChi2 / norm; 
//               }
//               Chi2VertexStepLast = Chi2VertexStepCurrent;

              //get IDs of tracks in Vertex
              for(VXFittableInfoList::const_iterator
                     Itr = tempFit.fitParentInfoList().begin();
                  Itr != tempFit.fitParentInfoList().end();
                  ++Itr)
              {
                   vecOfTrackIDs.push_back( (*Itr).index() );
              }
           }
           catch ( VXFitException& myException )
           {
              report( DEBUG, kFacilityString ) << "fit failled"<<endl;
              numTrackLeft = numberTracksInVertex;
              eventFlag = vertexingFails;
//              finalDeltaChi2 = DeltaChi2;
           }
        }
        //repeat until all tracks are below the chi2 contribution cut, 
     }while( areThereBadChi2 &&
             eventFlag       == goodEvent);
     //get final number of tracks
     numTrackLeft =  initialNumTracksInVertex - numTrackRemoved;
     if(numTrackLeft <  (*m_eventVertexHolder).MinTrk_Param() &&
        eventFlag    == goodEvent)
     {
        eventFlag = tooManyChi2Drop;
     }
  }

  report( DEBUG, kFacilityString ) << "\n numTrackTotal = " << numTrackTotal
                                   << "\n numTrackPassKinCuts = " << numTrackPassKinCuts
                                   << "\n numTrackRemoved = " <<numTrackRemoved
                                   << "\n numTrackLeft = " <<numTrackLeft
                                   << "\n eventFlag = " <<eventFlag <<endl;
  report( DEBUG, kFacilityString ) << "copying errorMatrices" <<endl;
  //Copy the position part of finalErrorMatrix to smallFinalErrorMatrix
  smallFinalErrorMatrix(EventVertexPrivate::kX,
                        EventVertexPrivate::kX) = finalErrorMatrix(KTKinematicData::kX,
                                                                   KTKinematicData::kX);
  smallFinalErrorMatrix(EventVertexPrivate::kX,
                        EventVertexPrivate::kY) = finalErrorMatrix(KTKinematicData::kX,
                                                                   KTKinematicData::kY);
  smallFinalErrorMatrix(EventVertexPrivate::kX,
                        EventVertexPrivate::kZ) = finalErrorMatrix(KTKinematicData::kX,
                                                                   KTKinematicData::kZ);
  smallFinalErrorMatrix(EventVertexPrivate::kY,
                        EventVertexPrivate::kX) = finalErrorMatrix(KTKinematicData::kY,
                                                                   KTKinematicData::kX);
  smallFinalErrorMatrix(EventVertexPrivate::kY,
                        EventVertexPrivate::kY) = finalErrorMatrix(KTKinematicData::kY,
                                                                   KTKinematicData::kY);
  smallFinalErrorMatrix(EventVertexPrivate::kY,
                        EventVertexPrivate::kZ) = finalErrorMatrix(KTKinematicData::kY,
                                                                   KTKinematicData::kZ);
  smallFinalErrorMatrix(EventVertexPrivate::kZ,
                        EventVertexPrivate::kX) = finalErrorMatrix(KTKinematicData::kZ,
                                                                   KTKinematicData::kX);
  smallFinalErrorMatrix(EventVertexPrivate::kZ,
                        EventVertexPrivate::kY) = finalErrorMatrix(KTKinematicData::kZ,
                                                                   KTKinematicData::kY);
  smallFinalErrorMatrix(EventVertexPrivate::kZ,
                        EventVertexPrivate::kZ) = finalErrorMatrix(KTKinematicData::kZ,
                                                                   KTKinematicData::kZ);
  report( DEBUG, kFacilityString ) << "\n smallFinalErrorMatrix = "
                                   << smallFinalErrorMatrix(EventVertexPrivate::kX, EventVertexPrivate::kX)
                                   << "  "
                                   << smallFinalErrorMatrix(EventVertexPrivate::kX, EventVertexPrivate::kY)
                                   << "  "
                                   << smallFinalErrorMatrix(EventVertexPrivate::kX, EventVertexPrivate::kZ)
                                   << "\n smallFinalErrorMatrix = "
                                   << smallFinalErrorMatrix(EventVertexPrivate::kY, EventVertexPrivate::kX)
                                   << "  "
                                   << smallFinalErrorMatrix(EventVertexPrivate::kY, EventVertexPrivate::kY)
                                   << "  "
                                   << smallFinalErrorMatrix(EventVertexPrivate::kY, EventVertexPrivate::kZ)
                                   << "\n smallFinalErrorMatrix = "
                                   << smallFinalErrorMatrix(EventVertexPrivate::kZ, EventVertexPrivate::kX)
                                   << "  "
                                   << smallFinalErrorMatrix(EventVertexPrivate::kZ, EventVertexPrivate::kY)
                                   << "  "
                                   << smallFinalErrorMatrix(EventVertexPrivate::kZ, EventVertexPrivate::kZ)
                                   << endl;
  report( DEBUG, kFacilityString )
     << "\n finalErrorMatrix      = "
     << finalErrorMatrix(  KTKinematicData::kPx, KTKinematicData::kPx)
     << "  "
     << finalErrorMatrix(  KTKinematicData::kPx, KTKinematicData::kPy)
     << "  "
     << finalErrorMatrix(  KTKinematicData::kPx, KTKinematicData::kPz)
     << "  "
     << finalErrorMatrix(  KTKinematicData::kPx, KTKinematicData::kEnergy)
     << "  "
     << finalErrorMatrix(  KTKinematicData::kPx, KTKinematicData::kX)
     << "  "
     << finalErrorMatrix(  KTKinematicData::kPx, KTKinematicData::kY)
     << "  "
     << finalErrorMatrix(  KTKinematicData::kPx, KTKinematicData::kZ)
     << "\n finalErrorMatrix      = "
     << finalErrorMatrix(  KTKinematicData::kPy, KTKinematicData::kPx)
     << "  "
     << finalErrorMatrix(  KTKinematicData::kPy, KTKinematicData::kPy)
     << "  "
     << finalErrorMatrix(  KTKinematicData::kPy, KTKinematicData::kPz)
     << "  "
     << finalErrorMatrix(  KTKinematicData::kPy, KTKinematicData::kEnergy)
     << "  "
     << finalErrorMatrix(  KTKinematicData::kPy, KTKinematicData::kX)
     << "  "
     << finalErrorMatrix(  KTKinematicData::kPy, KTKinematicData::kY)
     << "  "
     << finalErrorMatrix(  KTKinematicData::kPy, KTKinematicData::kZ)
     << "\n finalErrorMatrix      = "
     << finalErrorMatrix(  KTKinematicData::kPz, KTKinematicData::kPx)
     << "  "
     << finalErrorMatrix(  KTKinematicData::kPz, KTKinematicData::kPy)
     << "  "
     << finalErrorMatrix(  KTKinematicData::kPz, KTKinematicData::kPz)
     << "  "
     << finalErrorMatrix(  KTKinematicData::kPz, KTKinematicData::kEnergy)
     << "  "
     << finalErrorMatrix(  KTKinematicData::kPz, KTKinematicData::kX)
     << "  "
     << finalErrorMatrix(  KTKinematicData::kPz, KTKinematicData::kY)
     << "  "
     << finalErrorMatrix(  KTKinematicData::kPz, KTKinematicData::kZ)
     << "\n finalErrorMatrix      = "
     << finalErrorMatrix(  KTKinematicData::kEnergy, KTKinematicData::kPx)
     << "  "
     << finalErrorMatrix(  KTKinematicData::kEnergy, KTKinematicData::kPy)
     << "  "
     << finalErrorMatrix(  KTKinematicData::kEnergy, KTKinematicData::kPz)
     << "  "
     << finalErrorMatrix(  KTKinematicData::kEnergy, KTKinematicData::kEnergy)
     << "  "
     << finalErrorMatrix(  KTKinematicData::kEnergy, KTKinematicData::kX)
     << "  "
     << finalErrorMatrix(  KTKinematicData::kEnergy, KTKinematicData::kY)
     << "  "
     << finalErrorMatrix(  KTKinematicData::kEnergy, KTKinematicData::kZ)
     << "\n finalErrorMatrix      = "
     << finalErrorMatrix(  KTKinematicData::kX, KTKinematicData::kPx)
     << "  "
     << finalErrorMatrix(  KTKinematicData::kX, KTKinematicData::kPy)
     << "  "
     << finalErrorMatrix(  KTKinematicData::kX, KTKinematicData::kPz)
     << "  "
     << finalErrorMatrix(  KTKinematicData::kX, KTKinematicData::kEnergy)
     << "  "
     << finalErrorMatrix(  KTKinematicData::kX, KTKinematicData::kX)
     << "  "
     << finalErrorMatrix(  KTKinematicData::kX, KTKinematicData::kY)
     << "  "
     << finalErrorMatrix(  KTKinematicData::kX, KTKinematicData::kZ)
     << "\n finalErrorMatrix      = "
     << finalErrorMatrix(  KTKinematicData::kY, KTKinematicData::kPx)
     << "  "
     << finalErrorMatrix(  KTKinematicData::kY, KTKinematicData::kPy)
     << "  "
     << finalErrorMatrix(  KTKinematicData::kY, KTKinematicData::kPz)
     << "  "
     << finalErrorMatrix(  KTKinematicData::kY, KTKinematicData::kEnergy)
     << "  "
     << finalErrorMatrix(  KTKinematicData::kY, KTKinematicData::kX)
     << "  "
     << finalErrorMatrix(  KTKinematicData::kY, KTKinematicData::kY)
     << "  "
     << finalErrorMatrix(  KTKinematicData::kY, KTKinematicData::kZ)
     << "\n finalErrorMatrix      = "
     << finalErrorMatrix(  KTKinematicData::kZ, KTKinematicData::kPx)
     << "  "
     << finalErrorMatrix(  KTKinematicData::kZ, KTKinematicData::kPy)
     << "  "
     << finalErrorMatrix(  KTKinematicData::kZ, KTKinematicData::kPz)
     << "  "
     << finalErrorMatrix(  KTKinematicData::kZ, KTKinematicData::kEnergy)
     << "  "
     << finalErrorMatrix(  KTKinematicData::kZ, KTKinematicData::kX)
     << "  "
     << finalErrorMatrix(  KTKinematicData::kZ, KTKinematicData::kY)
     << "  "
     << finalErrorMatrix(  KTKinematicData::kZ, KTKinematicData::kZ)
     <<endl;
     
  
  //<-----------------------------------------------------------------------
  //have p_EventVertexPrivate hold onto the new object
  report( DEBUG, kFacilityString ) << "p_EventVertexPrivate.reset(...)"<<endl; 
  p_EventVertexPrivate.reset(new EventVertexPrivate( finalPosition,
                                                     smallFinalErrorMatrix,
                                                     finalVertexChi2,
                                                     numTrackPassKinCuts,
                                                     numTrackLeft,
                                                     eventFlag,
                                                     vecOfTrackIDs,
                                                     vecOfChiSquares,
                                                     vecOfRemovedTrackChi2,
                                                     cutNormFlag) );
  
  //Since no exception happened, tell p_EventVertexPrivate to give its pointer to
  // m_EventVertexPrivate
  //delete finalFitResult;
  return ( m_EventVertexPrivate = p_EventVertexPrivate.release() );
}

//
// const member functions
//

//
// static member functions
//

//
// 'bound' functions
//

//void
//EventVertexPrivateProxy::boundMethod( const Record& iRecord )
//{
//   report( INFO, kFacilityString) <<"BoundMethod: " <<iRecord.stream().value() << endl;
//}

//-----------------------------------------------
// DO NOT DELETE
#include "ProxyBind/Template/ProxyBindableTemplate.cc"
template class ProxyBindableTemplate< EventVertexPrivate >;

PROXY_BIND_METHOD( EventVertexPrivateProxy )
//-----------------------------------------------

