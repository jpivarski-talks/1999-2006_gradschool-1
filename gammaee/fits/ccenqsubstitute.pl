#!/usr/local/bin/perl

require("grand_list.pl");

# %gone = ();
# open(GOS, "ls ccencounting_scripts/ccg*.run |");
# while (my $go = <GOS>) {
#     $go =~ /ccg([0-9]+)\.run/;
#     $gone{$1} = 1;
# }

sub randomly {(rand() > 0.5 ? 1 : 0);}

foreach $r (sort randomly keys %run) {
#    next if (defined($gone{$r}));
#    next if ($run{$r}->[2] eq "scan"  ||
#	     $run{$r}->[2] eq "high");
    next if ($r != 121943  &&
	     $r != 121946  &&
	     $r != 121949  &&
	     $r != 122066  &&
	     $r != 122092  &&
	     $r != 122093  &&
	     $r != 122274  &&
	     $r != 122423  &&
	     $r != 122430  &&
	     $r != 122443  &&
	     $r != 122447  &&
	     $r != 122602  &&
	     $r != 122608  &&
	     $r != 122640  &&
	     $r != 122641  &&
	     $r != 122643  &&
	     $r != 122648  &&
	     $r != 122650  &&
	     $r != 122652  &&
	     $r != 122821  &&
	     $r != 122829  &&
	     $r != 122832  &&
	     $r != 122833  &&
	     $r != 122835  &&
	     $r != 123569  &&
	     $r != 123644  &&
	     $r != 123650  &&
	     $r != 123812  &&
	     $r != 123852  &&
	     $r != 123871  &&
	     $r != 124007  &&
	     $r != 124017  &&
	     $r != 124705  &&
	     $r != 125188  &&
	     $r != 125344  &&
	     $r != 126506  &&
	     $r != 126507  &&
	     $r != 126511  &&
	     $r != 126513  &&
	     $r != 126541  &&
	     $r != 126542  &&
	     $r != 126546  &&
	     $r != 126915  &&
	     $r != 127272  &&
	     $r != 127273  &&
	     $r != 127278  &&
	     $r != 127280  &&
	     $r != 127285  &&
	     $r != 129653  &&
	     $r != 129656  &&
	     $r != 129857  &&
	     $r != 130259  &&
	     $r != 130276  &&
	     $r != 130290  &&
	     $r != 130614  &&
	     $r != 130629  &&
	     $r != 130630     );

    system("rm -f /cdat/tem/mccann/ccencounting_logs/r$r.log");

    do {
        $qstat = `qstat -u mccann | fgrep ccg | wc -l`;
        chop($qstat);

	if ($qstat >= 8) {
	    print "Waiting five minutes...\n";
	    sleep 300;
	}
    } while ($qstat >= 8);

    system("perl ccencount.pl $r");
}
