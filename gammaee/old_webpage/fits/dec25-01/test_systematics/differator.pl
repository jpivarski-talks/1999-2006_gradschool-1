#!/usr/local/bin/perl

%region = (
           122567 => "H",
           122568 => "H",
           122569 => "H",
           122570 => "H",
           122571 => "H",
           122572 => "H",
           122573 => "H",
           122574 => "H",
           122575 => "H",
           122576 => "P",
           122577 => "P",
           122578 => "P",
           122579 => "P",
           122585 => "C",
           122586 => "C",
           122587 => "C",
           122590 => "C",
           122593 => "C",
           122594 => "C",
           122595 => "C",
           122596 => "C",
           122599 => "C",
           122600 => "C",
           122602 => "C",
           122603 => "C",
           122604 => "C",
           122605 => "C",
           122606 => "C",
           122608 => "P",
           122610 => "P",
           122613 => "P",
           122614 => "P",
           122615 => "P",
           122616 => "P",
           122617 => "P",
           122618 => "P",
           122619 => "P",
           122620 => "P",
           122622 => "P",
           122623 => "P",
           122625 => "P",
           122626 => "P",
           122627 => "P",
           122628 => "P",
           122629 => "P",
           122630 => "P",
           122631 => "P",
           122632 => "P",
           122634 => "P",
           122640 => "P",
           122641 => "P",
           122642 => "P",
           122643 => "P",
           122646 => "P",
           122647 => "P",
           122648 => "P",
           122649 => "P",
           122650 => "P",
           122653 => "P",
           122654 => "P",
           122657 => "P",
           122658 => "P",
           122661 => "P",
           122665 => "P",
           122667 => "P",
           122668 => "P",
           122669 => "P",
           122672 => "P",
           122673 => "P",
           );

%lumi = (
	 122536 => [1296.2, 10.3],
	 122537 => [1336.0, 10.4],
	 122538 => [1292.9, 10.2],
	 122539 => [1300.5, 10.3],
	 122540 => [1225.4, 10.0],
	 122541 => [1213.0, 9.9],
	 122542 => [1129.7, 9.6],
	 122545 => [1165.6, 9.7],
	 122546 => [163.5, 3.6],
	 122548 => [1126.5, 9.6],
	 122549 => [1383.6, 10.6],
	 122550 => [1301.9, 10.3],
	 122551 => [1314.1, 10.3],
	 122555 => [844.7, 8.3],
	 122556 => [870.3, 8.4],
	 122557 => [853.5, 8.3],
	 122559 => [1175.9, 9.8],
	 122560 => [1140.3, 9.6],
	 122562 => [1114.4, 9.5],
	 122563 => [1088.6, 9.4],
	 122564 => [1252.0, 10.1],
	 122567 => [60.6, 2.2],
	 122568 => [1057.3, 9.3],
	 122569 => [924.2, 8.7],
	 122570 => [1676.7, 11.7],
	 122571 => [1645.6, 11.5],
	 122572 => [1725.4, 11.8],
	 122573 => [1737.6, 11.9],
	 122574 => [1301.5, 10.3],
	 122575 => [1189.6, 9.8],
	 122576 => [362.5, 5.4],
	 122577 => [1314.9, 10.3],
	 122578 => [109.3, 3.0],
	 122579 => [442.6, 6.0],
	 122585 => [1675.7, 11.7],
	 122586 => [1670.6, 11.6],
	 122587 => [1660.5, 11.6],
	 122590 => [1415.6, 10.7],
	 122593 => [685.9, 7.5],
	 122594 => [755.9, 7.8],
	 122595 => [178.9, 3.8],
	 122596 => [1309.9, 10.3],
	 122599 => [419.7, 5.8],
	 122600 => [106.2, 2.9],
	 122602 => [1740.0, 11.9],
	 122603 => [1818.1, 12.1],
	 122604 => [1789.9, 12.0],
	 122605 => [1811.3, 12.1],
	 122606 => [558.7, 6.7],
	 122608 => [1769.9, 12.0],
	 122610 => [1923.4, 12.5],
	 122613 => [624.9, 7.1],
	 122614 => [2341.3, 13.8],
	 122615 => [2336.3, 13.8],
	 122616 => [2300.1, 13.7],
	 122618 => [2249.3, 13.5],
	 122619 => [2340.0, 13.8],
	 122620 => [2346.7, 13.8],
	 122622 => [203.2, 4.1],
	 122623 => [1012.8, 9.1],
	 122625 => [1662.3, 11.6],
	 122626 => [2178.6, 13.3],
	 122627 => [154.2, 3.5],
	 122628 => [525.8, 6.5],
	 122629 => [2253.8, 13.5],
	 122631 => [577.4, 6.8],
	 122632 => [658.6, 7.3],
	 122634 => [851.4, 8.3],
	 122640 => [1306.3, 10.3],
	 122641 => [2159.8, 13.2],
	 122642 => [2359.4, 13.8],
	 122643 => [2016.9, 12.8],
	 122646 => [1091.1, 9.4],
	 122647 => [891.5, 8.5],
	 122648 => [1190.9, 9.8],
	 122649 => [2331.6, 13.7],
	 122650 => [2163.6, 13.2],
	 122653 => [2387.3, 13.9],
	 122654 => [2075.0, 13.0],
	 122657 => [1260.3, 10.1],
	 122658 => [909.2, 8.6],
	 122661 => [740.9, 7.7],
	 122665 => [1663.6, 11.6],
	 122667 => [1180.8, 9.8],
	 122668 => [129.5, 3.2],
	 122669 => [176.5, 3.8],
	 122672 => [2250.7, 13.5],
	 122673 => [2303.8, 13.7],
	 );

open( ONE, $ARGV[0] );
open( TWO, $ARGV[1] );

$onecontnumer = 0;
$onecontdenom = 0;
$twocontnumer = 0;
$twocontdenom = 0;

$onepeaknumer = 0;
$onepeakdenom = 0;
$twopeaknumer = 0;
$twopeakdenom = 0;

$onehighnumer = 0;
$onehighdenom = 0;
$twohighnumer = 0;
$twohighdenom = 0;

while(<ONE>) {
    chop;
    (my $run, my $energy, my $number) = split(/\s+/);
    next if ( !defined( $region{$run} ) );

    $energy *= 2.;
    $energyMeV = $energy * 1000.;

    die if ( !defined($lumi{$run}) );
    my $l = $lumi{$run}->[0];
    my $le = $lumi{$run}->[1];

    my $hxc, $hxce;
    if ( $ARGV[2] == 2 ) {
	my $parent_hxc = `echo "77.05870 10.35820 4.668636 0 0.0263 $energyMeV" | ./spitout`;
	chop $parent_hxc;
	my $ups3sToEE_xc = 0.0181 * $parent_hxc;
	
	# in datasucker, you only used barrel bhabha luminosity
	# measurements, so that's the cross-section you'll use here. I'm
	# including the rest for completeness.
	#
	# In P1LumiMonProc.cc:
	# 	  const double k_barrelBhabhaCS ( 11.8271    ) ;
	# 	  const double k_barrelGamGamCS (  1.3948*0.988 ) ; // fac for trig losses @90deg
	# 	  const double k_endcapBhabhaCS ( 22.93  /4. ) ;
	# 	  const double k_endcapGamGamCS (  0.5721/4. ) ;
	# (these are at 5.29 GeV)
	my $bhabha_xc = 11.8271 * sqr(10580. / $energyMeV);
	my $all_ee_xc = $bhabha_xc + $ups3sToEE_xc; # I know this is an overestimate due to interference

	my $ee_count = $l * 11.8271 * sqr(10580. / $energyMeV);
	my $true_l = $ee_count / $all_ee_xc;
	my $true_le = $true_l / sqrt($ee_count);
	
	$hxc = $number / $true_l;
	$hxce = $hxc * sqrt(1/$number + ($true_le/$true_l)*($true_le/$true_l));
    }
    elsif ( $ARGV[2] == 1 ) {
	$hxc = $number / $l;
	$hxce = $hxc * sqrt(1/$number + ($le/$l)*($le/$l));
    }
    else { die; }

    my $weight = 1. / sqr($hxce);
    if ( $region{$run} eq "P" ) {
	$onepeaknumer += $hxc * $weight;
	$onepeakdenom += $weight;
    }
    elsif ( $region{$run} eq "C" ) {
	$onecontnumer += $hxc * $weight;
	$onecontdenom += $weight;
    }
    elsif ( $region{$run} eq "H" ) {
	$onehighnumer += $hxc * $weight;
	$onehighdenom += $weight;
    }
    else { die; }
}

while(<TWO>) {
    chop;
    (my $run, my $energy, my $number) = split(/\s+/);
    next if ( !defined( $region{$run} ) );

    $energy *= 2.;
    $energyMeV = $energy * 1000.;

    die if ( !defined($lumi{$run}) );
    my $l = $lumi{$run}->[0];
    my $le = $lumi{$run}->[1];

    my $hxc, $hxce;
    if ( $ARGV[3] == 2 ) {
	my $parent_hxc = `echo "77.05870 10.35820 4.668636 0 0.0263 $energyMeV" | ./spitout`;
	chop $parent_hxc;
	my $ups3sToEE_xc = 0.0181 * $parent_hxc;
	
	# in datasucker, you only used barrel bhabha luminosity
	# measurements, so that's the cross-section you'll use here. I'm
	# including the rest for completeness.
	#
	# In P1LumiMonProc.cc:
	# 	  const double k_barrelBhabhaCS ( 11.8271    ) ;
	# 	  const double k_barrelGamGamCS (  1.3948*0.988 ) ; // fac for trig losses @90deg
	# 	  const double k_endcapBhabhaCS ( 22.93  /4. ) ;
	# 	  const double k_endcapGamGamCS (  0.5721/4. ) ;
	# (these are at 5.29 GeV)
	my $bhabha_xc = 11.8271 * sqr(10580. / $energyMeV);
	my $all_ee_xc = $bhabha_xc + $ups3sToEE_xc; # I know this is an overestimate due to interference

	my $ee_count = $l * 11.8271 * sqr(10580. / $energyMeV);
	my $true_l = $ee_count / $all_ee_xc;
	my $true_le = $true_l / sqrt($ee_count);
	
	$hxc = $number / $true_l;
	$hxce = $hxc * sqrt(1/$number + ($true_le/$true_l)*($true_le/$true_l));
    }
    elsif ( $ARGV[3] == 1 ) {
	$hxc = $number / $l;
	$hxce = $hxc * sqrt(1/$number + ($le/$l)*($le/$l));
    }
    else { die; }

    my $weight = 1. / sqr($hxce);
    if ( $region{$run} eq "P" ) {
	$twopeaknumer += $hxc * $weight;
	$twopeakdenom += $weight;
    }
    elsif ( $region{$run} eq "C" ) {
	$twocontnumer += $hxc * $weight;
	$twocontdenom += $weight;
    }
    elsif ( $region{$run} eq "H" ) {
	$twohighnumer += $hxc * $weight;
	$twohighdenom += $weight;
    }
    else { die; }
}

$onecont = $onecontnumer / $onecontdenom;
$oneconte = sqrt( 1. / $onecontdenom );
$twocont = $twocontnumer / $twocontdenom;
$twoconte = sqrt( 1. / $twocontdenom );

$onepeak = $onepeaknumer / $onepeakdenom;
$onepeake = sqrt( 1. / $onepeakdenom );
$twopeak = $twopeaknumer / $twopeakdenom;
$twopeake = sqrt( 1. / $twopeakdenom );

$onehigh = $onehighnumer / $onehighdenom;
$onehighe = sqrt( 1. / $onehighdenom );
$twohigh = $twohighnumer / $twohighdenom;
$twohighe = sqrt( 1. / $twohighdenom );

printf( "           CONT                   PEAK                   HIGH\n" );
printf( "           =====================================================================\n" );
printf( "First  has %6.3f +/- %6.3f nb   %6.3f +/- %6.3f nb   %6.3f +/- %6.3f nb\n",
	$onecont, $oneconte, $onepeak, $onepeake, $onehigh, $onehighe );
printf( "Second has %6.3f +/- %6.3f nb   %6.3f +/- %6.3f nb   %6.3f +/- %6.3f nb\n",
	$twocont, $twoconte, $twopeak, $twopeake, $twohigh, $twohighe );
printf( "Diff   is  %6.3f +/- %6.3f nb   %6.3f +/- %6.3f nb   %6.3f +/- %6.3f nb\n",
	($onecont - $twocont), sqrt(sqr($oneconte) + sqr($twoconte)),
	($onepeak - $twopeak), sqrt(sqr($onepeake) + sqr($twopeake)),
	($onehigh - $twohigh), sqrt(sqr($onehighe) + sqr($twohighe)) );

print "\n(Don't trust those uncertainties.)\n\n";

$onepeakheight = $onepeak - $onecont * 0.994498;
$onehighheight = $onehigh - $onecont * 0.986777;
$twopeakheight = $twopeak - $twocont * 0.994498;
$twohighheight = $twohigh - $twocont * 0.986777;

printf( "First  above continuum            %6.3f                %6.3f\n",
	$onepeakheight, $onehighheight );
printf( "Second above continuum            %6.3f                %6.3f\n\n",
	$twopeakheight, $twohighheight );

printf( "Bias                              %6.3f%s               %6.3f%s\n",
	(100. * ($onepeakheight - $twopeakheight) / $onepeakheight), "%",
	(100. * ($onehighheight - $twohighheight) / $onehighheight), "%" );

sub sqr { return $_[0] * $_[0]; }
