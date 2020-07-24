m = 1777.03;
low = 10330;
high = 10400;

naievelow = 1/low^2;
naievehigh = 1/high^2;

tauxclow = naievelow;
tauxchigh = ( 1/high^2 * Sqrt[1 - m^2/high^2] * (1 + 0.5*m^2/high^2) )
    * naievelow / ( 1/low^2 * Sqrt[1 - m^2/low^2] * (1 + 0.5*m^2/low^2) )

                   -9
Out[35]= 9.24564 10

(tauxchigh / naievehigh - 1) * 100

Out[22]= 0.000888729

NIntegrate[ Pi / 137^2 / 10.330^2 *
	    (s^2*(1+costh)^2 * (1/s - 1/s/(1-costh))^2 +
	     (1-costh)^2 +
	     1/(1-costh)^2) /. s -> low^2, {costh, 0, 0.819152} ]
    * 0.38937929230 * 10^6

Out[48]= 6.43522

bhaxclow = naievelow;
bhaxchigh = NIntegrate[ Pi / 137^2 / s *
			(s^2*(1+costh)^2 * (1/s - 1/s/(1-costh))^2 +
			 (1-costh)^2 +
			 1/(1-costh)^2) /. s -> high^2, {costh, -0.93, 0.93} ]
    * naievelow / NIntegrate[ Pi / 137^2 / s *
		       (s^2*(1+costh)^2 * (1/s - 1/s/(1-costh))^2 +
			(1-costh)^2 +
			1/(1-costh)^2) /. s -> low^2, {costh, -0.93, 0.93} ]

                   -9
Out[45]= 9.24556 10

(bhaxchigh / naievehigh - 1) * 100

                   -14
Out[46]= 2.22045 10

Pi / 137^2 / s *
    (s^2*(1+costh)^2 * (1/s - 1/s/(1-costh))^2 +
     (1-costh)^2 +
     1/(1-costh)^2) // Expand

          2 Pi             2 Pi                  2 Pi
Out[49]= ------- + -------------------- - ------------------- + 
         18769 s                    2     18769 (1 - costh) s
                   18769 (1 - costh)  s
 
                                                         2
          2 costh Pi            4 costh Pi        2 costh  Pi
>    -------------------- - ------------------- + ----------- + 
                      2     18769 (1 - costh) s     18769 s
     18769 (1 - costh)  s
 
               2                       2
          costh  Pi             2 costh  Pi
>    -------------------- - -------------------
                      2     18769 (1 - costh) s
     18769 (1 - costh)  s

Exit

[Mathematica finished.]
