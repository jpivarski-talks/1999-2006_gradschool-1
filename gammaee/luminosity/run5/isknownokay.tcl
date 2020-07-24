default prompt off
exception continueEventLoop on

module sel CorbaModule
corba init
module sel RunStatisticsSourceModule
runstatistics in
module sel ConstantsModule
constants in $env(C3_CONST) standard CLEO3default
constants in $env(C3_CONST) meta BaseGeometry MetaListRetrieval

prod sel NavigationProd
prod sel TrackDeliveryProd
prod sel C3ccProd
param C3ccProd RequireRunGainsHotList false
prod sel MagFieldProd
prod sel EventPropertiesProd
prod sel EventTypeProd
prod sel CesrBeamEnergyProd

proc sel ../build_SunOS/shlib/IsKnownOkay

# module sel DBModule
# database in /nfs/cleo3/database/data16/db event startrun beginrun endrun
# database read_collection pass2

source_format sel PDSSourceFormat
source create pdschain
file add pdschain /cdat/dafe/mccann/acceptance/rzn3/raw122091.pds event beginrun startrun endrun
file add pdschain /cdat/dafe/mccann/acceptance/rzn3/raw122430.pds event beginrun startrun endrun
file add pdschain /cdat/dafe/mccann/acceptance/rzn3/raw123817.pds event beginrun startrun endrun
file add pdschain /cdat/dafe/mccann/acceptance/rzn3/raw125176.pds event beginrun startrun endrun
file add pdschain /cdat/dafe/mccann/acceptance/rzn3/raw126488.pds event beginrun startrun endrun
file add pdschain /cdat/dafe/mccann/acceptance/rzn3/raw130427.pds event beginrun startrun endrun
file add pdschain /cdat/dafe/mccann/acceptance/rzn4/raw121899.pds event beginrun startrun endrun
file add pdschain /cdat/dafe/mccann/acceptance/rzn4/raw121906.pds event beginrun startrun endrun
file add pdschain /cdat/dafe/mccann/acceptance/rzn4/raw122083.pds event beginrun startrun endrun
file add pdschain /cdat/dafe/mccann/acceptance/rzn4/raw122429.pds event beginrun startrun endrun
file add pdschain /cdat/dafe/mccann/acceptance/rzn4/raw122586.pds event beginrun startrun endrun
file add pdschain /cdat/dafe/mccann/acceptance/rzn4/raw122594.pds event beginrun startrun endrun
file add pdschain /cdat/dafe/mccann/acceptance/rzn4/raw122802.pds event beginrun startrun endrun
file add pdschain /cdat/dafe/mccann/acceptance/rzn5/raw121904.pds event beginrun startrun endrun
file add pdschain /cdat/dafe/mccann/acceptance/rzn5/raw122080.pds event beginrun startrun endrun
file add pdschain /cdat/dafe/mccann/acceptance/rzn5/raw122081.pds event beginrun startrun endrun
file add pdschain /cdat/dafe/mccann/acceptance/rzn5/raw122418.pds event beginrun startrun endrun
file add pdschain /cdat/dafe/mccann/acceptance/rzn5/raw122587.pds event beginrun startrun endrun
file add pdschain /cdat/dafe/mccann/acceptance/rzn5/raw122800.pds event beginrun startrun endrun
file add pdschain /cdat/dafe/mccann/acceptance/rzn5/raw126473.pds event beginrun startrun endrun
file add pdschain /cdat/dafe/mccann/acceptance/rzn5/raw126835.pds event beginrun startrun endrun
file add pdschain /cdat/dafe/mccann/acceptance/rzn5/raw129071.pds event beginrun startrun endrun
file add pdschain /cdat/dafe/mccann/acceptance/rzn5/raw129845.pds event beginrun startrun endrun
file add pdschain /cdat/dafe/mccann/acceptance/rzn5/raw129848.pds event beginrun startrun endrun
file add pdschain /cdat/dafe/mccann/acceptance/rzn4/raw121899_b.pds event beginrun startrun endrun

report level ERROR
go 1000
