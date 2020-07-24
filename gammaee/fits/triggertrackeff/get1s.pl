#!/usr/local/bin/perl

require("../grand_list.pl");

$cum_numer = 0;
$cum_denom = 0;
$cum_hist = (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

open(EFF17, "/cdat/tem/mccann/eff_17.log");
open(EFF18, "/cdat/tem/mccann/eff_18.log");
open(EFF19, "/cdat/tem/mccann/eff_19.log");

while (<EFF17>) {
    next if substr($_, 0, 40) ne " %% SYSTEM-Processor.HitEfficiency: RUN ";
    chop;
    $_ =~ /RUN ([0-9]{6}) eff = ([0-9]+) \/ ([0-9]+) trackshist ([0-9 ]+)/;
    $r = $1;
    next if $run{$r}->[0] != 1;
    $numer = $2;
    $denom = $3;
    @hist = split(' ', $4);

    $cum_numer += $numer;
    $cum_denom += $denom;
    foreach $i (0..29) {
	$cum_hist[$i] += $hist[$i];
    }
}

while (<EFF18>) {
    next if substr($_, 0, 40) ne " %% SYSTEM-Processor.HitEfficiency: RUN ";
    chop;
    $_ =~ /RUN ([0-9]{6}) eff = ([0-9]+) \/ ([0-9]+) trackshist ([0-9 ]+)/;
    $r = $1;
    next if $run{$r}->[0] != 1;
    $numer = $2;
    $denom = $3;
    @hist = split(' ', $4);

    $cum_numer += $numer;
    $cum_denom += $denom;
    foreach $i (0..29) {
	$cum_hist[$i] += $hist[$i];
    }
}

while (<EFF19>) {
    next if substr($_, 0, 40) ne " %% SYSTEM-Processor.HitEfficiency: RUN ";
    chop;
    $_ =~ /RUN ([0-9]{6}) eff = ([0-9]+) \/ ([0-9]+) trackshist ([0-9 ]+)/;
    $r = $1;
    next if $run{$r}->[0] != 1;
    $numer = $2;
    $denom = $3;
    @hist = split(' ', $4);

    $cum_numer += $numer;
    $cum_denom += $denom;
    foreach $i (0..29) {
	$cum_hist[$i] += $hist[$i];
    }
}

print "pt = N[$cum_numer / $cum_denom];\n";
print "pterr = Sqrt[pt * (1 - pt) / $cum_denom];\n";
$total = 0;
foreach $i (0..29) {
    $total += $cum_hist[$i];
}
foreach $i (0..29) {
    print "p[$i] = N[$cum_hist[$i] / $total];\n";
    print "perr[$i] = N[Sqrt[$cum_hist[$i]] / $total];\n";
}
