#!/usr/local/bin/perl

open(RUNINFO, "/nfs/cleo3/Offline/InfoFiles/data/runinfo.runinfo");
while ($line = <RUNINFO>) {
    chop($line);

    ($space, $run, $nevents, $nhads, $last,
     $bhalum, $bhalum_err, $bhalum_sys,
     $ebmcor, $ebmunc, $bfieldcor, $bfieldunc,
     $gglum, $gglum_err, $gglum_sys,
     $dataset) = split(/\s+/, $line);

    last if ($run == $ARGV[0]);
}

open(IN, $ARGV[1]);
$line = <IN>;  die if $line ne "IDXA\n";
$line = <IN>;  die if $line ne "1\n";
$line = <IN>;  die if $line ne "event\n";
$line = <IN>;  die if $line ne "IDXD\n";
open(OUT, "> $ARGV[2]");
print OUT "IDXA
1
event
IDXD
";
$e = 1;
while ($line = <IN>) {
    chop($line);
    ($one, $run, $event, $zero) = split(/\s+/, $line);
    die if $one ne "1";
    die if $run ne $ARGV[0];
    die if $zero ne "0";

    while ($event > $e) {
	print OUT "1 $ARGV[0] $e 0\n";
	$e++;
    }
    $e++;
}
die if ($e > ($last+1));
while ($e <= $last) {
    print OUT "1 $ARGV[0] $e 0\n";
    $e++;
}
