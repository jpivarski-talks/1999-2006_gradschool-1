default prompt off
exception continueEventLoop on

module sel LoadHbook4MModule
module sel HbookHistogramModule
hbook file ../data_method_rzn/y2segmcother_trigger.rzn
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

proc sel ../build_SunOS/shlib/Cuts
param Cuts usingEvtGen true

source_format sel PDSSourceFormat
source create pdschain
file add pdschain ../data_method_rzn/evtgen/y2s/mcpass2_129535.pds event physics startrun beginrun endrun
file add pdschain ../data_method_rzn/evtgen/y2s/mcpass2_129536.pds event physics startrun beginrun endrun
file add pdschain ../data_method_rzn/evtgen/y2s/mcpass2_129538.pds event physics startrun beginrun endrun
file add pdschain ../data_method_rzn/evtgen/y2s/mcpass2_129539.pds event physics startrun beginrun endrun
file add pdschain ../data_method_rzn/evtgen/y2s/mcpass2_129540.pds event physics startrun beginrun endrun
file add pdschain ../data_method_rzn/evtgen/y2s/mcpass2_129541.pds event physics startrun beginrun endrun
file add pdschain ../data_method_rzn/evtgen/y2s/mcpass2_129545.pds event physics startrun beginrun endrun
file add pdschain ../data_method_rzn/evtgen/y2s/mcpass2_129549.pds event physics startrun beginrun endrun
file add pdschain ../data_method_rzn/evtgen/y2s/mcpass2_129550.pds event physics startrun beginrun endrun
file add pdschain ../data_method_rzn/evtgen/y2s/mcpass2_129551.pds event physics startrun beginrun endrun
file add pdschain ../data_method_rzn/evtgen/y2s/mcpass2_129552.pds event physics startrun beginrun endrun
file add pdschain ../data_method_rzn/evtgen/y2s/mcpass2_129553.pds event physics startrun beginrun endrun
file add pdschain ../data_method_rzn/evtgen/y2s/mcpass2_129564.pds event physics startrun beginrun endrun
file add pdschain ../data_method_rzn/evtgen/y2s/mcpass2_129566.pds event physics startrun beginrun endrun
file add pdschain ../data_method_rzn/evtgen/y2s/mcpass2_129567.pds event physics startrun beginrun endrun
file add pdschain ../data_method_rzn/evtgen/y2s/mcpass2_129568.pds event physics startrun beginrun endrun
file add pdschain ../data_method_rzn/evtgen/y2s/mcpass2_129572.pds event physics startrun beginrun endrun
file add pdschain ../data_method_rzn/evtgen/y2s/mcpass2_129573.pds event physics startrun beginrun endrun
file add pdschain ../data_method_rzn/evtgen/y2s/mcpass2_129574.pds event physics startrun beginrun endrun
file add pdschain ../data_method_rzn/evtgen/y2s/mcpass2_129575.pds event physics startrun beginrun endrun
file add pdschain ../data_method_rzn/evtgen/y2s/mcpass2_129576.pds event physics startrun beginrun endrun
file add pdschain ../data_method_rzn/evtgen/y2s/mcpass2_129579.pds event physics startrun beginrun endrun
file add pdschain ../data_method_rzn/evtgen/y2s/mcpass2_129580.pds event physics startrun beginrun endrun
file add pdschain ../data_method_rzn/evtgen/y2s/mcpass2_129582.pds event physics startrun beginrun endrun
file add pdschain ../data_method_rzn/evtgen/y2s/mcpass2_129591.pds event physics startrun beginrun endrun
file add pdschain ../data_method_rzn/evtgen/y2s/mcpass2_129607.pds event physics startrun beginrun endrun
file add pdschain ../data_method_rzn/evtgen/y2s/mcpass2_129611.pds event physics startrun beginrun endrun
file add pdschain ../data_method_rzn/evtgen/y2s/mcpass2_129617.pds event physics startrun beginrun endrun
file add pdschain ../data_method_rzn/evtgen/y2s/mcpass2_129618.pds event physics startrun beginrun endrun
file add pdschain ../data_method_rzn/evtgen/y2s/mcpass2_129619.pds event physics startrun beginrun endrun
file add pdschain ../data_method_rzn/evtgen/y2s/mcpass2_129620.pds event physics startrun beginrun endrun
file add pdschain ../data_method_rzn/evtgen/y2s/mcpass2_129623.pds event physics startrun beginrun endrun
file add pdschain ../data_method_rzn/evtgen/y2s/mcpass2_129626.pds event physics startrun beginrun endrun
file add pdschain ../data_method_rzn/evtgen/y2s/mcpass2_129629.pds event physics startrun beginrun endrun

go
