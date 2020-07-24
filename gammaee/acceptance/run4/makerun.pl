#!/usr/local/bin/perl

opendir(DIR, ".");
@all = readdir(DIR);
closedir(DIR);

foreach my $tclfile (@all) {
    next if $tclfile !~ /\.tcl$/;

    my $runfile = $tclfile;
    $runfile =~ s/\.tcl$/.run/;
    $runfile =~ s/crap/K/;
    $runfile =~ s/trig/T/;

    my $logfile = $tclfile;
    $logfile =~ s/\.tcl$/.log/;

    open(RUN, "> $runfile");
    print RUN "#\$ -l u5
#\$ -o /cdat/tem/mccann/$logfile
#\$ -S /bin/bash
#\$ -j y

cd /home/mccann/acceptance/run4/
. /nfs/cleo3/scripts/cleo3defs
c3rel Dec10_03

suez -f $tclfile
rm -f core
";
    close(RUN);
}
