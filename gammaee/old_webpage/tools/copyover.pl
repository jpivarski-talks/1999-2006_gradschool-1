#!/usr/local/bin/perl

@base = ( "index.html", "run_infoY1s.html", "run_infoY2s.html", "run_infoY3s.html",
	  "run_info_frameset.html", "run_info_labels.html",
	  "images", "run_info_plots", "fits" );

$original = "/home/mccann/public_html/private/my_gammaee";
$copy = "/nfs/web/restricted/CLEO/analysis/QCD/gammaee";

### Copy everything which is currently there to a new backup tree ##################
&backup();
sub backup {
    my $n = 1;
    my $backup;
    while ( -e ( $backup = sprintf( "$copy/backup-%04d", $n ) ) ) { $n++ }
    mkdir( $backup, 0775 );
    opendir( COPY, $copy );
    @copy = readdir( COPY );
    closedir( COPY );
    foreach my $file ( @copy ) {
	next if ( $file eq "."  ||  $file eq ".."  ||  $file eq "gammaee.html"  ||
		  $file =~ /backup\-[0-9]{4}/ );
	rename( "$copy/$file", "$backup/$file" );
    }
}

### Subroutine to copy a file ######################################################
sub copy_file {
    my $file = @_[0];
    
    system( "cp", "$original/$file", "$copy/$file" );
    chmod( 0664, "$copy/$file" );
}

### Subroutine to copy a directory #################################################
sub copy_dir {
    my $dir = @_[0];

    mkdir( "$copy/$dir", 0775 );
    opendir( OLD, "$original/$dir" );
    my @old = readdir( OLD );
    closedir( OLD );
    my @new = ();
    foreach my $file ( @old ) {
	next if ( $file eq "."  ||  $file eq ".."  ||  $file =~ /~$/  ||  $file =~ /^\#.*\#$/ );
	push( @new, "$dir/$file" );
    }
    
    &recursively_copy( @new );
}

### Start the (recursive) copying process ##########################################
&recursively_copy( @base );
sub recursively_copy {
    my @tree = @_;
    foreach my $file ( @tree ) {
	if ( -d "$original/$file" ) {
	    copy_dir( $file );
	}
	else {
	    copy_file( $file );
	}
    }
}
