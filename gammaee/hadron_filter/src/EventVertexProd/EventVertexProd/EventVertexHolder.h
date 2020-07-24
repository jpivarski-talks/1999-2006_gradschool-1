#if !defined(EVENTVERTEXPROD_EVENTVERTEXHOLDER_H)
#define EVENTVERTEXPROD_EVENTVERTEXHOLDER_H
// -*- C++ -*-
//
// Package:     <EventVertexProd>
// Module:      EventVertexHolder
// 
/*class EventVertexHolder EventVertexHolder.h EventVertexProd/EventVertexHolder.h

 Description: Holder of EventVertexProd parameters

 Usage:
    <usage>

    */
// system include files

// user include files
#include "CommandPattern/Menu.h"
#include "CommandPattern/Parameter.h"


// forward declarations

//statics for Suez Parameters
static float d0Param = .01; //m
static float z0Param = .05; //m
static float momParam = .25;//GeV
static float NumMinTrkParam  = 3;
static float MaxChi2perTrackParam = 5;
static DABoolean TrackCutNormParam = false;
class EventVertexHolder
{
  // ---------- friend classes and functions ---------------

 public:
  // ---------- constants, enums and typedefs --------------
   
      
  // ---------- Constructors and destructor ----------------
  EventVertexHolder(Module* iModule);
  virtual ~EventVertexHolder();

  // ---------- member functions ---------------------------

  // ---------- const member functions ---------------------
  inline float d0_Param() const;
  inline float z0_Param() const;
  inline float TMom_Param() const;
  inline float MinTrk_Param() const;
  inline float MaxChi2_Param() const;
  inline DABoolean TrackCutNorm_Param() const;    
  // ---------- static member functions --------------------

 protected:
  // ---------- protected member functions -----------------

  // ---------- protected const member functions -----------

 private:
  // ---------- Constructors and destructor ----------------
  EventVertexHolder(const EventVertexHolder&); // stop default

  // ---------- assignment operator(s) ---------------------
  const EventVertexHolder& operator=(const EventVertexHolder&); // stop default

  // ---------- private member functions -------------------

  // ---------- private const member functions -------------

  // ---------- data members -------------------------------
  Menu             m_eventVertexParam;
  Parameter<float> m_Param_d0;
  Parameter<float> m_Param_z0;
  Parameter<float> m_Param_TMom;
  Parameter<float> m_Param_MinTrk;
  Parameter<float> m_Param_MaxChi2;
  Parameter<DABoolean> m_Param_TrackCutNorm;

     
      // ---------- static data members ------------------------

};

// inline function definitions
inline float EventVertexHolder::MinTrk_Param() const
{
   return m_Param_MinTrk.value();
}

inline float EventVertexHolder::d0_Param() const
{
   return m_Param_d0.value();
}
inline float EventVertexHolder::z0_Param() const
{
   return m_Param_z0.value();
}
inline float EventVertexHolder::TMom_Param() const
{
   return m_Param_TMom.value();
}
inline float EventVertexHolder::MaxChi2_Param() const
{
   return m_Param_MaxChi2.value();
}
inline DABoolean EventVertexHolder::TrackCutNorm_Param() const
{
   return m_Param_TrackCutNorm.value();
}
// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "DedxEventSkim/Template/DedxEventSkimHolder.cc"
//#endif

#endif /* EVENTVERTEXPROD_EVENTVERTEXHOLDER_H */
