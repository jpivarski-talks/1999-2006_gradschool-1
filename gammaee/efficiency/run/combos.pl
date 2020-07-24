#!/usr/local/bin/perl

%w = ();
$n = 0;

while (<>) {
    chop;
    $w{$n} = $_;
    $n++;
}

$mask = 1;
foreach $type ("hadron", "mupair", "CBSingleHi", "CESingleHi", "BarrelBhabha",
	       "EndcapBhabha", "ElTrack", "RadTau", "Pulser", "Random") {
    $this = 0;
    $total = 0;
    foreach $n (0..4095) {
	if (($n & $mask) > 0) {
	    $this += $w{$n};
	}
	$total += $w{$n};
    }
    print "$type: $this / $total\n";
    $mask = 2 * $mask;
}

# sol222% perl combos.pl < datal1combos.dat   |    sol222% perl combos.pl < mcl1combos.dat
# hadron: 681450 / 693337		      |    hadron: 4028554 / 4293924
# mupair: 541820 / 693337		      |    mupair: 3728114 / 4293924
# CBSingleHi: 0 / 693337		      |    CBSingleHi: 0 / 4293924
# CESingleHi: 0 / 693337		      |    CESingleHi: 0 / 4293924
# BarrelBhabha: 3614 / 693337		      |    BarrelBhabha: 78867 / 4293924
# EndcapBhabha: 943 / 693337		      |    EndcapBhabha: 9840 / 4293924
# ElTrack: 338385 / 693337		      |    ElTrack: 2284015 / 4293924
# RadTau: 667146 / 693337		      |    RadTau: 4192636 / 4293924
# Pulser: 0 / 693337			      |    Pulser: 0 / 4293924
# Random: 0 / 693337			      |    Random: 0 / 4293924











