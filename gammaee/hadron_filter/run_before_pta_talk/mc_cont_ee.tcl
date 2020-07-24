default prompt off
exception continueEventLoop on

module sel HbookHistogramModule
hbook file ../rzn/mc_cont_ee_cut3.rzn
hbook init

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
prod sel CesrBeamEnergyProd
prod sel EventPropertiesProd

run_file goldmine_fl_cont.tcl
run_file goldmine_mn_cont.tcl

proc sel ../build_SunOS/shlib/UpsToLeptons
param UpsToLeptons passE true
param UpsToLeptons passMu false
param UpsToLeptons passTau false

proc sel EventTypeFilterProc
param EventTypeFilterProc Hadron true

proc sel ../build_SunOS/shlib/HadronFilterProc
param HadronFilterProc noBunchWeight true
param HadronFilterProc ntupleSize 10000
param HadronFilterProc noBeamSpot true

param HadronFilterProc fillBuffer false
go

hbook terminate
exit
