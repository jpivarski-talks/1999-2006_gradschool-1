#!/usr/local/bin/perl

require("grand_list.pl");
require("energy.pl");

sub byenergy {$energy{$a} <=> $energy{$b}};

open(PAW, "> slideshow.kumac");
foreach $r (sort byenergy keys %run) {
    next if (!-e "/cdat/dafe/mccann/fits/plots$r.rzn");

    print PAW "h/file 0 /cdat/dafe/mccann/fits/plots$r.rzn\n";
    print PAW "message $r is $energy{$r} GeV U($run{$r}->[0]S) $run{$r}->[2] from $run{$r}->[1], db$run{$r}->[3]\n";
    print PAW "cd CountEvents\n";
    print PAW "h/plot $ARGV[0]\n";
    print PAW "wait\n";
}
