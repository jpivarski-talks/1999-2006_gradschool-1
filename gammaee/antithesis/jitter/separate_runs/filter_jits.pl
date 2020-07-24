#!/usr/local/bin/perl

@degrees = ("0.01", "0.02", "0.03", "0.04", "0.05", "0.06", "0.08",
	    "0.10", "0.12", "0.14", "0.16", "0.18", "0.20", "0.30",
	    "0.40", "0.50", "1.00");
%a = ();
%c = ();

foreach $res ("1s", "2s", "3s") {
    foreach $degree (@degrees) {

	@area = ();
	@chi2 = ();

	open(FILE, "j$res\_$degree.log");
	$lines = 0;
	$success = 0;
	while (<FILE>) {
# 	    if ($success == 1) {
# 		print "* ";
# 	    }
# 	    else {
# 		print "  ";
# 	    }
# 	    print $_;

	    if ($success == 1  &&
		$_ =~ /= ([0-9\.eE\-\+]+) with chi\^2 ([0-9\.eE\-\+]+)/) {
		
		push(@area, $1);
		push(@chi2, $2);
	    }


	    if ($_ =~ /Minuit succeeded/) {
		$success = 1;
	    }
	    else {
		$success = 0;
	    }
	    $lines++;
	}

	$a{"$res$degree"} = [@area];
	$c{"$res$degree"} = [@chi2];

	close(FILE);
    }
}

foreach $res ("1s", "2s", "3s") {
    print "# successful areas: ";
    foreach $d (@degrees) {
	next if &broken("$res$d");
	print ($#{ $a{"$res$d"} }+1);
	print " ";
    }
    print "\n";

    print "# successful chi2s: ";
    foreach $d (@degrees) {
	next if &broken("$res$d");
	print ($#{ $c{"$res$d"} }+1);
	print " ";
    }
    print "\n";

    print "jit$res = [";
    foreach $d (@degrees) {
	next if &broken("$res$d");
	print "$d, ";
    }
    print "]\n";
    
    print "area$res = [";
    foreach $d (@degrees) {
	next if &broken("$res$d");
	print &mean(@{ $a{"$res$d"} }).", ";
    }
    print "]\n";

    print "area$res\_err = [";
    foreach $d (@degrees) {
	next if &broken("$res$d");
	print &errmean(@{ $a{"$res$d"} }).", ";
    }
    print "]\n";

    print "chi2$res = [";
    foreach $d (@degrees) {
	next if &broken("$res$d");
	print &mean(@{ $c{"$res$d"} }).", ";
    }
    print "]\n";

    print "chi2$res\_err = [";
    foreach $d (@degrees) {
	next if &broken("$res$d");
	print &errmean(@{ $c{"$res$d"} }).", ";
    }
    print "]\n";
}

sub broken {
    $broke = 0;
    if ($#{ $a{$_[0]} } == -1) {$broke = 1;}
    if ($#{ $c{$_[0]} } == -1) {$broke = 1;}
    $broke;
}

sub mean {
    $sum = 0.;
    $n = 0.;
    foreach $v (@_) {
	$sum += $v;
	$n += 1.;
    }
    $sum / $n;
}

sub errmean {
    $sum2 = 0.;
    $sum = 0.;
    $n = 0.;
    foreach $v (@_) {
	$sum2 += $v * $v;
	$sum += $v;
	$n += 1.;
    }
    sqrt($sum2/$n - $sum*$sum/$n/$n)/sqrt($n);
}
