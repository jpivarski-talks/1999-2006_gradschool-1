#!/usr/local/bin/perl

require("../grand_list.pl");

$cum_numer = 0;
$cum_denom = 0;
$cum_hist = (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

open(EFF20, "/cdat/tem/mccann/eff_20.log");
open(EFF21, "/cdat/tem/mccann/eff_21.log");
open(EFF22, "/cdat/tem/mccann/eff_22.log");
open(EFF23, "/cdat/tem/mccann/eff_23.log");
open(EFF25, "/cdat/tem/mccann/eff_25.log");
open(EFF27, "/cdat/tem/mccann/eff_27.log");

while (<EFF20>) {
    next if substr($_, 0, 40) ne " %% SYSTEM-Processor.HitEfficiency: RUN ";
    chop;
    $_ =~ /RUN ([0-9]{6}) eff = ([0-9]+) \/ ([0-9]+) trackshist ([0-9 ]+)/;
    $r = $1;
    next if $run{$r}->[0] != 2;
    $numer = $2;
    $denom = $3;
    @hist = split(' ', $4);

    $cum_numer += $numer;
    $cum_denom += $denom;
    foreach $i (0..29) {
	$cum_hist[$i] += $hist[$i];
    }
}

while (<EFF21>) {
    next if substr($_, 0, 40) ne " %% SYSTEM-Processor.HitEfficiency: RUN ";
    chop;
    $_ =~ /RUN ([0-9]{6}) eff = ([0-9]+) \/ ([0-9]+) trackshist ([0-9 ]+)/;
    $r = $1;
    next if $run{$r}->[0] != 2;
    $numer = $2;
    $denom = $3;
    @hist = split(' ', $4);

    $cum_numer += $numer;
    $cum_denom += $denom;
    foreach $i (0..29) {
	$cum_hist[$i] += $hist[$i];
    }
}

while (<EFF22>) {
    next if substr($_, 0, 40) ne " %% SYSTEM-Processor.HitEfficiency: RUN ";
    chop;
    $_ =~ /RUN ([0-9]{6}) eff = ([0-9]+) \/ ([0-9]+) trackshist ([0-9 ]+)/;
    $r = $1;
    next if $run{$r}->[0] != 2;
    $numer = $2;
    $denom = $3;
    @hist = split(' ', $4);

    $cum_numer += $numer;
    $cum_denom += $denom;
    foreach $i (0..29) {
	$cum_hist[$i] += $hist[$i];
    }
}

while (<EFF23>) {
    next if substr($_, 0, 40) ne " %% SYSTEM-Processor.HitEfficiency: RUN ";
    chop;
    $_ =~ /RUN ([0-9]{6}) eff = ([0-9]+) \/ ([0-9]+) trackshist ([0-9 ]+)/;
    $r = $1;
    next if $run{$r}->[0] != 2;
    $numer = $2;
    $denom = $3;
    @hist = split(' ', $4);

    $cum_numer += $numer;
    $cum_denom += $denom;
    foreach $i (0..29) {
	$cum_hist[$i] += $hist[$i];
    }
}

while (<EFF25>) {
    next if substr($_, 0, 40) ne " %% SYSTEM-Processor.HitEfficiency: RUN ";
    chop;
    $_ =~ /RUN ([0-9]{6}) eff = ([0-9]+) \/ ([0-9]+) trackshist ([0-9 ]+)/;
    $r = $1;
    next if $run{$r}->[0] != 2;
    $numer = $2;
    $denom = $3;
    @hist = split(' ', $4);

    $cum_numer += $numer;
    $cum_denom += $denom;
    foreach $i (0..29) {
	$cum_hist[$i] += $hist[$i];
    }
}

while (<EFF27>) {
    next if substr($_, 0, 40) ne " %% SYSTEM-Processor.HitEfficiency: RUN ";
    chop;
    $_ =~ /RUN ([0-9]{6}) eff = ([0-9]+) \/ ([0-9]+) trackshist ([0-9 ]+)/;
    $r = $1;
    next if $run{$r}->[0] != 2;
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
