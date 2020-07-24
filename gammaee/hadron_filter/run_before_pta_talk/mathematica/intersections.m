Clear[CombineUV];
CombineUV[ u0a^2 + v0a^2 ] := 1;
CombineUV[ x_ + u0a^2 + v0a^2 ] := x + 1;
CombineUV[ y_ * ( u0a^2 + v0a^2 ) ] := y;
CombineUV[ x_ + y_ * ( u0a^2 + v0a^2 ) ] := x + y;
CombineUV[ u0b^2 + v0b^2 ] := 1;
CombineUV[ x_ + u0b^2 + v0b^2 ] := x + 1;
CombineUV[ y_ * ( u0b^2 + v0b^2 ) ] := y;
CombineUV[ x_ + y_ * ( u0b^2 + v0b^2 ) ] := x + y;
CombineUV[ other_ ] := other;

Clear[SquashPowers];
SquashPowers[ Sqrt[Times[x_^2,y_]] ] := x * Sqrt[y];
SquashPowers[ Sqrt[x_^2] ] := x;
SquashPowers[ other_ ] := other;

(* x == X - x0a, x0 = x0a - x0b, y == Y - y0a, y0 = y0a - y0b *)
{sol1, sol2} = 
    Simplify[ Solve[ { (x + v0a/rhoa)^2 + (y - u0a/rhoa)^2 == 1/rhoa^2,
		       (x + x0 + v0b/rhob)^2 + (y + y0 - u0b/rhob)^2 == 1/rhob^2 },
		     {x, y} ],
	      TransformationFunctions -> {Automatic,CombineUV}
	    ];

xsol1 = Simplify[ Simplify[ ( Normal[ Series[ x + x0a /. sol1, {rhoa, 0, 1}, {rhob, 0, 1} ] ]
			      /. {x0 -> x0a - x0b, y0 -> y0a - y0b} )
			    /. {x0a -> -d0a * Sin[phi0a], y0a -> d0a * Cos[phi0a],
				x0b -> -d0b * Sin[phi0b], y0b -> d0b * Cos[phi0b],
				rhoa -> 2 * curva, rhob -> 2 * curvb,
				u0a -> Cos[phi0a], v0a -> Sin[phi0a],
				u0b -> Cos[phi0b], v0b -> Sin[phi0b] }
			    , Trig -> True ]
		  , TransformationFunctions -> {Automatic,SquashPowers} ]

Out[4]= ((2 ((3 + 2 curva d0a) d0b + 
 
                        2               3      2                   2
>           curvb (4 d0a  + 16 curva d0a  + d0b  + 54 curva d0a d0b )) 
 
>         Cos[phi0a] + d0a (-1 + curva d0a) Cos[4 phi0a - 5 phi0b] + 
 
>        d0b Cos[3 phi0a - 4 phi0b] - 
 
>        4 curva d0a d0b Cos[3 phi0a - 4 phi0b] - 
 
                  2
>        curvb d0b  Cos[3 phi0a - 4 phi0b] + 
 
                              2
>        4 curva curvb d0a d0b  Cos[3 phi0a - 4 phi0b] + 
 
                                               2
>        d0b Cos[5 phi0a - 4 phi0b] - curvb d0b  Cos[5 phi0a - 4 phi0b] + 
 
>        4 d0a Cos[2 phi0a - 3 phi0b] + 
 
>        4 curvb d0a d0b Cos[2 phi0a - 3 phi0b] - 
 
                           2
>        20 curva curvb d0a  d0b Cos[2 phi0a - 3 phi0b] + 
 
                    2
>        4 curva d0b  Cos[2 phi0a - 3 phi0b] - 
 
                          3
>        8 curva curvb d0b  Cos[2 phi0a - 3 phi0b] - 
 
                                               2
>        d0a Cos[4 phi0a - 3 phi0b] + curva d0a  Cos[4 phi0a - 3 phi0b] + 
 
>        4 curvb d0a d0b Cos[4 phi0a - 3 phi0b] - 
 
                          2
>        4 curva curvb d0a  d0b Cos[4 phi0a - 3 phi0b] - 
 
                    2
>        4 curvb d0a  Cos[phi0a - 2 phi0b] + 
 
                           3
>        24 curva curvb d0a  Cos[phi0a - 2 phi0b] - 
 
>        4 d0b Cos[phi0a - 2 phi0b] + 4 curva d0a d0b Cos[phi0a - 2 phi0b] + 
 
                               2
>        60 curva curvb d0a d0b  Cos[phi0a - 2 phi0b] - 
 
                    2
>        4 curvb d0a  Cos[3 phi0a - 2 phi0b] + 
 
                          3
>        8 curva curvb d0a  Cos[3 phi0a - 2 phi0b] - 
 
>        4 d0b Cos[3 phi0a - 2 phi0b] - 
 
>        4 curva d0a d0b Cos[3 phi0a - 2 phi0b] + 
 
                               2
>        20 curva curvb d0a d0b  Cos[3 phi0a - 2 phi0b] + 
 
>        4 d0a Cos[2 phi0a - phi0b] - 4 curvb d0a d0b Cos[2 phi0a - phi0b] - 
 
                           2
>        60 curva curvb d0a  d0b Cos[2 phi0a - phi0b] + 
 
                    2
>        4 curva d0b  Cos[2 phi0a - phi0b] - 
 
                           3
>        24 curva curvb d0b  Cos[2 phi0a - phi0b] - 6 d0a Cos[phi0b] - 
 
                    2
>        2 curva d0a  Cos[phi0b] - 4 curvb d0a d0b Cos[phi0b] - 
 
                            2                             2
>        108 curva curvb d0a  d0b Cos[phi0b] - 8 curva d0b  Cos[phi0b] - 
 
                           3                               5
>        32 curva curvb d0b  Cos[phi0b]) Csc[phi0a - phi0b] ) / 16

xsol2 = Simplify[ Simplify[ ( Normal[ Series[ x + x0a /. sol2, {rhoa, 0, 1}, {rhob, 0, 1} ] ]
			      /. {x0 -> x0a - x0b, y0 -> y0a - y0b} )
			    /. {x0a -> -d0a * Sin[phi0a], y0a -> d0a * Cos[phi0a],
				x0b -> -d0b * Sin[phi0b], y0b -> d0b * Cos[phi0b],
				rhoa -> 2 * curva, rhob -> 2 * curvb,
				u0a -> Cos[phi0a], v0a -> Sin[phi0a],
				u0b -> Cos[phi0b], v0b -> Sin[phi0b] }
			    , Trig -> True ]
		  , TransformationFunctions -> {Automatic,SquashPowers} ]

                                              2       2      2
Out[5]= -((4 curvb (-5 - 4 curvb d0b + 2 curvb  (4 d0a  + d0b ) + 
 
                                                  2        2         2
>            2 curva d0a (5 + 12 curvb d0b + curvb  (16 d0a  + 54 d0b ))) 
 
                                               2
>          Cos[phi0a] + curva (1 + 2 curvb d0b)  Cos[8 phi0a - 7 phi0b] + 
 
>         curvb Cos[5 phi0a - 6 phi0b] + 
 
                 2
>         2 curvb  d0b Cos[5 phi0a - 6 phi0b] + 
 
>         curvb Cos[7 phi0a - 6 phi0b] - 
 
>         4 curva curvb d0a Cos[7 phi0a - 6 phi0b] + 
 
                 2
>         2 curvb  d0b Cos[7 phi0a - 6 phi0b] - 
 
                       2
>         8 curva curvb  d0a d0b Cos[7 phi0a - 6 phi0b] + 
 
>         curva Cos[4 phi0a - 5 phi0b] - 6 curva Cos[6 phi0a - 5 phi0b] - 
 
                 2
>         4 curvb  d0a Cos[6 phi0a - 5 phi0b] + 
 
                       2    2
>         4 curva curvb  d0a  Cos[6 phi0a - 5 phi0b] - 
 
>         20 curva curvb d0b Cos[6 phi0a - 5 phi0b] - 
 
                        2    2
>         20 curva curvb  d0b  Cos[6 phi0a - 5 phi0b] - 
 
>         6 curvb Cos[3 phi0a - 4 phi0b] + 
 
>         4 curva curvb d0a Cos[3 phi0a - 4 phi0b] - 
 
                 2
>         8 curvb  d0b Cos[3 phi0a - 4 phi0b] - 
 
                       2
>         8 curva curvb  d0a d0b Cos[3 phi0a - 4 phi0b] - 
 
                 3    2
>         4 curvb  d0b  Cos[3 phi0a - 4 phi0b] + 
 
                        3        2
>         16 curva curvb  d0a d0b  Cos[3 phi0a - 4 phi0b] - 
 
>         6 curvb Cos[5 phi0a - 4 phi0b] + 
 
>         20 curva curvb d0a Cos[5 phi0a - 4 phi0b] - 
 
                 2
>         8 curvb  d0b Cos[5 phi0a - 4 phi0b] + 
 
                        2
>         40 curva curvb  d0a d0b Cos[5 phi0a - 4 phi0b] - 
 
                 3    2
>         4 curvb  d0b  Cos[5 phi0a - 4 phi0b] - 
 
>         6 curva Cos[2 phi0a - 3 phi0b] - 
 
                 2
>         4 curvb  d0a Cos[2 phi0a - 3 phi0b] + 
 
                        2    2
>         20 curva curvb  d0a  Cos[2 phi0a - 3 phi0b] - 
 
>         4 curva curvb d0b Cos[2 phi0a - 3 phi0b] + 
 
                  3
>         16 curvb  d0a d0b Cos[2 phi0a - 3 phi0b] - 
 
                        3    2
>         80 curva curvb  d0a  d0b Cos[2 phi0a - 3 phi0b] + 
 
                        2    2
>         12 curva curvb  d0b  Cos[2 phi0a - 3 phi0b] - 
 
                        3    3
>         32 curva curvb  d0b  Cos[2 phi0a - 3 phi0b] + 
 
>         15 curva Cos[4 phi0a - 3 phi0b] + 
 
                  2
>         16 curvb  d0a Cos[4 phi0a - 3 phi0b] - 
 
                        2    2
>         16 curva curvb  d0a  Cos[4 phi0a - 3 phi0b] + 
 
>         40 curva curvb d0b Cos[4 phi0a - 3 phi0b] + 
 
                  3
>         16 curvb  d0a d0b Cos[4 phi0a - 3 phi0b] - 
 
                        3    2
>         16 curva curvb  d0a  d0b Cos[4 phi0a - 3 phi0b] + 
 
                        2    2
>         40 curva curvb  d0b  Cos[4 phi0a - 3 phi0b] + 
 
>         15 curvb Cos[phi0a - 2 phi0b] - 
 
>         20 curva curvb d0a Cos[phi0a - 2 phi0b] - 
 
                  3    2
>         16 curvb  d0a  Cos[phi0a - 2 phi0b] + 
 
                        3    3
>         96 curva curvb  d0a  Cos[phi0a - 2 phi0b] + 
 
                  2
>         14 curvb  d0b Cos[phi0a - 2 phi0b] - 
 
                        2
>         24 curva curvb  d0a d0b Cos[phi0a - 2 phi0b] + 
 
                         3        2
>         240 curva curvb  d0a d0b  Cos[phi0a - 2 phi0b] + 
 
>         15 curvb Cos[3 phi0a - 2 phi0b] - 
 
>         40 curva curvb d0a Cos[3 phi0a - 2 phi0b] - 
 
                  3    2
>         16 curvb  d0a  Cos[3 phi0a - 2 phi0b] + 
 
                        3    3
>         32 curva curvb  d0a  Cos[3 phi0a - 2 phi0b] + 
 
                  2
>         14 curvb  d0b Cos[3 phi0a - 2 phi0b] - 
 
                        2
>         96 curva curvb  d0a d0b Cos[3 phi0a - 2 phi0b] + 
 
                        3        2
>         80 curva curvb  d0a d0b  Cos[3 phi0a - 2 phi0b] - 
 
>         20 curva Cos[2 phi0a - phi0b] - 
 
                  2
>         24 curvb  d0a Cos[2 phi0a - phi0b] + 
 
                        2    2
>         40 curva curvb  d0a  Cos[2 phi0a - phi0b] - 
 
>         40 curva curvb d0b Cos[2 phi0a - phi0b] - 
 
                  3
>         16 curvb  d0a d0b Cos[2 phi0a - phi0b] - 
 
                         3    2
>         240 curva curvb  d0a  d0b Cos[2 phi0a - phi0b] - 
 
                        2    2
>         24 curva curvb  d0b  Cos[2 phi0a - phi0b] - 
 
                        3    3
>         96 curva curvb  d0b  Cos[2 phi0a - phi0b] + 15 curva Cos[phi0b] + 
 
                  2                                2    2
>         16 curvb  d0a Cos[phi0b] - 48 curva curvb  d0a  Cos[phi0b] + 
 
                                                  3
>         20 curva curvb d0b Cos[phi0b] - 16 curvb  d0a d0b Cos[phi0b] - 
 
                         3    2
>         432 curva curvb  d0a  d0b Cos[phi0b] - 
 
                        2    2                             3    3
>         12 curva curvb  d0b  Cos[phi0b] - 128 curva curvb  d0b  Cos[phi0b]) 
 
                          5             2
>       Csc[phi0a - phi0b] ) / (64 curvb )

ysol1 = Simplify[ Simplify[ ( Normal[ Series[ y + y0a /. sol1, {rhoa, 0, 1}, {rhob, 0, 1} ] ]
			      /. {x0 -> x0a - x0b, y0 -> y0a - y0b} )
			    /. {x0a -> -d0a * Sin[phi0a], y0a -> d0a * Cos[phi0a],
				x0b -> -d0b * Sin[phi0b], y0b -> d0b * Cos[phi0b],
				rhoa -> 2 * curva, rhob -> 2 * curvb,
				u0a -> Cos[phi0a], v0a -> Sin[phi0a],
				u0b -> Cos[phi0b], v0b -> Sin[phi0b] }
			    , Trig -> True ]
		  , TransformationFunctions -> {Automatic,SquashPowers} ]

                            5
Out[6]= -(Csc[phi0a - phi0b]  (-2 
 
>          ((3 + 2 curva d0a) d0b + 
 
                         2               3      2                   2
>            curvb (4 d0a  + 16 curva d0a  + d0b  + 54 curva d0a d0b )) 
 
>          Sin[phi0a] + d0a (-1 + curva d0a) Sin[4 phi0a - 5 phi0b] + 
 
>         d0b Sin[3 phi0a - 4 phi0b] - 
 
>         4 curva d0a d0b Sin[3 phi0a - 4 phi0b] - 
 
                   2
>         curvb d0b  Sin[3 phi0a - 4 phi0b] + 
 
                               2
>         4 curva curvb d0a d0b  Sin[3 phi0a - 4 phi0b] - 
 
                                                2
>         d0b Sin[5 phi0a - 4 phi0b] + curvb d0b  Sin[5 phi0a - 4 phi0b] + 
 
>         4 d0a Sin[2 phi0a - 3 phi0b] + 
 
>         4 curvb d0a d0b Sin[2 phi0a - 3 phi0b] - 
 
                            2
>         20 curva curvb d0a  d0b Sin[2 phi0a - 3 phi0b] + 
 
                     2
>         4 curva d0b  Sin[2 phi0a - 3 phi0b] - 
 
                           3
>         8 curva curvb d0b  Sin[2 phi0a - 3 phi0b] + 
 
                                                2
>         d0a Sin[4 phi0a - 3 phi0b] - curva d0a  Sin[4 phi0a - 3 phi0b] - 
 
>         4 curvb d0a d0b Sin[4 phi0a - 3 phi0b] + 
 
                           2
>         4 curva curvb d0a  d0b Sin[4 phi0a - 3 phi0b] - 
 
                     2
>         4 curvb d0a  Sin[phi0a - 2 phi0b] + 
 
                            3
>         24 curva curvb d0a  Sin[phi0a - 2 phi0b] - 
 
>         4 d0b Sin[phi0a - 2 phi0b] + 4 curva d0a d0b Sin[phi0a - 2 phi0b] + 
 
                                2
>         60 curva curvb d0a d0b  Sin[phi0a - 2 phi0b] + 
 
                     2
>         4 curvb d0a  Sin[3 phi0a - 2 phi0b] - 
 
                           3
>         8 curva curvb d0a  Sin[3 phi0a - 2 phi0b] + 
 
>         4 d0b Sin[3 phi0a - 2 phi0b] + 
 
>         4 curva d0a d0b Sin[3 phi0a - 2 phi0b] - 
 
                                2
>         20 curva curvb d0a d0b  Sin[3 phi0a - 2 phi0b] - 
 
>         4 d0a Sin[2 phi0a - phi0b] + 4 curvb d0a d0b Sin[2 phi0a - phi0b] + 
 
                            2
>         60 curva curvb d0a  d0b Sin[2 phi0a - phi0b] - 
 
                     2
>         4 curva d0b  Sin[2 phi0a - phi0b] + 
 
                            3
>         24 curva curvb d0b  Sin[2 phi0a - phi0b] + 6 d0a Sin[phi0b] + 
 
                     2
>         2 curva d0a  Sin[phi0b] + 4 curvb d0a d0b Sin[phi0b] + 
 
                             2                             2
>         108 curva curvb d0a  d0b Sin[phi0b] + 8 curva d0b  Sin[phi0b] + 
 
                            3
>         32 curva curvb d0b  Sin[phi0b])) / 16

ysol2 = Simplify[ Simplify[ ( Normal[ Series[ y + y0a /. sol2, {rhoa, 0, 1}, {rhob, 0, 1} ] ]
			      /. {x0 -> x0a - x0b, y0 -> y0a - y0b} )
			    /. {x0a -> -d0a * Sin[phi0a], y0a -> d0a * Cos[phi0a],
				x0b -> -d0b * Sin[phi0b], y0b -> d0b * Cos[phi0b],
				rhoa -> 2 * curva, rhob -> 2 * curvb,
				u0a -> Cos[phi0a], v0a -> Sin[phi0a],
				u0b -> Cos[phi0b], v0b -> Sin[phi0b] }
			    , Trig -> True ]
		  , TransformationFunctions -> {Automatic,SquashPowers} ]

                           5
Out[7]= (Csc[phi0a - phi0b]  (-4 curvb 
 
                                     2       2      2
>         (-5 - 4 curvb d0b + 2 curvb  (4 d0a  + d0b ) + 
 
                                                 2        2         2
>           2 curva d0a (5 + 12 curvb d0b + curvb  (16 d0a  + 54 d0b ))) 
 
                                              2
>         Sin[phi0a] - curva (1 + 2 curvb d0b)  Sin[8 phi0a - 7 phi0b] + 
 
                                               2
>        curvb Sin[5 phi0a - 6 phi0b] + 2 curvb  d0b Sin[5 phi0a - 6 phi0b] - 
 
>        curvb Sin[7 phi0a - 6 phi0b] + 
 
>        4 curva curvb d0a Sin[7 phi0a - 6 phi0b] - 
 
                2
>        2 curvb  d0b Sin[7 phi0a - 6 phi0b] + 
 
                      2
>        8 curva curvb  d0a d0b Sin[7 phi0a - 6 phi0b] + 
 
>        curva Sin[4 phi0a - 5 phi0b] + 6 curva Sin[6 phi0a - 5 phi0b] + 
 
                2
>        4 curvb  d0a Sin[6 phi0a - 5 phi0b] - 
 
                      2    2
>        4 curva curvb  d0a  Sin[6 phi0a - 5 phi0b] + 
 
>        20 curva curvb d0b Sin[6 phi0a - 5 phi0b] + 
 
                       2    2
>        20 curva curvb  d0b  Sin[6 phi0a - 5 phi0b] - 
 
>        6 curvb Sin[3 phi0a - 4 phi0b] + 
 
>        4 curva curvb d0a Sin[3 phi0a - 4 phi0b] - 
 
                2
>        8 curvb  d0b Sin[3 phi0a - 4 phi0b] - 
 
                      2
>        8 curva curvb  d0a d0b Sin[3 phi0a - 4 phi0b] - 
 
                3    2
>        4 curvb  d0b  Sin[3 phi0a - 4 phi0b] + 
 
                       3        2
>        16 curva curvb  d0a d0b  Sin[3 phi0a - 4 phi0b] + 
 
>        6 curvb Sin[5 phi0a - 4 phi0b] - 
 
>        20 curva curvb d0a Sin[5 phi0a - 4 phi0b] + 
 
                2
>        8 curvb  d0b Sin[5 phi0a - 4 phi0b] - 
 
                       2
>        40 curva curvb  d0a d0b Sin[5 phi0a - 4 phi0b] + 
 
                3    2
>        4 curvb  d0b  Sin[5 phi0a - 4 phi0b] - 
 
>        6 curva Sin[2 phi0a - 3 phi0b] - 
 
                2
>        4 curvb  d0a Sin[2 phi0a - 3 phi0b] + 
 
                       2    2
>        20 curva curvb  d0a  Sin[2 phi0a - 3 phi0b] - 
 
>        4 curva curvb d0b Sin[2 phi0a - 3 phi0b] + 
 
                 3
>        16 curvb  d0a d0b Sin[2 phi0a - 3 phi0b] - 
 
                       3    2
>        80 curva curvb  d0a  d0b Sin[2 phi0a - 3 phi0b] + 
 
                       2    2
>        12 curva curvb  d0b  Sin[2 phi0a - 3 phi0b] - 
 
                       3    3
>        32 curva curvb  d0b  Sin[2 phi0a - 3 phi0b] - 
 
>        15 curva Sin[4 phi0a - 3 phi0b] - 
 
                 2
>        16 curvb  d0a Sin[4 phi0a - 3 phi0b] + 
 
                       2    2
>        16 curva curvb  d0a  Sin[4 phi0a - 3 phi0b] - 
 
>        40 curva curvb d0b Sin[4 phi0a - 3 phi0b] - 
 
                 3
>        16 curvb  d0a d0b Sin[4 phi0a - 3 phi0b] + 
 
                       3    2
>        16 curva curvb  d0a  d0b Sin[4 phi0a - 3 phi0b] - 
 
                       2    2
>        40 curva curvb  d0b  Sin[4 phi0a - 3 phi0b] + 
 
>        15 curvb Sin[phi0a - 2 phi0b] - 
 
>        20 curva curvb d0a Sin[phi0a - 2 phi0b] - 
 
                 3    2
>        16 curvb  d0a  Sin[phi0a - 2 phi0b] + 
 
                       3    3
>        96 curva curvb  d0a  Sin[phi0a - 2 phi0b] + 
 
                 2
>        14 curvb  d0b Sin[phi0a - 2 phi0b] - 
 
                       2
>        24 curva curvb  d0a d0b Sin[phi0a - 2 phi0b] + 
 
                        3        2
>        240 curva curvb  d0a d0b  Sin[phi0a - 2 phi0b] - 
 
>        15 curvb Sin[3 phi0a - 2 phi0b] + 
 
>        40 curva curvb d0a Sin[3 phi0a - 2 phi0b] + 
 
                 3    2
>        16 curvb  d0a  Sin[3 phi0a - 2 phi0b] - 
 
                       3    3
>        32 curva curvb  d0a  Sin[3 phi0a - 2 phi0b] - 
 
                 2
>        14 curvb  d0b Sin[3 phi0a - 2 phi0b] + 
 
                       2
>        96 curva curvb  d0a d0b Sin[3 phi0a - 2 phi0b] - 
 
                       3        2
>        80 curva curvb  d0a d0b  Sin[3 phi0a - 2 phi0b] + 
 
                                                 2
>        20 curva Sin[2 phi0a - phi0b] + 24 curvb  d0a Sin[2 phi0a - phi0b] - 
 
                       2    2
>        40 curva curvb  d0a  Sin[2 phi0a - phi0b] + 
 
>        40 curva curvb d0b Sin[2 phi0a - phi0b] + 
 
                 3
>        16 curvb  d0a d0b Sin[2 phi0a - phi0b] + 
 
                        3    2
>        240 curva curvb  d0a  d0b Sin[2 phi0a - phi0b] + 
 
                       2    2
>        24 curva curvb  d0b  Sin[2 phi0a - phi0b] + 
 
                       3    3
>        96 curva curvb  d0b  Sin[2 phi0a - phi0b] - 15 curva Sin[phi0b] - 
 
                 2                                2    2
>        16 curvb  d0a Sin[phi0b] + 48 curva curvb  d0a  Sin[phi0b] - 
 
                                                 3
>        20 curva curvb d0b Sin[phi0b] + 16 curvb  d0a d0b Sin[phi0b] + 
 
                        3    2
>        432 curva curvb  d0a  d0b Sin[phi0b] + 
 
                       2    2                             3    3
>        12 curva curvb  d0b  Sin[phi0b] + 128 curva curvb  d0b  Sin[phi0b]))\
 
                 2
>     / (64 curvb )

dxsol1dd0a = Simplify[ D[xsol1, d0a], Trig -> True ]

                                                    2               2
Out[8]= ((4 (curva d0b + curvb (4 d0a + 24 curva d0a  + 27 curva d0b )) 
 
>         Cos[phi0a] + (-1 + 2 curva d0a) Cos[4 phi0a - 5 phi0b] - 
 
>        4 curva d0b Cos[3 phi0a - 4 phi0b] + 
 
                          2
>        4 curva curvb d0b  Cos[3 phi0a - 4 phi0b] + 
 
>        4 Cos[2 phi0a - 3 phi0b] + 4 curvb d0b Cos[2 phi0a - 3 phi0b] - 
 
>        40 curva curvb d0a d0b Cos[2 phi0a - 3 phi0b] - 
 
>        Cos[4 phi0a - 3 phi0b] + 2 curva d0a Cos[4 phi0a - 3 phi0b] + 
 
>        4 curvb d0b Cos[4 phi0a - 3 phi0b] - 
 
>        8 curva curvb d0a d0b Cos[4 phi0a - 3 phi0b] - 
 
>        8 curvb d0a Cos[phi0a - 2 phi0b] + 
 
                           2
>        72 curva curvb d0a  Cos[phi0a - 2 phi0b] + 
 
>        4 curva d0b Cos[phi0a - 2 phi0b] + 
 
                           2
>        60 curva curvb d0b  Cos[phi0a - 2 phi0b] - 
 
>        8 curvb d0a Cos[3 phi0a - 2 phi0b] + 
 
                           2
>        24 curva curvb d0a  Cos[3 phi0a - 2 phi0b] - 
 
>        4 curva d0b Cos[3 phi0a - 2 phi0b] + 
 
                           2
>        20 curva curvb d0b  Cos[3 phi0a - 2 phi0b] + 
 
>        4 Cos[2 phi0a - phi0b] - 4 curvb d0b Cos[2 phi0a - phi0b] - 
 
>        120 curva curvb d0a d0b Cos[2 phi0a - phi0b] - 6 Cos[phi0b] - 
 
>        4 curva d0a Cos[phi0b] - 4 curvb d0b Cos[phi0b] - 
 
                                                               5
>        216 curva curvb d0a d0b Cos[phi0b]) Csc[phi0a - phi0b] ) / 16

dxsol1dd0b = Simplify[ D[xsol1, d0b], Trig -> True ]

Out[9]= (((6 + 4 curvb d0b + 4 curva (d0a + 54 curvb d0a d0b)) Cos[phi0a] + 
 
>        (-1 + 4 curva d0a) (-1 + 2 curvb d0b) Cos[3 phi0a - 4 phi0b] + 
 
>        Cos[5 phi0a - 4 phi0b] - 2 curvb d0b Cos[5 phi0a - 4 phi0b] + 
 
>        4 curvb d0a Cos[2 phi0a - 3 phi0b] - 
 
                           2
>        20 curva curvb d0a  Cos[2 phi0a - 3 phi0b] + 
 
>        8 curva d0b Cos[2 phi0a - 3 phi0b] - 
 
                           2
>        24 curva curvb d0b  Cos[2 phi0a - 3 phi0b] + 
 
>        4 curvb d0a Cos[4 phi0a - 3 phi0b] - 
 
                          2
>        4 curva curvb d0a  Cos[4 phi0a - 3 phi0b] - 4 Cos[phi0a - 2 phi0b] + 
 
>        4 curva d0a Cos[phi0a - 2 phi0b] + 
 
>        120 curva curvb d0a d0b Cos[phi0a - 2 phi0b] - 
 
>        4 Cos[3 phi0a - 2 phi0b] - 4 curva d0a Cos[3 phi0a - 2 phi0b] + 
 
>        40 curva curvb d0a d0b Cos[3 phi0a - 2 phi0b] - 
 
>        4 curvb d0a Cos[2 phi0a - phi0b] - 
 
                           2
>        60 curva curvb d0a  Cos[2 phi0a - phi0b] + 
 
>        8 curva d0b Cos[2 phi0a - phi0b] - 
 
                           2
>        72 curva curvb d0b  Cos[2 phi0a - phi0b] - 4 curvb d0a Cos[phi0b] - 
 
                            2
>        108 curva curvb d0a  Cos[phi0b] - 16 curva d0b Cos[phi0b] - 
 
                           2                               5
>        96 curva curvb d0b  Cos[phi0b]) Csc[phi0a - phi0b] ) / 16

dxsol1dphi0a = Simplify[ D[xsol1, phi0a], Trig -> True ]

                                                    2
Out[10]= -((-2 (d0a + 24 curvb d0a d0b + 2 curva d0b  (3 + 82 curvb d0b) + 
 
                  2
>            5 d0a  (curva + 96 curva curvb d0b)) Cos[phi0a] + 
 
>         d0a (-1 + curva d0a) Cos[5 phi0a - 6 phi0b] + 
 
>         2 d0b Cos[4 phi0a - 5 phi0b] - 
 
>         8 curva d0a d0b Cos[4 phi0a - 5 phi0b] - 
 
                     2
>         2 curvb d0b  Cos[4 phi0a - 5 phi0b] + 
 
                               2
>         8 curva curvb d0a d0b  Cos[4 phi0a - 5 phi0b] + 
 
>         3 d0a Cos[3 phi0a - 4 phi0b] + 
 
                     2
>         9 curva d0a  Cos[3 phi0a - 4 phi0b] + 
 
>         12 curvb d0a d0b Cos[3 phi0a - 4 phi0b] - 
 
                            2
>         60 curva curvb d0a  d0b Cos[3 phi0a - 4 phi0b] + 
 
                      2
>         12 curva d0b  Cos[3 phi0a - 4 phi0b] - 
 
                            3
>         24 curva curvb d0b  Cos[3 phi0a - 4 phi0b] - 
 
                                                2
>         d0a Cos[5 phi0a - 4 phi0b] + curva d0a  Cos[5 phi0a - 4 phi0b] + 
 
>         4 curvb d0a d0b Cos[5 phi0a - 4 phi0b] - 
 
                           2
>         4 curva curvb d0a  d0b Cos[5 phi0a - 4 phi0b] - 
 
                      2
>         16 curvb d0a  Cos[2 phi0a - 3 phi0b] + 
 
                            3
>         96 curva curvb d0a  Cos[2 phi0a - 3 phi0b] - 
 
>         8 d0b Cos[2 phi0a - 3 phi0b] - 
 
>         16 curva d0a d0b Cos[2 phi0a - 3 phi0b] - 
 
                     2
>         8 curvb d0b  Cos[2 phi0a - 3 phi0b] + 
 
                                 2
>         272 curva curvb d0a d0b  Cos[2 phi0a - 3 phi0b] - 
 
                     2
>         8 curvb d0a  Cos[4 phi0a - 3 phi0b] + 
 
                            3
>         16 curva curvb d0a  Cos[4 phi0a - 3 phi0b] + 
 
>         2 d0b Cos[4 phi0a - 3 phi0b] - 
 
>         8 curva d0a d0b Cos[4 phi0a - 3 phi0b] - 
 
                      2
>         10 curvb d0b  Cos[4 phi0a - 3 phi0b] + 
 
                                2
>         40 curva curvb d0a d0b  Cos[4 phi0a - 3 phi0b] - 
 
                                                   2
>         2 d0a Cos[phi0a - 2 phi0b] - 10 curva d0a  Cos[phi0a - 2 phi0b] + 
 
>         8 curvb d0a d0b Cos[phi0a - 2 phi0b] - 
 
                             2
>         680 curva curvb d0a  d0b Cos[phi0a - 2 phi0b] - 
 
                      2
>         12 curva d0b  Cos[phi0a - 2 phi0b] - 
 
                             3
>         216 curva curvb d0b  Cos[phi0a - 2 phi0b] + 
 
>         3 d0a Cos[3 phi0a - 2 phi0b] + 
 
                     2
>         9 curva d0a  Cos[3 phi0a - 2 phi0b] + 
 
>         24 curvb d0a d0b Cos[3 phi0a - 2 phi0b] - 
 
                             2
>         216 curva curvb d0a  d0b Cos[3 phi0a - 2 phi0b] + 
 
                      2
>         12 curva d0b  Cos[3 phi0a - 2 phi0b] - 
 
                            3
>         72 curva curvb d0b  Cos[3 phi0a - 2 phi0b] + 
 
                             3
>         192 curva curvb d0a  Cos[2 phi0a - phi0b] - 
 
>         8 d0b Cos[2 phi0a - phi0b] - 
 
>         16 curva d0a d0b Cos[2 phi0a - phi0b] + 
 
                     2
>         8 curvb d0b  Cos[2 phi0a - phi0b] + 
 
                                 2
>         592 curva curvb d0a d0b  Cos[2 phi0a - phi0b] + 
 
                      2                                 3
>         24 curvb d0a  Cos[phi0b] + 336 curva curvb d0a  Cos[phi0b] + 
 
>         12 d0b Cos[phi0b] + 48 curva d0a d0b Cos[phi0b] + 
 
                      2                                      2
>         12 curvb d0b  Cos[phi0b] + 1008 curva curvb d0a d0b  Cos[phi0b]) 
 
                          6
>       Csc[phi0a - phi0b] ) / 32

dxsol1dphi0b = Simplify[ D[xsol1, phi0b], Trig -> True ]

                                                   2
Out[11]= ((-12 (d0a + 4 curvb d0a d0b + 2 curva d0b  (1 + 14 curvb d0b) + 
 
               2
>           d0a  (curva + 84 curva curvb d0b)) Cos[phi0a] + 
 
>        (-1 + 4 curva d0a) d0b (-1 + curvb d0b) Cos[4 phi0a - 5 phi0b] + 
 
                                               2
>        d0b Cos[6 phi0a - 5 phi0b] - curvb d0b  Cos[6 phi0a - 5 phi0b] - 
 
>        2 d0a Cos[3 phi0a - 4 phi0b] + 
 
                     2
>        10 curva d0a  Cos[3 phi0a - 4 phi0b] + 
 
>        8 curvb d0a d0b Cos[3 phi0a - 4 phi0b] - 
 
                           2
>        40 curva curvb d0a  d0b Cos[3 phi0a - 4 phi0b] + 
 
                    2
>        8 curva d0b  Cos[3 phi0a - 4 phi0b] - 
 
                           3
>        16 curva curvb d0b  Cos[3 phi0a - 4 phi0b] - 
 
                                                   2
>        2 d0a Cos[5 phi0a - 4 phi0b] + 2 curva d0a  Cos[5 phi0a - 4 phi0b] + 
 
>        8 curvb d0a d0b Cos[5 phi0a - 4 phi0b] - 
 
                          2
>        8 curva curvb d0a  d0b Cos[5 phi0a - 4 phi0b] - 
 
                     2
>        12 curvb d0a  Cos[2 phi0a - 3 phi0b] + 
 
                           3
>        72 curva curvb d0a  Cos[2 phi0a - 3 phi0b] - 
 
>        3 d0b Cos[2 phi0a - 3 phi0b] - 
 
>        24 curva d0a d0b Cos[2 phi0a - 3 phi0b] - 
 
                    2
>        9 curvb d0b  Cos[2 phi0a - 3 phi0b] + 
 
                                2
>        216 curva curvb d0a d0b  Cos[2 phi0a - 3 phi0b] - 
 
                     2
>        12 curvb d0a  Cos[4 phi0a - 3 phi0b] + 
 
                           3
>        24 curva curvb d0a  Cos[4 phi0a - 3 phi0b] - 
 
>        3 d0b Cos[4 phi0a - 3 phi0b] - 
 
>        12 curva d0a d0b Cos[4 phi0a - 3 phi0b] - 
 
                    2
>        9 curvb d0b  Cos[4 phi0a - 3 phi0b] + 
 
                               2
>        60 curva curvb d0a d0b  Cos[4 phi0a - 3 phi0b] + 
 
                                                 2
>        8 d0a Cos[phi0a - 2 phi0b] - 8 curva d0a  Cos[phi0a - 2 phi0b] + 
 
>        16 curvb d0a d0b Cos[phi0a - 2 phi0b] - 
 
                            2
>        592 curva curvb d0a  d0b Cos[phi0a - 2 phi0b] - 
 
                            3
>        192 curva curvb d0b  Cos[phi0a - 2 phi0b] + 
 
                                                   2
>        8 d0a Cos[3 phi0a - 2 phi0b] + 8 curva d0a  Cos[3 phi0a - 2 phi0b] + 
 
>        16 curvb d0a d0b Cos[3 phi0a - 2 phi0b] - 
 
                            2
>        272 curva curvb d0a  d0b Cos[3 phi0a - 2 phi0b] + 
 
                     2
>        16 curva d0b  Cos[3 phi0a - 2 phi0b] - 
 
                           3
>        96 curva curvb d0b  Cos[3 phi0a - 2 phi0b] + 
 
                     2
>        12 curvb d0a  Cos[2 phi0a - phi0b] + 
 
                            3
>        216 curva curvb d0a  Cos[2 phi0a - phi0b] + 
 
>        2 d0b Cos[2 phi0a - phi0b] - 8 curva d0a d0b Cos[2 phi0a - phi0b] + 
 
                     2
>        10 curvb d0b  Cos[2 phi0a - phi0b] + 
 
                                2
>        680 curva curvb d0a d0b  Cos[2 phi0a - phi0b] + 
 
                     2                                 3
>        12 curvb d0a  Cos[phi0b] + 328 curva curvb d0a  Cos[phi0b] + 
 
>        2 d0b Cos[phi0b] + 48 curva d0a d0b Cos[phi0b] + 
 
                     2                                     2
>        10 curvb d0b  Cos[phi0b] + 960 curva curvb d0a d0b  Cos[phi0b]) 
 
                         6
>      Csc[phi0a - phi0b] ) / 32

dxsol1dcurva = Simplify[ D[xsol1, curva], Trig -> True ]

Out[12]= ((-d0b + d0a Cos[phi0a - phi0b]) 
 
>      (-(d0a (1 + 40 curvb d0b) Cos[phi0a]) + d0a Cos[3 phi0a - 4 phi0b] - 
 
                                                   2
>        2 d0b Cos[2 phi0a - 3 phi0b] + 4 curvb d0b  Cos[2 phi0a - 3 phi0b] - 
 
>        d0a Cos[phi0a - 2 phi0b] - 20 curvb d0a d0b Cos[phi0a - 2 phi0b] + 
 
>        d0a Cos[3 phi0a - 2 phi0b] - 
 
>        4 curvb d0a d0b Cos[3 phi0a - 2 phi0b] + 
 
                    2
>        8 curvb d0a  Cos[2 phi0a - phi0b] - 2 d0b Cos[2 phi0a - phi0b] + 
 
                     2                                    2
>        12 curvb d0b  Cos[2 phi0a - phi0b] + 24 curvb d0a  Cos[phi0b] + 
 
                                        2                               5
>        4 d0b Cos[phi0b] + 16 curvb d0b  Cos[phi0b]) Csc[phi0a - phi0b] ) / 8

dxsol1dcurvb = Simplify[ D[xsol1, curvb], Trig -> True ]

Out[13]= ((d0a - d0b Cos[phi0a - phi0b]) 
 
                            2              2
>      (4 (d0a + 4 curva d0a  + 6 curva d0b ) Cos[phi0a] + 
 
>        (d0b - 4 curva d0a d0b) Cos[2 phi0a - 3 phi0b] + 
 
>        d0b Cos[4 phi0a - 3 phi0b] - 2 d0a Cos[phi0a - 2 phi0b] + 
 
                     2
>        12 curva d0a  Cos[phi0a - 2 phi0b] + 
 
                    2
>        8 curva d0b  Cos[phi0a - 2 phi0b] - 2 d0a Cos[3 phi0a - 2 phi0b] + 
 
                    2
>        4 curva d0a  Cos[3 phi0a - 2 phi0b] - d0b Cos[2 phi0a - phi0b] - 
 
>        20 curva d0a d0b Cos[2 phi0a - phi0b] - d0b Cos[phi0b] - 
 
                                                        5
>        40 curva d0a d0b Cos[phi0b]) Csc[phi0a - phi0b] ) / 8

dxsol2dd0a = Simplify[ D[xsol2, d0a], Trig -> True ]

                      2
Out[14]= ((-2 (8 curvb  d0a + curva 
 
                                      2        2         2
>            (5 + 12 curvb d0b + curvb  (48 d0a  + 54 d0b ))) Cos[phi0a] + 
 
>        curva (1 + 2 curvb d0b) Cos[7 phi0a - 6 phi0b] + 
 
>        curvb Cos[6 phi0a - 5 phi0b] - 
 
>        2 curva curvb d0a Cos[6 phi0a - 5 phi0b] - 
 
>        curva Cos[3 phi0a - 4 phi0b] + 
 
>        2 curva curvb d0b Cos[3 phi0a - 4 phi0b] - 
 
                      2    2
>        4 curva curvb  d0b  Cos[3 phi0a - 4 phi0b] - 
 
>        5 curva Cos[5 phi0a - 4 phi0b] - 
 
>        10 curva curvb d0b Cos[5 phi0a - 4 phi0b] + 
 
>        curvb Cos[2 phi0a - 3 phi0b] - 
 
>        10 curva curvb d0a Cos[2 phi0a - 3 phi0b] - 
 
                2
>        4 curvb  d0b Cos[2 phi0a - 3 phi0b] + 
 
                       2
>        40 curva curvb  d0a d0b Cos[2 phi0a - 3 phi0b] - 
 
>        4 curvb Cos[4 phi0a - 3 phi0b] + 
 
>        8 curva curvb d0a Cos[4 phi0a - 3 phi0b] - 
 
                2
>        4 curvb  d0b Cos[4 phi0a - 3 phi0b] + 
 
                      2
>        8 curva curvb  d0a d0b Cos[4 phi0a - 3 phi0b] + 
 
                                               2
>        5 curva Cos[phi0a - 2 phi0b] + 8 curvb  d0a Cos[phi0a - 2 phi0b] - 
 
                       2    2
>        72 curva curvb  d0a  Cos[phi0a - 2 phi0b] + 
 
>        6 curva curvb d0b Cos[phi0a - 2 phi0b] - 
 
                       2    2
>        60 curva curvb  d0b  Cos[phi0a - 2 phi0b] + 
 
>        10 curva Cos[3 phi0a - 2 phi0b] + 
 
                2
>        8 curvb  d0a Cos[3 phi0a - 2 phi0b] - 
 
                       2    2
>        24 curva curvb  d0a  Cos[3 phi0a - 2 phi0b] + 
 
>        24 curva curvb d0b Cos[3 phi0a - 2 phi0b] - 
 
                       2    2
>        20 curva curvb  d0b  Cos[3 phi0a - 2 phi0b] + 
 
>        6 curvb Cos[2 phi0a - phi0b] - 
 
>        20 curva curvb d0a Cos[2 phi0a - phi0b] + 
 
                2
>        4 curvb  d0b Cos[2 phi0a - phi0b] + 
 
                        2
>        120 curva curvb  d0a d0b Cos[2 phi0a - phi0b] - 4 curvb Cos[phi0b] + 
 
                                                2
>        24 curva curvb d0a Cos[phi0b] + 4 curvb  d0b Cos[phi0b] + 
 
                        2                                       5
>        216 curva curvb  d0a d0b Cos[phi0b]) Csc[phi0a - phi0b] ) / 
 
>    (16 curvb)

dxsol2dd0b = Simplify[ D[xsol2, d0b], Trig -> True ]

Out[15]= ((-8 curvb (-1 + curvb d0b + 6 curva (d0a + 9 curvb d0a d0b)) 
 
>         Cos[phi0a] - 2 curva (1 + 2 curvb d0b) Cos[8 phi0a - 7 phi0b] - 
 
>        curvb Cos[5 phi0a - 6 phi0b] - curvb Cos[7 phi0a - 6 phi0b] + 
 
>        4 curva curvb d0a Cos[7 phi0a - 6 phi0b] + 
 
>        10 curva Cos[6 phi0a - 5 phi0b] + 
 
>        20 curva curvb d0b Cos[6 phi0a - 5 phi0b] + 
 
>        4 curvb Cos[3 phi0a - 4 phi0b] + 
 
>        4 curva curvb d0a Cos[3 phi0a - 4 phi0b] + 
 
                2
>        4 curvb  d0b Cos[3 phi0a - 4 phi0b] - 
 
                       2
>        16 curva curvb  d0a d0b Cos[3 phi0a - 4 phi0b] + 
 
>        4 curvb Cos[5 phi0a - 4 phi0b] - 
 
>        20 curva curvb d0a Cos[5 phi0a - 4 phi0b] + 
 
                2
>        4 curvb  d0b Cos[5 phi0a - 4 phi0b] + 
 
>        2 curva Cos[2 phi0a - 3 phi0b] - 
 
                2
>        8 curvb  d0a Cos[2 phi0a - 3 phi0b] + 
 
                       2    2
>        40 curva curvb  d0a  Cos[2 phi0a - 3 phi0b] - 
 
>        12 curva curvb d0b Cos[2 phi0a - 3 phi0b] + 
 
                       2    2
>        48 curva curvb  d0b  Cos[2 phi0a - 3 phi0b] - 
 
>        20 curva Cos[4 phi0a - 3 phi0b] - 
 
                2
>        8 curvb  d0a Cos[4 phi0a - 3 phi0b] + 
 
                      2    2
>        8 curva curvb  d0a  Cos[4 phi0a - 3 phi0b] - 
 
>        40 curva curvb d0b Cos[4 phi0a - 3 phi0b] - 
 
>        7 curvb Cos[phi0a - 2 phi0b] + 
 
>        12 curva curvb d0a Cos[phi0a - 2 phi0b] - 
 
                        2
>        240 curva curvb  d0a d0b Cos[phi0a - 2 phi0b] - 
 
>        7 curvb Cos[3 phi0a - 2 phi0b] + 
 
>        48 curva curvb d0a Cos[3 phi0a - 2 phi0b] - 
 
                       2
>        80 curva curvb  d0a d0b Cos[3 phi0a - 2 phi0b] + 
 
                                                2
>        20 curva Cos[2 phi0a - phi0b] + 8 curvb  d0a Cos[2 phi0a - phi0b] + 
 
                        2    2
>        120 curva curvb  d0a  Cos[2 phi0a - phi0b] + 
 
>        24 curva curvb d0b Cos[2 phi0a - phi0b] + 
 
                        2    2
>        144 curva curvb  d0b  Cos[2 phi0a - phi0b] - 10 curva Cos[phi0b] + 
 
                2                                 2    2
>        8 curvb  d0a Cos[phi0b] + 216 curva curvb  d0a  Cos[phi0b] + 
 
                                                        2    2
>        12 curva curvb d0b Cos[phi0b] + 192 curva curvb  d0b  Cos[phi0b]) 
 
                         5
>      Csc[phi0a - phi0b] ) / (32 curvb)

dxsol2dphi0a = Simplify[ D[xsol2, phi0a], Trig -> True ]

                     2
Out[16]= ((-((8 curvb  d0a (11 + 24 curvb d0b) + 
 
                                               2         2          2
>             curva (65 + 180 curvb d0b + curvb  (-40 d0a  + 228 d0b ) + 
 
                         3         2             3
>                32 curvb  (120 d0a  d0b + 41 d0b ))) Cos[phi0a]) - 
 
                                  2
>        3 curva (1 + 2 curvb d0b)  Cos[9 phi0a - 8 phi0b] - 
 
>        2 curvb Cos[8 phi0a - 7 phi0b] + 
 
>        8 curva curvb d0a Cos[8 phi0a - 7 phi0b] - 
 
                2
>        4 curvb  d0b Cos[8 phi0a - 7 phi0b] + 
 
                       2
>        16 curva curvb  d0a d0b Cos[8 phi0a - 7 phi0b] + 
 
>        curva Cos[5 phi0a - 6 phi0b] + 19 curva Cos[7 phi0a - 6 phi0b] + 
 
                2
>        4 curvb  d0a Cos[7 phi0a - 6 phi0b] - 
 
                      2    2
>        4 curva curvb  d0a  Cos[7 phi0a - 6 phi0b] + 
 
>        72 curva curvb d0b Cos[7 phi0a - 6 phi0b] + 
 
                       2    2
>        72 curva curvb  d0b  Cos[7 phi0a - 6 phi0b] - 
 
>        2 curvb Cos[4 phi0a - 5 phi0b] + 
 
>        8 curva curvb d0a Cos[4 phi0a - 5 phi0b] + 
 
                2
>        4 curvb  d0b Cos[4 phi0a - 5 phi0b] - 
 
                       2
>        16 curva curvb  d0a d0b Cos[4 phi0a - 5 phi0b] - 
 
                3    2
>        8 curvb  d0b  Cos[4 phi0a - 5 phi0b] + 
 
                       3        2
>        32 curva curvb  d0a d0b  Cos[4 phi0a - 5 phi0b] + 
 
>        12 curvb Cos[6 phi0a - 5 phi0b] - 
 
>        48 curva curvb d0a Cos[6 phi0a - 5 phi0b] + 
 
                 2
>        24 curvb  d0b Cos[6 phi0a - 5 phi0b] - 
 
                       2
>        96 curva curvb  d0a d0b Cos[6 phi0a - 5 phi0b] - 
 
>        9 curva Cos[3 phi0a - 4 phi0b] - 
 
                 2
>        12 curvb  d0a Cos[3 phi0a - 4 phi0b] + 
 
                       2    2
>        60 curva curvb  d0a  Cos[3 phi0a - 4 phi0b] - 
 
>        12 curva curvb d0b Cos[3 phi0a - 4 phi0b] + 
 
                 3
>        48 curvb  d0a d0b Cos[3 phi0a - 4 phi0b] - 
 
                        3    2
>        240 curva curvb  d0a  d0b Cos[3 phi0a - 4 phi0b] + 
 
                       2    2
>        36 curva curvb  d0b  Cos[3 phi0a - 4 phi0b] - 
 
                       3    3
>        96 curva curvb  d0b  Cos[3 phi0a - 4 phi0b] - 
 
>        51 curva Cos[5 phi0a - 4 phi0b] - 
 
                 2
>        28 curvb  d0a Cos[5 phi0a - 4 phi0b] + 
 
                       2    2
>        28 curva curvb  d0a  Cos[5 phi0a - 4 phi0b] - 
 
>        180 curva curvb d0b Cos[5 phi0a - 4 phi0b] + 
 
                 3
>        16 curvb  d0a d0b Cos[5 phi0a - 4 phi0b] - 
 
                       3    2
>        16 curva curvb  d0a  d0b Cos[5 phi0a - 4 phi0b] - 
 
                        2    2
>        180 curva curvb  d0b  Cos[5 phi0a - 4 phi0b] + 
 
>        12 curvb Cos[2 phi0a - 3 phi0b] - 
 
>        48 curva curvb d0a Cos[2 phi0a - 3 phi0b] - 
 
                 3    2
>        64 curvb  d0a  Cos[2 phi0a - 3 phi0b] + 
 
                        3    3
>        384 curva curvb  d0a  Cos[2 phi0a - 3 phi0b] - 
 
                2
>        8 curvb  d0b Cos[2 phi0a - 3 phi0b] - 
 
                        2
>        160 curva curvb  d0a d0b Cos[2 phi0a - 3 phi0b] - 
 
                 3    2
>        32 curvb  d0b  Cos[2 phi0a - 3 phi0b] + 
 
                         3        2
>        1088 curva curvb  d0a d0b  Cos[2 phi0a - 3 phi0b] - 
 
>        30 curvb Cos[4 phi0a - 3 phi0b] + 
 
>        120 curva curvb d0a Cos[4 phi0a - 3 phi0b] - 
 
                 3    2
>        32 curvb  d0a  Cos[4 phi0a - 3 phi0b] + 
 
                       3    3
>        64 curva curvb  d0a  Cos[4 phi0a - 3 phi0b] - 
 
                 2
>        52 curvb  d0b Cos[4 phi0a - 3 phi0b] + 
 
                        2
>        208 curva curvb  d0a d0b Cos[4 phi0a - 3 phi0b] - 
 
                 3    2
>        40 curvb  d0b  Cos[4 phi0a - 3 phi0b] + 
 
                        3        2
>        160 curva curvb  d0a d0b  Cos[4 phi0a - 3 phi0b] + 
 
                                                 2
>        33 curva Cos[phi0a - 2 phi0b] + 52 curvb  d0a Cos[phi0a - 2 phi0b] - 
 
                        2    2
>        100 curva curvb  d0a  Cos[phi0a - 2 phi0b] + 
 
>        72 curva curvb d0b Cos[phi0a - 2 phi0b] + 
 
                 3
>        32 curvb  d0a d0b Cos[phi0a - 2 phi0b] - 
 
                         3    2
>        2720 curva curvb  d0a  d0b Cos[phi0a - 2 phi0b] + 
 
                       2    2
>        24 curva curvb  d0b  Cos[phi0a - 2 phi0b] - 
 
                        3    3
>        864 curva curvb  d0b  Cos[phi0a - 2 phi0b] + 
 
>        75 curva Cos[3 phi0a - 2 phi0b] + 
 
                 2
>        72 curvb  d0a Cos[3 phi0a - 2 phi0b] - 
 
                       2    2
>        24 curva curvb  d0a  Cos[3 phi0a - 2 phi0b] + 
 
>        240 curva curvb d0b Cos[3 phi0a - 2 phi0b] + 
 
                 3
>        96 curvb  d0a d0b Cos[3 phi0a - 2 phi0b] - 
 
                        3    2
>        864 curva curvb  d0a  d0b Cos[3 phi0a - 2 phi0b] + 
 
                        2    2
>        288 curva curvb  d0b  Cos[3 phi0a - 2 phi0b] - 
 
                        3    3
>        288 curva curvb  d0b  Cos[3 phi0a - 2 phi0b] + 
 
>        40 curvb Cos[2 phi0a - phi0b] - 
 
>        160 curva curvb d0a Cos[2 phi0a - phi0b] + 
 
                        3    3
>        768 curva curvb  d0a  Cos[2 phi0a - phi0b] + 
 
                 2
>        48 curvb  d0b Cos[2 phi0a - phi0b] - 
 
                        2
>        384 curva curvb  d0a d0b Cos[2 phi0a - phi0b] + 
 
                 3    2
>        32 curvb  d0b  Cos[2 phi0a - phi0b] + 
 
                         3        2
>        2368 curva curvb  d0a d0b  Cos[2 phi0a - phi0b] - 
 
>        30 curvb Cos[phi0b] + 120 curva curvb d0a Cos[phi0b] + 
 
                 3    2                              3    3
>        96 curvb  d0a  Cos[phi0b] + 1344 curva curvb  d0a  Cos[phi0b] - 
 
                 2                                 2
>        12 curvb  d0b Cos[phi0b] + 432 curva curvb  d0a d0b Cos[phi0b] + 
 
                 3    2                              3        2
>        48 curvb  d0b  Cos[phi0b] + 4032 curva curvb  d0a d0b  Cos[phi0b]) 
 
                         6              2
>      Csc[phi0a - phi0b] ) / (128 curvb )

dxsol2dphi0b = Simplify[ D[xsol2, phi0b], Trig -> True ]

                     2
Out[17]= ((6 (8 curvb  d0a (1 + 4 curvb d0b) + 
 
                                             2       2        2
>           curva (5 + 20 curvb d0b + 4 curvb  (2 d0a  + 9 d0b ) + 
 
                        3       2          3
>              224 curvb  (3 d0a  d0b + d0b ))) Cos[phi0a] + 
 
                                  2
>        2 curva (1 + 2 curvb d0b)  Cos[9 phi0a - 8 phi0b] + 
 
                                               2
>        curvb Cos[6 phi0a - 7 phi0b] + 2 curvb  d0b Cos[6 phi0a - 7 phi0b] + 
 
>        curvb Cos[8 phi0a - 7 phi0b] - 
 
>        4 curva curvb d0a Cos[8 phi0a - 7 phi0b] + 
 
                2
>        2 curvb  d0b Cos[8 phi0a - 7 phi0b] - 
 
                      2
>        8 curva curvb  d0a d0b Cos[8 phi0a - 7 phi0b] - 
 
>        12 curva Cos[7 phi0a - 6 phi0b] - 
 
>        48 curva curvb d0b Cos[7 phi0a - 6 phi0b] - 
 
                       2    2
>        48 curva curvb  d0b  Cos[7 phi0a - 6 phi0b] - 
 
>        5 curvb Cos[4 phi0a - 5 phi0b] - 
 
>        4 curva curvb d0a Cos[4 phi0a - 5 phi0b] - 
 
                 2
>        14 curvb  d0b Cos[4 phi0a - 5 phi0b] + 
 
                      2
>        8 curva curvb  d0a d0b Cos[4 phi0a - 5 phi0b] + 
 
                3    2
>        4 curvb  d0b  Cos[4 phi0a - 5 phi0b] - 
 
                       3        2
>        16 curva curvb  d0a d0b  Cos[4 phi0a - 5 phi0b] - 
 
>        5 curvb Cos[6 phi0a - 5 phi0b] + 
 
>        24 curva curvb d0a Cos[6 phi0a - 5 phi0b] - 
 
                 2
>        14 curvb  d0b Cos[6 phi0a - 5 phi0b] + 
 
                       2
>        48 curva curvb  d0a d0b Cos[6 phi0a - 5 phi0b] + 
 
                3    2
>        4 curvb  d0b  Cos[6 phi0a - 5 phi0b] + 
 
>        2 curva Cos[3 phi0a - 4 phi0b] + 
 
                2
>        8 curvb  d0a Cos[3 phi0a - 4 phi0b] - 
 
                       2    2
>        40 curva curvb  d0a  Cos[3 phi0a - 4 phi0b] + 
 
>        8 curva curvb d0b Cos[3 phi0a - 4 phi0b] - 
 
                 3
>        32 curvb  d0a d0b Cos[3 phi0a - 4 phi0b] + 
 
                        3    2
>        160 curva curvb  d0a  d0b Cos[3 phi0a - 4 phi0b] - 
 
                       2    2
>        24 curva curvb  d0b  Cos[3 phi0a - 4 phi0b] + 
 
                       3    3
>        64 curva curvb  d0b  Cos[3 phi0a - 4 phi0b] + 
 
>        30 curva Cos[5 phi0a - 4 phi0b] + 
 
                2
>        8 curvb  d0a Cos[5 phi0a - 4 phi0b] - 
 
                      2    2
>        8 curva curvb  d0a  Cos[5 phi0a - 4 phi0b] + 
 
>        120 curva curvb d0b Cos[5 phi0a - 4 phi0b] - 
 
                 3
>        32 curvb  d0a d0b Cos[5 phi0a - 4 phi0b] + 
 
                       3    2
>        32 curva curvb  d0a  d0b Cos[5 phi0a - 4 phi0b] + 
 
                        2    2
>        120 curva curvb  d0b  Cos[5 phi0a - 4 phi0b] + 
 
>        9 curvb Cos[2 phi0a - 3 phi0b] + 
 
>        24 curva curvb d0a Cos[2 phi0a - 3 phi0b] + 
 
                 3    2
>        48 curvb  d0a  Cos[2 phi0a - 3 phi0b] - 
 
                        3    3
>        288 curva curvb  d0a  Cos[2 phi0a - 3 phi0b] + 
 
                 2
>        30 curvb  d0b Cos[2 phi0a - 3 phi0b] + 
 
                        2
>        144 curva curvb  d0a d0b Cos[2 phi0a - 3 phi0b] + 
 
                 3    2
>        36 curvb  d0b  Cos[2 phi0a - 3 phi0b] - 
 
                        3        2
>        864 curva curvb  d0a d0b  Cos[2 phi0a - 3 phi0b] + 
 
>        9 curvb Cos[4 phi0a - 3 phi0b] - 
 
>        60 curva curvb d0a Cos[4 phi0a - 3 phi0b] + 
 
                 3    2
>        48 curvb  d0a  Cos[4 phi0a - 3 phi0b] - 
 
                       3    3
>        96 curva curvb  d0a  Cos[4 phi0a - 3 phi0b] + 
 
                 2
>        30 curvb  d0b Cos[4 phi0a - 3 phi0b] - 
 
                       2
>        72 curva curvb  d0a d0b Cos[4 phi0a - 3 phi0b] + 
 
                 3    2
>        36 curvb  d0b  Cos[4 phi0a - 3 phi0b] - 
 
                        3        2
>        240 curva curvb  d0a d0b  Cos[4 phi0a - 3 phi0b] - 
 
                                                 2
>        12 curva Cos[phi0a - 2 phi0b] - 32 curvb  d0a Cos[phi0a - 2 phi0b] + 
 
                       2    2
>        32 curva curvb  d0a  Cos[phi0a - 2 phi0b] - 
 
>        48 curva curvb d0b Cos[phi0a - 2 phi0b] - 
 
                 3
>        64 curvb  d0a d0b Cos[phi0a - 2 phi0b] + 
 
                         3    2
>        2368 curva curvb  d0a  d0b Cos[phi0a - 2 phi0b] - 
 
                       2    2
>        48 curva curvb  d0b  Cos[phi0a - 2 phi0b] + 
 
                        3    3
>        768 curva curvb  d0b  Cos[phi0a - 2 phi0b] - 
 
>        40 curva Cos[3 phi0a - 2 phi0b] - 
 
                 2
>        32 curvb  d0a Cos[3 phi0a - 2 phi0b] - 
 
                       2    2
>        32 curva curvb  d0a  Cos[3 phi0a - 2 phi0b] - 
 
>        160 curva curvb d0b Cos[3 phi0a - 2 phi0b] - 
 
                 3
>        64 curvb  d0a d0b Cos[3 phi0a - 2 phi0b] + 
 
                         3    2
>        1088 curva curvb  d0a  d0b Cos[3 phi0a - 2 phi0b] - 
 
                        2    2
>        224 curva curvb  d0b  Cos[3 phi0a - 2 phi0b] + 
 
                        3    3
>        384 curva curvb  d0b  Cos[3 phi0a - 2 phi0b] - 
 
>        5 curvb Cos[2 phi0a - phi0b] + 
 
>        80 curva curvb d0a Cos[2 phi0a - phi0b] - 
 
                 3    2
>        48 curvb  d0a  Cos[2 phi0a - phi0b] - 
 
                        3    3
>        864 curva curvb  d0a  Cos[2 phi0a - phi0b] - 
 
                 2
>        18 curvb  d0b Cos[2 phi0a - phi0b] + 
 
                        2
>        192 curva curvb  d0a d0b Cos[2 phi0a - phi0b] - 
 
                 3    2
>        40 curvb  d0b  Cos[2 phi0a - phi0b] - 
 
                         3        2
>        2720 curva curvb  d0a d0b  Cos[2 phi0a - phi0b] - 
 
>        5 curvb Cos[phi0b] - 60 curva curvb d0a Cos[phi0b] - 
 
                 3    2                              3    3
>        48 curvb  d0a  Cos[phi0b] - 1312 curva curvb  d0a  Cos[phi0b] - 
 
                 2                                 2
>        18 curvb  d0b Cos[phi0b] - 312 curva curvb  d0a d0b Cos[phi0b] - 
 
                 3    2                              3        2
>        40 curvb  d0b  Cos[phi0b] - 3840 curva curvb  d0a d0b  Cos[phi0b]) 
 
                         6              2
>      Csc[phi0a - phi0b] ) / (128 curvb )

dxsol2dcurva = Simplify[ D[xsol2, curva], Trig -> True ]

                                                 2        2         2
Out[18]= -((8 curvb d0a (5 + 12 curvb d0b + curvb  (16 d0a  + 54 d0b )) 
 
                                         2
>          Cos[phi0a] + (1 + 2 curvb d0b)  Cos[8 phi0a - 7 phi0b] - 
 
>         4 curvb d0a Cos[7 phi0a - 6 phi0b] - 
 
                 2
>         8 curvb  d0a d0b Cos[7 phi0a - 6 phi0b] + Cos[4 phi0a - 5 phi0b] - 
 
                                            2    2
>         6 Cos[6 phi0a - 5 phi0b] + 4 curvb  d0a  Cos[6 phi0a - 5 phi0b] - 
 
>         20 curvb d0b Cos[6 phi0a - 5 phi0b] - 
 
                  2    2
>         20 curvb  d0b  Cos[6 phi0a - 5 phi0b] + 
 
>         4 curvb d0a Cos[3 phi0a - 4 phi0b] - 
 
                 2
>         8 curvb  d0a d0b Cos[3 phi0a - 4 phi0b] + 
 
                  3        2
>         16 curvb  d0a d0b  Cos[3 phi0a - 4 phi0b] + 
 
>         20 curvb d0a Cos[5 phi0a - 4 phi0b] + 
 
                  2
>         40 curvb  d0a d0b Cos[5 phi0a - 4 phi0b] - 
 
                                             2    2
>         6 Cos[2 phi0a - 3 phi0b] + 20 curvb  d0a  Cos[2 phi0a - 3 phi0b] - 
 
>         4 curvb d0b Cos[2 phi0a - 3 phi0b] - 
 
                  3    2
>         80 curvb  d0a  d0b Cos[2 phi0a - 3 phi0b] + 
 
                  2    2
>         12 curvb  d0b  Cos[2 phi0a - 3 phi0b] - 
 
                  3    3
>         32 curvb  d0b  Cos[2 phi0a - 3 phi0b] + 15 Cos[4 phi0a - 3 phi0b] - 
 
                  2    2
>         16 curvb  d0a  Cos[4 phi0a - 3 phi0b] + 
 
>         40 curvb d0b Cos[4 phi0a - 3 phi0b] - 
 
                  3    2
>         16 curvb  d0a  d0b Cos[4 phi0a - 3 phi0b] + 
 
                  2    2
>         40 curvb  d0b  Cos[4 phi0a - 3 phi0b] - 
 
>         20 curvb d0a Cos[phi0a - 2 phi0b] + 
 
                  3    3
>         96 curvb  d0a  Cos[phi0a - 2 phi0b] - 
 
                  2
>         24 curvb  d0a d0b Cos[phi0a - 2 phi0b] + 
 
                   3        2
>         240 curvb  d0a d0b  Cos[phi0a - 2 phi0b] - 
 
>         40 curvb d0a Cos[3 phi0a - 2 phi0b] + 
 
                  3    3
>         32 curvb  d0a  Cos[3 phi0a - 2 phi0b] - 
 
                  2
>         96 curvb  d0a d0b Cos[3 phi0a - 2 phi0b] + 
 
                  3        2
>         80 curvb  d0a d0b  Cos[3 phi0a - 2 phi0b] - 
 
                                            2    2
>         20 Cos[2 phi0a - phi0b] + 40 curvb  d0a  Cos[2 phi0a - phi0b] - 
 
>         40 curvb d0b Cos[2 phi0a - phi0b] - 
 
                   3    2
>         240 curvb  d0a  d0b Cos[2 phi0a - phi0b] - 
 
                  2    2
>         24 curvb  d0b  Cos[2 phi0a - phi0b] - 
 
                  3    3
>         96 curvb  d0b  Cos[2 phi0a - phi0b] + 15 Cos[phi0b] - 
 
                  2    2
>         48 curvb  d0a  Cos[phi0b] + 20 curvb d0b Cos[phi0b] - 
 
                   3    2                          2    2
>         432 curvb  d0a  d0b Cos[phi0b] - 12 curvb  d0b  Cos[phi0b] - 
 
                   3    3                               5             2
>         128 curvb  d0b  Cos[phi0b]) Csc[phi0a - phi0b] ) / (64 curvb )

dxsol2dcurvb = Simplify[ D[xsol2, curvb], Trig -> True ]

                                2       2      2
Out[19]= ((-4 curvb (5 + 2 curvb  (4 d0a  + d0b ) + 
 
                                   2        2         2
>           2 curva d0a (-5 + curvb  (16 d0a  + 54 d0b ))) Cos[phi0a] + 
 
>        2 curva (1 + 2 curvb d0b) Cos[8 phi0a - 7 phi0b] + 
 
>        curvb Cos[5 phi0a - 6 phi0b] + curvb Cos[7 phi0a - 6 phi0b] - 
 
>        4 curva curvb d0a Cos[7 phi0a - 6 phi0b] + 
 
>        2 curva Cos[4 phi0a - 5 phi0b] - 12 curva Cos[6 phi0a - 5 phi0b] - 
 
>        20 curva curvb d0b Cos[6 phi0a - 5 phi0b] - 
 
>        6 curvb Cos[3 phi0a - 4 phi0b] + 
 
>        4 curva curvb d0a Cos[3 phi0a - 4 phi0b] + 
 
                3    2
>        4 curvb  d0b  Cos[3 phi0a - 4 phi0b] - 
 
                       3        2
>        16 curva curvb  d0a d0b  Cos[3 phi0a - 4 phi0b] - 
 
>        6 curvb Cos[5 phi0a - 4 phi0b] + 
 
>        20 curva curvb d0a Cos[5 phi0a - 4 phi0b] + 
 
                3    2
>        4 curvb  d0b  Cos[5 phi0a - 4 phi0b] - 
 
>        12 curva Cos[2 phi0a - 3 phi0b] - 
 
>        4 curva curvb d0b Cos[2 phi0a - 3 phi0b] - 
 
                 3
>        16 curvb  d0a d0b Cos[2 phi0a - 3 phi0b] + 
 
                       3    2
>        80 curva curvb  d0a  d0b Cos[2 phi0a - 3 phi0b] + 
 
                       3    3
>        32 curva curvb  d0b  Cos[2 phi0a - 3 phi0b] + 
 
>        30 curva Cos[4 phi0a - 3 phi0b] + 
 
>        40 curva curvb d0b Cos[4 phi0a - 3 phi0b] - 
 
                 3
>        16 curvb  d0a d0b Cos[4 phi0a - 3 phi0b] + 
 
                       3    2
>        16 curva curvb  d0a  d0b Cos[4 phi0a - 3 phi0b] + 
 
>        15 curvb Cos[phi0a - 2 phi0b] - 
 
>        20 curva curvb d0a Cos[phi0a - 2 phi0b] + 
 
                 3    2
>        16 curvb  d0a  Cos[phi0a - 2 phi0b] - 
 
                       3    3
>        96 curva curvb  d0a  Cos[phi0a - 2 phi0b] - 
 
                        3        2
>        240 curva curvb  d0a d0b  Cos[phi0a - 2 phi0b] + 
 
>        15 curvb Cos[3 phi0a - 2 phi0b] - 
 
>        40 curva curvb d0a Cos[3 phi0a - 2 phi0b] + 
 
                 3    2
>        16 curvb  d0a  Cos[3 phi0a - 2 phi0b] - 
 
                       3    3
>        32 curva curvb  d0a  Cos[3 phi0a - 2 phi0b] - 
 
                       3        2
>        80 curva curvb  d0a d0b  Cos[3 phi0a - 2 phi0b] - 
 
>        40 curva Cos[2 phi0a - phi0b] - 
 
>        40 curva curvb d0b Cos[2 phi0a - phi0b] + 
 
                 3
>        16 curvb  d0a d0b Cos[2 phi0a - phi0b] + 
 
                        3    2
>        240 curva curvb  d0a  d0b Cos[2 phi0a - phi0b] + 
 
                       3    3
>        96 curva curvb  d0b  Cos[2 phi0a - phi0b] + 30 curva Cos[phi0b] + 
 
                                                 3
>        20 curva curvb d0b Cos[phi0b] + 16 curvb  d0a d0b Cos[phi0b] + 
 
                        3    2
>        432 curva curvb  d0a  d0b Cos[phi0b] + 
 
                        3    3                               5             3
>        128 curva curvb  d0b  Cos[phi0b]) Csc[phi0a - phi0b] ) / (64 curvb )

dysol1dd0a = Simplify[ D[ysol1, d0a], Trig -> True ]

                             5
Out[20]= -(Csc[phi0a - phi0b]  (-4 
 
                                                   2               2
>          (curva d0b + curvb (4 d0a + 24 curva d0a  + 27 curva d0b )) 
 
>          Sin[phi0a] + (-1 + 2 curva d0a) Sin[4 phi0a - 5 phi0b] - 
 
>         4 curva d0b Sin[3 phi0a - 4 phi0b] + 
 
                           2
>         4 curva curvb d0b  Sin[3 phi0a - 4 phi0b] + 
 
>         4 Sin[2 phi0a - 3 phi0b] + 4 curvb d0b Sin[2 phi0a - 3 phi0b] - 
 
>         40 curva curvb d0a d0b Sin[2 phi0a - 3 phi0b] + 
 
>         Sin[4 phi0a - 3 phi0b] - 2 curva d0a Sin[4 phi0a - 3 phi0b] - 
 
>         4 curvb d0b Sin[4 phi0a - 3 phi0b] + 
 
>         8 curva curvb d0a d0b Sin[4 phi0a - 3 phi0b] - 
 
>         8 curvb d0a Sin[phi0a - 2 phi0b] + 
 
                            2
>         72 curva curvb d0a  Sin[phi0a - 2 phi0b] + 
 
>         4 curva d0b Sin[phi0a - 2 phi0b] + 
 
                            2
>         60 curva curvb d0b  Sin[phi0a - 2 phi0b] + 
 
>         8 curvb d0a Sin[3 phi0a - 2 phi0b] - 
 
                            2
>         24 curva curvb d0a  Sin[3 phi0a - 2 phi0b] + 
 
>         4 curva d0b Sin[3 phi0a - 2 phi0b] - 
 
                            2
>         20 curva curvb d0b  Sin[3 phi0a - 2 phi0b] - 
 
>         4 Sin[2 phi0a - phi0b] + 4 curvb d0b Sin[2 phi0a - phi0b] + 
 
>         120 curva curvb d0a d0b Sin[2 phi0a - phi0b] + 6 Sin[phi0b] + 
 
>         4 curva d0a Sin[phi0b] + 4 curvb d0b Sin[phi0b] + 
 
>         216 curva curvb d0a d0b Sin[phi0b])) / 16

dysol1dd0b = Simplify[ D[ysol1, d0b], Trig -> True ]

                             5
Out[21]= -(Csc[phi0a - phi0b]  (-2 
 
>          (3 + 2 curvb d0b + 2 curva (d0a + 54 curvb d0a d0b)) Sin[phi0a] + 
 
>         (-1 + 4 curva d0a) (-1 + 2 curvb d0b) Sin[3 phi0a - 4 phi0b] - 
 
>         Sin[5 phi0a - 4 phi0b] + 2 curvb d0b Sin[5 phi0a - 4 phi0b] + 
 
>         4 curvb d0a Sin[2 phi0a - 3 phi0b] - 
 
                            2
>         20 curva curvb d0a  Sin[2 phi0a - 3 phi0b] + 
 
>         8 curva d0b Sin[2 phi0a - 3 phi0b] - 
 
                            2
>         24 curva curvb d0b  Sin[2 phi0a - 3 phi0b] - 
 
>         4 curvb d0a Sin[4 phi0a - 3 phi0b] + 
 
                           2
>         4 curva curvb d0a  Sin[4 phi0a - 3 phi0b] - 
 
>         4 Sin[phi0a - 2 phi0b] + 4 curva d0a Sin[phi0a - 2 phi0b] + 
 
>         120 curva curvb d0a d0b Sin[phi0a - 2 phi0b] + 
 
>         4 Sin[3 phi0a - 2 phi0b] + 4 curva d0a Sin[3 phi0a - 2 phi0b] - 
 
>         40 curva curvb d0a d0b Sin[3 phi0a - 2 phi0b] + 
 
>         4 curvb d0a Sin[2 phi0a - phi0b] + 
 
                            2
>         60 curva curvb d0a  Sin[2 phi0a - phi0b] - 
 
>         8 curva d0b Sin[2 phi0a - phi0b] + 
 
                            2
>         72 curva curvb d0b  Sin[2 phi0a - phi0b] + 4 curvb d0a Sin[phi0b] + 
 
                             2
>         108 curva curvb d0a  Sin[phi0b] + 16 curva d0b Sin[phi0b] + 
 
                            2
>         96 curva curvb d0b  Sin[phi0b])) / 16

dysol1dphi0a = Simplify[ D[ysol1, phi0a], Trig -> True ]

                             6
Out[22]= -(Csc[phi0a - phi0b]  (-2 
 
                                                2
>          (d0a + 24 curvb d0a d0b + 2 curva d0b  (3 + 82 curvb d0b) + 
 
                  2
>            5 d0a  (curva + 96 curva curvb d0b)) Sin[phi0a] - 
 
>         d0a (-1 + curva d0a) Sin[5 phi0a - 6 phi0b] - 
 
>         2 d0b Sin[4 phi0a - 5 phi0b] + 
 
>         8 curva d0a d0b Sin[4 phi0a - 5 phi0b] + 
 
                     2
>         2 curvb d0b  Sin[4 phi0a - 5 phi0b] - 
 
                               2
>         8 curva curvb d0a d0b  Sin[4 phi0a - 5 phi0b] - 
 
>         3 d0a Sin[3 phi0a - 4 phi0b] - 
 
                     2
>         9 curva d0a  Sin[3 phi0a - 4 phi0b] - 
 
>         12 curvb d0a d0b Sin[3 phi0a - 4 phi0b] + 
 
                            2
>         60 curva curvb d0a  d0b Sin[3 phi0a - 4 phi0b] - 
 
                      2
>         12 curva d0b  Sin[3 phi0a - 4 phi0b] + 
 
                            3
>         24 curva curvb d0b  Sin[3 phi0a - 4 phi0b] - 
 
                                                2
>         d0a Sin[5 phi0a - 4 phi0b] + curva d0a  Sin[5 phi0a - 4 phi0b] + 
 
>         4 curvb d0a d0b Sin[5 phi0a - 4 phi0b] - 
 
                           2
>         4 curva curvb d0a  d0b Sin[5 phi0a - 4 phi0b] + 
 
                      2
>         16 curvb d0a  Sin[2 phi0a - 3 phi0b] - 
 
                            3
>         96 curva curvb d0a  Sin[2 phi0a - 3 phi0b] + 
 
>         8 d0b Sin[2 phi0a - 3 phi0b] + 
 
>         16 curva d0a d0b Sin[2 phi0a - 3 phi0b] + 
 
                     2
>         8 curvb d0b  Sin[2 phi0a - 3 phi0b] - 
 
                                 2
>         272 curva curvb d0a d0b  Sin[2 phi0a - 3 phi0b] - 
 
                     2
>         8 curvb d0a  Sin[4 phi0a - 3 phi0b] + 
 
                            3
>         16 curva curvb d0a  Sin[4 phi0a - 3 phi0b] + 
 
>         2 d0b Sin[4 phi0a - 3 phi0b] - 
 
>         8 curva d0a d0b Sin[4 phi0a - 3 phi0b] - 
 
                      2
>         10 curvb d0b  Sin[4 phi0a - 3 phi0b] + 
 
                                2
>         40 curva curvb d0a d0b  Sin[4 phi0a - 3 phi0b] + 
 
                                                   2
>         2 d0a Sin[phi0a - 2 phi0b] + 10 curva d0a  Sin[phi0a - 2 phi0b] - 
 
>         8 curvb d0a d0b Sin[phi0a - 2 phi0b] + 
 
                             2
>         680 curva curvb d0a  d0b Sin[phi0a - 2 phi0b] + 
 
                      2
>         12 curva d0b  Sin[phi0a - 2 phi0b] + 
 
                             3
>         216 curva curvb d0b  Sin[phi0a - 2 phi0b] + 
 
>         3 d0a Sin[3 phi0a - 2 phi0b] + 
 
                     2
>         9 curva d0a  Sin[3 phi0a - 2 phi0b] + 
 
>         24 curvb d0a d0b Sin[3 phi0a - 2 phi0b] - 
 
                             2
>         216 curva curvb d0a  d0b Sin[3 phi0a - 2 phi0b] + 
 
                      2
>         12 curva d0b  Sin[3 phi0a - 2 phi0b] - 
 
                            3
>         72 curva curvb d0b  Sin[3 phi0a - 2 phi0b] + 
 
                             3
>         192 curva curvb d0a  Sin[2 phi0a - phi0b] - 
 
>         8 d0b Sin[2 phi0a - phi0b] - 
 
>         16 curva d0a d0b Sin[2 phi0a - phi0b] + 
 
                     2
>         8 curvb d0b  Sin[2 phi0a - phi0b] + 
 
                                 2
>         592 curva curvb d0a d0b  Sin[2 phi0a - phi0b] + 
 
                      2                                 3
>         24 curvb d0a  Sin[phi0b] + 336 curva curvb d0a  Sin[phi0b] + 
 
>         12 d0b Sin[phi0b] + 48 curva d0a d0b Sin[phi0b] + 
 
                      2                                      2
>         12 curvb d0b  Sin[phi0b] + 1008 curva curvb d0a d0b  Sin[phi0b])) / 
 
>    32

dysol1dphi0b = Simplify[ D[ysol1, phi0b], Trig -> True ]

                            6
Out[23]= (Csc[phi0a - phi0b]  (-12 
 
                                              2
>         (d0a + 4 curvb d0a d0b + 2 curva d0b  (1 + 14 curvb d0b) + 
 
               2
>           d0a  (curva + 84 curva curvb d0b)) Sin[phi0a] - 
 
>        (-1 + 4 curva d0a) d0b (-1 + curvb d0b) Sin[4 phi0a - 5 phi0b] + 
 
                                               2
>        d0b Sin[6 phi0a - 5 phi0b] - curvb d0b  Sin[6 phi0a - 5 phi0b] + 
 
>        2 d0a Sin[3 phi0a - 4 phi0b] - 
 
                     2
>        10 curva d0a  Sin[3 phi0a - 4 phi0b] - 
 
>        8 curvb d0a d0b Sin[3 phi0a - 4 phi0b] + 
 
                           2
>        40 curva curvb d0a  d0b Sin[3 phi0a - 4 phi0b] - 
 
                    2
>        8 curva d0b  Sin[3 phi0a - 4 phi0b] + 
 
                           3
>        16 curva curvb d0b  Sin[3 phi0a - 4 phi0b] - 
 
                                                   2
>        2 d0a Sin[5 phi0a - 4 phi0b] + 2 curva d0a  Sin[5 phi0a - 4 phi0b] + 
 
>        8 curvb d0a d0b Sin[5 phi0a - 4 phi0b] - 
 
                          2
>        8 curva curvb d0a  d0b Sin[5 phi0a - 4 phi0b] + 
 
                     2
>        12 curvb d0a  Sin[2 phi0a - 3 phi0b] - 
 
                           3
>        72 curva curvb d0a  Sin[2 phi0a - 3 phi0b] + 
 
>        3 d0b Sin[2 phi0a - 3 phi0b] + 
 
>        24 curva d0a d0b Sin[2 phi0a - 3 phi0b] + 
 
                    2
>        9 curvb d0b  Sin[2 phi0a - 3 phi0b] - 
 
                                2
>        216 curva curvb d0a d0b  Sin[2 phi0a - 3 phi0b] - 
 
                     2
>        12 curvb d0a  Sin[4 phi0a - 3 phi0b] + 
 
                           3
>        24 curva curvb d0a  Sin[4 phi0a - 3 phi0b] - 
 
>        3 d0b Sin[4 phi0a - 3 phi0b] - 
 
>        12 curva d0a d0b Sin[4 phi0a - 3 phi0b] - 
 
                    2
>        9 curvb d0b  Sin[4 phi0a - 3 phi0b] + 
 
                               2
>        60 curva curvb d0a d0b  Sin[4 phi0a - 3 phi0b] - 
 
                                                 2
>        8 d0a Sin[phi0a - 2 phi0b] + 8 curva d0a  Sin[phi0a - 2 phi0b] - 
 
>        16 curvb d0a d0b Sin[phi0a - 2 phi0b] + 
 
                            2
>        592 curva curvb d0a  d0b Sin[phi0a - 2 phi0b] + 
 
                            3
>        192 curva curvb d0b  Sin[phi0a - 2 phi0b] + 
 
                                                   2
>        8 d0a Sin[3 phi0a - 2 phi0b] + 8 curva d0a  Sin[3 phi0a - 2 phi0b] + 
 
>        16 curvb d0a d0b Sin[3 phi0a - 2 phi0b] - 
 
                            2
>        272 curva curvb d0a  d0b Sin[3 phi0a - 2 phi0b] + 
 
                     2
>        16 curva d0b  Sin[3 phi0a - 2 phi0b] - 
 
                           3
>        96 curva curvb d0b  Sin[3 phi0a - 2 phi0b] + 
 
                     2
>        12 curvb d0a  Sin[2 phi0a - phi0b] + 
 
                            3
>        216 curva curvb d0a  Sin[2 phi0a - phi0b] + 
 
>        2 d0b Sin[2 phi0a - phi0b] - 8 curva d0a d0b Sin[2 phi0a - phi0b] + 
 
                     2
>        10 curvb d0b  Sin[2 phi0a - phi0b] + 
 
                                2
>        680 curva curvb d0a d0b  Sin[2 phi0a - phi0b] + 
 
                     2                                 3
>        12 curvb d0a  Sin[phi0b] + 328 curva curvb d0a  Sin[phi0b] + 
 
>        2 d0b Sin[phi0b] + 48 curva d0a d0b Sin[phi0b] + 
 
                     2                                     2
>        10 curvb d0b  Sin[phi0b] + 960 curva curvb d0a d0b  Sin[phi0b])) / 32

dysol1dcurva = Simplify[ D[ysol1, curva], Trig -> True ]

                                                            5
Out[24]= ((-d0b + d0a Cos[phi0a - phi0b]) Csc[phi0a - phi0b]  
 
>      (-(d0a (1 + 40 curvb d0b) Sin[phi0a]) - d0a Sin[3 phi0a - 4 phi0b] + 
 
                                                   2
>        2 d0b Sin[2 phi0a - 3 phi0b] - 4 curvb d0b  Sin[2 phi0a - 3 phi0b] + 
 
>        d0a Sin[phi0a - 2 phi0b] + 20 curvb d0a d0b Sin[phi0a - 2 phi0b] + 
 
>        d0a Sin[3 phi0a - 2 phi0b] - 
 
>        4 curvb d0a d0b Sin[3 phi0a - 2 phi0b] + 
 
                    2
>        8 curvb d0a  Sin[2 phi0a - phi0b] - 2 d0b Sin[2 phi0a - phi0b] + 
 
                     2                                    2
>        12 curvb d0b  Sin[2 phi0a - phi0b] + 24 curvb d0a  Sin[phi0b] + 
 
                                        2
>        4 d0b Sin[phi0b] + 16 curvb d0b  Sin[phi0b])) / 8

dysol1dcurvb = Simplify[ D[ysol1, curvb], Trig -> True ]

                                                            5
Out[25]= ((-d0a + d0b Cos[phi0a - phi0b]) Csc[phi0a - phi0b]  
 
                             2              2
>      (-4 (d0a + 4 curva d0a  + 6 curva d0b ) Sin[phi0a] + 
 
>        (d0b - 4 curva d0a d0b) Sin[2 phi0a - 3 phi0b] - 
 
>        d0b Sin[4 phi0a - 3 phi0b] - 2 d0a Sin[phi0a - 2 phi0b] + 
 
                     2
>        12 curva d0a  Sin[phi0a - 2 phi0b] + 
 
                    2
>        8 curva d0b  Sin[phi0a - 2 phi0b] + 2 d0a Sin[3 phi0a - 2 phi0b] - 
 
                    2
>        4 curva d0a  Sin[3 phi0a - 2 phi0b] + d0b Sin[2 phi0a - phi0b] + 
 
>        20 curva d0a d0b Sin[2 phi0a - phi0b] + d0b Sin[phi0b] + 
 
>        40 curva d0a d0b Sin[phi0b])) / 8

dysol2dd0a = Simplify[ D[ysol2, d0a], Trig -> True ]

                             5
Out[26]= -(Csc[phi0a - phi0b]  (2 
 
                   2
>          (8 curvb  d0a + curva 
 
                                       2        2         2
>             (5 + 12 curvb d0b + curvb  (48 d0a  + 54 d0b ))) Sin[phi0a] - 
 
>         curva (1 + 2 curvb d0b) Sin[7 phi0a - 6 phi0b] - 
 
>         curvb Sin[6 phi0a - 5 phi0b] + 
 
>         2 curva curvb d0a Sin[6 phi0a - 5 phi0b] - 
 
>         curva Sin[3 phi0a - 4 phi0b] + 
 
>         2 curva curvb d0b Sin[3 phi0a - 4 phi0b] - 
 
                       2    2
>         4 curva curvb  d0b  Sin[3 phi0a - 4 phi0b] + 
 
>         5 curva Sin[5 phi0a - 4 phi0b] + 
 
>         10 curva curvb d0b Sin[5 phi0a - 4 phi0b] + 
 
>         curvb Sin[2 phi0a - 3 phi0b] - 
 
>         10 curva curvb d0a Sin[2 phi0a - 3 phi0b] - 
 
                 2
>         4 curvb  d0b Sin[2 phi0a - 3 phi0b] + 
 
                        2
>         40 curva curvb  d0a d0b Sin[2 phi0a - 3 phi0b] + 
 
>         4 curvb Sin[4 phi0a - 3 phi0b] - 
 
>         8 curva curvb d0a Sin[4 phi0a - 3 phi0b] + 
 
                 2
>         4 curvb  d0b Sin[4 phi0a - 3 phi0b] - 
 
                       2
>         8 curva curvb  d0a d0b Sin[4 phi0a - 3 phi0b] + 
 
                                                2
>         5 curva Sin[phi0a - 2 phi0b] + 8 curvb  d0a Sin[phi0a - 2 phi0b] - 
 
                        2    2
>         72 curva curvb  d0a  Sin[phi0a - 2 phi0b] + 
 
>         6 curva curvb d0b Sin[phi0a - 2 phi0b] - 
 
                        2    2
>         60 curva curvb  d0b  Sin[phi0a - 2 phi0b] - 
 
>         10 curva Sin[3 phi0a - 2 phi0b] - 
 
                 2
>         8 curvb  d0a Sin[3 phi0a - 2 phi0b] + 
 
                        2    2
>         24 curva curvb  d0a  Sin[3 phi0a - 2 phi0b] - 
 
>         24 curva curvb d0b Sin[3 phi0a - 2 phi0b] + 
 
                        2    2
>         20 curva curvb  d0b  Sin[3 phi0a - 2 phi0b] - 
 
>         6 curvb Sin[2 phi0a - phi0b] + 
 
>         20 curva curvb d0a Sin[2 phi0a - phi0b] - 
 
                 2
>         4 curvb  d0b Sin[2 phi0a - phi0b] - 
 
                         2
>         120 curva curvb  d0a d0b Sin[2 phi0a - phi0b] + 
 
>         4 curvb Sin[phi0b] - 24 curva curvb d0a Sin[phi0b] - 
 
                 2                                 2
>         4 curvb  d0b Sin[phi0b] - 216 curva curvb  d0a d0b Sin[phi0b])) / 
 
>    (16 curvb)

dysol2dd0b = Simplify[ D[ysol2, d0b], Trig -> True ]

                            5
Out[27]= (Csc[phi0a - phi0b]  (-8 curvb 
 
>         (-1 + curvb d0b + 6 curva (d0a + 9 curvb d0a d0b)) Sin[phi0a] - 
 
>        2 curva (1 + 2 curvb d0b) Sin[8 phi0a - 7 phi0b] + 
 
>        curvb Sin[5 phi0a - 6 phi0b] - curvb Sin[7 phi0a - 6 phi0b] + 
 
>        4 curva curvb d0a Sin[7 phi0a - 6 phi0b] + 
 
>        10 curva Sin[6 phi0a - 5 phi0b] + 
 
>        20 curva curvb d0b Sin[6 phi0a - 5 phi0b] - 
 
>        4 curvb Sin[3 phi0a - 4 phi0b] - 
 
>        4 curva curvb d0a Sin[3 phi0a - 4 phi0b] - 
 
                2
>        4 curvb  d0b Sin[3 phi0a - 4 phi0b] + 
 
                       2
>        16 curva curvb  d0a d0b Sin[3 phi0a - 4 phi0b] + 
 
>        4 curvb Sin[5 phi0a - 4 phi0b] - 
 
>        20 curva curvb d0a Sin[5 phi0a - 4 phi0b] + 
 
                2
>        4 curvb  d0b Sin[5 phi0a - 4 phi0b] - 
 
>        2 curva Sin[2 phi0a - 3 phi0b] + 
 
                2
>        8 curvb  d0a Sin[2 phi0a - 3 phi0b] - 
 
                       2    2
>        40 curva curvb  d0a  Sin[2 phi0a - 3 phi0b] + 
 
>        12 curva curvb d0b Sin[2 phi0a - 3 phi0b] - 
 
                       2    2
>        48 curva curvb  d0b  Sin[2 phi0a - 3 phi0b] - 
 
>        20 curva Sin[4 phi0a - 3 phi0b] - 
 
                2
>        8 curvb  d0a Sin[4 phi0a - 3 phi0b] + 
 
                      2    2
>        8 curva curvb  d0a  Sin[4 phi0a - 3 phi0b] - 
 
>        40 curva curvb d0b Sin[4 phi0a - 3 phi0b] + 
 
>        7 curvb Sin[phi0a - 2 phi0b] - 
 
>        12 curva curvb d0a Sin[phi0a - 2 phi0b] + 
 
                        2
>        240 curva curvb  d0a d0b Sin[phi0a - 2 phi0b] - 
 
>        7 curvb Sin[3 phi0a - 2 phi0b] + 
 
>        48 curva curvb d0a Sin[3 phi0a - 2 phi0b] - 
 
                       2
>        80 curva curvb  d0a d0b Sin[3 phi0a - 2 phi0b] + 
 
                                                2
>        20 curva Sin[2 phi0a - phi0b] + 8 curvb  d0a Sin[2 phi0a - phi0b] + 
 
                        2    2
>        120 curva curvb  d0a  Sin[2 phi0a - phi0b] + 
 
>        24 curva curvb d0b Sin[2 phi0a - phi0b] + 
 
                        2    2
>        144 curva curvb  d0b  Sin[2 phi0a - phi0b] - 10 curva Sin[phi0b] + 
 
                2                                 2    2
>        8 curvb  d0a Sin[phi0b] + 216 curva curvb  d0a  Sin[phi0b] + 
 
                                                        2    2
>        12 curva curvb d0b Sin[phi0b] + 192 curva curvb  d0b  Sin[phi0b])) / 
 
>    (32 curvb)

dysol2dphi0a = Simplify[ D[ysol2, phi0a], Trig -> True ]

                            6            2
Out[28]= (Csc[phi0a - phi0b]  (-((8 curvb  d0a (11 + 24 curvb d0b) + 
 
                                               2         2          2
>             curva (65 + 180 curvb d0b + curvb  (-40 d0a  + 228 d0b ) + 
 
                         3         2             3
>                32 curvb  (120 d0a  d0b + 41 d0b ))) Sin[phi0a]) - 
 
                                  2
>        3 curva (1 + 2 curvb d0b)  Sin[9 phi0a - 8 phi0b] - 
 
>        2 curvb Sin[8 phi0a - 7 phi0b] + 
 
>        8 curva curvb d0a Sin[8 phi0a - 7 phi0b] - 
 
                2
>        4 curvb  d0b Sin[8 phi0a - 7 phi0b] + 
 
                       2
>        16 curva curvb  d0a d0b Sin[8 phi0a - 7 phi0b] - 
 
>        curva Sin[5 phi0a - 6 phi0b] + 19 curva Sin[7 phi0a - 6 phi0b] + 
 
                2
>        4 curvb  d0a Sin[7 phi0a - 6 phi0b] - 
 
                      2    2
>        4 curva curvb  d0a  Sin[7 phi0a - 6 phi0b] + 
 
>        72 curva curvb d0b Sin[7 phi0a - 6 phi0b] + 
 
                       2    2
>        72 curva curvb  d0b  Sin[7 phi0a - 6 phi0b] + 
 
>        2 curvb Sin[4 phi0a - 5 phi0b] - 
 
>        8 curva curvb d0a Sin[4 phi0a - 5 phi0b] - 
 
                2
>        4 curvb  d0b Sin[4 phi0a - 5 phi0b] + 
 
                       2
>        16 curva curvb  d0a d0b Sin[4 phi0a - 5 phi0b] + 
 
                3    2
>        8 curvb  d0b  Sin[4 phi0a - 5 phi0b] - 
 
                       3        2
>        32 curva curvb  d0a d0b  Sin[4 phi0a - 5 phi0b] + 
 
>        12 curvb Sin[6 phi0a - 5 phi0b] - 
 
>        48 curva curvb d0a Sin[6 phi0a - 5 phi0b] + 
 
                 2
>        24 curvb  d0b Sin[6 phi0a - 5 phi0b] - 
 
                       2
>        96 curva curvb  d0a d0b Sin[6 phi0a - 5 phi0b] + 
 
>        9 curva Sin[3 phi0a - 4 phi0b] + 
 
                 2
>        12 curvb  d0a Sin[3 phi0a - 4 phi0b] - 
 
                       2    2
>        60 curva curvb  d0a  Sin[3 phi0a - 4 phi0b] + 
 
>        12 curva curvb d0b Sin[3 phi0a - 4 phi0b] - 
 
                 3
>        48 curvb  d0a d0b Sin[3 phi0a - 4 phi0b] + 
 
                        3    2
>        240 curva curvb  d0a  d0b Sin[3 phi0a - 4 phi0b] - 
 
                       2    2
>        36 curva curvb  d0b  Sin[3 phi0a - 4 phi0b] + 
 
                       3    3
>        96 curva curvb  d0b  Sin[3 phi0a - 4 phi0b] - 
 
>        51 curva Sin[5 phi0a - 4 phi0b] - 
 
                 2
>        28 curvb  d0a Sin[5 phi0a - 4 phi0b] + 
 
                       2    2
>        28 curva curvb  d0a  Sin[5 phi0a - 4 phi0b] - 
 
>        180 curva curvb d0b Sin[5 phi0a - 4 phi0b] + 
 
                 3
>        16 curvb  d0a d0b Sin[5 phi0a - 4 phi0b] - 
 
                       3    2
>        16 curva curvb  d0a  d0b Sin[5 phi0a - 4 phi0b] - 
 
                        2    2
>        180 curva curvb  d0b  Sin[5 phi0a - 4 phi0b] - 
 
>        12 curvb Sin[2 phi0a - 3 phi0b] + 
 
>        48 curva curvb d0a Sin[2 phi0a - 3 phi0b] + 
 
                 3    2
>        64 curvb  d0a  Sin[2 phi0a - 3 phi0b] - 
 
                        3    3
>        384 curva curvb  d0a  Sin[2 phi0a - 3 phi0b] + 
 
                2
>        8 curvb  d0b Sin[2 phi0a - 3 phi0b] + 
 
                        2
>        160 curva curvb  d0a d0b Sin[2 phi0a - 3 phi0b] + 
 
                 3    2
>        32 curvb  d0b  Sin[2 phi0a - 3 phi0b] - 
 
                         3        2
>        1088 curva curvb  d0a d0b  Sin[2 phi0a - 3 phi0b] - 
 
>        30 curvb Sin[4 phi0a - 3 phi0b] + 
 
>        120 curva curvb d0a Sin[4 phi0a - 3 phi0b] - 
 
                 3    2
>        32 curvb  d0a  Sin[4 phi0a - 3 phi0b] + 
 
                       3    3
>        64 curva curvb  d0a  Sin[4 phi0a - 3 phi0b] - 
 
                 2
>        52 curvb  d0b Sin[4 phi0a - 3 phi0b] + 
 
                        2
>        208 curva curvb  d0a d0b Sin[4 phi0a - 3 phi0b] - 
 
                 3    2
>        40 curvb  d0b  Sin[4 phi0a - 3 phi0b] + 
 
                        3        2
>        160 curva curvb  d0a d0b  Sin[4 phi0a - 3 phi0b] - 
 
                                                 2
>        33 curva Sin[phi0a - 2 phi0b] - 52 curvb  d0a Sin[phi0a - 2 phi0b] + 
 
                        2    2
>        100 curva curvb  d0a  Sin[phi0a - 2 phi0b] - 
 
>        72 curva curvb d0b Sin[phi0a - 2 phi0b] - 
 
                 3
>        32 curvb  d0a d0b Sin[phi0a - 2 phi0b] + 
 
                         3    2
>        2720 curva curvb  d0a  d0b Sin[phi0a - 2 phi0b] - 
 
                       2    2
>        24 curva curvb  d0b  Sin[phi0a - 2 phi0b] + 
 
                        3    3
>        864 curva curvb  d0b  Sin[phi0a - 2 phi0b] + 
 
>        75 curva Sin[3 phi0a - 2 phi0b] + 
 
                 2
>        72 curvb  d0a Sin[3 phi0a - 2 phi0b] - 
 
                       2    2
>        24 curva curvb  d0a  Sin[3 phi0a - 2 phi0b] + 
 
>        240 curva curvb d0b Sin[3 phi0a - 2 phi0b] + 
 
                 3
>        96 curvb  d0a d0b Sin[3 phi0a - 2 phi0b] - 
 
                        3    2
>        864 curva curvb  d0a  d0b Sin[3 phi0a - 2 phi0b] + 
 
                        2    2
>        288 curva curvb  d0b  Sin[3 phi0a - 2 phi0b] - 
 
                        3    3
>        288 curva curvb  d0b  Sin[3 phi0a - 2 phi0b] + 
 
>        40 curvb Sin[2 phi0a - phi0b] - 
 
>        160 curva curvb d0a Sin[2 phi0a - phi0b] + 
 
                        3    3
>        768 curva curvb  d0a  Sin[2 phi0a - phi0b] + 
 
                 2
>        48 curvb  d0b Sin[2 phi0a - phi0b] - 
 
                        2
>        384 curva curvb  d0a d0b Sin[2 phi0a - phi0b] + 
 
                 3    2
>        32 curvb  d0b  Sin[2 phi0a - phi0b] + 
 
                         3        2
>        2368 curva curvb  d0a d0b  Sin[2 phi0a - phi0b] - 
 
>        30 curvb Sin[phi0b] + 120 curva curvb d0a Sin[phi0b] + 
 
                 3    2                              3    3
>        96 curvb  d0a  Sin[phi0b] + 1344 curva curvb  d0a  Sin[phi0b] - 
 
                 2                                 2
>        12 curvb  d0b Sin[phi0b] + 432 curva curvb  d0a d0b Sin[phi0b] + 
 
                 3    2                              3        2
>        48 curvb  d0b  Sin[phi0b] + 4032 curva curvb  d0a d0b  Sin[phi0b]))\
 
                  2
>     / (128 curvb )

dysol2dphi0b = Simplify[ D[ysol2, phi0b], Trig -> True ]

                             6
Out[29]= -(Csc[phi0a - phi0b]  (-6 
 
                   2
>          (8 curvb  d0a (1 + 4 curvb d0b) + 
 
                                              2       2        2
>            curva (5 + 20 curvb d0b + 4 curvb  (2 d0a  + 9 d0b ) + 
 
                         3       2          3
>               224 curvb  (3 d0a  d0b + d0b ))) Sin[phi0a] - 
 
                                   2
>         2 curva (1 + 2 curvb d0b)  Sin[9 phi0a - 8 phi0b] + 
 
>         curvb Sin[6 phi0a - 7 phi0b] + 
 
                 2
>         2 curvb  d0b Sin[6 phi0a - 7 phi0b] - 
 
>         curvb Sin[8 phi0a - 7 phi0b] + 
 
>         4 curva curvb d0a Sin[8 phi0a - 7 phi0b] - 
 
                 2
>         2 curvb  d0b Sin[8 phi0a - 7 phi0b] + 
 
                       2
>         8 curva curvb  d0a d0b Sin[8 phi0a - 7 phi0b] + 
 
>         12 curva Sin[7 phi0a - 6 phi0b] + 
 
>         48 curva curvb d0b Sin[7 phi0a - 6 phi0b] + 
 
                        2    2
>         48 curva curvb  d0b  Sin[7 phi0a - 6 phi0b] - 
 
>         5 curvb Sin[4 phi0a - 5 phi0b] - 
 
>         4 curva curvb d0a Sin[4 phi0a - 5 phi0b] - 
 
                  2
>         14 curvb  d0b Sin[4 phi0a - 5 phi0b] + 
 
                       2
>         8 curva curvb  d0a d0b Sin[4 phi0a - 5 phi0b] + 
 
                 3    2
>         4 curvb  d0b  Sin[4 phi0a - 5 phi0b] - 
 
                        3        2
>         16 curva curvb  d0a d0b  Sin[4 phi0a - 5 phi0b] + 
 
>         5 curvb Sin[6 phi0a - 5 phi0b] - 
 
>         24 curva curvb d0a Sin[6 phi0a - 5 phi0b] + 
 
                  2
>         14 curvb  d0b Sin[6 phi0a - 5 phi0b] - 
 
                        2
>         48 curva curvb  d0a d0b Sin[6 phi0a - 5 phi0b] - 
 
                 3    2
>         4 curvb  d0b  Sin[6 phi0a - 5 phi0b] + 
 
>         2 curva Sin[3 phi0a - 4 phi0b] + 
 
                 2
>         8 curvb  d0a Sin[3 phi0a - 4 phi0b] - 
 
                        2    2
>         40 curva curvb  d0a  Sin[3 phi0a - 4 phi0b] + 
 
>         8 curva curvb d0b Sin[3 phi0a - 4 phi0b] - 
 
                  3
>         32 curvb  d0a d0b Sin[3 phi0a - 4 phi0b] + 
 
                         3    2
>         160 curva curvb  d0a  d0b Sin[3 phi0a - 4 phi0b] - 
 
                        2    2
>         24 curva curvb  d0b  Sin[3 phi0a - 4 phi0b] + 
 
                        3    3
>         64 curva curvb  d0b  Sin[3 phi0a - 4 phi0b] - 
 
>         30 curva Sin[5 phi0a - 4 phi0b] - 
 
                 2
>         8 curvb  d0a Sin[5 phi0a - 4 phi0b] + 
 
                       2    2
>         8 curva curvb  d0a  Sin[5 phi0a - 4 phi0b] - 
 
>         120 curva curvb d0b Sin[5 phi0a - 4 phi0b] + 
 
                  3
>         32 curvb  d0a d0b Sin[5 phi0a - 4 phi0b] - 
 
                        3    2
>         32 curva curvb  d0a  d0b Sin[5 phi0a - 4 phi0b] - 
 
                         2    2
>         120 curva curvb  d0b  Sin[5 phi0a - 4 phi0b] + 
 
>         9 curvb Sin[2 phi0a - 3 phi0b] + 
 
>         24 curva curvb d0a Sin[2 phi0a - 3 phi0b] + 
 
                  3    2
>         48 curvb  d0a  Sin[2 phi0a - 3 phi0b] - 
 
                         3    3
>         288 curva curvb  d0a  Sin[2 phi0a - 3 phi0b] + 
 
                  2
>         30 curvb  d0b Sin[2 phi0a - 3 phi0b] + 
 
                         2
>         144 curva curvb  d0a d0b Sin[2 phi0a - 3 phi0b] + 
 
                  3    2
>         36 curvb  d0b  Sin[2 phi0a - 3 phi0b] - 
 
                         3        2
>         864 curva curvb  d0a d0b  Sin[2 phi0a - 3 phi0b] - 
 
>         9 curvb Sin[4 phi0a - 3 phi0b] + 
 
>         60 curva curvb d0a Sin[4 phi0a - 3 phi0b] - 
 
                  3    2
>         48 curvb  d0a  Sin[4 phi0a - 3 phi0b] + 
 
                        3    3
>         96 curva curvb  d0a  Sin[4 phi0a - 3 phi0b] - 
 
                  2
>         30 curvb  d0b Sin[4 phi0a - 3 phi0b] + 
 
                        2
>         72 curva curvb  d0a d0b Sin[4 phi0a - 3 phi0b] - 
 
                  3    2
>         36 curvb  d0b  Sin[4 phi0a - 3 phi0b] + 
 
                         3        2
>         240 curva curvb  d0a d0b  Sin[4 phi0a - 3 phi0b] - 
 
>         12 curva Sin[phi0a - 2 phi0b] - 
 
                  2
>         32 curvb  d0a Sin[phi0a - 2 phi0b] + 
 
                        2    2
>         32 curva curvb  d0a  Sin[phi0a - 2 phi0b] - 
 
>         48 curva curvb d0b Sin[phi0a - 2 phi0b] - 
 
                  3
>         64 curvb  d0a d0b Sin[phi0a - 2 phi0b] + 
 
                          3    2
>         2368 curva curvb  d0a  d0b Sin[phi0a - 2 phi0b] - 
 
                        2    2
>         48 curva curvb  d0b  Sin[phi0a - 2 phi0b] + 
 
                         3    3
>         768 curva curvb  d0b  Sin[phi0a - 2 phi0b] + 
 
>         40 curva Sin[3 phi0a - 2 phi0b] + 
 
                  2
>         32 curvb  d0a Sin[3 phi0a - 2 phi0b] + 
 
                        2    2
>         32 curva curvb  d0a  Sin[3 phi0a - 2 phi0b] + 
 
>         160 curva curvb d0b Sin[3 phi0a - 2 phi0b] + 
 
                  3
>         64 curvb  d0a d0b Sin[3 phi0a - 2 phi0b] - 
 
                          3    2
>         1088 curva curvb  d0a  d0b Sin[3 phi0a - 2 phi0b] + 
 
                         2    2
>         224 curva curvb  d0b  Sin[3 phi0a - 2 phi0b] - 
 
                         3    3
>         384 curva curvb  d0b  Sin[3 phi0a - 2 phi0b] + 
 
>         5 curvb Sin[2 phi0a - phi0b] - 
 
>         80 curva curvb d0a Sin[2 phi0a - phi0b] + 
 
                  3    2
>         48 curvb  d0a  Sin[2 phi0a - phi0b] + 
 
                         3    3
>         864 curva curvb  d0a  Sin[2 phi0a - phi0b] + 
 
                  2
>         18 curvb  d0b Sin[2 phi0a - phi0b] - 
 
                         2
>         192 curva curvb  d0a d0b Sin[2 phi0a - phi0b] + 
 
                  3    2
>         40 curvb  d0b  Sin[2 phi0a - phi0b] + 
 
                          3        2
>         2720 curva curvb  d0a d0b  Sin[2 phi0a - phi0b] + 
 
>         5 curvb Sin[phi0b] + 60 curva curvb d0a Sin[phi0b] + 
 
                  3    2                              3    3
>         48 curvb  d0a  Sin[phi0b] + 1312 curva curvb  d0a  Sin[phi0b] + 
 
                  2                                 2
>         18 curvb  d0b Sin[phi0b] + 312 curva curvb  d0a d0b Sin[phi0b] + 
 
                  3    2                              3        2
>         40 curvb  d0b  Sin[phi0b] + 3840 curva curvb  d0a d0b  Sin[phi0b]))\
 
                  2
>     / (128 curvb )

dysol2dcurva = Simplify[ D[ysol2, curva], Trig -> True ]

                            5
Out[30]= (Csc[phi0a - phi0b]  (-8 curvb d0a 
 
                                   2        2         2
>         (5 + 12 curvb d0b + curvb  (16 d0a  + 54 d0b )) Sin[phi0a] - 
 
                          2
>        (1 + 2 curvb d0b)  Sin[8 phi0a - 7 phi0b] + 
 
>        4 curvb d0a Sin[7 phi0a - 6 phi0b] + 
 
                2
>        8 curvb  d0a d0b Sin[7 phi0a - 6 phi0b] + Sin[4 phi0a - 5 phi0b] + 
 
                                           2    2
>        6 Sin[6 phi0a - 5 phi0b] - 4 curvb  d0a  Sin[6 phi0a - 5 phi0b] + 
 
>        20 curvb d0b Sin[6 phi0a - 5 phi0b] + 
 
                 2    2
>        20 curvb  d0b  Sin[6 phi0a - 5 phi0b] + 
 
>        4 curvb d0a Sin[3 phi0a - 4 phi0b] - 
 
                2
>        8 curvb  d0a d0b Sin[3 phi0a - 4 phi0b] + 
 
                 3        2
>        16 curvb  d0a d0b  Sin[3 phi0a - 4 phi0b] - 
 
>        20 curvb d0a Sin[5 phi0a - 4 phi0b] - 
 
                 2
>        40 curvb  d0a d0b Sin[5 phi0a - 4 phi0b] - 
 
                                            2    2
>        6 Sin[2 phi0a - 3 phi0b] + 20 curvb  d0a  Sin[2 phi0a - 3 phi0b] - 
 
>        4 curvb d0b Sin[2 phi0a - 3 phi0b] - 
 
                 3    2
>        80 curvb  d0a  d0b Sin[2 phi0a - 3 phi0b] + 
 
                 2    2
>        12 curvb  d0b  Sin[2 phi0a - 3 phi0b] - 
 
                 3    3
>        32 curvb  d0b  Sin[2 phi0a - 3 phi0b] - 15 Sin[4 phi0a - 3 phi0b] + 
 
                 2    2
>        16 curvb  d0a  Sin[4 phi0a - 3 phi0b] - 
 
>        40 curvb d0b Sin[4 phi0a - 3 phi0b] + 
 
                 3    2
>        16 curvb  d0a  d0b Sin[4 phi0a - 3 phi0b] - 
 
                 2    2
>        40 curvb  d0b  Sin[4 phi0a - 3 phi0b] - 
 
>        20 curvb d0a Sin[phi0a - 2 phi0b] + 
 
                 3    3
>        96 curvb  d0a  Sin[phi0a - 2 phi0b] - 
 
                 2
>        24 curvb  d0a d0b Sin[phi0a - 2 phi0b] + 
 
                  3        2
>        240 curvb  d0a d0b  Sin[phi0a - 2 phi0b] + 
 
>        40 curvb d0a Sin[3 phi0a - 2 phi0b] - 
 
                 3    3
>        32 curvb  d0a  Sin[3 phi0a - 2 phi0b] + 
 
                 2
>        96 curvb  d0a d0b Sin[3 phi0a - 2 phi0b] - 
 
                 3        2
>        80 curvb  d0a d0b  Sin[3 phi0a - 2 phi0b] + 
 
                                           2    2
>        20 Sin[2 phi0a - phi0b] - 40 curvb  d0a  Sin[2 phi0a - phi0b] + 
 
>        40 curvb d0b Sin[2 phi0a - phi0b] + 
 
                  3    2
>        240 curvb  d0a  d0b Sin[2 phi0a - phi0b] + 
 
                 2    2
>        24 curvb  d0b  Sin[2 phi0a - phi0b] + 
 
                 3    3
>        96 curvb  d0b  Sin[2 phi0a - phi0b] - 15 Sin[phi0b] + 
 
                 2    2
>        48 curvb  d0a  Sin[phi0b] - 20 curvb d0b Sin[phi0b] + 
 
                  3    2                          2    2
>        432 curvb  d0a  d0b Sin[phi0b] + 12 curvb  d0b  Sin[phi0b] + 
 
                  3    3                         2
>        128 curvb  d0b  Sin[phi0b])) / (64 curvb )

dysol2dcurvb = Simplify[ D[ysol2, curvb], Trig -> True ]

                            5
Out[31]= (Csc[phi0a - phi0b]  (-4 curvb 
 
                      2       2      2
>         (5 + 2 curvb  (4 d0a  + d0b ) + 
 
                                   2        2         2
>           2 curva d0a (-5 + curvb  (16 d0a  + 54 d0b ))) Sin[phi0a] + 
 
>        2 curva (1 + 2 curvb d0b) Sin[8 phi0a - 7 phi0b] - 
 
>        curvb Sin[5 phi0a - 6 phi0b] + curvb Sin[7 phi0a - 6 phi0b] - 
 
>        4 curva curvb d0a Sin[7 phi0a - 6 phi0b] - 
 
>        2 curva Sin[4 phi0a - 5 phi0b] - 12 curva Sin[6 phi0a - 5 phi0b] - 
 
>        20 curva curvb d0b Sin[6 phi0a - 5 phi0b] + 
 
>        6 curvb Sin[3 phi0a - 4 phi0b] - 
 
>        4 curva curvb d0a Sin[3 phi0a - 4 phi0b] - 
 
                3    2
>        4 curvb  d0b  Sin[3 phi0a - 4 phi0b] + 
 
                       3        2
>        16 curva curvb  d0a d0b  Sin[3 phi0a - 4 phi0b] - 
 
>        6 curvb Sin[5 phi0a - 4 phi0b] + 
 
>        20 curva curvb d0a Sin[5 phi0a - 4 phi0b] + 
 
                3    2
>        4 curvb  d0b  Sin[5 phi0a - 4 phi0b] + 
 
>        12 curva Sin[2 phi0a - 3 phi0b] + 
 
>        4 curva curvb d0b Sin[2 phi0a - 3 phi0b] + 
 
                 3
>        16 curvb  d0a d0b Sin[2 phi0a - 3 phi0b] - 
 
                       3    2
>        80 curva curvb  d0a  d0b Sin[2 phi0a - 3 phi0b] - 
 
                       3    3
>        32 curva curvb  d0b  Sin[2 phi0a - 3 phi0b] + 
 
>        30 curva Sin[4 phi0a - 3 phi0b] + 
 
>        40 curva curvb d0b Sin[4 phi0a - 3 phi0b] - 
 
                 3
>        16 curvb  d0a d0b Sin[4 phi0a - 3 phi0b] + 
 
                       3    2
>        16 curva curvb  d0a  d0b Sin[4 phi0a - 3 phi0b] - 
 
>        15 curvb Sin[phi0a - 2 phi0b] + 
 
>        20 curva curvb d0a Sin[phi0a - 2 phi0b] - 
 
                 3    2
>        16 curvb  d0a  Sin[phi0a - 2 phi0b] + 
 
                       3    3
>        96 curva curvb  d0a  Sin[phi0a - 2 phi0b] + 
 
                        3        2
>        240 curva curvb  d0a d0b  Sin[phi0a - 2 phi0b] + 
 
>        15 curvb Sin[3 phi0a - 2 phi0b] - 
 
>        40 curva curvb d0a Sin[3 phi0a - 2 phi0b] + 
 
                 3    2
>        16 curvb  d0a  Sin[3 phi0a - 2 phi0b] - 
 
                       3    3
>        32 curva curvb  d0a  Sin[3 phi0a - 2 phi0b] - 
 
                       3        2
>        80 curva curvb  d0a d0b  Sin[3 phi0a - 2 phi0b] - 
 
>        40 curva Sin[2 phi0a - phi0b] - 
 
>        40 curva curvb d0b Sin[2 phi0a - phi0b] + 
 
                 3
>        16 curvb  d0a d0b Sin[2 phi0a - phi0b] + 
 
                        3    2
>        240 curva curvb  d0a  d0b Sin[2 phi0a - phi0b] + 
 
                       3    3
>        96 curva curvb  d0b  Sin[2 phi0a - phi0b] + 30 curva Sin[phi0b] + 
 
                                                 3
>        20 curva curvb d0b Sin[phi0b] + 16 curvb  d0a d0b Sin[phi0b] + 
 
                        3    2
>        432 curva curvb  d0a  d0b Sin[phi0b] + 
 
                        3    3                         3
>        128 curva curvb  d0b  Sin[phi0b])) / (64 curvb )

DumpSave[ "intersections.mx", {xsol1, xsol2, ysol1, ysol2,
			       dxsol1dd0a, dxsol1dd0b, 
			       dxsol1dphi0a, dxsol1dphi0b, 
			       dxsol1dcurva, dxsol1dcurvb, 
			       dxsol2dd0a, dxsol2dd0b, 
			       dxsol2dphi0a, dxsol2dphi0b, 
			       dxsol2dcurva, dxsol2dcurvb, 
			       dysol1dd0a, dysol1dd0b, 
			       dysol1dphi0a, dysol1dphi0b, 
			       dysol1dcurva, dysol1dcurvb, 
			       dysol2dd0a, dysol2dd0b, 
			       dysol2dphi0a, dysol2dphi0b, 
			       dysol2dcurva, dysol2dcurvb} ];

double BigNTuple::xsol1( double curva, double d0a, double phi0a,
			 double curvb, double d0b, double phi0b )
{
    return
   ((2*((3 + 2*curva*d0a)*d0b + 
           curvb*(4*pow(d0a,2) + 16*curva*pow(d0a,3) + pow(d0b,2) + 
              54*curva*d0a*pow(d0b,2)))*cos(phi0a) + 
        d0a*(-1 + curva*d0a)*cos(4*phi0a - 5*phi0b) + 
        d0b*cos(3*phi0a - 4*phi0b) - 4*curva*d0a*d0b*cos(3*phi0a - 4*phi0b) - 
        curvb*pow(d0b,2)*cos(3*phi0a - 4*phi0b) + 
        4*curva*curvb*d0a*pow(d0b,2)*cos(3*phi0a - 4*phi0b) + 
        d0b*cos(5*phi0a - 4*phi0b) - 
        curvb*pow(d0b,2)*cos(5*phi0a - 4*phi0b) + 
        4*d0a*cos(2*phi0a - 3*phi0b) + 
        4*curvb*d0a*d0b*cos(2*phi0a - 3*phi0b) - 
        20*curva*curvb*pow(d0a,2)*d0b*cos(2*phi0a - 3*phi0b) + 
        4*curva*pow(d0b,2)*cos(2*phi0a - 3*phi0b) - 
        8*curva*curvb*pow(d0b,3)*cos(2*phi0a - 3*phi0b) - 
        d0a*cos(4*phi0a - 3*phi0b) + 
        curva*pow(d0a,2)*cos(4*phi0a - 3*phi0b) + 
        4*curvb*d0a*d0b*cos(4*phi0a - 3*phi0b) - 
        4*curva*curvb*pow(d0a,2)*d0b*cos(4*phi0a - 3*phi0b) - 
        4*curvb*pow(d0a,2)*cos(phi0a - 2*phi0b) + 
        24*curva*curvb*pow(d0a,3)*cos(phi0a - 2*phi0b) - 
        4*d0b*cos(phi0a - 2*phi0b) + 4*curva*d0a*d0b*cos(phi0a - 2*phi0b) + 
        60*curva*curvb*d0a*pow(d0b,2)*cos(phi0a - 2*phi0b) - 
        4*curvb*pow(d0a,2)*cos(3*phi0a - 2*phi0b) + 
        8*curva*curvb*pow(d0a,3)*cos(3*phi0a - 2*phi0b) - 
        4*d0b*cos(3*phi0a - 2*phi0b) - 
        4*curva*d0a*d0b*cos(3*phi0a - 2*phi0b) + 
        20*curva*curvb*d0a*pow(d0b,2)*cos(3*phi0a - 2*phi0b) + 
        4*d0a*cos(2*phi0a - phi0b) - 4*curvb*d0a*d0b*cos(2*phi0a - phi0b) - 
        60*curva*curvb*pow(d0a,2)*d0b*cos(2*phi0a - phi0b) + 
        4*curva*pow(d0b,2)*cos(2*phi0a - phi0b) - 
        24*curva*curvb*pow(d0b,3)*cos(2*phi0a - phi0b) - 6*d0a*cos(phi0b) - 
        2*curva*pow(d0a,2)*cos(phi0b) - 4*curvb*d0a*d0b*cos(phi0b) - 
        108*curva*curvb*pow(d0a,2)*d0b*cos(phi0b) - 
        8*curva*pow(d0b,2)*cos(phi0b) - 
        32*curva*curvb*pow(d0b,3)*cos(phi0b))*pow(sin(phi0a - phi0b),-5))/
    16.;
}

double BigNTuple::xsol2( double curva, double d0a, double phi0a,
			 double curvb, double d0b, double phi0b )
{
    return
   -((4*curvb*(-5 - 4*curvb*d0b + 
            2*pow(curvb,2)*(4*pow(d0a,2) + pow(d0b,2)) + 
            2*curva*d0a*(5 + 12*curvb*d0b + 
               pow(curvb,2)*(16*pow(d0a,2) + 54*pow(d0b,2))))*cos(phi0a)
           + curva*pow(1 + 2*curvb*d0b,2)*cos(8*phi0a - 7*phi0b) + 
         curvb*cos(5*phi0a - 6*phi0b) + 
         2*pow(curvb,2)*d0b*cos(5*phi0a - 6*phi0b) + 
         curvb*cos(7*phi0a - 6*phi0b) - 
         4*curva*curvb*d0a*cos(7*phi0a - 6*phi0b) + 
         2*pow(curvb,2)*d0b*cos(7*phi0a - 6*phi0b) - 
         8*curva*pow(curvb,2)*d0a*d0b*cos(7*phi0a - 6*phi0b) + 
         curva*cos(4*phi0a - 5*phi0b) - 6*curva*cos(6*phi0a - 5*phi0b) - 
         4*pow(curvb,2)*d0a*cos(6*phi0a - 5*phi0b) + 
         4*curva*pow(curvb,2)*pow(d0a,2)*cos(6*phi0a - 5*phi0b) - 
         20*curva*curvb*d0b*cos(6*phi0a - 5*phi0b) - 
         20*curva*pow(curvb,2)*pow(d0b,2)*cos(6*phi0a - 5*phi0b) - 
         6*curvb*cos(3*phi0a - 4*phi0b) + 
         4*curva*curvb*d0a*cos(3*phi0a - 4*phi0b) - 
         8*pow(curvb,2)*d0b*cos(3*phi0a - 4*phi0b) - 
         8*curva*pow(curvb,2)*d0a*d0b*cos(3*phi0a - 4*phi0b) - 
         4*pow(curvb,3)*pow(d0b,2)*cos(3*phi0a - 4*phi0b) + 
         16*curva*pow(curvb,3)*d0a*pow(d0b,2)*cos(3*phi0a - 4*phi0b) - 
         6*curvb*cos(5*phi0a - 4*phi0b) + 
         20*curva*curvb*d0a*cos(5*phi0a - 4*phi0b) - 
         8*pow(curvb,2)*d0b*cos(5*phi0a - 4*phi0b) + 
         40*curva*pow(curvb,2)*d0a*d0b*cos(5*phi0a - 4*phi0b) - 
         4*pow(curvb,3)*pow(d0b,2)*cos(5*phi0a - 4*phi0b) - 
         6*curva*cos(2*phi0a - 3*phi0b) - 
         4*pow(curvb,2)*d0a*cos(2*phi0a - 3*phi0b) + 
         20*curva*pow(curvb,2)*pow(d0a,2)*cos(2*phi0a - 3*phi0b) - 
         4*curva*curvb*d0b*cos(2*phi0a - 3*phi0b) + 
         16*pow(curvb,3)*d0a*d0b*cos(2*phi0a - 3*phi0b) - 
         80*curva*pow(curvb,3)*pow(d0a,2)*d0b*cos(2*phi0a - 3*phi0b) + 
         12*curva*pow(curvb,2)*pow(d0b,2)*cos(2*phi0a - 3*phi0b) - 
         32*curva*pow(curvb,3)*pow(d0b,3)*cos(2*phi0a - 3*phi0b) + 
         15*curva*cos(4*phi0a - 3*phi0b) + 
         16*pow(curvb,2)*d0a*cos(4*phi0a - 3*phi0b) - 
         16*curva*pow(curvb,2)*pow(d0a,2)*cos(4*phi0a - 3*phi0b) + 
         40*curva*curvb*d0b*cos(4*phi0a - 3*phi0b) + 
         16*pow(curvb,3)*d0a*d0b*cos(4*phi0a - 3*phi0b) - 
         16*curva*pow(curvb,3)*pow(d0a,2)*d0b*cos(4*phi0a - 3*phi0b) + 
         40*curva*pow(curvb,2)*pow(d0b,2)*cos(4*phi0a - 3*phi0b) + 
         15*curvb*cos(phi0a - 2*phi0b) - 
         20*curva*curvb*d0a*cos(phi0a - 2*phi0b) - 
         16*pow(curvb,3)*pow(d0a,2)*cos(phi0a - 2*phi0b) + 
         96*curva*pow(curvb,3)*pow(d0a,3)*cos(phi0a - 2*phi0b) + 
         14*pow(curvb,2)*d0b*cos(phi0a - 2*phi0b) - 
         24*curva*pow(curvb,2)*d0a*d0b*cos(phi0a - 2*phi0b) + 
         240*curva*pow(curvb,3)*d0a*pow(d0b,2)*cos(phi0a - 2*phi0b) + 
         15*curvb*cos(3*phi0a - 2*phi0b) - 
         40*curva*curvb*d0a*cos(3*phi0a - 2*phi0b) - 
         16*pow(curvb,3)*pow(d0a,2)*cos(3*phi0a - 2*phi0b) + 
         32*curva*pow(curvb,3)*pow(d0a,3)*cos(3*phi0a - 2*phi0b) + 
         14*pow(curvb,2)*d0b*cos(3*phi0a - 2*phi0b) - 
         96*curva*pow(curvb,2)*d0a*d0b*cos(3*phi0a - 2*phi0b) + 
         80*curva*pow(curvb,3)*d0a*pow(d0b,2)*cos(3*phi0a - 2*phi0b) - 
         20*curva*cos(2*phi0a - phi0b) - 
         24*pow(curvb,2)*d0a*cos(2*phi0a - phi0b) + 
         40*curva*pow(curvb,2)*pow(d0a,2)*cos(2*phi0a - phi0b) - 
         40*curva*curvb*d0b*cos(2*phi0a - phi0b) - 
         16*pow(curvb,3)*d0a*d0b*cos(2*phi0a - phi0b) - 
         240*curva*pow(curvb,3)*pow(d0a,2)*d0b*cos(2*phi0a - phi0b) - 
         24*curva*pow(curvb,2)*pow(d0b,2)*cos(2*phi0a - phi0b) - 
         96*curva*pow(curvb,3)*pow(d0b,3)*cos(2*phi0a - phi0b) + 
         15*curva*cos(phi0b) + 16*pow(curvb,2)*d0a*cos(phi0b) - 
         48*curva*pow(curvb,2)*pow(d0a,2)*cos(phi0b) + 
         20*curva*curvb*d0b*cos(phi0b) - 
         16*pow(curvb,3)*d0a*d0b*cos(phi0b) - 
         432*curva*pow(curvb,3)*pow(d0a,2)*d0b*cos(phi0b) - 
         12*curva*pow(curvb,2)*pow(d0b,2)*cos(phi0b) - 
         128*curva*pow(curvb,3)*pow(d0b,3)*cos(phi0b))*
       pow(sin(phi0a - phi0b),-5))/(64.*pow(curvb,2));
}

double BigNTuple::ysol1( double curva, double d0a, double phi0a,
			 double curvb, double d0b, double phi0b )
{
    return
   -(pow(sin(phi0a - phi0b),-5)*
       (-2*((3 + 2*curva*d0a)*d0b + 
            curvb*(4*pow(d0a,2) + 16*curva*pow(d0a,3) + pow(d0b,2) + 
               54*curva*d0a*pow(d0b,2)))*sin(phi0a) + 
         d0a*(-1 + curva*d0a)*sin(4*phi0a - 5*phi0b) + 
         d0b*sin(3*phi0a - 4*phi0b) - 
         4*curva*d0a*d0b*sin(3*phi0a - 4*phi0b) - 
         curvb*pow(d0b,2)*sin(3*phi0a - 4*phi0b) + 
         4*curva*curvb*d0a*pow(d0b,2)*sin(3*phi0a - 4*phi0b) - 
         d0b*sin(5*phi0a - 4*phi0b) + 
         curvb*pow(d0b,2)*sin(5*phi0a - 4*phi0b) + 
         4*d0a*sin(2*phi0a - 3*phi0b) + 
         4*curvb*d0a*d0b*sin(2*phi0a - 3*phi0b) - 
         20*curva*curvb*pow(d0a,2)*d0b*sin(2*phi0a - 3*phi0b) + 
         4*curva*pow(d0b,2)*sin(2*phi0a - 3*phi0b) - 
         8*curva*curvb*pow(d0b,3)*sin(2*phi0a - 3*phi0b) + 
         d0a*sin(4*phi0a - 3*phi0b) - 
         curva*pow(d0a,2)*sin(4*phi0a - 3*phi0b) - 
         4*curvb*d0a*d0b*sin(4*phi0a - 3*phi0b) + 
         4*curva*curvb*pow(d0a,2)*d0b*sin(4*phi0a - 3*phi0b) - 
         4*curvb*pow(d0a,2)*sin(phi0a - 2*phi0b) + 
         24*curva*curvb*pow(d0a,3)*sin(phi0a - 2*phi0b) - 
         4*d0b*sin(phi0a - 2*phi0b) + 4*curva*d0a*d0b*sin(phi0a - 2*phi0b) + 
         60*curva*curvb*d0a*pow(d0b,2)*sin(phi0a - 2*phi0b) + 
         4*curvb*pow(d0a,2)*sin(3*phi0a - 2*phi0b) - 
         8*curva*curvb*pow(d0a,3)*sin(3*phi0a - 2*phi0b) + 
         4*d0b*sin(3*phi0a - 2*phi0b) + 
         4*curva*d0a*d0b*sin(3*phi0a - 2*phi0b) - 
         20*curva*curvb*d0a*pow(d0b,2)*sin(3*phi0a - 2*phi0b) - 
         4*d0a*sin(2*phi0a - phi0b) + 4*curvb*d0a*d0b*sin(2*phi0a - phi0b) + 
         60*curva*curvb*pow(d0a,2)*d0b*sin(2*phi0a - phi0b) - 
         4*curva*pow(d0b,2)*sin(2*phi0a - phi0b) + 
         24*curva*curvb*pow(d0b,3)*sin(2*phi0a - phi0b) + 
         6*d0a*sin(phi0b) + 2*curva*pow(d0a,2)*sin(phi0b) + 
         4*curvb*d0a*d0b*sin(phi0b) + 
         108*curva*curvb*pow(d0a,2)*d0b*sin(phi0b) + 
         8*curva*pow(d0b,2)*sin(phi0b) + 
         32*curva*curvb*pow(d0b,3)*sin(phi0b)))/16.;
}

double BigNTuple::ysol2( double curva, double d0a, double phi0a,
			 double curvb, double d0b, double phi0b )
{
    return
   (pow(sin(phi0a - phi0b),-5)*
      (-4*curvb*(-5 - 4*curvb*d0b + 
           2*pow(curvb,2)*(4*pow(d0a,2) + pow(d0b,2)) + 
           2*curva*d0a*(5 + 12*curvb*d0b + 
              pow(curvb,2)*(16*pow(d0a,2) + 54*pow(d0b,2))))*sin(phi0a)\
         - curva*pow(1 + 2*curvb*d0b,2)*sin(8*phi0a - 7*phi0b) + 
        curvb*sin(5*phi0a - 6*phi0b) + 
        2*pow(curvb,2)*d0b*sin(5*phi0a - 6*phi0b) - 
        curvb*sin(7*phi0a - 6*phi0b) + 
        4*curva*curvb*d0a*sin(7*phi0a - 6*phi0b) - 
        2*pow(curvb,2)*d0b*sin(7*phi0a - 6*phi0b) + 
        8*curva*pow(curvb,2)*d0a*d0b*sin(7*phi0a - 6*phi0b) + 
        curva*sin(4*phi0a - 5*phi0b) + 6*curva*sin(6*phi0a - 5*phi0b) + 
        4*pow(curvb,2)*d0a*sin(6*phi0a - 5*phi0b) - 
        4*curva*pow(curvb,2)*pow(d0a,2)*sin(6*phi0a - 5*phi0b) + 
        20*curva*curvb*d0b*sin(6*phi0a - 5*phi0b) + 
        20*curva*pow(curvb,2)*pow(d0b,2)*sin(6*phi0a - 5*phi0b) - 
        6*curvb*sin(3*phi0a - 4*phi0b) + 
        4*curva*curvb*d0a*sin(3*phi0a - 4*phi0b) - 
        8*pow(curvb,2)*d0b*sin(3*phi0a - 4*phi0b) - 
        8*curva*pow(curvb,2)*d0a*d0b*sin(3*phi0a - 4*phi0b) - 
        4*pow(curvb,3)*pow(d0b,2)*sin(3*phi0a - 4*phi0b) + 
        16*curva*pow(curvb,3)*d0a*pow(d0b,2)*sin(3*phi0a - 4*phi0b) + 
        6*curvb*sin(5*phi0a - 4*phi0b) - 
        20*curva*curvb*d0a*sin(5*phi0a - 4*phi0b) + 
        8*pow(curvb,2)*d0b*sin(5*phi0a - 4*phi0b) - 
        40*curva*pow(curvb,2)*d0a*d0b*sin(5*phi0a - 4*phi0b) + 
        4*pow(curvb,3)*pow(d0b,2)*sin(5*phi0a - 4*phi0b) - 
        6*curva*sin(2*phi0a - 3*phi0b) - 
        4*pow(curvb,2)*d0a*sin(2*phi0a - 3*phi0b) + 
        20*curva*pow(curvb,2)*pow(d0a,2)*sin(2*phi0a - 3*phi0b) - 
        4*curva*curvb*d0b*sin(2*phi0a - 3*phi0b) + 
        16*pow(curvb,3)*d0a*d0b*sin(2*phi0a - 3*phi0b) - 
        80*curva*pow(curvb,3)*pow(d0a,2)*d0b*sin(2*phi0a - 3*phi0b) + 
        12*curva*pow(curvb,2)*pow(d0b,2)*sin(2*phi0a - 3*phi0b) - 
        32*curva*pow(curvb,3)*pow(d0b,3)*sin(2*phi0a - 3*phi0b) - 
        15*curva*sin(4*phi0a - 3*phi0b) - 
        16*pow(curvb,2)*d0a*sin(4*phi0a - 3*phi0b) + 
        16*curva*pow(curvb,2)*pow(d0a,2)*sin(4*phi0a - 3*phi0b) - 
        40*curva*curvb*d0b*sin(4*phi0a - 3*phi0b) - 
        16*pow(curvb,3)*d0a*d0b*sin(4*phi0a - 3*phi0b) + 
        16*curva*pow(curvb,3)*pow(d0a,2)*d0b*sin(4*phi0a - 3*phi0b) - 
        40*curva*pow(curvb,2)*pow(d0b,2)*sin(4*phi0a - 3*phi0b) + 
        15*curvb*sin(phi0a - 2*phi0b) - 
        20*curva*curvb*d0a*sin(phi0a - 2*phi0b) - 
        16*pow(curvb,3)*pow(d0a,2)*sin(phi0a - 2*phi0b) + 
        96*curva*pow(curvb,3)*pow(d0a,3)*sin(phi0a - 2*phi0b) + 
        14*pow(curvb,2)*d0b*sin(phi0a - 2*phi0b) - 
        24*curva*pow(curvb,2)*d0a*d0b*sin(phi0a - 2*phi0b) + 
        240*curva*pow(curvb,3)*d0a*pow(d0b,2)*sin(phi0a - 2*phi0b) - 
        15*curvb*sin(3*phi0a - 2*phi0b) + 
        40*curva*curvb*d0a*sin(3*phi0a - 2*phi0b) + 
        16*pow(curvb,3)*pow(d0a,2)*sin(3*phi0a - 2*phi0b) - 
        32*curva*pow(curvb,3)*pow(d0a,3)*sin(3*phi0a - 2*phi0b) - 
        14*pow(curvb,2)*d0b*sin(3*phi0a - 2*phi0b) + 
        96*curva*pow(curvb,2)*d0a*d0b*sin(3*phi0a - 2*phi0b) - 
        80*curva*pow(curvb,3)*d0a*pow(d0b,2)*sin(3*phi0a - 2*phi0b) + 
        20*curva*sin(2*phi0a - phi0b) + 
        24*pow(curvb,2)*d0a*sin(2*phi0a - phi0b) - 
        40*curva*pow(curvb,2)*pow(d0a,2)*sin(2*phi0a - phi0b) + 
        40*curva*curvb*d0b*sin(2*phi0a - phi0b) + 
        16*pow(curvb,3)*d0a*d0b*sin(2*phi0a - phi0b) + 
        240*curva*pow(curvb,3)*pow(d0a,2)*d0b*sin(2*phi0a - phi0b) + 
        24*curva*pow(curvb,2)*pow(d0b,2)*sin(2*phi0a - phi0b) + 
        96*curva*pow(curvb,3)*pow(d0b,3)*sin(2*phi0a - phi0b) - 
        15*curva*sin(phi0b) - 16*pow(curvb,2)*d0a*sin(phi0b) + 
        48*curva*pow(curvb,2)*pow(d0a,2)*sin(phi0b) - 
        20*curva*curvb*d0b*sin(phi0b) + 
        16*pow(curvb,3)*d0a*d0b*sin(phi0b) + 
        432*curva*pow(curvb,3)*pow(d0a,2)*d0b*sin(phi0b) + 
        12*curva*pow(curvb,2)*pow(d0b,2)*sin(phi0b) + 
        128*curva*pow(curvb,3)*pow(d0b,3)*sin(phi0b)))/
    (64.*pow(curvb,2));
}

double BigNTuple::dxsol1dd0a( double curva, double d0a, double phi0a,
			      double curvb, double d0b, double phi0b )
{
    return
   ((4*(curva*d0b + curvb*(4*d0a + 24*curva*pow(d0a,2) + 
              27*curva*pow(d0b,2)))*cos(phi0a) + 
        (-1 + 2*curva*d0a)*cos(4*phi0a - 5*phi0b) - 
        4*curva*d0b*cos(3*phi0a - 4*phi0b) + 
        4*curva*curvb*pow(d0b,2)*cos(3*phi0a - 4*phi0b) + 
        4*cos(2*phi0a - 3*phi0b) + 4*curvb*d0b*cos(2*phi0a - 3*phi0b) - 
        40*curva*curvb*d0a*d0b*cos(2*phi0a - 3*phi0b) - 
        cos(4*phi0a - 3*phi0b) + 2*curva*d0a*cos(4*phi0a - 3*phi0b) + 
        4*curvb*d0b*cos(4*phi0a - 3*phi0b) - 
        8*curva*curvb*d0a*d0b*cos(4*phi0a - 3*phi0b) - 
        8*curvb*d0a*cos(phi0a - 2*phi0b) + 
        72*curva*curvb*pow(d0a,2)*cos(phi0a - 2*phi0b) + 
        4*curva*d0b*cos(phi0a - 2*phi0b) + 
        60*curva*curvb*pow(d0b,2)*cos(phi0a - 2*phi0b) - 
        8*curvb*d0a*cos(3*phi0a - 2*phi0b) + 
        24*curva*curvb*pow(d0a,2)*cos(3*phi0a - 2*phi0b) - 
        4*curva*d0b*cos(3*phi0a - 2*phi0b) + 
        20*curva*curvb*pow(d0b,2)*cos(3*phi0a - 2*phi0b) + 
        4*cos(2*phi0a - phi0b) - 4*curvb*d0b*cos(2*phi0a - phi0b) - 
        120*curva*curvb*d0a*d0b*cos(2*phi0a - phi0b) - 6*cos(phi0b) - 
        4*curva*d0a*cos(phi0b) - 4*curvb*d0b*cos(phi0b) - 
        216*curva*curvb*d0a*d0b*cos(phi0b))*pow(sin(phi0a - phi0b),-5))/16.;
}

double BigNTuple::dxsol1dd0b( double curva, double d0a, double phi0a,
			      double curvb, double d0b, double phi0b )
{
    return
   (((6 + 4*curvb*d0b + 4*curva*(d0a + 54*curvb*d0a*d0b))*cos(phi0a) + 
        (-1 + 4*curva*d0a)*(-1 + 2*curvb*d0b)*cos(3*phi0a - 4*phi0b) + 
        cos(5*phi0a - 4*phi0b) - 2*curvb*d0b*cos(5*phi0a - 4*phi0b) + 
        4*curvb*d0a*cos(2*phi0a - 3*phi0b) - 
        20*curva*curvb*pow(d0a,2)*cos(2*phi0a - 3*phi0b) + 
        8*curva*d0b*cos(2*phi0a - 3*phi0b) - 
        24*curva*curvb*pow(d0b,2)*cos(2*phi0a - 3*phi0b) + 
        4*curvb*d0a*cos(4*phi0a - 3*phi0b) - 
        4*curva*curvb*pow(d0a,2)*cos(4*phi0a - 3*phi0b) - 
        4*cos(phi0a - 2*phi0b) + 4*curva*d0a*cos(phi0a - 2*phi0b) + 
        120*curva*curvb*d0a*d0b*cos(phi0a - 2*phi0b) - 
        4*cos(3*phi0a - 2*phi0b) - 4*curva*d0a*cos(3*phi0a - 2*phi0b) + 
        40*curva*curvb*d0a*d0b*cos(3*phi0a - 2*phi0b) - 
        4*curvb*d0a*cos(2*phi0a - phi0b) - 
        60*curva*curvb*pow(d0a,2)*cos(2*phi0a - phi0b) + 
        8*curva*d0b*cos(2*phi0a - phi0b) - 
        72*curva*curvb*pow(d0b,2)*cos(2*phi0a - phi0b) - 
        4*curvb*d0a*cos(phi0b) - 108*curva*curvb*pow(d0a,2)*cos(phi0b) - 
        16*curva*d0b*cos(phi0b) - 96*curva*curvb*pow(d0b,2)*cos(phi0b))*
      pow(sin(phi0a - phi0b),-5))/16.;
}

double BigNTuple::dxsol1dphi0a( double curva, double d0a, double phi0a,
				double curvb, double d0b, double phi0b )
{
    return
   -((-2*(d0a + 24*curvb*d0a*d0b + 2*curva*pow(d0b,2)*(3 + 82*curvb*d0b) + 
            5*pow(d0a,2)*(curva + 96*curva*curvb*d0b))*cos(phi0a) + 
         d0a*(-1 + curva*d0a)*cos(5*phi0a - 6*phi0b) + 
         2*d0b*cos(4*phi0a - 5*phi0b) - 
         8*curva*d0a*d0b*cos(4*phi0a - 5*phi0b) - 
         2*curvb*pow(d0b,2)*cos(4*phi0a - 5*phi0b) + 
         8*curva*curvb*d0a*pow(d0b,2)*cos(4*phi0a - 5*phi0b) + 
         3*d0a*cos(3*phi0a - 4*phi0b) + 
         9*curva*pow(d0a,2)*cos(3*phi0a - 4*phi0b) + 
         12*curvb*d0a*d0b*cos(3*phi0a - 4*phi0b) - 
         60*curva*curvb*pow(d0a,2)*d0b*cos(3*phi0a - 4*phi0b) + 
         12*curva*pow(d0b,2)*cos(3*phi0a - 4*phi0b) - 
         24*curva*curvb*pow(d0b,3)*cos(3*phi0a - 4*phi0b) - 
         d0a*cos(5*phi0a - 4*phi0b) + 
         curva*pow(d0a,2)*cos(5*phi0a - 4*phi0b) + 
         4*curvb*d0a*d0b*cos(5*phi0a - 4*phi0b) - 
         4*curva*curvb*pow(d0a,2)*d0b*cos(5*phi0a - 4*phi0b) - 
         16*curvb*pow(d0a,2)*cos(2*phi0a - 3*phi0b) + 
         96*curva*curvb*pow(d0a,3)*cos(2*phi0a - 3*phi0b) - 
         8*d0b*cos(2*phi0a - 3*phi0b) - 
         16*curva*d0a*d0b*cos(2*phi0a - 3*phi0b) - 
         8*curvb*pow(d0b,2)*cos(2*phi0a - 3*phi0b) + 
         272*curva*curvb*d0a*pow(d0b,2)*cos(2*phi0a - 3*phi0b) - 
         8*curvb*pow(d0a,2)*cos(4*phi0a - 3*phi0b) + 
         16*curva*curvb*pow(d0a,3)*cos(4*phi0a - 3*phi0b) + 
         2*d0b*cos(4*phi0a - 3*phi0b) - 
         8*curva*d0a*d0b*cos(4*phi0a - 3*phi0b) - 
         10*curvb*pow(d0b,2)*cos(4*phi0a - 3*phi0b) + 
         40*curva*curvb*d0a*pow(d0b,2)*cos(4*phi0a - 3*phi0b) - 
         2*d0a*cos(phi0a - 2*phi0b) - 
         10*curva*pow(d0a,2)*cos(phi0a - 2*phi0b) + 
         8*curvb*d0a*d0b*cos(phi0a - 2*phi0b) - 
         680*curva*curvb*pow(d0a,2)*d0b*cos(phi0a - 2*phi0b) - 
         12*curva*pow(d0b,2)*cos(phi0a - 2*phi0b) - 
         216*curva*curvb*pow(d0b,3)*cos(phi0a - 2*phi0b) + 
         3*d0a*cos(3*phi0a - 2*phi0b) + 
         9*curva*pow(d0a,2)*cos(3*phi0a - 2*phi0b) + 
         24*curvb*d0a*d0b*cos(3*phi0a - 2*phi0b) - 
         216*curva*curvb*pow(d0a,2)*d0b*cos(3*phi0a - 2*phi0b) + 
         12*curva*pow(d0b,2)*cos(3*phi0a - 2*phi0b) - 
         72*curva*curvb*pow(d0b,3)*cos(3*phi0a - 2*phi0b) + 
         192*curva*curvb*pow(d0a,3)*cos(2*phi0a - phi0b) - 
         8*d0b*cos(2*phi0a - phi0b) - 16*curva*d0a*d0b*cos(2*phi0a - phi0b) + 
         8*curvb*pow(d0b,2)*cos(2*phi0a - phi0b) + 
         592*curva*curvb*d0a*pow(d0b,2)*cos(2*phi0a - phi0b) + 
         24*curvb*pow(d0a,2)*cos(phi0b) + 
         336*curva*curvb*pow(d0a,3)*cos(phi0b) + 12*d0b*cos(phi0b) + 
         48*curva*d0a*d0b*cos(phi0b) + 12*curvb*pow(d0b,2)*cos(phi0b) + 
         1008*curva*curvb*d0a*pow(d0b,2)*cos(phi0b))*
       pow(sin(phi0a - phi0b),-6))/32.;
}

double BigNTuple::dxsol1dphi0b( double curva, double d0a, double phi0a,
				double curvb, double d0b, double phi0b )
{
    return
   ((-12*(d0a + 4*curvb*d0a*d0b + 2*curva*pow(d0b,2)*(1 + 14*curvb*d0b) + 
           pow(d0a,2)*(curva + 84*curva*curvb*d0b))*cos(phi0a) + 
        (-1 + 4*curva*d0a)*d0b*(-1 + curvb*d0b)*cos(4*phi0a - 5*phi0b) + 
        d0b*cos(6*phi0a - 5*phi0b) - 
        curvb*pow(d0b,2)*cos(6*phi0a - 5*phi0b) - 
        2*d0a*cos(3*phi0a - 4*phi0b) + 
        10*curva*pow(d0a,2)*cos(3*phi0a - 4*phi0b) + 
        8*curvb*d0a*d0b*cos(3*phi0a - 4*phi0b) - 
        40*curva*curvb*pow(d0a,2)*d0b*cos(3*phi0a - 4*phi0b) + 
        8*curva*pow(d0b,2)*cos(3*phi0a - 4*phi0b) - 
        16*curva*curvb*pow(d0b,3)*cos(3*phi0a - 4*phi0b) - 
        2*d0a*cos(5*phi0a - 4*phi0b) + 
        2*curva*pow(d0a,2)*cos(5*phi0a - 4*phi0b) + 
        8*curvb*d0a*d0b*cos(5*phi0a - 4*phi0b) - 
        8*curva*curvb*pow(d0a,2)*d0b*cos(5*phi0a - 4*phi0b) - 
        12*curvb*pow(d0a,2)*cos(2*phi0a - 3*phi0b) + 
        72*curva*curvb*pow(d0a,3)*cos(2*phi0a - 3*phi0b) - 
        3*d0b*cos(2*phi0a - 3*phi0b) - 
        24*curva*d0a*d0b*cos(2*phi0a - 3*phi0b) - 
        9*curvb*pow(d0b,2)*cos(2*phi0a - 3*phi0b) + 
        216*curva*curvb*d0a*pow(d0b,2)*cos(2*phi0a - 3*phi0b) - 
        12*curvb*pow(d0a,2)*cos(4*phi0a - 3*phi0b) + 
        24*curva*curvb*pow(d0a,3)*cos(4*phi0a - 3*phi0b) - 
        3*d0b*cos(4*phi0a - 3*phi0b) - 
        12*curva*d0a*d0b*cos(4*phi0a - 3*phi0b) - 
        9*curvb*pow(d0b,2)*cos(4*phi0a - 3*phi0b) + 
        60*curva*curvb*d0a*pow(d0b,2)*cos(4*phi0a - 3*phi0b) + 
        8*d0a*cos(phi0a - 2*phi0b) - 
        8*curva*pow(d0a,2)*cos(phi0a - 2*phi0b) + 
        16*curvb*d0a*d0b*cos(phi0a - 2*phi0b) - 
        592*curva*curvb*pow(d0a,2)*d0b*cos(phi0a - 2*phi0b) - 
        192*curva*curvb*pow(d0b,3)*cos(phi0a - 2*phi0b) + 
        8*d0a*cos(3*phi0a - 2*phi0b) + 
        8*curva*pow(d0a,2)*cos(3*phi0a - 2*phi0b) + 
        16*curvb*d0a*d0b*cos(3*phi0a - 2*phi0b) - 
        272*curva*curvb*pow(d0a,2)*d0b*cos(3*phi0a - 2*phi0b) + 
        16*curva*pow(d0b,2)*cos(3*phi0a - 2*phi0b) - 
        96*curva*curvb*pow(d0b,3)*cos(3*phi0a - 2*phi0b) + 
        12*curvb*pow(d0a,2)*cos(2*phi0a - phi0b) + 
        216*curva*curvb*pow(d0a,3)*cos(2*phi0a - phi0b) + 
        2*d0b*cos(2*phi0a - phi0b) - 8*curva*d0a*d0b*cos(2*phi0a - phi0b) + 
        10*curvb*pow(d0b,2)*cos(2*phi0a - phi0b) + 
        680*curva*curvb*d0a*pow(d0b,2)*cos(2*phi0a - phi0b) + 
        12*curvb*pow(d0a,2)*cos(phi0b) + 
        328*curva*curvb*pow(d0a,3)*cos(phi0b) + 2*d0b*cos(phi0b) + 
        48*curva*d0a*d0b*cos(phi0b) + 10*curvb*pow(d0b,2)*cos(phi0b) + 
        960*curva*curvb*d0a*pow(d0b,2)*cos(phi0b))*
      pow(sin(phi0a - phi0b),-6))/32.;
}

double BigNTuple::dxsol1dcurva( double curva, double d0a, double phi0a,
				double curvb, double d0b, double phi0b )
{
    return
   ((-d0b + d0a*cos(phi0a - phi0b))*
      (-(d0a*(1 + 40*curvb*d0b)*cos(phi0a)) + d0a*cos(3*phi0a - 4*phi0b) - 
        2*d0b*cos(2*phi0a - 3*phi0b) + 
        4*curvb*pow(d0b,2)*cos(2*phi0a - 3*phi0b) - 
        d0a*cos(phi0a - 2*phi0b) - 20*curvb*d0a*d0b*cos(phi0a - 2*phi0b) + 
        d0a*cos(3*phi0a - 2*phi0b) - 4*curvb*d0a*d0b*cos(3*phi0a - 2*phi0b) + 
        8*curvb*pow(d0a,2)*cos(2*phi0a - phi0b) - 
        2*d0b*cos(2*phi0a - phi0b) + 
        12*curvb*pow(d0b,2)*cos(2*phi0a - phi0b) + 
        24*curvb*pow(d0a,2)*cos(phi0b) + 4*d0b*cos(phi0b) + 
        16*curvb*pow(d0b,2)*cos(phi0b))*pow(sin(phi0a - phi0b),-5))/8.;
}

double BigNTuple::dxsol1dcurvb( double curva, double d0a, double phi0a,
				double curvb, double d0b, double phi0b )
{
    return
   ((d0a - d0b*cos(phi0a - phi0b))*
      (4*(d0a + 4*curva*pow(d0a,2) + 6*curva*pow(d0b,2))*cos(phi0a) + 
        (d0b - 4*curva*d0a*d0b)*cos(2*phi0a - 3*phi0b) + 
        d0b*cos(4*phi0a - 3*phi0b) - 2*d0a*cos(phi0a - 2*phi0b) + 
        12*curva*pow(d0a,2)*cos(phi0a - 2*phi0b) + 
        8*curva*pow(d0b,2)*cos(phi0a - 2*phi0b) - 
        2*d0a*cos(3*phi0a - 2*phi0b) + 
        4*curva*pow(d0a,2)*cos(3*phi0a - 2*phi0b) - 
        d0b*cos(2*phi0a - phi0b) - 20*curva*d0a*d0b*cos(2*phi0a - phi0b) - 
        d0b*cos(phi0b) - 40*curva*d0a*d0b*cos(phi0b))*
      pow(sin(phi0a - phi0b),-5))/8.;
}

double BigNTuple::dxsol2dd0a( double curva, double d0a, double phi0a,
			      double curvb, double d0b, double phi0b )
{
    return
   ((-2*(8*pow(curvb,2)*d0a + 
           curva*(5 + 12*curvb*d0b + 
              pow(curvb,2)*(48*pow(d0a,2) + 54*pow(d0b,2))))*cos(phi0a)\
         + curva*(1 + 2*curvb*d0b)*cos(7*phi0a - 6*phi0b) + 
        curvb*cos(6*phi0a - 5*phi0b) - 
        2*curva*curvb*d0a*cos(6*phi0a - 5*phi0b) - 
        curva*cos(3*phi0a - 4*phi0b) + 
        2*curva*curvb*d0b*cos(3*phi0a - 4*phi0b) - 
        4*curva*pow(curvb,2)*pow(d0b,2)*cos(3*phi0a - 4*phi0b) - 
        5*curva*cos(5*phi0a - 4*phi0b) - 
        10*curva*curvb*d0b*cos(5*phi0a - 4*phi0b) + 
        curvb*cos(2*phi0a - 3*phi0b) - 
        10*curva*curvb*d0a*cos(2*phi0a - 3*phi0b) - 
        4*pow(curvb,2)*d0b*cos(2*phi0a - 3*phi0b) + 
        40*curva*pow(curvb,2)*d0a*d0b*cos(2*phi0a - 3*phi0b) - 
        4*curvb*cos(4*phi0a - 3*phi0b) + 
        8*curva*curvb*d0a*cos(4*phi0a - 3*phi0b) - 
        4*pow(curvb,2)*d0b*cos(4*phi0a - 3*phi0b) + 
        8*curva*pow(curvb,2)*d0a*d0b*cos(4*phi0a - 3*phi0b) + 
        5*curva*cos(phi0a - 2*phi0b) + 
        8*pow(curvb,2)*d0a*cos(phi0a - 2*phi0b) - 
        72*curva*pow(curvb,2)*pow(d0a,2)*cos(phi0a - 2*phi0b) + 
        6*curva*curvb*d0b*cos(phi0a - 2*phi0b) - 
        60*curva*pow(curvb,2)*pow(d0b,2)*cos(phi0a - 2*phi0b) + 
        10*curva*cos(3*phi0a - 2*phi0b) + 
        8*pow(curvb,2)*d0a*cos(3*phi0a - 2*phi0b) - 
        24*curva*pow(curvb,2)*pow(d0a,2)*cos(3*phi0a - 2*phi0b) + 
        24*curva*curvb*d0b*cos(3*phi0a - 2*phi0b) - 
        20*curva*pow(curvb,2)*pow(d0b,2)*cos(3*phi0a - 2*phi0b) + 
        6*curvb*cos(2*phi0a - phi0b) - 
        20*curva*curvb*d0a*cos(2*phi0a - phi0b) + 
        4*pow(curvb,2)*d0b*cos(2*phi0a - phi0b) + 
        120*curva*pow(curvb,2)*d0a*d0b*cos(2*phi0a - phi0b) - 
        4*curvb*cos(phi0b) + 24*curva*curvb*d0a*cos(phi0b) + 
        4*pow(curvb,2)*d0b*cos(phi0b) + 
        216*curva*pow(curvb,2)*d0a*d0b*cos(phi0b))*
      pow(sin(phi0a - phi0b),-5))/(16.*curvb);
}

double BigNTuple::dxsol2dd0b( double curva, double d0a, double phi0a,
			      double curvb, double d0b, double phi0b )
{
    return
   ((-8*curvb*(-1 + curvb*d0b + 6*curva*(d0a + 9*curvb*d0a*d0b))*cos(phi0a) - 
        2*curva*(1 + 2*curvb*d0b)*cos(8*phi0a - 7*phi0b) - 
        curvb*cos(5*phi0a - 6*phi0b) - curvb*cos(7*phi0a - 6*phi0b) + 
        4*curva*curvb*d0a*cos(7*phi0a - 6*phi0b) + 
        10*curva*cos(6*phi0a - 5*phi0b) + 
        20*curva*curvb*d0b*cos(6*phi0a - 5*phi0b) + 
        4*curvb*cos(3*phi0a - 4*phi0b) + 
        4*curva*curvb*d0a*cos(3*phi0a - 4*phi0b) + 
        4*pow(curvb,2)*d0b*cos(3*phi0a - 4*phi0b) - 
        16*curva*pow(curvb,2)*d0a*d0b*cos(3*phi0a - 4*phi0b) + 
        4*curvb*cos(5*phi0a - 4*phi0b) - 
        20*curva*curvb*d0a*cos(5*phi0a - 4*phi0b) + 
        4*pow(curvb,2)*d0b*cos(5*phi0a - 4*phi0b) + 
        2*curva*cos(2*phi0a - 3*phi0b) - 
        8*pow(curvb,2)*d0a*cos(2*phi0a - 3*phi0b) + 
        40*curva*pow(curvb,2)*pow(d0a,2)*cos(2*phi0a - 3*phi0b) - 
        12*curva*curvb*d0b*cos(2*phi0a - 3*phi0b) + 
        48*curva*pow(curvb,2)*pow(d0b,2)*cos(2*phi0a - 3*phi0b) - 
        20*curva*cos(4*phi0a - 3*phi0b) - 
        8*pow(curvb,2)*d0a*cos(4*phi0a - 3*phi0b) + 
        8*curva*pow(curvb,2)*pow(d0a,2)*cos(4*phi0a - 3*phi0b) - 
        40*curva*curvb*d0b*cos(4*phi0a - 3*phi0b) - 
        7*curvb*cos(phi0a - 2*phi0b) + 
        12*curva*curvb*d0a*cos(phi0a - 2*phi0b) - 
        240*curva*pow(curvb,2)*d0a*d0b*cos(phi0a - 2*phi0b) - 
        7*curvb*cos(3*phi0a - 2*phi0b) + 
        48*curva*curvb*d0a*cos(3*phi0a - 2*phi0b) - 
        80*curva*pow(curvb,2)*d0a*d0b*cos(3*phi0a - 2*phi0b) + 
        20*curva*cos(2*phi0a - phi0b) + 
        8*pow(curvb,2)*d0a*cos(2*phi0a - phi0b) + 
        120*curva*pow(curvb,2)*pow(d0a,2)*cos(2*phi0a - phi0b) + 
        24*curva*curvb*d0b*cos(2*phi0a - phi0b) + 
        144*curva*pow(curvb,2)*pow(d0b,2)*cos(2*phi0a - phi0b) - 
        10*curva*cos(phi0b) + 8*pow(curvb,2)*d0a*cos(phi0b) + 
        216*curva*pow(curvb,2)*pow(d0a,2)*cos(phi0b) + 
        12*curva*curvb*d0b*cos(phi0b) + 
        192*curva*pow(curvb,2)*pow(d0b,2)*cos(phi0b))*
      pow(sin(phi0a - phi0b),-5))/(32.*curvb);
}

double BigNTuple::dxsol2dphi0a( double curva, double d0a, double phi0a,
				double curvb, double d0b, double phi0b )
{
    return
   ((-((8*pow(curvb,2)*d0a*(11 + 24*curvb*d0b) + 
             curva*(65 + 180*curvb*d0b + 
                pow(curvb,2)*(-40*pow(d0a,2) + 228*pow(d0b,2)) + 
                32*pow(curvb,3)*(120*pow(d0a,2)*d0b + 41*pow(d0b,3))))*
           cos(phi0a)) - 3*curva*pow(1 + 2*curvb*d0b,2)*
         cos(9*phi0a - 8*phi0b) - 2*curvb*cos(8*phi0a - 7*phi0b) + 
        8*curva*curvb*d0a*cos(8*phi0a - 7*phi0b) - 
        4*pow(curvb,2)*d0b*cos(8*phi0a - 7*phi0b) + 
        16*curva*pow(curvb,2)*d0a*d0b*cos(8*phi0a - 7*phi0b) + 
        curva*cos(5*phi0a - 6*phi0b) + 19*curva*cos(7*phi0a - 6*phi0b) + 
        4*pow(curvb,2)*d0a*cos(7*phi0a - 6*phi0b) - 
        4*curva*pow(curvb,2)*pow(d0a,2)*cos(7*phi0a - 6*phi0b) + 
        72*curva*curvb*d0b*cos(7*phi0a - 6*phi0b) + 
        72*curva*pow(curvb,2)*pow(d0b,2)*cos(7*phi0a - 6*phi0b) - 
        2*curvb*cos(4*phi0a - 5*phi0b) + 
        8*curva*curvb*d0a*cos(4*phi0a - 5*phi0b) + 
        4*pow(curvb,2)*d0b*cos(4*phi0a - 5*phi0b) - 
        16*curva*pow(curvb,2)*d0a*d0b*cos(4*phi0a - 5*phi0b) - 
        8*pow(curvb,3)*pow(d0b,2)*cos(4*phi0a - 5*phi0b) + 
        32*curva*pow(curvb,3)*d0a*pow(d0b,2)*cos(4*phi0a - 5*phi0b) + 
        12*curvb*cos(6*phi0a - 5*phi0b) - 
        48*curva*curvb*d0a*cos(6*phi0a - 5*phi0b) + 
        24*pow(curvb,2)*d0b*cos(6*phi0a - 5*phi0b) - 
        96*curva*pow(curvb,2)*d0a*d0b*cos(6*phi0a - 5*phi0b) - 
        9*curva*cos(3*phi0a - 4*phi0b) - 
        12*pow(curvb,2)*d0a*cos(3*phi0a - 4*phi0b) + 
        60*curva*pow(curvb,2)*pow(d0a,2)*cos(3*phi0a - 4*phi0b) - 
        12*curva*curvb*d0b*cos(3*phi0a - 4*phi0b) + 
        48*pow(curvb,3)*d0a*d0b*cos(3*phi0a - 4*phi0b) - 
        240*curva*pow(curvb,3)*pow(d0a,2)*d0b*cos(3*phi0a - 4*phi0b) + 
        36*curva*pow(curvb,2)*pow(d0b,2)*cos(3*phi0a - 4*phi0b) - 
        96*curva*pow(curvb,3)*pow(d0b,3)*cos(3*phi0a - 4*phi0b) - 
        51*curva*cos(5*phi0a - 4*phi0b) - 
        28*pow(curvb,2)*d0a*cos(5*phi0a - 4*phi0b) + 
        28*curva*pow(curvb,2)*pow(d0a,2)*cos(5*phi0a - 4*phi0b) - 
        180*curva*curvb*d0b*cos(5*phi0a - 4*phi0b) + 
        16*pow(curvb,3)*d0a*d0b*cos(5*phi0a - 4*phi0b) - 
        16*curva*pow(curvb,3)*pow(d0a,2)*d0b*cos(5*phi0a - 4*phi0b) - 
        180*curva*pow(curvb,2)*pow(d0b,2)*cos(5*phi0a - 4*phi0b) + 
        12*curvb*cos(2*phi0a - 3*phi0b) - 
        48*curva*curvb*d0a*cos(2*phi0a - 3*phi0b) - 
        64*pow(curvb,3)*pow(d0a,2)*cos(2*phi0a - 3*phi0b) + 
        384*curva*pow(curvb,3)*pow(d0a,3)*cos(2*phi0a - 3*phi0b) - 
        8*pow(curvb,2)*d0b*cos(2*phi0a - 3*phi0b) - 
        160*curva*pow(curvb,2)*d0a*d0b*cos(2*phi0a - 3*phi0b) - 
        32*pow(curvb,3)*pow(d0b,2)*cos(2*phi0a - 3*phi0b) + 
        1088*curva*pow(curvb,3)*d0a*pow(d0b,2)*cos(2*phi0a - 3*phi0b) - 
        30*curvb*cos(4*phi0a - 3*phi0b) + 
        120*curva*curvb*d0a*cos(4*phi0a - 3*phi0b) - 
        32*pow(curvb,3)*pow(d0a,2)*cos(4*phi0a - 3*phi0b) + 
        64*curva*pow(curvb,3)*pow(d0a,3)*cos(4*phi0a - 3*phi0b) - 
        52*pow(curvb,2)*d0b*cos(4*phi0a - 3*phi0b) + 
        208*curva*pow(curvb,2)*d0a*d0b*cos(4*phi0a - 3*phi0b) - 
        40*pow(curvb,3)*pow(d0b,2)*cos(4*phi0a - 3*phi0b) + 
        160*curva*pow(curvb,3)*d0a*pow(d0b,2)*cos(4*phi0a - 3*phi0b) + 
        33*curva*cos(phi0a - 2*phi0b) + 
        52*pow(curvb,2)*d0a*cos(phi0a - 2*phi0b) - 
        100*curva*pow(curvb,2)*pow(d0a,2)*cos(phi0a - 2*phi0b) + 
        72*curva*curvb*d0b*cos(phi0a - 2*phi0b) + 
        32*pow(curvb,3)*d0a*d0b*cos(phi0a - 2*phi0b) - 
        2720*curva*pow(curvb,3)*pow(d0a,2)*d0b*cos(phi0a - 2*phi0b) + 
        24*curva*pow(curvb,2)*pow(d0b,2)*cos(phi0a - 2*phi0b) - 
        864*curva*pow(curvb,3)*pow(d0b,3)*cos(phi0a - 2*phi0b) + 
        75*curva*cos(3*phi0a - 2*phi0b) + 
        72*pow(curvb,2)*d0a*cos(3*phi0a - 2*phi0b) - 
        24*curva*pow(curvb,2)*pow(d0a,2)*cos(3*phi0a - 2*phi0b) + 
        240*curva*curvb*d0b*cos(3*phi0a - 2*phi0b) + 
        96*pow(curvb,3)*d0a*d0b*cos(3*phi0a - 2*phi0b) - 
        864*curva*pow(curvb,3)*pow(d0a,2)*d0b*cos(3*phi0a - 2*phi0b) + 
        288*curva*pow(curvb,2)*pow(d0b,2)*cos(3*phi0a - 2*phi0b) - 
        288*curva*pow(curvb,3)*pow(d0b,3)*cos(3*phi0a - 2*phi0b) + 
        40*curvb*cos(2*phi0a - phi0b) - 
        160*curva*curvb*d0a*cos(2*phi0a - phi0b) + 
        768*curva*pow(curvb,3)*pow(d0a,3)*cos(2*phi0a - phi0b) + 
        48*pow(curvb,2)*d0b*cos(2*phi0a - phi0b) - 
        384*curva*pow(curvb,2)*d0a*d0b*cos(2*phi0a - phi0b) + 
        32*pow(curvb,3)*pow(d0b,2)*cos(2*phi0a - phi0b) + 
        2368*curva*pow(curvb,3)*d0a*pow(d0b,2)*cos(2*phi0a - phi0b) - 
        30*curvb*cos(phi0b) + 120*curva*curvb*d0a*cos(phi0b) + 
        96*pow(curvb,3)*pow(d0a,2)*cos(phi0b) + 
        1344*curva*pow(curvb,3)*pow(d0a,3)*cos(phi0b) - 
        12*pow(curvb,2)*d0b*cos(phi0b) + 
        432*curva*pow(curvb,2)*d0a*d0b*cos(phi0b) + 
        48*pow(curvb,3)*pow(d0b,2)*cos(phi0b) + 
        4032*curva*pow(curvb,3)*d0a*pow(d0b,2)*cos(phi0b))*
      pow(sin(phi0a - phi0b),-6))/(128.*pow(curvb,2));
}

double BigNTuple::dxsol2dphi0b( double curva, double d0a, double phi0a,
				double curvb, double d0b, double phi0b )
{
    return
   ((6*(8*pow(curvb,2)*d0a*(1 + 4*curvb*d0b) + 
           curva*(5 + 20*curvb*d0b + 
              4*pow(curvb,2)*(2*pow(d0a,2) + 9*pow(d0b,2)) + 
              224*pow(curvb,3)*(3*pow(d0a,2)*d0b + pow(d0b,3))))*
         cos(phi0a) + 2*curva*pow(1 + 2*curvb*d0b,2)*
         cos(9*phi0a - 8*phi0b) + curvb*cos(6*phi0a - 7*phi0b) + 
        2*pow(curvb,2)*d0b*cos(6*phi0a - 7*phi0b) + 
        curvb*cos(8*phi0a - 7*phi0b) - 
        4*curva*curvb*d0a*cos(8*phi0a - 7*phi0b) + 
        2*pow(curvb,2)*d0b*cos(8*phi0a - 7*phi0b) - 
        8*curva*pow(curvb,2)*d0a*d0b*cos(8*phi0a - 7*phi0b) - 
        12*curva*cos(7*phi0a - 6*phi0b) - 
        48*curva*curvb*d0b*cos(7*phi0a - 6*phi0b) - 
        48*curva*pow(curvb,2)*pow(d0b,2)*cos(7*phi0a - 6*phi0b) - 
        5*curvb*cos(4*phi0a - 5*phi0b) - 
        4*curva*curvb*d0a*cos(4*phi0a - 5*phi0b) - 
        14*pow(curvb,2)*d0b*cos(4*phi0a - 5*phi0b) + 
        8*curva*pow(curvb,2)*d0a*d0b*cos(4*phi0a - 5*phi0b) + 
        4*pow(curvb,3)*pow(d0b,2)*cos(4*phi0a - 5*phi0b) - 
        16*curva*pow(curvb,3)*d0a*pow(d0b,2)*cos(4*phi0a - 5*phi0b) - 
        5*curvb*cos(6*phi0a - 5*phi0b) + 
        24*curva*curvb*d0a*cos(6*phi0a - 5*phi0b) - 
        14*pow(curvb,2)*d0b*cos(6*phi0a - 5*phi0b) + 
        48*curva*pow(curvb,2)*d0a*d0b*cos(6*phi0a - 5*phi0b) + 
        4*pow(curvb,3)*pow(d0b,2)*cos(6*phi0a - 5*phi0b) + 
        2*curva*cos(3*phi0a - 4*phi0b) + 
        8*pow(curvb,2)*d0a*cos(3*phi0a - 4*phi0b) - 
        40*curva*pow(curvb,2)*pow(d0a,2)*cos(3*phi0a - 4*phi0b) + 
        8*curva*curvb*d0b*cos(3*phi0a - 4*phi0b) - 
        32*pow(curvb,3)*d0a*d0b*cos(3*phi0a - 4*phi0b) + 
        160*curva*pow(curvb,3)*pow(d0a,2)*d0b*cos(3*phi0a - 4*phi0b) - 
        24*curva*pow(curvb,2)*pow(d0b,2)*cos(3*phi0a - 4*phi0b) + 
        64*curva*pow(curvb,3)*pow(d0b,3)*cos(3*phi0a - 4*phi0b) + 
        30*curva*cos(5*phi0a - 4*phi0b) + 
        8*pow(curvb,2)*d0a*cos(5*phi0a - 4*phi0b) - 
        8*curva*pow(curvb,2)*pow(d0a,2)*cos(5*phi0a - 4*phi0b) + 
        120*curva*curvb*d0b*cos(5*phi0a - 4*phi0b) - 
        32*pow(curvb,3)*d0a*d0b*cos(5*phi0a - 4*phi0b) + 
        32*curva*pow(curvb,3)*pow(d0a,2)*d0b*cos(5*phi0a - 4*phi0b) + 
        120*curva*pow(curvb,2)*pow(d0b,2)*cos(5*phi0a - 4*phi0b) + 
        9*curvb*cos(2*phi0a - 3*phi0b) + 
        24*curva*curvb*d0a*cos(2*phi0a - 3*phi0b) + 
        48*pow(curvb,3)*pow(d0a,2)*cos(2*phi0a - 3*phi0b) - 
        288*curva*pow(curvb,3)*pow(d0a,3)*cos(2*phi0a - 3*phi0b) + 
        30*pow(curvb,2)*d0b*cos(2*phi0a - 3*phi0b) + 
        144*curva*pow(curvb,2)*d0a*d0b*cos(2*phi0a - 3*phi0b) + 
        36*pow(curvb,3)*pow(d0b,2)*cos(2*phi0a - 3*phi0b) - 
        864*curva*pow(curvb,3)*d0a*pow(d0b,2)*cos(2*phi0a - 3*phi0b) + 
        9*curvb*cos(4*phi0a - 3*phi0b) - 
        60*curva*curvb*d0a*cos(4*phi0a - 3*phi0b) + 
        48*pow(curvb,3)*pow(d0a,2)*cos(4*phi0a - 3*phi0b) - 
        96*curva*pow(curvb,3)*pow(d0a,3)*cos(4*phi0a - 3*phi0b) + 
        30*pow(curvb,2)*d0b*cos(4*phi0a - 3*phi0b) - 
        72*curva*pow(curvb,2)*d0a*d0b*cos(4*phi0a - 3*phi0b) + 
        36*pow(curvb,3)*pow(d0b,2)*cos(4*phi0a - 3*phi0b) - 
        240*curva*pow(curvb,3)*d0a*pow(d0b,2)*cos(4*phi0a - 3*phi0b) - 
        12*curva*cos(phi0a - 2*phi0b) - 
        32*pow(curvb,2)*d0a*cos(phi0a - 2*phi0b) + 
        32*curva*pow(curvb,2)*pow(d0a,2)*cos(phi0a - 2*phi0b) - 
        48*curva*curvb*d0b*cos(phi0a - 2*phi0b) - 
        64*pow(curvb,3)*d0a*d0b*cos(phi0a - 2*phi0b) + 
        2368*curva*pow(curvb,3)*pow(d0a,2)*d0b*cos(phi0a - 2*phi0b) - 
        48*curva*pow(curvb,2)*pow(d0b,2)*cos(phi0a - 2*phi0b) + 
        768*curva*pow(curvb,3)*pow(d0b,3)*cos(phi0a - 2*phi0b) - 
        40*curva*cos(3*phi0a - 2*phi0b) - 
        32*pow(curvb,2)*d0a*cos(3*phi0a - 2*phi0b) - 
        32*curva*pow(curvb,2)*pow(d0a,2)*cos(3*phi0a - 2*phi0b) - 
        160*curva*curvb*d0b*cos(3*phi0a - 2*phi0b) - 
        64*pow(curvb,3)*d0a*d0b*cos(3*phi0a - 2*phi0b) + 
        1088*curva*pow(curvb,3)*pow(d0a,2)*d0b*cos(3*phi0a - 2*phi0b) - 
        224*curva*pow(curvb,2)*pow(d0b,2)*cos(3*phi0a - 2*phi0b) + 
        384*curva*pow(curvb,3)*pow(d0b,3)*cos(3*phi0a - 2*phi0b) - 
        5*curvb*cos(2*phi0a - phi0b) + 
        80*curva*curvb*d0a*cos(2*phi0a - phi0b) - 
        48*pow(curvb,3)*pow(d0a,2)*cos(2*phi0a - phi0b) - 
        864*curva*pow(curvb,3)*pow(d0a,3)*cos(2*phi0a - phi0b) - 
        18*pow(curvb,2)*d0b*cos(2*phi0a - phi0b) + 
        192*curva*pow(curvb,2)*d0a*d0b*cos(2*phi0a - phi0b) - 
        40*pow(curvb,3)*pow(d0b,2)*cos(2*phi0a - phi0b) - 
        2720*curva*pow(curvb,3)*d0a*pow(d0b,2)*cos(2*phi0a - phi0b) - 
        5*curvb*cos(phi0b) - 60*curva*curvb*d0a*cos(phi0b) - 
        48*pow(curvb,3)*pow(d0a,2)*cos(phi0b) - 
        1312*curva*pow(curvb,3)*pow(d0a,3)*cos(phi0b) - 
        18*pow(curvb,2)*d0b*cos(phi0b) - 
        312*curva*pow(curvb,2)*d0a*d0b*cos(phi0b) - 
        40*pow(curvb,3)*pow(d0b,2)*cos(phi0b) - 
        3840*curva*pow(curvb,3)*d0a*pow(d0b,2)*cos(phi0b))*
      pow(sin(phi0a - phi0b),-6))/(128.*pow(curvb,2));
}

double BigNTuple::dxsol2dcurva( double curva, double d0a, double phi0a,
				double curvb, double d0b, double phi0b )
{
    return
   -((8*curvb*d0a*(5 + 12*curvb*d0b + 
            pow(curvb,2)*(16*pow(d0a,2) + 54*pow(d0b,2)))*cos(phi0a) + 
         pow(1 + 2*curvb*d0b,2)*cos(8*phi0a - 7*phi0b) - 
         4*curvb*d0a*cos(7*phi0a - 6*phi0b) - 
         8*pow(curvb,2)*d0a*d0b*cos(7*phi0a - 6*phi0b) + 
         cos(4*phi0a - 5*phi0b) - 6*cos(6*phi0a - 5*phi0b) + 
         4*pow(curvb,2)*pow(d0a,2)*cos(6*phi0a - 5*phi0b) - 
         20*curvb*d0b*cos(6*phi0a - 5*phi0b) - 
         20*pow(curvb,2)*pow(d0b,2)*cos(6*phi0a - 5*phi0b) + 
         4*curvb*d0a*cos(3*phi0a - 4*phi0b) - 
         8*pow(curvb,2)*d0a*d0b*cos(3*phi0a - 4*phi0b) + 
         16*pow(curvb,3)*d0a*pow(d0b,2)*cos(3*phi0a - 4*phi0b) + 
         20*curvb*d0a*cos(5*phi0a - 4*phi0b) + 
         40*pow(curvb,2)*d0a*d0b*cos(5*phi0a - 4*phi0b) - 
         6*cos(2*phi0a - 3*phi0b) + 
         20*pow(curvb,2)*pow(d0a,2)*cos(2*phi0a - 3*phi0b) - 
         4*curvb*d0b*cos(2*phi0a - 3*phi0b) - 
         80*pow(curvb,3)*pow(d0a,2)*d0b*cos(2*phi0a - 3*phi0b) + 
         12*pow(curvb,2)*pow(d0b,2)*cos(2*phi0a - 3*phi0b) - 
         32*pow(curvb,3)*pow(d0b,3)*cos(2*phi0a - 3*phi0b) + 
         15*cos(4*phi0a - 3*phi0b) - 
         16*pow(curvb,2)*pow(d0a,2)*cos(4*phi0a - 3*phi0b) + 
         40*curvb*d0b*cos(4*phi0a - 3*phi0b) - 
         16*pow(curvb,3)*pow(d0a,2)*d0b*cos(4*phi0a - 3*phi0b) + 
         40*pow(curvb,2)*pow(d0b,2)*cos(4*phi0a - 3*phi0b) - 
         20*curvb*d0a*cos(phi0a - 2*phi0b) + 
         96*pow(curvb,3)*pow(d0a,3)*cos(phi0a - 2*phi0b) - 
         24*pow(curvb,2)*d0a*d0b*cos(phi0a - 2*phi0b) + 
         240*pow(curvb,3)*d0a*pow(d0b,2)*cos(phi0a - 2*phi0b) - 
         40*curvb*d0a*cos(3*phi0a - 2*phi0b) + 
         32*pow(curvb,3)*pow(d0a,3)*cos(3*phi0a - 2*phi0b) - 
         96*pow(curvb,2)*d0a*d0b*cos(3*phi0a - 2*phi0b) + 
         80*pow(curvb,3)*d0a*pow(d0b,2)*cos(3*phi0a - 2*phi0b) - 
         20*cos(2*phi0a - phi0b) + 
         40*pow(curvb,2)*pow(d0a,2)*cos(2*phi0a - phi0b) - 
         40*curvb*d0b*cos(2*phi0a - phi0b) - 
         240*pow(curvb,3)*pow(d0a,2)*d0b*cos(2*phi0a - phi0b) - 
         24*pow(curvb,2)*pow(d0b,2)*cos(2*phi0a - phi0b) - 
         96*pow(curvb,3)*pow(d0b,3)*cos(2*phi0a - phi0b) + 
         15*cos(phi0b) - 48*pow(curvb,2)*pow(d0a,2)*cos(phi0b) + 
         20*curvb*d0b*cos(phi0b) - 
         432*pow(curvb,3)*pow(d0a,2)*d0b*cos(phi0b) - 
         12*pow(curvb,2)*pow(d0b,2)*cos(phi0b) - 
         128*pow(curvb,3)*pow(d0b,3)*cos(phi0b))*
       pow(sin(phi0a - phi0b),-5))/(64.*pow(curvb,2));
}

double BigNTuple::dxsol2dcurvb( double curva, double d0a, double phi0a,
				double curvb, double d0b, double phi0b )
{
    return
   ((-4*curvb*(5 + 2*pow(curvb,2)*(4*pow(d0a,2) + pow(d0b,2)) + 
           2*curva*d0a*(-5 + pow(curvb,2)*
               (16*pow(d0a,2) + 54*pow(d0b,2))))*cos(phi0a) + 
        2*curva*(1 + 2*curvb*d0b)*cos(8*phi0a - 7*phi0b) + 
        curvb*cos(5*phi0a - 6*phi0b) + curvb*cos(7*phi0a - 6*phi0b) - 
        4*curva*curvb*d0a*cos(7*phi0a - 6*phi0b) + 
        2*curva*cos(4*phi0a - 5*phi0b) - 12*curva*cos(6*phi0a - 5*phi0b) - 
        20*curva*curvb*d0b*cos(6*phi0a - 5*phi0b) - 
        6*curvb*cos(3*phi0a - 4*phi0b) + 
        4*curva*curvb*d0a*cos(3*phi0a - 4*phi0b) + 
        4*pow(curvb,3)*pow(d0b,2)*cos(3*phi0a - 4*phi0b) - 
        16*curva*pow(curvb,3)*d0a*pow(d0b,2)*cos(3*phi0a - 4*phi0b) - 
        6*curvb*cos(5*phi0a - 4*phi0b) + 
        20*curva*curvb*d0a*cos(5*phi0a - 4*phi0b) + 
        4*pow(curvb,3)*pow(d0b,2)*cos(5*phi0a - 4*phi0b) - 
        12*curva*cos(2*phi0a - 3*phi0b) - 
        4*curva*curvb*d0b*cos(2*phi0a - 3*phi0b) - 
        16*pow(curvb,3)*d0a*d0b*cos(2*phi0a - 3*phi0b) + 
        80*curva*pow(curvb,3)*pow(d0a,2)*d0b*cos(2*phi0a - 3*phi0b) + 
        32*curva*pow(curvb,3)*pow(d0b,3)*cos(2*phi0a - 3*phi0b) + 
        30*curva*cos(4*phi0a - 3*phi0b) + 
        40*curva*curvb*d0b*cos(4*phi0a - 3*phi0b) - 
        16*pow(curvb,3)*d0a*d0b*cos(4*phi0a - 3*phi0b) + 
        16*curva*pow(curvb,3)*pow(d0a,2)*d0b*cos(4*phi0a - 3*phi0b) + 
        15*curvb*cos(phi0a - 2*phi0b) - 
        20*curva*curvb*d0a*cos(phi0a - 2*phi0b) + 
        16*pow(curvb,3)*pow(d0a,2)*cos(phi0a - 2*phi0b) - 
        96*curva*pow(curvb,3)*pow(d0a,3)*cos(phi0a - 2*phi0b) - 
        240*curva*pow(curvb,3)*d0a*pow(d0b,2)*cos(phi0a - 2*phi0b) + 
        15*curvb*cos(3*phi0a - 2*phi0b) - 
        40*curva*curvb*d0a*cos(3*phi0a - 2*phi0b) + 
        16*pow(curvb,3)*pow(d0a,2)*cos(3*phi0a - 2*phi0b) - 
        32*curva*pow(curvb,3)*pow(d0a,3)*cos(3*phi0a - 2*phi0b) - 
        80*curva*pow(curvb,3)*d0a*pow(d0b,2)*cos(3*phi0a - 2*phi0b) - 
        40*curva*cos(2*phi0a - phi0b) - 
        40*curva*curvb*d0b*cos(2*phi0a - phi0b) + 
        16*pow(curvb,3)*d0a*d0b*cos(2*phi0a - phi0b) + 
        240*curva*pow(curvb,3)*pow(d0a,2)*d0b*cos(2*phi0a - phi0b) + 
        96*curva*pow(curvb,3)*pow(d0b,3)*cos(2*phi0a - phi0b) + 
        30*curva*cos(phi0b) + 20*curva*curvb*d0b*cos(phi0b) + 
        16*pow(curvb,3)*d0a*d0b*cos(phi0b) + 
        432*curva*pow(curvb,3)*pow(d0a,2)*d0b*cos(phi0b) + 
        128*curva*pow(curvb,3)*pow(d0b,3)*cos(phi0b))*
      pow(sin(phi0a - phi0b),-5))/(64.*pow(curvb,3));
}

double BigNTuple::dysol1dd0a( double curva, double d0a, double phi0a,
			      double curvb, double d0b, double phi0b )
{
    return
   -(pow(sin(phi0a - phi0b),-5)*
       (-4*(curva*d0b + curvb*(4*d0a + 24*curva*pow(d0a,2) + 
               27*curva*pow(d0b,2)))*sin(phi0a) + 
         (-1 + 2*curva*d0a)*sin(4*phi0a - 5*phi0b) - 
         4*curva*d0b*sin(3*phi0a - 4*phi0b) + 
         4*curva*curvb*pow(d0b,2)*sin(3*phi0a - 4*phi0b) + 
         4*sin(2*phi0a - 3*phi0b) + 4*curvb*d0b*sin(2*phi0a - 3*phi0b) - 
         40*curva*curvb*d0a*d0b*sin(2*phi0a - 3*phi0b) + 
         sin(4*phi0a - 3*phi0b) - 2*curva*d0a*sin(4*phi0a - 3*phi0b) - 
         4*curvb*d0b*sin(4*phi0a - 3*phi0b) + 
         8*curva*curvb*d0a*d0b*sin(4*phi0a - 3*phi0b) - 
         8*curvb*d0a*sin(phi0a - 2*phi0b) + 
         72*curva*curvb*pow(d0a,2)*sin(phi0a - 2*phi0b) + 
         4*curva*d0b*sin(phi0a - 2*phi0b) + 
         60*curva*curvb*pow(d0b,2)*sin(phi0a - 2*phi0b) + 
         8*curvb*d0a*sin(3*phi0a - 2*phi0b) - 
         24*curva*curvb*pow(d0a,2)*sin(3*phi0a - 2*phi0b) + 
         4*curva*d0b*sin(3*phi0a - 2*phi0b) - 
         20*curva*curvb*pow(d0b,2)*sin(3*phi0a - 2*phi0b) - 
         4*sin(2*phi0a - phi0b) + 4*curvb*d0b*sin(2*phi0a - phi0b) + 
         120*curva*curvb*d0a*d0b*sin(2*phi0a - phi0b) + 6*sin(phi0b) + 
         4*curva*d0a*sin(phi0b) + 4*curvb*d0b*sin(phi0b) + 
         216*curva*curvb*d0a*d0b*sin(phi0b)))/16.;
}

double BigNTuple::dysol1dd0b( double curva, double d0a, double phi0a,
			      double curvb, double d0b, double phi0b )
{
    return
   -(pow(sin(phi0a - phi0b),-5)*
       (-2*(3 + 2*curvb*d0b + 2*curva*(d0a + 54*curvb*d0a*d0b))*sin(phi0a) + 
         (-1 + 4*curva*d0a)*(-1 + 2*curvb*d0b)*sin(3*phi0a - 4*phi0b) - 
         sin(5*phi0a - 4*phi0b) + 2*curvb*d0b*sin(5*phi0a - 4*phi0b) + 
         4*curvb*d0a*sin(2*phi0a - 3*phi0b) - 
         20*curva*curvb*pow(d0a,2)*sin(2*phi0a - 3*phi0b) + 
         8*curva*d0b*sin(2*phi0a - 3*phi0b) - 
         24*curva*curvb*pow(d0b,2)*sin(2*phi0a - 3*phi0b) - 
         4*curvb*d0a*sin(4*phi0a - 3*phi0b) + 
         4*curva*curvb*pow(d0a,2)*sin(4*phi0a - 3*phi0b) - 
         4*sin(phi0a - 2*phi0b) + 4*curva*d0a*sin(phi0a - 2*phi0b) + 
         120*curva*curvb*d0a*d0b*sin(phi0a - 2*phi0b) + 
         4*sin(3*phi0a - 2*phi0b) + 4*curva*d0a*sin(3*phi0a - 2*phi0b) - 
         40*curva*curvb*d0a*d0b*sin(3*phi0a - 2*phi0b) + 
         4*curvb*d0a*sin(2*phi0a - phi0b) + 
         60*curva*curvb*pow(d0a,2)*sin(2*phi0a - phi0b) - 
         8*curva*d0b*sin(2*phi0a - phi0b) + 
         72*curva*curvb*pow(d0b,2)*sin(2*phi0a - phi0b) + 
         4*curvb*d0a*sin(phi0b) + 108*curva*curvb*pow(d0a,2)*sin(phi0b) + 
         16*curva*d0b*sin(phi0b) + 96*curva*curvb*pow(d0b,2)*sin(phi0b)))/
    16.;
}

double BigNTuple::dysol1dphi0a( double curva, double d0a, double phi0a,
				double curvb, double d0b, double phi0b )
{
    return
   -(pow(sin(phi0a - phi0b),-6)*
       (-2*(d0a + 24*curvb*d0a*d0b + 
            2*curva*pow(d0b,2)*(3 + 82*curvb*d0b) + 
            5*pow(d0a,2)*(curva + 96*curva*curvb*d0b))*sin(phi0a) - 
         d0a*(-1 + curva*d0a)*sin(5*phi0a - 6*phi0b) - 
         2*d0b*sin(4*phi0a - 5*phi0b) + 
         8*curva*d0a*d0b*sin(4*phi0a - 5*phi0b) + 
         2*curvb*pow(d0b,2)*sin(4*phi0a - 5*phi0b) - 
         8*curva*curvb*d0a*pow(d0b,2)*sin(4*phi0a - 5*phi0b) - 
         3*d0a*sin(3*phi0a - 4*phi0b) - 
         9*curva*pow(d0a,2)*sin(3*phi0a - 4*phi0b) - 
         12*curvb*d0a*d0b*sin(3*phi0a - 4*phi0b) + 
         60*curva*curvb*pow(d0a,2)*d0b*sin(3*phi0a - 4*phi0b) - 
         12*curva*pow(d0b,2)*sin(3*phi0a - 4*phi0b) + 
         24*curva*curvb*pow(d0b,3)*sin(3*phi0a - 4*phi0b) - 
         d0a*sin(5*phi0a - 4*phi0b) + 
         curva*pow(d0a,2)*sin(5*phi0a - 4*phi0b) + 
         4*curvb*d0a*d0b*sin(5*phi0a - 4*phi0b) - 
         4*curva*curvb*pow(d0a,2)*d0b*sin(5*phi0a - 4*phi0b) + 
         16*curvb*pow(d0a,2)*sin(2*phi0a - 3*phi0b) - 
         96*curva*curvb*pow(d0a,3)*sin(2*phi0a - 3*phi0b) + 
         8*d0b*sin(2*phi0a - 3*phi0b) + 
         16*curva*d0a*d0b*sin(2*phi0a - 3*phi0b) + 
         8*curvb*pow(d0b,2)*sin(2*phi0a - 3*phi0b) - 
         272*curva*curvb*d0a*pow(d0b,2)*sin(2*phi0a - 3*phi0b) - 
         8*curvb*pow(d0a,2)*sin(4*phi0a - 3*phi0b) + 
         16*curva*curvb*pow(d0a,3)*sin(4*phi0a - 3*phi0b) + 
         2*d0b*sin(4*phi0a - 3*phi0b) - 
         8*curva*d0a*d0b*sin(4*phi0a - 3*phi0b) - 
         10*curvb*pow(d0b,2)*sin(4*phi0a - 3*phi0b) + 
         40*curva*curvb*d0a*pow(d0b,2)*sin(4*phi0a - 3*phi0b) + 
         2*d0a*sin(phi0a - 2*phi0b) + 
         10*curva*pow(d0a,2)*sin(phi0a - 2*phi0b) - 
         8*curvb*d0a*d0b*sin(phi0a - 2*phi0b) + 
         680*curva*curvb*pow(d0a,2)*d0b*sin(phi0a - 2*phi0b) + 
         12*curva*pow(d0b,2)*sin(phi0a - 2*phi0b) + 
         216*curva*curvb*pow(d0b,3)*sin(phi0a - 2*phi0b) + 
         3*d0a*sin(3*phi0a - 2*phi0b) + 
         9*curva*pow(d0a,2)*sin(3*phi0a - 2*phi0b) + 
         24*curvb*d0a*d0b*sin(3*phi0a - 2*phi0b) - 
         216*curva*curvb*pow(d0a,2)*d0b*sin(3*phi0a - 2*phi0b) + 
         12*curva*pow(d0b,2)*sin(3*phi0a - 2*phi0b) - 
         72*curva*curvb*pow(d0b,3)*sin(3*phi0a - 2*phi0b) + 
         192*curva*curvb*pow(d0a,3)*sin(2*phi0a - phi0b) - 
         8*d0b*sin(2*phi0a - phi0b) - 16*curva*d0a*d0b*sin(2*phi0a - phi0b) + 
         8*curvb*pow(d0b,2)*sin(2*phi0a - phi0b) + 
         592*curva*curvb*d0a*pow(d0b,2)*sin(2*phi0a - phi0b) + 
         24*curvb*pow(d0a,2)*sin(phi0b) + 
         336*curva*curvb*pow(d0a,3)*sin(phi0b) + 12*d0b*sin(phi0b) + 
         48*curva*d0a*d0b*sin(phi0b) + 12*curvb*pow(d0b,2)*sin(phi0b) + 
         1008*curva*curvb*d0a*pow(d0b,2)*sin(phi0b)))/32.;
}

double BigNTuple::dysol1dphi0b( double curva, double d0a, double phi0a,
				double curvb, double d0b, double phi0b )
{
    return
   (pow(sin(phi0a - phi0b),-6)*
      (-12*(d0a + 4*curvb*d0a*d0b + 2*curva*pow(d0b,2)*(1 + 14*curvb*d0b) + 
           pow(d0a,2)*(curva + 84*curva*curvb*d0b))*sin(phi0a) - 
        (-1 + 4*curva*d0a)*d0b*(-1 + curvb*d0b)*sin(4*phi0a - 5*phi0b) + 
        d0b*sin(6*phi0a - 5*phi0b) - 
        curvb*pow(d0b,2)*sin(6*phi0a - 5*phi0b) + 
        2*d0a*sin(3*phi0a - 4*phi0b) - 
        10*curva*pow(d0a,2)*sin(3*phi0a - 4*phi0b) - 
        8*curvb*d0a*d0b*sin(3*phi0a - 4*phi0b) + 
        40*curva*curvb*pow(d0a,2)*d0b*sin(3*phi0a - 4*phi0b) - 
        8*curva*pow(d0b,2)*sin(3*phi0a - 4*phi0b) + 
        16*curva*curvb*pow(d0b,3)*sin(3*phi0a - 4*phi0b) - 
        2*d0a*sin(5*phi0a - 4*phi0b) + 
        2*curva*pow(d0a,2)*sin(5*phi0a - 4*phi0b) + 
        8*curvb*d0a*d0b*sin(5*phi0a - 4*phi0b) - 
        8*curva*curvb*pow(d0a,2)*d0b*sin(5*phi0a - 4*phi0b) + 
        12*curvb*pow(d0a,2)*sin(2*phi0a - 3*phi0b) - 
        72*curva*curvb*pow(d0a,3)*sin(2*phi0a - 3*phi0b) + 
        3*d0b*sin(2*phi0a - 3*phi0b) + 
        24*curva*d0a*d0b*sin(2*phi0a - 3*phi0b) + 
        9*curvb*pow(d0b,2)*sin(2*phi0a - 3*phi0b) - 
        216*curva*curvb*d0a*pow(d0b,2)*sin(2*phi0a - 3*phi0b) - 
        12*curvb*pow(d0a,2)*sin(4*phi0a - 3*phi0b) + 
        24*curva*curvb*pow(d0a,3)*sin(4*phi0a - 3*phi0b) - 
        3*d0b*sin(4*phi0a - 3*phi0b) - 
        12*curva*d0a*d0b*sin(4*phi0a - 3*phi0b) - 
        9*curvb*pow(d0b,2)*sin(4*phi0a - 3*phi0b) + 
        60*curva*curvb*d0a*pow(d0b,2)*sin(4*phi0a - 3*phi0b) - 
        8*d0a*sin(phi0a - 2*phi0b) + 
        8*curva*pow(d0a,2)*sin(phi0a - 2*phi0b) - 
        16*curvb*d0a*d0b*sin(phi0a - 2*phi0b) + 
        592*curva*curvb*pow(d0a,2)*d0b*sin(phi0a - 2*phi0b) + 
        192*curva*curvb*pow(d0b,3)*sin(phi0a - 2*phi0b) + 
        8*d0a*sin(3*phi0a - 2*phi0b) + 
        8*curva*pow(d0a,2)*sin(3*phi0a - 2*phi0b) + 
        16*curvb*d0a*d0b*sin(3*phi0a - 2*phi0b) - 
        272*curva*curvb*pow(d0a,2)*d0b*sin(3*phi0a - 2*phi0b) + 
        16*curva*pow(d0b,2)*sin(3*phi0a - 2*phi0b) - 
        96*curva*curvb*pow(d0b,3)*sin(3*phi0a - 2*phi0b) + 
        12*curvb*pow(d0a,2)*sin(2*phi0a - phi0b) + 
        216*curva*curvb*pow(d0a,3)*sin(2*phi0a - phi0b) + 
        2*d0b*sin(2*phi0a - phi0b) - 8*curva*d0a*d0b*sin(2*phi0a - phi0b) + 
        10*curvb*pow(d0b,2)*sin(2*phi0a - phi0b) + 
        680*curva*curvb*d0a*pow(d0b,2)*sin(2*phi0a - phi0b) + 
        12*curvb*pow(d0a,2)*sin(phi0b) + 
        328*curva*curvb*pow(d0a,3)*sin(phi0b) + 2*d0b*sin(phi0b) + 
        48*curva*d0a*d0b*sin(phi0b) + 10*curvb*pow(d0b,2)*sin(phi0b) + 
        960*curva*curvb*d0a*pow(d0b,2)*sin(phi0b)))/32.;
}

double BigNTuple::dysol1dcurva( double curva, double d0a, double phi0a,
				double curvb, double d0b, double phi0b )
{
    return
   ((-d0b + d0a*cos(phi0a - phi0b))*pow(sin(phi0a - phi0b),-5)*
      (-(d0a*(1 + 40*curvb*d0b)*sin(phi0a)) - d0a*sin(3*phi0a - 4*phi0b) + 
        2*d0b*sin(2*phi0a - 3*phi0b) - 
        4*curvb*pow(d0b,2)*sin(2*phi0a - 3*phi0b) + 
        d0a*sin(phi0a - 2*phi0b) + 20*curvb*d0a*d0b*sin(phi0a - 2*phi0b) + 
        d0a*sin(3*phi0a - 2*phi0b) - 4*curvb*d0a*d0b*sin(3*phi0a - 2*phi0b) + 
        8*curvb*pow(d0a,2)*sin(2*phi0a - phi0b) - 
        2*d0b*sin(2*phi0a - phi0b) + 
        12*curvb*pow(d0b,2)*sin(2*phi0a - phi0b) + 
        24*curvb*pow(d0a,2)*sin(phi0b) + 4*d0b*sin(phi0b) + 
        16*curvb*pow(d0b,2)*sin(phi0b)))/8.;
}

double BigNTuple::dysol1dcurvb( double curva, double d0a, double phi0a,
				double curvb, double d0b, double phi0b )
{
    return
   ((-d0a + d0b*cos(phi0a - phi0b))*pow(sin(phi0a - phi0b),-5)*
      (-4*(d0a + 4*curva*pow(d0a,2) + 6*curva*pow(d0b,2))*sin(phi0a) + 
        (d0b - 4*curva*d0a*d0b)*sin(2*phi0a - 3*phi0b) - 
        d0b*sin(4*phi0a - 3*phi0b) - 2*d0a*sin(phi0a - 2*phi0b) + 
        12*curva*pow(d0a,2)*sin(phi0a - 2*phi0b) + 
        8*curva*pow(d0b,2)*sin(phi0a - 2*phi0b) + 
        2*d0a*sin(3*phi0a - 2*phi0b) - 
        4*curva*pow(d0a,2)*sin(3*phi0a - 2*phi0b) + 
        d0b*sin(2*phi0a - phi0b) + 20*curva*d0a*d0b*sin(2*phi0a - phi0b) + 
        d0b*sin(phi0b) + 40*curva*d0a*d0b*sin(phi0b)))/8.;
}

double BigNTuple::dysol2dd0a( double curva, double d0a, double phi0a,
			      double curvb, double d0b, double phi0b )
{
    return
   -(pow(sin(phi0a - phi0b),-5)*
       (2*(8*pow(curvb,2)*d0a + 
            curva*(5 + 12*curvb*d0b + 
               pow(curvb,2)*(48*pow(d0a,2) + 54*pow(d0b,2))))*sin(phi0a)
           - curva*(1 + 2*curvb*d0b)*sin(7*phi0a - 6*phi0b) - 
         curvb*sin(6*phi0a - 5*phi0b) + 
         2*curva*curvb*d0a*sin(6*phi0a - 5*phi0b) - 
         curva*sin(3*phi0a - 4*phi0b) + 
         2*curva*curvb*d0b*sin(3*phi0a - 4*phi0b) - 
         4*curva*pow(curvb,2)*pow(d0b,2)*sin(3*phi0a - 4*phi0b) + 
         5*curva*sin(5*phi0a - 4*phi0b) + 
         10*curva*curvb*d0b*sin(5*phi0a - 4*phi0b) + 
         curvb*sin(2*phi0a - 3*phi0b) - 
         10*curva*curvb*d0a*sin(2*phi0a - 3*phi0b) - 
         4*pow(curvb,2)*d0b*sin(2*phi0a - 3*phi0b) + 
         40*curva*pow(curvb,2)*d0a*d0b*sin(2*phi0a - 3*phi0b) + 
         4*curvb*sin(4*phi0a - 3*phi0b) - 
         8*curva*curvb*d0a*sin(4*phi0a - 3*phi0b) + 
         4*pow(curvb,2)*d0b*sin(4*phi0a - 3*phi0b) - 
         8*curva*pow(curvb,2)*d0a*d0b*sin(4*phi0a - 3*phi0b) + 
         5*curva*sin(phi0a - 2*phi0b) + 
         8*pow(curvb,2)*d0a*sin(phi0a - 2*phi0b) - 
         72*curva*pow(curvb,2)*pow(d0a,2)*sin(phi0a - 2*phi0b) + 
         6*curva*curvb*d0b*sin(phi0a - 2*phi0b) - 
         60*curva*pow(curvb,2)*pow(d0b,2)*sin(phi0a - 2*phi0b) - 
         10*curva*sin(3*phi0a - 2*phi0b) - 
         8*pow(curvb,2)*d0a*sin(3*phi0a - 2*phi0b) + 
         24*curva*pow(curvb,2)*pow(d0a,2)*sin(3*phi0a - 2*phi0b) - 
         24*curva*curvb*d0b*sin(3*phi0a - 2*phi0b) + 
         20*curva*pow(curvb,2)*pow(d0b,2)*sin(3*phi0a - 2*phi0b) - 
         6*curvb*sin(2*phi0a - phi0b) + 
         20*curva*curvb*d0a*sin(2*phi0a - phi0b) - 
         4*pow(curvb,2)*d0b*sin(2*phi0a - phi0b) - 
         120*curva*pow(curvb,2)*d0a*d0b*sin(2*phi0a - phi0b) + 
         4*curvb*sin(phi0b) - 24*curva*curvb*d0a*sin(phi0b) - 
         4*pow(curvb,2)*d0b*sin(phi0b) - 
         216*curva*pow(curvb,2)*d0a*d0b*sin(phi0b)))/(16.*curvb);
}

double BigNTuple::dysol2dd0b( double curva, double d0a, double phi0a,
			      double curvb, double d0b, double phi0b )
{
    return
   (pow(sin(phi0a - phi0b),-5)*
      (-8*curvb*(-1 + curvb*d0b + 6*curva*(d0a + 9*curvb*d0a*d0b))*
         sin(phi0a) - 2*curva*(1 + 2*curvb*d0b)*sin(8*phi0a - 7*phi0b) + 
        curvb*sin(5*phi0a - 6*phi0b) - curvb*sin(7*phi0a - 6*phi0b) + 
        4*curva*curvb*d0a*sin(7*phi0a - 6*phi0b) + 
        10*curva*sin(6*phi0a - 5*phi0b) + 
        20*curva*curvb*d0b*sin(6*phi0a - 5*phi0b) - 
        4*curvb*sin(3*phi0a - 4*phi0b) - 
        4*curva*curvb*d0a*sin(3*phi0a - 4*phi0b) - 
        4*pow(curvb,2)*d0b*sin(3*phi0a - 4*phi0b) + 
        16*curva*pow(curvb,2)*d0a*d0b*sin(3*phi0a - 4*phi0b) + 
        4*curvb*sin(5*phi0a - 4*phi0b) - 
        20*curva*curvb*d0a*sin(5*phi0a - 4*phi0b) + 
        4*pow(curvb,2)*d0b*sin(5*phi0a - 4*phi0b) - 
        2*curva*sin(2*phi0a - 3*phi0b) + 
        8*pow(curvb,2)*d0a*sin(2*phi0a - 3*phi0b) - 
        40*curva*pow(curvb,2)*pow(d0a,2)*sin(2*phi0a - 3*phi0b) + 
        12*curva*curvb*d0b*sin(2*phi0a - 3*phi0b) - 
        48*curva*pow(curvb,2)*pow(d0b,2)*sin(2*phi0a - 3*phi0b) - 
        20*curva*sin(4*phi0a - 3*phi0b) - 
        8*pow(curvb,2)*d0a*sin(4*phi0a - 3*phi0b) + 
        8*curva*pow(curvb,2)*pow(d0a,2)*sin(4*phi0a - 3*phi0b) - 
        40*curva*curvb*d0b*sin(4*phi0a - 3*phi0b) + 
        7*curvb*sin(phi0a - 2*phi0b) - 
        12*curva*curvb*d0a*sin(phi0a - 2*phi0b) + 
        240*curva*pow(curvb,2)*d0a*d0b*sin(phi0a - 2*phi0b) - 
        7*curvb*sin(3*phi0a - 2*phi0b) + 
        48*curva*curvb*d0a*sin(3*phi0a - 2*phi0b) - 
        80*curva*pow(curvb,2)*d0a*d0b*sin(3*phi0a - 2*phi0b) + 
        20*curva*sin(2*phi0a - phi0b) + 
        8*pow(curvb,2)*d0a*sin(2*phi0a - phi0b) + 
        120*curva*pow(curvb,2)*pow(d0a,2)*sin(2*phi0a - phi0b) + 
        24*curva*curvb*d0b*sin(2*phi0a - phi0b) + 
        144*curva*pow(curvb,2)*pow(d0b,2)*sin(2*phi0a - phi0b) - 
        10*curva*sin(phi0b) + 8*pow(curvb,2)*d0a*sin(phi0b) + 
        216*curva*pow(curvb,2)*pow(d0a,2)*sin(phi0b) + 
        12*curva*curvb*d0b*sin(phi0b) + 
        192*curva*pow(curvb,2)*pow(d0b,2)*sin(phi0b)))/(32.*curvb);
}

double BigNTuple::dysol2dphi0a( double curva, double d0a, double phi0a,
				double curvb, double d0b, double phi0b )
{
    return
   (pow(sin(phi0a - phi0b),-6)*
      (-((8*pow(curvb,2)*d0a*(11 + 24*curvb*d0b) + 
             curva*(65 + 180*curvb*d0b + 
                pow(curvb,2)*(-40*pow(d0a,2) + 228*pow(d0b,2)) + 
                32*pow(curvb,3)*(120*pow(d0a,2)*d0b + 41*pow(d0b,3))))*
           sin(phi0a)) - 3*curva*pow(1 + 2*curvb*d0b,2)*
         sin(9*phi0a - 8*phi0b) - 2*curvb*sin(8*phi0a - 7*phi0b) + 
        8*curva*curvb*d0a*sin(8*phi0a - 7*phi0b) - 
        4*pow(curvb,2)*d0b*sin(8*phi0a - 7*phi0b) + 
        16*curva*pow(curvb,2)*d0a*d0b*sin(8*phi0a - 7*phi0b) - 
        curva*sin(5*phi0a - 6*phi0b) + 19*curva*sin(7*phi0a - 6*phi0b) + 
        4*pow(curvb,2)*d0a*sin(7*phi0a - 6*phi0b) - 
        4*curva*pow(curvb,2)*pow(d0a,2)*sin(7*phi0a - 6*phi0b) + 
        72*curva*curvb*d0b*sin(7*phi0a - 6*phi0b) + 
        72*curva*pow(curvb,2)*pow(d0b,2)*sin(7*phi0a - 6*phi0b) + 
        2*curvb*sin(4*phi0a - 5*phi0b) - 
        8*curva*curvb*d0a*sin(4*phi0a - 5*phi0b) - 
        4*pow(curvb,2)*d0b*sin(4*phi0a - 5*phi0b) + 
        16*curva*pow(curvb,2)*d0a*d0b*sin(4*phi0a - 5*phi0b) + 
        8*pow(curvb,3)*pow(d0b,2)*sin(4*phi0a - 5*phi0b) - 
        32*curva*pow(curvb,3)*d0a*pow(d0b,2)*sin(4*phi0a - 5*phi0b) + 
        12*curvb*sin(6*phi0a - 5*phi0b) - 
        48*curva*curvb*d0a*sin(6*phi0a - 5*phi0b) + 
        24*pow(curvb,2)*d0b*sin(6*phi0a - 5*phi0b) - 
        96*curva*pow(curvb,2)*d0a*d0b*sin(6*phi0a - 5*phi0b) + 
        9*curva*sin(3*phi0a - 4*phi0b) + 
        12*pow(curvb,2)*d0a*sin(3*phi0a - 4*phi0b) - 
        60*curva*pow(curvb,2)*pow(d0a,2)*sin(3*phi0a - 4*phi0b) + 
        12*curva*curvb*d0b*sin(3*phi0a - 4*phi0b) - 
        48*pow(curvb,3)*d0a*d0b*sin(3*phi0a - 4*phi0b) + 
        240*curva*pow(curvb,3)*pow(d0a,2)*d0b*sin(3*phi0a - 4*phi0b) - 
        36*curva*pow(curvb,2)*pow(d0b,2)*sin(3*phi0a - 4*phi0b) + 
        96*curva*pow(curvb,3)*pow(d0b,3)*sin(3*phi0a - 4*phi0b) - 
        51*curva*sin(5*phi0a - 4*phi0b) - 
        28*pow(curvb,2)*d0a*sin(5*phi0a - 4*phi0b) + 
        28*curva*pow(curvb,2)*pow(d0a,2)*sin(5*phi0a - 4*phi0b) - 
        180*curva*curvb*d0b*sin(5*phi0a - 4*phi0b) + 
        16*pow(curvb,3)*d0a*d0b*sin(5*phi0a - 4*phi0b) - 
        16*curva*pow(curvb,3)*pow(d0a,2)*d0b*sin(5*phi0a - 4*phi0b) - 
        180*curva*pow(curvb,2)*pow(d0b,2)*sin(5*phi0a - 4*phi0b) - 
        12*curvb*sin(2*phi0a - 3*phi0b) + 
        48*curva*curvb*d0a*sin(2*phi0a - 3*phi0b) + 
        64*pow(curvb,3)*pow(d0a,2)*sin(2*phi0a - 3*phi0b) - 
        384*curva*pow(curvb,3)*pow(d0a,3)*sin(2*phi0a - 3*phi0b) + 
        8*pow(curvb,2)*d0b*sin(2*phi0a - 3*phi0b) + 
        160*curva*pow(curvb,2)*d0a*d0b*sin(2*phi0a - 3*phi0b) + 
        32*pow(curvb,3)*pow(d0b,2)*sin(2*phi0a - 3*phi0b) - 
        1088*curva*pow(curvb,3)*d0a*pow(d0b,2)*sin(2*phi0a - 3*phi0b) - 
        30*curvb*sin(4*phi0a - 3*phi0b) + 
        120*curva*curvb*d0a*sin(4*phi0a - 3*phi0b) - 
        32*pow(curvb,3)*pow(d0a,2)*sin(4*phi0a - 3*phi0b) + 
        64*curva*pow(curvb,3)*pow(d0a,3)*sin(4*phi0a - 3*phi0b) - 
        52*pow(curvb,2)*d0b*sin(4*phi0a - 3*phi0b) + 
        208*curva*pow(curvb,2)*d0a*d0b*sin(4*phi0a - 3*phi0b) - 
        40*pow(curvb,3)*pow(d0b,2)*sin(4*phi0a - 3*phi0b) + 
        160*curva*pow(curvb,3)*d0a*pow(d0b,2)*sin(4*phi0a - 3*phi0b) - 
        33*curva*sin(phi0a - 2*phi0b) - 
        52*pow(curvb,2)*d0a*sin(phi0a - 2*phi0b) + 
        100*curva*pow(curvb,2)*pow(d0a,2)*sin(phi0a - 2*phi0b) - 
        72*curva*curvb*d0b*sin(phi0a - 2*phi0b) - 
        32*pow(curvb,3)*d0a*d0b*sin(phi0a - 2*phi0b) + 
        2720*curva*pow(curvb,3)*pow(d0a,2)*d0b*sin(phi0a - 2*phi0b) - 
        24*curva*pow(curvb,2)*pow(d0b,2)*sin(phi0a - 2*phi0b) + 
        864*curva*pow(curvb,3)*pow(d0b,3)*sin(phi0a - 2*phi0b) + 
        75*curva*sin(3*phi0a - 2*phi0b) + 
        72*pow(curvb,2)*d0a*sin(3*phi0a - 2*phi0b) - 
        24*curva*pow(curvb,2)*pow(d0a,2)*sin(3*phi0a - 2*phi0b) + 
        240*curva*curvb*d0b*sin(3*phi0a - 2*phi0b) + 
        96*pow(curvb,3)*d0a*d0b*sin(3*phi0a - 2*phi0b) - 
        864*curva*pow(curvb,3)*pow(d0a,2)*d0b*sin(3*phi0a - 2*phi0b) + 
        288*curva*pow(curvb,2)*pow(d0b,2)*sin(3*phi0a - 2*phi0b) - 
        288*curva*pow(curvb,3)*pow(d0b,3)*sin(3*phi0a - 2*phi0b) + 
        40*curvb*sin(2*phi0a - phi0b) - 
        160*curva*curvb*d0a*sin(2*phi0a - phi0b) + 
        768*curva*pow(curvb,3)*pow(d0a,3)*sin(2*phi0a - phi0b) + 
        48*pow(curvb,2)*d0b*sin(2*phi0a - phi0b) - 
        384*curva*pow(curvb,2)*d0a*d0b*sin(2*phi0a - phi0b) + 
        32*pow(curvb,3)*pow(d0b,2)*sin(2*phi0a - phi0b) + 
        2368*curva*pow(curvb,3)*d0a*pow(d0b,2)*sin(2*phi0a - phi0b) - 
        30*curvb*sin(phi0b) + 120*curva*curvb*d0a*sin(phi0b) + 
        96*pow(curvb,3)*pow(d0a,2)*sin(phi0b) + 
        1344*curva*pow(curvb,3)*pow(d0a,3)*sin(phi0b) - 
        12*pow(curvb,2)*d0b*sin(phi0b) + 
        432*curva*pow(curvb,2)*d0a*d0b*sin(phi0b) + 
        48*pow(curvb,3)*pow(d0b,2)*sin(phi0b) + 
        4032*curva*pow(curvb,3)*d0a*pow(d0b,2)*sin(phi0b)))/
    (128.*pow(curvb,2));
}

double BigNTuple::dysol2dphi0b( double curva, double d0a, double phi0a,
				double curvb, double d0b, double phi0b )
{
    return
   -(pow(sin(phi0a - phi0b),-6)*
       (-6*(8*pow(curvb,2)*d0a*(1 + 4*curvb*d0b) + 
            curva*(5 + 20*curvb*d0b + 
               4*pow(curvb,2)*(2*pow(d0a,2) + 9*pow(d0b,2)) + 
               224*pow(curvb,3)*(3*pow(d0a,2)*d0b + pow(d0b,3))))*
          sin(phi0a) - 2*curva*pow(1 + 2*curvb*d0b,2)*
          sin(9*phi0a - 8*phi0b) + curvb*sin(6*phi0a - 7*phi0b) + 
         2*pow(curvb,2)*d0b*sin(6*phi0a - 7*phi0b) - 
         curvb*sin(8*phi0a - 7*phi0b) + 
         4*curva*curvb*d0a*sin(8*phi0a - 7*phi0b) - 
         2*pow(curvb,2)*d0b*sin(8*phi0a - 7*phi0b) + 
         8*curva*pow(curvb,2)*d0a*d0b*sin(8*phi0a - 7*phi0b) + 
         12*curva*sin(7*phi0a - 6*phi0b) + 
         48*curva*curvb*d0b*sin(7*phi0a - 6*phi0b) + 
         48*curva*pow(curvb,2)*pow(d0b,2)*sin(7*phi0a - 6*phi0b) - 
         5*curvb*sin(4*phi0a - 5*phi0b) - 
         4*curva*curvb*d0a*sin(4*phi0a - 5*phi0b) - 
         14*pow(curvb,2)*d0b*sin(4*phi0a - 5*phi0b) + 
         8*curva*pow(curvb,2)*d0a*d0b*sin(4*phi0a - 5*phi0b) + 
         4*pow(curvb,3)*pow(d0b,2)*sin(4*phi0a - 5*phi0b) - 
         16*curva*pow(curvb,3)*d0a*pow(d0b,2)*sin(4*phi0a - 5*phi0b) + 
         5*curvb*sin(6*phi0a - 5*phi0b) - 
         24*curva*curvb*d0a*sin(6*phi0a - 5*phi0b) + 
         14*pow(curvb,2)*d0b*sin(6*phi0a - 5*phi0b) - 
         48*curva*pow(curvb,2)*d0a*d0b*sin(6*phi0a - 5*phi0b) - 
         4*pow(curvb,3)*pow(d0b,2)*sin(6*phi0a - 5*phi0b) + 
         2*curva*sin(3*phi0a - 4*phi0b) + 
         8*pow(curvb,2)*d0a*sin(3*phi0a - 4*phi0b) - 
         40*curva*pow(curvb,2)*pow(d0a,2)*sin(3*phi0a - 4*phi0b) + 
         8*curva*curvb*d0b*sin(3*phi0a - 4*phi0b) - 
         32*pow(curvb,3)*d0a*d0b*sin(3*phi0a - 4*phi0b) + 
         160*curva*pow(curvb,3)*pow(d0a,2)*d0b*sin(3*phi0a - 4*phi0b) - 
         24*curva*pow(curvb,2)*pow(d0b,2)*sin(3*phi0a - 4*phi0b) + 
         64*curva*pow(curvb,3)*pow(d0b,3)*sin(3*phi0a - 4*phi0b) - 
         30*curva*sin(5*phi0a - 4*phi0b) - 
         8*pow(curvb,2)*d0a*sin(5*phi0a - 4*phi0b) + 
         8*curva*pow(curvb,2)*pow(d0a,2)*sin(5*phi0a - 4*phi0b) - 
         120*curva*curvb*d0b*sin(5*phi0a - 4*phi0b) + 
         32*pow(curvb,3)*d0a*d0b*sin(5*phi0a - 4*phi0b) - 
         32*curva*pow(curvb,3)*pow(d0a,2)*d0b*sin(5*phi0a - 4*phi0b) - 
         120*curva*pow(curvb,2)*pow(d0b,2)*sin(5*phi0a - 4*phi0b) + 
         9*curvb*sin(2*phi0a - 3*phi0b) + 
         24*curva*curvb*d0a*sin(2*phi0a - 3*phi0b) + 
         48*pow(curvb,3)*pow(d0a,2)*sin(2*phi0a - 3*phi0b) - 
         288*curva*pow(curvb,3)*pow(d0a,3)*sin(2*phi0a - 3*phi0b) + 
         30*pow(curvb,2)*d0b*sin(2*phi0a - 3*phi0b) + 
         144*curva*pow(curvb,2)*d0a*d0b*sin(2*phi0a - 3*phi0b) + 
         36*pow(curvb,3)*pow(d0b,2)*sin(2*phi0a - 3*phi0b) - 
         864*curva*pow(curvb,3)*d0a*pow(d0b,2)*sin(2*phi0a - 3*phi0b) - 
         9*curvb*sin(4*phi0a - 3*phi0b) + 
         60*curva*curvb*d0a*sin(4*phi0a - 3*phi0b) - 
         48*pow(curvb,3)*pow(d0a,2)*sin(4*phi0a - 3*phi0b) + 
         96*curva*pow(curvb,3)*pow(d0a,3)*sin(4*phi0a - 3*phi0b) - 
         30*pow(curvb,2)*d0b*sin(4*phi0a - 3*phi0b) + 
         72*curva*pow(curvb,2)*d0a*d0b*sin(4*phi0a - 3*phi0b) - 
         36*pow(curvb,3)*pow(d0b,2)*sin(4*phi0a - 3*phi0b) + 
         240*curva*pow(curvb,3)*d0a*pow(d0b,2)*sin(4*phi0a - 3*phi0b) - 
         12*curva*sin(phi0a - 2*phi0b) - 
         32*pow(curvb,2)*d0a*sin(phi0a - 2*phi0b) + 
         32*curva*pow(curvb,2)*pow(d0a,2)*sin(phi0a - 2*phi0b) - 
         48*curva*curvb*d0b*sin(phi0a - 2*phi0b) - 
         64*pow(curvb,3)*d0a*d0b*sin(phi0a - 2*phi0b) + 
         2368*curva*pow(curvb,3)*pow(d0a,2)*d0b*sin(phi0a - 2*phi0b) - 
         48*curva*pow(curvb,2)*pow(d0b,2)*sin(phi0a - 2*phi0b) + 
         768*curva*pow(curvb,3)*pow(d0b,3)*sin(phi0a - 2*phi0b) + 
         40*curva*sin(3*phi0a - 2*phi0b) + 
         32*pow(curvb,2)*d0a*sin(3*phi0a - 2*phi0b) + 
         32*curva*pow(curvb,2)*pow(d0a,2)*sin(3*phi0a - 2*phi0b) + 
         160*curva*curvb*d0b*sin(3*phi0a - 2*phi0b) + 
         64*pow(curvb,3)*d0a*d0b*sin(3*phi0a - 2*phi0b) - 
         1088*curva*pow(curvb,3)*pow(d0a,2)*d0b*sin(3*phi0a - 2*phi0b) + 
         224*curva*pow(curvb,2)*pow(d0b,2)*sin(3*phi0a - 2*phi0b) - 
         384*curva*pow(curvb,3)*pow(d0b,3)*sin(3*phi0a - 2*phi0b) + 
         5*curvb*sin(2*phi0a - phi0b) - 
         80*curva*curvb*d0a*sin(2*phi0a - phi0b) + 
         48*pow(curvb,3)*pow(d0a,2)*sin(2*phi0a - phi0b) + 
         864*curva*pow(curvb,3)*pow(d0a,3)*sin(2*phi0a - phi0b) + 
         18*pow(curvb,2)*d0b*sin(2*phi0a - phi0b) - 
         192*curva*pow(curvb,2)*d0a*d0b*sin(2*phi0a - phi0b) + 
         40*pow(curvb,3)*pow(d0b,2)*sin(2*phi0a - phi0b) + 
         2720*curva*pow(curvb,3)*d0a*pow(d0b,2)*sin(2*phi0a - phi0b) + 
         5*curvb*sin(phi0b) + 60*curva*curvb*d0a*sin(phi0b) + 
         48*pow(curvb,3)*pow(d0a,2)*sin(phi0b) + 
         1312*curva*pow(curvb,3)*pow(d0a,3)*sin(phi0b) + 
         18*pow(curvb,2)*d0b*sin(phi0b) + 
         312*curva*pow(curvb,2)*d0a*d0b*sin(phi0b) + 
         40*pow(curvb,3)*pow(d0b,2)*sin(phi0b) + 
         3840*curva*pow(curvb,3)*d0a*pow(d0b,2)*sin(phi0b)))/
    (128.*pow(curvb,2));
}

double BigNTuple::dysol2dcurva( double curva, double d0a, double phi0a,
				double curvb, double d0b, double phi0b )
{
    return
   (pow(sin(phi0a - phi0b),-5)*
      (-8*curvb*d0a*(5 + 12*curvb*d0b + 
           pow(curvb,2)*(16*pow(d0a,2) + 54*pow(d0b,2)))*sin(phi0a) - 
        pow(1 + 2*curvb*d0b,2)*sin(8*phi0a - 7*phi0b) + 
        4*curvb*d0a*sin(7*phi0a - 6*phi0b) + 
        8*pow(curvb,2)*d0a*d0b*sin(7*phi0a - 6*phi0b) + 
        sin(4*phi0a - 5*phi0b) + 6*sin(6*phi0a - 5*phi0b) - 
        4*pow(curvb,2)*pow(d0a,2)*sin(6*phi0a - 5*phi0b) + 
        20*curvb*d0b*sin(6*phi0a - 5*phi0b) + 
        20*pow(curvb,2)*pow(d0b,2)*sin(6*phi0a - 5*phi0b) + 
        4*curvb*d0a*sin(3*phi0a - 4*phi0b) - 
        8*pow(curvb,2)*d0a*d0b*sin(3*phi0a - 4*phi0b) + 
        16*pow(curvb,3)*d0a*pow(d0b,2)*sin(3*phi0a - 4*phi0b) - 
        20*curvb*d0a*sin(5*phi0a - 4*phi0b) - 
        40*pow(curvb,2)*d0a*d0b*sin(5*phi0a - 4*phi0b) - 
        6*sin(2*phi0a - 3*phi0b) + 
        20*pow(curvb,2)*pow(d0a,2)*sin(2*phi0a - 3*phi0b) - 
        4*curvb*d0b*sin(2*phi0a - 3*phi0b) - 
        80*pow(curvb,3)*pow(d0a,2)*d0b*sin(2*phi0a - 3*phi0b) + 
        12*pow(curvb,2)*pow(d0b,2)*sin(2*phi0a - 3*phi0b) - 
        32*pow(curvb,3)*pow(d0b,3)*sin(2*phi0a - 3*phi0b) - 
        15*sin(4*phi0a - 3*phi0b) + 
        16*pow(curvb,2)*pow(d0a,2)*sin(4*phi0a - 3*phi0b) - 
        40*curvb*d0b*sin(4*phi0a - 3*phi0b) + 
        16*pow(curvb,3)*pow(d0a,2)*d0b*sin(4*phi0a - 3*phi0b) - 
        40*pow(curvb,2)*pow(d0b,2)*sin(4*phi0a - 3*phi0b) - 
        20*curvb*d0a*sin(phi0a - 2*phi0b) + 
        96*pow(curvb,3)*pow(d0a,3)*sin(phi0a - 2*phi0b) - 
        24*pow(curvb,2)*d0a*d0b*sin(phi0a - 2*phi0b) + 
        240*pow(curvb,3)*d0a*pow(d0b,2)*sin(phi0a - 2*phi0b) + 
        40*curvb*d0a*sin(3*phi0a - 2*phi0b) - 
        32*pow(curvb,3)*pow(d0a,3)*sin(3*phi0a - 2*phi0b) + 
        96*pow(curvb,2)*d0a*d0b*sin(3*phi0a - 2*phi0b) - 
        80*pow(curvb,3)*d0a*pow(d0b,2)*sin(3*phi0a - 2*phi0b) + 
        20*sin(2*phi0a - phi0b) - 
        40*pow(curvb,2)*pow(d0a,2)*sin(2*phi0a - phi0b) + 
        40*curvb*d0b*sin(2*phi0a - phi0b) + 
        240*pow(curvb,3)*pow(d0a,2)*d0b*sin(2*phi0a - phi0b) + 
        24*pow(curvb,2)*pow(d0b,2)*sin(2*phi0a - phi0b) + 
        96*pow(curvb,3)*pow(d0b,3)*sin(2*phi0a - phi0b) - 15*sin(phi0b) + 
        48*pow(curvb,2)*pow(d0a,2)*sin(phi0b) - 20*curvb*d0b*sin(phi0b) + 
        432*pow(curvb,3)*pow(d0a,2)*d0b*sin(phi0b) + 
        12*pow(curvb,2)*pow(d0b,2)*sin(phi0b) + 
        128*pow(curvb,3)*pow(d0b,3)*sin(phi0b)))/(64.*pow(curvb,2));
}

double BigNTuple::dysol2dcurvb( double curva, double d0a, double phi0a,
				double curvb, double d0b, double phi0b )
{
    return
   (pow(sin(phi0a - phi0b),-5)*
      (-4*curvb*(5 + 2*pow(curvb,2)*(4*pow(d0a,2) + pow(d0b,2)) + 
           2*curva*d0a*(-5 + pow(curvb,2)*
               (16*pow(d0a,2) + 54*pow(d0b,2))))*sin(phi0a) + 
        2*curva*(1 + 2*curvb*d0b)*sin(8*phi0a - 7*phi0b) - 
        curvb*sin(5*phi0a - 6*phi0b) + curvb*sin(7*phi0a - 6*phi0b) - 
        4*curva*curvb*d0a*sin(7*phi0a - 6*phi0b) - 
        2*curva*sin(4*phi0a - 5*phi0b) - 12*curva*sin(6*phi0a - 5*phi0b) - 
        20*curva*curvb*d0b*sin(6*phi0a - 5*phi0b) + 
        6*curvb*sin(3*phi0a - 4*phi0b) - 
        4*curva*curvb*d0a*sin(3*phi0a - 4*phi0b) - 
        4*pow(curvb,3)*pow(d0b,2)*sin(3*phi0a - 4*phi0b) + 
        16*curva*pow(curvb,3)*d0a*pow(d0b,2)*sin(3*phi0a - 4*phi0b) - 
        6*curvb*sin(5*phi0a - 4*phi0b) + 
        20*curva*curvb*d0a*sin(5*phi0a - 4*phi0b) + 
        4*pow(curvb,3)*pow(d0b,2)*sin(5*phi0a - 4*phi0b) + 
        12*curva*sin(2*phi0a - 3*phi0b) + 
        4*curva*curvb*d0b*sin(2*phi0a - 3*phi0b) + 
        16*pow(curvb,3)*d0a*d0b*sin(2*phi0a - 3*phi0b) - 
        80*curva*pow(curvb,3)*pow(d0a,2)*d0b*sin(2*phi0a - 3*phi0b) - 
        32*curva*pow(curvb,3)*pow(d0b,3)*sin(2*phi0a - 3*phi0b) + 
        30*curva*sin(4*phi0a - 3*phi0b) + 
        40*curva*curvb*d0b*sin(4*phi0a - 3*phi0b) - 
        16*pow(curvb,3)*d0a*d0b*sin(4*phi0a - 3*phi0b) + 
        16*curva*pow(curvb,3)*pow(d0a,2)*d0b*sin(4*phi0a - 3*phi0b) - 
        15*curvb*sin(phi0a - 2*phi0b) + 
        20*curva*curvb*d0a*sin(phi0a - 2*phi0b) - 
        16*pow(curvb,3)*pow(d0a,2)*sin(phi0a - 2*phi0b) + 
        96*curva*pow(curvb,3)*pow(d0a,3)*sin(phi0a - 2*phi0b) + 
        240*curva*pow(curvb,3)*d0a*pow(d0b,2)*sin(phi0a - 2*phi0b) + 
        15*curvb*sin(3*phi0a - 2*phi0b) - 
        40*curva*curvb*d0a*sin(3*phi0a - 2*phi0b) + 
        16*pow(curvb,3)*pow(d0a,2)*sin(3*phi0a - 2*phi0b) - 
        32*curva*pow(curvb,3)*pow(d0a,3)*sin(3*phi0a - 2*phi0b) - 
        80*curva*pow(curvb,3)*d0a*pow(d0b,2)*sin(3*phi0a - 2*phi0b) - 
        40*curva*sin(2*phi0a - phi0b) - 
        40*curva*curvb*d0b*sin(2*phi0a - phi0b) + 
        16*pow(curvb,3)*d0a*d0b*sin(2*phi0a - phi0b) + 
        240*curva*pow(curvb,3)*pow(d0a,2)*d0b*sin(2*phi0a - phi0b) + 
        96*curva*pow(curvb,3)*pow(d0b,3)*sin(2*phi0a - phi0b) + 
        30*curva*sin(phi0b) + 20*curva*curvb*d0b*sin(phi0b) + 
        16*pow(curvb,3)*d0a*d0b*sin(phi0b) + 
        432*curva*pow(curvb,3)*pow(d0a,2)*d0b*sin(phi0b) + 
        128*curva*pow(curvb,3)*pow(d0b,3)*sin(phi0b)))/
    (64.*pow(curvb,3));
}

Exit
[Mathematica finished.]
