#!/usr/local/bin/perl

open(GOODEVENTS, "> stability/newGoodEvents.pl");
open(BGE, "> stability/bge.pl");
open(BGP, "> stability/bgp.pl");
open(E1, "> stability/e1.pl");
open(P2, "> stability/p2.pl");
open(VISEN, "> stability/visen.pl");
open(CCEN, "> stability/ccen.pl");
open(TRACKS, "> stability/tracks.pl");

print GOODEVENTS "\%newGoodEvents = ();\n";
print BGE "\%bge = ();\n";
print BGP "\%bgp = ();\n";
print E1 "\%e1 = ();\n";
print P2 "\%p2 = ();\n";
print VISEN "\%visen = ();\n";
print CCEN "\%ccen = ();\n";
print TRACKS "\%tracks = ();\n";

foreach $file ("/cdat/tem/mccann/db16.log",
	       "/cdat/tem/mccann/db17.log",
	       "/cdat/tem/mccann/db18a.log",
	       "/cdat/tem/mccann/db18b.log",
	       "/cdat/tem/mccann/db18c.log",
	       "/cdat/tem/mccann/db19.log",
	       "/cdat/tem/mccann/db19b.log",
	       "/cdat/tem/mccann/db21.log",
	       "/cdat/tem/mccann/db22.log",
	       "/cdat/tem/mccann/db23.log",
	       "/cdat/tem/mccann/db25.log",
	       "/cdat/tem/mccann/db27.log") {
    open(FILE, $file);
    while (my $line = <FILE>) {
	next if substr($line, 0, 4) ne "RUN ";
	my ($dum1, $run, $dum2, $events, $dum3,
	    $dumcos, $dum4, $bge, $dum5, $bgp, $dum6,
	    $dum7, $dum8, $e1, $p2, $visen, $ccen, $tracks) = split(' ', $line);
	print GOODEVENTS "\$newGoodEvents{$run} = $events;\n";
	print BGE "\$bge{$run} = $bge;\n";
	print BGP "\$bgp{$run} = $bgp;\n";
	print E1 "\$e1{$run} = $e1;\n";
	print P2 "\$p2{$run} = $p2;\n";
	print VISEN "\$visen{$run} = $visen;\n";
	print CCEN "\$ccen{$run} = $ccen;\n";
	print TRACKS "\$tracks{$run} = $tracks;\n";
    }
}

print GOODEVENTS "1;\n";
print BGE "1;\n";
print BGP "1;\n";
print E1 "1;\n";
print P2 "1;\n";
print VISEN "1;\n";
print CCEN "1;\n";
print TRACKS "1;\n";

