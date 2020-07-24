#!/usr/local/bin/perl
require("/cdat/dafe/mccann/acceptance/decaymodes_table.pl");

%cl0decay = ();
%cl1decay = ();
%cl2decay = ();
%cl3decay = ();
%cl4decay = ();
%alldecay = ();
$total = 0;

open(IN, "/cdat/dafe/mccann/acceptance/decaymodes_$ARGV[0].dat");
while (my $line = <IN>) {
    chop($line);
    $level = substr($line, 0, 1);
    my $mode = substr($line, 2);

    $hasll = 0;
    $hastautau = 0;
    $hasradglue = 0;
    &classify($mode);
    $class = "X";
    if ($hasradglue == 0) {
	if ($hasll == 1) {
	    $class = "C";
	}
	elsif ($hastautau == 1) {
	    $class = "B";
	}
	else {
	    $class = "A";
	}
    }
    else {
	if ($hasll == 1) {
	    $class = "F";
	}
	elsif ($hastautau == 1) {
	    $class = "E";
	}
	else {
	    $class = "D";
	}
    }
    
    &recurse($mode);
}
close(IN);

sub classify {
    my $mode = @_[0];

    my $pointer = 0;
    $pointer++ while (substr($mode, $pointer, 1) ne "(");
    my $parent = substr($mode, 0, $pointer);

    my @children = ();
    $pointer++;
    while (substr($mode, $pointer, 1) ne ")") {
	my $decision;
	my $childstart = $pointer;
	$pointer++ while (($decision = substr($mode, $pointer, 1)) ne " "  &&
			  $decision ne "("  &&  $decision ne ")");
	push(@children, substr($mode, $childstart, $pointer-$childstart));

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
	    &classify(substr($mode, $childstart, $pointer-$childstart));

	    $pointer++ if (substr($mode, $pointer, 1) eq " ");
	}
    }

#  0 => "vpho",
#  1 => "gamma",
#  7 => "e-",
#  8 => "e+",
#  11 => "mu-",
#  12 => "mu+",
#  15 => "tau-",
#  16 => "tau+",
#  95 => "Upsilon(1S)",
#  97 => "Upsilon(2S)",
#  98 => "Upsilon(3S)",
#  495 => "string",

    if (($parent == 95  ||  $parent == 97  ||  $parent == 98)  &&
	$#children - 1 >= 0  &&
	$children[$#children-1] == 7  &&  $children[$#children] == 8) {
	$hasll = 1;
    }

    if (($parent == 95  ||  $parent == 97  ||  $parent == 98)  &&
	$#children - 1 >= 0  &&
	$children[$#children-1] == 11  &&  $children[$#children] == 12) {
	$hasll = 1;
    }

    if (($parent == 95  ||  $parent == 97  ||  $parent == 98)  &&
	$#children - 1 >= 0  &&
	$children[$#children-1] == 15  &&  $children[$#children] == 16) {
	$hastautau = 1;
    }

    if (($parent == 95  ||  $parent == 97  ||  $parent == 98)  &&
	$#children == 1  &&
	$children[0] == 1  &&  $children[1] == 495) {
	$hasradglue = 1;
    }
}

sub recurse {
    my $mode = @_[0];

    my $pointer = 0;
    $pointer++ while (substr($mode, $pointer, 1) ne "(");
    my $parent = substr($mode, 0, $pointer);

    my @children = ();
    $pointer++;
    while (substr($mode, $pointer, 1) ne ")") {
	my $decision;
	my $childstart = $pointer;
	$pointer++ while (($decision = substr($mode, $pointer, 1)) ne " "  &&
			  $decision ne "("  &&  $decision ne ")");
	push(@children, substr($mode, $childstart, $pointer-$childstart));

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
	    &recurse(substr($mode, $childstart, $pointer-$childstart));

	    $pointer++ if (substr($mode, $pointer, 1) eq " ");
	}
    }

    die $class if ($class eq "X"  ||  $class eq "E"  ||  $class eq "F");

    my $decay = $class . join(' ', ($parent, @children));
    if (!defined($alldecay{$decay})) {
	$cl0decay{$decay} = 0;
	$cl1decay{$decay} = 0;
	$cl2decay{$decay} = 0;
	$cl3decay{$decay} = 0;
	$cl4decay{$decay} = 0;
	$alldecay{$decay} = 0;
    }
    $cl0decay{$decay}++ if ($level == 0);
    $cl1decay{$decay}++ if ($level == 1);
    $cl2decay{$decay}++ if ($level == 2);
    $cl3decay{$decay}++ if ($level == 3);
    $cl4decay{$decay}++ if ($level == 4);
    $alldecay{$decay}++;
    $total++;
}

sub byfreq {
    $alldecay{$b} <=> $alldecay{$a};
}

sub header {
    print "
\\noindent
\\begin{tabular}{p{4 cm} r | r r r r r}
  Decay Node & Occurances &
\\begin{tabular}{c} \\% Failed \\\\ Trigger \\end{tabular} &
\\begin{tabular}{c} Visible \\\\ Energy \\end{tabular} &
\\begin{tabular}{c} Anti- \\\\ \$e^+e^-\$ \\end{tabular} &
\\begin{tabular}{c} Anti- \\\\ \$\\mu^+\\mu^-\$ \\end{tabular} &
\\begin{tabular}{c} Passed \\\\ All Cuts \\end{tabular} \\\\\\hline\\hline
";
}

sub nicify {
    my $x = @_[0];
    return 0 if ($x == 0);

    my $n = 0;

    while($x < 100) {
	$x *= 10;
	$n++;
    }
    $x = int($x + 0.5);

    while($n > 0) {
	$x /= 10;
	$n--;
    }

    $x =~ s/e-0*([0-9]+)/\\times 10^\{$1\}/;
    $x;
}

sub middle() {
    my $count = 0;
    foreach my $decay (sort byfreq keys %alldecay) {
	next if (substr($decay, 0, 1) ne $class);
	next if (substr($decay, 1, 4) eq "495 ");

	my ($parent, @children) = split(' ', $decay);
	my $name = $tabletex{substr($parent,1)} . " \\to";
	foreach my $child (@children) {
	    $name .= " " . $tabletex{$child};
	}
	my $br = $alldecay{$decay};
	my $cl0 = &nicify($cl0decay{$decay} / $alldecay{$decay} * 100);
	my $cl1 = &nicify($cl1decay{$decay} / $alldecay{$decay} * 100);
	my $cl2 = &nicify($cl2decay{$decay} / $alldecay{$decay} * 100);
	my $cl3 = &nicify($cl3decay{$decay} / $alldecay{$decay} * 100);
	my $cl4 = $cl4decay{$decay} / $alldecay{$decay} * 100;
	
	$count++;
	if ($count == 41) {
	    $count = 0;
	    &footer() if ($hitten == 0);
	    &header() if ($hitten == 0);
	}

	if ($br < 11) {
	    if ($hitten == 0) {
		&footer();
		print "\n";
	    }
	    $hitten = 1;
	}

	my $comment = "";
	$comment = "\%\% " if ($hitten == 1);

	printf("%s\$$name\$ & $br & $cl0 & $cl1 & $cl2 & $cl3 & %5.2f \\\\\n", $comment, $cl4);
    }
}

sub middle_string() {
    print "\n";

    my $count = 0;
    foreach my $decay (sort byfreq keys %alldecay) {
	next if (substr($decay, 0, 1) ne $class);
	next if (substr($decay, 1, 4) ne "495 ");

	my ($parent, @children) = split(' ', $decay);
	my $name = $tabletex{substr($parent,1)} . " \\to";
	foreach my $child (@children) {
	    $name .= " " . $tabletex{$child};
	}
	my $br = $alldecay{$decay};
	my $cl0 = &nicify($cl0decay{$decay} / $alldecay{$decay} * 100);
	my $cl1 = &nicify($cl1decay{$decay} / $alldecay{$decay} * 100);
	my $cl2 = &nicify($cl2decay{$decay} / $alldecay{$decay} * 100);
	my $cl3 = &nicify($cl3decay{$decay} / $alldecay{$decay} * 100);
	my $cl4 = $cl4decay{$decay} / $alldecay{$decay} * 100;
	
	printf("%s\$$name\$ & $br & $cl0 & $cl1 & $cl2 & $cl3 & %5.2f \\\\\n", "\%\% ", $cl4);
    }
}

sub footer {
    print "\\hline\\hline
\\end\{tabular\}
";
}

$hitten = 0;
$class = "A";
print "\\begin{center}
No \$\\Upsilon(nS) \\to \\ell^+ \\ell^-\$, \$\\to \\tau^+ \\tau^-\$, \$\\to \\gamma\$ string events:
\\end{center}
";
&header();
&middle();
&footer() if ($hitten == 0);
&middle_string();
print "\n";

$hitten = 0;
$class = "B";
print "\\pagebreak
\\begin{center}
Events with \$\\Upsilon(nS) \\to \\tau^+ \\tau^-\$:
\\end{center}
";
&header();
&middle();
&footer() if ($hitten == 0);
&middle_string();
print "\n";

$hitten = 0;
$class = "C";
print "\\pagebreak
\\begin{center}
Events with \$\\Upsilon(nS) \\to \\ell^+ \\ell^-\$:
\\end{center}
";
&header();
&middle();
&footer() if ($hitten == 0);
&middle_string();
print "\n";

$hitten = 0;
$class = "D";
print "\\pagebreak
\\begin{center}
\$\\Upsilon(nS) \\to \\gamma\$ string events:
\\end{center}
";
&header();
&middle();
&footer() if ($hitten == 0);
&middle_string();
print "\n";
