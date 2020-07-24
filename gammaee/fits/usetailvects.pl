#!/usr/local/bin/perl

require("energy.pl");

opendir(DIR, "/cdat/dafe/mccann/fits/tails");
@dir = readdir(DIR);
closedir(DIR);

foreach $file (@dir) {
    next if $file !~ /tail([0-9]{6})\.vec/;
    $runnum = $1;
    die if (!-e "/cdat/dafe/mccann/fits/plots$runnum.rzn");

    open(PAW, "| /nfs/cern/pro/bin/pawX11");
    print PAW "0
nt/cr 1 'blah' 1 ! ! 'ccen'
nt/read 1 /cdat/dafe/mccann/fits/tails/tail$runnum.vec
h/cr/1d 900 '$runnum CC total energy' 50 0. 1.25
nt/plot 1.ccen/2/$energy{$runnum} ! ! ! ! 'N' 900
h/file 2 /cdat/dafe/mccann/fits/plots$runnum.rzn
h/copy //lun2/CountEvents/800 801
add 900 //lun2/CountEvents/800 1000
h/file 1 /cdat/dafe/mccann/fits/tails/tail$runnum.rzn ! 'n'
hrout 801
hrout 900
hrout 1000
exit
";

}
