#!/usr/local/bin/perl

foreach $tcl (@ARGV) {
    $log = $tcl;
    $log =~ s/\.tcl$/\.log/;
    $run = $tcl;
    $run =~ s/\.tcl$/\.run/;

    open(RUN, "> $run");
    print RUN "#\$ -l u5
#\$ -o /cdat/tem/mccann/$log
#\$ -S /bin/bash
#\$ -j y

cd /home/mccann/neweff/run/
. /nfs/cleo3/scripts/cleo3defs
c3rel Dec10_03

suez -f $tcl
";
    close RUN;
}
