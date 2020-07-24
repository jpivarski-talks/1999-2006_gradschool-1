#!/usr/local/bin/perl

%dirs = ("y1s" , ["apr02-02", "apr08-02", "feb06-02", "feb14-02", "feb20-02", "feb28-02", "jan16-02",
		  "jan30-02", "mar06-02", "mar14-02", "mar21-02"],
	 "y2s" , ["aug07-02", "jul11-02", "jul24-02", "jun11-02", "jun28-02", "may28-02", "nov04-02",
		  "oct22-02", "sep29-02"],
	 "y3s" , ["dec06-01", "dec13-01", "dec20-01", "dec25-01", "jan03-02", "jan10-02", "nov29-01"]);

foreach $res ("y1s", "y2s", "y3s") {
    foreach $dir (@{$dirs{$res}}) {
	foreach $type ("scan", "cont", "peak", "high") {
	    if (-e "/home/mccann/super_hadrons/final_peakfits/$res/$dir/$type.num") {
		open(RUNS, "/home/mccann/super_hadrons/final_peakfits/$res/$dir/$type.num");
		@runs = ();
		while (my $line = <RUNS>) {
		    chop($line);
		    (my $run, $num, $err) = split(/\s+/, $line);
		    push(@runs, $run);
		}

		if ($#runs > 0) {
		    open(TCL, "> $res-$dir-$type.tcl");
		    print TCL "default prompt off
exception continueEventLoop on

module sel HbookHistogramModule
hbook file /cdat/sol300/disk5/mccann/$res-$dir-$type.rzn
hbook init

run_file \$env(C3_SCRIPTS)/runOnPass2.tcl

prod sel EventPropertiesProd
prod sel EventTypeProd
prod sel CesrBeamEnergyProd
prod sel DBEventHeaderProd

prod sel MCInfoDelivery
prod desel MCInfoDelivery
prod sel MCTagHolderProd
prod desel MCTagHolderProd

source_format sel BeamSpotFileSourceFormat
file in \$env(C3_INFO)/data/beamspot.beamspot beginrun

proc sel ../build_SunOS/shlib/Efficiency.so
param Efficiency isMC false

proc sel ../build_SunOS/shlib/TrackEfficiency.so
param TrackEfficiency isMC false
";

		    foreach my $run (@runs) {
			my $db;
			if ($run >= 121339  &&  $run <= 122179) {
			    $db = 16;
			} elsif ($run >= 122245  &&  $run <= 123304) {
			    $db = 17;
			} elsif ($run >= 123314  &&  $run <= 124575) {
			    $db = 18;
			} elsif ($run >= 124624  &&  $run <= 125416) {
			    $db = 19;
			} elsif ($run >= 125428  &&  $run <= 126206) {
			    $db = 20;
			} elsif ($run >= 126252  &&  $run <= 127545) {
			    $db = 21;
			} elsif ($run >= 127550  &&  $run <= 128401) {
			    $db = 22;
			} elsif ($run >= 128684  &&  $run <= 129223) {
			    $db = 23;
			} elsif ($run >= 129519  &&  $run <= 129865) {
			    $db = 25;
			} elsif ($run >= 130198  &&  $run <= 130630) {
			    $db = 27;
			} else {
			    die "where did $run come from?!?";
			}

			print TCL "
module sel DBModule
database in /nfs/cleo3/database/data$db/db event startrun beginrun endrun
database read_collection pass2 hadron
database run $run
go
";
		    } # end database run $run
			close(TCL);
			open(RUN, "> $res-$dir-$type.run");
			print RUN "#\$ -l calibration
#\$ -o /cdat/tem/mccann/$res-$dir-$type.log
#\$ -S /bin/bash
#\$ -j y

cd /home/mccann/efficiency/run
. /nfs/cleo3/scripts/cleo3defs
c3rel Apr18_03_P2

suez -f $res-$dir-$type.tcl
";
			close(RUN);
		} # end if @runs is nonempty
	    } # end if res-dir-type exists
	} # end loop over types
    } # end loop over directories
} # end loop over resonances
