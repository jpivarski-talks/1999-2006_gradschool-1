#!/usr/local/bin/perl

foreach $file (

"MCInfo/MCTypes.h",
"MCInfo/MCDecayFileParser/AngularHelicityCommand.h",
"MCInfo/MCDecayFileParser/CParityCommand.h",
"MCInfo/MCDecayFileParser/ChannelCommand.h",
"MCInfo/MCDecayFileParser/CommandParser.h",
"MCInfo/MCDecayFileParser/DecayCommand.h",
"MCInfo/MCDecayFileParser/GeantCommand.h",
"MCInfo/MCDecayFileParser/HelicityCommand.h",
"MCInfo/MCDecayFileParser/MCDecayFileParser.h",
"MCInfo/MCDecayFileParser/MixingCommand.h",
"MCInfo/MCDecayFileParser/PDGCommand.h",
"MCInfo/MCDecayFileParser/ParityCommand.h",
"MCInfo/MCDecayFileParser/ParticleCommand.h",
"MCInfo/MCDecayFileParser/QQBarCommand.h",
"MCInfo/MCDecayFileParser/RedefineCommand.h",
"MCInfo/MCDecayFileParser/VersionCommand.h",
"MCInfo/MCDecayTree/MCDecayTree.h",
"MCInfo/MCDecayTree/MCDecayTreeItr.h",
"MCInfo/MCDecayTree/MCIdManager.h",
"MCInfo/MCDecayTree/MCIdMngrPtr.h",
"MCInfo/MCDecayTree/MCListItr.h",
"MCInfo/MCDecayTree/MCNoParticleExistsException.h",
"MCInfo/MCDecayTree/MCNoVertexExistsException.h",
"MCInfo/MCDecayTree/MCParticle.h",
"MCInfo/MCDecayTree/MCStablePartItr.h",
"MCInfo/MCDecayTree/MCTreeNode.h",
"MCInfo/MCDecayTree/MCVertex.h",
"MCInfo/MCDecayTree/interaction_types.h",
"MCInfo/MCParticleProperty/HelicityConfig.h",
"MCInfo/MCParticleProperty/MCDecayMode.h",
"MCInfo/MCParticleProperty/MCNoParticlePropertyExistsException.h",
"MCInfo/MCParticleProperty/MCPPStoreItr.h",
"MCInfo/MCParticleProperty/MCParticleProperty.h",
"MCInfo/MCParticleProperty/MCParticlePropertyStore.h",
"MCInfo/MCParticleProperty/MCQQBar.h",
"MCInfo/MCParticleProperty/PDGScheme.h",
"MCInfo/MCParticleProperty/SimpleAngularHelicity.h",
"MCInfo/MCParticleProperty/SimpleHelicity.h",
"MCInfo/MCParticleProperty/pdgNum.h",
"MCInfo/Storage/DeliverDummyMCDT.h",
"MCInfo/Storage/DeliverDummyMCPPS.h",
"MCInfo/Storage/MCDecayModeStorageHelper.h",
"MCInfo/Storage/MCDecayTreeStorageHelper.h",
"MCInfo/Storage/MCParticlePropDecayModeStorageInterface.h",
"MCInfo/Storage/MCParticlePropDecayModeStorageInterfaceStorageHelper.h",
"MCInfo/Storage/MCParticlePropertyStorageHelper.h",
"MCInfo/Storage/MCParticlePropertyStoreStorageHelper.h",
"MCInfo/Storage/MCParticleStorageHelper.h",
"MCInfo/Storage/MCVertexStorageHelper.h",
"MCInfo/Storage/SimpleAngularHelicityHolderStorageHelper.h",
"MCInfo/Storage/SimpleAngularHelicityStorageHelper.h",
"MCInfo/Storage/SimpleHelicityHolderStorageHelper.h",
"MCInfo/Storage/SimpleHelicityStorageHelper.h",
"MCInfo/Utility/Formatable3Vector.h",
"MCInfo/Utility/FormatableLorentzVector.h",
"MCInfo/Utility/FormatablePoint3D.h",
"MCInfo/Utility/RCPInterface.h",
"MCInfo/Utility/RefCntPtr.h",
"MCInfo/Utility/quoteChildren.h",
"MCInfo/Utility/quoteDecay.h",

"CleoInstantiate/T_MCDecayTree.cc",
"CleoInstantiate/T_MCParticlePropertyStore.cc",
"Instantiate/T_deque_of_double.cc",
"Instantiate/T_vector_of_Double.cc",
"Instantiate/instantiate_sort_qqid.cc",
"Class/MCDecayFileParser/AngularHelicityCommand.cc",
"Class/MCDecayFileParser/CParityCommand.cc",
"Class/MCDecayFileParser/ChannelCommand.cc",
"Class/MCDecayFileParser/DecayCommand.cc",
"Class/MCDecayFileParser/GeantCommand.cc",
"Class/MCDecayFileParser/HelicityCommand.cc",
"Class/MCDecayFileParser/MCDecayFileParser.cc",
"Class/MCDecayFileParser/MixingCommand.cc",
"Class/MCDecayFileParser/PDGCommand.cc",
"Class/MCDecayFileParser/ParityCommand.cc",
"Class/MCDecayFileParser/ParticleCommand.cc",
"Class/MCDecayFileParser/QQBarCommand.cc",
"Class/MCDecayFileParser/RedefineCommand.cc",
"Class/MCDecayFileParser/VersionCommand.cc",
"Class/MCDecayTree/MCDecayTree.cc",
"Class/MCDecayTree/MCIdManager.cc",
"Class/MCDecayTree/MCIdMngrPtr.cc",
"Class/MCDecayTree/MCParticle.cc",
"Class/MCDecayTree/MCStablePartItr.cc",
"Class/MCDecayTree/MCTreeNode.cc",
"Class/MCDecayTree/MCVertex.cc",
"Class/MCParticleProperty/MCDecayMode.cc",
"Class/MCParticleProperty/MCPPStoreItr.cc",
"Class/MCParticleProperty/MCParticleProperty.cc",
"Class/MCParticleProperty/MCParticlePropertyStore.cc",
"Class/MCParticleProperty/MCQQBar.cc",
"Class/MCParticleProperty/SimpleAngularHelicity.cc",
"Class/MCParticleProperty/SimpleHelicity.cc",
"Class/Storage/DeliverDummyMCDT.cc",
"Class/Storage/DeliverDummyMCPPS.cc",
"Class/Storage/MCDecayModeStorageHelper.cc",
"Class/Storage/MCDecayTreeStorageHelper.cc",
"Class/Storage/MCParticlePropDecayModeStorageInterfaceStorageHelper.cc",
"Class/Storage/MCParticlePropertyStorageHelper.cc",
"Class/Storage/MCParticlePropertyStoreStorageHelper.cc",
"Class/Storage/MCParticleStorageHelper.cc",
"Class/Storage/MCVertexStorageHelper.cc",
"Class/Storage/SimpleAngularHelicityHolderStorageHelper.cc",
"Class/Storage/SimpleAngularHelicityStorageHelper.cc",
"Class/Storage/SimpleHelicityHolderStorageHelper.cc",
"Class/Storage/SimpleHelicityStorageHelper.cc",
"Class/Storage/T_MCDecayModeStorageHelper.cc",
"Class/Storage/T_MCParticlePropDecayModeStorageInterfaceStorageHelper.cc",
"Class/Storage/T_MCParticlePropertyStorageHelper.cc",
"Class/Storage/T_MCParticleStorageHelper.cc",
"Class/Storage/T_MCVertexStorageHelper.cc",
"Class/Storage/T_SimpleAngularHelicityStorageHelper.cc",
"Class/Storage/T_SimpleHelicityStorageHelper.cc",
"Instantiate/MCDecayFileParser/T_deque_of_vector_of_double.cc",
"Instantiate/MCDecayFileParser/T_getline_ifstream.cc",
"Instantiate/MCDecayFileParser/T_getline_istrstream.cc",
"Instantiate/MCDecayFileParser/T_map_of_string_commandparser.cc",
"Instantiate/MCDecayFileParser/T_map_string_MCDecayMode.cc",
"Instantiate/MCDecayTree/T_deque_of_MCParticle.cc",
"Instantiate/MCDecayTree/T_deque_of_pair_MCParticle_iter.cc",
"Instantiate/MCDecayTree/T_deque_of_pair_MCVertex_iter.cc",
"Instantiate/MCDecayTree/T_list_of_MCParticle.cc",
"Instantiate/MCDecayTree/T_list_of_MCVertex.cc",
"Instantiate/MCDecayTree/T_list_of_interaction.cc",
"Instantiate/MCDecayTree/instantiate_MCDecayTreeItr.cc",
"Instantiate/MCDecayTree/instantiate_MCListItr.cc",
"Instantiate/MCDecayTree/instantiate_binary_search_qqid.cc",
"Instantiate/MCDecayTree/instantiate_find_if_MCDecayTree_pIter.cc",
"Instantiate/MCDecayTree/instantiate_find_if_vIter_CheckId.cc",
"Instantiate/MCDecayTree/instantiate_find_if_vector_qqid.cc",
"Instantiate/MCDecayTree/instantiate_transform_qqid_string.cc",
"Instantiate/MCDecayTree/instantiate_transform_string_qqid.cc",
"Instantiate/MCParticleProperty/T_equal_vector_of_qqid.cc",
"Instantiate/MCParticleProperty/T_map_of_Helicity_CosThetaDep.cc",
"Instantiate/MCParticleProperty/T_map_of_Likelihood_ChildHelicities.cc",
"Instantiate/MCParticleProperty/T_map_of_Likelihood_MCDecayMode.cc",
"Instantiate/MCParticleProperty/T_map_of_pdgid_qqid.cc",
"Instantiate/MCParticleProperty/T_map_of_string_helicity.cc",
"Instantiate/MCParticleProperty/T_map_of_string_qqid.cc",
"Instantiate/MCParticleProperty/T_vector_of_HelicityConfig.cc",
"Instantiate/MCParticleProperty/T_vector_of_MCDecayMode.cc",
"Instantiate/MCParticleProperty/T_vector_of_MCParticleProperty.cc",
"Instantiate/MCParticleProperty/T_vector_of_qqid.cc",
"Instantiate/MCParticleProperty/instantiate_MCPPStoreItr.cc",
"Instantiate/MCParticleProperty/instantiate_equal_MCPPStoreItr.cc",
"Instantiate/MCParticleProperty/instantiate_equal_MCParticle_constItr.cc",
"Instantiate/MCParticleProperty/instantiate_equal_vector_double.cc",
"Instantiate/MCParticleProperty/instantiate_find_if_ChildHelicity_map.cc",
"Instantiate/MCParticleProperty/instantiate_find_if_DecayMode_map.cc",
"Instantiate/MCParticleProperty/instantiate_find_if_ModeCheck.cc",
"Instantiate/MCParticleProperty/instantiate_find_if_ModeCheckId.cc",
"Instantiate/MCParticleProperty/instantiate_transform_conjugate.cc",
"Instantiate/MCParticleProperty/instantiate_transform_const_qqid_string.cc",
"Instantiate/MCParticleProperty/instantiate_transform_const_string_qqid.cc",
"Instantiate/MCParticleProperty/instantiate_transform_qqid_string.cc",
"Instantiate/MCParticleProperty/instantiate_transform_string_qqid.cc",
"MCInfo/MCDecayTree/Template/MCDecayTreeItr.cc",
"MCInfo/MCDecayTree/Template/MCListItr.cc",
"MCInfo/Utility/Template/RefCntPtr.cc",

	    ) {
    print "======================== $file\n";
    system("diff ../src_Jun27_02_MC/MCInfo/$file /nfs/cleo3/Offline/rel/Jun27_02_MC/src/MCInfo/$file");
    print "\n";
}

# sol567% perl compare.pl
# ======================== MCInfo/MCTypes.h

# ======================== MCInfo/MCDecayFileParser/AngularHelicityCommand.h
# 15c15
# < // $Id: AngularHelicityCommand.h,v 1.2 2002/11/21 21:11:57 cleo3 Exp $
# ---
# > // $Id: AngularHelicityCommand.h,v 1.1 1999/06/22 21:29:46 lkg Exp $
# 20,22d19
# < // Revision 1.2  2002/11/21 21:11:57  cleo3
# < // changed fstream.h to C++Std/fstream.h
# < //
# 31c28
# < #include "C++Std/fstream.h"
# ---
# > #include <fstream.h>

# ======================== MCInfo/MCDecayFileParser/CParityCommand.h
# 15c15
# < // $Id: CParityCommand.h,v 1.2 2002/11/21 21:11:57 cleo3 Exp $
# ---
# > // $Id: CParityCommand.h,v 1.1 1999/06/22 21:29:47 lkg Exp $
# 20,22d19
# < // Revision 1.2  2002/11/21 21:11:57  cleo3
# < // changed fstream.h to C++Std/fstream.h
# < //
# 31c28
# < #include "C++Std/fstream.h"
# ---
# > #include <fstream.h>

# ======================== MCInfo/MCDecayFileParser/ChannelCommand.h
# 15c15
# < // $Id: ChannelCommand.h,v 1.2 2002/11/21 21:11:58 cleo3 Exp $
# ---
# > // $Id: ChannelCommand.h,v 1.1 1999/06/22 21:29:48 lkg Exp $
# 20,22d19
# < // Revision 1.2  2002/11/21 21:11:58  cleo3
# < // changed fstream.h to C++Std/fstream.h
# < //
# 31c28
# < #include "C++Std/fstream.h"
# ---
# > #include <fstream.h>

# ======================== MCInfo/MCDecayFileParser/CommandParser.h

# ======================== MCInfo/MCDecayFileParser/DecayCommand.h
# 15c15
# < // $Id: DecayCommand.h,v 1.2 2002/11/21 21:11:58 cleo3 Exp $
# ---
# > // $Id: DecayCommand.h,v 1.1 1999/06/22 21:29:49 lkg Exp $
# 20,22d19
# < // Revision 1.2  2002/11/21 21:11:58  cleo3
# < // changed fstream.h to C++Std/fstream.h
# < //
# 31c28
# < #include "C++Std/fstream.h"
# ---
# > #include <fstream.h>

# ======================== MCInfo/MCDecayFileParser/GeantCommand.h
# 15c15
# < // $Id: GeantCommand.h,v 1.2 2002/11/21 21:12:00 cleo3 Exp $
# ---
# > // $Id: GeantCommand.h,v 1.1 1999/10/19 21:24:48 lkg Exp $
# 20,22d19
# < // Revision 1.2  2002/11/21 21:12:00  cleo3
# < // changed fstream.h to C++Std/fstream.h
# < //
# 34c31
# < #include "C++Std/fstream.h"
# ---
# > #include <fstream.h>

# ======================== MCInfo/MCDecayFileParser/HelicityCommand.h
# 15c15
# < // $Id: HelicityCommand.h,v 1.2 2002/11/21 21:12:00 cleo3 Exp $
# ---
# > // $Id: HelicityCommand.h,v 1.1 1999/06/22 21:29:49 lkg Exp $
# 20,22d19
# < // Revision 1.2  2002/11/21 21:12:00  cleo3
# < // changed fstream.h to C++Std/fstream.h
# < //
# 31c28
# < #include "C++Std/fstream.h"
# ---
# > #include <fstream.h>

# ======================== MCInfo/MCDecayFileParser/MCDecayFileParser.h
# 47c47
# < // $Id: MCDecayFileParser.h,v 1.2 2002/11/21 21:12:00 cleo3 Exp $
# ---
# > // $Id: MCDecayFileParser.h,v 1.1 1999/06/22 21:29:50 lkg Exp $
# 52,54d51
# < // Revision 1.2  2002/11/21 21:12:00  cleo3
# < // changed fstream.h to C++Std/fstream.h
# < //
# 66c63
# < #include "C++Std/fstream.h"
# ---
# > #include <fstream.h>

# ======================== MCInfo/MCDecayFileParser/MixingCommand.h
# 15c15
# < // $Id: MixingCommand.h,v 1.2 2002/11/21 21:12:01 cleo3 Exp $
# ---
# > // $Id: MixingCommand.h,v 1.1 1999/10/19 21:24:49 lkg Exp $
# 20,22d19
# < // Revision 1.2  2002/11/21 21:12:01  cleo3
# < // changed fstream.h to C++Std/fstream.h
# < //
# 29c26
# < #include "C++Std/fstream.h"
# ---
# > #include <fstream.h>

# ======================== MCInfo/MCDecayFileParser/PDGCommand.h
# 15c15
# < // $Id: PDGCommand.h,v 1.2 2002/11/21 21:12:01 cleo3 Exp $
# ---
# > // $Id: PDGCommand.h,v 1.1 1999/06/22 21:29:50 lkg Exp $
# 20,22d19
# < // Revision 1.2  2002/11/21 21:12:01  cleo3
# < // changed fstream.h to C++Std/fstream.h
# < //
# 31c28
# < #include "C++Std/fstream.h"
# ---
# > #include <fstream.h>

# ======================== MCInfo/MCDecayFileParser/ParityCommand.h
# 15c15
# < // $Id: ParityCommand.h,v 1.2 2002/11/21 21:12:01 cleo3 Exp $
# ---
# > // $Id: ParityCommand.h,v 1.1 1999/06/22 21:29:51 lkg Exp $
# 20,22d19
# < // Revision 1.2  2002/11/21 21:12:01  cleo3
# < // changed fstream.h to C++Std/fstream.h
# < //
# 31c28
# < #include "C++Std/fstream.h"
# ---
# > #include <fstream.h>

# ======================== MCInfo/MCDecayFileParser/ParticleCommand.h
# 15c15
# < // $Id: ParticleCommand.h,v 1.2 2002/11/21 21:12:02 cleo3 Exp $
# ---
# > // $Id: ParticleCommand.h,v 1.1 1999/06/22 21:29:52 lkg Exp $
# 20,22d19
# < // Revision 1.2  2002/11/21 21:12:02  cleo3
# < // changed fstream.h to C++Std/fstream.h
# < //
# 31c28
# < #include "C++Std/fstream.h"
# ---
# > #include <fstream.h>

# ======================== MCInfo/MCDecayFileParser/QQBarCommand.h
# 15c15
# < // $Id: QQBarCommand.h,v 1.2 2002/11/21 21:12:02 cleo3 Exp $
# ---
# > // $Id: QQBarCommand.h,v 1.1 1999/06/22 21:29:52 lkg Exp $
# 20,22d19
# < // Revision 1.2  2002/11/21 21:12:02  cleo3
# < // changed fstream.h to C++Std/fstream.h
# < //
# 29c26
# < #include "C++Std/fstream.h"
# ---
# > #include <fstream.h>

# ======================== MCInfo/MCDecayFileParser/RedefineCommand.h
# 15c15
# < // $Id: RedefineCommand.h,v 1.2 2002/11/21 21:12:02 cleo3 Exp $
# ---
# > // $Id: RedefineCommand.h,v 1.1 2001/10/25 18:56:56 lkg Exp $
# 20,22d19
# < // Revision 1.2  2002/11/21 21:12:02  cleo3
# < // changed fstream.h to C++Std/fstream.h
# < //
# 34c31
# < #include "C++Std/fstream.h"
# ---
# > #include <fstream.h>

# ======================== MCInfo/MCDecayFileParser/VersionCommand.h
# 15c15
# < // $Id: VersionCommand.h,v 1.2 2002/11/21 21:12:03 cleo3 Exp $
# ---
# > // $Id: VersionCommand.h,v 1.1 1999/06/22 21:29:54 lkg Exp $
# 20,22d19
# < // Revision 1.2  2002/11/21 21:12:03  cleo3
# < // changed fstream.h to C++Std/fstream.h
# < //
# 31c28
# < #include "C++Std/fstream.h"
# ---
# > #include <fstream.h>

# ======================== MCInfo/MCDecayTree/MCDecayTree.h

# ======================== MCInfo/MCDecayTree/MCDecayTreeItr.h

# ======================== MCInfo/MCDecayTree/MCIdManager.h

# ======================== MCInfo/MCDecayTree/MCIdMngrPtr.h

# ======================== MCInfo/MCDecayTree/MCListItr.h
# 22c22
# < // $Id: MCListItr.h,v 1.7 2002/12/06 16:44:59 cleo3 Exp $
# ---
# > // $Id: MCListItr.h,v 1.6 2001/09/10 20:04:29 cleo3 Exp $
# 27,29d26
# < // Revision 1.7  2002/12/06 16:44:59  cleo3
# < // added typename
# < //
# 73c70
# <       typedef  typename iterator_traits<T_iter>::iterator_category iterator_category;
# ---
# >       typedef  iterator_traits<T_iter>::iterator_category iterator_category;

# ======================== MCInfo/MCDecayTree/MCNoParticleExistsException.h
# 18c18
# < // $Id: MCNoParticleExistsException.h,v 1.2 2002/12/06 16:51:54 cleo3 Exp $
# ---
# > // $Id: MCNoParticleExistsException.h,v 1.1 2002/01/20 19:26:53 lkg Exp $
# 23,25d22
# < // Revision 1.2  2002/12/06 16:51:54  cleo3
# < // deal with strstream/stringstream
# < //
# 33,37d29
# < #if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)           
# < #include <strstream.h>
# < #else
# < #include <sstream>
# < #endif
# 67d58
# < #if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)           
# 72,76d62
# < #else
# <           stringstream oStream1;
# <           oStream1 << m_treeId <<endl;
# <           string treeIdString( oStream1.str() );
# < #endif

# ======================== MCInfo/MCDecayTree/MCNoVertexExistsException.h
# 18c18
# < // $Id: MCNoVertexExistsException.h,v 1.2 2002/12/06 16:51:54 cleo3 Exp $
# ---
# > // $Id: MCNoVertexExistsException.h,v 1.1 2002/01/20 19:26:54 lkg Exp $
# 23,25d22
# < // Revision 1.2  2002/12/06 16:51:54  cleo3
# < // deal with strstream/stringstream
# < //
# 33,37d29
# < #if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)           
# < #include <strstream.h>
# < #else
# < #include <sstream>
# < #endif
# 67d58
# < #if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)           
# 72,76d62
# < #else
# <           stringstream oStream1;
# <           oStream1 << m_treeId <<endl;
# <           string treeIdString( oStream1.str() );
# < #endif

# ======================== MCInfo/MCDecayTree/MCParticle.h
# 17c17
# < // $Id: MCParticle.h,v 1.9 2003/08/01 21:57:53 bkh Exp $
# ---
# > // $Id: MCParticle.h,v 1.7 2002/05/03 18:59:02 lkg Exp $
# 22,27d21
# < // Revision 1.9  2003/08/01 21:57:53  bkh
# < // Fix MCParticle::operator=
# < //
# < // Revision 1.8  2003/02/03 20:24:50  bkh
# < // Add new unwinding function
# < //
# 203,211d196
# <       // go up decay tree from this particle 
# <       // until find a particle which is inside
# <       // a given cylininder defined by a fabs(radius) and fabs(z).
# <       // negative values of either radius or z (default) means go back to
# <       // a particle produced directly in the e+e- interaction
# <       // Result may be this particle, or 0.
# <       const MCParticle* unwindToInsideRZ( const double aRadius = -1 ,
# <                                         const double aZ      = -1  ) const ;
# < 
# 277,278d261
# < 
# <       void deleteMyVertexList() ;

# ======================== MCInfo/MCDecayTree/MCStablePartItr.h

# ======================== MCInfo/MCDecayTree/MCTreeNode.h
# 15c15
# < // $Id: MCTreeNode.h,v 1.6 2002/09/20 17:51:48 bkh Exp $
# ---
# > // $Id: MCTreeNode.h,v 1.4 2002/02/05 03:33:24 lkg Exp $
# 20,22d19
# < // Revision 1.6  2002/09/20 17:51:48  bkh
# < // Undo previous change -- not necessary
# < //

# ======================== MCInfo/MCDecayTree/MCVertex.h

# ======================== MCInfo/MCDecayTree/interaction_types.h

# ======================== MCInfo/MCParticleProperty/HelicityConfig.h

# ======================== MCInfo/MCParticleProperty/MCDecayMode.h

# ======================== MCInfo/MCParticleProperty/MCNoParticlePropertyExistsException.h
# 18c18
# < // $Id: MCNoParticlePropertyExistsException.h,v 1.3 2003/01/16 21:07:49 cdj Exp $
# ---
# > // $Id: MCNoParticlePropertyExistsException.h,v 1.1 2002/01/20 19:34:52 lkg Exp $
# 23,28d22
# < // Revision 1.3  2003/01/16 21:07:49  cdj
# < // use stringstream if available
# < //
# < // Revision 1.2  2003/01/12 19:22:15  cdj
# < // missed some strstream changes
# < //
# 39,43d32
# < #if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
# < #include <strstream.h>
# < #else
# < #include <sstream>
# < #endif
# 70d58
# < #if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)           
# 73,75d60
# < #else
# <           ostringstream oStream1;
# < #endif
# 77c62
# <             string propertyIdString( oStream1.str() );
# ---
# >             string propertyIdString( buffer );
# 114,131d98
# < 
# < 
# < 
# < 
# < 
# < 
# < 
# < 
# < 
# < 
# < 
# < 
# < 
# < 
# < 
# < 
# < 
# < 

# ======================== MCInfo/MCParticleProperty/MCPPStoreItr.h

# ======================== MCInfo/MCParticleProperty/MCParticleProperty.h

# ======================== MCInfo/MCParticleProperty/MCParticlePropertyStore.h

# ======================== MCInfo/MCParticleProperty/MCQQBar.h

# ======================== MCInfo/MCParticleProperty/PDGScheme.h
# 15,22c15,22
# < static const int kDown    = 1;
# < static const int kUp      = 2;
# < static const int kStrange = 3;
# < static const int kCharm   = 4;
# < static const int kBottom  = 5;
# < static const int kTop     = 6;
# < static const int kBprime  = 7;
# < static const int kTprime  = 8;
# ---
# > static const kDown    = 1;
# > static const kUp      = 2;
# > static const kStrange = 3;
# > static const kCharm   = 4;
# > static const kBottom  = 5;
# > static const kTop     = 6;
# > static const kBprime  = 7;
# > static const kTprime  = 8;

# ======================== MCInfo/MCParticleProperty/SimpleAngularHelicity.h

# ======================== MCInfo/MCParticleProperty/SimpleHelicity.h

# ======================== MCInfo/MCParticleProperty/pdgNum.h
# diff: /nfs/cleo3/Offline/rel/Jun27_02_MC/src/MCInfo/MCInfo/MCParticleProperty/pdgNum.h: No such file or directory

# ======================== MCInfo/Storage/DeliverDummyMCDT.h

# ======================== MCInfo/Storage/DeliverDummyMCPPS.h

# ======================== MCInfo/Storage/MCDecayModeStorageHelper.h

# ======================== MCInfo/Storage/MCDecayTreeStorageHelper.h

# ======================== MCInfo/Storage/MCParticlePropDecayModeStorageInterface.h

# ======================== MCInfo/Storage/MCParticlePropDecayModeStorageInterfaceStorageHelper.h

# ======================== MCInfo/Storage/MCParticlePropertyStorageHelper.h
# 15c15
# < // $Id: MCParticlePropertyStorageHelper.h,v 1.2 2003/10/16 17:22:12 ryd Exp $
# ---
# > // $Id: MCParticlePropertyStorageHelper.h,v 1.1 2001/12/19 18:20:22 lkg Exp $
# 20,22d19
# < // Revision 1.2  2003/10/16 17:22:12  ryd
# < // Change storage of charge such that fractional (1/3) charges can be stored.
# < //
# 65d61
# <       MCParticleProperty* deliverV2( SMSourceStream& iSource );

# ======================== MCInfo/Storage/MCParticlePropertyStoreStorageHelper.h

# ======================== MCInfo/Storage/MCParticleStorageHelper.h

# ======================== MCInfo/Storage/MCVertexStorageHelper.h

# ======================== MCInfo/Storage/SimpleAngularHelicityHolderStorageHelper.h

# ======================== MCInfo/Storage/SimpleAngularHelicityStorageHelper.h

# ======================== MCInfo/Storage/SimpleHelicityHolderStorageHelper.h

# ======================== MCInfo/Storage/SimpleHelicityStorageHelper.h

# ======================== MCInfo/Utility/Formatable3Vector.h
# diff: /nfs/cleo3/Offline/rel/Jun27_02_MC/src/MCInfo/MCInfo/Utility/Formatable3Vector.h: No such file or directory

# ======================== MCInfo/Utility/FormatableLorentzVector.h
# diff: /nfs/cleo3/Offline/rel/Jun27_02_MC/src/MCInfo/MCInfo/Utility/FormatableLorentzVector.h: No such file or directory

# ======================== MCInfo/Utility/FormatablePoint3D.h
# diff: /nfs/cleo3/Offline/rel/Jun27_02_MC/src/MCInfo/MCInfo/Utility/FormatablePoint3D.h: No such file or directory

# ======================== MCInfo/Utility/RCPInterface.h

# ======================== MCInfo/Utility/RefCntPtr.h

# ======================== MCInfo/Utility/quoteChildren.h

# ======================== MCInfo/Utility/quoteDecay.h

# ======================== CleoInstantiate/T_MCDecayTree.cc

# ======================== CleoInstantiate/T_MCParticlePropertyStore.cc

# ======================== Instantiate/T_deque_of_double.cc

# ======================== Instantiate/T_vector_of_Double.cc

# ======================== Instantiate/instantiate_sort_qqid.cc

# ======================== Class/MCDecayFileParser/AngularHelicityCommand.cc
# 13c13
# < // $Id: AngularHelicityCommand.cc,v 1.2 2003/01/16 21:07:40 cdj Exp $
# ---
# > // $Id: AngularHelicityCommand.cc,v 1.1 1999/06/22 21:28:39 lkg Exp $
# 18,20d17
# < // Revision 1.2  2003/01/16 21:07:40  cdj
# < // use stringstream if available
# < //
# 34d30
# < #if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
# 36,38d31
# < #else
# < #include<sstream>
# < #endif
# 51d43
# < #if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
# 53,55d44
# < #else
# < #include<sstream>
# < #endif
# 57d45
# < 
# 97d84
# < #if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
# 100,102d86
# < #else
# <    istringstream propStream( parameterList );
# < #endif

# ======================== Class/MCDecayFileParser/CParityCommand.cc
# 13c13
# < // $Id: CParityCommand.cc,v 1.3 2003/01/16 21:07:41 cdj Exp $
# ---
# > // $Id: CParityCommand.cc,v 1.2 2001/12/19 18:10:50 lkg Exp $
# 18,20d17
# < // Revision 1.3  2003/01/16 21:07:41  cdj
# < // use stringstream if available
# < //
# 37d33
# <  #if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
# 39,41d34
# < #else
# < #include <sstream>
# < #endif
# 52d44
# <  #if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
# 54,56d45
# < #else
# < #include <sstream>
# < #endif
# 93d81
# <  #if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
# 96,98d83
# < #else
# <    istringstream propStream( theCommand.parameterList );
# < #endif

# ======================== Class/MCDecayFileParser/ChannelCommand.cc
# 13c13
# < // $Id: ChannelCommand.cc,v 1.2 2003/01/16 21:07:41 cdj Exp $
# ---
# > // $Id: ChannelCommand.cc,v 1.1 1999/06/22 21:28:40 lkg Exp $
# 18,20d17
# < // Revision 1.2  2003/01/16 21:07:41  cdj
# < // use stringstream if available
# < //
# 35d31
# < #if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
# 37,39d32
# < #else
# < #include <sstream>
# < #endif
# 57d49
# < #if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
# 59,61d50
# < #else
# < #include <sstream>
# < #endif
# 100d88
# < #if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
# 103,105d90
# < #else
# <    istringstream propStream( parameterList );
# < #endif

# ======================== Class/MCDecayFileParser/DecayCommand.cc
# 13c13
# < // $Id: DecayCommand.cc,v 1.4 2003/01/16 21:07:41 cdj Exp $
# ---
# > // $Id: DecayCommand.cc,v 1.3 2001/12/19 18:10:50 lkg Exp $
# 18,20d17
# < // Revision 1.4  2003/01/16 21:07:41  cdj
# < // use stringstream if available
# < //
# 43d39
# < #if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
# 45,47d40
# < #else
# < #include <sstream>
# < #endif
# 61d53
# < #if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
# 63,65d54
# < #else
# < #include <sstream>
# < #endif
# 98d86
# < #if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
# 101,103d88
# < #else
# <    istringstream propStream( theCommand.parameterList );
# < #endif

# ======================== Class/MCDecayFileParser/GeantCommand.cc
# 13c13
# < // $Id: GeantCommand.cc,v 1.3 2003/01/16 21:07:41 cdj Exp $
# ---
# > // $Id: GeantCommand.cc,v 1.2 2001/12/19 18:10:50 lkg Exp $
# 18,20d17
# < // Revision 1.3  2003/01/16 21:07:41  cdj
# < // use stringstream if available
# < //
# 40d36
# < #if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
# 42,44d37
# < #else
# < #include <sstream>
# < #endif
# 55d47
# < #if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
# 57,59d48
# < #else
# < #include <sstream>
# < #endif
# 96d84
# < #if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
# 99,101c87
# < #else
# <    istringstream propStream( theCommand.parameterList );
# < #endif
# ---
# > 

# ======================== Class/MCDecayFileParser/HelicityCommand.cc
# 13c13
# < // $Id: HelicityCommand.cc,v 1.2 2003/01/16 21:07:42 cdj Exp $
# ---
# > // $Id: HelicityCommand.cc,v 1.1 1999/06/22 21:28:41 lkg Exp $
# 18,20d17
# < // Revision 1.2  2003/01/16 21:07:42  cdj
# < // use stringstream if available
# < //
# 34d30
# < #if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
# 36,38d31
# < #else
# < #include <sstream>
# < #endif
# 51d43
# < #if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
# 53,55d44
# < #else
# < #include <sstream>
# < #endif
# 99d87
# < #if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
# 102,104d89
# < #else
# <    istringstream propStream( parameterList );
# < #endif

# ======================== Class/MCDecayFileParser/MCDecayFileParser.cc
# 13c13
# < // $Id: MCDecayFileParser.cc,v 1.7 2003/01/12 19:22:11 cdj Exp $
# ---
# > // $Id: MCDecayFileParser.cc,v 1.4 2001/10/25 18:56:51 lkg Exp $
# 18,26d17
# < // Revision 1.7  2003/01/12 19:22:11  cdj
# < // missed some strstream changes
# < //
# < // Revision 1.6  2002/12/06 16:51:54  cleo3
# < // deal with strstream/stringstream
# < //
# < // Revision 1.5  2002/06/03 20:30:54  cleo3
# < // replaced cpp switch NO_GETLINE_WITH_STRING_BUG to NO_GETLINE_ISTREAM_STRING_BUG
# < //
# 43a35,37
# > #if defined(SUNCC)
# > #define NO_GETLINE_WITH_STRING_BUG
# > #endif
# 53,58d46
# < #if !defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)          
# < #include <sstream>
# < #else
# < #include <strstream.h>
# < #endif
# < 
# 267c255
# < #if !defined(NO_GETLINE_ISTREAM_STRING_BUG)
# ---
# > #if !defined(NO_GETLINE_WITH_STRING_BUG)
# 290d277
# < #if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)           
# 292,294c279
# < #else
# <        istringstream lineStream( nextLine );
# < #endif
# ---
# >        
# 299c284
# < #if !defined(NO_GETLINE_ISTREAM_STRING_BUG)
# ---
# > #if !defined(NO_GETLINE_WITH_STRING_BUG)

# ======================== Class/MCDecayFileParser/MixingCommand.cc
# 13c13
# < // $Id: MixingCommand.cc,v 1.3 2003/01/16 21:07:42 cdj Exp $
# ---
# > // $Id: MixingCommand.cc,v 1.2 2001/12/19 18:10:50 lkg Exp $
# 18,20d17
# < // Revision 1.3  2003/01/16 21:07:42  cdj
# < // use stringstream if available
# < //
# 40d36
# < #if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
# 42,44d37
# < #else
# < #include <sstream>
# < #endif
# 55d47
# < #if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
# 57,59d48
# < #else
# < #include <sstream>
# < #endif
# 96d84
# < #if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
# 99,101c87
# < #else
# <    istringstream propStream( theCommand.parameterList ); 
# < #endif
# ---
# > 

# ======================== Class/MCDecayFileParser/PDGCommand.cc
# 13c13
# < // $Id: PDGCommand.cc,v 1.5 2003/10/08 16:36:08 ryd Exp $
# ---
# > // $Id: PDGCommand.cc,v 1.2 2001/12/19 18:10:51 lkg Exp $
# 18,26d17
# < // Revision 1.5  2003/10/08 16:36:08  ryd
# < // Removed debug printout that I should not have left
# < //
# < // Revision 1.4  2003/10/08 03:02:09  ryd
# < // Fix such that the map from pdg id to qq id is updated in MCParticlePropertyStore when the pdg id is read from the decay file
# < //
# < // Revision 1.3  2003/01/16 21:07:42  cdj
# < // use stringstream if available
# < //
# 43d33
# < #if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
# 45,47d34
# < #else
# < #include <sstream>
# < #endif
# 58d44
# < #if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
# 60,62d45
# < #else
# < #include <sstream>
# < #endif
# 99d81
# < #if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
# 102,104d83
# < #else
# <    istringstream propStream( theCommand.parameterList );
# < #endif
# 119c98
# <    MCParticleProperty propertyToUpdate = theStore.getUsingName( theName );
# ---
# >    MCParticleProperty& propertyToUpdate = theStore.getModifiableUsingName( theName );
# 121,122c100
# <    // set the PDG ID for the property and replace it in order to have
# <    // the MCParticlePropertyStore rebuild the maps.
# ---
# >    // set the PDG ID for the property
# 124,126d101
# <    theStore.replaceProperty(propertyToUpdate);
# <    
# < 

# ======================== Class/MCDecayFileParser/ParityCommand.cc
# 13c13
# < // $Id: ParityCommand.cc,v 1.3 2003/01/16 21:07:43 cdj Exp $
# ---
# > // $Id: ParityCommand.cc,v 1.2 2001/12/19 18:10:51 lkg Exp $
# 18,20d17
# < // Revision 1.3  2003/01/16 21:07:43  cdj
# < // use stringstream if available
# < //
# 37d33
# < #if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
# 39,41d34
# < #else
# < #include <sstream>
# < #endif
# 52d44
# < #if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
# 54,56d45
# < #else
# < #include <sstream>
# < #endif
# 93d81
# < #if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
# 96,98d83
# < #else
# <    istringstream propStream( theCommand.parameterList );
# < #endif

# ======================== Class/MCDecayFileParser/ParticleCommand.cc
# 13c13
# < // $Id: ParticleCommand.cc,v 1.2 2003/01/16 21:07:43 cdj Exp $
# ---
# > // $Id: ParticleCommand.cc,v 1.1 1999/06/22 21:28:44 lkg Exp $
# 18,20d17
# < // Revision 1.2  2003/01/16 21:07:43  cdj
# < // use stringstream if available
# < //
# 34d30
# < #if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
# 36,38d31
# < #else
# < #include <sstream>
# < #endif
# 50d42
# < #if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
# 52,54d43
# < #else
# < #include <sstream>
# < #endif
# 105d93
# < #if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
# 107a96
# > 
# 110,113d98
# < #else
# <    istringstream countStream( parameterList );
# < #endif
# < 
# 148d132
# < #if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
# 150,152d133
# < #else
# <    istringstream propStream( parameterList );
# < #endif

# ======================== Class/MCDecayFileParser/QQBarCommand.cc
# 13c13
# < // $Id: QQBarCommand.cc,v 1.2 2003/01/16 21:07:44 cdj Exp $
# ---
# > // $Id: QQBarCommand.cc,v 1.1 1999/06/22 21:28:44 lkg Exp $
# 18,20d17
# < // Revision 1.2  2003/01/16 21:07:44  cdj
# < // use stringstream if available
# < //
# 34d30
# < #if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
# 36,38d31
# < #else
# < #include <sstream>
# < #endif
# 51d43
# < #if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
# 53,55d44
# < #else
# < #include <sstream>
# < #endif
# 95d83
# < #if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
# 98,100d85
# < #else
# <    istringstream propStream( theCommand.parameterList );
# < #endif

# ======================== Class/MCDecayFileParser/RedefineCommand.cc
# 17c17
# < // $Id: RedefineCommand.cc,v 1.4 2003/01/16 21:07:44 cdj Exp $
# ---
# > // $Id: RedefineCommand.cc,v 1.3 2001/12/19 18:10:51 lkg Exp $
# 22,24d21
# < // Revision 1.4  2003/01/16 21:07:44  cdj
# < // use stringstream if available
# < //
# 47d43
# < #if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
# 49,51d44
# < #else
# < #include <sstream>
# < #endif
# 63d55
# < #if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
# 65,67d56
# < #else
# < #include <sstream>
# < #endif
# 114d102
# < #if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
# 116a105
# > 
# 119,122d107
# < #else
# <    istringstream countStream( parameterList );
# < #endif
# < 
# 157d141
# < #if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
# 159,161d142
# < #else
# <    istringstream propStream( parameterList );
# < #endif

# ======================== Class/MCDecayFileParser/VersionCommand.cc
# 13c13
# < // $Id: VersionCommand.cc,v 1.2 2003/01/16 21:07:44 cdj Exp $
# ---
# > // $Id: VersionCommand.cc,v 1.1 1999/06/22 21:28:45 lkg Exp $
# 18,20d17
# < // Revision 1.2  2003/01/16 21:07:44  cdj
# < // use stringstream if available
# < //
# 34d30
# < #if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
# 36,38d31
# < #else
# < #include <sstream>
# < #endif
# 49d41
# < #if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
# 51,53d42
# < #else
# < #include <sstream>
# < #endif
# 90d78
# < #if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
# 93,95d80
# < #else
# <    istringstream propStream( theCommand.parameterList );
# < #endif

# ======================== Class/MCDecayTree/MCDecayTree.cc
# 13c13
# < // $Id: MCDecayTree.cc,v 1.11 2003/05/02 14:32:02 lkg Exp $
# ---
# > // $Id: MCDecayTree.cc,v 1.9 2002/05/03 19:44:35 lkg Exp $
# 18,27d17
# < // Revision 1.11  2003/05/02 14:32:02  lkg
# < // non-const versions of getVertexPtr and getParticlePtr modified.  They
# < // were still defined via the non-const version of getVertex and getParticle
# < // which return  references, but throw exceptions if pointer is zero.
# < // Now defined by casting away the const in the const versions w/ same
# < // names.
# < //
# < // Revision 1.10  2002/08/16 15:17:37  cleo3
# < // replaced iostream.h with C++/iostream.h
# < //
# 76c66
# < //#include "C++Std/iostream.h"
# ---
# > //#include <iostream.h>
# 103,104c93,94
# < static const char* const kIdString  = "$Id: MCDecayTree.cc,v 1.11 2003/05/02 14:32:02 lkg Exp $";
# < static const char* const kTagString = "$Name: v03_11_02 $";
# ---
# > static const char* const kIdString  = "$Id: MCDecayTree.cc,v 1.9 2002/05/03 19:44:35 lkg Exp $";
# > static const char* const kTagString = "$Name: v03_02_02 $";
# 337,338c327
# <    const MCDecayTree* treeCopy = this;
# <    return const_cast<MCParticle*>( treeCopy->getParticlePtr( treeId ) );
# ---
# >    return &getParticle( treeId );
# 351,352c340
# <    const MCDecayTree* treeCopy = this;
# <    return const_cast<MCVertex*>( treeCopy->getVertexPtr( treeId ) );
# ---
# >    return &getVertex( treeId );

# ======================== Class/MCDecayTree/MCIdManager.cc
# 51c51
# < static const char* const kTagString = "$Name: v03_11_02 $";
# ---
# > static const char* const kTagString = "$Name: v03_02_02 $";

# ======================== Class/MCDecayTree/MCIdMngrPtr.cc
# 47c47
# < static const char* const kTagString = "$Name: v03_11_02 $";
# ---
# > static const char* const kTagString = "$Name: v03_02_02 $";

# ======================== Class/MCDecayTree/MCParticle.cc
# 27c27
# < // $Id: MCParticle.cc,v 1.18 2003/08/01 21:57:50 bkh Exp $
# ---
# > // $Id: MCParticle.cc,v 1.12 2002/05/03 19:45:28 lkg Exp $
# 32,49d31
# < // Revision 1.18  2003/08/01 21:57:50  bkh
# < // Fix MCParticle::operator=
# < //
# < // Revision 1.17  2003/05/19 20:23:13  lkg
# < // in dump utilities, use formattable version of vector or point
# < //
# < // Revision 1.16  2003/02/03 20:24:43  bkh
# < // Add new unwinding function
# < //
# < // Revision 1.15  2003/01/29 19:15:29  cdj
# < // get iomanip header from C++Std package
# < //
# < // Revision 1.14  2002/12/06 16:51:03  cleo3
# < // deal with new return type for stream::setf
# < //
# < // Revision 1.13  2002/08/16 15:17:38  cleo3
# < // replaced iostream.h with C++/iostream.h
# < //
# 101,102c83,84
# < #include "C++Std/iostream.h"
# < #include "C++Std/iomanip.h"
# ---
# > #include <iostream.h>
# > #include <iomanip.h>
# 111c93
# < #include "MCInfo/Utility/FormatableLorentzVector.h"
# ---
# > 
# 124,125c106,107
# < static const char* const kIdString  = "$Id: MCParticle.cc,v 1.18 2003/08/01 21:57:50 bkh Exp $";
# < static const char* const kTagString = "$Name: v03_11_02 $";
# ---
# > static const char* const kIdString  = "$Id: MCParticle.cc,v 1.12 2002/05/03 19:45:28 lkg Exp $";
# > static const char* const kTagString = "$Name: v03_02_02 $";
# 267,268c249
# < void
# < MCParticle::deleteMyVertexList()
# ---
# > MCParticle::~MCParticle()
# 272c253
# <    
# ---
# > 
# 280,284d260
# < MCParticle::~MCParticle()
# < {
# <    deleteMyVertexList() ;
# < }
# < 
# 289a266
# >       KTKinematicData::operator=( rhs )             ;
# 292,321c269,271
# <       m_pProductionVertex = 0 ; //rhs.m_pProductionVertex ;
# < 
# <       KTKinematicData::operator=( rhs ) ; // copy KTKinematicData portion
# <       setManager( *new MCIdManager( this ) ) ;   // MCTreeNode portion
# <       setId( 1 ) ;                        // for MCTreeNode portion
# < 
# <       deleteMyVertexList() ; // remove old vertices if any
# <       //
# <       // Each particle owns the vertices in its list of vertices, so we
# <       // must replicate each vertex here
# <       //
# < 
# <       // inform the ID manager that we are about to begin the cloning descent
# <       // down the tree below this particle => delay ID resetting
# <       manager().copyStarting();
# <    
# <       // clone any vertices (which makes a deep copy, so you get any
# <       // particle chains attached to the vertex as well), and add
# <       // them to the vertex list.
# <       const_vIterator done  = rhs.vEnd();
# <       for ( const_vIterator itVertex = rhs.vBegin();
# <           itVertex != done;
# <           ++itVertex ) {
# <        addVertex( itVertex->clone(this) );
# <       }
# < 
# <       // inform the ID manager that we have finished the cloning of this particle
# <       // If this is the top of the clone, the id's will get reset by the
# <       // manager
# <       manager().copyDone();
# ---
# >       m_pProductionVertex = rhs.m_pProductionVertex ;
# >       m_vertexList        = rhs.m_vertexList        ;
# >       m_deathVertex       = rhs.m_deathVertex       ;
# 404,409c354
# < #if defined(USING_IOSTREAM_H_BUG)
# <    typedef int fmtflags;
# < #else
# <    typedef ios_base::fmtflags fmtflags;
# < #endif
# <    fmtflags oldflags = theStream.setf(ios::showpoint);
# ---
# >    int oldflags = theStream.setf(ios::showpoint);
# 426,427c371
# <    FormatableLorentzVector dumpVector( lorentzMomentum() );
# <    theStream << setw(9)    << dumpVector << " ";
# ---
# >    theStream << setw(9)    << lorentzMomentum() << " ";
# 498,540d441
# < const MCParticle* 
# < MCParticle::unwindToInsideRZ( const double aRadius ,
# <                             const double aZ        ) const 
# < {
# <    const MCParticle* returnValue ( this ) ;
# < 
# < //   cout << "    ========== MC Id = " << identifier() 
# < //    << ", name = " << properties().name() << endl ;
# <    const MCVertex* vertex ( productionVertex() ) ;
# <    if( 0 != vertex )
# <    {
# <       const HepPoint3D& birthPos ( vertex->position() ) ;
# < //      cout << " ********** vertex = " << birthPos << endl ;
# < 
# <       if( 0 > aRadius ||
# <         0 > aZ         ) // unwind to initial particle
# <       {
# <        if( vertex->parent().identifier() != 1 )
# <        {
# <           returnValue = vertex->parent().unwindToInsideRZ() ;
# <        }
# <       }
# <       else
# <       {
# <        if( aRadius < birthPos.perp()            ||
# <            aZ      < fabs( birthPos.z() )             )
# <        {
# <           returnValue = vertex->parent().unwindToInsideRZ( aRadius, aZ ) ;
# < //        cout << " ################## setting returnvalue from winding for "
# < //             << returnValue->identifier() << endl ;
# <        }
# <       }
# <    }
# <    else
# <    {
# <       returnValue = 0 ;
# < //      cout << " @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ setting retval= 0 !"<<endl;
# <    }
# < //   if( returnValue == this ) cout << "________________returning this " <<
# < //                            identifier() << endl ;
# <    return returnValue ;
# < }
# < 
# 718a620,631
# > /* comment out this nicer implementation so that users can link with
# > // CLHEP properly
# > ostream& operator <<(ostream& s, const HepLorentzVector &q)
# > {
# >   int userWidth = s.width();
# >   return s << setw(0) << "(" 
# >            << setw(userWidth) << q.x() << "," 
# >          << setw(userWidth) << q.y() << ","
# >            << setw(userWidth) << q.z() << ";" 
# >          << setw(userWidth) << q.t() << ")";
# > }
# > */

# ======================== Class/MCDecayTree/MCStablePartItr.cc
# 55c55
# < static const char* const kTagString = "$Name: v03_11_02 $";
# ---
# > static const char* const kTagString = "$Name: v03_02_02 $";

# ======================== Class/MCDecayTree/MCTreeNode.cc
# 13c13
# < // $Id: MCTreeNode.cc,v 1.4 2002/09/20 17:51:41 bkh Exp $
# ---
# > // $Id: MCTreeNode.cc,v 1.2 2002/02/05 03:33:27 lkg Exp $
# 18,20d17
# < // Revision 1.4  2002/09/20 17:51:41  bkh
# < // Undo previous change -- not necessary
# < //
# 50,51c47,48
# < static const char* const kIdString  = "$Id: MCTreeNode.cc,v 1.4 2002/09/20 17:51:41 bkh Exp $";
# < static const char* const kTagString = "$Name: v03_11_02 $";
# ---
# > static const char* const kIdString  = "$Id: MCTreeNode.cc,v 1.2 2002/02/05 03:33:27 lkg Exp $";
# > static const char* const kTagString = "$Name: v03_02_02 $";

# ======================== Class/MCDecayTree/MCVertex.cc
# 25c25
# < // $Id: MCVertex.cc,v 1.21 2004/03/11 15:43:42 ryd Exp $
# ---
# > // $Id: MCVertex.cc,v 1.17 2002/05/03 19:45:28 lkg Exp $
# 30,41d29
# < // Revision 1.21  2004/03/11 15:43:42  ryd
# < // added missing endl
# < //
# < // Revision 1.20  2003/07/08 15:24:27  cdj
# < // throw exception instead of returning a null DecayMode
# < //
# < // Revision 1.19  2003/05/19 20:23:13  lkg
# < // in dump utilities, use formattable version of vector or point
# < //
# < // Revision 1.18  2003/01/29 19:15:30  cdj
# < // get iomanip header from C++Std package
# < //
# 122c110
# < #include "C++Std/iomanip.h"
# ---
# > #include <iomanip.h>
# 139d126
# < #include "MCInfo/Utility/FormatablePoint3D.h"
# 141,142d127
# < #include "DAException/DAException.h"
# < 
# 166,167c151,152
# < static const char* const kIdString  = "$Id: MCVertex.cc,v 1.21 2004/03/11 15:43:42 ryd Exp $";
# < static const char* const kTagString = "$Name: v03_11_02 $";
# ---
# > static const char* const kIdString  = "$Id: MCVertex.cc,v 1.17 2002/05/03 19:45:28 lkg Exp $";
# > static const char* const kTagString = "$Name: v03_02_02 $";
# 664,665c649
# <        << quoteDecay(m_pParentParticle->properties().name(),m_childNameList)
# <        << endl;
# ---
# >        << quoteDecay(m_pParentParticle->properties().name(),m_childNameList);
# 973d956
# <    FormatablePoint3D dumpPoint( position() );
# 975,976c958,959
# <    theStream.width(9);
# <    theStream.precision(6);
# ---
# >    theStream.width(10);
# >    theStream.precision(5);
# 978c961
# <       << dumpPoint << " ";
# ---
# >       << position() << " ";
# 1015,1016d997
# <       throw DAException("requested a DecayMode from a MCVertex which has none.\n  If you used stand alone qq to generate the MC,\n  check to see if you told suez about a user decay file you might have used.");
# <       /*
# 1021d1001
# <        */
# 1130c1110
# <       << " position" << setw(30) 
# ---
# >       << setw(34) << "position"
# 1147a1128,1138
# > /* comment out this nicer implementation so that users can link with
# > // CLHEP properly
# > ostream& operator <<(ostream& s, const Hep3Vector &q)
# > {
# >   int userWidth = s.width();
# >   return s << setw(0) << "(" 
# >            << setw(userWidth) << q.x() << "," 
# >          << setw(userWidth) << q.y() << ","
# >            << setw(userWidth) << q.z() << ")";
# > }
# > */

# ======================== Class/MCParticleProperty/MCDecayMode.cc
# 15c15
# < // $Id: MCDecayMode.cc,v 1.11 2003/10/09 17:10:23 ryd Exp $
# ---
# > // $Id: MCDecayMode.cc,v 1.8 2002/01/20 19:29:03 lkg Exp $
# 20,28d19
# < // Revision 1.11  2003/10/09 17:10:23  ryd
# < // added missing math.h
# < //
# < // Revision 1.10  2003/10/08 20:51:17  ryd
# < // Not directly compare two floats for equality, see if difference is small
# < //
# < // Revision 1.9  2003/01/29 19:15:32  cdj
# < // get iomanip header from C++Std package
# < //
# 71c62
# < #include "C++Std/iomanip.h"
# ---
# > #include <iomanip.h>
# 73d63
# < #include <math.h>
# 103,104c93,94
# < static const char* const kIdString  = "$Id: MCDecayMode.cc,v 1.11 2003/10/09 17:10:23 ryd Exp $";
# < static const char* const kTagString = "$Name: v03_11_02 $";
# ---
# > static const char* const kIdString  = "$Id: MCDecayMode.cc,v 1.8 2002/01/20 19:29:03 lkg Exp $";
# > static const char* const kTagString = "$Name: v03_02_02 $";
# 341c331
# <       if ( fabs(parentProp.charge()-chargeTotal)>1e-6 ) {
# ---
# >       if ( parentProp.charge() != chargeTotal ) {

# ======================== Class/MCParticleProperty/MCPPStoreItr.cc
# 47c47
# < static const char* const kTagString = "$Name: v03_11_02 $";
# ---
# > static const char* const kTagString = "$Name: v03_02_02 $";

# ======================== Class/MCParticleProperty/MCParticleProperty.cc
# 21c21
# < // $Id: MCParticleProperty.cc,v 1.11 2003/01/29 19:15:32 cdj Exp $
# ---
# > // $Id: MCParticleProperty.cc,v 1.10 2001/12/19 18:11:43 lkg Exp $
# 26,28d25
# < // Revision 1.11  2003/01/29 19:15:32  cdj
# < // get iomanip header from C++Std package
# < //
# 74c71
# < #include "C++Std/iomanip.h"
# ---
# > #include <iomanip.h>

# ======================== Class/MCParticleProperty/MCParticlePropertyStore.cc
# 12c12
# < // $Id: MCParticlePropertyStore.cc,v 1.10 2003/01/29 19:15:32 cdj Exp $
# ---
# > // $Id: MCParticlePropertyStore.cc,v 1.9 2002/02/05 03:39:00 lkg Exp $
# 17,19d16
# < // Revision 1.10  2003/01/29 19:15:32  cdj
# < // get iomanip header from C++Std package
# < //
# 62c59
# < #include "C++Std/iomanip.h"
# ---
# > #include <iomanip.h>

# ======================== Class/MCParticleProperty/MCQQBar.cc
# 63c63
# < static const char* const kTagString = "$Name: v03_11_02 $";
# ---
# > static const char* const kTagString = "$Name: v03_02_02 $";

# ======================== Class/MCParticleProperty/SimpleAngularHelicity.cc
# 13c13
# < // $Id: SimpleAngularHelicity.cc,v 1.3 2003/05/19 20:18:41 lkg Exp $
# ---
# > // $Id: SimpleAngularHelicity.cc,v 1.2 2001/12/19 18:12:17 lkg Exp $
# 18,20d17
# < // Revision 1.3  2003/05/19 20:18:41  lkg
# < // abs -> fabs
# < //
# 37d33
# < #include <math.h>
# 54,55c50,51
# < static const char* const kIdString  = "$Id: SimpleAngularHelicity.cc,v 1.3 2003/05/19 20:18:41 lkg Exp $";
# < static const char* const kTagString = "$Name: v03_11_02 $";
# ---
# > static const char* const kIdString  = "$Id: SimpleAngularHelicity.cc,v 1.2 2001/12/19 18:12:17 lkg Exp $";
# > static const char* const kTagString = "$Name: v03_02_02 $";
# 171c167
# <        max_dNdCosTheta += fabs(theConfig[j]);
# ---
# >        max_dNdCosTheta += abs(theConfig[j]);

# ======================== Class/MCParticleProperty/SimpleHelicity.cc
# 13c13
# < // $Id: SimpleHelicity.cc,v 1.5 2003/01/29 19:15:33 cdj Exp $
# ---
# > // $Id: SimpleHelicity.cc,v 1.4 2001/12/19 18:12:17 lkg Exp $
# 18,20d17
# < // Revision 1.5  2003/01/29 19:15:33  cdj
# < // get iomanip header from C++Std package
# < //
# 44c41
# < #include "C++Std/iomanip.h"
# ---
# > #include <iomanip.h>
# 68,69c65,66
# < static const char* const kIdString  = "$Id: SimpleHelicity.cc,v 1.5 2003/01/29 19:15:33 cdj Exp $";
# < static const char* const kTagString = "$Name: v03_11_02 $";
# ---
# > static const char* const kIdString  = "$Id: SimpleHelicity.cc,v 1.4 2001/12/19 18:12:17 lkg Exp $";
# > static const char* const kTagString = "$Name: v03_02_02 $";

# ======================== Class/Storage/DeliverDummyMCDT.cc
# 67c67
# < static const char* const kTagString = "$Name: v03_11_02 $";
# ---
# > static const char* const kTagString = "$Name: v03_02_02 $";

# ======================== Class/Storage/DeliverDummyMCPPS.cc
# 63c63
# < static const char* const kTagString = "$Name: v03_11_02 $";
# ---
# > static const char* const kTagString = "$Name: v03_02_02 $";

# ======================== Class/Storage/MCDecayModeStorageHelper.cc
# 13c13
# < // $Id: MCDecayModeStorageHelper.cc,v 1.3 2002/06/06 01:26:56 lkg Exp $
# ---
# > // $Id: MCDecayModeStorageHelper.cc,v 1.1 2001/12/19 18:20:07 lkg Exp $
# 18,23d17
# < // Revision 1.3  2002/06/06 01:26:56  lkg
# < // get rid of unneeded code that was formerly not used because of bad SUNCC1 flag
# < //
# < // Revision 1.2  2002/06/04 18:56:04  lkg
# < // replaced SUNCC flags with specific bug flags
# < //
# 87,88c81,82
# < static const char* const kIdString  = "$Id: MCDecayModeStorageHelper.cc,v 1.3 2002/06/06 01:26:56 lkg Exp $";
# < static const char* const kTagString = "$Name: v03_11_02 $";
# ---
# > static const char* const kIdString  = "$Id: MCDecayModeStorageHelper.cc,v 1.1 2001/12/19 18:20:07 lkg Exp $";
# > static const char* const kTagString = "$Name: v03_01_00 $";
# 267a262,273
# > #if defined(SUNCC1)
# > template<>
# > struct iterator_traits<SimpleHelicity*> {
# > public:
# >      typedef SimpleHelicity* value_type;
# > };
# > template<>
# > struct iterator_traits<SimpleAngularHelicity*> {
# > public:
# >      typedef SimpleAngularHelicity* value_type;
# > };
# > #endif

# ======================== Class/Storage/MCDecayTreeStorageHelper.cc
# 13c13
# < // $Id: MCDecayTreeStorageHelper.cc,v 1.4 2002/06/04 18:56:04 lkg Exp $
# ---
# > // $Id: MCDecayTreeStorageHelper.cc,v 1.3 2000/07/07 15:01:43 lkg Exp $
# 18,20d17
# < // Revision 1.4  2002/06/04 18:56:04  lkg
# < // replaced SUNCC flags with specific bug flags
# < //
# 104,105c101,102
# < static const char* const kIdString  = "$Id: MCDecayTreeStorageHelper.cc,v 1.4 2002/06/04 18:56:04 lkg Exp $";
# < static const char* const kTagString = "$Name: v03_11_02 $";
# ---
# > static const char* const kIdString  = "$Id: MCDecayTreeStorageHelper.cc,v 1.3 2000/07/07 15:01:43 lkg Exp $";
# > static const char* const kTagString = "$Name: v03_01_00 $";
# 227c224
# < #if defined(NO_ITERATOR_TRAITS_BUG)
# ---
# > #if defined(SUNCC)
# 244c241
# < #if defined(NO_ITERATOR_TRAITS_BUG)
# ---
# > #if defined(SUNCC)

# ======================== Class/Storage/MCParticlePropDecayModeStorageInterfaceStorageHelper.cc
# 80c80
# < static const char* const kTagString = "$Name: v03_11_02 $";
# ---
# > static const char* const kTagString = "$Name: v03_02_02 $";

# ======================== Class/Storage/MCParticlePropertyStorageHelper.cc
# 13c13
# < // $Id: MCParticlePropertyStorageHelper.cc,v 1.4 2003/10/20 20:13:09 ryd Exp $
# ---
# > // $Id: MCParticlePropertyStorageHelper.cc,v 1.2 2002/02/05 03:13:11 lkg Exp $
# 18,23d17
# < // Revision 1.4  2003/10/20 20:13:09  ryd
# < // Changed the packing of charge (again)
# < //
# < // Revision 1.3  2003/10/16 17:22:10  ryd
# < // Change storage of charge such that fractional (1/3) charges can be stored.
# < //
# 67d60
# < #include <math.h>
# 86,87c79,80
# < static const char* const kIdString  = "$Id: MCParticlePropertyStorageHelper.cc,v 1.4 2003/10/20 20:13:09 ryd Exp $";
# < static const char* const kTagString = "$Name: v03_11_02 $";
# ---
# > static const char* const kIdString  = "$Id: MCParticlePropertyStorageHelper.cc,v 1.2 2002/02/05 03:13:11 lkg Exp $";
# > static const char* const kTagString = "$Name: v03_02_02 $";
# 102d94
# <    registerVersion( &MCParticlePropertyStorageHelper::deliverV2 );
# 142,144d133
# <   
# <   int chg3=floor(iData.charge()*3+0.5);
# < 
# 151c140
# <       << sm_pack( sm_field("charge3", chg3),-6,6,1)
# ---
# >       << sm_pack( SM_VAR( iData, charge ), -2., 2., 1. )
# 215,273d203
# <       width,  
# <       minMass,  
# <       maxMass,  
# <       spin,  
# <       parity,  
# <       cParity,  
# <       mixable ) ); 
# < }
# < 
# < MCParticleProperty* 
# < MCParticlePropertyStorageHelper::deliverV2( SMSourceStream& iSource )
# < {
# <    
# <    string name; 
# <    QQ_id qqId; 
# <    Stable_id stableId; 
# <    PDG_id pdgId; 
# <    Geant_id geantId; 
# <    int charge; 
# <    Double ctau; 
# <    Double mass; 
# <    Double width; 
# <    Double minMass; 
# <    Double maxMass; 
# <    Double spin; 
# <    Integer parity; 
# <    Integer cParity; 
# <    unsigned char mixable_as_char;
# <    DABoolean mixable; 
# < 
# <    iSource 
# <       >> name 
# <       >> qqId 
# <       >> stableId 
# <       >> pdgId 
# <       >> geantId 
# <       >> charge 
# <       >> ctau 
# <       >> mass 
# <       >> width 
# <       >> minMass 
# <       >> maxMass 
# <       >> spin 
# <       >> parity 
# <       >> cParity 
# <       >> mixable_as_char
# <        ;
# < 
# <    mixable = mixable_as_char;
# < 
# <    return make( MCParticleProperty( 
# <       name,  
# <       qqId,  
# <       stableId,  
# <       pdgId,  
# <       geantId,  
# <       charge/3.0,  
# <       ctau,  
# <       mass,  

# ======================== Class/Storage/MCParticlePropertyStoreStorageHelper.cc
# 13c13
# < // $Id: MCParticlePropertyStoreStorageHelper.cc,v 1.2 2003/07/08 15:26:17 cdj Exp $
# ---
# > // $Id: MCParticlePropertyStoreStorageHelper.cc,v 1.1 2001/12/19 18:20:08 lkg Exp $
# 18,20d17
# < // Revision 1.2  2003/07/08 15:26:17  cdj
# < // fixed memory leak
# < //
# 115,116c112,113
# < static const char* const kIdString  = "$Id: MCParticlePropertyStoreStorageHelper.cc,v 1.2 2003/07/08 15:26:17 cdj Exp $";
# < static const char* const kTagString = "$Name: v03_11_02 $";
# ---
# > static const char* const kIdString  = "$Id: MCParticlePropertyStoreStorageHelper.cc,v 1.1 2001/12/19 18:20:08 lkg Exp $";
# > static const char* const kTagString = "$Name: v03_02_02 $";
# 198,203d194
# <    for(STL_VECTOR(MCParticlePropDecayModeStorageInterface*)::iterator
# <         itIface = dmInterface.begin();
# <        itIface != dmInterface.end();
# <        ++itIface ) {
# <       delete *itIface;
# <    }

# ======================== Class/Storage/MCParticleStorageHelper.cc
# 119c119
# < static const char* const kTagString = "$Name: v03_11_02 $";
# ---
# > static const char* const kTagString = "$Name: v03_02_02 $";

# ======================== Class/Storage/MCVertexStorageHelper.cc
# 13c13
# < // $Id: MCVertexStorageHelper.cc,v 1.6 2003/07/08 15:27:12 cdj Exp $
# ---
# > // $Id: MCVertexStorageHelper.cc,v 1.5 2001/12/19 18:10:37 lkg Exp $
# 18,20d17
# < // Revision 1.6  2003/07/08 15:27:12  cdj
# < // can now read back the case where we stored an unknown decay mode
# < //
# 113,114c110,111
# < static const char* const kIdString  = "$Id: MCVertexStorageHelper.cc,v 1.6 2003/07/08 15:27:12 cdj Exp $";
# < static const char* const kTagString = "$Name: v03_11_02 $";
# ---
# > static const char* const kIdString  = "$Id: MCVertexStorageHelper.cc,v 1.5 2001/12/19 18:10:37 lkg Exp $";
# > static const char* const kTagString = "$Name: v03_02_02 $";
# 244d240
# <    assert(m_particlePtr.size() != 0 );
# 263,276c259,261
# <       if( cTypeList.empty() ) {
# <        // assume the decay mode is unknown
# <        tmpVertPtr->setDecayMode(MCDecayMode::unknown() );
# <       } else {
# <        MCParticleProperty::const_iterator theDecayMode =
# <           m_particlePtr.top()->properties().findDecayMode( cTypeList );
# < 
# <        if( m_particlePtr.top()->properties().end() != theDecayMode ) {
# <           tmpVertPtr->setDecayMode( *theDecayMode );
# <        } else {
# <           ostream& tempReport = report(ERROR,kFacilityString) ;
# <           tempReport <<"unable to find decay mode for decay vertex of particle " <<*(m_particlePtr.top()) <<endl;
# <        }
# <       }
# ---
# >       MCParticleProperty::const_iterator theDecayMode =
# >        m_particlePtr.top()->properties().findDecayMode( cTypeList );
# >       tmpVertPtr->setDecayMode( *theDecayMode );

# ======================== Class/Storage/SimpleAngularHelicityHolderStorageHelper.cc
# 13c13
# < // $Id: SimpleAngularHelicityHolderStorageHelper.cc,v 1.3 2002/06/04 18:56:04 lkg Exp $
# ---
# > // $Id: SimpleAngularHelicityHolderStorageHelper.cc,v 1.2 2001/12/21 20:30:29 lkg Exp $
# 18,20d17
# < // Revision 1.3  2002/06/04 18:56:04  lkg
# < // replaced SUNCC flags with specific bug flags
# < //
# 76c73
# < #if defined(NO_ITERATOR_TRAITS_BUG)
# ---
# > #if defined(SUNCC)

# ======================== Class/Storage/SimpleAngularHelicityStorageHelper.cc
# 92c92
# < static const char* const kTagString = "$Name: v03_11_02 $";
# ---
# > static const char* const kTagString = "$Name: v03_02_02 $";

# ======================== Class/Storage/SimpleHelicityHolderStorageHelper.cc
# 13c13
# < // $Id: SimpleHelicityHolderStorageHelper.cc,v 1.3 2002/06/04 18:56:04 lkg Exp $
# ---
# > // $Id: SimpleHelicityHolderStorageHelper.cc,v 1.2 2001/12/21 20:30:30 lkg Exp $
# 18,20d17
# < // Revision 1.3  2002/06/04 18:56:04  lkg
# < // replaced SUNCC flags with specific bug flags
# < //
# 76c73
# < #if defined(NO_ITERATOR_TRAITS_BUG)
# ---
# > #if defined(SUNCC)

# ======================== Class/Storage/SimpleHelicityStorageHelper.cc
# 92c92
# < static const char* const kTagString = "$Name: v03_11_02 $";
# ---
# > static const char* const kTagString = "$Name: v03_02_02 $";

# ======================== Class/Storage/T_MCDecayModeStorageHelper.cc

# ======================== Class/Storage/T_MCParticlePropDecayModeStorageInterfaceStorageHelper.cc

# ======================== Class/Storage/T_MCParticlePropertyStorageHelper.cc

# ======================== Class/Storage/T_MCParticleStorageHelper.cc

# ======================== Class/Storage/T_MCVertexStorageHelper.cc

# ======================== Class/Storage/T_SimpleAngularHelicityStorageHelper.cc

# ======================== Class/Storage/T_SimpleHelicityStorageHelper.cc

# ======================== Instantiate/MCDecayFileParser/T_deque_of_vector_of_double.cc
# 11c11
# < // $Id: T_deque_of_vector_of_double.cc,v 1.2 2002/06/04 18:56:10 lkg Exp $
# ---
# > // $Id: T_deque_of_vector_of_double.cc,v 1.1 1999/06/22 21:29:05 lkg Exp $
# 40c40
# < #if defined(AUTO_INSTANTIATE_TEMPLATE_BUG)
# ---
# > #if defined(SUNCC)

# ======================== Instantiate/MCDecayFileParser/T_getline_ifstream.cc
# 11c11
# < // $Id: T_getline_ifstream.cc,v 1.5 2002/12/06 16:42:14 cleo3 Exp $
# ---
# > // $Id: T_getline_ifstream.cc,v 1.3 2001/09/10 20:08:58 cleo3 Exp $
# 16,21d15
# < // Revision 1.5  2002/12/06 16:42:14  cleo3
# < // deal with g++ namespace instantiation bug
# < //
# < // Revision 1.4  2002/11/21 21:11:55  cleo3
# < // changed fstream.h to C++Std/fstream.h
# < //
# 37c31
# < #include "C++Std/fstream.h"
# ---
# > #include <fstream.h>
# 49,53d42
# < #if defined(NEED_TO_BE_IN_NAMESPACE_TO_INSTANTIATE_TEMPLATE_BUG)
# < #undef STD_PREFIX
# < #define STD_PREFIX
# < namespace std {
# < #endif
# 56,58d44
# < #if defined(NEED_TO_BE_IN_NAMESPACE_TO_INSTANTIATE_TEMPLATE_BUG)
# < }
# < #endif

# ======================== Instantiate/MCDecayFileParser/T_getline_istrstream.cc

# ======================== Instantiate/MCDecayFileParser/T_map_of_string_commandparser.cc

# ======================== Instantiate/MCDecayFileParser/T_map_string_MCDecayMode.cc
# diff: /nfs/cleo3/Offline/rel/Jun27_02_MC/src/MCInfo/Instantiate/MCDecayFileParser/T_map_string_MCDecayMode.cc: No such file or directory

# ======================== Instantiate/MCDecayTree/T_deque_of_MCParticle.cc

# ======================== Instantiate/MCDecayTree/T_deque_of_pair_MCParticle_iter.cc

# ======================== Instantiate/MCDecayTree/T_deque_of_pair_MCVertex_iter.cc

# ======================== Instantiate/MCDecayTree/T_list_of_MCParticle.cc

# ======================== Instantiate/MCDecayTree/T_list_of_MCVertex.cc

# ======================== Instantiate/MCDecayTree/T_list_of_interaction.cc
# 11c11
# < // $Id: T_list_of_interaction.cc,v 1.5 2002/12/06 16:42:14 cleo3 Exp $
# ---
# > // $Id: T_list_of_interaction.cc,v 1.4 2001/09/10 20:08:01 cleo3 Exp $
# 16,18d15
# < // Revision 1.5  2002/12/06 16:42:14  cleo3
# < // deal with g++ namespace instantiation bug
# < //
# 51,55d47
# < #if defined(NEED_TO_BE_IN_NAMESPACE_TO_INSTANTIATE_TEMPLATE_BUG)
# < #undef STD_PREFIX
# < #define STD_PREFIX
# < namespace std {
# < #endif
# 65,67d56
# < #if defined(NEED_TO_BE_IN_NAMESPACE_TO_INSTANTIATE_TEMPLATE_BUG)
# < }
# < #endif

# ======================== Instantiate/MCDecayTree/instantiate_MCDecayTreeItr.cc

# ======================== Instantiate/MCDecayTree/instantiate_MCListItr.cc

# ======================== Instantiate/MCDecayTree/instantiate_binary_search_qqid.cc

# ======================== Instantiate/MCDecayTree/instantiate_find_if_MCDecayTree_pIter.cc

# ======================== Instantiate/MCDecayTree/instantiate_find_if_vIter_CheckId.cc

# ======================== Instantiate/MCDecayTree/instantiate_find_if_vector_qqid.cc

# ======================== Instantiate/MCDecayTree/instantiate_transform_qqid_string.cc

# ======================== Instantiate/MCDecayTree/instantiate_transform_string_qqid.cc

# ======================== Instantiate/MCParticleProperty/T_equal_vector_of_qqid.cc

# ======================== Instantiate/MCParticleProperty/T_map_of_Helicity_CosThetaDep.cc

# ======================== Instantiate/MCParticleProperty/T_map_of_Likelihood_ChildHelicities.cc

# ======================== Instantiate/MCParticleProperty/T_map_of_Likelihood_MCDecayMode.cc

# ======================== Instantiate/MCParticleProperty/T_map_of_pdgid_qqid.cc

# ======================== Instantiate/MCParticleProperty/T_map_of_string_helicity.cc

# ======================== Instantiate/MCParticleProperty/T_map_of_string_qqid.cc

# ======================== Instantiate/MCParticleProperty/T_vector_of_HelicityConfig.cc

# ======================== Instantiate/MCParticleProperty/T_vector_of_MCDecayMode.cc

# ======================== Instantiate/MCParticleProperty/T_vector_of_MCParticleProperty.cc

# ======================== Instantiate/MCParticleProperty/T_vector_of_qqid.cc

# ======================== Instantiate/MCParticleProperty/instantiate_MCPPStoreItr.cc

# ======================== Instantiate/MCParticleProperty/instantiate_equal_MCPPStoreItr.cc

# ======================== Instantiate/MCParticleProperty/instantiate_equal_MCParticle_constItr.cc

# ======================== Instantiate/MCParticleProperty/instantiate_equal_vector_double.cc

# ======================== Instantiate/MCParticleProperty/instantiate_find_if_ChildHelicity_map.cc

# ======================== Instantiate/MCParticleProperty/instantiate_find_if_DecayMode_map.cc

# ======================== Instantiate/MCParticleProperty/instantiate_find_if_ModeCheck.cc

# ======================== Instantiate/MCParticleProperty/instantiate_find_if_ModeCheckId.cc

# ======================== Instantiate/MCParticleProperty/instantiate_transform_conjugate.cc

# ======================== Instantiate/MCParticleProperty/instantiate_transform_const_qqid_string.cc

# ======================== Instantiate/MCParticleProperty/instantiate_transform_const_string_qqid.cc

# ======================== Instantiate/MCParticleProperty/instantiate_transform_qqid_string.cc

# ======================== Instantiate/MCParticleProperty/instantiate_transform_string_qqid.cc

# ======================== MCInfo/MCDecayTree/Template/MCDecayTreeItr.cc
# 80c80
# < static const char* const kTagString = "$Name: v03_11_02 $";
# ---
# > static const char* const kTagString = "$Name: v03_02_02 $";

# ======================== MCInfo/MCDecayTree/Template/MCListItr.cc
# 53c53
# < static const char* const kTagString = "$Name: v03_11_02 $";
# ---
# > static const char* const kTagString = "$Name: v03_02_02 $";

# ======================== MCInfo/Utility/Template/RefCntPtr.cc
# 47c47
# < static const char* const kTagString = "$Name: v03_11_02 $";
# ---
# > static const char* const kTagString = "$Name: v03_02_02 $";

