default prompt off
exception continueEventLoop on

module sel LoadHbook4MModule
module sel HbookHistogramModule
hbook file ../rzn3/mcoldrel_y1s.rzn
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
param ShowersOnly eBeam 4.73015

#  proc sel ../build_OSF1/shlib/Cuts
#  param Cuts mcInfo true
#  param Cuts triggerInfo true

source_format sel PDSSourceFormat

file in ../remc3/y1s/Jun13_03_MC/mcpass2_123633.pds physics event beginrun startrun endrun
go
source rm mcpass2_123633

file in ../remc3/y1s/Jun13_03_MC/mcpass2_123639.pds physics event beginrun startrun endrun
go
source rm mcpass2_123639

file in ../remc3/y1s/Jun13_03_MC/mcpass2_123640.pds physics event beginrun startrun endrun
go
source rm mcpass2_123640

file in ../remc3/y1s/Jun13_03_MC/mcpass2_123645.pds physics event beginrun startrun endrun
go
source rm mcpass2_123645

file in ../remc3/y1s/Jun13_03_MC/mcpass2_123646.pds physics event beginrun startrun endrun
go
source rm mcpass2_123646

#  file in ../remc3/y1s/May12_03_MC/mcpass2_123651.pds physics event beginrun startrun endrun
#  go
#  source rm mcpass2_123651

file in ../remc3/y1s/May12_03_MC/mcpass2_123652.pds physics event beginrun startrun endrun
go
source rm mcpass2_123652

file in ../remc3/y1s/May12_03_MC/mcpass2_123653.pds physics event beginrun startrun endrun
go
source rm mcpass2_123653

file in ../remc3/y1s/May12_03_MC/mcpass2_123654.pds physics event beginrun startrun endrun
go
source rm mcpass2_123654

file in ../remc3/y1s/May12_03_MC/mcpass2_123658.pds physics event beginrun startrun endrun
go
source rm mcpass2_123658

file in ../remc3/y1s/May12_03_MC/mcpass2_123670.pds physics event beginrun startrun endrun
go
source rm mcpass2_123670

exit
