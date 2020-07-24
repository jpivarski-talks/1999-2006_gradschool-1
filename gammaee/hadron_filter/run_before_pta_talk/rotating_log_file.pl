#!/usr/local/bin/perl

open( STDIN2, "<&STDIN" );

$name = $ARGV[0];

$count = 0;
$which = 0;
while( <STDIN2> )
{
    if ( $count == 0  &&  $which == 0 )
    {
	open( FILE, "> /cdat/tem/mccann/$name-a.log" );
	$which = 1;
    }
    elsif ( $count == 0  &&  $which == 1 )
    {
	open( FILE, "> /cdat/tem/mccann/$name-b.log" );
	$which = 0;
    }
    print FILE $_;
    $count++;
    if ( $count == 100000 )
    {
	$count = 0;
    }
}
