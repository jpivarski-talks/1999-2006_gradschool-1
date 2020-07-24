##################################################################
# file: $C3_SCRIPTS/mcpass2/controlMCWriteout_mcpass2.tcl
#
# purpose: control exactly what objects are written to the 
#           output file in mcpass2
# 
##################################################################
echo " %%%%%%%%%%%%%%%%%%%%%%%%%%%%"
echo " % MCPASS2 CONTROL WRITEOUT %"
echo " %%%%%%%%%%%%%%%%%%%%%%%%%%%%"

########################################
# set up the list of data to store     #
# First set up an empty list, and then #
# concatenate each detector's output   #
########################################

set listMCOutput [list]

# pass2 output
set listMCOutput [concat $listMCOutput {\
     DBTrackerValues \
     FATable<TRTrack> \
     FATable<TRHelixExitPionFit> \
     FATable<TRHelixKaonFit> \
     FATable<TRHelixPionFit> \
     FATable<TRHelixProtonFit> \
     FATable<TRExitPionQuality> \
     FATable<TRKaonQuality> \
     FATable<TRPionQuality> \
     FATable<TRProtonQuality> \
     FATable<TRSeedTrackQuality> \
     FATable<TRSeedTrack> \
     FATable<DoitSeedQuality> \
     FATable<VXFitVeeKShort> \
     FATable<VXFitVeeLambda> \
     FATable<VXFitVeeConversion> \
     FATable<MuTrack> \
     FATable<RichTrackAveAngles> \
     FATable<RichTrackPrototype> \
     RichTracksMethod \
     FATable<CcBasicShowerAttsArg> \
     TrackShowerLattice \
     FATable<CcConRegAttributes>\
     CcConRegShowerLattice \
     TriggerL1Data \
     TriggerInfo \
     Level3TagWord \
     Level4Decision \
     EventProperties \
     BunchDecision \
     DBEventHeader \
     EventType \
} ]

# MC specials:
set listMCOutput [concat $listMCOutput {\
     MCTrackTaggerLatticeTRSeedTrackCleo3 \
     MCCCTaggerLattice \
     MCDecayTree \
     {MCDecayTree Generator} \
     {FATable<DedxInfo> MC} \
     MCTriggerPhase \
     MCTrueRfBucket \
     MCBeamParticles \
     MCEventVertex   \
} ]

# listMCOutput must actually be a list of a list
set listMCOutput [ list $listMCOutput]

echo " %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"
echo " % MCPASS2 CONTROL WRITEOUT DONE %"
echo " %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"
#######################################################
