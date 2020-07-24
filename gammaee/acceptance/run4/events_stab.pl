#!/usr/local/bin/perl

%ev = ();
open(ALL, "/cdat/tem/mccann/count_all.dat");
while(<ALL>) {
    chop;
    my ($run, $events, $e1, $p2, $visen, $ccen, $tracks) = split(/\s+/);
    $ev{$run} = $tracks;
}
close(ALL);

while(<STDIN>) {
    chop;
    if (!defined($ev{$_})) {
	warn $_;
    }
    else {
	print "$_ $ev{$_}\n";
    }
}
