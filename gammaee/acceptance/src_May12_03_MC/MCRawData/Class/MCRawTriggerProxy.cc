// -*- C++ -*-
//
// Package:     MCRawData
// Module:      MCRawTriggerProxy
// 
// Description:
//
// Implementation:
//
// Author:      Brian K. Heltsley
// Created:     Tue Feb 23 17:35:16 EST 1999
// $Id: MCRawTriggerProxy.cc,v 1.26 2003/01/29 19:31:08 cleo3 Exp $
//
// Revision history
//
// $Log: MCRawTriggerProxy.cc,v $
// Revision 1.26  2003/01/29 19:31:08  cleo3
// changes needed to compile using g++
//
// Revision 1.25  2002/09/27 20:23:13  bkh
// ZD addition
// Cleanup of obsolete classes
//
// Revision 1.24  2002/06/13 19:53:35  bkh
// Implement use of ccmcpeeldaqmap in the calorimeter processing
// Implement parameter to turn off trigger simulation as with other detectors
//
// Revision 1.23  2002/02/11 22:25:33  bkh
// Go back once again to using merged calibrated DR hits for trigger
//
// Revision 1.22  2002/02/06 23:12:49  bkh
// Go back to raw dr hits for trigger
//
// Revision 1.21  2002/01/09 21:45:12  kamal
// add ultra low showers algorithm
//
// Revision 1.20  2001/12/19 22:26:10  bkh
// Correct exception type from item to table
//
// Revision 1.19  2001/12/19 19:08:46  kamal
//  add overloping showers algorithm for showers with E greater than 150 MeV
//
// Revision 1.18  2001/12/18 22:33:10  bkh
// Institute CC "fake merge" flag like other detectors
// Force trigger to get CalibratedDRHits not raw data
//
// Revision 1.17  2001/09/25 17:42:05  nlowrey
// bux fix
//
// Revision 1.16  2001/09/24 20:45:45  nlowrey
// no longer catching exceptions when extracting CC-info
//
// Revision 1.15  2001/09/18 16:11:59  kamal
// fixed bug in filing information
//
// Revision 1.14  2001/09/17 18:46:58  kamal
// add cc trigger and L1D simulations
//
// Revision 1.13  2001/07/06 15:06:09  cplager
//  got rid of couts
//
// Revision 1.12  2001/07/02 18:20:20  cplager
// working copy of tracking trigger info
//
// Revision 1.11  2001/01/26 15:53:35  rhans
// Removed unnecessary header files
//
// Revision 1.10  2001/01/25 13:45:16  rhans
// Forgot to remove code for testing...done now
//
// Revision 1.9  2001/01/24 15:39:54  rhans
// Data inversion (from TriggerData to MCRawTrigger) is now complete 
// and correct.
//
// Revision 1.8  2000/11/14 16:08:26  rhans
// Fixed bug: not FAItem<TriggerData>, just TriggerData
//
// Revision 1.7  2000/11/13 14:17:03  rhans
// Remove extract TriggerData call
//
// Revision 1.6  2000/11/10 22:01:19  rhans
// Reinstated sections removed by jjo and added some comments
//
// Revision 1.5  2000/03/30 00:28:08  jjo
// Add empty trigger info that was in previous c3tag'd version
// to prevent Suez exception for no trigger info.
//
// Revision 1.4  2000/03/27 19:50:45  jjo
// Comment out faultHandler to avoid missing
// symbols - TrigCBArray & FAItem<TriggerData>
//
// Revision 1.3  2000/03/15 18:07:31  rhans
// First version
//
// Revision 1.2  1999/06/04 21:38:55  bkh
// CC code closer to working, structural mods to others
//
// Revision 1.1  1999/02/25 22:02:56  bkh
// fix name conflicts
//
// Revision 1.1.1.1  1999/02/25 20:29:12  bkh
// imported MCRawData sources
//
//

#include "Experiment/Experiment.h"

// system include files
#include <stdlib.h>   // for ::exit
#include <assert.h>

#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"

#include "DataHandler/Record.h"
#include "FrameAccess/extract.h"           
#include "FrameAccess/FAItem.h"
#include "FrameAccess/FATable.h"
#include "DataHandler/Frame.h"
#include "FrameAccess/FAConstants.h"
#include "FrameAccess/FANonSeqConstants.h"
#include "DAException/DANoDataException.h"
#include "DAException/DAException.h"
#include "C3cc/CcStream.h"
#include "ConstantsMapping/CC.h"
#include "DBCCElecMap.hh"
#include "DBTrigMCCCATOC.hh"

#include "MCRawData/MCRawTriggerProxy.h"
#include "MCTriggerPhase/MCTriggerPhase.h"
#include "TriggerData/TriggerData.h"  //For enum
#include "TriggerData/TrigCCTiles.h"
#include "TriggerData/TrigAxialWires.h"  
#include "TriggerData/TrigStereoBlocks.h"  
#include "TriggerData/TrigTracking.h"  
#include "TriggerData/TrigCBArray.h"
#include "TriggerData/L1TrigCBArray.h"
#include "TriggerL1Data/TriggerL1Data.h"

#include "RawData/RawDRHits.h"
#include "CalibratedData/CalibratedDRHit.h"
#include "RawData/DRDatum.h"
#include "ADRGeom/ADRSenseWireStore.h"
#include "DBTRIGDeadAxWires.hh"

#include "TrigSubs/lumiSizes.h" // for sizes in getLumiInfo
#include "C3trig/TrigStream.h"

#include "RandomModule/RandomGenerator.h"

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>

//
// constants, enums and typedefs
// next 2 used in in extern "C" block below
const int kLayers = TrigStereoBlocks::kNumStereoLayers;
// 87 = TrigStereoBlocks::kBlocksPerLayer[kLayers - 1];
const int kMaxBlocks = 87; 

static const char* const kFacilityString = "MCRawData.MCRawTriggerProxy" ;
static const char* const kIdString  = 
   "$Id: MCRawTriggerProxy.cc,v 1.26 2003/01/29 19:31:08 cleo3 Exp $";
static const char* const kTagString = "$Name: v05_02_06 $";

// external functions
extern "C" {
   void add_hit_ (const int*, const int*, int*);
   void dr3_trigger_();
   void filltrig_();
   void getStereoBlocks(UInt32 array[kLayers][kMaxBlocks]);
   void TrigSimInit();
   void TrigSimReset();
   // constants defined in "TrigSubs/lumiSizes.h"
   void getLumiInfo (int axial[kAxCellSize], int cal[kCcCellSize],
                     int *nCorHi, int *nCorLo, int *axCount,
                     int lowPos[kLowPosSize]);
   void getTrackingInfo (unsigned char axMap[kAxCellSize]);
   void getAxialTrackMap (unsigned char trackMap[kAxialKeyWires]);

   // FORTRAN subroutine used to determine the CC-digital Trigger crates
   // responce for a given set of greybits
   void ccdigtrig_ (MCRawTriggerProxy::TproInfoArray *TproArray,
                    MCRawTriggerProxy::CountsArray *counts,
                    MCRawTriggerProxy::CLEOIIbits *bits);
}

//
// static data member definitions
//

// CardDB map initialization: see MCRawTriggerProxy.h for usage
const int MCRawTriggerProxy::kCardDBMap[MCRawTriggerProxy::kNumCards+1][MCRawTriggerProxy::kCardDBMap_numOpt] =
{{  0,  0},
 {  1,  6},
 {  2,  5},
 {  3,  4},
 {  4,  3},
 {  5,  2},
 {  6,  1},
 {  7, 12},
 {  8, 11},
 {  9, 10},
 { 10,  9},
 { 11,  8},
 { 12,  7},
 { 13, 18},
 { 14, 17},
 { 15, 16},
 { 16, 15},
 { 17, 14},
 { 18, 13},
 { 19, 24},
 { 20, 23},
 { 21, 22},
 { 22, 21},
 { 23, 20},
 { 24, 19}};

// Tpro map initialization: see MCRawTriggerProxy.h for usage
const int MCRawTriggerProxy::kTproMap[MCRawTriggerProxy::kNumTpros+1][MCRawTriggerProxy::kNumProcPerTpro+1][MCRawTriggerProxy::kTproMap_numOpt] =
{{{  0, 0},   // Tpro0, proc0 (does not exist)
  {  0, 0},   // Tpro0, proc1 (does not exist)
  {  0, 0},   // Tpro0, proc2 (does not exist)
  {  0, 0},   // Tpro0, proc3 (does not exist)
  {  0, 0}},  // Tpro0, proc4 (does not exist)
 {{  0, 0},   // Tpro1, proc0 (does not exist)
  {  1, MCRawTriggerProxy::kRev   },    // Tpro1, proc1
  {  9, MCRawTriggerProxy::kNoRev },    // Tpro1, proc2
  {  2, MCRawTriggerProxy::kRev   },    // Tpro1, proc3
  { 10, MCRawTriggerProxy::kNoRev }},   // Tpro1, proc4
 {{  0, 0},   // Tpro2, proc0 (does not exist)
  {  3, MCRawTriggerProxy::kRev   },    // Tpro2, proc1
  { 11, MCRawTriggerProxy::kNoRev },    // Tpro2, proc2
  {  4, MCRawTriggerProxy::kRev   },    // Tpro2, proc3
  { 12, MCRawTriggerProxy::kNoRev }},   // Tpro2, proc4
 {{  0, 0},   // Tpro3, proc0 (does not exist)
  {  5, MCRawTriggerProxy::kRev   },    // Tpro3, proc1
  { 13, MCRawTriggerProxy::kNoRev },    // Tpro3, proc2
  {  6, MCRawTriggerProxy::kRev   },    // Tpro3, proc3
  { 14, MCRawTriggerProxy::kNoRev }},   // Tpro3, proc4
 {{  0, 0},   // Tpro4, proc0 (does not exist)
  {  7, MCRawTriggerProxy::kRev   },    // Tpro4, proc1
  { 15, MCRawTriggerProxy::kNoRev },    // Tpro4, proc2
  {  8, MCRawTriggerProxy::kRev   },    // Tpro4, proc3
  { 16, MCRawTriggerProxy::kNoRev }},   // Tpro4, proc4
 {{  0, 0},   // Tpro5, proc0 (does not exist)
  { 17, MCRawTriggerProxy::kNoRev },    // Tpro5, proc1
  { 18, MCRawTriggerProxy::kNoRev },    // Tpro5, proc2
  { 19, MCRawTriggerProxy::kNoRev },    // Tpro5, proc3
  { 20, MCRawTriggerProxy::kNoRev }},   // Tpro5, proc4
 {{  0, 0},   // Tpro6, proc0 (does not exist)
  { 21, MCRawTriggerProxy::kNoRev },    // Tpro6, proc1
  { 22, MCRawTriggerProxy::kNoRev },    // Tpro6, proc2
  { 23, MCRawTriggerProxy::kNoRev },    // Tpro6, proc3
  { 24, MCRawTriggerProxy::kNoRev }}};  // Tpro6, proc4

// LumiCountsMap initialization: see MCRawTriggerProxy.h for usage
const unsigned int MCRawTriggerProxy::kLumiCountsMap[MCRawTriggerProxy::kNumShowerTypes][MCRawTriggerProxy::kNumCCreg][MCRawTriggerProxy::kLumiMap_numOpt] =
{{{ 6, 20}, { 7,  6}},
 {{ 7,  0}, { 7,  9}},
 {{ 7,  3}, { 7, 12}}};

// LumiOldbitsMap initialization: see MCRawTriggerProxy.h for usage
const unsigned int MCRawTriggerProxy::kLumiOldbitsMap[MCRawTriggerProxy::kNumShowerTypes][MCRawTriggerProxy::kNumCCreg][MCRawTriggerProxy::kLumiMap_numOpt] =
{{{ 6,  8}, { 6, 10}},
 {{ 6, 12}, { 6, 14}},
 {{ 6, 16}, { 6, 18}}};

// MBDBMap initialization: see MCRawTriggerProxy.h for usage
const int MCRawTriggerProxy::kMBDBMap[MCRawTriggerProxy::kNumMBs+1][MCRawTriggerProxy::kMBDBMap_numOpt] =
{{  0,  0},  // There is no MB 0
 {  1, 24},  // barrel (MBs 1..16) are completely filled
 {  1, 24},
 {  1, 24},
 {  1, 24},
 {  1, 24},
 {  1, 24},
 {  1, 24},
 {  1, 24},
 {  1, 24},
 {  1, 24},
 {  1, 24},
 {  1, 24},
 {  1, 24},
 {  1, 24},
 {  1, 24},
 {  1, 24},
 {  1, 15},  // east endcap (MBs 17..20), only slots 1..15 are filled
 {  1, 15},
 {  1, 15},
 {  1, 15},
 { 10, 24},  // west endcap (MBs 21..24), only slots 10..24 are filled
 { 10, 24},
 { 10, 24},
 { 10, 24}};

//
// constructors and destructor
//
MCRawTriggerProxy::MCRawTriggerProxy( const Parameter<DABoolean>& aParm ) :
   m_RawTrigger( 0 ) ,
   m_words    ( ),
   m_getRawTrigger ( aParm )
{
   // allocate reasonable length just once!

   //Calculation is (buckets * words/bucket + header/footer words) *
   //(boards listed + axpr) + (buckets *words/bucket + header/footer words) * 
   //(lumi + listed boards) + (buckets + header/footer words) * L1trigs + padding

   //This calculation is no longer exact.  With sparsification, we no longer
   //know how many words there will be.  The amount reserved below should be
   //large enough to cover almost every event, but a little too big on average.
   m_words.reserve( ((1 * 6) + 4) *
                    (TriggerData::kNumberOfAxtrs + 
                     TriggerData::kNumberOfSttrs
		     + TriggerData::kNumberOfTrcrs + 1)
                    + (((kNumBuckets * 6) + 4) *
		    (1 + TriggerData::kNumberOfTpros + 
                     TriggerData::kNumberOfSurfs))
                    + ((kNumBuckets + 4) * 
                       TriggerData::kNumberOfL1Trigs) + 10 ) ; 
}

MCRawTriggerProxy::~MCRawTriggerProxy()
{
   delete m_RawTrigger ;
}

//
// member functions
//

void
MCRawTriggerProxy::invalidateCache()
{
   delete m_RawTrigger ;
   m_RawTrigger = 0 ;
   m_words.clear();
}

const MCRawTriggerProxy::value_type*
MCRawTriggerProxy::faultHandler( const Record& iRecord,
				 const DataKey& iKey )
{
   assert( 0 == m_RawTrigger ) ;
   assert( m_words.empty()  ) ; // always start out empty

   if( m_getRawTrigger.value() )
   {
      //Must produce TriggerData from DR and CC raw information
      TriggerData my_TriggerData;
      int status = makeTriggerData(iRecord,my_TriggerData);
      if(status != 0)
      {
	 report( EMERGENCY, kFacilityString)
	    << "Cannot create TriggerData from DR/CC information!  Abort."
	    << endl;
	 return 0;  //Throw exception
      }
   
      //Fill m_words with RawTrigger from TriggerData
      status = fillRawTrigger(my_TriggerData);
      if(status != 0)
      {
	 report( EMERGENCY, kFacilityString)
	    << "Cannot create RawTrigger from TriggerData!  Abort."
	    << endl;
	 return 0;  //Throw exception
      }
   }
   //Create (and fill) the RawTrigger object from m_words
   //----------------------------------------------------------------
   m_RawTrigger = new RawTrigger( &(*(m_words.begin())), m_words.size() );

   return m_RawTrigger ;
}

//Function to create RawTrigger from TriggerData
int 
MCRawTriggerProxy::fillRawTrigger(const TriggerData& trigDat)
{
   //This routine creates the structure of the trigger data subunits just like
   //the TrigSparse routine.  It is as follows (once for each board in the readout):
   //Length of block (in words) (data + 4)
   //ASCII board name
   //slot
   //data word 0
   //data word 1
   //...
   //Length

   //This goes in m_words

   //The sparsified boards, AXTR, STTR, TPRO, have  different data subunits
   //as created by the AxtrSparse, SttrSparse and CCDSparse, shown below:

   //AXTR
   //Length of block (words)
   //0x41585452 = 'AXTR' (ASCII board name)
   //size2/size1 (words)
   //size4/size3 
   //size6/size5
   //...
   //size16/size15
   //data
   //...
   //Length (repeat of first length)
   //
   //where, sizeX+1/sizeX means that each 1/2-word contains the
   //length (in words) of the data from the given board, and
   //the data words are described below.
   //Each 1/2-word from the boards is examined.  Any non-zero
   //half words are retained and copied into the lower half of
   //one of the data words listed above.  The upper half of this
   //data word is the tag, telling what 1/2-word this is.  The
   //tag is as follows: bits 31-28 = board (0 - 15), bits 27-16
   //which 1/2-word on this board.
   //In general, no more than 64 time buckets should be read
   //out, so there are 64(times)x3(ports)x2(words)x2(1/2-words) =
   //768 1/2-words, at most.  This is 9-bits.  (Note that reading
   //out all 512 buckets will use 12 bits, which still fits.)
   //Note, the lower half of each non-zero data word is counted
   //first, and the first half word is number 0.

   //STTR
   //Length of block (words)
   //0x53545452 = 'STTR' (ASCII board name)
   //size2/size1 (words)
   //size4/size3 
   //size6/size5
   //...
   //size12/size11
   //data
   //...
   //Length (repeat of first length)
   //
   //where, sizeX+1/sizeX means that each 1/2-word contains the
   //length (in words) of the data from the given board, and
   //the data words are described below.
   //Each 1/2-word from the boards is examined.  Any non-zero
   //half words are retained and copied into the lower half of
   //one of the data words listed above.  The upper half of this
   //data word is the tag, telling what 1/2-word this is.  The
   //tag is as follows: bits 31-28 = board (0 - 12), bits 27-16
   //which 1/2-word on this board.
   
   //TPRO
   //length of block (words)
   //0x5450524f = 'TPRO' (ascii name)
   //size2/size1 (words)
   //size4/size3 
   //size6/size5
   //data
   //...
   //length (repeat of first length)
   //
   //where, sizeX+1/sizeX means that each 1/2 word contains the
   //length (in words) of the data from the given board, and
   //the data words are described below.
   //Each 1/2-word from the boards is examined.  Any non-zero
   //half words are retained and copied into the lower half of
   //one of the data words listed above.  The upper half of this
   //data word is the tag, telling what 1/2-word this is.  The
   //tag is as follows: bits 31-28 = board (0 - 15), bits 27-16
   //which 1/2-word on this board.
   
   //These also go in m_words

   //-----------------------------------------------------
   //Get to work filling the words from the boards in TriggerData

   //Do AXTR
   int status = fillSparsifiedBoard(TriggerData::kNumberOfAxtrs,
                                    TriggerData::TB_AXTR,trigDat);
   //Do STTR
   status = fillSparsifiedBoard(TriggerData::kNumberOfSttrs,
                                TriggerData::TB_STTR,trigDat);
   //Do TPRO
   status = fillSparsifiedBoard(TriggerData::kNumberOfTpros,
                                TriggerData::TB_TPRO,trigDat);
   
   //Do SURF
   status = fillNormalBoard(TriggerData::kNumberOfSurfs,
                            TriggerData::TB_SURF,trigDat);
   
   //Do AXPR
   status = fillNormalBoard(1,TriggerData::TB_AXPR,trigDat);

   //Do TRCR
   status = fillNormalBoard(TriggerData::kNumberOfTrcrs,
                            TriggerData::TB_TRCR,trigDat);

   //Do LUMI
   status = fillNormalBoard(1,TriggerData::TB_LUMI,trigDat);
   
   
   int board;
/*
   const TrigCBArray* my_Array;
   
   //\************AXTR*********************
   //This board is sparsified, so will have to collect information
   //from all of the boards before writing anything.
   
   //Initialize some variables
   int num_data = 0;
   int dual_size_word[8] = {0,0,0,0,0,0,0,0};

   //Max data is 64 buckets x 6 words/bucket x 2 half words x number of boards
   //This is more than any other board type has, so can reuse this variable
   UInt32 data[64*6*2*TriggerData::kNumberOfAxtrs];
   
   //Loop over the boards
   for(board = 0; board < TriggerData::kNumberOfAxtrs; board++)
   {
      my_Array = trigDat.getAxtrData(board);  //Get the data
      if(my_Array != 0) //Check that it exists
      {
         //Fill dual_size word for this board
         unsigned int size = my_Array->getNumberOfWords();
         dual_size_word[board/2] = size << (16*(board%2));

         //Loop over data in this board looking for non-zero words
         for(int i = 0; i < size/2; ++i)
         {
            UInt32 d32 = 0;
            //Examine Upper SRAM half words (only higher half used on AXTR)
            int status = my_Array->getRawBits(i + size/2,d32,0,32);
            if(status != 0)
            {
               report( EMERGENCY, kFacilityString)
                  << "TriggerData object corrupted! Could not read word "
                  << i + size/2 << " from AXTR board " << board << ".  Aborting"
                  << endl;
               assert( false );
               ::exit( 1 );
            }
            if((0xffff0000 & d32) != 0) //Found a non-zero 1/2 word!
            {
               //Data is board (31:28), which 1/2 word (27:16), data (15:0)
               data[num_data] = (board << 28) + ((i*4 + 1) << 16) +
                  ((0xffff0000 & d32) >> 16);
               ++num_data;
            }

            //Now examine Lower SRAM half words
            for(int half = 0; half < 2; ++half)
            {
               d32 = 0;
               status = my_Array->getRawBits(i,d32,0,32);
               if(status != 0)
               {
                  report( EMERGENCY, kFacilityString)
                     << "TriggerData object corrupted!  Could not read word "
                     << i << " from AXTR board " << board << ". Aborting"
                     << endl;
                  assert ( false );
                  ::exit( 1 );
               }
               if(((0xffff << (16*half)) & d32) != 0) //Found a non-zero 1/2 word!
               {
                  //Data is board (31:28), which 1/2 word (27:16), data (15:0)
                  data[num_data] = (board << 28) + ((i*4 + 2 + half) << 16) +
                     (((0xffff << (16*half)) & d32) >> (16*half)) ;
                  ++num_data;
               }
            }
         } //End of loop over data in a board
      } //End of check that TrigCBArray exists
   } //End of loop over boards
   
   //Now save the info we've gathered
   m_words.push_back(num_data + 11); //Length (in words)
   m_words.push_back(TriggerData::TB_AXTR); //ASCII name
   for(int axtrsby2 = 0; axtrsby2 < TriggerData::kNumberOfAxtrs/2; ++axtrsby2)
   {
      m_words.push_back(dual_size_word[axtrsby2]); //sizeN+1/sizeN
   }
   for(int axtrwords = 0; axtrwords < num_data; ++axtrwords)
   {
      m_words.push_back(data[axtrwords]); //data
   }
   m_words.push_back(num_data + 11);  //Repeated length
   
   //\************STTR*********************
   //This board is sparsified, so will have to collect information
   //from all of the boards before writing anything.
   
   //Initialize some variables
   num_data = 0;
   int dual_size_wordS[TriggerData::kNumberOfSttrs/2] = {0,0,0,0,0,0};
   
   //Loop over the boards
   for(board = 0; board < TriggerData::kNumberOfSttrs; board++)
   {
      my_Array = trigDat.getSttrData(board);  //Get the data
      if(my_Array != 0) //Check that it exists
      {
         //Fill dual_size word for this board
         unsigned int size = my_Array->getNumberOfWords();
         dual_size_wordS[board/2] = size << (16*(board%2));

         //Loop over data in this board looking for non-zero words
         for(int i = 0; i < size/2; ++i)
         {
            UInt32 d32 = 0;
            //Examine Upper SRAM half words
            int status = my_Array->getRawBits(i + size/2,d32,0,32);
            if(status != 0)
            {
               report( EMERGENCY, kFacilityString)
                  << "TriggerData object corrupted! Could not read word "
                  << i + size/2 << " from STTR board " << board << ".  Aborting"
                  << endl;
               assert( false );
               ::exit( 1 );
            }
            //Loop over the half words
            for(int half = 0; half < 2; ++half)
            {
               if(((0xffff << (16*half)) & d32) != 0) //Found a non-zero 1/2 word!
               {
                  //Data is board (31:28), which 1/2 word (27:16), data (15:0)
                  data[num_data] = (board << 28) + ((i*4 + half) << 16) +
                     (((0xffff << (16*half)) & d32) >> (16*half));
                  ++num_data;
               }
            }

            //Now examine Lower SRAM half words
            d32 = 0;
            status = my_Array->getRawBits(i,d32,0,32);
            if(status != 0)
            {
               report( EMERGENCY, kFacilityString)
                  << "TriggerData object corrupted!  Could not read word "
                  << i << " from Sttr board " << board << ". Aborting"
                  << endl;
               assert ( false );
               ::exit( 1 );
            }
            //Loop over the half words
            for(int half = 0; half < 2; ++half)
            {
               if(((0xffff << (16*half)) & d32) != 0) //Found a non-zero 1/2 word!
               {
                  //Data is board (31:28), which 1/2 word (27:16), data (15:0)
                  data[num_data] = (board << 28) + ((i*4 + 2 + half) << 16) +
                     (((0xffff << (16*half)) & d32) >> (16*half)) ;
                  ++num_data;
               }
            }
         } //End of loop over data in a board
      } //End of check that TrigCBArray exists
   } //End of loop over boards
   
   //Now save the info we've gathered
   m_words.push_back(num_data + 9); //Length (in words)
   m_words.push_back(TriggerData::TB_STTR); //ASCII name
   for(int sttrsby2 = 0; sttrsby2 < TriggerData::kNumberOfSttrs/2; ++sttrsby2)
   {
      m_words.push_back(dual_size_wordS[sttrsby2]); //sizeN+1/sizeN
   }
   for(int sttrwords = 0; sttrwords < num_data; ++sttrwords)
   {
      m_words.push_back(data[sttrwords]); //data
   }
   m_words.push_back(num_data + 9);  //Repeated length
   
   //\*************TPRO****************
   //This board is sparsified, so will have to collect information
   //from all of the boards before writing anything.
   
   //Initialize some variables
   num_data = 0;
   int dual_size_wordC[TriggerData::kNumberOfTpros/2] = {0,0,0};
   
   //Loop over the boards
   for(board = 0; board < TriggerData::kNumberOfTpros; board++)
   {
      my_Array = trigDat.getTproData(board);  //Get the data
      if(my_Array != 0) //Check that it exists
      {
         //Fill dual_size word for this board
         unsigned int size = my_Array->getNumberOfWords();
         dual_size_wordC[board/2] = size << (16*(board%2));

         //Loop over data in this board looking for non-zero words
         for(int i = 0; i < size/2; ++i)
         {
            UInt32 d32 = 0;
            //Examine Upper SRAM half words
            int status = my_Array->getRawBits(i + size/2,d32,0,32);
            if(status != 0)
            {
               report( EMERGENCY, kFacilityString)
                  << "TriggerData object corrupted! Could not read word "
                  << i + size/2 << " from TPRO board " << board << ".  Aborting"
                  << endl;
               assert( false );
               ::exit( 1 );
            }
            //Loop over the half words
            for(int half = 0; half < 2; ++half)
            {
               if(((0xffff << (16*half)) & d32) != 0) //Found a non-zero 1/2 word!
               {
                  //Data is board (31:28), which 1/2 word (27:16), data (15:0)
                  data[num_data] = (board << 28) + ((i*4 + half) << 16) +
                     (((0xffff << (16*half)) & d32) >> (16*half));
                  ++num_data;
               }
            }

            //Now examine Lower SRAM half words
            d32 = 0;
            status = my_Array->getRawBits(i,d32,0,32);
            if(status != 0)
            {
               report( EMERGENCY, kFacilityString)
                  << "TriggerData object corrupted!  Could not read word "
                  << i << " from TPRO board " << board << ". Aborting"
                  << endl;
               assert ( false );
               ::exit( 1 );
            }
            //Loop over the half words
            for(int half = 0; half < 2; ++half)
            {
               if(((0xffff << (16*half)) & d32) != 0) //Found a non-zero 1/2 word!
               {
                  //Data is board (31:28), which 1/2 word (27:16), data (15:0)
                  data[num_data] = (board << 28) + ((i*4 + 2 + half) << 16) +
                     (((0xffff << (16*half)) & d32) >> (16*half)) ;
                  ++num_data;
               }
            }
         } //End of loop over data in a board
      } //End of check that TrigCBArray exists
   } //End of loop over boards
   
   //Now save the info we've gathered
   m_words.push_back(num_data + 6); //Length (in words)
   m_words.push_back(TriggerData::TB_TPRO); //ASCII name
   for(int tprosby2 = 0; tprosby2 < TriggerData::kNumberOfTpros/2; ++tprosby2)
   {
      m_words.push_back(dual_size_wordC[tprosby2]); //sizeN+1/sizeN
   }
   for(int tprowords = 0; tprowords < num_data; ++tprowords)
   {
      m_words.push_back(data[tprowords]); //data
   }
   m_words.push_back(num_data + 6);  //Repeated length

   //\*************SURF****************
   //Loop over the boards
   for(board = 0; board < TriggerData::kNumberOfSurfs; board++)
   {
      my_Array = trigDat.getSurfData(board);  //Get the data
      if(my_Array != 0) //Check that it exists
      {
         unsigned int size = my_Array->getNumberOfWords();
         m_words.push_back(size + 4);  //Length (in words)
         m_words.push_back(TriggerData::TB_SURF);  //ASCII name
         switch (board)
         {
            case 0:
               m_words.push_back(TriggerData::TB_SURF_SLOT0);  //Slot
               break;
            case 1:
               m_words.push_back(TriggerData::TB_SURF_SLOT1);  //Slot
               break;
            default:
               report( EMERGENCY, kFacilityString)
                  << "Exceeded number of SURF boards, something corrupted!  Aborting."
                  << endl;
               assert(false);
               ::exit(1);
         }  //End of switch (board)

         //Put in the data words
         for(int word = 0; word < size/2; word++)
         {
            UInt32 d32 = 0;
            //Get upper-half word
            if(0 != my_Array->getRawBits(word + (size/2),d32))
            {
               report( EMERGENCY, kFacilityString )
                  << "TriggerData object corrupted!  Aborting." << endl;
               assert( false );
               ::exit( 1 );
            }
            m_words.push_back(d32);
            //Get lower-half word
            if(0 != my_Array->getRawBits(word,d32))
            {
               report( EMERGENCY, kFacilityString )
                  << "TriggerData object corrupted!  Aborting." << endl;
               assert( false );
               ::exit( 1 );
            }
            m_words.push_back(d32);
         }
         m_words.push_back(size + 4);  //Repeated length
      }
   }  //End of SURF loop

   //\*************TRCR****************
   //Loop over the boards
   for(board = 0; board < TriggerData::kNumberOfTrcrs; board++)
   {
      my_Array = trigDat.getTrcrData(board);  //Get the data
      if(my_Array != 0) //Check that it exists
      {
         unsigned int size = my_Array->getNumberOfWords();
         m_words.push_back(size + 4);  //Length (in words)
         m_words.push_back(TriggerData::TB_TRCR);  //ASCII name
         m_words.push_back(TriggerData::TB_TRCR_OFFSET + board ); //Slot
         //Put in the data words
         for(int word = 0; word < size/2; word++)
         {
            UInt32 d32 = 0;
            //Get upper-half word
            if(0 != my_Array->getRawBits(word + (size/2),d32))
            {
               report( EMERGENCY, kFacilityString )
                  << "TriggerData object corrupted!  Aborting." << endl;
               assert( false );
               ::exit( 1 );
            }
            m_words.push_back(d32);
            //Get lower-half word
            if(0 != my_Array->getRawBits(word,d32))
            {
               report( EMERGENCY, kFacilityString )
                  << "TriggerData object corrupted!  Aborting." << endl;
               assert( false );
               ::exit( 1 );
            }
            m_words.push_back(d32);
         }
         m_words.push_back(size + 4);  //Repeated length
      }
   }  //End of TRCR loop

   //\***********AXPR**************
   my_Array = trigDat.getAxprData();  //Get the data
   if(my_Array != 0) //Check that it exists
   {
      unsigned int size = my_Array->getNumberOfWords();
      m_words.push_back(size + 4);  //Length (in words)
      m_words.push_back(TriggerData::TB_AXPR);  //ASCII name
      m_words.push_back(TriggerData::TB_AXPR_SLOT ); //Slot
      //Put in the data words
      for(int word = 0; word < size/2; word++)
      {
         UInt32 d32 = 0;
         //Get upper-half word
         if(0 != my_Array->getRawBits(word + (size/2),d32))
         {
            report( EMERGENCY, kFacilityString )
               << "TriggerData object corrupted!  Aborting." << endl;
            assert( false );
            ::exit( 1 );
         }
         m_words.push_back(d32);
         //Get lower-half word
         if(0 != my_Array->getRawBits(word,d32))
         {
            report( EMERGENCY, kFacilityString )
               << "TriggerData object corrupted!  Aborting." << endl;
            assert( false );
            ::exit( 1 );
         }
         m_words.push_back(d32);
      }
      m_words.push_back(size + 4);  //Repeated length
   }

   //\***********LUMI**************
   my_Array = trigDat.getLumiData();  //Get the data
   if(my_Array != 0) //Check that it exists
   {
      unsigned int size = my_Array->getNumberOfWords();
      m_words.push_back(size + 4);  //Length (in words)
      m_words.push_back(TriggerData::TB_LUMI);  //ASCII name
      m_words.push_back(TriggerData::TB_LUMI_SLOT ); //Slot
      //Put in the data words
      for(int word = 0; word < size/2; word++)
      {
         UInt32 d32 = 0;
         //Get upper-half word
         if(0 != my_Array->getRawBits(word + (size/2),d32))
         {
            report( EMERGENCY, kFacilityString )
               << "TriggerData object corrupted!  Aborting." << endl;
            assert( false );
            ::exit( 1 );
         }
         m_words.push_back(d32);
         //Get lower-half word
         if(0 != my_Array->getRawBits(word,d32))
         {
            report( EMERGENCY, kFacilityString )
               << "TriggerData object corrupted!  Aborting." << endl;
            assert( false );
            ::exit( 1 );
         }
         m_words.push_back(d32);
      }
      m_words.push_back(size + 4);  //Repeated length
   }
*/
   //***********L1TR**************//
   const L1TrigCBArray* my_L1Array;
   //Loop over the boards
   for(board = 0; board < TriggerData::kNumberOfL1Trigs; board++)
   {
      my_L1Array = trigDat.getL1TrigData(board);  //Get the data
      if(my_L1Array != 0) //Check that it exists
      {
         unsigned int size = my_L1Array->getNumberOfWords();
         m_words.push_back(size + 4);  //Length (in words)
         m_words.push_back(TriggerData::TB_L1TR);  //ASCII name
         m_words.push_back(TriggerData::TB_L1TR_OFFSET + board ); //Slot
         //Put in the data words (recall that L1TR only uses lower-half words)
         for(int word = 0; word < size; word++)
         {
            UInt32 d32 = 0;
            if(0 != my_L1Array->getRawBits(word,d32))
            {
               report( EMERGENCY, kFacilityString )
                  << "TriggerData object corrupted!  Aborting." << endl;
               assert( false );
               ::exit( 1 );
            }
            m_words.push_back(d32);
         }
         m_words.push_back(size + 4);  //Repeated length
      }
   }  //End of L1TR loop

   //All done!
   return 0;
}

//************************************************************
//Function for put data into sparsified board format
int
MCRawTriggerProxy::fillSparsifiedBoard(
   int num_boards,UInt32 which_board,const TriggerData& trigDat)
{
   //This board is sparsified, so will have to collect information
   //from all of the boards before writing anything.
   
   int board;
   const TrigCBArray* my_Array;
   //Initialize some variables
   int num_data = 0;
   int dual_size_word[8] = {0};  //8 is the most we need, so use that (NumAXTR/2)

   //Max data is 64 buckets x 6 words/bucket x 2 half words x number of boards
   //This is more than any other board type has, so can reuse this variable
   UInt32 data[64*6*2*TriggerData::kNumberOfAxtrs];
   
   //Loop over the boards
   for(board = 0; board < num_boards; board++)
   {
      //Get the data
      switch (which_board)
      {
         case TriggerData::TB_AXTR:
            my_Array = trigDat.getAxtrData(board);
            break;
         case TriggerData::TB_STTR:
            my_Array = trigDat.getSttrData(board);
            break;
         case TriggerData::TB_TPRO:
            my_Array = trigDat.getTproData(board);
            break;
         default:
            assert(false);
            ::exit( 1 );
      }

      if(my_Array != 0) //Check that it exists
      {
         //Fill dual_size word for this board
         unsigned int size = my_Array->getNumberOfWords();
         dual_size_word[board/2] |= size << (16*(board%2));

         //Loop over data in this board looking for non-zero words
         for(int i = 0; i < size/2; ++i)
         {
            UInt32 d32 = 0;

            //Examine Upper SRAM half words
            int status = my_Array->getRawBits(i + size/2,d32,0,32);
            if(status != 0)
            {
               report( EMERGENCY, kFacilityString)
                  << "TriggerData object corrupted! Could not read word "
                  << i + size/2 << " from board type 0x" << hex << which_board
                  << dec << ", board " << board << ".  Aborting" << endl;
               assert( false );
               ::exit( 1 );
            }
            
            //Loop over the half words
            for(int half = 0; half < 2; ++half)
            {
               if(((0xffff << (16*half)) & d32) != 0) //Found a non-zero 1/2 word!
               {
                  //Data is board (31:28), which 1/2 word (27:16), data (15:0)
                  data[num_data] = (board << 28) + ((i*4 + half) << 16) +
                     (((0xffff << (16*half)) & d32) >> (16*half));
                  ++num_data;
               }
            }

            //Now examine Lower SRAM half words
            d32 = 0;
            status = my_Array->getRawBits(i,d32,0,32);
            if(status != 0)
            {
               report( EMERGENCY, kFacilityString)
                  << "TriggerData object corrupted!  Could not read word "
                  << i << " from board type 0x" << hex << which_board
                  << dec << ", board " << board << ".  Aborting" << endl;
               assert ( false );
               ::exit( 1 );
            }

            //Loop over half words
            for(int haff = 0; haff < 2; ++haff)
            {
               if(((0xffff << (16*haff)) & d32) != 0) //Found a non-zero 1/2 word!
               {
                  //Data is board (31:28), which 1/2 word (27:16), data (15:0)
                  data[num_data] = (board << 28) + ((i*4 + 2 + haff) << 16) +
                     (((0xffff << (16*haff)) & d32) >> (16*haff)) ;
                  ++num_data;
               }
            }
         } //End of loop over data in a board
      } //End of check that TrigCBArray exists
   } //End of loop over boards
   
   //Now save the info we've gathered
   m_words.push_back(num_data + 3 + num_boards/2); //Length (in words)
   m_words.push_back(which_board);    //ASCII name
   
   for(int by2 = 0; by2 < num_boards/2; ++by2)
   {
      m_words.push_back(dual_size_word[by2]); //sizeN+1/sizeN
   }
   for(int thewords = 0; thewords < num_data; ++thewords)
   {
      m_words.push_back(data[thewords]); //data
   }
   m_words.push_back(num_data + 3 + num_boards/2);  //Repeated length
   
   return 0;
}

//************************************************************
//Function to put data into normal (unsparsified) board format
int
MCRawTriggerProxy::fillNormalBoard(
   int num_boards,UInt32 which_board,const TriggerData& trigDat)
{
   //Setup variables we need
   const TrigCBArray* my_Array;

   //Loop over the boards
   for(int board = 0; board < num_boards; board++)
   {
      //Get the data
      switch (which_board)
      {
         case TriggerData::TB_SURF:
            my_Array = trigDat.getSurfData(board);
            break;
         case TriggerData::TB_TRCR:
            my_Array = trigDat.getTrcrData(board);
            break;
         case TriggerData::TB_AXPR:
            my_Array = trigDat.getAxprData();
            break;
         case TriggerData::TB_LUMI:
            my_Array = trigDat.getLumiData();
            break;
         default:
            assert( false );
            ::exit( 1 );
      }
      
      if(my_Array != 0) //Check that it exists
      {
         unsigned int size = my_Array->getNumberOfWords();
         m_words.push_back(size + 4);  //Length (in words)
         m_words.push_back(which_board);  //ASCII name

         //Fill the slot number
         switch (which_board)
         {
            case TriggerData::TB_SURF:
               switch (board)
               {
                  case 0:
                     m_words.push_back(TriggerData::TB_SURF_SLOT0);  //Slot
                     break;
                  case 1:
                     m_words.push_back(TriggerData::TB_SURF_SLOT1);  //Slot
                     break;
                  default:
                     report( EMERGENCY, kFacilityString)
                        << "Exceeded number of SURF boards, something corrupted!  Aborting."
                        << endl;
                     assert(false);
                     ::exit(1);
               }  //End of switch (board) for SURF
               break;
            case TriggerData::TB_AXPR:
               m_words.push_back(TriggerData::TB_AXPR_SLOT ); //Slot
               break;
            case TriggerData::TB_TRCR:
               m_words.push_back(TriggerData::TB_TRCR_OFFSET + board ); //Slot
               break;
            case TriggerData::TB_LUMI:
               m_words.push_back(TriggerData::TB_LUMI_SLOT ); //Slot
               break;
            default:
               assert( false );
               ::exit( 1 );
         } //End of switch (which_board) for slot number

         //Put in the data words
         for(int word = 0; word < size/2; word++)
         {
            UInt32 d32 = 0;
            //Get upper SRAM word
            if(0 != my_Array->getRawBits(word + (size/2),d32))
            {
               report( EMERGENCY, kFacilityString )
                  << "TriggerData object corrupted!  Aborting." << endl;
               assert( false );
               ::exit( 1 );
            }
            m_words.push_back(d32);
            //Get lower SRAM word
            if(0 != my_Array->getRawBits(word,d32))
            {
               report( EMERGENCY, kFacilityString )
                  << "TriggerData object corrupted!  Aborting." << endl;
               assert( false );
               ::exit( 1 );
            }
            m_words.push_back(d32);
         }
         m_words.push_back(size + 4);  //Repeated length
      }
   }  //End of loop over boards

   return 0;
}

//************************************************************
//Function to create TriggerData from DR and CC information
int
MCRawTriggerProxy::makeTriggerData(const Record& iRecord, 
                                   TriggerData& trigDat)
{
   // Get a reference to the frame
   Frame& iFrame = iRecord.frame();
   int buckets = kNumBuckets;
   TrigCBArray *lumiPtr = new TrigCBArray (TriggerData::TB_LUMI_BOARDMASK,
                                           buckets);
   // Make tracking part
   int trstatus = makeTrackingTriggerData(iRecord, trigDat, lumiPtr);
      
   // Make calorimeter part
   int ccstatus = makeCCTriggerData(iFrame, trigDat, lumiPtr);

   // put lumi information into trigger data
   trigDat.addLumi(lumiPtr);

   // Make final decision part
   int l1status = makeL1TriggerData(iRecord, trigDat);

   // I don't know if this is reasonable, but it seems better than
   // returning 0 (Chas)
   return trstatus | ccstatus | l1status;
   //return 0;
 }
 
//************************************************************
//Function to create the L1D trigger information 
int
MCRawTriggerProxy::makeL1TriggerData(const Record& iRecord,
                                     TriggerData& trigDat)
{
   Frame& iFrame = iRecord.frame();
   // prescale counters
   static int numECbhabhas = 0;
   static int num2tracks = 0;
   // get what CESR phase should be from Lawrence
   FAItem< MCTriggerPhase> MCPhase;
   // try
   extract (iFrame.record(Stream::kEvent), MCPhase);
   // catch (maybe later)
   UInt32 phase = MCPhase->triggerPhase();

   // create L1D boards
   int buckets = kNumBuckets; // each L1d has this many buckets
   int L1Darray[] = {TriggerL1Data::kBoard1Number, 
                     TriggerL1Data::kBoard2Number};
   //something
   int numL1Ds = 2; // there are 2 L1D boards
   trigDat.createL1Ds (buckets, L1Darray, numL1Ds);

   // put in cesr phase
   trigDat.putCesrPhase(phase);

   //*******************************************//
   //Simulate the L1TR functionality

   //start of Kamal's code
   //Loop over buckets.  Buckets are defined as:
   //0 = early
   //1 = in-time
   //2 = late
   //3 = problem
   //Tracking information is valid for 0-2, but not for 3
   //Early, in-time and late are for within the CC.
   for(int bucket = 0; bucket < 4; bucket++)
   {
      //Simulate the L1TR trigger hardware

      //What do we want to do about timing bits???      
      //      int TimeCB = myTrigDat->getCBTimeBits(bucket);
      //      int TimeTR = myTrigDat->getTrackingTimeBits(bucket);
      //      int TimeCE = myTrigDat->getCETimeBits(bucket);

      //Fill these words with the bits from the trigger lines
      UInt32 word1;  //Board 1
      UInt32 word2;  //Board 2
      word1 = 0;
      word2 = 0;
      
      //      DABoolean mupair       = false;
      //      DABoolean hadron       = false;
      //      DABoolean Barrelbhabha = false;
      //      DABoolean Endbhabha    = false;
      //      DABoolean Eltrack      = false;
      //      DABoolean RadTau       = false;
      //      DABoolean twoTracks     = false;
       
      //      if (TimeCB==1||TimeTR==2)
      //      {
	 
      ///RadTau
      if((( trigDat.getHiTrackCount(bucket)+
            trigDat.getLoTrackCount(bucket)) >1)&&
         ((trigDat.getCBMdCount(bucket) >0)||
          ( trigDat.getCBLoCount(bucket)>1)))
      {
         //	 RadTau = true;
         word2 |= TriggerL1Data::kRadTau;
      }

      //ElTrack
      if((trigDat.getAxTrackCount(bucket)>0)&&(
         trigDat.getCBMdCount(bucket)>0))	 
      {
         //	 Eltrack = true;
         word2 |= TriggerL1Data::kElTrack;
      }
      
      //TwoTrack
      if (trigDat.getAxTrackCount(bucket)>1)
      {
         //	 twoTracks = true;
         //Do the prescale!!!
         ++num2tracks; // increment the prescale counter
         if (
            // after run 120852, we precale by 20
            ((iRecord.syncValue().runNumber() >= 120852) &&
            (0 == num2tracks % 20)) || 
            // after run 108986, we prescale by 10
            ((iRecord.syncValue().runNumber() >= 108986) &&
             (0 == num2tracks % 10)) ||
            // before run 108986, we prescale by 6
            ((iRecord.syncValue().runNumber() < 108986) &&
             (0 == num2tracks % 6)))
         {
            word1 |= TriggerL1Data::kTwoTrack;
         }
      }

      //Hadron
      if((trigDat.getAxTrackCount(bucket)>2)&&(trigDat.
                                               getCBLoCount(bucket)>0))
      {
         //	 hadron = true;
         word2 |= TriggerL1Data::kHadron;
      }
      
      //BarrelBhabha
      if(trigDat.getCBHiOld(bucket)==3)
      {
         //	 Barrelbhabha = true;
         word2 |= TriggerL1Data::kBarrelBhabha;
      }
      
      //MuPair
      if(trigDat.getHiTrackCount(bucket)>1)
      {
         UInt32 phi = trigDat.getTrAxProjection(bucket);
         for (int i=0; i<13; i++)
         {
            if (((phi&(1<<i))!=0)& ((phi&(1<<((i+11)%24)))||
                                    (phi&(1<<((i+12)%24)))||
                                    (phi&(1<<((i+13)%24)))))
            {
//	       mupair = true;
               word2 |= TriggerL1Data::kMuPair;
               i=13;
            }
	    
         }
      }
      
      //	 if (TimeCE==1||TimeTR==2)
      //	 {
      //EndcapBhabha
      if(trigDat.getCEHiOld(bucket)>1)
      {
         //	 Endbhabha = true;
         //Do the prescale!!!
         // if we are less than the magic run number, set the bit
         // if we are greater than the magic run number AND the event
         // number is divisible by 4, set the bit
         ++numECbhabhas; // increment the prescale counter
         if (
            // before run 108986 there is no prescale
            (iRecord.syncValue().runNumber() < 108986) ||
            // between runs 108986 and 112998, we prescaled by 4
            ( (iRecord.syncValue().runNumber() < 112998) &&
              (0 == numECbhabhas % 4)) ||
            // after run 112998, we prescaled by 8
            ( (iRecord.syncValue().runNumber() >= 112998) &&
              (0 == numECbhabhas % 8) ) 
            )
         {
            word2 |= TriggerL1Data::kEndcapBhabha;
         }
      } // if getCEHiOld(bucket) > 1

      //Fill L1TR boards with any asserted trigger lines
      int stat = trigDat.putTriggerLines(TriggerL1Data::kBoard1Number,
					 bucket,word1);
      if(stat != 0)
      {
	 return stat;
      }
      
      stat = trigDat.putTriggerLines(TriggerL1Data::kBoard2Number,
				     bucket,word2);
      if(stat != 0)
      {
	 return stat;      
      }
      
   } // for bucket
   //end of Kamal's code   
   
   
   return 0;
}
   

//************************************************************
//Function to create the tracking trigger information from the DR information
int
MCRawTriggerProxy::makeTrackingTriggerData(const Record& iRecord, 
                                           TriggerData& trigDat,
                                           TrigCBArray *lumiPtr)
{
   Frame& iFrame = iRecord.frame();
   // constants
   const UInt32 kAll = ~UInt32(0);
   // variable definitions
   TrigAxialWires axialWires;
   TrigStereoBlocks stereoBlocks;
   TrigTracking tracking;
   UInt32 trackMap32[TriggerData::kNumberOfAxialKeyWires];
   static FANonSeqConstants< DBTRIGDeadAxWires > deadWireConst;
   static FAItem< ADRSenseWireStore > iADRSenseWireStore ;
   static char firstTime = 1;
   static bool useDeadWires = false;
   if (firstTime)
   {
      firstTime = 0;
      //////////////////////////////////////////
      // Extract geometry info from the frame //
      //////////////////////////////////////////
      extract( iFrame.record( Stream::kDRAlignment ), iADRSenseWireStore );
      if(! iADRSenseWireStore.valid()  )
      { 
         // couldn't get geometry
         report (ERROR, kFacilityString ) 
            << "Couldn't get geometry information for wires" << endl;
         return 1;
         
      }  
      TrigSimInit();
      if (iRecord.syncValue().runNumber() >= 110775)
      {
         /////////////////////////////////
         // Extract Dead Wire constants //
         /////////////////////////////////
         const Record& theCurrentRecord =
            iRecord.frame().record(TrigStream::kTrigDeadAxWires);
         extract( theCurrentRecord, deadWireConst); //If it fails, let it!
         useDeadWires = true;
      }
   }
   // reset trigger simulation
   TrigSimReset();


   ////////////////////////////////////
   // Extract DR hits from the frame //
   ////////////////////////////////////
//   FAItem<RawDRHits> rawDR;

   FATable< CalibratedDRHit > calDR ;
   try
   {
      extract (iFrame.record(Stream::kEvent), calDR ) ; //rawDR);
   }
   catch ( NO_TABLE_EXCEPTION( CalibratedDRHit ) & iException)
//   catch ( NO_ITEM_EXCEPTION( RawDRHits ) & iException)
   {
      report (WARNING, kFacilityString ) << iException.what() << endl
                                         << "No Dr Hits.  Aborting" 
                                         << endl;
      return 1; // return code?
   }
   //////////////////////////////////////////////
   // Load DR hits into trigger representation //
   //////////////////////////////////////////////
   int numAxial = 0, numStereo = 0;
//   RawDRHits::const_iterator rawDRend( rawDR->end() );
//   for (RawDRHits::const_iterator drIter( rawDR->begin() );
//        drIter != rawDRend;
//        ++drIter)
//   {
      // dereference pointer to get at the value
//      const UInt32 word (*drIter);
   FATable< CalibratedDRHit >::const_iterator calDRend( calDR.end() );
   for ( FATable< CalibratedDRHit >::const_iterator drIter( calDR.begin() );
        drIter != calDRend; ++drIter)
   {
      const CalibratedDRHit& hit (*drIter);

      if( hit.charge() <= 0 ) // do not keep if no positive charge
      {
         continue;
      }
      // Is the hit within the time window?
      // ??????????????????????????????????
      const UInt32 cellID ( hit.wire() );
      // make sure it's not garbage
//      if (rawDR->rawNeglectHit(word))
//      {
         // this isn't good
//         continue;
//      }
//      const DRDatum::IsTimeType isTime( rawDR->rawIsTime(word) );
//      if (! isTime)
//      {
         // T isn't a time hit.  Don't bother
//         continue;
//      }
      // Is the hit within the time window?
      // ??????????????????????????????????
//      UInt32 cellID ( rawDR->rawDaqId(word) );

      const ADRSenseWireStore::LayerWire 
         lw (iADRSenseWireStore->layerWire(cellID));
      const int layer = lw.first;
      const int wire =  lw.second + 1; // we want 1.., they give us 0..
      int time = 0;
      add_hit_ (&layer, &wire, &time);
      // is this an axial layer
      if (layer <= 16)
      {
         // It is.  Let's fill TrigAxialWire
         axialWires.setWire (layer, wire, kAll);
         ++numAxial;
      } else { // axial wire
         ++numStereo;
      }
   } // for drIter

   /////////////////////////////////////////////
   // Load dead wires into trigger simulation //
   /////////////////////////////////////////////
   if (useDeadWires)
   {
      FANonSeqConstants< DBTRIGDeadAxWires >::const_iterator
         itrEnd = deadWireConst.end();
      for(FANonSeqConstants< DBTRIGDeadAxWires >::const_iterator itr =
             deadWireConst.begin(); itr != itrEnd; ++itr)
      {
         int layer = (*itr).get_Layer();
         int wire = (*itr).get_WireInLayer() + 1;
         int time = 0;
         add_hit_(&layer, &wire, &time );
      }
   }

   /////////////////////////////
   // Call trigger simulation //
   /////////////////////////////
   dr3_trigger_();
   filltrig_();

   ////////////////////////
   // Fill stereo blocks //
   ////////////////////////
   //UInt32 stereoBlockArray[kLayers][kMaxBlocks] = {{}};
   // sun sucks
   UInt32 stereoBlockArray[kLayers][kMaxBlocks];
   for (int index1 = 0; index1 < kLayers; ++index1)
   {
      for (int index2 = 0; index2 < kLayers; ++index2)
      {
         stereoBlockArray[index1][index2] = 0;
      } // index2
   } // index1
   getStereoBlocks (stereoBlockArray);
   for (int layer = 1; layer <= kLayers; ++layer)
   {
      for (int block = 1; 
           block <= TrigStereoBlocks::kBlocksPerLayer[layer - 1];
           ++block)
      {
         if (stereoBlockArray[layer - 1][block - 1])
         {
            stereoBlocks.setBlock (layer, block, kAll);
         } // good hit
      } // for block
   } // for layer

   ////////////////////////////////////////
   // Fill trigger tracking (AXPR, TRCR) //
   ////////////////////////////////////////
   unsigned char trackMap8[kAxialKeyWires];
   getAxialTrackMap (trackMap8);
   for (int wire = 1; wire <= kAxialKeyWires; ++wire)
   {
      if (trackMap8[wire - 1])
      {
         trackMap32[wire - 1] = kAll;
      } else {
         trackMap32[wire - 1] = 0;
      }
   } // for wire
   unsigned char axMap[kAxCellSize];
   getTrackingInfo (axMap);
   for (int cell = 1; cell <= 48; ++cell)
   {
      // check axial bit
      if (axMap[cell - 1] & kAxialBit)
      {
         // we've got one
         tracking.setAxial (cell, kAll);
      }
      // check Upos bit
      if (axMap[cell - 1] & kUposBit)
      {
         // we've got one
         tracking.setUpos (cell, kAll);
      }
      // check Uneg bit
      if (axMap[cell - 1] & kUnegBit)
      {
         // we've got one
         tracking.setUneg (cell, kAll);
      }
      // check Vpos bit
      if (axMap[cell - 1] & kVposBit)
      {
         // we've got one
         tracking.setVpos (cell, kAll);
      }
      // check Vneg bit
      if (axMap[cell - 1] & kVnegBit)
      {
         // we've got one
         tracking.setVneg (cell, kAll);
      }
   } // for cell

   ///////////////
   // Fill lumi //
   ///////////////
   int axial[kAxCellSize];
   int cal[kCcCellSize];
   int nCorHi;
   int nCorLo;
   int axCount;
   int lowPos[kLowPosSize];
   getLumiInfo (axial, cal, &nCorHi, &nCorLo, &axCount, lowPos);
   ////////////////////////////////////////
   // Ram 0 ( 0:23) tr_top_ax  <= Axial  //
   // Ram 1 ( 0:23) tr_top_cc  <= Cal    //
   // Ram 2 ( 0: 3) tr_n_hi    <= NcorHI //
   //       ( 4: 7) tr_n_lo    <= NcorLO //
   //       ( 8:11) tr_n_ax    <= AxCnt  //
   //       (12:13) tr_lowpos  <= lowpos //
   ////////////////////////////////////////

   // maps
   // Axial
   const UInt32 kLumiTime = 0x1ff; // first 3 bits
   int bit; // sun sucks
   for (bit = 0; bit < kAxCellSize; ++bit)
   {
      if (axial[bit])
      {
         // o.k.  there is something here.  We'll report it
         // as ON al the time.
         int ram = 0;         
         TriggerData::putTimeOrder (lumiPtr, ram, bit, kLumiTime);
      }
   } // for bit
   // Cal
   for (bit = 0; bit < kCcCellSize; ++bit)
   {
      if (cal[bit])
      {
         // o.k.  there is something here.  We'll report it
         // as ON al the time.
         int ram = 1;         
         TriggerData::putTimeOrder (lumiPtr, ram, bit, kLumiTime);
      }
   } // for bit
   // lowPos
   for (bit = 0; bit < kLowPosSize; ++bit)
   {
      if (lowPos[bit])
      {
         // o.k.  there is something here.  We'll report it
         // as ON al the time.
         int ram = 2;
         int absBit = 12 + bit;
         TriggerData::putTimeOrder (lumiPtr, ram, absBit, kLumiTime);
      }
   } // for bit

   // scalars
   // NcorHI
   if (nCorHi > 15) // 15 = 1111 binary
   {
      nCorHi = 15;
   }
   // the next three numbers come from the table above
   int ram = 2;
   int startbit = 0;
   int numbits = 4;
   TriggerData::putSpaceOrder (lumiPtr, ram, startbit, numbits, nCorHi, 0, 3);
   // NcorLo
   if (nCorLo > 15) // 15 = 1111 binary
   {
      nCorLo = 15;
   }
   startbit = 4;
   TriggerData::putSpaceOrder (lumiPtr, ram, startbit, numbits, nCorLo, 0, 3);
   // axCount
   if (axCount > 15) // 15 = 1111 binary
   {
      axCount = 15;
   }
   startbit = 8;
   TriggerData::putSpaceOrder (lumiPtr, ram, startbit, numbits, axCount, 0, 3);

   /////////////////////////////////////////////////
   // Put information into the TriggerData object //
   /////////////////////////////////////////////////
   const int kNumberOfTrackingBuckets = 1;
   trigDat.putAxialWires (axialWires,     kNumberOfTrackingBuckets);
   trigDat.putStereoBlocks (stereoBlocks, kNumberOfTrackingBuckets);
   trigDat.putAxialTrackMap (trackMap32,  kNumberOfTrackingBuckets);
   trigDat.putTriggerTracking (tracking,  kNumberOfTrackingBuckets);
   // Since we don't know who to believe
   // cout << "Trig Tracking:" << endl << tracking << endl;
   // cout << "axial track map ";
   // for (int alpha = 0; alpha < 112; ++alpha) {
   //    if (trackMap32[alpha])
   //    {
   //       cout << alpha + 1 << "  ";
   //    }
   // }
   // cout << endl;
   // cout << "Stereo Blocks:" << endl << stereoBlocks << endl;
   return 0;
}

//************************************************************
//Function to create the CC trigger information from the CC information
int
MCRawTriggerProxy::makeCCTriggerData(Frame& iFrame, TriggerData& trigDat,
                                     TrigCBArray *lumiPtr)
{
   // Constants used to determine time buckets for showers
   const float kVLoErg = 0.150;   // showers under 150 MeV are "Very LOW"
   const float kVLoSigma = 2.90;  // rand num sigma for VLo showers
   const float kVLoMean = -0.30;  // rand num mean for VLo showers
   const float kVLoShort = 0.66;  // probability VLo showers are 4 buckets
   const float kVLoProb = 0.05;   // probability VLo shower is problematic
   const float kVLoGaussLoBound = -2.5;  // lower bound on valid gaussian
   const float kVLoGaussHiBound = 2.5;   // upper bound on valid gaussian
   const float kVLoFlatLoBound = 0.58;   // boundary between "-3" and "-4"
   const float kVLoFlatHiBound = 0.63;   // boundary between "+3" and "+4"
   const float kMinus3Region = -3.0;     // "-3 region"
   const float kMinus4Region = -4.0;     // "-4 region"
   const float kPlus3Region = 3.0;       // "+3 region"
   const float kPlus4Region = 4.0;       // "+4 region"
   const float kLoSigma = 1.63;   // rand num sigma for lo showers
   const float kLoMean = -0.66;   // rand num mean for lo showers
   const float kLoShort = 0.6;    // probability lo showers are 4 buckets
   const float kLoProb = 0.05;    // probability lo shower is problematic
   const float kMdSigma = 0.75;   // rand num sigma for md showers
   const float kMdMean = -0.43;   // rand num mean for md showers
   const float kMdShort = 0.68;   // probability md showers are 4 buckets
   const float kMdProb = 0.05;    // probability md shower is problematic
   const float kHiSigma = 0.67;   // rand num sigma for hi showers
   const float kHiMean = -0.34;   // rand num mean for hi showers
   const float kHiShort = 0.86;   // probability hi showers are 4 buckets
   const float kHiProb = 0.05;    // probability hi shower is problematic
   const int kShortWidth = 4;     // "short" width showers are 4 buckets
   const int kLongWidth = 5;      // "long" width showers are 5 buckets
   const int kBucketOffset = 4;   // offset to central bucket

   // setup a flag to indicate first time in this method
   // used to avoid multiple initializations
   static DABoolean firstTime = true;

   // kXtalMap
   // Maps each CC crystal to a particular mixer-shaper crate and card
   // 1st index: crystal number (1..7784)
   // 2nd index: map option (0..1)
   //            kCrate (0) --> element = mixer-shaper crate number (1..24)
   //            kCard  (1) --> element = mixer-shaper card number  (1..24)
   static int kXtalMap[kNumXtals+1][kXtalMap_numOpt];

   // If first time in this method, need to do some initialization
   if(firstTime)
   {
      // Initialize kXtalMap
      // Read constants from database
      FANonSeqConstants< DBCCElecMap > map;
      extract( iFrame.record(CcStream::kElecMap), map);
      for(FANonSeqConstants< DBCCElecMap >::const_iterator iMap(map.begin());
          iMap != map.end();
          ++iMap)
      {
         const int xtal = (int)iMap->get_DaqId();
         if((xtal > 0) && (xtal <= kNumXtals))  // check to see if valid xtal
         {
            const UInt32 address = iMap->get_MSChannelAddress();
            const int crate = (int)MS_CRATE(address);
            const int card = (int)MS_SLOT(address);
            kXtalMap[xtal][kCrate] = crate;
            kXtalMap[xtal][kCard] = card;
         }
      }

      // update flag indicating 1st time in this method
      firstTime = false;
   }

   // cardErg (2-D float array)
   // energy on each mixer-shaper card within each mixer-shaper crate
   // 1st index: mixer-shaper crate (1..24)
   // 2nd index: mixer-shaper card  (1..24)
   // Element  = energy in GeV
   float cardErg[kNumCrates+1][kNumCards+1];

   // VLoTags (2-D boolean array)
   // flags each "very-low" energy shower
   // 1st index: motherboard number   (1..24)
   // 2nd index: daughterboard number (1..24)
   // Element  = true  --> shower at specified MB/DB is very-low
   //          = false --> shower at specified MB/DB is not very-low
   DABoolean VLoTags[kNumMBs+1][kNumDBs+1];

   // timeBucket (3-D boolean array)
   // time bucket of each shower
   // 1st index: motherboard number   (1..24)
   // 2nd index: daughterboard number (1..24)
   // 3rd index: bucket (0..8 for good buckets, 9 for problematic bucket)
   // Element  = true  --> shower at specified MB and DB exists
   //                      in specified timing bucket
   //          = false --> shower at specified MB and DB does not exist
   //                      in specified timing bucket
   DABoolean timeBucket[kNumMBs+1][kNumDBs+1][kNumBuckets];

   // greyBits (3-D DABoolean array)
   // output of each daughterboard
   // 1st index: motherboard number   (1..24)
   // 2nd index: daughterboard number (1..24)
   // 3rd index: greybit (0=lo bit, 1=hi bit)
   // Element  = status of specified bit (false = off, true = on)
   DABoolean greyBits[kNumMBs+1][kNumDBs+1][kNumGreybits];

   // initialize cardErg, VLoTags, timeBucket, and greyBits arrays
   int MB;  // loop variable -- declare here to avoid sun complaining
   for(MB = 1; MB <= kNumMBs; ++MB)  // MB/crate loop
   {
      for(int DB = 1; DB <= kNumDBs; ++DB)  // DB/card loop
      {
         // initialization of energy in each mixer-shaper card
         cardErg[MB][DB] = 0.0;

         // initialization of VLoTags array
         VLoTags[MB][DB] = false;

         // initialization of daughterboard responses
         for(int grey = 0; grey < kNumGreybits; ++grey)  // greybit loop
         {
            greyBits[MB][DB][grey] = false;  // greybits initialization
         }

         // time bucket initialization
         for(int bucket = 0; bucket < kNumBuckets; ++bucket)  // bucket loop
         {
            timeBucket[MB][DB][bucket] = false;
         }
      }
   }

   // Retrieve CC info
   FATable< CcEnergyHit > hits;  // stores CC info
   extract(iFrame.record(Stream::kEvent), hits );

   // Apply sharing to CC info
/*
  Pseudo code:
    uhhh....   i dunno
*/

   // Compute energy in each mixer-shaper card
   FATable< CcEnergyHit >::const_iterator iHit;
   for(iHit = hits.begin(); iHit != hits.end(); ++iHit)  // loop over CC hits
   {
      const CcEnergyHit& hit(*iHit);
      const CcCellIdType Xtal(hit.cellId());
      const CcGeV        erg(hit.energy());

      // Store energy of the shower into cardErg array
      // Note: each card covers 16 crystals, to the sum is accumulated
      int crate = kXtalMap[Xtal][kCrate];  // read crate from map
      int card = kXtalMap[Xtal][kCard];  // read card from map
      cardErg[crate][card] += erg;  // add in energy to appropriate card
   }

   // Apply turn-on curves to determine daughterboards' responses
   int Tpro;  // interation variable -- declare here to avoid sun complaints
   for(Tpro = 1; Tpro <= kNumTpros; ++Tpro)  // loop over Tpro boards
   {
      for(int proc = kNumProcPerTpro; proc > 0; --proc)  // processors
      {
         // Determine motherboard number (same as crate number)
         int MBrd = kTproMap[Tpro][proc][kMB];
         int crate = MBrd;

         // Determine correct card --> daughterboard map
         int option = kTproMap[Tpro][proc][kCardDBMapOpt];

         for(int card = 1; card <= kNumCards; ++card)  // card loop
         {
            // Determine proper daughterboard number
            int DBrd = kCardDBMap[card][option];

            // Check to see if this DB slot is actually filled
            if((DBrd < kMBDBMap[MBrd][kFirstDB]) ||
               (DBrd > kMBDBMap[MBrd][kLastDB]))
            {
               // currently checking an unfilled DB slot -- go to next slot
               continue;
            }

            // Determine probability for hi,md, or no shower
            float probH = findProb(iFrame,MBrd,DBrd,cardErg[crate][card],kHi);
            float probM = findProb(iFrame,MBrd,DBrd,cardErg[crate][card],kMd);
            float probL = findProb(iFrame,MBrd,DBrd,cardErg[crate][card],kLo);

            // Stack the probabilities (Hi,Md,Lo)
            float endpointH = probH;
            float endpointM = endpointH + probM;
            float endpointL = endpointM + probL;

            // Is the probability stack too large?
            if(endpointL > 1.0)
            {
               // probH + probM + probL > 1.0 -- renormalize
               endpointH /= endpointL;
               endpointM /= endpointL;
               endpointL /= endpointL;
            }

            // Retrieve a random number
            RandomGenerator& rand( RandomGenerator::instance() );
            float randNum = (float)rand.flat();

            // Determine shower type
            int showerType = kNumShowerTypes;  // garbage initialization
            if(randNum < endpointH)
            {
               // Hi shower
               showerType = kHi;
            }
            else if(randNum < endpointM)
            {
               // Medium shower
               showerType = kMd;
            }
            else if(randNum < endpointL)
            {
               // Lo shower
               showerType = kLo;

               // check to see if this is a very-low energy shower
               if(cardErg[crate][card] < kVLoErg)
               {
                  // flag as very-low energy shower
                  VLoTags[MBrd][DBrd] = true;
               }
            }

            // Set appropriate greybits
            if((showerType == kLo) || (showerType == kMd))
            {
               // Lo or meduim energy shower --- set Lo greybit
               greyBits[MBrd][DBrd][kLoBit] = true;
            }

            // Set Hi greybit is shower is Md or Hi
            if((showerType == kMd) || (showerType == kHi))
            {
               // Medium or high shower --- set Hi greybit
               greyBits[MBrd][DBrd][kHiBit] = true;
            }
         } // end card loop
      } // end processor loop
   } // end Tpro loop

   // Determine time bucket of each shower (fill timeBucket array)
   for(MB = 1; MB <= kNumMBs; ++MB)  // motherboard loop
   {
      // loop over all DBs of specified MB
      int DBfirst = kMBDBMap[MB][kFirstDB];
      int DBlast = kMBDBMap[MB][kLastDB];
      for(int DB = DBfirst; DB <= DBlast; ++DB)  // daughterboard loop
      {
         // determine shower type at specified MB and DB
         int type = kNumShowerTypes;  // garbage initialization
         float mean;  // used to determine end shower bucket
         float sigma;  // used to determine end shower bucket
         float widthProb;  // used to determine width of shower
         float badProb;  // used to determine if shower is problematic
         if((greyBits[MB][DB][kLoBit]) && (greyBits[MB][DB][kHiBit]))
         {
            // low bit on, high bit on --> medium shower
            type = kMd;
            mean = kMdMean;
            sigma = kMdSigma;
            widthProb = kMdShort;
            badProb = kMdProb;
         }
         else if((greyBits[MB][DB][kLoBit]) && (!greyBits[MB][DB][kHiBit]))
         {
            // low bit on, high bit off --> low shower
            type = kLo;

            // is this a very-low shower?
            if(VLoTags[MB][DB])
            {
               // VLo shower
               mean = kVLoMean;
               sigma = kVLoSigma;
               widthProb = kVLoShort;
               badProb = kVLoProb;
            }
            else
            {
               // standard Lo shower
               mean = kLoMean;
               sigma = kLoSigma;
               widthProb = kLoShort;
               badProb = kLoProb;
            }
         }
         else if((!greyBits[MB][DB][kLoBit]) && (greyBits[MB][DB][kHiBit]))
         {
            // low bit off, high bit on --> high shower
            type = kHi;
            mean = kHiMean;
            sigma = kHiSigma;
            widthProb = kHiShort;
            badProb = kHiProb;
         }
         else
         {
            // both bits off --> no shower --> go to next DB
            continue;
         }

         // Determine if shower is problematic
         RandomGenerator& rand( RandomGenerator::instance() );
         if(rand.flat() < badProb)
         {
            // turn on bit in problematic bucket and go to next DB
            timeBucket[MB][DB][kProblematic] = true;
            continue;
         }

         // Determine width of shower
         int width;  // shower's width
         if(rand.flat() < widthProb)
         {
            // shower is shorter width
            width = kShortWidth;
         }
         else
         {
            // shower is longer width
            width = kLongWidth;
         }

         // Determine last bucket in which shower exists
         float gaussian = rand.gauss(mean,sigma);
         if(VLoTags[MB][DB])
         {
            // very-low shower
            // Gaussian good only for results from -2 to 2
            // Below -2, use a flat randNum to determine if the endBucket
            //    is -3 or -4
            // Above 2, use a flat randNum to determine if the endBucket
            //    is 3 or 4
            if(gaussian < kVLoGaussLoBound)
            {
               // below gaussian region
               float flat = rand.flat();
               if(flat < kVLoFlatLoBound)
               {
                  // -3 region
                  gaussian = kMinus3Region;
               }
               else
               {
                  // -4 region
                  gaussian = kMinus4Region;
               }
            }
            else if(gaussian > kVLoGaussHiBound)
            {
               // above gaussian region
               float flat = rand.flat();
               if(flat < kVLoFlatHiBound)
               {
                  // +3 region
                  gaussian = kPlus3Region;
               }
               else
               {
                  // +4 region
                  gaussian = kPlus4Region;
               }
            }
         }

         // Truncate the gaussian number and add the offset to determine
         // the last timing bucket of the shower
         int endBucket = ((int)gaussian) + kBucketOffset;

         // Determine first bucket in which shower exists
         int beginBucket = endBucket - width + 1;

         // Is this shower in the region we keep (buckets 0..8)
         if((beginBucket > kLastBucket) || (endBucket < kFirstBucket))
         {
            // shower is out of range -- go to next DB
            continue;
         }

         // Truncate shower region to correct range (0..8)
         if(beginBucket < kFirstBucket)
         {
            // shower begins too early -- set to begin in first bucket (0)
            beginBucket = kFirstBucket;
         }
         if(endBucket > kLastBucket)
         {
            // shower ends too late -- set to end in last bucket (8)
            endBucket = kLastBucket;
         }

         // set correct bucket bits
         for(int bucket = beginBucket; bucket <= endBucket; ++bucket)
         {
            timeBucket[MB][DB][bucket] = true;
         }
      } // end DB loop
   } // end MB loop / end determining time buckets

   // ccTiles (TrigCCTiles object)
   // used to fill TriggerData object
   TrigCCTiles ccTiles;
   ccTiles.zeroTiles();  // zero the TrigCCTiles object
   ccTiles.setMask(kNumBuckets);  // set up mask in TrigCCTiles object

   // Fill the TrigCCTiles object
   // To set a bit, use setGreyBits method of TrigCCTiles:
   // TrigCCTiles::setGreyBits(mixer#,daughter#,which bit,which bucket)
   for(MB = 1; MB <= kNumMBs; ++MB)  // loop over all MBs
   {
      // Determine filled DB slots
      int DBfirst = kMBDBMap[MB][kFirstDB];
      int DBlast = kMBDBMap[MB][kLastDB];
      for(int DB = DBfirst; DB <= DBlast; ++DB)  // loop over filled DB slots
      {
         for(int grey = 0; grey < kNumGreybits; ++grey)  // loop over greybits
         {
            if(greyBits[MB][DB][grey])
            {
               // bits need to be set
               for(int bucket = 0; bucket < kNumBuckets; ++bucket)  // bkt loop
               {
                  if(timeBucket[MB][DB][bucket])
                  {
                     // set bit in specified bucket
                     ccTiles.setGreyBits(MB,DB,grey,bucket);
                  }
               }
            }
         } // end loop over both greybits
      } // end loop over all DBs
   } // end loop over all MBs

   //  Fill the Tpro data into the TriggerData object
   trigDat.putCCTiles(ccTiles, kNumBuckets);

   //  TproArray (4-D FORTRAN array)
   //  used as input parameter for CC-digital trigger crates
   //  1st index: greybit number (1=lo bit, 2=hi bit)
   //  2nd index: processor number on Tpro board (1..4)
   //  3rd index: Tpro board number (1..6)
   //  4th index: time bucket (1=early, 2=in time, 3=late, 4=problematic)
   //  Element  = 24 bit integer, LSB corresponds to DB 1, MSB = DB24
   TproInfoArray TproArray;

   // Fill TproArray
   int bucket;  // interation variable -- declare here to avoid sun complaints
   for(bucket = 0; bucket < kNumBuckets; ++bucket)  // bucket loop
   {
      for(int Tpro = 1; Tpro <= kNumTpros; ++Tpro)  // Tpro board loop
      {
         for(int proc = kNumProcPerTpro; proc > 0; --proc)  // QPR pair loop
         {
            // Determine motherboard number
            int MBrd = kTproMap[Tpro][proc][kMB];
            for(int grey = kNumGreybits-1; grey >= 0; --grey)  // greybit loop
            {
               // Will shift the data value of the specified greybit for
               // each daughterboard into the variable temp
               FInteger temp = 0;
               for(int DBrd = kNumDBs; DBrd > 0; --DBrd)  // DB loop (24..1)
               {
                  // Shift all bits in temp one to the left
                  temp = temp << 1;

                  // Is DB slot filled?
                  if((DBrd < kMBDBMap[MBrd][kFirstDB]) ||
                     (DBrd > kMBDBMap[MBrd][kLastDB]))
                  {
                     // Empty DB slot....  go to next slot
                     continue;
                  }

                  // If specified greybit is set, then set LSB of temp
                  if(ccTiles.greybits(MBrd,DBrd,grey,bucket))
                  {
                     // turn on LSB of temp
                     ++temp;
                  }
               } // end loop over DBs
               // Load temp into correct array element
               int bucketIndex = bucket + 1;  // 4th index of TproArray
               int greyIndex = grey + 1;  // 1st index of TproArray
               TproArray(greyIndex,proc,Tpro,bucketIndex) = temp;
            } // end loop over greybits
         } // end loop over processors (QPR pairs)
      } // end loop over Tpros
   } // end loop over buckets

   //  counts (3-D FORTRAN array)
   //  the counts output of the CC-digital trigger crates
   //  1st index: shower type (1=lo, 2=md, 3=hi)
   //  2nd index: time bucket (1=early, 2=in time, 3=late, 4=problematic)
   //  3rd index: region of CC (1=CB, 2=CE)
   //  Element  = number of specified showers in event
   CountsArray counts;

   //  oldBits (3-D FORTRAN array)
   //  the CLEOIIbits output of the CC-digital trigger crates
   //  1st index: shower type (1=lo, 2=md, 3=hi)
   //  2nd index: time bucket (1=early, 2=in time, 3=late, 4=problematic)
   //  3rd index: region of CC (1=CB, 2=CE)
   //  Element  = 0 --> no showers
   //           = 1 --> at least one shower
   //           = 2 --> at least two non-adjacent showers
   //           = 3 --> at least one pair of back-to-back showers
   CLEOIIbits oldBits;

   // Send the input to the CC-digital Trigger Crates and
   // receive the output of the CC-digital Trigger Crates
   // Input: TproArray
   // Output: counts and bits
   ccdigtrig_(&TproArray, &counts, &oldBits);

   // Store CC-digital trigger crates' outputs in Lumi board
   for(bucket = 0; bucket < kNumBuckets; ++bucket)  // bucket loop
   {
      for(int type = 0; type < kNumShowerTypes; ++type)  // shower type loop
      {
         for(int reg = 0; reg < kNumCCreg; ++reg)  // CC region loop
         {
            // read in counts and bits data
            UInt32 cData = (UInt32)counts(type+1,bucket+1,reg+1);
            UInt32 bData = (UInt32)oldBits(type+1,bucket+1,reg+1);

            // read in QPR numebrs and offsets
            unsigned int cQPR = kLumiCountsMap[type][reg][kQPR];
            unsigned int cOff = kLumiCountsMap[type][reg][kOffset];
            unsigned int bQPR = kLumiOldbitsMap[type][reg][kQPR];
            unsigned int bOff = kLumiOldbitsMap[type][reg][kOffset];

            // write counts and oldbits data to Lumi board
            lumiPtr->setBits(cQPR,bucket,cData,cOff,kNumCountBits);
            lumiPtr->setBits(bQPR,bucket,bData,bOff,kNumOldBits);
         }
      }
   }

   return 0;
}

//************************************************************
//Function to return probability of being a certain type of shower based
//on the turn-on curve constants.  Used by makeCCTriggerData
//
// Turn-on curve description
//
// Probability of low shower vs Energy
//    Prob
//     ^
//     |  I        II      III      IV      V
//  H  |               ---------
//     |              /          \
//     |             /            \
//     |            /              \
//     |           /                \
//  B1 |----------/                  \
//     |                              \
//  B2 |                               \-------------
//     |
//     ---------------------------------------------------> Energy
//                  E1              E2
//             -->  W1 <--       <--W2->
//
// Region 1: slope zero line at probability B1
// Region 2: positive slope line, midpoint at energy E1, energy width of W1
// Region 3: slope zero line at probability H
// Region 4: negative slope line, midpoint at energy E2, energy width of W2
// Region 5: slope zero line at probability B2
//
// Probability of medium shower vs Energy follows the same format
// Probability of high shower vs Energy does not have parts 4 and 5
//     -- instead, part 3 extends out to "infinite energy"
//
// Determining probability if energy is in region 2 (or 4):
// Using similar triangles, the following proportion is easy to determine
//       prob - B1              H - B1
//   --------------------   =   ------
//   energy - (E1 - W1/2)         W1
//
// Special cases:
// If W1 == 0 and energy == E1, then we are in region 1
// If W2 == 0 and energy == E2, then we are in region 3
// If E1 == E2, W1 == W2, and energy == E1 (example, endcap ideal medium
// TOC prob at the thresh-hold value) then we are in region 1
//
// findProb: determine probability of being a shower of type specified by
// 5th input argument by using appropriate turn-on curve constants
//
// 1st input parameter: frame
// 2nd input parameter: motherboard number (1..24)
// 3rd input parameter: daughterboard number (1..24)
// 4th input parameter: energy of shower (in GeV)
// 5th input parameter: type of shower (0=lo, 1=md, 2=hi)
float
MCRawTriggerProxy::findProb(const Frame& iFrame, int MB, int DB, float erg,
                            int showerType) const
{
   // setup a flag to indicate the first time in this method
   static DABoolean firstTime = true;

   // kTOCconsts
   // Turn-on curve constants
   // 1st index: MB number (1..24)
   // 2nd index: DB number (1..24)
   // 3rd index: specific curve (0=lo, 1=md, 2=hi)
   // 4th index: specific constant (0=H,1=B1,2=E1,3=W1,4=B2,5=E2,6=W2)
   // WARNING: this array is initialized only once based on the TOC
   //          constants stored in the database for the appropriate
   //          run-number.
   // IMPROTANT NOTE: use this program for only one run at a time
   static float kTOCconsts[kNumMBs+1][kNumDBs+1][kNumShowerTypes][kNumTOCconsts];

   // If first time in this method, read in TOC constants from database
   if(firstTime)
   {
      // extract TOC constants
      FAConstants< DBTrigMCCCATOC > TOCconsts;
      extract( iFrame.record(TrigStream::kTrigMCCCATOC), TOCconsts );
      if(!TOCconsts.valid())
      {
         // constants not available
         report( EMERGENCY, kFacilityString )
            << "Unable to extract turn-on curve constants -- terminating"
            << endl;
         assert(false);
      }

      // loop over all TOC constants
      FAConstants< DBTrigMCCCATOC >::const_iterator iter;
      FAConstants< DBTrigMCCCATOC >::const_iterator last = TOCconsts.end();
      for(iter = TOCconsts.begin(); iter != last; ++iter)
      {
         // dereference constants
         DBTrigMCCCATOC TOC = *iter;

         // retrieve constants
         int MB = (int)TOC.get_Motherboard();
         int DB = (int)TOC.get_Daughterboard();
         float LoH = TOC.get_LoHeight();
         float LoB1 = TOC.get_LoBase1();
         float LoB2 = TOC.get_LoBase2();
         float LoE1 = TOC.get_LoEnergy1();
         float LoE2 = TOC.get_LoEnergy2();
         float LoW1 = TOC.get_LoWidth1();
         float LoW2 = TOC.get_LoWidth2();
         float MdH = TOC.get_MdHeight();
         float MdB1 = TOC.get_MdBase1();
         float MdB2 = TOC.get_MdBase2();
         float MdE1 = TOC.get_MdEnergy1();
         float MdE2 = TOC.get_MdEnergy2();
         float MdW1 = TOC.get_MdWidth1();
         float MdW2 = TOC.get_MdWidth2();
         float HiH = TOC.get_HiHeight();
         float HiB1 = TOC.get_HiBase1();
         float HiE1 = TOC.get_HiEnergy1();
         float HiW1 = TOC.get_HiWidth1();

         // Begin reality checks on constants
         DABoolean good = true;  // flag indicating failed check
         if((LoH < 0.0) || (LoH > 1.0))
         {
            // LoHeight not physical
            report( EMERGENCY, kFacilityString )
               << "LoHeight not physical" << endl;
            good = false;
         }
         if((LoB1 < 0.0) || (LoB1 > 1.0))
         {
            // LoBase1 not physical
            report( EMERGENCY, kFacilityString )
               << "LoBase1 not physical" << endl;
            good = false;
         }
         if((LoB2 < 0.0) || (LoB2 > 1.0))
         {
            // LoBase2 not physical
            report( EMERGENCY, kFacilityString )
               << "LoBase2 not physical" << endl;
            good = false;
         }
         if((LoH < LoB1) || (LoH < LoB2))
         {
            // LoHeight to small
            report( EMERGENCY, kFacilityString )
               << "LoHeight to small relative to baselines" << endl;
            good = false;
         }
         if(LoE1 < 0.0)
         {
            // LoEnergy1 not physical
            report( EMERGENCY, kFacilityString )
               << "LoEnergy1 not physical" << endl;
            good = false;
         }
         if(LoW1 < 0.0)
         {
            // LoWidth1 not physical
            report( EMERGENCY, kFacilityString )
               << "LoWidth1 not physical" << endl;
            good = false;
         }
         if(LoE2 < 0.0)
         {
            // LoEnergy2 not physical
            report( EMERGENCY, kFacilityString )
               << "LoEnergy2 not physical" << endl;
            good = false;
         }
         if(LoW2 < 0.0)
         {
            // LoWidth2 not physical
            report( EMERGENCY, kFacilityString )
               << "LoWidth2 not physical" << endl;
            good = false;
         }
         if((LoE2 - (LoW2 / 2.0)) < (LoE1 + (LoW1 / 2.0)))
         {
            // overlapping turn-on and turn-off
            report( EMERGENCY, kFacilityString )
               << "Low turn-on region overlaps low turn-off region" << endl;
            good = false;
         }
         if((MdH < 0.0) || (MdH > 1.0))
         {
            // MdHeight not physical
            report( EMERGENCY, kFacilityString )
               << "MdHeight not physical" << endl;
            good = false;
         }
         if((MdB1 < 0.0) || (MdB1 > 1.0))
         {
            // MdBase1 not physical
            report( EMERGENCY, kFacilityString )
               << "MdBase1 not physical" << endl;
            good = false;
         }
         if((MdB2 < 0.0) || (MdB2 > 1.0))
         {
            // MdBase2 not physical
            report( EMERGENCY, kFacilityString )
               << "MdBase2 not physical" << endl;
            good = false;
         }
         if((MdH < MdB1) || (MdH < MdB2))
         {
            // MdHeight to small
            report( EMERGENCY, kFacilityString )
               << "MdHeight to small relative to baselines" << endl;
            good = false;
         }
         if(MdE1 < 0.0)
         {
            // MdEnergy1 not physical
            report( EMERGENCY, kFacilityString )
               << "MdEnergy1 not physical" << endl;
            good = false;
         }
         if(MdW1 < 0.0)
         {
            // MdWidth1 not physical
            report( EMERGENCY, kFacilityString )
               << "MdWidth1 not physical" << endl;
            good = false;
         }
         if(MdE2 < 0.0)
         {
            // MdEnergy2 not physical
            report( EMERGENCY, kFacilityString )
               << "MdEnergy2 not physical" << endl;
            good = false;
         }
         if(MdW2 < 0.0)
         {
            // MdWidth2 not physical
            report( EMERGENCY, kFacilityString )
               << "MdWidth2 not physical" << endl;
            good = false;
         }
         if((MdE2 - (MdW2 / 2.0)) < (MdE1 + (MdW1 / 2.0)))
         {
            // overlapping turn-on and turn-off
            report( EMERGENCY, kFacilityString )
               << "Mid turn-on region overlaps mid turn-off region" << endl;
            good = false;
         }
         if((HiH < 0.0) || (HiH > 1.0))
         {
            // HiHeight not physical
            report( EMERGENCY, kFacilityString )
               << "HiHeight not physical" << endl;
            good = false;
         }
         if((HiB1 < 0.0) || (HiB1 > 1.0))
         {
            // HiBase1 not physical
            report( EMERGENCY, kFacilityString )
               << "HiBase1 not physical" << endl;
            good = false;
         }
         if(HiE1 < 0.0)
         {
            // HiEnergy1 not physical
            report( EMERGENCY, kFacilityString )
               << "HiEnergy1 not physical" << endl;
            good = false;
         }
         if(HiW1 < 0.0)
         {
            // HiWidth1 not physical
            report( EMERGENCY, kFacilityString )
               << "HiWidth1 not physical" << endl;
            good = false;
         }
         if(!good)
         {
            report( EMERGENCY, kFacilityString )
               << "Index: " << TOC.get_Index() << endl;
            report( EMERGENCY, kFacilityString )
               << "Motherboard = " << MB << endl;
            report( EMERGENCY, kFacilityString )
               << "Daughterboard = " << DB << endl;
            report( EMERGENCY, kFacilityString )
               << "LoHeight = " << LoH << endl;
            report( EMERGENCY, kFacilityString )
               << "LoBase1 = " << LoB1 << endl;
            report( EMERGENCY, kFacilityString )
               << "LoBase2 = " << LoB2 << endl;
            report( EMERGENCY, kFacilityString )
               << "LoEnergy1 = " << LoE1 << endl;
            report( EMERGENCY, kFacilityString )
               << "LoEnergy2 = " << LoE2 << endl;
            report( EMERGENCY, kFacilityString )
               << "LoWidth1 = " << LoW1 << endl;
            report( EMERGENCY, kFacilityString )
               << "LoWidth2 = " << LoW2 << endl;
            report( EMERGENCY, kFacilityString )
               << "MdHeight = " << MdH << endl;
            report( EMERGENCY, kFacilityString )
               << "MdBase1 = " << MdB1 << endl;
            report( EMERGENCY, kFacilityString )
               << "MdBase2 = " << MdB2 << endl;
            report( EMERGENCY, kFacilityString )
               << "MdEnergy1 = " << MdE1 << endl;
            report( EMERGENCY, kFacilityString )
               << "MdEnergy2 = " << MdE2 << endl;
            report( EMERGENCY, kFacilityString )
               << "MdWidth1 = " << MdW1 << endl;
            report( EMERGENCY, kFacilityString )
               << "MdWidth2 = " << MdW2 << endl;
            report( EMERGENCY, kFacilityString )
               << "HiHeight = " << HiH << endl;
            report( EMERGENCY, kFacilityString )
               << "HiBase1 = " << HiB1 << endl;
            report( EMERGENCY, kFacilityString )
               << "HiEnergy1 = " << HiE1 << endl;
            report( EMERGENCY, kFacilityString )
               << "HiWidth1 = " << HiW1 << endl;
            report( EMERGENCY, kFacilityString )
               << "Terminating" << endl;
            assert(false);
         }

         // Fill kTOCconsts array
         kTOCconsts[MB][DB][kLo][kHeight] = LoH;
         kTOCconsts[MB][DB][kLo][kBase1] = LoB1;
         kTOCconsts[MB][DB][kLo][kBase2] = LoB2;
         kTOCconsts[MB][DB][kLo][kErg1] = LoE1;
         kTOCconsts[MB][DB][kLo][kErg2] = LoE2;
         kTOCconsts[MB][DB][kLo][kWidth1] = LoW1;
         kTOCconsts[MB][DB][kLo][kWidth2] = LoW2;
         kTOCconsts[MB][DB][kMd][kHeight] = MdH;
         kTOCconsts[MB][DB][kMd][kBase1] = MdB1;
         kTOCconsts[MB][DB][kMd][kBase2] = MdB2;
         kTOCconsts[MB][DB][kMd][kErg1] = MdE1;
         kTOCconsts[MB][DB][kMd][kErg2] = MdE2;
         kTOCconsts[MB][DB][kMd][kWidth1] = MdW1;
         kTOCconsts[MB][DB][kMd][kWidth2] = MdW2;
         kTOCconsts[MB][DB][kHi][kHeight] = HiH;
         kTOCconsts[MB][DB][kHi][kBase1] = HiB1;
         kTOCconsts[MB][DB][kHi][kErg1] = HiE1;
         kTOCconsts[MB][DB][kHi][kWidth1] = HiW1;
      }

      // update flag indicating 1st time in this method
      firstTime = false;
   }

   // First, load E1 and W1
   float E1 = kTOCconsts[MB][DB][showerType][kErg1];
   float W1 = kTOCconsts[MB][DB][showerType][kWidth1];

   // Is the energy in region 1?
   if(erg <= (E1 - (W1 / 2.0)))
   {
      // Region 1: probability = B1
      float B1 = kTOCconsts[MB][DB][showerType][kBase1];
      return B1;
   }

   // Is the energy in region 2?
   if(erg < (E1 + (W1 / 2.0)))  // Note, this cannot be true if W1 == 0
   {
      // Region 2: use similar triangles to determine probability
      // Note, there is no possibility for division by zero:
      // If W1 = 0 and erg < E1 + W1 / 2.0, then we are in region 1.
      // This statement would not be reached.
      // Read in B1 and H constants
      float B1 = kTOCconsts[MB][DB][showerType][kBase1];
      float H = kTOCconsts[MB][DB][showerType][kHeight];

      // Use similar triangle proportionalities to determine probability
      float prob = (((H - B1) * (erg + (W1 / 2.0) - E1)) / W1) + B1;
      return prob;
   }

   // If showerType specified is Hi (kHi), then we are in part 3:
   if(showerType == kHi)
   {
      // Region 3 (Prob of high vs energy): probability = H
      float H = kTOCconsts[MB][DB][showerType][kHeight];
      return H;
   }

   // Load in E2 and W2 constants
   float E2 = kTOCconsts[MB][DB][showerType][kErg2];
   float W2 = kTOCconsts[MB][DB][showerType][kWidth2];

   // Is the energy in region 3?
   if(erg <= (E2 - (W2 / 2.0)))
   {
      // Region 3: probability = H
      float H = kTOCconsts[MB][DB][showerType][kHeight];
      return H;
   }

   // Is the energy in region 4?
   if(erg < (E2 + (W2 / 2.0)))  // can't be true if W2 == 0
   {
      // We're in part 4: negative slope piece (use similar triangles)
      // As before, there is no possibility for division by zero since this
      // statement cannot be reached if W2 == 0.
      // Read in H and B2 constants
      float H = kTOCconsts[MB][DB][showerType][kHeight];
      float B2 = kTOCconsts[MB][DB][showerType][kBase2];

      // Determine probability using similar triangle proportionalities
      float prob = (((H - B2) * (E2 + (W2 / 2.0) - erg)) / W2) + B2;
      return prob;
   }

   // Energy must be in region 5: probability = B2
   float B2 = kTOCconsts[MB][DB][showerType][kBase2];
   return B2;
} // end findProb

//
// const member functions
//

//
// static member functions
//


