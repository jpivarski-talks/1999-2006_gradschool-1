##################################################################
# file: $C3_SCRIPTS/pass2/controlWriteout_pass2.tcl
#
# purpose: control exactly what objects are written to the
#           output file in pass2
#
# usage:
#   DBModule allows either a
#     1) positive list
#     or a
#     2) negative list
#   of what should get or not get written out.
# 
# The convention used here is that the store list is set up 
# to reflect the order given in OBBase to make verification
#  that all objects written out have somewhere to go easier.
#
#
##################################################################
echo " %%%%%%%%%%%%%%%%%%%%%%%%%%"
echo " % PASS2 CONTROL WRITEOUT %"
echo " %%%%%%%%%%%%%%%%%%%%%%%%%%"

########################################
# set up the list of data to store     #
# First set up an empty list, and then #
# concatenate each detectors' output   #
########################################
set toStoreList [list]
########################
# Analysis Store
########################
# Note that RawEventData is not really part of Analysis Store
# but has to be included here for DB reasons.
# TRACKS
set toStoreList [concat $toStoreList {\
RawEventData\
DBTrackerValues\
FATable<TRTrack>\
FATable<TRHelixExitPionFit>\
FATable<TRHelixKaonFit>\
FATable<TRHelixPionFit>\
FATable<TRHelixProtonFit>\
FATable<TRKaonQuality>\
FATable<TRExitPionQuality>\
FATable<TRPionQuality>\
FATable<TRProtonQuality>\
FATable<TRSeedTrackQuality>\
FATable<TRSeedTrack>\
FATable<DoitSeedQuality>\
} ]
# VFINDER
set toStoreList [concat $toStoreList {\
FATable<VXFitVeeKShort>\
FATable<VXFitVeeLambda>\
FATable<VXFitVeeConversion>\
} ]
# MUON
set toStoreList [concat $toStoreList {\
FATable<MuTrack>\
} ]
# RICH
set toStoreList [concat $toStoreList {\
FATable<RichTrackAveAngles>\
FATable<RichTrackPrototype>\
RichTracksMethod\
} ]
# DEDX
set toStoreList [concat $toStoreList {\
FATable<DedxRecon>\
DedxEventFlag\
} ]
# CC
set toStoreList [concat $toStoreList {\
FATable<CcBasicShowerAttsArg>\
TrackShowerLattice\
FATable<CcConRegAttributes>\
CcConRegShowerLattice\
} ]
# TRIGGER
set toStoreList [concat $toStoreList {\
TriggerL1Data\
Level3TagWord\
Level4Decision\
} ]
# EVENT
set toStoreList [concat $toStoreList {\
EventProperties\
BunchDecision\
DBEventHeader\
EventType\
} ]
########################
# Warm Store
########################
# Seed Anawarm
set toStoreList [concat $toStoreList {\
SeedTrackCathodeHitLattice\
SeedTrackDRHitLattice\
SeedTrackSVRHitLattice\
SeedTrackSVZHitLattice\
} ]
########################
# Cold Store
########################
# Fit Lattices Cold
set toStoreList [concat $toStoreList {\
ExitPionFitCathodeHitLattice\
ExitPionFitDRHitLattice\
ExitPionFitSVRHitLattice\
ExitPionFitSVZHitLattice\
KaonFitCathodeHitLattice\
KaonFitDRHitLattice\
KaonFitSVRHitLattice\
KaonFitSVZHitLattice\
PionFitCathodeHitLattice\
PionFitDRHitLattice\
PionFitSVRHitLattice\
PionFitSVZHitLattice\
ProtonFitCathodeHitLattice\
ProtonFitDRHitLattice\
ProtonFitSVRHitLattice\
ProtonFitSVZHitLattice\
} ]
# Kalman Quality Cold
set toStoreList [concat $toStoreList {\
FATable<KalmanExitPionQuality>\
FATable<KalmanKaonQuality>\
FATable<KalmanPionQuality>\
FATable<KalmanProtonQuality>\
} ]
# Calibrated Hits Cold
set toStoreList [concat $toStoreList {\
CathodeClusterHitLattice\
FATable<DRCACorrectHit>\
SVRHitStripLattice\
SVZHitStripLattice\
} ]
# CC Hits Cold
set toStoreList [concat $toStoreList {\
FATable<CcEnergyHit>\
CcHitShowerLattice\
} ]

#-------------- Now tell DBModule ------------
# set up subcollections to write to
prod sel EventClassificationProd
param EventClassificationProd eventClassSchemeParm pass2
#
module sel DBModule
param DBModule dataKeysToStore [join $toStoreList]
#

echo " %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"
echo " % PASS2 CONTROL WRITEOUT DONE %"
echo " %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"
