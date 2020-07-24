#!/usr/local/bin/perl

require("/home/mccann/fits/grand_list.pl");

# $run{$r}->[0] is the resonance number (1, 2, 3)
# $run{$r}->[1] is the scan name ("nov29-01"...)
# $run{$r}->[2] is the run type ("peak", "cont", "scan", "high")
# $run{$r}->[3] is the database number (16..27)

# USER_DB
# USER_RUN

foreach $r (keys %run) {
    open(RUN, "> daf9/runs/R$r.run");
    print RUN "#\$ -l u5
#\$ -o /cdat/tem/mccann/relatives_$r.log
#\$ -S /bin/bash
#\$ -j y

cd /home/mccann/luminosity/run3/
. /nfs/cleo3/scripts/cleo3defs
c3rel Dec10_03

export USER_DB=$run{$r}->[3]
export USER_RUN=$r

suez -f relatives.tcl
# | tee /cdat/tem/mccann/tmp_$r.log
rm -f core
# fgrep PYTHON /cdat/tem/mccann/tmp_$r.log >> daf9/relatives.py
# rm -f /cdat/tem/mccann/tmp_$r.log

exit
";
    close(RUN);
} # end foreach run


