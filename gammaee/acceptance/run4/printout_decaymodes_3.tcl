default prompt off
exception continueEventLoop on

prod sel CustomBeamEnergyProd
param CustomBeamEnergyProd BeamEnergy 5.1776
param CustomBeamEnergyProd NoRunStat true
prod sel NavigationProd
prod sel TrackDeliveryProd
prod sel MagFieldProd
source_format sel BeamSpotFileSourceFormat
file in $env(C3_INFO)/mc/zeromc.beamspot beginrun

proc sel ../build_tmp/shlib/ReCuts
param ReCuts mode 3

source_format sel PDSSourceFormat
source create pdschain

file add pdschain ../remc3/y3s/Jun27_02_MC/mcpass2_121916.pds physics event beginrun startrun endrun
file add pdschain ../remc3/y3s/Jun27_02_MC/mcpass2_121917.pds physics event beginrun startrun endrun
file add pdschain ../remc3/y3s/Jun27_02_MC/mcpass2_121918.pds physics event beginrun startrun endrun
file add pdschain ../remc3/y3s/Jun27_02_MC/mcpass2_121920.pds physics event beginrun startrun endrun
file add pdschain ../remc3/y3s/Jun27_02_MC/mcpass2_121924.pds physics event beginrun startrun endrun
file add pdschain ../remc3/y3s/Jun27_02_MC/mcpass2_121925.pds physics event beginrun startrun endrun
file add pdschain ../remc3/y3s/Jun27_02_MC/mcpass2_121927.pds physics event beginrun startrun endrun
file add pdschain ../remc3/y3s/Jun27_02_MC/mcpass2_121928.pds physics event beginrun startrun endrun
file add pdschain ../remc3/y3s/Jun27_02_MC/mcpass2_121929.pds physics event beginrun startrun endrun
file add pdschain ../remc3/y3s/Jun27_02_MC/mcpass2_121930.pds physics event beginrun startrun endrun
file add pdschain ../remc3/y3s/Jun27_02_MC/mcpass2_121932.pds physics event beginrun startrun endrun
file add pdschain ../remc3/y3s/Jun27_02_MC/mcpass2_121933.pds physics event beginrun startrun endrun
file add pdschain ../remc3/y3s/Jun27_02_MC/mcpass2_121936.pds physics event beginrun startrun endrun
file add pdschain ../remc3/y3s/Jun27_02_MC/mcpass2_121939.pds physics event beginrun startrun endrun

go
exit
