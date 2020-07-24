#!/usr/local/bin/perl

%n = ();

while (<>) {
    chop;
    next if (substr($_, 0, 3) ne " %%");

    $ptocup = $1 if ($_ =~ /ptocup\s*=\s*([0-9\.]+)/);
    $ptocdo = $1 if ($_ =~ /ptocdo\s*=\s*([0-9\.]+)/);

    $n{$1} = $2 if ($_ =~ /HINFO[^0-9]*([0-9]+)[^0-9]*=[^0-9]*([0-9\.]+)/);
}

sub numly {$a <=> $b}

print "hptoc = ".(($ptocup+$ptocdo)/2).";\n";
print "hptocerr = ".abs(($ptocup-$ptocdo)/2).";\n";

foreach $k (sort numly keys %n) {
    if ($k > 1000  &&  $k % 100 == 1) {
	die "$k ".(int($k/100)*100+9) if (!defined($n{int($k/100)*100+9}));
	print "h\[$k\] = ".($n{$k} - $n{int($k/100)*100+9}).";\n";
    }
    elsif ($k > 1000  &&  $k % 100 == 9) {
	die "$k ".(int($k/100)*100+2) if (!defined($n{int($k/100)*100+2}));
	print "h\[$k\] = ".($n{$k} - $n{int($k/100)*100+2}).";\n";
    }
    else {
	print "h\[$k\] = $n{$k};\n";
    }
}
