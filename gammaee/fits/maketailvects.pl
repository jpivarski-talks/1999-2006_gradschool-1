#!/usr/local/bin/perl

opendir(DIR, "/cdat/tem/mccann/ccencounting_logs");
@dir = readdir(DIR);
closedir(DIR);

open(FAILURES, "> failed_runs.txt");

foreach $file (@dir) {
    next if $file !~ /r([0-9]{6})\.log/;
    $runnum = $1;
    next if -e "/cdat/tem/mccann/ccencounting_logs/tmp$runnum.log";
    $tailfile = "/cdat/dafe/mccann/fits/tails/tail$runnum.vec";
    next if -s $tailfile;

    print "Working on $runnum\n";
    open(FILE, "/cdat/tem/mccann/ccencounting_logs/$file");
    open(TAIL, "> $tailfile");
    $survived = 0;
    while ($line = <FILE>) {
	$survived = 1 if substr($line, 0, 38) eq " %% SYSTEM-Processor.CcenFailures: RUN";
	next if substr($line, 0, 4) ne "CCEN";
	next if $line !~ /^CCEN ([0-9\.]+)$/;

	print TAIL "$1\n";
    }
    close(TAIL);
    close(FILE);

    if (!$survived || -z $tailfile) {
	system("rm -f $tailfile");
	print FAILURES "$runnum\n";
    }
}
