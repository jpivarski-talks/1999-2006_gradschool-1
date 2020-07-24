#!/usr/local/bin/perl

$base_dir = $ENV{"HOME"}."/public_html/private/my_gammaee";

@run_info_files = (
		    "$base_dir/run_infoY1s.html",
#		    "$base_dir/run_infoY2s.html",
#		    "$base_dir/run_infoY3s.html",
		   );
$run_info_plots_dir = "$base_dir/run_info_plots";
$fits_dir = "$base_dir/fits";
$tmp_dir = "$base_dir/tmp";

$gnuplot_comm = "/usr/local/bin/gnuplot";
$ppm_to_gif_comm = $ENV{"USER_DAF"}."/software/pbmplus/ppmtogif -interlace";
$giftrans_comm = "/usr/local/X11/giftrans";
$luminosities = "/home/dlk/Luminosities";

%tag = ();
%title = ();
%energy = ();
%lumi = ();
%hxc_online = ();

%h_num_pass1 = ();
%hxc_pass1 = ();
%ee_num_pass1 = ();
%ee_lum_pass1 = ();
%gam_num_pass1 = ();
%gam_lum_pass1 = ();
%mumu_num_pass1 = ();
%mumu_lum_pass1 = ();

&make_rawdata();


    




# $totalnumhad = 0;
# foreach $run ( keys %tag ) {
#     $totalnumhad += $h_num_pass1{$run};
# }
# print "Total number of hadrons (pass1) is: $totalnumhad\n";

# $totalintlumi = 0;
# foreach $run ( keys %tag ) {
#     $totalintlumi += $lumi{$run};
# }
# print "Total int lumi is: $totalintlumi\n";

# $myintlumi = 0.;
# $hxcnumer = 0.;
# $hxcdenom = 0.;
# foreach $run ( keys %tag ) {
#     if ( $run >= 121899  &&  $run <= 121915 ) {
# 	print "run is $run\n";
# 	$myintlumi += $lumi{$run};
# 	my $weight = 1./$hxc_pass1{$run}->[1]/$hxc_pass1{$run}->[1];
# 	$hxcnumer += $hxc_pass1{$run}->[0] * $weight;
# 	$hxcdenom += $weight;
#     }
# }
# print "The integrated luminosity in [121899,121915] is $myintlumi\n";
# print "The hadronic cross-section is ".($hxcnumer/$hxcdenom)." +/- ".sqrt(1./$hxcdenom)."\n";

# $scan = 0;
# $high = 0;
# $cont = 0;
# $peak = 0;
# foreach $run ( keys %tag ) {
#     if ( $title{$run} =~ /scan/i ) {
# 	$scan += $lumi{$run};
#     }
#     elsif ( $title{$run} =~ /high/i ) {
# 	$high += $lumi{$run};
#     }
#     elsif ( $title{$run} =~ /cont/i ) {
# 	$cont += $lumi{$run};
#     }
#     elsif ( $title{$run} =~ /peak/i ) {
# 	$peak += $lumi{$run};
#     }
# }

# print "Scan lumi: $scan\n";
# print "High lumi: $high\n";
# print "Cont lumi: $cont\n";
# print "Peak lumi: $peak\n";

# print "\n";

# foreach $run ( keys %tag ) {
#     if ( $tag{$run} eq "dec25-01" ) {
# 	print "$run    $energy{$run}   $ee_lum_pass1{$run}->[0] $ee_lum_pass1{$run}->[1]     $gam_lum_pass1{$run}->[0] $gam_lum_pass1{$run}->[1]    $h_num_pass1{$run}\n";
#     }
# }

#########################################################################

sub allruns { return 1; }

sub scanQ {
    ( my $title, my $run, my $energy, my $lumi, my $hxc ) = @_;
    if ( $title =~ /scan/i ) { return 1; } return 0;
}
sub contQ {
    ( my $title, my $run, my $energy, my $lumi, my $hxc ) = @_;
    if ( $title =~ /cont/i ) { return 1; } return 0;
}
sub peakQ {
    ( my $title, my $run, my $energy, my $lumi, my $hxc ) = @_;
    if ( $title =~ /peak/i ) { return 1; } return 0;
}

sub Y3sQ {
    ( my $title, my $run, my $energy, my $lumi, my $hxc ) = @_;
    if ( $title =~ /November 29 /   ||
	 $title =~ /December 6 /    ||
	 $title =~ /December 13 /   ||
	 $title =~ /December 20 /   ||
	 $title =~ /December 25 /   ||
	 $title =~ /January 3 /     ||
	 $title =~ /January 10 /       ) {
	return 1;
    } else {
	return 0;
    }
}

sub biglumi {
    ( my $title, my $run, my $energy, my $lumi, my $hxc ) = @_;
    return ( $lumi > 1500. ? 1. : 0. );
}

#########################################################################

sub get_set {
    my ( $runs, $hash ) = @_;
    my @set = ();

    foreach my $run ( @{ $runs } ) {
	push( @set, $hash->{$run} )
	    if ( defined( $hash->{$run} ) );
    }
    return @set;
}

#########################################################################

sub sum {
    my @numbers = @_;
    my $sum = 0.;
    foreach my $num ( @numbers ) {
	$sum += $num;
    }
    return $sum;
}

sub mean {
    my @numbers = @_;
    my $sum = 0.;
    my $n = 0;
    foreach my $num ( @numbers ) {
	$sum += $num;
	$n++;
    }
    return $sum / $n;
}

sub rms {
    my @numbers = @_;
    my $sum = 0.;
    my $squaresum = 0.;
    my $n = 0;
    foreach my $num ( @numbers ) {
	$sum += $num;
	$squaresum += $num * $num;
	$n++;
    }
    my $square_of_mean = &sqr( $sum / $n );
    my $mean_of_square = $squaresum / $n;

    return sqrt( $mean_of_square - $square_of_mean );
}

sub minimum {
    my @numbers = @_;
    my $min = "start";
    foreach my $num ( @numbers ) {
	$min = $num
	    if ( $min eq "start"  ||  $num < $min );
    }
    return $min;
}

sub maximum {
    my @numbers = @_;
    my $max = "start";
    foreach my $num ( @numbers ) {
	$max = $num
	    if ( $max eq "start"  ||  $num > $max );
    }
    return $max;
}

sub area {
    my @pairs = @_;
    my $a = 0.;
    my $lastx = "start";
    my $lasty = 0.;
    foreach my $pair ( sort byx @pairs ) {
	if ( $lastx ne "start" ) {
	    my $midy = ( $pair->[1] + $lasty ) / 2.;
	    my $width = ( $pair->[0] - $lastx );
	    $a += $width * $midy;
	}
	$lastx = $pair->[0];
	$lasty = $pair->[1];
    }
    return $a;
}

sub byx { $a->[0] <=> $b->[0]; }

sub deped {
    my @numbers = @{ @_[0] };
    my $pedistal = @_[1];
    foreach my $i ( 0..$#numbers ) {
	$numbers[$i] -= $pedistal;
    }
    return @numbers;
}

sub weighted_mean {
    my @pairs = @_;
    my $sum_xsig = 0.;
    my $sum_sig = 0.;
    foreach my $pair ( @pairs ) {
	my $xi = $pair->[0];
	my $sigi = 1. / $pair->[1] / $pair->[1];

	$sum_xsig += $xi * $sigi;
	$sum_sig += $sigi;
    }
    return [ $sum_xsig / $sum_sig, sqrt( 1. / $sum_sig ) ];
}

sub generate_uncertanties {
    my @numbers = @_;
    my @pairs = ();
    foreach my $num ( @numbers ) {
	push( @pairs, [ $num, sqrt( $num ) ] );
    }
    return @pairs;
}

sub sqr { return @_[0] * @_[0]; }

#########################################################################

sub make_rawdata {
    print "Getting all pass1 information...\n";
    &get_pass1();
    chdir( $tmp_dir );

    my %all_tags = ();
    print "Getting all run_info.html information...\n";
    my @runs = sort &get_runs( \&allruns );
    my $col = 0;
    my %beenseen = ();
    foreach my $run ( @runs ) {
	print "    " if ( $col == 0 );
	print "$run ";
	$col++;
	if ( $col == 5 ) {
	    print "\n";
	    $col = 0;
	}

	$all_tags{$tag{$run}} = 1;

	my $type = "X";
	if ( $title{$run} =~ /scan/i ) { $type = "S"; }
	if ( $title{$run} =~ /high/i ) { $type = "H"; }
	if ( $title{$run} =~ /cont/i ) { $type = "C"; }
	if ( $title{$run} =~ /peak/i ) { $type = "P"; }

	### Make raw data and put it in the right directories
	if ( ! -e "$fits_dir/$tag{$run}" ) {
	    mkdir( "$fits_dir/$tag{$run}", 0755 );
	}

	if ( defined( $hxc_online{$run} ) ) {
	    if ( ! -e "$fits_dir/$tag{$run}/online" ) {
		mkdir( "$fits_dir/$tag{$run}/online", 0755 );
	    }

	    if ( ! defined( $beenseen{"$tag{$run}-online"} ) ) {
		unlink( "$fits_dir/$tag{$run}/online/data.dat" )
		    if ( -e "$fits_dir/$tag{$run}/online/data.dat" );
		$beenseen{"$tag{$run}-online"} = 1;
	    }

	    open( DATA, ">> $fits_dir/$tag{$run}/online/data.dat" );
	    print DATA "$run\t$type\t$energy{$run}\t$hxc_online{$run}->[0]\t$hxc_online{$run}->[1]\n";
	    close DATA;

	} # endif we have online data

	if ( defined( $hxc_pass1{$run} ) ) {
	    if ( ! -e "$fits_dir/$tag{$run}/pass1" ) {
		mkdir( "$fits_dir/$tag{$run}/pass1", 0755 );
	    }

	    if ( ! defined( $beenseen{"$tag{$run}-pass1"} ) ) {
		unlink( "$fits_dir/$tag{$run}/pass1/data.dat" )
		    if ( -e "$fits_dir/$tag{$run}/pass1/data.dat" );
		unlink( "$fits_dir/$tag{$run}/pass1/raw.dat" )
		    if ( -e "$fits_dir/$tag{$run}/pass1/raw.dat" );
		$beenseen{"$tag{$run}-pass1"} = 1;
	    }

	    open( DATA, ">> $fits_dir/$tag{$run}/pass1/data.dat" );
	    open( RAW, ">> $fits_dir/$tag{$run}/pass1/raw.dat" );
	    print DATA "$run\t$type\t$energy{$run}\t$hxc_pass1{$run}->[0]\t$hxc_pass1{$run}->[1]\n";
	    print RAW "$run\t$type\t$energy{$run}\t$h_num_pass1{$run}\t$ee_num_pass1{$run}\t$gam_num_pass1{$run}\t$hxc_pass1{$run}->[0]\n";
	    close DATA;
	    close RAW;

	} # endif we have pass1 data
    } # end foreach run
    print "\n" if ( $col != 0 );

    foreach my $mytag ( keys %all_tags ) {
	### Make plots of the peaks for scans
	
	if ( ! -e "$run_info_plots_dir/$mytag\_scan.gif"
	     && $mytag ne "feb14-02"
	     ) {
	    print "Making a scan plot for $mytag...\n";

	    open( TMP, "> $mytag\_scan.dat" );

	    my $mytitle = "";
	    my @energies = ();
	    my @hxcs = ();
# 	    my @energy_hxc_pairs = ();
	    foreach my $run ( @runs ) {
		next if ( $tag{$run} ne $mytag  ||
			  ( $title{$run} !~ /scan/i  &&  $title{$run} !~ /high/i ) );
		$mytitle = $title{$run} if ( $mytitle eq "" );

		if ( defined( $hxc_pass1{$run} ) ) {
		    print TMP "$energy{$run}\t$hxc_pass1{$run}->[0]\t$hxc_pass1{$run}->[1]\n";
		    push( @energies, $energy{$run} );
		    push( @hxcs, $hxc_pass1{$run}->[0] );
# 		    push( @energy_hxc_pairs, [ $energy{$run}, $hxc_pass1{$run}->[0] ] );
			
		} elsif ( defined( $hxc_online{$run} ) ) {
		    print TMP "$energy{$run}\t$hxc_online{$run}->[0]\t$hxc_online{$run}->[1]\n";
		    push( @energies, $energy{$run} );
		    push( @hxcs, $hxc_online{$run}->[0] );
# 		    push( @energy_hxc_pairs, [ $energy{$run}, $hxc_online{$run}->[0] ] );
		    
		} # endif data exists

	    } # end first loop over runs in this scan
	    close( TMP );

	    $mytitle =~ s/^\s*[0-9]+\.\s*//;
	    $mytitle =~ s/\s*\(.*\)\s*//g;

# 	    my $pedistal = &minimum( @hxcs );
# 	    my $area = &area( @energy_hxc_pairs ) -
# 		$pedistal * ( &maximum( @energies ) - &minimum( @energies ) );

#  	    my @energy_hxcs = ();
#  	    my @energy_squared_hxcs = ();
#  	    my @hxcs_deped = ();
#  	    foreach my $run ( @runs ) {
#  		next if ( $tag{$run} ne $mytag  ||  $title{$run} !~ /scan/i );

#  		if ( defined( $hxc_pass1{$run} ) ) {
#  		    push( @energy_hxcs, $energy{$run} *
#  			  ( $hxc_pass1{$run}->[0] - $pedistal ) );
#  		    push( @energy_squared_hxcs, &sqr( $energy{$run} ) *
#  			  ( $hxc_pass1{$run}->[0] - $pedistal ) );
#  		    push( @hxcs_deped, $hxc_pass1{$run}->[0] - $pedistal );

#  		} elsif ( defined( $hxc_online{$run} ) ) {
#  		    push( @energy_hxcs, $energy{$run} *
#  			  ( $hxc_online{$run}->[0] - $pedistal ) );
#  		    push( @energy_squared_hxcs, &sqr( $energy{$run} ) *
#  			  ( $hxc_online{$run}->[0] - $pedistal ) );
#  		    push( @hxcs_deped, $hxc_online{$run}->[0] - $pedistal );
#  		}
#  	    } # end second loop over runs in this scan

#  	    my $mean = &mean( @energy_hxcs ) / &mean( @hxcs_deped );
#  	    my $rms = sqrt( ( &mean( @energy_squared_hxcs ) / &mean( @hxcs_deped ) ) -
#  			    &sqr( $mean ) );

# 	    my $peak = $area / sqrt( 6.2832 ) / $rms;
	    my $window_bottom = 0.;
# 	    my $window_top = &maximum( @hxcs, $peak ) + 2.;
	    my $window_top = &maximum( @hxcs ) + 2.;
	    my $window_left = &minimum( @energies ) - 0.002;
	    my $window_right = &maximum( @energies ) + 0.002;

#  	    open( FITSEED, "> $fits_dir/$mytag/fitseed.dat" );
#  	    print FITSEED "$area, $mean, $rms, $pedistal\n";
#  	    close( FITSEED );

	    open( GNUPLOT, "> $mytag\_scan.gnuplot" );
	    print GNUPLOT "set nokey\n";
	    print GNUPLOT "set size 0.75,0.5\n";
	    print GNUPLOT "set term pbm small monochrome\n";
	    print GNUPLOT "set output \"$mytag\_scan.pbm\"\n";
# 	    print GNUPLOT "set title \"$mytitle (with a lousy Gaussian pseudofit)\"\n";
	    print GNUPLOT "set title \"$mytitle\"\n";
	    print GNUPLOT "set xlabel \"Beam Energy in GeV\"\n";
	    print GNUPLOT "set ylabel \"Hadronic Cross-Section in nb\"\n";
#  	    print GNUPLOT "plot [$window_left:$window_right][$window_bottom:$window_top] ".
#  		"\"$mytag\_scan.dat\" with errorbars, $pedistal+$peak*exp(-(x-$mean)**2/2/$rms**2)\n";
	    print GNUPLOT "plot [$window_left:$window_right][$window_bottom:$window_top] ".
		"\"$mytag\_scan.dat\" with errorbars\n";
	    print GNUPLOT "exit\n";
	    close( GNUPLOT );

	    system( "$gnuplot_comm $mytag\_scan.gnuplot" );

	    system( "$ppm_to_gif_comm $mytag\_scan.pbm | $giftrans_comm -t \"#ffffff\" > $run_info_plots_dir/$mytag\_scan.gif" );

	} # end if the scan plot doesn't yet exist

	### Make plots of energy and hadronic cross-section stability for
	### continuum and peaks

	if ( ! -e "$run_info_plots_dir/$mytag\_peak-en.gif" ) {
	    &make_stability_plot( $mytag, "peak", "en", [ @runs ] );
	}
	if ( ! -e "$run_info_plots_dir/$mytag\_peak-xc.gif" ) {
	    &make_stability_plot( $mytag, "peak", "xc", [ @runs ] );
	}
	if ( ! -e "$run_info_plots_dir/$mytag\_cont-en.gif" ) {
	    &make_stability_plot( $mytag, "cont", "en", [ @runs ] );
	}
	if ( ! -e "$run_info_plots_dir/$mytag\_cont-xc.gif" ) {
	    &make_stability_plot( $mytag, "cont", "xc", [ @runs ] );
	}

    } # end foreach tag
}

sub make_stability_plot {
    ( my $mytag, my $point, my $var, my $runsref ) = @_;

    die if ( $point ne "peak"  &&  $point ne "cont" );
    die if ( $var ne "en"  &&  $var ne "xc" );

    print "Making a stability plot for $mytag\_$point-$var...\n";

    chdir( $tmp_dir );

    open( TMP, "> $mytag\_$point-$var.dat" );

    my $mytitle = "";
    my @values = ();
    my $minrun = "start";
    my $maxrun = "start";
    foreach my $run ( @{ $runsref } ) {
	next if ( $tag{$run} ne $mytag  ||  $title{$run} !~ /$point/i );
	$mytitle = $title{$run} if ( $mytitle eq "" );

	$minrun = $run if ( $minrun eq "start"  ||  $run < $minrun );
	$maxrun = $run if ( $maxrun eq "start"  ||  $run > $maxrun );

	if ( $var eq "en" ) {
	    print TMP "$run\t$energy{$run}\n";
	    push( @values, $energy{$run} );

	} elsif ( $var eq "xc" ) {
	    if ( defined( $hxc_pass1{$run} ) ) {
		print TMP "$run\t$hxc_pass1{$run}->[0]\t$hxc_pass1{$run}->[1]\n";
		push( @values, $hxc_pass1{$run}->[0] );

	    } elsif ( defined( $hxc_online{$run} ) ) {
		print TMP "$run\t$hxc_online{$run}->[0]\t$hxc_online{$run}->[1]\n";
		push( @values, $hxc_online{$run}->[0] );

	    } # end if data exists
	} # end switch var
    } # end first loop over runs in this point
    close( TMP );

    $mytitle =~ s/^\s*[0-9]+\.\s*//;
    $mytitle =~ s/\s*\(.*\)\s*//g;
    my $window_bottom;
    my $window_top;

    my $en_up_line;
    my $en_mid_line;
    my $en_down_line;
    if ( $var eq "en" ) {
	my $max = &maximum( @values );
	my $min = &minimum( @values );

	my $middle = ( $max + $min ) / 2.;
	my $range = ( $max - $min );

	if ( 0.6 * $range > 0.0004 ) {
	    $window_bottom = $middle - 0.6 * $range;
	    $window_top = $middle + 0.6 * $range;
	} else {
	    $window_bottom = $middle - 0.0004;
	    $window_top = $middle + 0.0004;
	}

	$en_up_line = $middle - 0.0002;
	$en_mid_line = $middle;
	$en_down_line = $middle + 0.0002;

    } elsif ( $var eq "xc" ) {
	$window_bottom = 0.;
	$window_top = 1.2 * &maximum( @values );
    }

    my $window_left = $minrun - 5;
    my $window_right = $maxrun + 5;

    my $midrun = int( ( $maxrun + $minrun ) / 2. );

    open( GNUPLOT, "> $mytag\_$point-$var.gnuplot" );
    print GNUPLOT "set nokey\n";
    print GNUPLOT "set size 0.6,0.5\n";
    print GNUPLOT "set term pbm small monochrome\n";
    print GNUPLOT "set output \"$mytag\_$point-$var.pbm\"\n";
    print GNUPLOT "set title \"$mytitle ".( $var eq "en" ? "Energy" : "Hadronic XC" )." Stability\"\n";
    print GNUPLOT "set xlabel \"Runs\"\n";
    print GNUPLOT "set xtics ($minrun, $midrun, $maxrun)\n";
    print GNUPLOT "set ylabel \"".( $var eq "en" ? "Energy in GeV" : "Hadronic XC in nb" )."\"\n";
    print GNUPLOT "plot [$window_left:$window_right][$window_bottom:$window_top] ".
	"\"$mytag\_$point-$var.dat\"".( $var eq "en" ? ", $en_up_line with lines 2, $en_mid_line with lines 1, $en_down_line with lines 2" : " with errorbars" )."\n";
    print GNUPLOT "exit\n";
    close( GNUPLOT );
    
    system( "$gnuplot_comm $mytag\_$point-$var.gnuplot" );
    
    system( "$ppm_to_gif_comm $mytag\_$point-$var.pbm | $giftrans_comm -t \"#ffffff\" > $run_info_plots_dir/$mytag\_$point-$var.gif" );

}

#########################################################################

sub branching_fractions {
    &get_pass1();

    my @cont_runs = &get_runs( sub { &contQ(@_) && &Y3sQ(@_) } );
    my @peak_runs = &get_runs( sub { &peakQ(@_) && &Y3sQ(@_) } );

    my $en_cont = &mean( &get_set( [ @cont_runs ], \%energy ) );
    my $en_peak = &mean( &get_set( [ @peak_runs ], \%energy ) );
    my $one_over_s = &sqr( $en_cont / $en_peak );
    print "en_cont = $en_cont GeV (energy at continuum point)\n";
    print "en_peak = $en_peak GeV (energy at peak point)\n";
    print "one_over_s = $one_over_s (en_cont^2 / en_peak^2)\n";
    print "\n";
    
    my $gam_cont = &sum( &get_set( [ @cont_runs ], \%gam_num_pass1 ) );
    my $gam_peak = &sum( &get_set( [ @peak_runs ], \%gam_num_pass1 ) );
    my $lumi_ratio = $gam_peak / $gam_cont * $one_over_s;
    my $lumi_ratio_err = $lumi_ratio * sqrt( 1. / $gam_cont + 1. / $gam_peak );
    print "gam_cont = $gam_cont (gamgam count at continuum)\n";
    print "gam_peak = $gam_peak (gamgam count at peak)\n";
    print "lumi_ratio = $lumi_ratio +/- $lumi_ratio_err " .
	"(gam_peak / gam_cont * one_over_s)\n";
    print "\n";

    my $h_cont = &sum( &get_set( [ @cont_runs ], \%h_num_pass1 ) );
    my $h_peak = &sum( &get_set( [ @peak_runs ], \%h_num_pass1 ) );
    my $h_pred = $h_cont * $one_over_s * $lumi_ratio;
    my $h_pred_err = $h_pred * sqrt( 1. / $h_cont +
				     &sqr( $lumi_ratio_err / $lumi_ratio ) );
    my $h_excess = $h_peak - $h_pred;
    my $h_excess_err = sqrt( $h_peak + &sqr( $h_pred_err ) );
    print "h_cont = $h_cont (hadron count at continuum)\n";
    print "h_peak = $h_peak (hadron count at peak)\n";
    print "h_pred = $h_pred +/- $h_pred_err (h_cont * one_over_s * lumi_ratio)\n";
    print "h_excess = $h_excess +/- $h_excess_err (h_peak - h_pred)\n";
    print "\n";

    my $ee_cont = &sum( &get_set( [ @cont_runs ], \%ee_num_pass1 ) );
    my $ee_peak = &sum( &get_set( [ @peak_runs ], \%ee_num_pass1 ) );
    my $ee_pred = $ee_cont * $one_over_s * $lumi_ratio;
    my $ee_pred_err = $ee_pred * sqrt( 1. / $ee_cont +
				       &sqr( $lumi_ratio_err / $lumi_ratio ) );
    my $ee_excess = $ee_peak - $ee_pred;
    my $ee_excess_err = sqrt( $ee_peak + &sqr( $ee_pred_err ) );
    print "ee_cont = $ee_cont (e+e- count at continuum)\n";
    print "ee_peak = $ee_peak (e+e- count at peak)\n";
    print "ee_pred = $ee_pred +/- $ee_pred_err (ee_cont * one_over_s * lumi_ratio)\n";
    print "ee_excess = $ee_excess +/- $ee_excess_err (ee_peak - ee_pred)\n";
    print "\n";

    my $mumu_cont = &sum( &get_set( [ @cont_runs ], \%mumu_num_pass1 ) );
    my $mumu_peak = &sum( &get_set( [ @peak_runs ], \%mumu_num_pass1 ) );
    my $mumu_pred = $mumu_cont * $one_over_s * $lumi_ratio;
    my $mumu_pred_err = $mumu_pred * sqrt( 1. / $mumu_cont +
					   &sqr( $lumi_ratio_err / $lumi_ratio ) );
    my $mumu_excess = $mumu_peak - $mumu_pred;
    my $mumu_excess_err = sqrt( $mumu_peak + &sqr( $mumu_pred_err ) );
    print "mumu_cont = $mumu_cont (mu+mu- count at continuum)\n";
    print "mumu_peak = $mumu_peak (mu+mu- count at peak)\n";
    print "mumu_pred = $mumu_pred +/- $mumu_pred_err " .
	"(mumu_cont * one_over_s * lumi_ratio)\n";
    print "mumu_excess = $mumu_excess +/- $mumu_excess_err (mumu_peak - mumu_pred)\n";
    print "\n";

#      my $total_excess = $h_excess + $ee_excess + 2. * $mumu_excess;
#      my $total_excess_err = sqrt( &sqr( $h_excess_err ) + &sqr( $ee_excess_err ) +
#  				 &sqr( 2. * $mumu_excess_err ) );
#      print "total_excess = $total_excess +/- $total_excess_err " .
#  	"(h_excess + ee_excess + 2. * mumu_excess)\n";
#      print "\n";

    my $total_excess = $h_excess + 3. * $ee_excess;
    my $total_excess_err = sqrt( &sqr( $h_excess_err ) + &sqr( $ee_excess_err ) +
				 &sqr( 2. * $mumu_excess_err ) );
    print "total_excess = $total_excess +/- $total_excess_err " .
	"(h_excess + 3. * ee_excess)\n";
    print "\n";

    my $ee_branching_fraction = $ee_excess / $total_excess;
    my $ee_branching_err = abs( $ee_branching_fraction ) *
	sqrt( &sqr( $ee_excess_err / $ee_excess ) +
	      &sqr( $total_excess_err / $total_excess ) );
    print "ee_branching_fraction = $ee_branching_fraction +/- $ee_branching_err " .
	"(ee_excess / total_excess)\n";
    print "\n";
    
    my $mumu_branching_fraction = $mumu_excess / $total_excess;
    my $mumu_branching_err = abs( $mumu_branching_fraction ) *
	sqrt( &sqr( $mumu_excess_err / $mumu_excess ) +
	      &sqr( $total_excess_err / $total_excess ) );
    print "mumu_branching_fraction = $mumu_branching_fraction +/- $mumu_branching_err" .
	" (mumu_excess / total_excess)\n";
    print "\n";

}

#########################################################################

sub get_runs {
    my $cond = @_[0];

    my $n = 0;
    my @good = ();
    foreach my $run_info_file ( @run_info_files ) {
	open( RUN_INFO, $run_info_file ) || die;
	my $indiv = 0;
	my $tag = "";
	my $title = "";

	print "Reading $run_info_file...\n";
	while ( my $line = <RUN_INFO> ) {
	    chop $line;

	    $indiv = 1 if ( $line =~ /<div/  &&  $line !~ /<\/div/ );
	    $indiv = 0 if ( $line =~ /<\/div/  &&  $line !~ /<div/ );
	    $indiv = 1 if ( $line =~ /<\/div.*<div/ );

	    $tag = $1
		if ( $indiv == 1  &&  $line =~ /<a\s+name\s*\=\s*\"([^\"]+)\"/ );

	    if ( $indiv == 1  &&  $line =~ /^[A-Za-z]+\s+[0-9]+/ ) {
		$title = sprintf( "%03d. %s", ++$n, $line );
		$title =~ s/<[^>]+>//g;
		$title =~ s/\s+$//;

		print "$title\n";
	    }

	    if ( $indiv == 1  &&
		 ( $line =~ /^([0-9]{6})/  ||  $line =~ /[^\#]{1}([0-9]{6})/ ) ) {
		my $run = $1;
		my $stripped = $line;
		$stripped =~ s/<[^>]+>//g;
		my $energy = substr( $stripped, 41, 9 );
		$energy =~ s/^\s+//;

		my $lumi_str = substr( $stripped, 50, 13 );
		$lumi = "n/a";
		$lumi = $1 if ( $lumi_str =~ /([0-9\.]+)/ );

		my $hxc_str = substr( $stripped, 64 );
		my $hxc = "n/a";
		$hxc = [ $1, $2 ]
		    if ( $hxc_str =~ /([0-9\.]+)\s+\+\/\-\s+([0-9\.]+)/ );

		my @run_line = ( $title, $run, $energy, $lumi, $hxc );
		if ( &$cond( @run_line ) ) {
		    push( @good, $run );
		    $tag{$run} = $tag;
		    $title{$run} = $title;
		    $energy{$run} = $energy;
		    $lumi{$run} = $lumi if ( $lumi ne "n/a" );

		    print $lumi{$run}."\n";

		    $hxc_online{$run} = $hxc if ( $hxc ne "n/a" );
		} # end if good
	    } # end if this is a good run
	} # end loop over lines
	close RUN_INFO;
    } # end foreach run info file
    return @good;
}
		 
#########################################################################

sub get_pass1 {
    opendir( LUMIS, $luminosities );
    my @lumis = readdir( LUMIS );
    closedir( LUMIS );

    my $col = 0;
    foreach my $file ( @lumis ) {
	next if ( $file !~ /^lumi\.[0-9]+$/  &&  $file !~ /^lumi\.[0-9]+\.gz$/ );

	print "    " if ( $col == 0 );
	printf "%-12s ", $file;
	$col++;
	if ( $col == 5 ) {
	    print "\n";
	    $col = 0;
	}

	if ( $file =~ /gz$/ ) {
	    open( PASS1, "gunzip -c $luminosities/$file |" );
	} else {
	    open( PASS1, "$luminosities/$file" );
	}
	while ( my $line = <PASS1> ) {
	    ( $hxc_pass1{$1}, $h_num_pass1{$1} ) = ( [ $2, $3 ], $4 )
		if ( $line =~ /^run([0-9]{6})\s+\*\s+CC Hadronic Cross Section \=\s+([0-9\.\-eE\+]+)\s+\+\-\s+([0-9\.\-eE\+]+)\s+nb\s+\(\s*([0-9]+)\)/ );

	    ( $ee_lum_pass1{$1}, $ee_num_pass1{$1} ) = ( [ $2, $3 ], $4 )
		if ( $line =~ /^run([0-9]{6})\s+Barrel Bhabha Lum\s+\=\s+BBLM\s+\=\s+([0-9\.\-eE\+]+)\s+\+\-\s+([0-9\.\-eE\+]+)\s+\/nb\s+\(\s*([0-9]+)\s*\)/ );

	    ( $gam_lum_pass1{$1}, $gam_num_pass1{$1} ) = ( [ $2, $3 ], $4 )
		if ( $line =~ /^run([0-9]{6})\s+Barrel GamGam Lum\s+\/BBLM\s+\=\s+([0-9\.\-eE\+]+)\s+\+\-\s+([0-9\.\-eE\+]+)\s+\(\s*([0-9]+)\s*\)/ );

	    ( $mumu_lum_pass1{$1}, $mumu_num_pass1{$1} ) = ( [ $2, $3 ], $4 )
		if ( $line =~ /^run([0-9]{6})\s+\*\s+CC MuPair\/Cosmic Cross Sec\s*\=\s+([0-9\.\-eE\+]+)\s+\+\-\s+([0-9\.\-eE\+]+)\s+nb\s+\(\s*([0-9]+)\s*\)/ );

	} # end loop through file
    } # end foreach file
    print "\n" if ( $col != 0 );

    return @runs;
}

#########################################################################

#  sub branching_fractions_old {
#      &get_pass1();

#      my @cont_runs = &get_runs( sub { &contQ(@_) && &Y3sQ(@_) && &biglumi(@_) } );
#      my @peak_runs = &get_runs( sub { &peakQ(@_) && &Y3sQ(@_) && &biglumi(@_) } );

#      my $en_cont = &mean( &get_set( [ @cont_runs ], \%energy ) );
#      print "en_cont = $en_cont GeV\n";
#      my $en_peak = &mean( &get_set( [ @peak_runs ], \%energy ) );
#      print "en_peak = $en_peak GeV\n\n";

#      my $one_over_s = $en_cont * $en_cont / $en_peak / $en_peak;

#      my $hxc_cont = &weighted_mean( &get_set( [ @cont_runs ], \%hxc_pass1 ) );
#      print "hxc_cont = $hxc_cont->[0] +/- $hxc_cont->[1] nb\n";
#      my $hxc_prop = [ $hxc_cont->[0] * $one_over_s,
#  		     $hxc_cont->[1] * $one_over_s ];
#      my $hxc_peak = &weighted_mean( &get_set( [ @peak_runs ], \%hxc_pass1 ) );
#      print "hxc_peak = $hxc_peak->[0] +/- $hxc_peak->[1] nb\n";
#      my $hxc_excess = [ $hxc_peak->[0] - $hxc_prop->[0],
#  		       sqrt( $hxc_peak->[1] * $hxc_peak->[1] +
#  			     $hxc_prop->[1] * $hxc_prop->[1] ) ];
#      print "hxc_excess = $hxc_excess->[0] +/- $hxc_excess->[1] nb\n\n";

#      my $h_num_cont = &weighted_mean( &generate_uncertanties( &get_set(
#  		       [ @cont_runs ], \%h_num_pass1 ) ) );
#      print "h_num_cont = $h_num_cont->[0] +/- $h_num_cont->[1]\n";
#      my $h_num_prop = [ $h_num_cont->[0] * $one_over_s,
#  		       $h_num_cont->[1] * $one_over_s ];
#      my $h_num_peak = &weighted_mean( &generate_uncertanties( &get_set(
#  		       [ @peak_runs ], \%h_num_pass1 ) ) );
#      print "h_num_peak = $h_num_peak->[0] +/- $h_num_peak->[1]\n";
#      my $h_num_excess = [ $h_num_peak->[0] - $h_num_prop->[0],
#  			 sqrt( $h_num_peak->[1] * $h_num_peak->[1] +
#  			       $h_num_prop->[1] * $h_num_prop->[1] ) ];
#      print "h_num_excess = $h_num_excess->[0] +/- $h_num_excess->[1]\n\n";

#      my $ee_cont = &weighted_mean( &generate_uncertanties( &get_set(
#  		       [ @cont_runs ], \%ee_num_pass1 ) ) );
#      print "ee_cont = $ee_cont->[0] +/- $ee_cont->[1]\n";
#      my $ee_prop = [ $ee_cont->[0] * $one_over_s,
#  		    $ee_cont->[1] * $one_over_s ];
#      my $ee_peak = &weighted_mean( &generate_uncertanties( &get_set(
#  		       [ @peak_runs ], \%ee_num_pass1 ) ) );
#      print "ee_peak = $ee_peak->[0] +/- $ee_peak->[1]\n";
#      my $ee_excess = [ $ee_peak->[0] - $ee_prop->[0],
#  		      sqrt( $ee_peak->[1] * $ee_peak->[1] +
#  			    $ee_prop->[1] * $ee_prop->[1] ) ];
#      print "ee_excess = $ee_excess->[0] +/- $ee_excess->[1]\n\n";

#      my $mumu_cont = &weighted_mean( &generate_uncertanties( &get_set(
#  		       [ @cont_runs ], \%mumu_num_pass1 ) ) );
#      print "mumu_cont = $mumu_cont->[0] +/- $mumu_cont->[1]\n";
#      my $mumu_prop = [ $mumu_cont->[0] * $one_over_s,
#  		     $mumu_cont->[1] * $one_over_s ];
#      my $mumu_peak = &weighted_mean( &generate_uncertanties( &get_set(
#  		       [ @peak_runs ], \%mumu_num_pass1 ) ) );
#      print "mumu_peak = $mumu_peak->[0] +/- $mumu_peak->[1]\n";
#      my $mumu_excess = [ $mumu_peak->[0] - $mumu_prop->[0],
#  		       sqrt( $mumu_peak->[1] * $mumu_peak->[1] +
#  			     $mumu_prop->[1] * $mumu_prop->[1] ) ];
#      print "mumu_excess = $mumu_excess->[0] +/- $mumu_excess->[1]\n\n";

#      my $ee_branching_fraction =
#  	$ee_excess->[0] / ( $h_num_excess->[0] +
#  			    $ee_excess->[0] + 2. * $mumu_excess->[0] );
#      my $ee_branching_fraction_err = $ee_branching_fraction *
#  	sqrt( &sqr( $h_num_excess->[1] / $h_num_excess->[0] ) +
#  	      ( &sqr( $h_num_excess->[1] ) +
#  		&sqr( $ee_excess->[1] ) + 2. * &sqr( $mumu_excess->[1] ) ) /
#  	      &sqr( $h_num_excess->[0] +
#  		    $ee_excess->[0] + 2. * $mumu_excess->[0] ) );
#      print "ee_branching_function = $ee_branching_fraction" .
#  	" +/- $ee_branching_fraction_err\n";
#      print "There isn't an expected value, but I would think it" .
#  	" should be smaller than this!\n\n";

#      my $mumu_branching_fraction =
#  	$mumu_excess->[0] / ( $h_num_excess->[0] +
#  			    $ee_excess->[0] + 2. * $mumu_excess->[0] );
#      my $mumu_branching_fraction_err = $mumu_branching_fraction *
#  	sqrt( &sqr( $h_num_excess->[1] / $h_num_excess->[0] ) +
#  	      ( &sqr( $h_num_excess->[1] ) +
#  		&sqr( $ee_excess->[1] ) + 2. * &sqr( $mumu_excess->[1] ) ) /
#  	      &sqr( $h_num_excess->[0] +
#  		    $ee_excess->[0] + 2. * $mumu_excess->[0] ) );
#      print "mumu_branching_function = $mumu_branching_fraction" .
#  	" +/- $mumu_branching_fraction_err\n";
#      print "This should be 0.0181 +/- 0.0017 for the Y(3s).\n\n";

#      my $gam_cont = &weighted_mean( &generate_uncertanties( &get_set(
#  		       [ @cont_runs ], \%gam_num_pass1 ) ) );
#      print "gam_cont = $gam_cont->[0] +/- $gam_cont->[1]\n";
#      my $gam_prop = [ $gam_cont->[0] * $one_over_s,
#  		     $gam_cont->[1] * $one_over_s ];
#      my $gam_peak = &weighted_mean( &generate_uncertanties( &get_set(
#  		       [ @peak_runs ], \%gam_num_pass1 ) ) );
#      print "gam_peak = $gam_peak->[0] +/- $gam_peak->[1]\n";
#      my $gam_excess = [ $gam_peak->[0] - $gam_prop->[0],
#  		       sqrt( $gam_peak->[1] * $gam_peak->[1] +
#  			     $gam_prop->[1] * $gam_prop->[1] ) ];
#      print "gam_excess = $gam_excess->[0] +/- $gam_excess->[1]\n\n";

#      my $gam_branching_fraction =
#  	$gam_excess->[0] / ( $h_num_excess->[0] +
#  			    $ee_excess->[0] + 2. * $mumu_excess->[0] );
#      my $gam_branching_fraction_err = $gam_branching_fraction *
#  	sqrt( &sqr( $h_num_excess->[1] / $h_num_excess->[0] ) +
#  	      ( &sqr( $h_num_excess->[1] ) +
#  		&sqr( $ee_excess->[1] ) + 2. * &sqr( $mumu_excess->[1] ) ) /
#  	      &sqr( $h_num_excess->[0] +
#  		    $ee_excess->[0] + 2. * $mumu_excess->[0] ) );
#      print "gam_branching_function = $gam_branching_fraction" .
#  	" +/- $gam_branching_fraction_err\n";
#      print "Interpreting this as \"Y(3s)-->Y(2s)\" gam gam, this should be" .
#  	" 0.050 +/- 0.007. (What are the gam gam cuts?)\n\n";
#  }

#  &get_pass1();
#  open( NTUPLE, "> tmp.ntuple" );
#  foreach my $run ( &get_runs( sub { &Y3sQ(@_) } ) ) {
#      if ( $mumu_num_pass1{$run} > 0.  &&  $gam_num_pass1{$run} ) {
#  	print NTUPLE ( "$energy{$run}\t" .
#  		       $mumu_num_pass1{$run} / $gam_num_pass1{$run} . "\t" .
#  		       ( $mumu_num_pass1{$run} / $gam_num_pass1{$run} ) *
#  		       sqrt( 1. / $mumu_num_pass1{$run} +
#  			     1. / $gam_num_pass1{$run} ) . "\n" );
#      }
#  }

