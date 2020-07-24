#!/usr/local/bin/perl

$dataset = 16;
foreach $run ( 121887, 121875, 121868 ) {
    &make_file($dataset, $run);
}

$dataset = 17;
foreach $run ( 122249, 122247, 122536, 122564, 123010, 123020,
	       123193, 122576, 122608, 122673, 122567, 122575 ) {
    &make_file($dataset, $run);
}

$dataset = 18;
foreach $run ( 124527 ) {
    &make_file($dataset, $run);
}

$dataset = 21;
foreach $run ( 126252, 126274, 126649, 126673, 126831, 126858, 126915 ) {
    &make_file($dataset, $run);
}

sub make_file {
    (my $d, my $r) = @_;

    open(FILE, "> tf_$run.run");
    print FILE "#\$ -l calibration
#\$ -o /cdat/tem/mccann/tf_$run.out
#\$ -S /bin/bash
#\$ -j y

USER_DB=$d
export USER_DB
USER_RUN=$run
export USER_RUN

cd /home/mccann/super_hadrons/run
. /nfs/cleo3/scripts/cleo3defs
c3rel Nov04_02_P2

suez -f test_factor.tcl > /cdat/tem/mccann/tf_$run.log
";
    close(FILE);
}

