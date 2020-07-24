default prompt off
exception continueEventLoop on

prod sel CustomBeamEnergyProd
param CustomBeamEnergyProd BeamEnergy 5.1776
param CustomBeamEnergyProd NoRunStat true

proc sel ../build_SunOS/shlib/PrintOutDecayModes

source_format sel PDSSourceFormat
source create pdschain

file add pdschain ../mc/y3s/mcpass2_121916.pds physics event beginrun startrun endrun
file add pdschain ../mc/y3s/mcpass2_121917.pds physics event beginrun startrun endrun
file add pdschain ../mc/y3s/mcpass2_121918.pds physics event beginrun startrun endrun
file add pdschain ../mc/y3s/mcpass2_121920.pds physics event beginrun startrun endrun
file add pdschain ../mc/y3s/mcpass2_121924.pds physics event beginrun startrun endrun
file add pdschain ../mc/y3s/mcpass2_121925.pds physics event beginrun startrun endrun
file add pdschain ../mc/y3s/mcpass2_121927.pds physics event beginrun startrun endrun
file add pdschain ../mc/y3s/mcpass2_121928.pds physics event beginrun startrun endrun
file add pdschain ../mc/y3s/mcpass2_121929.pds physics event beginrun startrun endrun
file add pdschain ../mc/y3s/mcpass2_121930.pds physics event beginrun startrun endrun
file add pdschain ../mc/y3s/mcpass2_121932.pds physics event beginrun startrun endrun
file add pdschain ../mc/y3s/mcpass2_121933.pds physics event beginrun startrun endrun
file add pdschain ../mc/y3s/mcpass2_121936.pds physics event beginrun startrun endrun
file add pdschain ../mc/y3s/mcpass2_121939.pds physics event beginrun startrun endrun
file add pdschain ../mc/y3s/mcpass2_121940.pds physics event beginrun startrun endrun
file add pdschain ../mc/y3s/mcpass2_121943.pds physics event beginrun startrun endrun
file add pdschain ../mc/y3s/mcpass2_121944.pds physics event beginrun startrun endrun
file add pdschain ../mc/y3s/mcpass2_121946.pds physics event beginrun startrun endrun
file add pdschain ../mc/y3s/mcpass2_121948.pds physics event beginrun startrun endrun
file add pdschain ../mc/y3s/mcpass2_121949.pds physics event beginrun startrun endrun
file add pdschain ../mc/y3s/mcpass2_121950.pds physics event beginrun startrun endrun
file add pdschain ../mc/y3s/mcpass2_121951.pds physics event beginrun startrun endrun
file add pdschain ../mc/y3s/mcpass2_121952.pds physics event beginrun startrun endrun
file add pdschain ../mc/y3s/mcpass2_121953.pds physics event beginrun startrun endrun
file add pdschain ../mc/y3s/mcpass2_121962.pds physics event beginrun startrun endrun

go
exit
