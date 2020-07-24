default prompt off
exception continueEventLoop on

prod sel CustomBeamEnergyProd
param CustomBeamEnergyProd BeamEnergy 4.73015
param CustomBeamEnergyProd NoRunStat true

proc sel ../build_SunOS/shlib/PrintOutDecayModes

source_format sel PDSSourceFormat
source create pdschain

file add pdschain ../mc/y1s/mcpass2_123610.pds physics event beginrun startrun endrun
file add pdschain ../mc/y1s/mcpass2_123611.pds physics event beginrun startrun endrun
file add pdschain ../mc/y1s/mcpass2_123612.pds physics event beginrun startrun endrun
file add pdschain ../mc/y1s/mcpass2_123615.pds physics event beginrun startrun endrun
file add pdschain ../mc/y1s/mcpass2_123616.pds physics event beginrun startrun endrun
file add pdschain ../mc/y1s/mcpass2_123617.pds physics event beginrun startrun endrun
file add pdschain ../mc/y1s/mcpass2_123618.pds physics event beginrun startrun endrun
file add pdschain ../mc/y1s/mcpass2_123619.pds physics event beginrun startrun endrun
file add pdschain ../mc/y1s/mcpass2_123620.pds physics event beginrun startrun endrun
file add pdschain ../mc/y1s/mcpass2_123621.pds physics event beginrun startrun endrun
file add pdschain ../mc/y1s/mcpass2_123623.pds physics event beginrun startrun endrun
file add pdschain ../mc/y1s/mcpass2_123624.pds physics event beginrun startrun endrun
file add pdschain ../mc/y1s/mcpass2_123631.pds physics event beginrun startrun endrun
file add pdschain ../mc/y1s/mcpass2_123632.pds physics event beginrun startrun endrun
file add pdschain ../mc/y1s/mcpass2_123633.pds physics event beginrun startrun endrun
file add pdschain ../mc/y1s/mcpass2_123635.pds physics event beginrun startrun endrun
file add pdschain ../mc/y1s/mcpass2_123636.pds physics event beginrun startrun endrun
file add pdschain ../mc/y1s/mcpass2_123637.pds physics event beginrun startrun endrun
file add pdschain ../mc/y1s/mcpass2_123638.pds physics event beginrun startrun endrun
file add pdschain ../mc/y1s/mcpass2_123639.pds physics event beginrun startrun endrun
file add pdschain ../mc/y1s/mcpass2_123640.pds physics event beginrun startrun endrun
file add pdschain ../mc/y1s/mcpass2_123641.pds physics event beginrun startrun endrun
file add pdschain ../mc/y1s/mcpass2_123643.pds physics event beginrun startrun endrun
file add pdschain ../mc/y1s/mcpass2_123644.pds physics event beginrun startrun endrun
file add pdschain ../mc/y1s/mcpass2_123645.pds physics event beginrun startrun endrun

go
exit
