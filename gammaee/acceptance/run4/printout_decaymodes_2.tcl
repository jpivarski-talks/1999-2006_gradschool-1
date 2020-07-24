default prompt off
exception continueEventLoop on

prod sel CustomBeamEnergyProd
param CustomBeamEnergyProd BeamEnergy 5.01163
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

file add pdschain ../remc3/y2s/Apr16_03_MC/mcpass2_129535.pds physics event beginrun startrun endrun
file add pdschain ../remc3/y2s/Apr16_03_MC/mcpass2_129536.pds physics event beginrun startrun endrun
file add pdschain ../remc3/y2s/Apr16_03_MC/mcpass2_129538.pds physics event beginrun startrun endrun
file add pdschain ../remc3/y2s/Apr16_03_MC/mcpass2_129539.pds physics event beginrun startrun endrun
file add pdschain ../remc3/y2s/Apr16_03_MC/mcpass2_129540.pds physics event beginrun startrun endrun
file add pdschain ../remc3/y2s/Apr16_03_MC/mcpass2_129541.pds physics event beginrun startrun endrun
file add pdschain ../remc3/y2s/Apr16_03_MC/mcpass2_129545.pds physics event beginrun startrun endrun
file add pdschain ../remc3/y2s/Apr16_03_MC/mcpass2_129549.pds physics event beginrun startrun endrun
file add pdschain ../remc3/y2s/Apr16_03_MC/mcpass2_129550.pds physics event beginrun startrun endrun
file add pdschain ../remc3/y2s/Apr16_03_MC/mcpass2_129551.pds physics event beginrun startrun endrun
file add pdschain ../remc3/y2s/Apr16_03_MC/mcpass2_129552.pds physics event beginrun startrun endrun
file add pdschain ../remc3/y2s/Apr16_03_MC/mcpass2_129553.pds physics event beginrun startrun endrun
file add pdschain ../remc3/y2s/Apr16_03_MC/mcpass2_129566.pds physics event beginrun startrun endrun
file add pdschain ../remc3/y2s/Jun13_03_MC/mcpass2_129618.pds physics event beginrun startrun endrun
file add pdschain ../remc3/y2s/Jun13_03_MC/mcpass2_129619.pds physics event beginrun startrun endrun
file add pdschain ../remc3/y2s/Jun13_03_MC/mcpass2_129620.pds physics event beginrun startrun endrun
file add pdschain ../remc3/y2s/Jun13_03_MC/mcpass2_129623.pds physics event beginrun startrun endrun
file add pdschain ../remc3/y2s/Jun13_03_MC/mcpass2_129626.pds physics event beginrun startrun endrun
file add pdschain ../remc3/y2s/Jun13_03_MC/mcpass2_129629.pds physics event beginrun startrun endrun
file add pdschain ../remc3/y2s/Jun13_03_MC/mcpass2_129630.pds physics event beginrun startrun endrun
file add pdschain ../remc3/y2s/Jun13_03_MC/mcpass2_129631.pds physics event beginrun startrun endrun
file add pdschain ../remc3/y2s/Jun13_03_MC/mcpass2_129632.pds physics event beginrun startrun endrun
file add pdschain ../remc3/y2s/Jun13_03_MC/mcpass2_129633.pds physics event beginrun startrun endrun
file add pdschain ../remc3/y2s/Jun13_03_MC/mcpass2_129635.pds physics event beginrun startrun endrun
file add pdschain ../remc3/y2s/Jun13_03_MC/mcpass2_129637.pds physics event beginrun startrun endrun
file add pdschain ../remc3/y2s/Jun13_03_MC/mcpass2_129638.pds physics event beginrun startrun endrun
file add pdschain ../remc3/y2s/Jun13_03_MC/mcpass2_129641.pds physics event beginrun startrun endrun

go
exit
