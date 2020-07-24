#!/usr/local/bin/perl

foreach $x ("all1", "db18", "db19", "all2", "db21", "db23", "all3", "db16", "db17", "small3", "big3") {
    foreach $y ("bblumi", "gglumi") {
	foreach $z ("aggrcc", "coolcc", "normcc") {
	    $name = "$x\_$y\_$z";
	    $undername = "$x\\_$y\\_$z";

# 	    $fixed = "";
# 	    open(LOG, "$name.m.table2");
# 	    while (<LOG>) {
# 		next if ($_ !~ /\& Null \&/);
# 		$_ =~ s/In\[4\]:= //;
# 		$_ =~ s/\& Null //;
# 		$_ =~ s/([0-9\%\.\\]+) \&/& $1 &/;
# 		if ($_ =~ /CC energy/) {
# 		    chop $_;
# 		    $_ .= "\\hline\n";
# 		}

# 		$fixed .= $_;
# 	    }
# 	    close(LOG);
# 	    open(LOG2, "> $name.table3");
# 	    print LOG2 $fixed;
# 	    close(LOG2);

# 	    system("rm -f $name.pdf");
# 	    system("epstopdf $name.eps -o=$name.pdf");
	}
	
	$name = "$x\_$y";
	$undername = "$x\\_$y";
	print "\\input{gather_$name.tex}\n";

	open(TEMPLATE, "gather_template");
	open(NEWG, "> gather_$name.tex");
	while (<TEMPLATE>) {
	    $_ =~ s/NORMALNAME/$name/g;
	    $_ =~ s/UNDERSCOREDNAME/$undername/g;
	    print NEWG $_;
	}
	close(TEMPLATE);
	close(NEWG);

    }
}
