#!/usr/local/bin/perl
require("/cdat/dafe/mccann/acceptance/decaymodes_table.pl");

%ee_total = ();
%ee_fail = ();
%mumu_total = ();
%mumu_fail = ();
%tautau_total = ();
%tautau_fail = ();
%taushape_total = ();
%taushape_fail = ();
%glue_total = ();
%glue_fail = ();
%ggpho_total = ();
%ggpho_fail = ();
%all_modals = ();

open(IN, "/cdat/dafe/mccann/acceptance/new2_decaymodes_$ARGV[0].dat");
while (my $line = <IN>) {
    chop($line);
    $level = substr($line, 0, 1);
    my $mode = substr($line, 2);

    $taushape = "";
    $is_ee = $is_mumu = $is_tautau = 0;
    $photofied = 0;
    $is_glue = $is_ggpho = 0;
    @modal = ();
    my $ala_mode = &classify($mode);
    $ala_mode = "*$ala_mode" if ($photofied == 1);
    $taushape = $ala_mode."Z".$taushape;
    $all_modals{$ala_mode} = [@modal];

    $ph = " ";
    $ph = "*" if ($photofied == 1);
    $name = "     ";
    $name = "ee   " if ($is_ee == 1);
    $name = "mumu " if ($is_mumu == 1);
    $name = "taus " if ($is_tautau == 1);
    $name = "glue " if ($is_glue == 1);
    $name = "ggpho" if ($is_ggpho == 1);
    die "$ph$name $ala_mode has $is_ee + $is_mumu + $is_tautau + $is_glue + $is_ggpho"
	if ($is_ee + $is_mumu + $is_tautau + $is_glue + $is_ggpho != 1);

    if ($is_ee == 1) {
	if (!defined($ee_total{$ala_mode})) {
	    $ee_total{$ala_mode} = 0;
	    $ee_fail{$ala_mode} = 0;
	}
	$ee_total{$ala_mode}++;
	$ee_fail{$ala_mode}++ if ($level != 4);
    }

    if ($is_mumu == 1) {
	if (!defined($mumu_total{$ala_mode})) {
	    $mumu_total{$ala_mode} = 0;
	    $mumu_fail{$ala_mode} = 0;
	}
	$mumu_total{$ala_mode}++;
	$mumu_fail{$ala_mode}++ if ($level != 4);
    }

    if ($is_tautau == 1) {
	if (!defined($tautau_total{$ala_mode})) {
	    $tautau_total{$ala_mode} = 0;
	    $tautau_fail{$ala_mode} = 0;
	}
	$tautau_total{$ala_mode}++;
	$tautau_fail{$ala_mode}++ if ($level != 4);

	if (!defined($taushape_total{$taushape})) {
	    $taushape_total{$taushape} = 0;
	    $taushape_fail{$taushape} = 0;
	}
	$taushape_total{$taushape}++;
	$taushape_fail{$taushape}++ if ($level != 4);
    }

    if ($is_glue == 1) {
	if (!defined($glue_total{$ala_mode})) {
	    $glue_total{$ala_mode} = 0;
	    $glue_fail{$ala_mode} = 0;
	}
	$glue_total{$ala_mode}++;
	$glue_fail{$ala_mode}++ if ($level != 4);
    }

    if ($is_ggpho == 1) {
	if (!defined($ggpho_total{$ala_mode})) {
	    $ggpho_total{$ala_mode} = 0;
	    $ggpho_fail{$ala_mode} = 0;
	}
	$ggpho_total{$ala_mode}++;
	$ggpho_fail{$ala_mode}++ if ($level != 4);
    }

}
close(IN);

#  0 => "vpho",
#  1 => "gamma",
#  7 => "e-",
#  8 => "e+",
#  9 => "nu_e",
#  10 => "anti-nu_e",
#  11 => "mu-",
#  12 => "mu+",
#  13 => "nu_mu",
#  14 => "anti-nu_mu",
#  15 => "tau-",
#  16 => "tau+",
#  17 => "nu_tau",
#  18 => "anti-nu_tau",
#  21 => "pi+",
#  22 => "pi-",
#  51 => "pi0",
#  95 => "Upsilon(1S)",
#  97 => "Upsilon(2S)",
#  98 => "Upsilon(3S)",
#  100 => "chi_b0(1P)",
#  101 => "chi_b1(1P)",
#  102 => "chi_b2(1P)",
#  103 => "chi_b0(2P)",
#  104 => "chi_b1(3P)",
#  105 => "chi_b2(2P)",
#  577 => "Upsilon_1(2D)",
#  578 => "Upsilon_2(2D)",
#  579 => "Upsilon_1(1D)",
#  580 => "Upsilon_2(1D)",
#  581 => "Upsilon_3(2D)",
#  582 => "Upsilon_3(1D)",
#  584 => "chi_b0(3P)",
#  585 => "chi_b1(2P)",
#  586 => "chi_b2(3P)",
#  495 => "string",

sub classify {
    my $mode = @_[0];

    my $pointer = 0;
    $pointer++ while (substr($mode, $pointer, 1) ne "(");
    my $parent = substr($mode, 0, $pointer);

    my @children = ();
    my @urchins = ($parent);
    $pointer++;
    while (substr($mode, $pointer, 1) ne ")") {
	my $decision;
	my $childstart = $pointer;
	$pointer++ while (($decision = substr($mode, $pointer, 1)) ne " "  &&
			  $decision ne "("  &&  $decision ne ")");
	my $child = substr($mode, $childstart, $pointer-$childstart);
	my $only_child = $child;

	if ($decision eq " ") {
	    $pointer++;
	}
	elsif ($decision eq "(") {
	    my $parenlevel = 1;
	    while ($parenlevel > 0) {
		$pointer++;
		$parenlevel++ if (substr($mode, $pointer, 1) eq "(");
		$parenlevel-- if (substr($mode, $pointer, 1) eq ")");
	    }
	    $pointer++;

	    if ($child == 0  ||
		$child == 95  ||  $child == 97  ||  $child == 98  ||
		$child == 100  ||  $child == 101  ||  $child == 102  ||
		$child == 103  ||  $child == 104  ||  $child == 105  ||
		$child == 577  ||  $child == 578  ||  $child == 579  ||
		$child == 580  ||  $child == 581  ||  $child == 582  ||
		$child == 584  ||  $child == 585  ||  $child == 586    ) {

		my $inner_child = &classify(substr($mode, $childstart, $pointer-$childstart));

		if ($child == 100  &&  substr($inner_child, 0, 9) ne "100(1 95(") {
		    $inner_child = "100(495)";
		    $is_glue = 1;
		}
		$child = $inner_child;
	    }

	    if ($child == 15  ||  $child == 16) {
		my $inner_child = &classify(substr($mode, $childstart, $pointer-$childstart));

		if ($inner_child ne "15(17 22 51)"         	 &&  # nu_tau pi- pi0
		    $inner_child ne "15(11 14 17)"         	 &&  # mu- anti-nu_mu nu_tau
		    $inner_child ne "15(7 10 17)"          	 &&  # e- anti-nu_e nu_tau
		    $inner_child ne "15(17 22)"            	 &&  # nu_tau pi-
		    $inner_child ne "15(17 22 51 51)"      	 &&  # nu_tau pi- pi0 pi0
		    $inner_child ne "15(17 21 22 22)"      	 &&  # nu_tau pi+ pi- pi-
		    $inner_child ne "15(17 21 22 22 51)"   	 &&  # nu_tau pi+ pi- pi- pi0
		    $inner_child ne "15(1 7 10 17)"        	 &&  # gamma e- anti-nu_e nu_tau
		    $inner_child ne "15(17 64)"            	 &&  # nu_tau K*-
		    $inner_child ne "15(17 22 51 51 51 51)"	 &&  # nu_tau pi- pi0 pi0 pi0 pi0

		    $inner_child ne "16(18 21 51)"         	 &&  # anti-nu_tau pi+ pi0
		    $inner_child ne "16(12 13 18)"         	 &&  # mu+ nu_mu anti-nu_tau
		    $inner_child ne "16(8 9 18)"           	 &&  # e+ nu_e anti-nu_tau
		    $inner_child ne "16(18 21)"            	 &&  # anti-nu_tau pi+
		    $inner_child ne "16(18 21 51 51)"      	 &&  # anti-nu_tau pi+ pi0 pi0
		    $inner_child ne "16(18 21 21 22)"      	 &&  # anti-nu_tau pi+ pi+ pi-
		    $inner_child ne "16(18 21 21 22 51)"   	 &&  # anti-nu_tau pi+ pi+ pi- pi0
		    $inner_child ne "16(1 8 9 18)"         	 &&  # gamma e+ nu_e anti-nu_tau
		    $inner_child ne "16(18 63)"            	 &&  # anti-nu_tau K*+
		    $inner_child ne "16(18 21 51 51 51)"   	     # anti-nu_tau pi+ pi0 pi0 pi0
		    ) {
		    $inner_child = "$child(other)";
		}
		$taushape .= $inner_child;
	    }

	    $pointer++ if (substr($mode, $pointer, 1) eq " ");
	}

	push(@children, $child);
	push(@urchins, $only_child);
    }

    my $parent_isbb = 0;
    $parent_isbb = 1 if ($parent == 95  ||  $parent == 97  ||  $parent == 98  ||
			 $parent == 100  ||  $parent == 101  ||  $parent == 102  ||
			 $parent == 103  ||  $parent == 104  ||  $parent == 105  ||
			 $parent == 577  ||  $parent == 578  ||  $parent == 579  ||
			 $parent == 580  ||  $parent == 581  ||  $parent == 582  ||
			 $parent == 584  ||  $parent == 585  ||  $parent == 586    );

    if ($parent_isbb  &&
	$#children - 1 >= 0  &&
	$children[$#children-1] == 7  &&  $children[$#children] == 8) {
	$is_ee = 1;
	$photofied = 1 if ($children[0] == 1);
    }

    if ($parent_isbb  &&
	$#children - 1 >= 0  &&
	$children[$#children-1] == 11  &&  $children[$#children] == 12) {
	$is_mumu = 1;
	$photofied = 1 if ($children[0] == 1);
    }

    if ($parent_isbb  &&
	$#children - 1 >= 0  &&
	$children[$#children-1] == 15  &&  $children[$#children] == 16) {
	$is_tautau = 1;
	$photofied = 1 if ($children[0] == 1);
    }

    if ($parent_isbb  &&  $children[0] == 495) {
	$is_glue = 1;
    }

    if ($parent_isbb  &&  $children[0] == 1  &&  $children[1] == 495) {
	$is_ggpho = 1;
    }

    if ($parent != 100  &&  $#children >= 2  &&
	$children[0] == 1  &&  $children[1] == 21  &&  $children[2] == 22) {
	$photofied = 1;
    }

    if ($parent != 100  &&  $#children >= 3  &&
	$children[0] == 1  &&  $children[1] == 1  &&  $children[2] == 21  &&  $children[3] == 22) {
	$photofied = 1;
    }

    push(@modal, "\"".join(' ', @urchins)."\"") if ($parent != 15  &&  $parent != 16  &&  $parent != 100);
    if ($parent == 100) {
	my $tmp = "\"".join(' ', @urchins)."\"";
	if ($tmp eq "\"100 1 95\"") {
	    push(@modal, $tmp);
	}
	else {
	    push(@modal, "\"100 495\"");
	}
    }
    return "$parent(" . join(' ', @children) . ")";
}

sub bytotee { $ee_total{$b} <=> $ee_total{$a}; }
print "ee$ARGV[0]s = {\n";
foreach my $k (sort bytotee keys %ee_total) {
    my $kk = $k;
    next if (substr($k, 0, 1) eq "*");
    print "{$ee_fail{$k}, $ee_total{$k}, \"$kk\", {".join(", ", @{$all_modals{$k}})."}},\n";
}
print "};\nee$ARGV[0]spho = {\n";
foreach my $k (sort bytotee keys %ee_total) {
    my $kk = $k;
    next if (substr($k, 0, 1) ne "*");
    $kk = substr($k, 1);
    print "{$ee_fail{$k}, $ee_total{$k}, \"$kk\", {".join(", ", @{$all_modals{$k}})."}},\n";
}
print "};\n\n";

sub bytotmumu { $mumu_total{$b} <=> $mumu_total{$a}; }
print "mumu$ARGV[0]s = {\n";
foreach my $k (sort bytotmumu keys %mumu_total) {
    my $kk = $k;
    next if (substr($k, 0, 1) eq "*");
    print "{$mumu_fail{$k}, $mumu_total{$k}, \"$kk\", {".join(", ", @{$all_modals{$k}})."}},\n";
}
print "};\nmumu$ARGV[0]spho = {\n";
foreach my $k (sort bytotmumu keys %mumu_total) {
    my $kk = $k;
    next if (substr($k, 0, 1) ne "*");
    $kk = substr($k, 1);
    print "{$mumu_fail{$k}, $mumu_total{$k}, \"$kk\", {".join(", ", @{$all_modals{$k}})."}},\n";
}
print "};\n\n";

sub bytottautau { $tautau_total{$b} <=> $tautau_total{$a}; }
print "tautau$ARGV[0]s = {\n";
foreach my $k (sort bytottautau keys %tautau_total) {
    my $kk = $k;
    next if (substr($k, 0, 1) eq "*");
    print "{$tautau_fail{$k}, $tautau_total{$k}, \"$kk\", {".join(", ", @{$all_modals{$k}})."}},\n";
}
print "};\ntautau$ARGV[0]spho = {\n";
foreach my $k (sort bytottautau keys %tautau_total) {
    my $kk = $k;
    next if (substr($k, 0, 1) ne "*");
    $kk = substr($k, 1);
    print "{$tautau_fail{$k}, $tautau_total{$k}, \"$kk\", {".join(", ", @{$all_modals{$k}})."}},\n";
}
print "};\n\n";

sub bytotglue { $glue_total{$b} <=> $glue_total{$a}; }
print "glue$ARGV[0]s = {\n";
foreach my $k (sort bytotglue keys %glue_total) {
    my $kk = $k;
    next if (substr($k, 0, 1) eq "*");
    print "{$glue_fail{$k}, $glue_total{$k}, \"$kk\", {".join(", ", @{$all_modals{$k}})."}},\n";
}
print "};\nglue$ARGV[0]spho = {\n";
foreach my $k (sort bytotglue keys %glue_total) {
    my $kk = $k;
    next if (substr($k, 0, 1) ne "*");
    $kk = substr($k, 1);
    print "{$glue_fail{$k}, $glue_total{$k}, \"$kk\", {".join(", ", @{$all_modals{$k}})."}},\n";
}
print "};\n\n";

sub bytotggpho { $ggpho_total{$b} <=> $ggpho_total{$a}; }
print "ggpho$ARGV[0]s = {\n";
foreach my $k (sort bytotggpho keys %ggpho_total) {
    my $kk = $k;
    next if (substr($k, 0, 1) eq "*");
    print "{$ggpho_fail{$k}, $ggpho_total{$k}, \"$kk\", {".join(", ", @{$all_modals{$k}})."}},\n";
}
print "};\nggpho$ARGV[0]spho = {\n";
foreach my $k (sort bytotggpho keys %ggpho_total) {
    my $kk = $k;
    next if (substr($k, 0, 1) ne "*");
    $kk = substr($k, 1);
    print "{$ggpho_fail{$k}, $ggpho_total{$k}, \"$kk\", {".join(", ", @{$all_modals{$k}})."}},\n";
}
print "};\n\n";

sub bytottaushape { $taushape_total{$b} <=> $taushape_total{$a}; }
print "taushape$ARGV[0]s = {\n";
foreach my $k (sort bytottaushape keys %taushape_total) {
    next if (substr($k, 0, 1) eq "*");
    my ($kk, $ts) = split("Z", $k);
    my $lr = substr($ts, 3);
    chop($lr);
    my ($l, $r) = split("\\)16\\(", $lr);

    print "{$taushape_fail{$k}, $taushape_total{$k}, \"$l\", \"$r\", {".join(", ", @{$all_modals{$kk}})."}},\n";
}
print "};\ntaushape$ARGV[0]spho = {\n";
foreach my $k (sort bytottaushape keys %taushape_total) {
    next if (substr($k, 0, 1) ne "*");
    my ($kk, $ts) = split("Z", $k);
    my $lr = substr($ts, 3);
    chop($lr);
    my ($l, $r) = split("\\)16\\(", $lr);

    print "{$taushape_fail{$k}, $taushape_total{$k}, \"$l\", \"$r\", {".join(", ", @{$all_modals{$kk}})."}},\n";
}
print "};\n\n";
