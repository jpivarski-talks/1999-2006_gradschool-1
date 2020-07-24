a = 4*xa^2 + 4*xb^2 + 2*(yb - ya)^2 + 2*(yb - ya)^2 - 8*xa*xb;
b = -4*xa^3 - 4*xb^3 - 4*xa*((yb - ya)^2 + (rb^2 - ra^2))
    - 4*xb*((yb - ya)^2 - (rb^2 - ra^2)) + 4*xa*xb^2 + 4*xa^2*xb;
c = xa^4 + xb^4 + 2*xa^2*((yb - ya)^2 + (rb^2 - ra^2))
    + 2*xb^2*((yb - ya)^2 - (rb^2 -ra^2)) - 2*xa^2*xb^2
    - 4*rb^2*(yb - ya)^2 + ((yb - ya)^2 + (rb^2 - ra^2))^2;

xsol1 = (-b + Sqrt[ b^2 - 4*a*c ])/2/a;
xsol2 = (-b - Sqrt[ b^2 - 4*a*c ])/2/a;

ysol1xs1 = yb + Sqrt[ rb^2 - (xsol1 - xb)^2 ];
ysol2xs1 = yb - Sqrt[ rb^2 - (xsol1 - xb)^2 ];
ysol1xs2 = yb + Sqrt[ rb^2 - (xsol2 - xb)^2 ];
ysol2xs2 = yb - Sqrt[ rb^2 - (xsol2 - xb)^2 ];

CircleMiss[ x_, y_, xa_, xb_, ya_, yb_, ra_, rb_ ] :=
    Abs[ (x - xa)^2 + (y - ya)^2 - ra^2 ] + Abs[ (x - xb)^2 + (y - yb)^2 - rb^2 ];

Module[ { mx0a = Random[ Real, {-15, 15} ],
	  my0a = Random[ Real, {-15, 15} ],
	  mRa = Random[ Real, {0, 30} ],
	  mx0b = Random[ Real, {-15, 15} ],
	  my0b = Random[ Real, {-15, 15} ],
	  mRb = Random[ Real, {0, 30} ],
	  specifics, points
	},
	(
	    Print[ "Circle A: ", mx0a, " ", my0a, " ", mRa ];
	    Print[ "Circle B: ", mx0b, " ", my0b, " ", mRb ];
	    specifics = { xa -> mx0a, xb -> mx0b, ya -> my0a, yb -> my0b, ra -> mRa, rb -> mRb };
	    points = ( 
		If[ ( b^2 - 4*a*c /. specifics ) > 0,
		    { If[ ( CircleMiss[ xsol1, ysol1xs1, xa, xb, ya, yb, ra, rb ] /. specifics )
			  < ( CircleMiss[ xsol1, ysol2xs1, xa, xb, ya, yb, ra, rb ] /. specifics ),
			  Point[ {xsol1, ysol1xs1} /. specifics // N ],
			  Point[ {xsol1, ysol2xs1} /. specifics // N ]
			],
		      If[ ( CircleMiss[ xsol2, ysol1xs2, xa, xb, ya, yb, ra, rb ] /. specifics )
			  < ( CircleMiss[ xsol2, ysol2xs2, xa, xb, ya, yb, ra, rb ] /. specifics ),
			  Point[ {xsol2, ysol1xs2} /. specifics // N ],
			  Point[ {xsol2, ysol2xs2} /. specifics // N ]
			]
		    },
		    {}
		  ]
		     );
	    Print[points];
	    Show[ 
		ParametricPlot[ {xa+ra*Cos[t] /. specifics, ya+ra*Sin[t] /. specifics}
				, {t,0,2 Pi}
				, DisplayFunction -> Identity
			      ],
		ParametricPlot[ {xb+rb*Cos[t] /. specifics, yb+rb*Sin[t] /. specifics}
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

(* This is how I found my mistakes... *)

ra = Sqrt[ (x - xa)^2 + (y - ya)^2 /. y -> yb + Sqrt[ rb^2 - (x - xb)^2 ] ];

Simplify[ (x - xa)^4 + (x - xb)^4 + ((yb - ya)^2 + rb^2 - ra^2)^2 - 2*(x - xa)^2*(x - xb)^2
	  - 2*(x - xb)^2*((yb - ya)^2 + rb^2 - ra^2) + 2*(x - xa)^2*((yb - ya)^2 + rb^2 - ra^2)
	  == 4*rb^2*(yb - ya)^2 - 4*(x - xb)^2*(yb - ya)^2 ]

Out[20]= True


Simplify[ (x - xa)^4
	  + (x - xb)^4
	  + ((yb - ya)^2 + rb^2 - ra^2)^2
	  - 2*(x - xa)^2*(x - xb)^2
	  + 2*(x - xb)^2*(yb - ya)^2
	  - 2*(x - xb)^2*(rb^2 - ra^2)
	  + 2*(x - xa)^2*((yb - ya)^2 + rb^2 - ra^2)
	  == 4*rb^2*(yb - ya)^2 ]

Out[67]= True

Simplify[ (x - xa)^4
	  + (x - xb)^4
	  + 2*(x - xa)^2*((yb - ya)^2 + rb^2 - ra^2)
	  + 2*(x - xb)^2*((yb - ya)^2 - rb^2 + ra^2)
	  - 2*(x - xa)^2*(x - xb)^2
	  == 4*rb^2*(yb - ya)^2 - ((yb - ya)^2 + (rb^2 - ra^2))^2 ]

Out[68]= True

Simplify[ 4*x^2*xa^2 + xa^4 - 4*x*xa^3
	  + 4*x^2*xb^2 + xb^4 - 4*x*xb^3
	  + 2*(x^2 - 2*x*xa + xa^2)*((yb - ya)^2 + (rb^2-ra^2))
	  + 2*(x^2 - 2*x*xb + xb^2)*((yb - ya)^2 - (rb^2 - ra^2))
	  - 8*x^2*xa*xb + 4*x*xa*xb^2 + 4*x*xa^2*xb - 2*xa^2*xb^2
	  == 4*rb^2*(yb - ya)^2 - ((yb - ya)^2 + (rb^2 - ra^2))^2 ]

Out[70]= True


Simplify[ x^2*( 4*xa^2 + 4*xb^2 + 2*(yb - ya)^2 + 2*(yb - ya)^2 - 8*xa*xb )
	  + x*(-4*xa^3 - 4*xb^3 - 4*xa*((yb - ya)^2 + (rb^2 - ra^2)) - 4*xb*((yb - ya)^2 - (rb^2 - ra^2)) + 4*xa*xb^2 + 4*xa^2*xb)
	  + ( xa^4 + xb^4 + 2*xa^2*((yb - ya)^2 + (rb^2 - ra^2)) + 2*xb^2*((yb - ya)^2 - (rb^2 -ra^2)) - 2*xa^2*xb^2 )
	  == 4*rb^2*(yb - ya)^2 - ((yb - ya)^2 + (rb^2 - ra^2))^2 ]

Out[71]= True

(* Now for the derivatives. *)

( pre = Simplify[ -b/2/a ] ) // CForm

Out[4]//CForm= (Power(rb,2)*(xa - xb) + Power(ra,2)*(-xa + xb) + 
      (xa + xb)*(Power(xa,2) - 2*xa*xb + Power(xb,2) + Power(ya - yb,2)))/
    (2.*(Power(xa,2) - 2*xa*xb + Power(xb,2) + Power(ya - yb,2)))

( disc = Simplify[ b^2/4/a^2 - c/a ] ) // CForm

Out[5]//CForm= (Power(4*Power(ra,2)*(xa - xb) - 
        4*(Power(rb,2)*(xa - xb) + 
           (xa + xb)*(Power(xa,2) - 2*xa*xb + Power(xb,2) + Power(ya - yb,2)))
        ,2) - 16*(Power(xa,2) - 2*xa*xb + Power(xb,2) + Power(ya - yb,2))*
       (Power(xa,4) - 2*Power(xa,2)*Power(xb,2) + Power(xb,4) + 
         2*Power(xb,2)*(Power(ra,2) - Power(rb,2) + Power(ya - yb,2)) + 
         2*Power(xa,2)*(-Power(ra,2) + Power(rb,2) + Power(ya - yb,2)) + 
         Power(-Power(ra,2) + Power(rb,2) + Power(ya - yb,2),2) - 
         4*Power(rb,2)*Power(ya - yb,2)))/
    (64.*Power(Power(xa,2) - 2*xa*xb + Power(xb,2) + Power(ya - yb,2),2))




Simplify[ D[ pre, xa ] ] // CForm

Simplify[ D[ pre, ya ] ] // CForm

Simplify[ D[ pre, ra ] ] // CForm

Simplify[ D[ pre, xb ] ] // CForm

Simplify[ D[ pre, yb ] ] // CForm

Simplify[ D[ pre, rb ] ] // CForm







Simplify[ D[ disc, xa ] ] // CForm

Simplify[ D[ disc, ya ] ] // CForm

Simplify[ D[ disc, ra ] ] // CForm

Simplify[ D[ disc, xb ] ] // CForm

Simplify[ D[ disc, yb ] ] // CForm

Simplify[ D[ disc, rb ] ] // CForm







(* Now to relate them to tracking variables. *)

ra = 1/2/curva;
xa = -(d0a+ra)*Sin[phi0a];
ya = (d0a+ra)*Cos[phi0a];
rb = 1/2/curvb;
xb = -(d0b+rb)*Sin[phi0b];
yb = (d0b+rb)*Cos[phi0b];

circ = { ra, xa, ya, rb, xb, yb };
track = { curva, d0a, phi0a, curvb, d0b, phi0b };

analjac = Table[ D[circ[[i]],track[[j]]], {i,1,6}, {j,1,6} ]

Out[301]//TableForm= 
 
       -1
    --------
           2
    2 curva       0             0                               0              0             0

    Sin[phi0a]
    ----------                        1
            2                   -((------- + d0a) Cos[phi0a])
     2 curva      -Sin[phi0a]      2 curva                      0              0             0

    -Cos[phi0a]
    -----------                       1
            2                   -((------- + d0a) Sin[phi0a])
     2 curva      Cos[phi0a]       2 curva                      0              0             0
     

                                                                   -1
                                                                --------
                                                                       2
    0             0             0                               2 curvb        0             0
     

                                                                Sin[phi0b]
                                                                ----------
                                                                        2                          1                       
    0             0             0                                2 curvb                     -((------- + d0b) Cos[phi0b]) 
     									       -Sin[phi0b]      2 curvb                    

                                                                -Cos[phi0b]
                                                                -----------                        1                      
                                                                        2                    -((------- + d0b) Sin[phi0b])
    0             0             0                                2 curvb       Cos[phi0b]       2 curvb                   
     


(* checking the calculations in the code *)

subs = { ra -> 1/2/curva,
	 xa -> -(d0a+ra)*Sin[phi0a],
	 ya -> (d0a+ra)*Cos[phi0a],
	 rb -> 1/2/curvb,
	 xb -> -(d0b+rb)*Sin[phi0b],
	 yb -> (d0b+rb)*Cos[phi0b] };

Clear[curva,d0a,phi0a,curvb,d0b,phi0b];
Clear[ra,xa,ya,rb,xb,yb];

dpredra = D[ pre, ra ];
dpredxa = D[ pre, xa ];
dpredya = D[ pre, ya ];
dpredrb = D[ pre, rb ];
dpredxb = D[ pre, xb ];
dpredyb = D[ pre, yb ];
ddiscdra = D[ disc, ra ];
ddiscdxa = D[ disc, xa ];
ddiscdya = D[ disc, ya ];
ddiscdrb = D[ disc, rb ];
ddiscdxb = D[ disc, xb ];
ddiscdyb = D[ disc, yb ];

{ dpredra, dpredxa, dpredya, dpredrb, dpredxb, dpredyb, ddiscdra, ddiscdxa, ddiscdya, ddiscdrb, ddiscdxb, ddiscdyb }

{ dpredra-dpredra2, dpredxa-dpredxa2, dpredya-dpredya2, dpredrb-dpredrb2, dpredxb-dpredxb2, dpredyb-dpredyb2, ddiscdra-ddiscdra2, ddiscdxa-ddiscdxa2, ddiscdya-ddiscdya2, ddiscdrb-ddiscdrb2, ddiscdxb-ddiscdxb2, ddiscdyb-ddiscdyb2 }

xderivs = Table[ D[ xsol1, {ra,xa,ya,rb,xb,yb}[[i]] ], {i,1,6} ];
yderivs = Table[ D[ ysol1xs1, {ra,xa,ya,rb,xb,yb}[[i]] ], {i,1,6} ];

xderivs

yderivs

xderivs2 = Table[ D[ xsol1 /. subs /. subs, {curva,d0a,phi0a,curvb,d0b,phi0b}[[i]] ], {i,1,6} ];
yderivs2 = Table[ D[ ysol1xs1 /. subs /. subs, {curva,d0a,phi0a,curvb,d0b,phi0b}[[i]] ], {i,1,6} ];

xderivs2

yderivs2


    0.03976256599627675     0.07749565111239967    0.004522843104342784                       0                       0 
    0.07749565111239967     0.01891232032227546     0.02256843775749992                       0                       0 
   0.004522843104342784     0.02256843775749992     0.06563615833002716                       0                       0 
                      0                       0                       0                       1                       0 
                      0                       0                       0                       0                       1 


    0.08276619769890439     0.08454237495040742      0.0718070009460738                       0                       0 
    0.08454237495040742     0.02911465804010132      0.0586718344676046                       0                       0 
     0.0718070009460738      0.0586718344676046     0.04434339426862392                       0                       0 
                      0                       0                       0                       1                       0 
                      0                       0                       0                       0                       1 

curva = 0.5402386547441023, d0a = 0.1594592120120853, phi0a = 3.850373851741081, curvb = 0.9282204657124546, d0b = 0.2746055482650228, phi0b = 4.20934598834193
ra = 0.9255168907468083, xa = 0.7062207038338519, ya = -0.8236658673480988, rb = 0.5386651323360184, xb = 0.7125223938924002, yb = -0.3920727459632
dpre_dra = 0.03130399621351166, dpre_dxa = -1.019437604207647, dpre_dya = 0.04438007047351418, dpre_drb = -0.01821940953383474, dpre_dxb = 2.019437604207647, dpre_dyb = -0.04438007047351418, ddisc_dra = -1.887810440334779, ddisc_dxa = -0.01945357306104121, ddisc_dya = -17.78449514581046, ddisc_drb = 2.175835486951854, ddisc_dxb = 0.01945357306104121, ddisc_dyb = 17.78449514581046
dx_dra = 3.073506063901209, dx_dxa = -0.9880882171475145, dx_dya = 28.70405201071967, dx_drb = -3.524573159849647, dx_dxb = 1.988088217147514, dx_dyb = -28.70405201071967
dy_dra = 2.099543674911636, dy_dxa = -0.6749732466555045, dy_dya = 19.60803381885835, dy_drb = -1.196623252559646, dy_dxb = 0.6749732466555045, dy_dyb = -18.60803381885835
jac = IdentityMatrix[6]; jac[[1,1]] = -1.713163030115279; jac[[1,2]] = 0; jac[[1,3]] = 0; jac[[1,4]] = 0; jac[[1,5]] = 0; jac[[1,6]] = 0; jac[[2,1]] = -1.115113224921423; jac[[2,2]] = 0.6509089942516368; jac[[2,3]] = 0.8236658673480988; jac[[2,4]] = 0; jac[[2,5]] = 0; jac[[2,6]] = 0; jac[[3,1]] = 1.300557597094073; jac[[3,2]] = -0.7591557687341397; jac[[3,3]] = 0.7062207038338519; jac[[3,4]] = 0; jac[[3,5]] = 0; jac[[3,6]] = 0; jac[[4,1]] = 0; jac[[4,2]] = 0; jac[[4,3]] = 0; jac[[4,4]] = -0.5803202495891604; jac[[4,5]] = 0; jac[[4,6]] = 0; jac[[5,1]] = 0; jac[[5,2]] = 0; jac[[5,3]] = 0; jac[[5,4]] = -0.508429952443283; jac[[5,5]] = 0.8761196129261862; jac[[5,6]] = 0.3920727459632; jac[[6,1]] = 0; jac[[6,2]] = 0; jac[[6,3]] = 0; jac[[6,4]] = 0.2797687894346801; jac[[6,5]] = -0.4820937915448296; jac[[6,6]] = 0.7125223938924002; 

dx_dcurva = 33.1676861867444, dx_dd0a = -22.434002177638, dx_dphi0a = 19.45754127550069, dx_dcurvb = -6.995920304787298, dx_dd0b = 15.57984834581823, dx_dphi0b = -19.67280464657583
dy_dcurva = 22.65718833703644, dy_dd0a = -15.32489814424772, dy_dphi0a = 13.29164701970885, dy_dcurvb = -4.854699006369528, dy_dd0b = 9.562174876523187, dy_dphi0b = -12.99400218797577

xderiv = { 33.1676861867444, -22.434002177638, 19.45754127550069, -6.995920304787298, 15.57984834581823, -19.67280464657583 };
yderiv = { 22.65718833703644, -15.32489814424772, 13.29164701970885, -4.854699006369528, 9.562174876523187, -12.99400218797577 };

sigma = IdentityMatrix[6]; sigma[[1,1]] = 0.03976256599627675; sigma[[1,2]] = 0.004522843104342784; sigma[[1,3]] = 0.07749565111239967; sigma[[1,4]] = 0; sigma[[1,5]] = 0; sigma[[1,6]] = 0; sigma[[2,1]] = 0.004522843104342784; sigma[[2,2]] = 0.06563615833002716; sigma[[2,3]] = 0.02256843775749992; sigma[[2,4]] = 0; sigma[[2,5]] = 0; sigma[[2,6]] = 0; sigma[[3,1]] = 0.07749565111239967; sigma[[3,2]] = 0.02256843775749992; sigma[[3,3]] = 0.01891232032227546; sigma[[3,4]] = 0; sigma[[3,5]] = 0; sigma[[3,6]] = 0; sigma[[4,1]] = 0; sigma[[4,2]] = 0; sigma[[4,3]] = 0; sigma[[4,4]] = 0.08276619769890439; sigma[[4,5]] = 0.0718070009460738; sigma[[4,6]] = 0.08454237495040742; sigma[[5,1]] = 0; sigma[[5,2]] = 0; sigma[[5,3]] = 0; sigma[[5,4]] = 0.0718070009460738; sigma[[5,5]] = 0.04434339426862392; sigma[[5,6]] = 0.0586718344676046; sigma[[6,1]] = 0; sigma[[6,2]] = 0; sigma[[6,3]] = 0; sigma[[6,4]] = 0.08454237495040742; sigma[[6,5]] = 0.0586718344676046; sigma[[6,6]] = 0.02911465804010132;

x_std[kCurva] = 2.725241669083598, x_std[kD0a] = -0.8833431689607765, x_std[kPhi0a] = 2.432038308422027, x_std[kCurvb] = -1.123469164880881, x_std[kD0b] = -0.9657322358379523, x_std[kPhi0b] = -0.2501204143290376
y_std[kCurva] = 1.861640676793541, y_std[kD0a] = -0.6034208244944629, y_std[kPhi0a] = 1.661350438693778, y_std[kCurvb] = -0.8137176824070937, y_std[kD0b] = -0.6869640309726889, y_std[kPhi0b] = -0.2277133724374501
sigx = 12.460444527527, sigy = 8.593566314199213

Sqrt[ xderiv . sigma . xderiv ]

Out[148]= 12.4604

Sqrt[ yderiv . sigma . yderiv ]

Out[149]= 8.59357


(* the final test *)


Show[ 
    ParametricPlot[ {1.07922+1.1145*Cos[t], 0.13999+1.1145*Sin[t]}
                   , {t,0,2 Pi}
                   , DisplayFunction -> Identity
                 ]
    , ParametricPlot[ {-0.566711+0.711254*Cos[t], -0.471654+0.711254*Sin[t]}
                   , {t,0,2 Pi}
                   , DisplayFunction -> Identity
                 ]
    , Graphics[{Point[{0.144527,-0.467015}]
               , Point[{-0.0250442,-0.0106994}]
               , Line[{{-0.027285,-0.0106994},{-0.0228035,-0.0106994}}]
               , Line[{{-0.0250442,-0.0129882},{-0.0250442,-0.0084105}}]}]
    , AspectRatio -> 1
    , PlotRange -> {{-0.25,0.25},{-0.25,0.25}}
    , DisplayFunction -> $DisplayFunction
    ];
Show[ 
    ParametricPlot[ {1.07922+1.1145*Cos[t], 0.13999+1.1145*Sin[t]}
                   , {t,0,2 Pi}
                   , DisplayFunction -> Identity
                 ]
    , ParametricPlot[ {-0.150766+0.141815*Cos[t], 0.0447057+0.141815*Sin[t]}
                   , {t,0,2 Pi}
                   , DisplayFunction -> Identity
                 ]
    , Graphics[{Point[{-0.0239211,-0.0187126}]
               , Point[{-0.0352017,0.126903}]
               , Line[{{-0.0275231,-0.0187126},{-0.0203191,-0.0187126}}]
               , Line[{{-0.0239211,-0.020924},{-0.0239211,-0.0165013}}]}]
    , AspectRatio -> 1
    , PlotRange -> {{-0.25,0.25},{-0.25,0.25}}
    , DisplayFunction -> $DisplayFunction
    ];
Show[ 
    ParametricPlot[ {1.07922+1.1145*Cos[t], 0.13999+1.1145*Sin[t]}
                   , {t,0,2 Pi}
                   , DisplayFunction -> Identity
                 ]
    , ParametricPlot[ {0.208329+-0.225601*Cos[t], -0.0127594+-0.225601*Sin[t]}
                   , {t,0,2 Pi}
                   , DisplayFunction -> Identity
                 ]
, AspectRatio -> 1
    , PlotRange -> {{-0.25,0.25},{-0.25,0.25}}
    , DisplayFunction -> $DisplayFunction
    ];
Show[ 
    ParametricPlot[ {1.07922+1.1145*Cos[t], 0.13999+1.1145*Sin[t]}
                   , {t,0,2 Pi}
                   , DisplayFunction -> Identity
                 ]
    , ParametricPlot[ {-0.0805685+-0.138455*Cos[t], -0.125896+-0.138455*Sin[t]}
                   , {t,0,2 Pi}
                   , DisplayFunction -> Identity
                 ]
    , Graphics[{Point[{0.0235121,-0.217204}]
               , Point[{-0.0266569,0.00163154}]
               , Line[{{-0.0294655,0.00163154},{-0.0238483,0.00163154}}]
               , Line[{{-0.0266569,-0.00204111},{-0.0266569,0.00530418}}]}]
    , AspectRatio -> 1
    , PlotRange -> {{-0.25,0.25},{-0.25,0.25}}
    , DisplayFunction -> $DisplayFunction
    ];
Show[ 
    ParametricPlot[ {-0.566711+0.711254*Cos[t], -0.471654+0.711254*Sin[t]}
                   , {t,0,2 Pi}
                   , DisplayFunction -> Identity
                 ]
    , ParametricPlot[ {-0.150766+0.141815*Cos[t], 0.0447057+0.141815*Sin[t]}
                   , {t,0,2 Pi}
                   , DisplayFunction -> Identity
                 ]
    , Graphics[{Point[{-0.0218768,-0.0144475}]
               , Point[{-0.236008,0.158043}]
               , Line[{{-0.034339,-0.0144475},{-0.0094147,-0.0144475}}]
               , Line[{{-0.0218768,-0.0480505},{-0.0218768,0.0191555}}]}]
    , AspectRatio -> 1
    , PlotRange -> {{-0.25,0.25},{-0.25,0.25}}
    , DisplayFunction -> $DisplayFunction
    ];
Show[ 
    ParametricPlot[ {-0.566711+0.711254*Cos[t], -0.471654+0.711254*Sin[t]}
                   , {t,0,2 Pi}
                   , DisplayFunction -> Identity
                 ]
    , ParametricPlot[ {0.208329+-0.225601*Cos[t], -0.0127594+-0.225601*Sin[t]}
                   , {t,0,2 Pi}
                   , DisplayFunction -> Identity
                 ]
    , Graphics[{Point[{0.0934354,-0.206912}]
               , Point[{-0.0171508,-0.0201392}]
               , Line[{{-0.0339009,-0.0201392},{-0.000400629,-0.0201392}}]
               , Line[{{-0.0171508,-0.467171},{-0.0171508,0.426893}}]}]
    , AspectRatio -> 1
    , PlotRange -> {{-0.25,0.25},{-0.25,0.25}}
    , DisplayFunction -> $DisplayFunction
    ];
Show[ 
    ParametricPlot[ {-0.566711+0.711254*Cos[t], -0.471654+0.711254*Sin[t]}
                   , {t,0,2 Pi}
                   , DisplayFunction -> Identity
                 ]
    , ParametricPlot[ {-0.0805685+-0.138455*Cos[t], -0.125896+-0.138455*Sin[t]}
                   , {t,0,2 Pi}
                   , DisplayFunction -> Identity
                 ]
    , Graphics[{Point[{0.0577838,-0.131231}]
               , Point[{-0.0402055,0.00654478}]
               , Line[{{-0.0827131,0.00654478},{0.0023021,0.00654478}}]
               , Line[{{-0.0402055,-0.0112212},{-0.0402055,0.0243108}}]}]
    , AspectRatio -> 1
    , PlotRange -> {{-0.25,0.25},{-0.25,0.25}}
    , DisplayFunction -> $DisplayFunction
    ];
Show[ 
    ParametricPlot[ {-0.150766+0.141815*Cos[t], 0.0447057+0.141815*Sin[t]}
                   , {t,0,2 Pi}
                   , DisplayFunction -> Identity
                 ]
    , ParametricPlot[ {0.208329+-0.225601*Cos[t], -0.0127594+-0.225601*Sin[t]}
                   , {t,0,2 Pi}
                   , DisplayFunction -> Identity
                 ]
    , Graphics[{Point[{-0.00898515,0.0478223}]
               , Point[{-0.0170381,-0.00249987}]
               , Line[{{-0.0191786,-0.00249987},{-0.0148976,-0.00249987}}]
               , Line[{{-0.0170381,-0.0321676},{-0.0170381,0.0271678}}]}]
    , AspectRatio -> 1
    , PlotRange -> {{-0.25,0.25},{-0.25,0.25}}
    , DisplayFunction -> $DisplayFunction
    ];
Show[ 
    ParametricPlot[ {-0.150766+0.141815*Cos[t], 0.0447057+0.141815*Sin[t]}
                   , {t,0,2 Pi}
                   , DisplayFunction -> Identity
                 ]
    , ParametricPlot[ {-0.0805685+-0.138455*Cos[t], -0.125896+-0.138455*Sin[t]}
                   , {t,0,2 Pi}
                   , DisplayFunction -> Identity
                 ]
    , Graphics[{Point[{-0.0171511,-0.0028189}]
               , Point[{-0.212241,-0.0830921}]
               , Line[{{-0.0423806,-0.0028189},{0.00807837,-0.0028189}}]
               , Line[{{-0.0171511,-0.0134308},{-0.0171511,0.00779299}}]}]
    , AspectRatio -> 1
    , PlotRange -> {{-0.25,0.25},{-0.25,0.25}}
    , DisplayFunction -> $DisplayFunction
    ];
Show[ 
    ParametricPlot[ {0.208329+-0.225601*Cos[t], -0.0127594+-0.225601*Sin[t]}
                   , {t,0,2 Pi}
                   , DisplayFunction -> Identity
                 ]
    , ParametricPlot[ {-0.0805685+-0.138455*Cos[t], -0.125896+-0.138455*Sin[t]}
                   , {t,0,2 Pi}
                   , DisplayFunction -> Identity
                 ]
    , Graphics[{Point[{0.0496008,-0.173075}]
               , Point[{-0.0170546,-0.0028687}]
               , Line[{{-0.0275253,-0.0028687},{-0.00658381,-0.0028687}}]
               , Line[{{-0.0170546,-0.00603624},{-0.0170546,0.000298843}}]}]
    , AspectRatio -> 1
    , PlotRange -> {{-0.25,0.25},{-0.25,0.25}}
    , DisplayFunction -> $DisplayFunction
    ];

Show[ 
    ParametricPlot[ {-3.3496+3.12398*Cos[t], -0.728287+3.12398*Sin[t]}
		    , {t,0,2 Pi}
		    , PlotPoints -> 100
		    , DisplayFunction -> Identity
		  ]
    , ParametricPlot[ {3.43324+-4.00587*Cos[t], 1.47022+-4.00587*Sin[t]}
		    , {t,0,2 Pi}
		    , PlotPoints -> 100
		    , DisplayFunction -> Identity
		  ]
    , Graphics[{Point[{-0.377827,0.234946}]
		, Point[{-0.377455,0.235066}]
		}]
    , AspectRatio -> 1
    , PlotRange -> {{-0.8,0},{0,0.5}}
    , DisplayFunction -> $DisplayFunction
    ];

ra = 3.12398, xa = -3.3496, ya = -0.728287, rb = -4.00587, xb = 3.43324, yb = 1.47022

ax = xa + ra / Sqrt[1 + ((yb - ya)/(xb - xa))^2];
ay = ya + (yb - ya)/(xb - xa) * (ax - xa);
bx = xb + rb / Sqrt[1 + ((yb - ya)/(xb - xa))^2];
by = yb + (yb - ya)/(xb - xa) * (bx - xb);

subs = {ra -> 3.12398, xa -> -3.3496, ya -> -0.728287, rb -> -4.00587, xb -> 3.43324, yb -> 1.47022};

{{ax, ay}, {bx, by}} /. subs

Out[203]= {{-0.377828, 0.234947}, {-0.377455, 0.235068}}

{D[ax,ra], D[ax,xa], D[ax,ya], D[ax,rb], D[ax,xb], D[ax,yb]} /. subs

Out[205]= {0.951278, 0.958347, 0.128509, 0, 0.0416535, -0.128509}

{D[ay,ra], D[ay,xa], D[ay,ya], D[ay,rb], D[ay,xb], D[ay,yb]} /. subs

Out[206]= {0.308336, 0.128509, 0.603522, 0, -0.128509, 0.396478}

{D[bx,ra], D[bx,xa], D[bx,ya], D[bx,rb], D[bx,xb], D[bx,yb]} /. subs

Out[207]= {0, 0.0534121, -0.164787, 0.951278, 0.946588, 0.164787}

{D[by,ra], D[by,xa], D[by,ya], D[by,rb], D[by,xb], D[by,yb]} /. subs

Out[208]= {0, -0.164787, 0.508402, 0.308336, 0.164787, 0.491598}

dax_dra = 0.951278, dax_dxa = 0.958347, dax_dya = 0.128509, dax_drb = 0, dax_dxb = 0.0416533, dax_dyb = -0.128509
day_dra = 0.308335, day_dxa = 0.128509, day_dya = 0.603522, day_drb = 0, day_dxb = -0.128509, day_dyb = 0.396478

dbx_dra = 0, dbx_dxa = 0.0534118, dbx_dya = -0.164787, dbx_drb = 0.951278, dbx_dxb = 0.946588, dbx_dyb = 0.164787
dby_dra = 0, dby_dxa = -0.164787, dby_dya = 0.508402, dby_drb = 0.308335, dby_dxb = 0.164787, dby_dyb = 0.491598


(* derivatives for the directional derivatives *)

axprime = ( ax*(bx - ax) + ay*(by - ay) ) / Sqrt[ (bx - ax)^2 + (by - ay)^2 ];
bxprime = ( bx*(bx - ax) + by*(by - ay) ) / Sqrt[ (bx - ax)^2 + (by - ay)^2 ];

Simplify[ D[ axprime, ax ] ] // CForm

Out[11]//CForm= 
   ((ax - bx)*(sqr(ax) - ax*bx + ay*(ay - by)) + 
      (-2*ax + bx)*(sqr(ax - bx) + sqr(ay - by)))/
    pow(sqr(ax - bx) + sqr(ay - by),1.5)

Simplify[ D[ axprime, bx ] ] // CForm

Out[12]//CForm= 
   ((ay - by)*(bx*ay - ax*by))/
    pow(sqr(ax) - 2*ax*bx + sqr(bx) + sqr(ay - by),1.5)

Simplify[ D[ axprime, ay ] ] // CForm

Out[13]//CForm= 
   (-(sqr(ax)*ay) - pow(ay - by,3) + ax*bx*(3*ay - by) + 
      sqr(bx)*(-2*ay + by))/
    pow(sqr(ax) - 2*ax*bx + sqr(bx) + sqr(ay - by),1.5)

Simplify[ D[ axprime, by ] ] // CForm

Out[14]//CForm= 
   ((ax - bx)*(-(bx*ay) + ax*by))/
    pow(sqr(ax) - 2*ax*bx + sqr(bx) + sqr(ay - by),1.5)



Simplify[ D[ bxprime, ax ] ] // CForm

Out[15]//CForm= 
   ((ay - by)*(-(bx*ay) + ax*by))/
    pow(sqr(ax) - 2*ax*bx + sqr(bx) + sqr(ay - by),1.5)

Simplify[ D[ bxprime, bx ] ] // CForm

Out[16]//CForm= 
   (-pow(ax,3) + 3*sqr(ax)*bx - ax*(3*sqr(bx) + ay*(ay - by)) + 
      bx*(sqr(bx) + 2*sqr(ay) - 3*ay*by + sqr(by)))/
    pow(sqr(ax) - 2*ax*bx + sqr(bx) + sqr(ay - by),1.5)

Simplify[ D[ bxprime, ay ] ] // CForm

Out[17]//CForm= 
   -(((ax - bx)*(-(bx*ay) + ax*by))/
      pow(sqr(ax) - 2*ax*bx + sqr(bx) + sqr(ay - by),1.5))

Simplify[ D[ bxprime, by ] ] // CForm

Out[18]//CForm= 
   (-pow(ay,3) + ax*bx*(ay - 3*by) - sqr(ax)*(ay - 2*by) + 
      sqr(bx)*by + 3*sqr(ay)*by - 3*ay*sqr(by) + pow(by,3))/
    pow(sqr(ax) - 2*ax*bx + sqr(bx) + sqr(ay - by),1.5)



<< Statistics`ContinuousDistributions`

Random[NormalDistribution[0,5]]


Inverse[{{Cos[theta],Sin[theta]},{-Sin[theta],Cos[theta]}}]//Simplify//MatrixForm

Out[40]//MatrixForm= Cos[theta]    -Sin[theta]

                     Sin[theta]    Cos[theta]



Show[ Graphics[{}]
    , ParametricPlot[ {0.165266 + 0.251969*Cos[t], 0.29183 + 0.251969*Sin[t]}
                    , {t,0,2 Pi}
                    , DisplayFunction -> Identity
                  ]
    , ParametricPlot[ {0.165266 + 0.251969*Cos[t], 0.29183 + 0.251969*Sin[t]}
                    , {t,0,2 Pi}
                    , DisplayFunction -> Identity
                  ]
    , ParametricPlot[ {-3.21821 + 3.76214*Cos[t], 1.26546 + 3.76214*Sin[t]}
                    , {t,0,2 Pi}
                    , DisplayFunction -> Identity
                  ]
    , Graphics[{RGBColor[0,0,1]
         , RGBColor[0,0,1]
                , Point[{0.375828, 0.153438}]
                , Line[{{0.341378, 0.153438}, {0.410278, 0.153438}}]
         , Line[{{0.375828, 0.0421636}, {0.375828, 0.264713}}]
         , RGBColor[1,0,0]
         , Line[{{1.44515, 1.07877}, {-0.815352, -0.608642}}]
         , RGBColor[0,0,1]
                , Point[{0.235121, 0.0497371}]
                , Line[{{0.228648, 0.0497371}, {0.241594, 0.0497371}}]
         , Line[{{0.235121, -0.0672402}, {0.235121, 0.166714}}]
         , RGBColor[1,0,0]
         , Line[{{0.00523892, 0.102405}, {0.00106429, 0.0208036}}]
         , RGBColor[0,0,1]
                , Point[{0.23034, -0.238271}]
                , Line[{{0.0658101, -0.238271}, {0.394871, -0.238271}}]
         , Line[{{0.23034, -1.94995}, {0.23034, 1.47341}}]
         , RGBColor[1,0,0]
         , Line[{{-0.00704626, -0.415163}, {-0.000906731, -0.0534243}}]
         , RGBColor[0,0,0]
         , Line[{{0.194338, 0.0490488}, {0.275873, 0.0490488}}]
         , Line[{{0.235106, -0.0740688}, {0.235106, 0.172166}}]
               }]
    , AspectRatio -> 1
    , PlotRange -> {{-0.0148943, 0.485106}, {-0.200951, 0.299049}}
    , DisplayFunction -> $DisplayFunction
    ];

Show[ Graphics[{}]
    , ParametricPlot[ {-0.52659 + 0.836878*Cos[t], 0.466862 + 0.836878*Sin[t]}
                    , {t,0,2 Pi}
                    , DisplayFunction -> Identity
                  ]
    , ParametricPlot[ {-0.52659 + 0.836878*Cos[t], 0.466862 + 0.836878*Sin[t]}
                    , {t,0,2 Pi}
                    , DisplayFunction -> Identity
                  ]
    , ParametricPlot[ {-0.52659 + 0.836878*Cos[t], 0.466862 + 0.836878*Sin[t]}
                    , {t,0,2 Pi}
                    , DisplayFunction -> Identity
                  ]
    , ParametricPlot[ {-1.42286 + -1.71046*Cos[t], 0.322447 + -1.71046*Sin[t]}
                    , {t,0,2 Pi}
                    , DisplayFunction -> Identity
                  ]
    , ParametricPlot[ {-1.42286 + -1.71046*Cos[t], 0.322447 + -1.71046*Sin[t]}
                    , {t,0,2 Pi}
                    , DisplayFunction -> Identity
                  ]
    , ParametricPlot[ {-13.8254 + -14.291*Cos[t], 2.53145 + -14.291*Sin[t]}
                    , {t,0,2 Pi}
                    , DisplayFunction -> Identity
                  ]
    , Graphics[{RGBColor[0,0,1]
         , RGBColor[0,0,1]
                , Point[{0.286796, 0.269965}]
                , Line[{{0.181151, 0.269965}, {0.39244, 0.269965}}]
         , Line[{{0.286796, -3.31593}, {0.286796, 3.85586}}]
         , RGBColor[1,0,0]
         , Line[{{0.0835698, 0.369576}, {0.0604843, 0.267483}}]
         , RGBColor[0,0,1]
                , Point[{0.283134, 0.255409}]
                , Line[{{-0.360525, 0.255409}, {0.926792, 0.255409}}]
         , Line[{{0.283134, -3.7514}, {0.283134, 4.26222}}]
         , RGBColor[1,0,0]
         , Line[{{-0.00116711, 0.282383}, {-0.00093443, 0.226086}}]
         , RGBColor[0,0,1]
                , Point[{0.178949, 0.0167744}]
                , Line[{{-2.81156, 0.0167744}, {3.16946, 0.0167744}}]
         , Line[{{0.178949, -11.6762}, {0.178949, 11.7098}}]
         , RGBColor[1,0,0]
         , RGBColor[0,0,1]
                , Point[{0.196589, -0.228065}]
                , Line[{{-0.447129, -0.228065}, {0.840306, -0.228065}}]
         , Line[{{0.196589, -3.50168}, {0.196589, 3.04555}}]
         , RGBColor[1,0,0]
         , RGBColor[0,0,1]
                , Point[{0.286099, 0.39411}]
                , Line[{{-1.28132, 0.39411}, {1.85351, 0.39411}}]
         , Line[{{0.286099, -4.62659}, {0.286099, 5.41481}}]
         , RGBColor[1,0,0]
         , RGBColor[0,0,1]
                , Point[{0.320726, 0.502116}]
                , Line[{{-2.44874, 0.502116}, {3.0902, 0.502116}}]
         , Line[{{0.320726, -7.91424}, {0.320726, 8.91848}}]
         , RGBColor[1,0,0]
         , RGBColor[0,0,0]
               }]
    , AspectRatio -> 1
      , PlotRegion -> {0.32+{-1,1}, 0.50+{-1,1}}
    , DisplayFunction -> $DisplayFunction
    ];

Show[ Graphics[{}]
    , ParametricPlot[ {-6.60677 + -7.72582*Cos[t], 3.83943 + -7.72582*Sin[t]}
                    , {t,0,2 Pi}
                    , DisplayFunction -> Identity
                  ]
    , AspectRatio -> 1
    , PlotRange -> {{-0.173877, 0.326123}, {-0.291913, 0.208087}}
    , DisplayFunction -> $DisplayFunction
    ];

Exit
[Mathematica finished.]
