#!/usr/local/bin/perl

if ( !defined( $ARGV[0] )  ||  !defined( $ARGV[1] )  ||  !defined( $ARGV[2] ) )
{
    print $_ while( <STDIN> );
    die "./colorize.pl scan|cont|peak \"Month #\" mon##-##\n";
}

$background = "#ffffaa";
$heading_prefix = $ARGV[1];
$label = $ARGV[2];

if ( $ARGV[0] =~ /^scan$/i ) {
    $type = "scan";
    $color = "#cc0000";
    $heading = "$heading_prefix Scan";
    $plots = "<img src=\"run_info_plots/$label\_scan.gif\">";
} elsif ( $ARGV[0] =~ /^cont/i ) {
    $type = "cont";
    $color = "#006600";
    $heading = "$heading_prefix Continuum Point";
    $plots = "     <img src=\"run_info_plots/$label\_cont-en.gif\">     <img src=\"run_info_plots/$label\_cont-xc.gif\">";
} elsif ( $ARGV[0] =~ /^peak$/i ) {
    $type = "peak";
    $color = "#0000bb";
    $heading = "$heading_prefix Peak Point";
    $plots = "     <img src=\"run_info_plots/$label\_peak-en.gif\">     <img src=\"run_info_plots/$label\_peak-xc.gif\">";
} # end switch over types

#  if ( $type eq "scan" ) {
#      print "<a name=\"$label\">";
#  }

print "<div style=\"color: $color;\">
$heading
$plots

";
$indiv = 1;

while ( <STDIN> )
{
    if ( $_ =~ /DataTaking\s+[0-9\.]+\s+[0-9\.]+/ ) {
	# should include this line

	if ( $indiv == 1 ) {
	    print $_;
	} else {
	    print "<div style=\"color: $color;\">".$_;
	    $indiv = 1;
	}

    } else {
	# should not include this line

	if ( $indiv == 1 ) {
	    print "</div>".$_;
	    $indiv = 0;
	} else {
	    print $_;
	}

    } # end if a line should be included or not
} # end loop over lines

if ( $indiv == 1 ) {
    print "</div>\n";
} else {
    print "\n";
}
