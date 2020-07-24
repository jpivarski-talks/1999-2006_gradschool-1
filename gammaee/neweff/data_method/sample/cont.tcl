default prompt off
exception continueEventLoop on

module sel LoadHbook4MModule
module sel HbookHistogramModule
hbook file ../../data_method_rzn/sample/cont.rzn
hbook init

module sel CorbaModule
corba init
module sel RunStatisticsSourceModule
runstatistics in
module sel ConstantsModule
constants in $env(C3_CONST) standard CLEO3default streams superconductingquad magfudge

prod sel NavigationProd
prod sel TrackDeliveryProd

prod sel MagFieldProd
# prod sel CesrBeamEnergyProd
# prod sel DoNotReadFromTapeProd

run_file $env(C3_SCRIPTS)/CcHotList.tcl

proc sel ../../build_SunOS/shlib/DuperCuts

source_format sel BeamSpotFileSourceFormat
file in $env(C3_INFO)/data/beamspot.beamspot beginrun

source_format sel PDSSourceFormat
file in ../../data_method_rzn/sample/r129863.pds event startrun
go
source rm r129863

source_format sel PDSSourceFormat
file in ../../data_method_rzn/sample/r129864.pds event startrun
go
