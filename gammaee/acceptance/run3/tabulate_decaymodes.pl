#!/usr/local/bin/perl
require("/cdat/dafe/mccann/acceptance/decaymodes_table.pl");

%mall = ();
%mcut = ();
$total = 0;
@modes = ();

open(IN, "/cdat/dafe/mccann/acceptance/decaymodes_$ARGV[0].dat");
while (my $line = <IN>) {
    chop($line);
 #   my $level = substr($line, 0, 1);
    my $mode = substr($line, 2);

    if (!defined($mall{$mode})) {
	$mall{$mode} = 0;
	$mcut{"0 $mode"} = 0;
	$mcut{"1 $mode"} = 0;
	$mcut{"2 $mode"} = 0;
	$mcut{"3 $mode"} = 0;
	$mcut{"4 $mode"} = 0;
	push(@modes, $mode);
    }
    
    $mall{$mode}++;
    $mcut{$line}++;
    $total++;
}
close(IN);

%cl = ();
%br = ();
foreach my $mode (@modes) {
    $cl{"0 $mode"} = $mcut{"0 $mode"} / $mall{$mode};
    $cl{"1 $mode"} = $mcut{"1 $mode"} / $mall{$mode};
    $cl{"2 $mode"} = $mcut{"2 $mode"} / $mall{$mode};
    $cl{"3 $mode"} = $mcut{"3 $mode"} / $mall{$mode};
    $cl{"4 $mode"} = $mcut{"4 $mode"} / $mall{$mode};

    $br{$mode} = $mall{$mode} / $total;
}

@smodes = sort bybr @modes;

sub bybr {
    $br{$b} <=> $br{$a};
}

printf("%40s | %9s | %9s | %9s | %9s | %9s| %9s\n",
       "MODE", "CL0", "CL1", "CL2", "CL3", "CL4", "BR");
print "-----------------------------------------+-----------+-----------+-----------+-----------+-----------+-----------\n";
foreach my $mode (@smodes) {
    next if ($mall{$mode} < 10);
    printf("%40s | %9g | %9g | %9g | %9g | %9g | %9g\n",
	   $mode,
	   $cl{"0 $mode"},
	   $cl{"1 $mode"},
	   $cl{"2 $mode"},
	   $cl{"3 $mode"},
	   $cl{"4 $mode"},
	   $br{$mode});
}
