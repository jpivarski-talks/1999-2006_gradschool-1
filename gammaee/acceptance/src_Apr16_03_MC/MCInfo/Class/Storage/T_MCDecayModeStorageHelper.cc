#include "Experiment/Experiment.h"
#include "MCInfo/MCParticleProperty/MCDecayMode.h"

//this is done to create a TypeTag and its name
#include "FrameAccess/instantiate_macros.h"
INSTANTIATE_ONE(MCDecayMode)
#include "StorageManagement/instantiate_one_typetag.h"

#include "StorageManagement/Template/SMStorageHelper.cc"
template class SMStorageHelper<MCDecayMode>;


