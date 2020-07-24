Suppose we start with two general circles:

circa = (x - x0a)^2 + (y - y0a)^2 == Ra^2;
circb = (x - x0b)^2 + (y - y0b)^2 == Rb^2;

Never mind for the moment how x0a, y0a, x0b and y0b relate to tracking
parameters. That's a solved problem.

x is easy to solve for, and there are two solutions.

( {{xsol1}, {xsol2}} = Solve[ circb, x ] ) // InputForm

Out[7]//InputForm= 
{{x -> x0b - Sqrt[Rb^2 - y^2 + 2*y*y0b - y0b^2]}, 
 {x -> x0b + Sqrt[Rb^2 - y^2 + 2*y*y0b - y0b^2]}}

( {{ysol1xs1}, {ysol2xs1}} = Solve[ circa /. xsol1, y ] ) // InputForm

Out[8]//InputForm= 
{{y -> (-4*Ra^2*y0a + 4*Rb^2*y0a + 4*x0a^2*y0a - 8*x0a*x0b*y0a + 
     4*x0b^2*y0a + 4*y0a^3 + 4*Ra^2*y0b - 4*Rb^2*y0b + 4*x0a^2*y0b - 
     8*x0a*x0b*y0b + 4*x0b^2*y0b - 4*y0a^2*y0b - 4*y0a*y0b^2 + 4*y0b^3 - 
     4*Sqrt[-(Ra^4*x0a^2) + 2*Ra^2*Rb^2*x0a^2 - Rb^4*x0a^2 + 2*Ra^2*x0a^4 + 
        2*Rb^2*x0a^4 - x0a^6 + 2*Ra^4*x0a*x0b - 4*Ra^2*Rb^2*x0a*x0b + 
        2*Rb^4*x0a*x0b - 8*Ra^2*x0a^3*x0b - 8*Rb^2*x0a^3*x0b + 6*x0a^5*x0b - 
        Ra^4*x0b^2 + 2*Ra^2*Rb^2*x0b^2 - Rb^4*x0b^2 + 12*Ra^2*x0a^2*x0b^2 + 
        12*Rb^2*x0a^2*x0b^2 - 15*x0a^4*x0b^2 - 8*Ra^2*x0a*x0b^3 - 
        8*Rb^2*x0a*x0b^3 + 20*x0a^3*x0b^3 + 2*Ra^2*x0b^4 + 2*Rb^2*x0b^4 - 
        15*x0a^2*x0b^4 + 6*x0a*x0b^5 - x0b^6 + 2*Ra^2*x0a^2*y0a^2 + 
        2*Rb^2*x0a^2*y0a^2 - 2*x0a^4*y0a^2 - 4*Ra^2*x0a*x0b*y0a^2 - 
        4*Rb^2*x0a*x0b*y0a^2 + 8*x0a^3*x0b*y0a^2 + 2*Ra^2*x0b^2*y0a^2 + 
        2*Rb^2*x0b^2*y0a^2 - 12*x0a^2*x0b^2*y0a^2 + 8*x0a*x0b^3*y0a^2 - 
        2*x0b^4*y0a^2 - x0a^2*y0a^4 + 2*x0a*x0b*y0a^4 - x0b^2*y0a^4 - 
        4*Ra^2*x0a^2*y0a*y0b - 4*Rb^2*x0a^2*y0a*y0b + 4*x0a^4*y0a*y0b + 
        8*Ra^2*x0a*x0b*y0a*y0b + 8*Rb^2*x0a*x0b*y0a*y0b - 
        16*x0a^3*x0b*y0a*y0b - 4*Ra^2*x0b^2*y0a*y0b - 4*Rb^2*x0b^2*y0a*y0b + 
        24*x0a^2*x0b^2*y0a*y0b - 16*x0a*x0b^3*y0a*y0b + 4*x0b^4*y0a*y0b + 
        4*x0a^2*y0a^3*y0b - 8*x0a*x0b*y0a^3*y0b + 4*x0b^2*y0a^3*y0b + 
        2*Ra^2*x0a^2*y0b^2 + 2*Rb^2*x0a^2*y0b^2 - 2*x0a^4*y0b^2 - 
        4*Ra^2*x0a*x0b*y0b^2 - 4*Rb^2*x0a*x0b*y0b^2 + 8*x0a^3*x0b*y0b^2 + 
        2*Ra^2*x0b^2*y0b^2 + 2*Rb^2*x0b^2*y0b^2 - 12*x0a^2*x0b^2*y0b^2 + 
        8*x0a*x0b^3*y0b^2 - 2*x0b^4*y0b^2 - 6*x0a^2*y0a^2*y0b^2 + 
        12*x0a*x0b*y0a^2*y0b^2 - 6*x0b^2*y0a^2*y0b^2 + 4*x0a^2*y0a*y0b^3 - 
        8*x0a*x0b*y0a*y0b^3 + 4*x0b^2*y0a*y0b^3 - x0a^2*y0b^4 + 
        2*x0a*x0b*y0b^4 - x0b^2*y0b^4])/
    (2*(4*x0a^2 - 8*x0a*x0b + 4*x0b^2 + 4*y0a^2 - 8*y0a*y0b + 4*y0b^2))}, 
 {y -> (-4*Ra^2*y0a + 4*Rb^2*y0a + 4*x0a^2*y0a - 8*x0a*x0b*y0a + 
     4*x0b^2*y0a + 4*y0a^3 + 4*Ra^2*y0b - 4*Rb^2*y0b + 4*x0a^2*y0b - 
     8*x0a*x0b*y0b + 4*x0b^2*y0b - 4*y0a^2*y0b - 4*y0a*y0b^2 + 4*y0b^3 + 
     4*Sqrt[-(Ra^4*x0a^2) + 2*Ra^2*Rb^2*x0a^2 - Rb^4*x0a^2 + 2*Ra^2*x0a^4 + 
        2*Rb^2*x0a^4 - x0a^6 + 2*Ra^4*x0a*x0b - 4*Ra^2*Rb^2*x0a*x0b + 
        2*Rb^4*x0a*x0b - 8*Ra^2*x0a^3*x0b - 8*Rb^2*x0a^3*x0b + 6*x0a^5*x0b - 
        Ra^4*x0b^2 + 2*Ra^2*Rb^2*x0b^2 - Rb^4*x0b^2 + 12*Ra^2*x0a^2*x0b^2 + 
        12*Rb^2*x0a^2*x0b^2 - 15*x0a^4*x0b^2 - 8*Ra^2*x0a*x0b^3 - 
        8*Rb^2*x0a*x0b^3 + 20*x0a^3*x0b^3 + 2*Ra^2*x0b^4 + 2*Rb^2*x0b^4 - 
        15*x0a^2*x0b^4 + 6*x0a*x0b^5 - x0b^6 + 2*Ra^2*x0a^2*y0a^2 + 
        2*Rb^2*x0a^2*y0a^2 - 2*x0a^4*y0a^2 - 4*Ra^2*x0a*x0b*y0a^2 - 
        4*Rb^2*x0a*x0b*y0a^2 + 8*x0a^3*x0b*y0a^2 + 2*Ra^2*x0b^2*y0a^2 + 
        2*Rb^2*x0b^2*y0a^2 - 12*x0a^2*x0b^2*y0a^2 + 8*x0a*x0b^3*y0a^2 - 
        2*x0b^4*y0a^2 - x0a^2*y0a^4 + 2*x0a*x0b*y0a^4 - x0b^2*y0a^4 - 
        4*Ra^2*x0a^2*y0a*y0b - 4*Rb^2*x0a^2*y0a*y0b + 4*x0a^4*y0a*y0b + 
        8*Ra^2*x0a*x0b*y0a*y0b + 8*Rb^2*x0a*x0b*y0a*y0b - 
        16*x0a^3*x0b*y0a*y0b - 4*Ra^2*x0b^2*y0a*y0b - 4*Rb^2*x0b^2*y0a*y0b + 
        24*x0a^2*x0b^2*y0a*y0b - 16*x0a*x0b^3*y0a*y0b + 4*x0b^4*y0a*y0b + 
        4*x0a^2*y0a^3*y0b - 8*x0a*x0b*y0a^3*y0b + 4*x0b^2*y0a^3*y0b + 
        2*Ra^2*x0a^2*y0b^2 + 2*Rb^2*x0a^2*y0b^2 - 2*x0a^4*y0b^2 - 
        4*Ra^2*x0a*x0b*y0b^2 - 4*Rb^2*x0a*x0b*y0b^2 + 8*x0a^3*x0b*y0b^2 + 
        2*Ra^2*x0b^2*y0b^2 + 2*Rb^2*x0b^2*y0b^2 - 12*x0a^2*x0b^2*y0b^2 + 
        8*x0a*x0b^3*y0b^2 - 2*x0b^4*y0b^2 - 6*x0a^2*y0a^2*y0b^2 + 
        12*x0a*x0b*y0a^2*y0b^2 - 6*x0b^2*y0a^2*y0b^2 + 4*x0a^2*y0a*y0b^3 - 
        8*x0a*x0b*y0a*y0b^3 + 4*x0b^2*y0a*y0b^3 - x0a^2*y0b^4 + 
        2*x0a*x0b*y0b^4 - x0b^2*y0b^4])/
    (2*(4*x0a^2 - 8*x0a*x0b + 4*x0b^2 + 4*y0a^2 - 8*y0a*y0b + 4*y0b^2))}}

( {{ysol1xs2}, {ysol2xs2}} = Solve[ circa /. xsol2, y ] ) // InputForm

Out[9]//InputForm= 
{{y -> (-4*Ra^2*y0a + 4*Rb^2*y0a + 4*x0a^2*y0a - 8*x0a*x0b*y0a + 
     4*x0b^2*y0a + 4*y0a^3 + 4*Ra^2*y0b - 4*Rb^2*y0b + 4*x0a^2*y0b - 
     8*x0a*x0b*y0b + 4*x0b^2*y0b - 4*y0a^2*y0b - 4*y0a*y0b^2 + 4*y0b^3 - 
     4*Sqrt[-(Ra^4*x0a^2) + 2*Ra^2*Rb^2*x0a^2 - Rb^4*x0a^2 + 2*Ra^2*x0a^4 + 
        2*Rb^2*x0a^4 - x0a^6 + 2*Ra^4*x0a*x0b - 4*Ra^2*Rb^2*x0a*x0b + 
        2*Rb^4*x0a*x0b - 8*Ra^2*x0a^3*x0b - 8*Rb^2*x0a^3*x0b + 6*x0a^5*x0b - 
        Ra^4*x0b^2 + 2*Ra^2*Rb^2*x0b^2 - Rb^4*x0b^2 + 12*Ra^2*x0a^2*x0b^2 + 
        12*Rb^2*x0a^2*x0b^2 - 15*x0a^4*x0b^2 - 8*Ra^2*x0a*x0b^3 - 
        8*Rb^2*x0a*x0b^3 + 20*x0a^3*x0b^3 + 2*Ra^2*x0b^4 + 2*Rb^2*x0b^4 - 
        15*x0a^2*x0b^4 + 6*x0a*x0b^5 - x0b^6 + 2*Ra^2*x0a^2*y0a^2 + 
        2*Rb^2*x0a^2*y0a^2 - 2*x0a^4*y0a^2 - 4*Ra^2*x0a*x0b*y0a^2 - 
        4*Rb^2*x0a*x0b*y0a^2 + 8*x0a^3*x0b*y0a^2 + 2*Ra^2*x0b^2*y0a^2 + 
        2*Rb^2*x0b^2*y0a^2 - 12*x0a^2*x0b^2*y0a^2 + 8*x0a*x0b^3*y0a^2 - 
        2*x0b^4*y0a^2 - x0a^2*y0a^4 + 2*x0a*x0b*y0a^4 - x0b^2*y0a^4 - 
        4*Ra^2*x0a^2*y0a*y0b - 4*Rb^2*x0a^2*y0a*y0b + 4*x0a^4*y0a*y0b + 
        8*Ra^2*x0a*x0b*y0a*y0b + 8*Rb^2*x0a*x0b*y0a*y0b - 
        16*x0a^3*x0b*y0a*y0b - 4*Ra^2*x0b^2*y0a*y0b - 4*Rb^2*x0b^2*y0a*y0b + 
        24*x0a^2*x0b^2*y0a*y0b - 16*x0a*x0b^3*y0a*y0b + 4*x0b^4*y0a*y0b + 
        4*x0a^2*y0a^3*y0b - 8*x0a*x0b*y0a^3*y0b + 4*x0b^2*y0a^3*y0b + 
        2*Ra^2*x0a^2*y0b^2 + 2*Rb^2*x0a^2*y0b^2 - 2*x0a^4*y0b^2 - 
        4*Ra^2*x0a*x0b*y0b^2 - 4*Rb^2*x0a*x0b*y0b^2 + 8*x0a^3*x0b*y0b^2 + 
        2*Ra^2*x0b^2*y0b^2 + 2*Rb^2*x0b^2*y0b^2 - 12*x0a^2*x0b^2*y0b^2 + 
        8*x0a*x0b^3*y0b^2 - 2*x0b^4*y0b^2 - 6*x0a^2*y0a^2*y0b^2 + 
        12*x0a*x0b*y0a^2*y0b^2 - 6*x0b^2*y0a^2*y0b^2 + 4*x0a^2*y0a*y0b^3 - 
        8*x0a*x0b*y0a*y0b^3 + 4*x0b^2*y0a*y0b^3 - x0a^2*y0b^4 + 
        2*x0a*x0b*y0b^4 - x0b^2*y0b^4])/
    (2*(4*x0a^2 - 8*x0a*x0b + 4*x0b^2 + 4*y0a^2 - 8*y0a*y0b + 4*y0b^2))}, 
 {y -> (-4*Ra^2*y0a + 4*Rb^2*y0a + 4*x0a^2*y0a - 8*x0a*x0b*y0a + 
     4*x0b^2*y0a + 4*y0a^3 + 4*Ra^2*y0b - 4*Rb^2*y0b + 4*x0a^2*y0b - 
     8*x0a*x0b*y0b + 4*x0b^2*y0b - 4*y0a^2*y0b - 4*y0a*y0b^2 + 4*y0b^3 + 
     4*Sqrt[-(Ra^4*x0a^2) + 2*Ra^2*Rb^2*x0a^2 - Rb^4*x0a^2 + 2*Ra^2*x0a^4 + 
        2*Rb^2*x0a^4 - x0a^6 + 2*Ra^4*x0a*x0b - 4*Ra^2*Rb^2*x0a*x0b + 
        2*Rb^4*x0a*x0b - 8*Ra^2*x0a^3*x0b - 8*Rb^2*x0a^3*x0b + 6*x0a^5*x0b - 
        Ra^4*x0b^2 + 2*Ra^2*Rb^2*x0b^2 - Rb^4*x0b^2 + 12*Ra^2*x0a^2*x0b^2 + 
        12*Rb^2*x0a^2*x0b^2 - 15*x0a^4*x0b^2 - 8*Ra^2*x0a*x0b^3 - 
        8*Rb^2*x0a*x0b^3 + 20*x0a^3*x0b^3 + 2*Ra^2*x0b^4 + 2*Rb^2*x0b^4 - 
        15*x0a^2*x0b^4 + 6*x0a*x0b^5 - x0b^6 + 2*Ra^2*x0a^2*y0a^2 + 
        2*Rb^2*x0a^2*y0a^2 - 2*x0a^4*y0a^2 - 4*Ra^2*x0a*x0b*y0a^2 - 
        4*Rb^2*x0a*x0b*y0a^2 + 8*x0a^3*x0b*y0a^2 + 2*Ra^2*x0b^2*y0a^2 + 
        2*Rb^2*x0b^2*y0a^2 - 12*x0a^2*x0b^2*y0a^2 + 8*x0a*x0b^3*y0a^2 - 
        2*x0b^4*y0a^2 - x0a^2*y0a^4 + 2*x0a*x0b*y0a^4 - x0b^2*y0a^4 - 
        4*Ra^2*x0a^2*y0a*y0b - 4*Rb^2*x0a^2*y0a*y0b + 4*x0a^4*y0a*y0b + 
        8*Ra^2*x0a*x0b*y0a*y0b + 8*Rb^2*x0a*x0b*y0a*y0b - 
        16*x0a^3*x0b*y0a*y0b - 4*Ra^2*x0b^2*y0a*y0b - 4*Rb^2*x0b^2*y0a*y0b + 
        24*x0a^2*x0b^2*y0a*y0b - 16*x0a*x0b^3*y0a*y0b + 4*x0b^4*y0a*y0b + 
        4*x0a^2*y0a^3*y0b - 8*x0a*x0b*y0a^3*y0b + 4*x0b^2*y0a^3*y0b + 
        2*Ra^2*x0a^2*y0b^2 + 2*Rb^2*x0a^2*y0b^2 - 2*x0a^4*y0b^2 - 
        4*Ra^2*x0a*x0b*y0b^2 - 4*Rb^2*x0a*x0b*y0b^2 + 8*x0a^3*x0b*y0b^2 + 
        2*Ra^2*x0b^2*y0b^2 + 2*Rb^2*x0b^2*y0b^2 - 12*x0a^2*x0b^2*y0b^2 + 
        8*x0a*x0b^3*y0b^2 - 2*x0b^4*y0b^2 - 6*x0a^2*y0a^2*y0b^2 + 
        12*x0a*x0b*y0a^2*y0b^2 - 6*x0b^2*y0a^2*y0b^2 + 4*x0a^2*y0a*y0b^3 - 
        8*x0a*x0b*y0a*y0b^3 + 4*x0b^2*y0a*y0b^3 - x0a^2*y0b^4 + 
        2*x0a*x0b*y0b^4 - x0b^2*y0b^4])/
    (2*(4*x0a^2 - 8*x0a*x0b + 4*x0b^2 + 4*y0a^2 - 8*y0a*y0b + 4*y0b^2))}}

specifics = { x0a -> 12, x0b -> -13, y0a -> 4, y0b -> 15, Ra -> 35, Rb -> 30 };
Print[specifics];
points = {
    Point[{(x /. xsol1) /. ysol1xs1, y /. ysol1xs1} /. specifics // N],
(*    Point[{(x /. xsol1) /. ysol2xs1, y /. ysol2xs1} /. specifics // N]
    Point[{(x /. xsol2) /. ysol1xs2, y /. ysol1xs2} /. specifics // N] *)
    Point[{(x /. xsol2) /. ysol2xs2, y /. ysol2xs2} /. specifics // N]
	 };
Print[points];
points = Select[ points, (Im[#[[1]]]=={0,0})& ];
Show[ 
    ParametricPlot[ {x0a+Ra*Cos[t],y0a+Ra*Sin[t]} /. specifics
		    , {t,0,2 Pi}
		    , DisplayFunction -> Identity
		  ],
    ParametricPlot[ {x0b+Rb*Cos[t],y0b+Rb*Sin[t]} /. specifics
		    , {t,0,2 Pi}
		    , DisplayFunction -> Identity
		  ],
    Graphics[{points}]
    , AspectRatio -> 1
    , PlotRange -> {{-50,50}, {-50,50}}
    , DisplayFunction -> $DisplayFunction
    ];

Module[ { mx0a = Random[ Real, {-15, 15} ],
	  my0a = Random[ Real, {-15, 15} ],
	  mRa = Random[ Real, {0, 30} ],
	  mx0b = Random[ Real, {-15, 15} ],
	  my0b = Random[ Real, {-15, 15} ],
	  mRb = Random[ Real, {0, 30} ]
	},
	(
	    Print[ "Circle A: ", x0a, " ", y0a, " ", Ra ];
	    Print[ "Circle B: ", x0b, " ", y0b, " ", Rb ];
	    specifics = { x0a -> mx0a, x0b -> mx0b, y0a -> my0a, y0b -> my0b, Ra -> mRa, Rb -> mRb };
	    points = {
		Point[{(x /. xsol1) /. ysol1xs1, y /. ysol1xs1} /. specifics // N],
		Point[{(x /. xsol1) /. ysol2xs1, y /. ysol2xs1} /. specifics // N],
		Point[{(x /. xsol2) /. ysol1xs2, y /. ysol1xs2} /. specifics // N],
		Point[{(x /. xsol2) /. ysol2xs2, y /. ysol2xs2} /. specifics // N]
		     };
	    Print[points];
	    points = Select[ points, (Im[#[[1]]]=={0,0})& ];
	    Show[ 
		ParametricPlot[ {x0a+Ra*Cos[t],y0a+Ra*Sin[t]} /. specifics
				, {t,0,2 Pi}
				, DisplayFunction -> Identity
			      ],
		ParametricPlot[ {x0b+Rb*Cos[t],y0b+Rb*Sin[t]} /. specifics
				, {t,0,2 Pi}
				, DisplayFunction -> Identity
			      ],
		Graphics[{points}]
		, AspectRatio -> 1
		, PlotRange -> {{-50,50}, {-50,50}}
		, DisplayFunction -> $DisplayFunction
		];
	)
      ]


sol1 = Simplify[ Expand[ {(x /. xsol1) /. ysol1xs1, y /. ysol1xs1}
			 /. { x0a -> -(d0a+1/2/curva)*Sin[phi0a],
			      y0a -> (d0a+1/2/curva)*Cos[phi0a],
			      Ra -> 1/2/curva,
			      x0b -> -(d0b+1/2/curvb)*Sin[phi0b],
			      y0b -> (d0b+1/2/curvb)*Cos[phi0b],
			      Rb -> 1/2/curvb }
		       ], Trig -> True ];

sol2 = Simplify[ Expand[ {(x /. xsol1) /. ysol2xs1, y /. ysol2xs1}
			 /. { x0a -> -(d0a+1/2/curva)*Sin[phi0a],
			      y0a -> (d0a+1/2/curva)*Cos[phi0a],
			      Ra -> 1/2/curva,
			      x0b -> -(d0b+1/2/curvb)*Sin[phi0b],
			      y0b -> (d0b+1/2/curvb)*Cos[phi0b],
			      Rb -> 1/2/curvb }
		       ], Trig -> True ];

sol3 = Simplify[ Expand[ {(x /. xsol2) /. ysol1xs2, y /. ysol1xs2}
			 /. { x0a -> -(d0a+1/2/curva)*Sin[phi0a],
			      y0a -> (d0a+1/2/curva)*Cos[phi0a],
			      Ra -> 1/2/curva,
			      x0b -> -(d0b+1/2/curvb)*Sin[phi0b],
			      y0b -> (d0b+1/2/curvb)*Cos[phi0b],
			      Rb -> 1/2/curvb }
		       ], Trig -> True ];

sol4 = Simplify[ Expand[ {(x /. xsol2) /. ysol2xs2, y /. ysol2xs2}
			 /. { x0a -> -(d0a+1/2/curva)*Sin[phi0a],
			      y0a -> (d0a+1/2/curva)*Cos[phi0a],
			      Ra -> 1/2/curva,
			      x0b -> -(d0b+1/2/curvb)*Sin[phi0b],
			      y0b -> (d0b+1/2/curvb)*Cos[phi0b],
			      Rb -> 1/2/curvb }
		       ], Trig -> True ];

dsol1dd0a = D[ sol1, d0a ];
dsol1dphi0a = D[ sol1, phi0a ];
dsol1dcurva = D[ sol1, curva ];
dsol1dd0b = D[ sol1, d0b ];
dsol1dphi0b = D[ sol1, phi0b ];
dsol1dcurvb = D[ sol1, curvb ];

dsol2dd0a = D[ sol2, d0a ];
dsol2dphi0a = D[ sol2, phi0a ];
dsol2dcurva = D[ sol2, curva ];
dsol2dd0b = D[ sol2, d0b ];
dsol2dphi0b = D[ sol2, phi0b ];
dsol2dcurvb = D[ sol2, curvb ];

dsol3dd0a = D[ sol3, d0a ];
dsol3dphi0a = D[ sol3, phi0a ];
dsol3dcurva = D[ sol3, curva ];
dsol3dd0b = D[ sol3, d0b ];
dsol3dphi0b = D[ sol3, phi0b ];
dsol3dcurvb = D[ sol3, curvb ];

dsol4dd0a = D[ sol4, d0a ];
dsol4dphi0a = D[ sol4, phi0a ];
dsol4dcurva = D[ sol4, curva ];
dsol4dd0b = D[ sol4, d0b ];
dsol4dphi0b = D[ sol4, phi0b ];
dsol4dcurvb = D[ sol4, curvb ];

DumpSave[ "intersections3.mx", { sol1, sol2, sol3, sol4,
				 dsol1dd0a, dsol1dphi0a, dsol1dcurva, dsol1dd0b, dsol1dphi0b, dsol1dcurvb,
				 dsol2dd0a, dsol2dphi0a, dsol2dcurva, dsol2dd0b, dsol2dphi0b, dsol2dcurvb,
				 dsol3dd0a, dsol3dphi0a, dsol3dcurva, dsol3dd0b, dsol3dphi0b, dsol3dcurvb,
				 dsol4dd0a, dsol4dphi0a, dsol4dcurva, dsol4dd0b, dsol4dphi0b, dsol4dcurvb
			       } ];

<< "intersections3.mx";

Clear[Compare];
Compare[ x_, y_ ] := If[ x == y, same, x ]
    /; Length[x] == 0  &&  Length[y] == 0;
Compare[ x_, y_ ] := Head[x] @@ Table[ Compare[ x[[i]], y[[i]] ], {i, 1, Length[x]} ]
    /; Head[x] === Head[y]  &&  Length[x] == Length[y];
Compare[ x_, y_ ] := x;

No use... they're different.

Clear[Discriminants];
Discriminants[ Sqrt[x_] ] := Print["sqrtarg",++myeye," = ",CForm[x],";\n"] /; ! NumericQ[x];
Discriminants[ x_ ] := Discriminants /@ x /; Length[x] > 1;
Discriminants[ x_ ] := {};

Clear[WithDiscrims];
WithDiscrims[ Sqrt[x_] ] := Sqrt[ToExpression["sqrtarg"<>ToString[++myeye]]] /; ! NumericQ[x];
WithDiscrims[ x_ ] := WithDiscrims /@ x /; Length[x] > 1;
WithDiscrims[ x_ ] := x;

myeye = 0;
Discriminants[sol4[[1]]];
Discriminants[sol4[[2]]];
myeye = 0;
Print[ "x = ",CForm[ WithDiscrims[sol4[[1]]] ], ";" ];
Print[ "y = ",CForm[ WithDiscrims[sol4[[2]]] ], ";" ];

Print[ "   double dxdd0a( ", CForm[ dsol4dd0a[[1]] ], " );" ];
Print[ "   double dxdphi0a( ", CForm[ dsol4dphi0a[[1]] ], " );" ];
Print[ "   double dxdcurva( ", CForm[ dsol4dcurva[[1]] ], " );" ];
Print[ "   double dxdd0b( ", CForm[ dsol4dd0b[[1]] ], " );" ];
Print[ "   double dxdphi0b( ", CForm[ dsol4dphi0b[[1]] ], " );" ];
Print[ "   double dxdcurvb( ", CForm[ dsol4dcurvb[[1]] ], " );\n" ];
Print[ "   double dydd0a( ", CForm[ dsol4dd0a[[2]] ], " );" ];
Print[ "   double dydphi0a( ", CForm[ dsol4dphi0a[[2]] ], " );" ];
Print[ "   double dydcurva( ", CForm[ dsol4dcurva[[2]] ], " );" ];
Print[ "   double dydd0b( ", CForm[ dsol4dd0b[[2]] ] ];
Print[ "   double dydphi0b( ", CForm[ dsol4dphi0b[[2]] ], " );" ];
Print[ "   double dydcurvb( ", CForm[ dsol4dcurvb[[2]] ], " );" ];

Exit
[Mathematica finished.]

