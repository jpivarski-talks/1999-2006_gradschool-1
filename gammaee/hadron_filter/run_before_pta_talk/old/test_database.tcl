exception continueEventLoop on

#  run_file $env(C3_SCRIPTS)/runOnPass2.tcl
prod sel CesrBeamEnergyProd
#  module sel DBModule
#  database in /nfs/cleo3/database/data16/db beginrun event startrun endrun
#  database read_collection pass2 radlep

module sel CorbaModule
corba init
module sel RunStatisticsSourceModule
runstatistics in
module sel ConstantsModule
constants in $env(C3_CONST) meta FieldMap MetaListRetrieval
source_format sel MagFudgeFileSourceFormat
file in normal.magfudge
prod sel NavigationProd
prod sel TrackDeliveryProd
prod sel C3ccProd
prod sel MagFieldProd
prod sel DBEventHeaderProd

run_file goldmine.tcl

proc sel ../build_SunOS/shlib/HadronFilterProc.so
param HadronFilterProc noBunchWeight true
param HadronFilterProc ntupleSize -1
param HadronFilterProc noBeamSpot true
param HadronFilterProc fillBuffer false

proc sel EventTypeFilterProc
param EventTypeFilterProc BeamGas true
param EventTypeFilterProc BhabhaLoose true
param EventTypeFilterProc BhabhaTight true
param EventTypeFilterProc Cosmic true
param EventTypeFilterProc ElGamJunk true
param EventTypeFilterProc GamGam true
param EventTypeFilterProc Hadron true
param EventTypeFilterProc HadronTight true
param EventTypeFilterProc HardGam true
param EventTypeFilterProc Known true
param EventTypeFilterProc LoPt2Leptons true
param EventTypeFilterProc LoPt4Pions true
param EventTypeFilterProc LoPtGT2Tk true
param EventTypeFilterProc LoPtLoose true
param EventTypeFilterProc LoPtOneTag true
param EventTypeFilterProc LoPtTwoTk true
param EventTypeFilterProc LoPtTwotag true
param EventTypeFilterProc MuPair true
param EventTypeFilterProc RadBha true
param EventTypeFilterProc RadGam true
param EventTypeFilterProc RadMuP true
param EventTypeFilterProc Tau true
param EventTypeFilterProc Tau1vN true
param EventTypeFilterProc TauLoBgd true
param EventTypeFilterProc TranDiElec true
param EventTypeFilterProc TranDiMuon true
param EventTypeFilterProc TranLepTk true
param EventTypeFilterProc Unknown true

go
exit
