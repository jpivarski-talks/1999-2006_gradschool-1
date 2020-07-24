#!/usr/local/bin/perl

@theJulianDate = ( 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 );

sub leap_day                 
{                           
    my ($year,$month,$day) = @_;

    if (year % 4) {
	0;
    }

    if (!(year % 100)) {    # years that are multiples of 100 are not leap years
	if (year % 400) {   # unless they are multiples of 400
	    0;
	}
    }
    if (month < 2) {
	0;
    } elsif ((month == 2) && (day < 29)) {
	0;
    } else {
	1;
    }
}

sub julian_day
{
#     my ($dateInSeconds) = @_;
#     my ($sec, $min, $hour, $mday, $mon, $year, $wday, $yday);
#     ($sec, $min, $hour, $mday, $mon, $year, $wday, $yday) =
# 	localtime($dateInSeconds);

    my ($year, $mon, $mday) = @_;
    $mon--;

    $theJulianDate[$mon] + $mday + &leap_day($year,$mon,$mday);
}

sub seconds_since_midnight
{
    my ($hour, $minute) = @_;
    60 * ((60 * $hour) + $minute);
}

sub cesr_timestamp
{
    1e6 * (&julian_day(@_[0..2]) - 1) + int(&seconds_since_midnight(@_[3..4]) / 0.0864);
}

print &cesr_timestamp(substr($ARGV[0], 0, 4), substr($ARGV[0], 4, 2), substr($ARGV[0], 6, 2),
		      substr($ARGV[1], 0, 2), substr($ARGV[1], 3, 2)), "\n";
