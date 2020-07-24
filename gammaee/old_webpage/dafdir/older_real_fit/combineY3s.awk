BEGIN{ conts = 0; conten = 0; contx = 0; contsig = 0;
       peaks = 0; peaken = 0; peakx = 0; peaksig = 0;
       highs = 0; highen = 0; highx = 0; highsig = 0; }

($1<=10.34){ conts++; conten += $1; weight = 1./$3/$3; contx += $2*weight; contsig += weight; }

($1>10.34 && $1<10.3575){ print $0 };

($1>=10.3575 && $1<=10.361){ peaks++; peaken += $1; weight = 1./$3/$3; peakx += $2*weight; peaksig += weight; }

($1>10.361 && $1<10.39){ print $0 };

($1>=10.39){ highs++; highen += $1; weight = 1./$3/$3; highx += $2*weight; highsig += weight; }

END{ printf "%16.14f\t%16.14f\t%16.14f\n", (conten/conts), (contx/contsig), (1./sqrt(contsig));
     printf "%16.14f\t%16.14f\t%16.14f\n", (peaken/peaks), (peakx/peaksig), (1./sqrt(peaksig));
     printf "%16.14f\t%16.14f\t%16.14f\n", (highen/highs), (highx/highsig), (1./sqrt(highsig)); }


