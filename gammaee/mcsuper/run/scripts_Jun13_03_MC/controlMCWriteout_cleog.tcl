##################################################################
# file: $C3_SCRIPTS/controlMCWriteout_cleog.tcl
#
# purpose: control exactly what objects are written to the 
#           output file in cleog
# 
##################################################################
echo " %%%%%%%%%%%%%%%%%%%%%%%%%%"
echo " % CLEOG CONTROL WRITEOUT %"
echo " %%%%%%%%%%%%%%%%%%%%%%%%%%"

########################################
# set up the list of data to store     #
# First set up an empty list, and then #
# concatenate each detector's output   #
########################################

set listMCOutput [list]

# pass2 output
set listMCOutput [concat $listMCOutput {\
     BunchDecision \
     DBEventHeader \
     FATable<MCCCResponse>    \
     FATable<MCDRResponse> \
     FATable<CalibratedDRHit> \
     FATable<CcEnergyHit>     \
     FATable<DRCACorrectHit>  \
     FATable<RichCalibratedHit> \
     FATable<CalibratedSVRphiHit> \
     FATable<CalibratedSVZHit>    \
     TriggerL1Data \
     RawEventData \
     TriggerInfo \
} ]

# MC specials:
set listMCOutput [concat $listMCOutput {\
     MCDecayTree \
     {MCDecayTree Generator} \
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
