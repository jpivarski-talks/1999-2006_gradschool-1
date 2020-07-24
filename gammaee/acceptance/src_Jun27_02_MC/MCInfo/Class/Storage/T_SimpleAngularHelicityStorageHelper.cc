#include "Experiment/Experiment.h"
#include "MCInfo/MCParticleProperty/SimpleAngularHelicity.h"

//this is done to create a TypeTag and its name
#include "FrameAccess/instantiate_macros.h"
INSTANTIATE_ONE(SimpleAngularHelicity)
#include "StorageManagement/instantiate_one_typetag.h"

#include "StorageManagement/Template/SMStorageHelper.cc"
template class SMStorageHelper<SimpleAngularHelicity>;


