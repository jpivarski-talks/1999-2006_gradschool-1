#####################################################
# file: $C3_SCRIPTS/richAna.tcl
#
# purpose: reconstruct RICH info
#
# 
#####################################################
#
#  This is a script to configure RICH producers
#  Initial version for mini pass2 data  TS 8/3/00
#
#  $Id: richAna.tcl,v 1.5 2002/01/21 18:01:43 mahlke Exp $
#  $Log: richAna.tcl,v $
#  Revision 1.5  2002/01/21 18:01:43  mahlke
#  updated RichTrackPrototypesProd Z0ResoFudgeFactor
#
#  Revision 1.4  2001/10/26 19:56:38  potlia
#  updated fudgefactors
#
#  Revision 1.4  2001/10/26 15:12;04  potlia
#  update fudgefactors
#
#  Revision 1.3  2001/10/02 22:12:33  jed
#   minor comments mods, add in RichTrack PrototypesProd Electron(MUON) 8 parameter, add in RichAnglesProd Pexact 200000.0 to get code speed up everywhere
#
#  Revision 1.2  2000/11/20 03:12:05  ts
#  update rich scripts to use RichTrackPrototypesProd etc.
#
#  Revision 1.1  2000/08/03 22:43:41  ts
#  add rich scripts
#
#

# RICH producers ---------------------------------------------

#  Minimum pulse height for charged track hits
set PHTRK 700

# starting from raw data 
prod sel RawDataProd

#
#  rich calibrated hits
#
prod sel RichCalibratedHits

#
#  rich clustering
#
prod sel RichClustering
prod sel RichClustChamberCoord


#
#  make RichTrackPrototype's
#
prod sel RichTrackPrototypesProd
#
#  to speed up processing 
#  you can exclude up to four hypotheses from
#  being analyzed by uncommenting lines below
#  e.g. for Bhabhas leave only the Electron line 
#       commented out
#
param RichTrackPrototypesProd Electron 8
param RichTrackPrototypesProd Muon 8
#param RichTrackPrototypesProd Pion 0
#param RichTrackPrototypesProd Kaon 0
#param RichTrackPrototypesProd Proton 0
# Note that Z0ResoFudgeFactor might change if alignment changes
param RichTrackPrototypesProd Z0ResoFudgeFactor 1.4
#
#  make RichTrack's
#
prod sel RichTracksProd


#
#  match tracks to rich hits
#
prod sel RichTrackClusterMatchProd

#
#  create photon candidates
#
prod sel RichPhotonsProd
param RichPhotonsProd BumpPulseHeightMax $PHTRK

#
#  improve track parameters used in Rich analysis 
#  by using info from matched Rich hit (if any)
#
prod sel RichImprovedTracksProd
param RichImprovedTracksProd TrackHitPulseHeightMin $PHTRK
#        resolution improved if track is improved with rich hit
# Note that Z0ResoFudgeFactor might change if alignment changes
param RichImprovedTracksProd Z0ResoFudgeFactor 0.2

#
# calculate Cherenkov angles for track-photon combinations
#
prod sel RichAnglesProd
#    for a large CPU speed-up with some deterioration in particle ID
#    uncomment the following line
param RichAnglesProd Pexact 200000.0

#
# calculate track-average quantities (first pass)
#
prod sel RichAverageAnglesProd
param RichAverageAnglesProd production_tag unrefined
#
# now refine by removing shared hits between more than
# one track   
#
prod sel RichRefinedAverageAnglesProd
# ----------------------------------------------------------
