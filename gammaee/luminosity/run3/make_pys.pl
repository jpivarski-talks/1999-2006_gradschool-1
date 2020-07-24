#!/usr/local/bin/perl

require("/home/mccann/fits/grand_list.pl");

foreach $r (keys %run) {
    open(LOG, "/cdat/tem/mccann/relativity_$r.log");
    open(PY, "> daf9/lumi2_$r.py");
    $pys = 0;
    print "run $r\n";
    while (<LOG>) {
	if ($_ =~ s/^PYTHON run\[$r\]/boing/) {
	    print PY $_;
	    $pys++;
	}
    }
    die "run $r is bad" if $pys != 1;
    close(LOG);
    close(PY);
}
