default prompt off
exception continueEventLoop on

module sel LoadHbook4MModule
module sel HbookHistogramModule
hbook file ../rzn3/mcoldrel_y2s.rzn
hbook init

#  module sel CorbaModule
#  corba init
#  module sel RunStatisticsSourceModule
#  runstatistics in
#  module sel ConstantsModule
#  constants in $env(C3_CONST) standard CLEO3default streams superconductingquad magfudge
#  constants in $env(C3_CONST) meta BaseGeometry MetaListRetrieval

#  prod sel NavigationProd
#  prod sel TrackDeliveryProd
#  prod sel C3ccProd
#  param C3ccProd RequireRunGainsHotList false
#  prod sel MagFieldProd
#  prod sel EventPropertiesProd
#  prod sel EventTypeProd
#  prod sel CesrBeamEnergyProd

#  source_format sel BeamSpotFileSourceFormat
#  file in $env(C3_INFO)/mc/zeromc.beamspot beginrun
#  run_file $env(C3_SCRIPTS)/CcHotList.tcl

proc sel ../build_OSF1/shlib/ShowersOnly
param ShowersOnly eBeam 5.01163

#  proc sel ../build_OSF1/shlib/Cuts
#  param Cuts mcInfo true
#  param Cuts triggerInfo true

source_format sel PDSSourceFormat

file in ../remc3/y2s/Apr16_03_MC/mcpass2_129545.pds physics event beginrun startrun endrun
go
source rm mcpass2_129545

#  file in ../remc3/y2s/Apr16_03_MC/mcpass2_129549.pds physics event beginrun startrun endrun
#  go
#  source rm mcpass2_129549

file in ../remc3/y2s/Apr16_03_MC/mcpass2_129551.pds physics event beginrun startrun endrun
go
source rm mcpass2_129551

#  file in ../remc3/y2s/Apr16_03_MC/mcpass2_129552.pds physics event beginrun startrun endrun
#  go
#  source rm mcpass2_129552

file in ../remc3/y2s/Apr16_03_MC/mcpass2_129566.pds physics event beginrun startrun endrun
go
source rm mcpass2_129566

#  file in ../remc3/y2s/Jun13_03_MC/mcpass2_129618.pds physics event beginrun startrun endrun
#  go
#  source rm mcpass2_129618

file in ../remc3/y2s/Jun13_03_MC/mcpass2_129620.pds physics event beginrun startrun endrun
go
source rm mcpass2_129620

file in ../remc3/y2s/Jun13_03_MC/mcpass2_129623.pds physics event beginrun startrun endrun
go
source rm mcpass2_129623

file in ../remc3/y2s/Jun13_03_MC/mcpass2_129626.pds physics event beginrun startrun endrun
go
source rm mcpass2_129626

file in ../remc3/y2s/Jun13_03_MC/mcpass2_129629.pds physics event beginrun startrun endrun
go
source rm mcpass2_129629

file in ../remc3/y2s/Jun13_03_MC/mcpass2_129631.pds physics event beginrun startrun endrun
go
source rm mcpass2_129631

file in ../remc3/y2s/Jun13_03_MC/mcpass2_129635.pds physics event beginrun startrun endrun
go
source rm mcpass2_129635

file in ../remc3/y2s/Jun13_03_MC/mcpass2_129637.pds physics event beginrun startrun endrun
go
source rm mcpass2_129637

file in ../remc3/y2s/Jun13_03_MC/mcpass2_129638.pds physics event beginrun startrun endrun
go
source rm mcpass2_129638

file in ../remc3/y2s/Apr16_03_MC/mcpass2_129539.pds physics event beginrun startrun endrun
go
source rm mcpass2_129539

exit
