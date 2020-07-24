#!/usr/local/bin/perl

foreach my $res ("y1s", "y2s", "y3s") {
    foreach my $type ("peak", "cont", "high") {
	my %beamgas = ();
	open(BEAMGAS, "cat /home/mccann/super_hadrons/final_peakfits/$res/*/$type.beamgas |");
	while (<BEAMGAS>) {
	    chop;
	    my ($run, $before, $errbefore, $after, $errafter) = split(/\s+/);
	    $beamgas{$run} = $after;
	    $bgerr{$run} = $errafter;
	}
	close(BEAMGAS);

	my %lumi = ();
	open(LUMI, "cat /home/mccann/super_hadrons/final_peakfits/$res/*/$type.gglumi |");
	while (<LUMI>) {
	    chop;
	    my ($run, $lum, $err) = split(/\s+/);
	    $lumi{$run} = $lum;
	    $lumerr{$run} = $err;
	}
	close(LUMI);

# 	%bgxs = ();
# 	foreach my $run (sort keys %beamgas) {
# 	    die if (! defined($lumi{$run}));
# 	    if (($type eq "peak"  ||  $type eq "cont")  &&
# 		$lumi{$run} > 1500) {
# 		$bgxs{$run} = ($beamgas{$run} / $lumi{$run});
# 	    }
# 	    elsif ($type eq "high") {
# 		$bgxs{$run} = ($beamgas{$run} / $lumi{$run});
# 	    }
# 	}

# 	open(OUT, "> $res\_$type.bgxs");
# 	foreach my $run (sort byval keys %bgxs) {
# 	    print OUT "$run $bgxs{$run}\n";
# 	}
# 	close(OUT);

# 	open(OUT, "> $res\_$type.lubgerr");
# 	foreach my $run (sort keys %beamgas) {
# 	    die if (! defined($lumi{$run}));
# 	    print OUT "$run $lumi{$run} $beamgas{$run}\n";
# 	}
# 	close(OUT);

	my $lumisum = 0.;
	my $lumierrsum2 = 0.;
	my $bgsum = 0.;
	my $bgerrsum2 = 0.;
	my $n = 0;

	foreach my $run (sort keys %beamgas) {
	    die if (! defined($lumi{$run}));
	    
	    if (
		($res eq "y1s" && $type eq "high" &&
		 ($run == 124960 || $run == 124961 || $run == 124962 ||
		  $run == 124963 || $run == 124966 || $run == 124967 ||
		  $run == 124968 || $run == 124969 || $run == 124970 ||
		  $run == 124971 || $run == 124972 || $run == 124973)
		 )    ||

		($res eq "y1s" && $type eq "cont" &&
		 ($run == 123370 || $run == 123566 || $run == 123570 ||
		  $run == 123774 || $run == 123944 || $run == 123961 ||
		  $run == 124126 || $run == 124300 || $run == 124475 ||
		  $run == 124665 || $run == 124667 || $run == 124807 ||
		  $run == 124808 || $run == 125175 || $run == 125176 ||
		  $run == 125297 )
		 ) ||

		($res eq "y1s" && $type eq "peak" &&
		 ($run == 123197 || $run == 123636 || $run == 123864 ||
		  $run == 123865 || $run == 123996 || $run == 124092 ||
		  $run == 124146 || $run == 124328 || $run == 124343 ||
		  $run == 124373 || $run == 124481 || $run == 124498 ||
		  $run == 124699 || $run == 124702 || $run == 124853 ||
		  $run == 125155 || $run == 125183 || $run == 125222 ||
		  $run == 125264 || $run == 125318)
		 )    ||


		($res eq "y2s" && $type eq "high" &&
		 ($run == 127206 || $run == 127213 || $run == 127214 ||
		  $run == 127215 || $run == 127217 || $run == 127218 ||
		  $run == 127219 )
		 )    ||

		($res eq "y2s" && $type eq "cont" &&
		 ($run == 126265 || $run == 126476 || $run == 126673 ||
		  $run == 126846 || $run == 126851 || $run == 127422 ||
		  $run == 127444 || $run == 127680 || $run == 127690 ||
		  $run == 127955 || $run == 129066 || $run == 129531 ||
		  $run == 129689 || $run == 129724 || $run == 129853 )
		 )    ||

		($res eq "y2s" && $type eq "peak" &&
		 ($run == 126503 || $run == 126509 || $run == 126831 ||
		  $run == 126892 || $run == 127268 || $run == 127269 ||
		  $run == 127279 || $run == 127285 || $run == 127306 ||
		  $run == 127327 || $run == 129553 || $run == 129564 ||
		  $run == 129573 || $run == 129617 || $run == 129635 ||
		  $run == 129651 )
		 )    ||


		($res eq "y3s" && $type eq "high" &&
		 ($run == 122568 || $run == 122569 || $run == 122570 ||
		  $run == 122571 || $run == 122572 || $run == 122573 ||
		  $run == 122574 || $run == 122575 )
		 )    ||

		($res eq "y3s" && $type eq "cont" &&
		 ($run == 121906 || $run == 121914 || $run == 121915 ||
		  $run == 122081 || $run == 122083 || $run == 122264 ||
		  $run == 122269 || $run == 122418 || $run == 122427 ||
		  $run == 122428 || $run == 122585 || $run == 122593 ||
		  $run == 122797 || $run == 122800 || $run == 122810 ||
		  $run == 123011 )
		 )    ||

		($res eq "y3s" && $type eq "peak" &&
		 ($run == 121946 || $run == 121966 || $run == 122079 ||
		  $run == 122105 || $run == 122123 || $run == 122263 ||
		  $run == 122301 || $run == 122454 || $run == 122472 ||
		  $run == 122480 || $run == 122577 || $run == 122619 ||
		  $run == 122649 || $run == 122831 || $run == 122859 ||
		  $run == 123026 || $run == 123042 || $run == 123056 )
		 )
		) {
		$lumisum += $lumi{$run};
		$lumierrsum2 += &sqr($lumerr{$run});
		
		$bgsum += $beamgas{$run};
		$bgerrsum2 += &sqr($bgerr{$run});

		$n++;
	    }
	}

	$lumierr = sqrt($lumierrsum2);
	$bgerr = sqrt($bgerrsum2);

	print "$res $type has $n runs with $lumisum +- $lumierr nb-1 and $bgsum +- $bgerr beamgas events.\n";

    }
}

sub byval {$bgxs{$a} <=> $bgxs{$b};}

sub sqr {$_[0] * $_[0];}
