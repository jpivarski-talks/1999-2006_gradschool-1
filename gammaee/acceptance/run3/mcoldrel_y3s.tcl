default prompt off
exception continueEventLoop on

module sel LoadHbook4MModule
module sel HbookHistogramModule
hbook file ../rzn3/mcoldrel_y3s.rzn
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
param ShowersOnly eBeam 5.1776

#  proc sel ../build_OSF1/shlib/Cuts
#  param Cuts mcInfo true
#  param Cuts triggerInfo true

source_format sel PDSSourceFormat

file in ../remc3/y3s/Jun27_02_MC/mcpass2_121916.pds physics event beginrun startrun endrun
go
source rm mcpass2_121916

file in ../remc3/y3s/Jun27_02_MC/mcpass2_121917.pds physics event beginrun startrun endrun
go
source rm mcpass2_121917

file in ../remc3/y3s/Jun27_02_MC/mcpass2_121918.pds physics event beginrun startrun endrun
go
source rm mcpass2_121918

file in ../remc3/y3s/Jun27_02_MC/mcpass2_121924.pds physics event beginrun startrun endrun
go
source rm mcpass2_121924

file in ../remc3/y3s/Jun27_02_MC/mcpass2_121927.pds physics event beginrun startrun endrun
go
source rm mcpass2_121927

file in ../remc3/y3s/Jun27_02_MC/mcpass2_121928.pds physics event beginrun startrun endrun
go
source rm mcpass2_121928

file in ../remc3/y3s/Jun27_02_MC/mcpass2_121930.pds physics event beginrun startrun endrun
go
source rm mcpass2_121930

file in ../remc3/y3s/Jun27_02_MC/mcpass2_121932.pds physics event beginrun startrun endrun
go
source rm mcpass2_121932

file in ../remc3/y3s/Jun27_02_MC/mcpass2_121939.pds physics event beginrun startrun endrun
go
source rm mcpass2_121939

exit
