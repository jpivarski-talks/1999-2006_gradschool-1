<< Graphics`Graphics`

g[x_, sig_] := Exp[ -x^2/2/sig^2 ] / sig / Sqrt[2 Pi];
bw[x_, gam_] := (gam/2) / (x^2 + gam^2/4) / Pi;
kf[x_, s_] := Simplify[ ( ( t*frac^(t-1) * (1 + (alpha/Pi)*(Pi^2/3 - 1/2) + (3/4)*t
					    -(t^2/24) * ((1/2)*Log[s/me^2] + 2*Pi^2 - 37/4))
			    -t*(1 - frac/2)
			    +(t^2/8) * (4*(2-frac)*Log[1/frac]
					- ((1 + 3*(1-frac)^2)/frac)*Log[1-frac] - 6 + frac)
			  ) /. { t -> 2*(alpha/Pi)*(Log[s/me^2] - 1), frac -> x/(s+x) }
			) /. { alpha -> 1/137.0359997650, me -> 0.51099890221 }
		      ];

Integrate[#,{z,0,10}]& /@ ( List @@ Expand[ kf[z,s] ] )


Integrate[ Simplify[ kf[z,10.358]*bw[1.1-z,26.3/1000] ], {z, 0, 1.1} ]

                                 1
Power::infy: Infinite expression -- encountered.
                                 0.

                                 1
Power::infy: Infinite expression -- encountered.
                                 0.

                                 1
Power::infy: Infinite expression -- encountered.
                                 0.

General::stop: Further output of Power::infy
     will be suppressed during this calculation.

                                                       0
Infinity::indet: Indeterminate expression (-I Infinity)  encountered.

                                                       0
Infinity::indet: Indeterminate expression (-I Infinity)  encountered.

Infinity::indet: Indeterminate expression 0 Infinity encountered.

General::stop: Further output of Infinity::indet
     will be suppressed during this calculation.

                                    0.0126488
Out[96]= 0.00418578 Integrate[(-------------------- + 
                                    z      0.987547
                               (----------)
                                10.358 + z
 
         -0.128986 - 0.0062264 z
>        ----------------------- + 
               10.358 + z
 
                                                     2        10.358
>        ((-0.0083187 - 0.000401559 z - 0.000019384 z ) Log[----------] + 
                                                            10.358 + z
 
>           z (-0.00120468 - 0.0000969201 z + 
 
                                                 10.358 + z
>              (0.00160624 + 0.0000775361 z) Log[----------])) / 
                                                     z
 
                                                  2
>         (z (10.358 + z))) / (1.21017 - 2.2 z + z ), {z, 0, 1.1}]

Out[95]= -Graphics-

Out[94]= -Graphics-








NIntegrate[ kf[x, 10.358], {x, 0, 100} ]



Module[ {x, y, z, integrand},
	integrand = Simplify[ g[z, 4.58] * bw[y-z, 52.5/1000] * kf[x-y, 10.358] ]
(*	Plot[ integrand, {y, x, x-5} ] *)
(* 	Table[ NIntegrate[ integrand, {y, x - 10^power, x - 5} ], {power, -1, -10, -1} ] *)
      ]







