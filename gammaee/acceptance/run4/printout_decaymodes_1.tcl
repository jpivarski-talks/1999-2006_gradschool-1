default prompt off
exception continueEventLoop on

prod sel CustomBeamEnergyProd
param CustomBeamEnergyProd BeamEnergy 4.73015
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

file add pdschain ../remc3/y1s/Jun13_03_MC/mcpass2_123633.pds physics event beginrun startrun endrun
file add pdschain ../remc3/y1s/Jun13_03_MC/mcpass2_123635.pds physics event beginrun startrun endrun
file add pdschain ../remc3/y1s/Jun13_03_MC/mcpass2_123636.pds physics event beginrun startrun endrun
file add pdschain ../remc3/y1s/Jun13_03_MC/mcpass2_123637.pds physics event beginrun startrun endrun
file add pdschain ../remc3/y1s/Jun13_03_MC/mcpass2_123638.pds physics event beginrun startrun endrun
file add pdschain ../remc3/y1s/Jun13_03_MC/mcpass2_123639.pds physics event beginrun startrun endrun
file add pdschain ../remc3/y1s/Jun13_03_MC/mcpass2_123640.pds physics event beginrun startrun endrun
file add pdschain ../remc3/y1s/Jun13_03_MC/mcpass2_123641.pds physics event beginrun startrun endrun
file add pdschain ../remc3/y1s/Jun13_03_MC/mcpass2_123643.pds physics event beginrun startrun endrun
file add pdschain ../remc3/y1s/Jun13_03_MC/mcpass2_123644.pds physics event beginrun startrun endrun
file add pdschain ../remc3/y1s/Jun13_03_MC/mcpass2_123645.pds physics event beginrun startrun endrun
file add pdschain ../remc3/y1s/Jun13_03_MC/mcpass2_123646.pds physics event beginrun startrun endrun
file add pdschain ../remc3/y1s/Jun13_03_MC/mcpass2_123648.pds physics event beginrun startrun endrun
file add pdschain ../remc3/y1s/May12_03_MC/mcpass2_123651.pds physics event beginrun startrun endrun
file add pdschain ../remc3/y1s/May12_03_MC/mcpass2_123652.pds physics event beginrun startrun endrun
file add pdschain ../remc3/y1s/May12_03_MC/mcpass2_123653.pds physics event beginrun startrun endrun
file add pdschain ../remc3/y1s/May12_03_MC/mcpass2_123654.pds physics event beginrun startrun endrun
file add pdschain ../remc3/y1s/May12_03_MC/mcpass2_123656.pds physics event beginrun startrun endrun
file add pdschain ../remc3/y1s/May12_03_MC/mcpass2_123658.pds physics event beginrun startrun endrun
file add pdschain ../remc3/y1s/May12_03_MC/mcpass2_123659.pds physics event beginrun startrun endrun
file add pdschain ../remc3/y1s/May12_03_MC/mcpass2_123665.pds physics event beginrun startrun endrun
file add pdschain ../remc3/y1s/May12_03_MC/mcpass2_123670.pds physics event beginrun startrun endrun
file add pdschain ../remc3/y1s/May12_03_MC/mcpass2_123673.pds physics event beginrun startrun endrun
file add pdschain ../remc3/y1s/May12_03_MC/mcpass2_123674.pds physics event beginrun startrun endrun
file add pdschain ../remc3/y1s/May12_03_MC/mcpass2_123675.pds physics event beginrun startrun endrun
file add pdschain ../remc3/y1s/May12_03_MC/mcpass2_123678.pds physics event beginrun startrun endrun

go
exit
