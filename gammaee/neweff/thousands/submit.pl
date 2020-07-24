#!/usr/local/bin/perl

@runorder = ();
open(RUNORDER, "runorder_resorted.txt");
while (<RUNORDER>) {
    chop;
    push(@runorder, $_) if (!-e "go$_.run");
}
close(RUNORDER);

foreach $run (@runorder) {
    do {
        print "Waiting $ARGV[0] seconds...\n";
        sleep $ARGV[0];

        $qstat = `qstat -u mccann | grep go | wc -l`;
        chop($qstat);

    } while ($qstat >= 8);

    $db = 0;
    $db = 16 if ($run >= 121339 && $run <= 122179);
    $db = 17 if ($run >= 122245 && $run <= 123304);
    $db = 18 if ($run >= 123314 && $run <= 124575);
    $db = 19 if ($run >= 124624 && $run <= 125416);
    $db = 20 if ($run >= 125428 && $run <= 126206);
    $db = 21 if ($run >= 126252 && $run <= 127545);
    $db = 22 if ($run >= 127550 && $run <= 128401);
    $db = 23 if ($run >= 128684 && $run <= 129223);
    $db = 24 if ($run >= 129257 && $run <= 129488);
    $db = 25 if ($run >= 129519 && $run <= 129865);
    $db = 26 if ($run >= 129897 && $run <= 130187);
    $db = 27 if ($run >= 130198 && $run <= 130630);
    die "So Jim, in what database is run $run?" if ($db == 0);

    open(RUN, "> go$run.run");
    print RUN "#\$ -l u5
#\$ -o /cdat/tem/mccann/thousands/go$run.log
#\$ -S /bin/bash
#\$ -j y

cd /home/mccann/neweff/thousands/
. /nfs/cleo3/scripts/cleo3defs
c3rel Dec10_03

export USER_RUN=$run
export USER_DB=$db

suez -f run.tcl
";
    close(RUN);
    system("qsub go$run.run");
}




