default prompt off
exception continueEventLoop on

module sel LoadHbook4MModule
module sel HbookHistogramModule
hbook file ../chib_rzn/cont$env(USER_DB).rzn
hbook init

module sel CorbaModule
corba init
module sel RunStatisticsSourceModule
runstatistics in
module sel ConstantsModule
constants in $env(C3_CONST) standard CLEO3default streams superconductingquad magfudge
constants in $env(C3_CONST) meta BaseGeometry MetaListRetrieval

prod sel NavigationProd
prod sel TrackDeliveryProd
prod sel C3ccProd
param C3ccProd RequireRunGainsHotList false
prod sel MagFieldProd
prod sel EventPropertiesProd
prod sel CesrBeamEnergyProd

source_format sel BeamSpotFileSourceFormat
file in $env(C3_INFO)/data/beamspot.beamspot beginrun
run_file $env(C3_SCRIPTS)/CcHotList.tcl

run_file $env(C3_SCRIPTS)/RunInfo.tcl
param RunInfoProc MinBeamEnergy 4.995
param RunInfoProc MaxBeamEnergy 5.005

proc sel ../build_SunOS/shlib/ChiBSkim

module sel DBModule
database in /nfs/cleo3/database/data$env(USER_DB)/db event startrun beginrun endrun
database read_collection pass2 radlep

sink_format sel PDSSinkFormat
file out ../chib_rzn/cont$env(USER_DB).pds {event{\
    DBTrackerValues FATable<TRTrack> FATable<TRHelixPionFit> FATable<TRPionQuality>\
    FATable<CcBasicShowerAttsArg> TrackShowerLattice FATable<CcConRegAttributes> CcConRegShowerLattice\
    EventProperties DBEventHeader\
}} startrun beginrun endrun

go




