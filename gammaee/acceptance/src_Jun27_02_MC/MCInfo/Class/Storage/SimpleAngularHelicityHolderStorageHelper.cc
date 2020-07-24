// -*- C++ -*-
//
// Package:     <MCInfo>
// Module:      SimpleAngularHelicityHolderStorageHelper
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Lawrence Gibbons
// Created:     Wed May 30 11:51:02 EDT 2001
// $Id: SimpleAngularHelicityHolderStorageHelper.cc,v 1.2 2001/12/21 20:30:29 lkg Exp $
//
// Revision history
//
// $Log: SimpleAngularHelicityHolderStorageHelper.cc,v $
// Revision 1.2  2001/12/21 20:30:29  lkg
// repair instantiations to get all symbols appearing, and occuring only once within library
//
// Revision 1.1  2001/12/19 18:20:09  lkg
// add storage helpers for particle properties
//
//

#include "Experiment/Experiment.h"

// ??? not done in rich ??? #define HETEROCONTAINER_HCTYPETAGTEMPLATE_CC

// system include files
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
//#include "Experiment/report.h"
#include "MCInfo/Storage/SimpleAngularHelicityHolderStorageHelper.h"
#include "MCInfo/Storage/MCDecayModeStorageHelper.h"
#include "MCInfo/MCParticleProperty/SimpleAngularHelicity.h"

#include "STLUtility/iterator_traits_fix.h"
#include "ToolBox/TBDerefItr.h"

#include <vector>

typedef SimpleAngularHelicity* _ptr_element_ ;
typedef SimpleAngularHelicity  _val_element_ ;
#include "StorageManagement/instantiate_smptrholderhelper.h"

typedef SMPtrHolderStorageHelper<_ptr_element_,_val_element_> SimpleAngularHelicityHolderStorageHelper;
typedef SMPtrHolder<_ptr_element_,_val_element_> SimpleAngularHelicityHolder;

//this is done to create a TypeTag and its name
#include "FrameAccess/instantiate_macros.h"
INSTANTIATE_SMPTRHOLDER( SimpleAngularHelicity*, SimpleAngularHelicity )
#include "StorageManagement/instantiate_one_typetag.h"

#include "StorageManagement/SMDeliverer.h"
SM_REGISTER_VERSION_DEF(SimpleAngularHelicityHolderStorageHelper,SimpleAngularHelicityHolder)

SM_REGISTER_STORAGE(SimpleAngularHelicityHolderStorageHelper)

typedef SMPtrHolder<_ptr_element_,_val_element_> _vector_contents_;
#include "STLUtility/instantiate_vector.h"

#if defined(SUNCC)
template<>
struct iterator_traits<MCDecayModeStorageHelper::angHolder*> {
public:
     typedef MCDecayModeStorageHelper::angHolder value_type;
};
#endif
