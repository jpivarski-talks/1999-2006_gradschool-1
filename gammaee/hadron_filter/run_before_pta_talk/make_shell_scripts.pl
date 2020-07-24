#!/usr/local/bin/perl

foreach my $argv ( @ARGV ) {
    next if $argv !~ /^(.*)\.tcl$/;

    open( SCRIPT, "> $1.run" );
    print SCRIPT "#!/usr/local/bin/tcsh

cd \$HOME/hadron_filter/run
. /nfs/cleo3/scripts/cleo3defs
c3cur

suez -f $1.tcl > \$USER_TMP/$1.log
";
}
