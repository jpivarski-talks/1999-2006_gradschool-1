#!/usr/local/bin/perl

require("grand_list.pl");
require("energy.pl");

opendir(DIR, "/cdat/dafe/mccann/fits/tails");
@dir = readdir(DIR);
closedir(DIR);

@lookat = ();
foreach $file (@dir) {
    next if $file !~ /tail([0-9]{6})\.rzn/;
    $runnum = $1;
    push(@lookat, $runnum);
}

sub byenergy {$energy{$a} <=> $energy{$b}};

open(PAW, "> lookattailvects.kumac");
foreach $runnum (sort byenergy @lookat) {
    print PAW "h/file 1 /cdat/dafe/mccann/fits/tails/tail$runnum.rzn
message $runnum is $energy{$runnum} GeV U($run{$runnum}->[0]S) $run{$runnum}->[2] from $run{$runnum}->[1], db$run{$runnum}->[3]
h/plot 1000
wait
close 1

";

}
