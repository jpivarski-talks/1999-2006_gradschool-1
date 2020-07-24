#!/usr/local/bin/perl

%lumi = ();
%lumi_err = ();
%lumi_sys = ();
while ($run = <>) {
    chop($run);
    $lumi{$run} = "na";
    $lumi_err{$run} = "na";
    $lumi_sys{$run} = "na";
}

$sum = 0;
$sum2 = 0;
open(RUNINFO, "/nfs/cleo3/Offline/InfoFiles/data/runinfo.runinfo");
while ($line = <RUNINFO>) {
    chop($line);

    ($space, $run, $nevents, $nhads, $last,
     $bhalum, $bhalum_err, $bhalum_sys,
     $ebmcor, $ebmunc, $bfieldcor, $bfieldunc,
     $gglum, $gglum_err, $gglum_sys,
     $dataset) = split(/\s+/, $line);

    if (defined($lumi{$run})) {
	$lumi{$run} = $gglum;
	$lumi_err{$run} = $gglum_err;
	$lumi_sys{$run} = $gglum_sys;

	$sum += $lumi{$run};
	$sum2 += $lumi_err{$run} * $lumi_err{$run};

	print "$run $lumi{$run} $lumi_err{$run} $lumi_sys{$run}\n";
    }
}
close(RUNINFO);

$allok = 1;
foreach $run (keys %lumi) {
    if ($lumi{$run} eq "na") {
	$allok = 0;
	print "$run $lumi{$run} $lumi_err{$run} $lumi_sys{$run}\n";
    }
}

if ($allok == 1) {
    $sum2 = sqrt($sum2);
    print "==========================================
       $sum +/- $sum2
";
}
