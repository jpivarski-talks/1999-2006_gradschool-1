#!/usr/local/bin/perl

open( AREAY1S, "> area_y1s.txt" );
open( MASSY1S, "> mass_y1s.txt" );
open( WIDEY1S, "> wide_y1s.txt" );
open( BACKY1S, "> back_y1s.txt" );

open( AREAY3S, "> area_y3s.txt" );
open( MASSY3S, "> mass_y3s.txt" );
open( WIDEY3S, "> wide_y3s.txt" );
open( BACKY3S, "> back_y3s.txt" );

$n = 0;
foreach $tag ( "jan16-02", "jan30-02", "feb06-02", "feb20-02", "feb28-02", "mar06-02", "mar14-02", "apr02-02" ) {
    $n++;
    open( RESULTS, "../../fits/$tag/pass1/real.txt" );
    while ( <RESULTS> ) {
	chop;
	( $param, $eq, $val, $pm, $err ) = split( /\s+/ );
	if ( $param eq "area" ) {
	    print AREAY1S "$n\t$val\t$err\n";
	}
	if ( $param eq "mass" ) {
	    $val *= 1000.;
	    print MASSY1S "$n\t$val\t$err\n";
	}
	if ( $param eq "wide" ) {
	    print WIDEY1S "$n\t$val\t$err\n";
	}
	if ( $param eq "back" ) {
	    print BACKY1S "$n\t$val\t$err\n";
	}
    } # end while
} # end loop over tags

$n = 0;
foreach $tag ( "nov29-01", "dec06-01", "dec13-01", "dec20-01", "dec25-01", "jan03-02", "jan10-02" ) {
    $n++;
    open( RESULTS, "../../fits/$tag/pass1/real.txt" );
    while ( <RESULTS> ) {
	chop;
	( $param, $eq, $val, $pm, $err ) = split( /\s+/ );
	if ( $param eq "area" ) {
	    print AREAY3S "$n\t$val\t$err\n";
	}
	if ( $param eq "mass" ) {
	    $val *= 1000.;
	    print MASSY3S "$n\t$val\t$err\n";
	}
	if ( $param eq "wide" ) {
	    print WIDEY3S "$n\t$val\t$err\n";
	}
	if ( $param eq "back" ) {
	    print BACKY3S "$n\t$val\t$err\n";
	}
    } # end while
} # end loop over tags

