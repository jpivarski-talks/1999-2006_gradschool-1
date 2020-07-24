#!/usr/local/bin/perl

%frac = ();
%err = ();
open(ALL, "/cdat/tem/mccann/ccen_all.dat");
while(<ALL>) {
    chop;
    my ($run, $fr, $e) = split(" ");
    $frac{$run} = $fr;
    $err{$run} = $e;
}
close(ALL);

while(<STDIN>) {
    chop;
    if (!defined($frac{$_})) {
	warn $_;
    }
    else {
	print "$_ $frac{$_} $err{$_}\n";
    }
}
