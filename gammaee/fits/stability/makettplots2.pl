#!/usr/local/bin/perl

require("tt.pl");
require("../gglumi.pl");
require("../grand_list.pl");

$n = 1;
foreach $which (1..3) {
    if ($which == 1) { $clum = 183343 }
    elsif ($which == 2) { $clum = 358181 }
    elsif ($which == 3) { $clum = 94739 }

    if ($which == 1) { $cnumer = 50416 }
    elsif ($which == 2) { $cnumer = 92637 }
    elsif ($which == 3) { $cnumer = 23100 }

    if ($which == 1) { $cdenom = 54952 }
    elsif ($which == 2) { $cdenom = 100703 }
    elsif ($which == 3) { $cdenom = 25252 }

    $ptoc = 0;
    $numer = 0;
    $denom = 0;

    $firstr = 0;

    foreach $r (sort numly %run) {
	next if ($run{$r}->[0] != $which);
	next if $run{$r}->[2] eq "cont";

	$firstr = $r if $firstr == 0;

	$ptoc += $lumi{$r}/$clum;
	$numer += $ttnumer{$r};
	$denom += $ttdenom{$r};

	if ($denom > 5000) {
	    $frac = ($numer - $ptoc * $cnumer) / ($denom - $ptoc * $cdenom);
	    print "$n $frac\n";

	    $ptoc = 0;
	    $numer = 0;
	    $denom = 0;

	    $n++;
	    warn "runs $firstr - $r have $frac" if ($frac < 0.95 || $frac > 1.03);
	    $firstr = 0;
	}
    }
    warn $n;
}

sub sqr { $_[0] * $_[0] };
