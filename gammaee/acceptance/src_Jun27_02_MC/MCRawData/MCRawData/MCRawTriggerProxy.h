#if !defined(MCRAWDATA_MCRAWTRIGGERPROXY_H)
#define MCRAWDATA_MCRAWTRIGGERPROXY_H
// -*- C++ -*-
//
// Package:     MCRawData
// Module:      MCRawTriggerProxy
// 
// Description:
//
// Usage:
//
// Author:      Brian K. Heltsley
// Created:     Tue Feb 23 17:35:15 EST 1999
// $Id: MCRawTriggerProxy.h,v 1.8 2002/06/13 19:53:46 bkh Exp $
//
// Revision history
//
// $Log: MCRawTriggerProxy.h,v $
// Revision 1.8  2002/06/13 19:53:46  bkh
// Implement use of ccmcpeeldaqmap in the calorimeter processing
// Implement parameter to turn off trigger simulation as with other detectors
//
// Revision 1.7  2001/12/19 19:09:52  kamal
//  add overloping showers algorithm for showers with E greater than 150 MeV
//
// Revision 1.6  2001/09/17 18:47:01  kamal
// add cc trigger and L1D simulations
//
// Revision 1.5  2001/07/02 18:20:23  cplager
// working copy of tracking trigger info
//
// Revision 1.4  2001/01/24 15:39:58  rhans
// Data inversion (from TriggerData to MCRawTrigger) is now complete and correct.
//
// Revision 1.3  2000/03/15 18:08:49  rhans
// First version
//
// Revision 1.2  1999/06/04 21:39:08  bkh
// CC code closer to working, structural mods to others
//
// Revision 1.1  1999/02/25 22:02:13  bkh
// fix name conflicts
//
// Revision 1.1.1.1  1999/02/25 20:29:11  bkh
// imported MCRawData sources
//
//

// system include files

// user include files
#include "DataHandler/ProxyTemplate.h"
#include "RawData/RawTrigger.h"
#include "C3cc/CcEnergyHit.h"  // added by Norm
//#include "TriggerData/TrigCCTiles.h"  // added by Norm
//#include "TriggerData/TriggerData.h"  // added by Norm
#include "ToolBox/TBFortranArrays.h"  // added by Norm
#include "Experiment/fortran_types.h"  // added by Norm
#include "CommandPattern/Parameter.h"

// forward declarations
class TriggerData;
class TrigCBArray;
class Frame;

#include "STLUtility/fwd_vector.h"

class MCRawTriggerProxy : public ProxyTemplate< RawTrigger >
{
      // friend classes and functions

   public:
      // constants, enums and typedefs
      enum  // Xtal map options
      {
         kCrate,             // option 0: element = mixer-shaper crate number
         kCard,              // option 1: element = mixer-shaper card  number
         kXtalMap_numOpt     // Two options
      };
      enum  // CardDB map options
      {
         kNoRev,             // option 0: do not use reversing effect
         kRev,               // option 1: use reversing effect
         kCardDBMap_numOpt   // Two options
      };
      enum  // Tpro map options
      {
         kMB,                // option 0: determine motherboard number
         kCardDBMapOpt,      // option 1: determine kCardDBMap option
         kTproMap_numOpt     // Two options
      };
      enum  // LumiCounts map options AND LumiBits map options
      {
         kQPR,               // option 0: determine QPR number
         kOffset,            // option 1: determibe bit offset
         kLumiMap_numOpt     // Two options
      };
      enum  // MBDB map options
      {
         kFirstDB,        // option 0 = first DB slot filled
         kLastDB,         // option 1 = last DB slot filled
         kMBDBMap_numOpt  // two options
      };
      enum  // regions of the CC
      {
         kCB,           // kCB = 0
         kCE,           // kCE = 1
         kNumCCreg      // two regions within CC
      };
      enum  // Timing buckets
      {
         kFirstBucket = 0,  // bucket 0 is the first bucket we keep
         kLastBucket = 8,  // bucket 8 is the last bucket we keep
         kProblematic = 9,  // bucket 9 is the problematic bucket
         kNumBuckets = 10   // 10 buckets: 0..9
      };
      enum  // greybits
      {
         kLoBit,        // lo greybit = 0
         kHiBit,        // hi greybit = 1
         kNumGreybits   // number of greybits = 2
      };
      enum  // types of showers
      {
         kLo = 0,             // Lo shower = 0
         kMd = 1,             // Mid shower = 1
         kHi = 2,             // Hi shower = 2
         kNumShowerTypes = 3  // Three types of showers
      };
      enum  // constants used to characterize turn-on curves: findProb
      {
         kHeight,         // constant H
         kBase1,          // constant B1
         kErg1,           // constant E1
         kWidth1,         // constant W1
         kBase2,          // constant B2
         kErg2,           // constant E2
         kWidth2,         // constant W2
         kNumTOCconsts    // 7 consts characterizing each turn-on curve (TOC)
      };
      enum  // other constants
      {
         kNumXtals = 7784,          // 7784 CC crystals
         kNumCrates = 24,           // 24 mixer-shaper crates (1..24)
         kNumMBs = 24,              // 24 motherboards (1..24)
         kNumCards = 24,            // 24 mixer-shaper cards per crate (1..24)
         kNumDBs = 24,              // 24 DBs per MB (1..24)
         kNumTpros = 6,             // 6 Tpro boards (1..6)
         kNumProcPerTpro = 4,       // 4 processors per TPRO board (1..4)
         kNumCountBits = 3,         // 3 bits used to store shower counts
         kNumOldBits = 2            // 2 bits used to store oldbits
      };

      typedef RawTrigger value_type;
      typedef TBFortran4DArray< FInteger,
                                kNumGreybits,
                                kNumProcPerTpro,
                                kNumTpros,
                                kNumBuckets > TproInfoArray;
      typedef TBFortran3DArray< FInteger,
                                kNumShowerTypes,
                                kNumBuckets,
                                kNumCCreg > CountsArray;
      typedef TBFortran3DArray< FInteger,
                                kNumShowerTypes,
                                kNumBuckets,
                                kNumCCreg > CLEOIIbits;

      // Constructors and destructor
      MCRawTriggerProxy( const Parameter<DABoolean>& aParam );
      virtual ~MCRawTriggerProxy();

      // member functions
      // const member functions
      // static member functions
   protected:
      // protected member functions
      virtual void invalidateCache() ;
      virtual const value_type* faultHandler( const Record& aRecord,
					      const DataKey& aKey );
      // protected const member functions
   private:
      // Constructors and destructor
      MCRawTriggerProxy( const MCRawTriggerProxy& );
      // assignment operator(s)
      const MCRawTriggerProxy& operator=( const MCRawTriggerProxy& );
      // private member functions
      // private const member functions

      //Function to create the TriggerData from DR and CC information
      int makeTriggerData(const Record& iRecord, TriggerData& trigDat);

      //Function to create RawTrigger from TriggerData
      int fillRawTrigger(const TriggerData& trigDat);
      
      //Function to fill sparsified boards
      //Give it number of boards, which type of board (TriggerData::TB_AXTR, etc),
      //and the trigger data object it is using to fill the m_words array.
      int fillSparsifiedBoard(int num_boards,UInt32 which_board,
                              const TriggerData& trigDat);

      //Function to fill normal (unsparsified) boards
      //Give it number of boards, which type of board (TriggerData::TB_AXPR, etc),
      //and the trigger data object it is using to fill the m_words array.
      int fillNormalBoard(int num_boards,UInt32 which_board,
                          const TriggerData& trigDat);

      //Function to create the L1D Trigger data from the DR information
      int makeL1TriggerData(const Record& iRecord, TriggerData& trigDat);
                            

      //Function to create the TrackingTrigger data from the DR information
      int makeTrackingTriggerData(const Record& iRecord, TriggerData& trigDat,
                                  TrigCBArray *lumiPtr);
      
      //Function to create the CCTrigger data from the CC information
      int makeCCTriggerData(Frame& iFrame, TriggerData& trigDat,
                            TrigCBArray *lumiPtr);

      //Function to determine probability based on TOC constants
      // 1st input parameter: frame (needed to extract TOC constants)
      // 2nd input parameter: motherbaord number (1..24)
      // 3rd input parameter: daughterboard number (1..24)
      // 4th input parameter: energy of a shower (in GeV)
      // 5th input parameter: which TOC to use (0=lo, 1=md, 2=hi)
      // Output: pobability that a shower of energy given by rth input
      // parameter will be a shower of type given by 5th input parameter
      // based on TOC parameters for specified MB and DB
      float findProb(const Frame& iFrame, int MB, int DB, float erg,
                     int showerType) const;

      
      //**************************************************
      // data members
      value_type* m_RawTrigger ;

      DABoolean m_getRawTrigger ;

      STL_VECTOR( UInt32 )& m_words ; // this proxy owns the data words!

      // static data members

      // CardDB map
      // Works two ways:
      //   1) Given mixer-shaper card number, determine daughterboard number
      //   2) Given daughterboard number, determine mixer-shaper card number
      // East half barrel crates have some reversing between card# and DB#:
      //   card  1 --> DB  6, card  2 --> DB  5, ..., card  6 --> DB  1
      //   card  7 --> DB 12, card  8 --> DB 11, ..., card 12 --> DB  6
      //   card 13 --> DB 18, card 14 --> DB 17, ..., card 18 --> DB 12
      //   card 19 --> DB 24, card 20 --> DB 23, ..., card 24 --> DB 19
      // West half barrel crates and endcap crates do not have this reversing
      // 1st index: mixer-shaper card number (1..24)
      // 2nd index: map option (0..1)
      //            kNoRev (0) --> do not use the reversing effect
      //            kRev   (1) --> use the reversing effect
      // Element = daughterboard number (1..24)
      // If instead, the daughterboard number is used as the 1st index, then
      // the element equals the mixer-shaper card number
      static const int kCardDBMap[kNumCards+1][kCardDBMap_numOpt];

      // Tpro map
      // Maps each processor on each Tpro board to a paticular motherboard
      // number and determines the correct option to use with kCardDBMap
      // 1st index: Tpro number (1..6)
      // 2nd index: processor number on the Tpro board (1..4)
      // 3rd index: map option (0..1)
      //            kMB           (0) --> element = motherboard number (1..24)
      //            kCardDBMapOpt (1) --> element = kCardDBMap option
      static const int kTproMap[kNumTpros+1][kNumProcPerTpro+1][kTproMap_numOpt];

      // LumiCounts map
      // Determines Lumi QPR and offset for shower counts of each shower type
      // in both regions of the CC
      // 1st index: shower type (kLo, kMd, kHi --> 0, 1, 2 --> lo, md, hi)
      // 2nd index: CC region (kCB, kCE --> 0, 1 --> barrel, endcap)
      // 3rd index: map option (0..1)
      //            kQPR    (0) --> element = Lumi QPR number (0..7)
      //            kOffset (1) --> element = bit offset (0..23)
      static const unsigned int kLumiCountsMap[kNumShowerTypes][kNumCCreg][kLumiMap_numOpt];

      // LumiOldbits map
      // Determines Lumi QPR and offset for CLEOII old bits of each shower
      // type in both regions of the CC
      // 1st index: shower type (kLo, kMd, kHi --> 0, 1, 2 --> lo, md, hi)
      // 2nd index: CC region (kCB, kCE --> 0, 1 --> barrel, endcap)
      // 3rd index: map option (0..1)
      //            kQPR    (0) --> element = Lumi QPR number (0..7)
      //            kOffset (1) --> element = bit offset (0..23)
      static const unsigned int kLumiOldbitsMap[kNumShowerTypes][kNumCCreg][kLumiMap_numOpt];

      // kMBDBMap
      // Determines first DB slot filled and last DB slot filled on each MB
      // 1st index: MB number (1..24)
      // 2nd index: map option (0..1)
      //            kFirstDB (0) --> element = first DB slot filled on MB
      //            kLastDB  (1) --> element = last  DB slot filled on MB
      static const int kMBDBMap[kNumMBs+1][kMBDBMap_numOpt];
};

// inline function definitions
#endif /* MCRAWDATA_MCRAWTRIGGERPROXY_H */
