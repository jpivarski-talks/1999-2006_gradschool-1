default prompt off
exception continueEventLoop on

run_file $env(C3_SCRIPTS)/runOnPass2.tcl
proc sel ../build_SunOS/shlib/GetWayOutEvents
run_file $env(C3_SCRIPTS)/viewTrackFitter.tcl

source_format sel PDSSourceFormat
source create pdschain

# no-beam
file add pdschain /cdat/dafe/mccann/neweff/rzn/cosmic/r128706.pds event beginrun startrun endrun
file add pdschain /cdat/dafe/mccann/neweff/rzn/cosmic/r128736.pds event beginrun startrun endrun
file add pdschain /cdat/dafe/mccann/neweff/rzn/cosmic/r128741.pds event beginrun startrun endrun
file add pdschain /cdat/dafe/mccann/neweff/rzn/cosmic/r128746.pds event beginrun startrun endrun
file add pdschain /cdat/dafe/mccann/neweff/rzn/cosmic/r128748.pds event beginrun startrun endrun
file add pdschain /cdat/dafe/mccann/neweff/rzn/cosmic/r128750.pds event beginrun startrun endrun
file add pdschain /cdat/dafe/mccann/neweff/rzn/cosmic/r128751.pds event beginrun startrun endrun

# # electron single-beam
# file add pdschain /cdat/dafe/mccann/neweff/rzn/beamgas_neg/r126828.pds event beginrun startrun endrun
# file add pdschain /cdat/dafe/mccann/neweff/rzn/beamgas_neg/r126920.pds event beginrun startrun endrun
# file add pdschain /cdat/dafe/mccann/neweff/rzn/beamgas_neg/r126922.pds event beginrun startrun endrun
# file add pdschain /cdat/dafe/mccann/neweff/rzn/beamgas_neg/r127014.pds event beginrun startrun endrun

go
