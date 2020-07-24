#include "Experiment/Experiment.h"

#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

#include "MCInfo/Storage/MCParticlePropDecayModeStorageInterface.h"

#include <vector>

//this is done to create a TypeTag and its name
#include "FrameAccess/instantiate_macros.h"
INSTANTIATE_ONE(MCParticlePropDecayModeStorageInterface)
#include "StorageManagement/instantiate_one_typetag.h"

#include "StorageManagement/Template/SMStorageHelper.cc"
template class SMStorageHelper<MCParticlePropDecayModeStorageInterface>;

typedef MCParticlePropDecayModeStorageInterface* _vector_contents_;
#include "STLUtility/instantiate_vector.h"
