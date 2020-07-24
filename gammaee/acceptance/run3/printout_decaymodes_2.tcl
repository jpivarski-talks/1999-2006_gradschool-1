default prompt off
exception continueEventLoop on

prod sel CustomBeamEnergyProd
param CustomBeamEnergyProd BeamEnergy 5.01163
param CustomBeamEnergyProd NoRunStat true

proc sel ../build_SunOS/shlib/PrintOutDecayModes

source_format sel PDSSourceFormat
source create pdschain

file add pdschain ../mc/y2s/mcpass2_129535.pds physics event beginrun startrun endrun
file add pdschain ../mc/y2s/mcpass2_129536.pds physics event beginrun startrun endrun
file add pdschain ../mc/y2s/mcpass2_129538.pds physics event beginrun startrun endrun
file add pdschain ../mc/y2s/mcpass2_129539.pds physics event beginrun startrun endrun
file add pdschain ../mc/y2s/mcpass2_129540.pds physics event beginrun startrun endrun
file add pdschain ../mc/y2s/mcpass2_129541.pds physics event beginrun startrun endrun
file add pdschain ../mc/y2s/mcpass2_129574.pds physics event beginrun startrun endrun
file add pdschain ../mc/y2s/mcpass2_129575.pds physics event beginrun startrun endrun
file add pdschain ../mc/y2s/mcpass2_129576.pds physics event beginrun startrun endrun
file add pdschain ../mc/y2s/mcpass2_129579.pds physics event beginrun startrun endrun
file add pdschain ../mc/y2s/mcpass2_129580.pds physics event beginrun startrun endrun
file add pdschain ../mc/y2s/mcpass2_129582.pds physics event beginrun startrun endrun
file add pdschain ../mc/y2s/mcpass2_129591.pds physics event beginrun startrun endrun
file add pdschain ../mc/y2s/mcpass2_129607.pds physics event beginrun startrun endrun
file add pdschain ../mc/y2s/mcpass2_129611.pds physics event beginrun startrun endrun
file add pdschain ../mc/y2s/mcpass2_129617.pds physics event beginrun startrun endrun
file add pdschain ../mc/y2s/mcpass2_129618.pds physics event beginrun startrun endrun
file add pdschain ../mc/y2s/mcpass2_129619.pds physics event beginrun startrun endrun
file add pdschain ../mc/y2s/mcpass2_129620.pds physics event beginrun startrun endrun
file add pdschain ../mc/y2s/mcpass2_129623.pds physics event beginrun startrun endrun
file add pdschain ../mc/y2s/mcpass2_129626.pds physics event beginrun startrun endrun
file add pdschain ../mc/y2s/mcpass2_129629.pds physics event beginrun startrun endrun
file add pdschain ../mc/y2s/mcpass2_129630.pds physics event beginrun startrun endrun
file add pdschain ../mc/y2s/mcpass2_129631.pds physics event beginrun startrun endrun
file add pdschain ../mc/y2s/mcpass2_129632.pds physics event beginrun startrun endrun

go
exit
