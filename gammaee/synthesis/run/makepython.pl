#!/usr/local/bin/perl

opendir(DIR, "../log");
foreach $file (readdir(DIR)) {
    next if ($file !~ /\.log$/);

    $python = $file;
    $python =~ s/\.log$/\.py/;
    $pickle = $python;
    $pickle =~ s/\.py/\.p/;
    if (-e "../pickle/$pickle") {
	print "Already generated $pickle!\n";
	next;
    }

    $empty = 1;

    open(FILE, "../log/$file");
    open(FILE2, "> ../python/$python");

    while ($line = <FILE>) {
	next if (substr($line, 0, 7) ne "PYTHON "  &&
		 substr($line, 0, 13) ne "Suez> PYTHON "    );

	$line =~ s/^PYTHON //;
	$line =~ s/^Suez> PYTHON //;
# 	$line =~ s/\-NaN/-1000/g;
# 	$line =~ s/NaN/-1000/g;

	print FILE2 $line;
	$empty = 0;
    }

    close(FILE2);
    close(FILE);

    if ($empty == 1) {
	system("rm -f ../python/$python");
    }
    else {
	system("/nfs/cleo3/Offline/rel/current/other_sources/python/bin/python2.4 makepython.py ../python/$python ../pickle/$pickle");
	print "Done with $file.\n";
    }
}

