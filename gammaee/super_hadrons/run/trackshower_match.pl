#!/usr/local/bin/perl

%before = ();

open(BEFORE, "/cdat/tem/mccann/trackshower_before.log");
while (<BEFORE>) {
    next if ( substr($_, 0, 6) ne "NTUPLE" );
    chop;
    ($tag, $run, $event, $num, $mat, $conreg, $nobrem, $ishadron) = split(/\s+/);
    $before{"$run $event"} = [$num, $mat, $conreg, $nobrem, $ishadron];
}
close(BEFORE);

$bis_ais = 0;
$bis_aisnt = 0;
$bisnt_ais = 0;
$bisnt_aisnt = 0;

open(AFTER, "/cdat/tem/mccann/trackshower_after.log");
while (<AFTER>) {
    next if ( substr($_, 0, 6) ne "NTUPLE" );
    chop;
    ($tag, $run, $event, $num, $mat, $conreg, $nobrem, $ishadron) = split(/\s+/);
    if ( defined($before{"$run $event"}) ) {
	($bnum, $bmat, $bconreg, $bnobrem, $bishadron) = @{ $before{"$run $event"} };
	
	if ( $bishadron == 1 ) {
	    if ( $ishadron == 1 ) {
		$bis_ais++;
	    }
	    else {
		$bis_aisnt++;

		printf("BIS_AISNT: %2d-%2d=%2d, %2d-%2d=%2d, %2d-%2d=%2d\n",
		       $bmat, $mat, ($bmat-$mat),
		       $bconreg, $conreg, ($bconreg-$conreg),
		       $bnobrem, $nobrem, ($bnobrem-$nobrem));
	    }
	}
	else {
	    if ( $ishadron == 1 ) {
		$bisnt_ais++;

		printf("BISNT_AIS: %2d-%2d=%2d, %2d-%2d=%2d, %2d-%2d=%2d\n",
		       $bmat, $mat, ($bmat-$mat),
		       $bconreg, $conreg, ($bconreg-$conreg),
		       $bnobrem, $nobrem, ($bnobrem-$nobrem));
	    }
	    else {
		$bisnt_aisnt++;
	    }
	}
	    
    }
}
close(AFTER);

printf("              BEFORE IS           BEFORE ISNT\n");
printf("  AFTER IS    %20d %20d\n", $bis_ais, $bisnt_ais);
printf("  AFTER ISNT  %20d %20d\n", $bis_aisnt, $bisnt_aisnt);

