#!/usr/local/bin/perl

$divlevel = 0;
foreach my $res ( "../run_infoY1s.html", "../run_infoY2s.html", "../run_infoY3s.html" ) {
    open(RES, $res);
    $linenumber = 0;
    print "This comes from $res\n";

    while (my $line = <RES>) {
	$linenumber++;

	die "$res:$linenumber" if ( $line =~ /div.*div/ );
	if ( $line =~ /<\s*div/ ) {
	    $divlevel++;
	}
	elsif ( $line =~ /<\s*\/\s*div/ ) {
	    $divlevel--;
	}
	die "$res:$linenumber has $divlevel" if ( $divlevel != 0  &&  $divlevel != 1 );

	if ( $divlevel == 1 ) {
	    $line =~ s/<a\s+name\s*=\s*"?([a-zA-Z0-9\-]+)"?[^>]*>/\nTAG $1\n/g;

	    $line =~ s/<[^>]*>//g;
	    print $line;
	}
    }
}
