#!/usr/local/bin/perl

%def = ();
while ($run = <>) {
    chop($run);
    $def{$run} = "na";
}

foreach $res (1, 2, 3) {
    foreach $type ("cont", "peak", "scan", "high") {
	$announced = 0;

	open(FILE, "$type$res"."s.txt");
	while ($line = <FILE>) {
	    chop($line);
	    ($run, $num, $num_err) = split(/\s+/, $line);
	    
	    if (defined($def{$run})) {
		if ($announced == 0) {
		    $announced = 1;
		    print "\n======= $type$res =================\n";
		}

		print "$run\n";
	    }
	}
	close(FILE);
    }
}
