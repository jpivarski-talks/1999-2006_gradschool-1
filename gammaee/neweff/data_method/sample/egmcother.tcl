default prompt off
exception continueEventLoop on

module sel LoadHbook4MModule
module sel HbookHistogramModule
hbook file ../../data_method_rzn/sample/egmcother.rzn
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
file in $env(C3_INFO)/mc/zeromc.beamspot beginrun
run_file $env(C3_SCRIPTS)/CcHotList.tcl

proc sel ../../build_SunOS/shlib/DuperCuts2
param DuperCuts2 mcother true

source_format sel PDSSourceFormat

file in ../../data_method_rzn/evtgen/mcpass2_129535.pds physics event startrun beginrun endrun 
go
source rm mcpass2_129535
file in ../../data_method_rzn/evtgen/mcpass2_129536.pds physics event startrun beginrun endrun 
go
source rm mcpass2_129536
file in ../../data_method_rzn/evtgen/mcpass2_129538.pds physics event startrun beginrun endrun 
go
source rm mcpass2_129538
file in ../../data_method_rzn/evtgen/mcpass2_129539.pds physics event startrun beginrun endrun 
go
source rm mcpass2_129539
file in ../../data_method_rzn/evtgen/mcpass2_129540.pds physics event startrun beginrun endrun 
go
source rm mcpass2_129540
file in ../../data_method_rzn/evtgen/mcpass2_129541.pds physics event startrun beginrun endrun 
go
source rm mcpass2_129541
file in ../../data_method_rzn/evtgen/mcpass2_129545.pds physics event startrun beginrun endrun 
go
source rm mcpass2_129545
file in ../../data_method_rzn/evtgen/mcpass2_129549.pds physics event startrun beginrun endrun 
go
source rm mcpass2_129549
file in ../../data_method_rzn/evtgen/mcpass2_129550.pds physics event startrun beginrun endrun 
go
source rm mcpass2_129550
file in ../../data_method_rzn/evtgen/mcpass2_129551.pds physics event startrun beginrun endrun 
go
source rm mcpass2_129551
file in ../../data_method_rzn/evtgen/mcpass2_129552.pds physics event startrun beginrun endrun 
go
source rm mcpass2_129552
file in ../../data_method_rzn/evtgen/mcpass2_129553.pds physics event startrun beginrun endrun 
go
source rm mcpass2_129553
file in ../../data_method_rzn/evtgen/mcpass2_129564.pds physics event startrun beginrun endrun 
go
source rm mcpass2_129564
file in ../../data_method_rzn/evtgen/mcpass2_129566.pds physics event startrun beginrun endrun 
go
source rm mcpass2_129566
file in ../../data_method_rzn/evtgen/mcpass2_129567.pds physics event startrun beginrun endrun 
go
source rm mcpass2_129567
file in ../../data_method_rzn/evtgen/mcpass2_129568.pds physics event startrun beginrun endrun 
go
source rm mcpass2_129568
file in ../../data_method_rzn/evtgen/mcpass2_129572.pds physics event startrun beginrun endrun 
go
source rm mcpass2_129572
file in ../../data_method_rzn/evtgen/mcpass2_129573.pds physics event startrun beginrun endrun 
go
source rm mcpass2_129573
file in ../../data_method_rzn/evtgen/mcpass2_129574.pds physics event startrun beginrun endrun 
go
source rm mcpass2_129574
file in ../../data_method_rzn/evtgen/mcpass2_129575.pds physics event startrun beginrun endrun 
go
source rm mcpass2_129575
file in ../../data_method_rzn/evtgen/mcpass2_129576.pds physics event startrun beginrun endrun 
go
source rm mcpass2_129576
file in ../../data_method_rzn/evtgen/mcpass2_129579.pds physics event startrun beginrun endrun 
go
source rm mcpass2_129579
file in ../../data_method_rzn/evtgen/mcpass2_129580.pds physics event startrun beginrun endrun 
go
source rm mcpass2_129580
file in ../../data_method_rzn/evtgen/mcpass2_129582.pds physics event startrun beginrun endrun 
go
source rm mcpass2_129582
file in ../../data_method_rzn/evtgen/mcpass2_129591.pds physics event startrun beginrun endrun 
go
source rm mcpass2_129591
file in ../../data_method_rzn/evtgen/mcpass2_129607.pds physics event startrun beginrun endrun 
go
source rm mcpass2_129607
file in ../../data_method_rzn/evtgen/mcpass2_129611.pds physics event startrun beginrun endrun 
go
source rm mcpass2_129611
file in ../../data_method_rzn/evtgen/mcpass2_129617.pds physics event startrun beginrun endrun 
go
source rm mcpass2_129617
file in ../../data_method_rzn/evtgen/mcpass2_129618.pds physics event startrun beginrun endrun 
go
source rm mcpass2_129618
file in ../../data_method_rzn/evtgen/mcpass2_129619.pds physics event startrun beginrun endrun 
go
source rm mcpass2_129619
file in ../../data_method_rzn/evtgen/mcpass2_129620.pds physics event startrun beginrun endrun 
go
source rm mcpass2_129620
file in ../../data_method_rzn/evtgen/mcpass2_129623.pds physics event startrun beginrun endrun 
go
source rm mcpass2_129623
file in ../../data_method_rzn/evtgen/mcpass2_129626.pds physics event startrun beginrun endrun 
go
source rm mcpass2_129626
file in ../../data_method_rzn/evtgen/mcpass2_129629.pds physics event startrun beginrun endrun 
go
source rm mcpass2_129629
file in ../../data_method_rzn/evtgen/mcpass2_129731.pds physics event startrun beginrun endrun 
go
source rm mcpass2_129731
file in ../../data_method_rzn/evtgen/mcpass2_129764.pds physics event startrun beginrun endrun 
go
source rm mcpass2_129764
