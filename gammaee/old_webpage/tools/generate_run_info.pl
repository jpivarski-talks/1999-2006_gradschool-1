#!/usr/local/bin/perl

die "Get thee to a SunOS!\n" if ( `uname` ne "SunOS\n" );

if ( $ARGV[0] =~ /^[0-9]+$/  &&  $ARGV[1] =~ /^[0-9]+$/  && $ARGV[0] < $ARGV[1] ) {
    @runs = ( $ARGV[0]..$ARGV[1] );
    
    foreach $run ( @runs )
    {
	$activity = "n/a";
	$date = "n/a";
	$time = "n/a";
	$energy = "n/a";
	$lumi = "n/a";
	$cchad = "n/a";
	$cchaderr = "n/a";

	open( CONST2, "/nfs/cleo3/Common/rel/current/bin/sparc-sun-solaris2.6/DBRunStatisticsRetrieve $run 2 |" );
	while( <CONST2> )
	{
	    $activity = $1 if ( $_ =~ /Sequence:\s+Global\|([^ \n]+)/ );
	}
	close( CONST2 );

	open( CONST4, "/nfs/cleo3/Common/rel/current/bin/sparc-sun-solaris2.6/DBRunStatisticsRetrieve $run 4 |" );
	while( <CONST4> )
	{
	    ( $date, $time ) = ( $1, $2 ) if ( $_ =~ /^Created on E[SD]T: ([0-9]+\/[0-9]+\/[0-9]+)\s+([0-9]+:[0-9 ]+)/ );

	    $energy = $1 if ( $_ =~ /^CESR\/energy:\s+([0-9\.\-]+)/ );
	}
	close( CONST4 );

	open( CONST8, "/nfs/cleo3/Common/rel/current/bin/sparc-sun-solaris2.6/DBRunStatisticsRetrieve $run 8 |" );
	while( <CONST8> )
	{
	    $lumi = $1 if ( /LiveLuminosity\s+\(nb\^\{\-1\}\)\:\s+([0-9\.]+)/ );
	}

	open( CONST128, "/nfs/cleo3/Common/rel/current/bin/sparc-sun-solaris2.6/DBRunStatisticsRetrieve $run 128 |" );
	while( <CONST128> )
	{
	    ( $cchad, $cchaderr ) = ( $1, $2 )
		if ( /CC Hadronic XC \(nb\):\s+\(length\s+[0-9]+\)\s+([0-9\.\-eE\+]+)\s+([0-9\.\-eE\+]+)/ );
	}
	close( CONST128 );

	$date = "    n/a   " if ( $date eq "n/a" );
	$date2 = $date; $date2 =~ s/\//-/g;
	$time = " n/a " if ( $time eq "n/a" );
	$activity = "          n/a   " if ( $activity eq "n/a" );

	if ( $energy eq "n/a" ) {
	    $energy = "    n/a  "; }
	else {
	    $energy = sprintf( "%9.5f", $energy ); }

	if ( $lumi eq "n/a" ) {
	    $lumi = "        n/a "; }
	else {
	    $lumi = sprintf( "%12.2f", $lumi ); }

	if ( $cchad eq "n/a" || $cchaderr eq "n/a" ) {
	    $hadronXC = "       n/a      "; }
	else {
	    $hadronXC = sprintf( "%6.2f +/- %5.2f", $cchad, $cchaderr ); }

	if ( $date eq "    n/a   " ) {
	    $line = sprintf( "%6d %10s %5s %16s %9s %12s %16s\n", $run, $date, $time, $activity, $energy, $lumi, $hadronXC ); }
	else {
	    $line = sprintf( "<a href=\"http://lnson3.lns.cornell.edu/rbin/runsheet/displayRun.pl?run=$run-$date2\">%6d</a> %10s %5s %16s %9s %12s %16s\n", $run, $date, $time, $activity, $energy, $lumi, $hadronXC ); }

	$line =~ s/n\/a/<i>n\/a<\/i>/g;

	print $line;
    }
}
