#!/usr/local/bin/perl

# Location of things
$base = "/home/mccann/public_html/private/my_gammaee";

open( INFO, "$base/run_infoY1s.html" );
print "\n\nrun_infoY1s.html:\n";
&check();
open( INFO, "$base/run_infoY2s.html" );
print "\n\nrun_infoY2s.html:\n";
&check();
open( INFO, "$base/run_infoY3s.html" );
print "\n\nrun_infoY3s.html:\n";
&check();

sub check {
    my $prev = 0;
    my $divdepth = 0;
    my $lineno = 0;
    while ( my $line = <INFO> ) {
	$lineno++;

	my $htmlfree = $line;
	$htmlfree =~ s/<[^>]*>//g;

	if ( $htmlfree =~ /^([0-9]{6})/ ) {
	    my $run = $1;
	    if ( $prev != 0  &&  $prev != ($run - 1) ) {
		print "NONSEQ: $lineno $line";
	    }
	    $prev = $run;
	} # end if a run line

	if ( $line =~ /<div/ ) { $divdepth++ }
	if ( $line =~ /<\/div/ ) { $divdepth-- }
	if ( $divdepth > 1 ) {
	    print "DIVDEPTH=$divdepth: $lineno $line";
	}

    } # end while
}




