#!/usr/local/bin/perl

%en = ();
open(ALL, "/nfs/cleo3/Offline/InfoFiles/data/runinfo.runinfo");
while(<ALL>) {
    chop;
    my @stuff = split(/\s+/);
    $en{@stuff[1]} = @stuff[8];
}
close(ALL);

while(<STDIN>) {
    chop;
    if (!defined($en{$_})) {
	warn $_;
    }
    else {
	print "$_ $en{$_}\n";
    }
}
