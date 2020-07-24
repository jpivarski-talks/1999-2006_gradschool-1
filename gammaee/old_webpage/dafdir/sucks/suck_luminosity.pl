#!/usr/local/bin/perl

%en = ();
%livelu = ();
%bblu = ();
%gglu = ();

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
	$energy =~ s/^\s+//g;
	$lumi = substr( $stripped, 50, 13 );
	$lumi =~ s/^\s+//g;
	$xc = substr( $stripped, 64 );
	
	$en{$title}{$run} = $energy;
	$livelu{$title}{$run} = $lumi;
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
	$bblu{$1} = [ $2, $3, $4 ]
	    if ( $line =~ /^run([0-9]{6})\s+Barrel\s+Bhabha\s+Lum\s+=\s+BBLM\s+=\s+([0-9\.]+)\s+\+\-\s+([0-9\.]+)\s+\/nb\s+\(\s*([0-9]+)\)/ );

	$gglu{$1} = [ $2, $3, $4 ]
	    if ( $line =~ /^run([0-9]{6})\s+Barrel\s+GamGam\s+Lum\s+\/BBLM\s+=\s+([0-9.]+)\s+\+\-\s+([0-9.]+)\s+\(\s*([0-9]+)\s*\)/ );

    } # end of one lumi file
    close( PASS1 );
} # end of loop over lumi files

foreach $title ( sort keys %en )
{
#    next if ( $title !~ /scan/i );

    print "==================================== $title\n\n";

    print "Bhabha Lumi VS. Energy:\n";
    foreach $run ( sort keys %{ $en{$title} } )
    { print "{ $run, { $en{$title}{$run}, $bblu{$run}->[0], $bblu{$run}->[1] } },\n"
	  if ( defined( $bblu{$run} ) ); }
    print "\n";

    print "Bhabha Count VS. Energy:\n";
    foreach $run ( sort keys %{ $en{$title} } )
    { print "{ $run, { $en{$title}{$run}, $bblu{$run}->[2], ".sqrt($bblu{$run}->[2])." } },\n"
	  if ( defined( $bblu{$run} ) ); }
    print "\n";

    print "Bhabha Lumi / LiveLuminosity VS Energy:\n";
    foreach $run ( sort keys %{ $en{$title} } )
    { print "{ $run, { $en{$title}{$run}, ".( $bblu{$run}->[0] / $livelu{$title}{$run} ).", ".( $bblu{$run}->[1] / $livelu{$title}{$run} )." } },\n"
	  if ( defined( $bblu{$run} )  &&  defined( $livelu{$title}{$run} )
	       &&  $livelu{$title}{$run} != 0 ); }
    print "\n";

    print "Bhabha Lumi / Two-photon Lumi VS Energy:\n";
    foreach $run ( sort keys %{ $en{$title} } ) {
	if ( defined( $bblu{$run} )  &&  defined( $gglu{$run} )  &&
	     $gglu{$run} != 0. ) {
	    my $ratio = $bblu{$run}->[0] / $gglu{$run}->[0];
	    my $bberr = $bblu{$run}->[1] / $bblu{$run}->[0];
	    my $ggerr = $gglu{$run}->[1] / $gglu{$run}->[0];
	    my $err = $ratio * sqrt( $bberr * $bberr + $ggerr * $ggerr );

	    print "{ $run, { $en{$title}{$run}, $ratio, $err } },\n";
	} # end if defined
    } # end foreach run
    print "\n";

    print "Bhabha Events / Two-photon Events VS Energy:\n";
    foreach $run ( sort keys %{ $en{$title} } ) {
	if ( defined( $bblu{$run} )  &&  defined( $gglu{$run} )  &&
	     $gglu{$run} != 0 ) {
	    my $ratio = $bblu{$run}->[2] / $gglu{$run}->[2];
	    my $bberr = 1. / $bblu{$run}->[2];
	    my $ggerr = 1. / $gglu{$run}->[2];
	    my $err = $ratio * sqrt( $bberr + $ggerr );

	    print "{ $run, { $en{$title}{$run}, $ratio, $err } },\n";
	} # end if defined
    } # end foreach run
    print "\n";

} # end loop over titles
