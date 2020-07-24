($1=="param" && $2=="area"){ printf( "area = %7.3f +/- %5.3f MeV nb\n", $4, $6 ) }
($1=="param" && $2=="mass"){ printf( "mass = %10.8f +/- %10.8f GeV\n", $4, $6 ) }
($1=="param" && $2=="wide"){ printf( "wide = %8.6f +/- %8.6f MeV\n", $4, $6 ) }
($1=="param" && $2=="back"){ printf( "back = %7.5f +/- %7.5f nb\n", $4, $6 ) }
