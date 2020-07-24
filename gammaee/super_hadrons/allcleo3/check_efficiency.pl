#!/usr/local/bin/perl

@y1scont = (123369..123382, 123565..123592, 123767..123775,
	    123793..123820, 123938..123962, 124113..124141,
	    124299..124326, 124454..124478, 124644..124668,
	    124807..124821, 125158..125178);
@y1s = (123180..123202, 123396..123504, 123543..123564,
	123610..123718, 123821..123898, 123963..124040,
	124142..124280, 124328..124398, 124479..124548,
	124671..124739, 124822..124917, 125149..125155,
	125179..125253, 125316..125370);
@y2scont = (126252..126274, 126648..126673, 126832..126856);
@y2s = (126275..126376, 126496..126579, 126675..126749,
	126858..126937);
@y3scont = (121899..121915, 122080..122091, 122264..122273,
	    122418..122434, 122585..122606, 122783..122810,
	    123011..123019);
@y3s = (121916..122062, 122092..122244, 122274..122407,
	122437..122534, 122608..122765, 122812..122911,
	123020..123065);

%file = ();
foreach $db ("DATA16", "DATA17", "DATA18") {
    open(LS, "ls /home/pass2/Pass2Production/pass2/Pass2ReproScripts/$db/Log*/*_pass2.log* |");
    while (<LS>) {
	chop;
	if ( $_ =~ /([0-9]{6})_pass2\.log/ ) {
	    $file{$1} = $_;
	}
    }
}

%betweenCuts = ();
%numberOfEvents = ();
%numberOfEventsStat = ();
%numberOfEventsSyst = ();
%luminosity = ();
%luminosityStat = ();
%luminositySyst = ();

sub sqr { $_[0] * $_[0]; }

open(COLLECTION, "/home/mccann/super_hadrons/allcleo3/dafedir/collection2.dat");
while (my $line = <COLLECTION>) {
    chop($line);
    my ($run,
	$passed, $subtotal,
	$beamgas, $bgstat, $bgsyst,
	$cosmics, $cstat, $csyst)
	= split("\t", $line);
    $betweenCuts{$run} = $subtotal;
    $numberOfEvents{$run} = $passed - $beamgas - $cosmics;
    $numberOfEventsStat{$run} = sqrt($passed + &sqr($bgstat) + &sqr($cstat));
    $numberOfEventsSyst{$run} = $bgsyst + $csyst;
}
close(COLLECTION);

open(RUNINFO, "/nfs/cleo3/Offline/InfoFiles/data/runinfo.runinfo");
while (my $line = <RUNINFO>) {
    chop($line);
    my ($run,
	$evts, $had, $last,
	$bhalum, $bbstat, $bbsyst,
	$e_cor, $e_uncor,
	$b_cor, $b_uncor,
	$gglum, $ggstat, $ggsyst,
	$db)
	= split(/\s+/, substr($line, 2));
    $luminosity{$run} = $gglum;
    $luminosityStat{$run} = $ggstat;
    $luminositySyst{$run} = $ggsyst;
}
close(RUNINFO);

#######################################################################################

$lumi = 0;
$lumi_err = 0;
$lumi_syst = 0;
$allsuperpassed = 0;
$allsuperpassed_err = 0;
$allsuperpassed_syst = 0;
$allpassed = 0;
$alltotal = 0;
$nominal_energy = 4.71674;
foreach $run ( @y1scont ) {
    next if ( ! defined($file{$run})  ||  ! defined($numberOfEvents{$run}) );
    my ($passed, $total) = &scanlog($run, $nominal_energy);

    if ( $passed - $betweenCuts{$run} < 0 ) { print "Ack! $run $passed != $betweenCuts{$run}\n"; }
    else {
	$lumi += $luminosity{$run};
	$lumi_err += &sqr($luminosityStat{$run});
	$lumi_syst += $luminositySyst{$run};
	$allsuperpassed += $numberOfEvents{$run};
	$allsuperpassed_err += &sqr($numberOfEventsStat{$run});
	$allsuperpassed_syst += $numberOfEventsSyst{$run} + ($passed - $betweenCuts{$run});
	$allpassed += $passed;
	$alltotal += $total;
    }
}
$lumi_err = sqrt($lumi_err);
$allsuperpassed_err = sqrt($allsuperpassed_err);
print "(* lumi is $lumi +/- $lumi_err +/- $lumi_syst *)\n";
print "
(* For Y(1S) *)
Pc = $allsuperpassed;
dPc = $allsuperpassed_err;
stepPc = $allsuperpassed_syst;
Nc = $alltotal;
dNc = Sqrt[Nc];
sigc = ".($allsuperpassed/$lumi).";
dsigc = ".($allsuperpassed/$lumi * sqrt(&sqr($allsuperpassed_err/$allsuperpassed) + &sqr($lumi_err/$lumi))).";
stepsigc = ".($allsuperpassed/$lumi - ($allsuperpassed-$allsuperpassed_syst)/($lumi+$lumi_syst))."; \"Evaluated.\"

";

$lumi = 0;
$lumi_err = 0;
$lumi_syst = 0;
$allsuperpassed = 0;
$allsuperpassed_err = 0;
$allsuperpassed_syst = 0;
$allpassed = 0;
$alltotal = 0;
$nominal_energy = 4.73006;
foreach $run ( @y1s ) {
    next if ( ! defined($file{$run})  ||  ! defined($numberOfEvents{$run}) );
    my ($passed, $total) = &scanlog($run, $nominal_energy);
    if ( $passed - $betweenCuts{$run} < 0 ) { print "Ack! $run $passed != $betweenCuts{$run}\n"; }
    else {
	$lumi += $luminosity{$run};
	$lumi_err += &sqr($luminosityStat{$run});
	$lumi_syst += $luminositySyst{$run};
	$allsuperpassed += $numberOfEvents{$run};
	$allsuperpassed_err += &sqr($numberOfEventsStat{$run});
	$allsuperpassed_syst += $numberOfEventsSyst{$run} + ($passed - $betweenCuts{$run});
	$allpassed += $passed;
	$alltotal += $total;
    }
}
$lumi_err = sqrt($lumi_err);
$allsuperpassed_err = sqrt($allsuperpassed_err);
print "(* lumi is $lumi +/- $lumi_err +/- $lumi_syst *)\n";
print "
(* For Y(1S) *)
Pp = $allsuperpassed;
dPp = $allsuperpassed_err;
stepPp = $allsuperpassed_syst;
Np = $alltotal;
dNp = Sqrt[Np];
sigp = ".($allsuperpassed/$lumi).";
dsigp = ".($allsuperpassed/$lumi * sqrt(&sqr($allsuperpassed_err/$allsuperpassed) + &sqr($lumi_err/$lumi))).";
stepsigp = ".($allsuperpassed/$lumi - ($allsuperpassed-$allsuperpassed_syst)/($lumi+$lumi_syst))."; \"Evaluated.\"

";

# $lumi = 0;
# $lumi_err = 0;
# $lumi_syst = 0;
# $allsuperpassed = 0;
# $allsuperpassed_err = 0;
# $allsuperpassed_syst = 0;
# $allpassed = 0;
# $alltotal = 0;
# $nominal_energy = 4.99860;
# foreach $run ( @y2scont ) {
#     next if ( ! defined($file{$run})  ||  ! defined($numberOfEvents{$run}) );
#     my ($passed, $total) = &scanlog($run, $nominal_energy);
#     if ( $passed - $betweenCuts{$run} < 0 ) { print "Ack! $run $passed != $betweenCuts{$run}\n"; }
#     else {
# 	$lumi += $luminosity{$run};
# 	$lumi_err += &sqr($luminosityStat{$run});
# 	$lumi_syst += $luminositySyst{$run};
# 	$allsuperpassed += $numberOfEvents{$run};
# 	$allsuperpassed_err += &sqr($numberOfEventsStat{$run});
# 	$allsuperpassed_syst += $numberOfEventsSyst{$run} + ($passed - $betweenCuts{$run});
# 	$allpassed += $passed;
# 	$alltotal += $total;
#     }
# }
# $lumi_err = sqrt($lumi_err);
# $allsuperpassed_err = sqrt($allsuperpassed_err);
# print "(* lumi is $lumi +/- $lumi_err +/- $lumi_syst *)\n";
# print "
# (* For Y(2S) *)
# Pc = $allsuperpassed;
# dPc = $allsuperpassed_err;
# stepPc = $allsuperpassed_syst;
# Nc = $alltotal;
# dNc = Sqrt[Nc];
# sigc = ".($allsuperpassed/$lumi).";
# dsigc = ".($allsuperpassed/$lumi * sqrt(&sqr($allsuperpassed_err/$allsuperpassed) + &sqr($lumi_err/$lumi))).";
# stepsigc = ".($allsuperpassed/$lumi - ($allsuperpassed-$allsuperpassed_syst)/($lumi+$lumi_syst))."; \"Evaluated.\"

# ";

# $lumi = 0;
# $lumi_err = 0;
# $lumi_syst = 0;
# $allsuperpassed = 0;
# $allsuperpassed_err = 0;
# $allsuperpassed_syst = 0;
# $allpassed = 0;
# $alltotal = 0;
# $nominal_energy = 5.01259;
# foreach $run ( @y2s ) {
#     next if ( ! defined($file{$run})  ||  ! defined($numberOfEvents{$run}) );
#     my ($passed, $total) = &scanlog($run, $nominal_energy);
#     if ( $passed - $betweenCuts{$run} < 0 ) { print "Ack! $run $passed != $betweenCuts{$run}\n"; }
#     else {
# 	$lumi += $luminosity{$run};
# 	$lumi_err += &sqr($luminosityStat{$run});
# 	$lumi_syst += $luminositySyst{$run};
# 	$allsuperpassed += $numberOfEvents{$run};
# 	$allsuperpassed_err += &sqr($numberOfEventsStat{$run});
# 	$allsuperpassed_syst += $numberOfEventsSyst{$run} + ($passed - $betweenCuts{$run});
# 	$allpassed += $passed;
# 	$alltotal += $total;
#     }
# }
# $lumi_err = sqrt($lumi_err);
# $allsuperpassed_err = sqrt($allsuperpassed_err);
# print "(* lumi is $lumi +/- $lumi_err +/- $lumi_syst *)\n";
# print "
# (* For Y(2S) *)
# Pp = $allsuperpassed;
# dPp = $allsuperpassed_err;
# stepPp = $allsuperpassed_syst;
# Np = $alltotal;
# dNp = Sqrt[Np];
# sigp = ".($allsuperpassed/$lumi).";
# dsigp = ".($allsuperpassed/$lumi * sqrt(&sqr($allsuperpassed_err/$allsuperpassed) + &sqr($lumi_err/$lumi))).";
# stepsigp = ".($allsuperpassed/$lumi - ($allsuperpassed-$allsuperpassed_syst)/($lumi+$lumi_syst))."; \"Evaluated.\"

# ";

$lumi = 0;
$lumi_err = 0;
$lumi_syst = 0;
$allsuperpassed = 0;
$allsuperpassed_err = 0;
$allsuperpassed_syst = 0;
$allpassed = 0;
$alltotal = 0;
$nominal_energy = 5.16479;
foreach $run ( @y3scont ) {
    next if ( ! defined($file{$run})  ||  ! defined($numberOfEvents{$run}) );
    my ($passed, $total) = &scanlog($run, $nominal_energy);
    if ( $passed - $betweenCuts{$run} < 0 ) { print "Ack! $run $passed != $betweenCuts{$run}\n"; }
    else {
	$lumi += $luminosity{$run};
	$lumi_err += &sqr($luminosityStat{$run});
	$lumi_syst += $luminositySyst{$run};
	$allsuperpassed += $numberOfEvents{$run};
	$allsuperpassed_err += &sqr($numberOfEventsStat{$run});
	$allsuperpassed_syst += $numberOfEventsSyst{$run} + ($passed - $betweenCuts{$run});
	$allpassed += $passed;
	$alltotal += $total;
    }
}
$lumi_err = sqrt($lumi_err);
$allsuperpassed_err = sqrt($allsuperpassed_err);
print "(* lumi is $lumi +/- $lumi_err +/- $lumi_syst *)\n";
print "
(* For Y(3S) *)
Pc = $allsuperpassed;
dPc = $allsuperpassed_err;
stepPc = $allsuperpassed_syst;
Nc = $alltotal;
dNc = Sqrt[Nc];
sigc = ".($allsuperpassed/$lumi).";
dsigc = ".($allsuperpassed/$lumi * sqrt(&sqr($allsuperpassed_err/$allsuperpassed) + &sqr($lumi_err/$lumi))).";
stepsigc = ".($allsuperpassed/$lumi - ($allsuperpassed-$allsuperpassed_syst)/($lumi+$lumi_syst))."; \"Evaluated.\"

";

$lumi = 0;
$lumi_err = 0;
$lumi_syst = 0;
$allsuperpassed = 0;
$allsuperpassed_err = 0;
$allsuperpassed_syst = 0;
$allpassed = 0;
$alltotal = 0;
$nominal_energy = 5.17973;
foreach $run ( @y3s ) {
    next if ( ! defined($file{$run})  ||  ! defined($numberOfEvents{$run}) );
    my ($passed, $total) = &scanlog($run, $nominal_energy);
    if ( $passed - $betweenCuts{$run} < 0 ) { print "Ack! $run $passed != $betweenCuts{$run}\n"; }
    else {
	$lumi += $luminosity{$run};
	$lumi_err += &sqr($luminosityStat{$run});
	$lumi_syst += $luminositySyst{$run};
	$allsuperpassed += $numberOfEvents{$run};
	$allsuperpassed_err += &sqr($numberOfEventsStat{$run});
	$allsuperpassed_syst += $numberOfEventsSyst{$run} + ($passed - $betweenCuts{$run});
	$allpassed += $passed;
	$alltotal += $total;
    }
}
$lumi_err = sqrt($lumi_err);
$allsuperpassed_err = sqrt($allsuperpassed_err);
print "(* lumi is $lumi +/- $lumi_err +/- $lumi_syst *)\n";
print "
(* For Y(3S) *)
Pp = $allsuperpassed;
dPp = $allsuperpassed_err;
stepPp = $allsuperpassed_syst;
Np = $alltotal;
dNp = Sqrt[Np];
sigp = ".($allsuperpassed/$lumi).";
dsigp = ".($allsuperpassed/$lumi * sqrt(&sqr($allsuperpassed_err/$allsuperpassed) + &sqr($lumi_err/$lumi))).";
stepsigp = ".($allsuperpassed/$lumi - ($allsuperpassed-$allsuperpassed_syst)/($lumi+$lumi_syst))."; \"Evaluated.\"

";

#######################################################################################

sub scanlog {
    my ($run, $nominal_energy) = @_;

    if ( $file{$run} =~ /gz$/ ) {
	open(LOG, "gunzip -c $file{$run} |");
    } else {
	open(LOG, $file{$run});
    }

    my $badrun = 0;
    my $done = 0;
    my $total = 0;
    my $passed = 0;
    while (($done == 0)  &&  ($_ = <LOG>)) {
	if ( substr($_, 0, 22) eq "   *    Beam Energy = "  &&
	     $_ =~ /Energy\s+=\s+([0-9\.\-\+eE]+)\s+GeV/ ) {
	    if ( abs($1 - $nominal_energy) > 0.010 ) {
		print "BADRUN $run!\n";
		$badrun = 1;
		$done = 1;
	    }
	}

	if ( substr($_, 0, 49) eq " ****** Summary from EventTypeFilterProc **** for"  &&
	     $_ =~ /for\s+([0-9]+)\s+events/ ) {
	    $total = $1;
	}

	if ( substr($_, 0, 10) eq "T00 Hadron"  &&
	     $_ =~ /Hadron\s+([0-9]+)\s+([0-9]+)/ ) {
	    $passed = $1 + $2
	    }

	if ( $passed > 0  &&  $total > 0 ) { $done = 1; }
    }

    if ( $badrun == 1 ) { $passed = $total = 0; }

    close(LOG);
    ($passed, $total);
}
