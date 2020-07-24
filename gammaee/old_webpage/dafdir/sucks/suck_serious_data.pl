#!/usr/local/bin/perl

%en = ();
%online = ();
%pass1 = ();

$indiv = 0;
$n = 0;
$title = "";

open( RI, "run_info.html" );
while( $line = <RI> )
{
    chop $line;

    $indiv = 1 if ( $line =~ /<div/  &&  $line !~ /<\/div/ );
    $indiv = 0 if ( $line =~ /<\/div/  &&  $line !~ /<div/ );
    $indiv = 1 if ( $line =~ /<\/div.*<div/ );

    if ( $indiv == 1  &&  $line =~ /^[A-Za-z]+\s+[0-9]+/ )
    {
	$title = sprintf( "%03d. %s", ++$n, $line );
	$title =~ s/<[^>]+>//g;
	$title =~ s/\s+$//;
    }

    if ( $indiv == 1 &&
	 ( $line =~ /^([0-9]{6})/ || $line =~ /[^\#]{1}([0-9]{6})/ ) )
    {
	$run = $1;
	$stripped = $line;
	$stripped =~ s/<[^>]+>//g;
	$energy = substr( $stripped, 41, 9 );
	$energy =~ s/^\s+//;
	$lumi = substr( $stripped, 64 );
	
	$en{$title}{$run} = $energy;
 	$online{$title}{$run} = [ $1, $2 ]
 	    if ( $lumi =~ /([0-9\.]+)\s+\+\/\-\s+([0-9\.]+)/ )
    }
} # end loop over lines in run_info.html

opendir( DLK, "/home/dlk/Luminosities/" );
@dlk = readdir( DLK );
closedir( DLK );

foreach $file ( @dlk )
{
    next if ( $file !~ /^lumi\.[0-9]+$/ );
    open( PASS1, "/home/dlk/Luminosities/$file" );
    while ( $line = <PASS1> )
    {
	$pass1{$1} = [ $2, $3 ]
	    if ( $line =~ /^run([0-9]{6})\s+\*\s+CC Hadronic Cross Section \=\s+([0-9\.\-eE\+]+)\s+\+\-\s+([0-9\.\-eE\+]+)\s+nb/ );
    } # end of one lumi file
    close( PASS1 );
} # end of loop over lumi files

foreach $title ( sort keys %en )
{
    print "==================================== $title\n\n";

    print "Pass1 Lumi VS. Energy:\n";
    foreach $run ( sort keys %{ $en{$title} } )
    { print "{ $run, { $en{$title}{$run}, $pass1{$run}->[0], $pass1{$run}->[1] } },\n"
	  if ( defined( $pass1{$run} ) ); }
    print "\n";

} # end loop over titles
