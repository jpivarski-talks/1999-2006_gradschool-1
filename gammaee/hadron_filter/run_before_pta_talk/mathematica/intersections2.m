Suppose we start with two general circles:

circa = (x - x0a)^2 + (y - y0a)^2 == Ra^2;
circb = (x - x0b)^2 + (y - y0b)^2 == Rb^2;

Never mind for the moment how x0a, y0a, x0b and y0b relate to tracking
parameters. That's a solved problem.

x is easy to solve for, and there are two solutions.

( {{xsol1}, {xsol2}} = Solve[ circb, x ] )//InputForm

Out[6]//InputForm= 
{{x -> x0b - Sqrt[Rb^2 - y^2 + 2*y*y0b - y0b^2]}, 
 {x -> x0b + Sqrt[Rb^2 - y^2 + 2*y*y0b - y0b^2]}}

After plugging the above into circa, you lose the two solutions when
you get the square root onto one side and square both sides. A nice
cancellation of y^4 terms happens (because you should really only get
two solutions in the end), and you end up with this:

Solve[ 0 == (Ra^2 - Rb^2 + 2*y*(y0a + y0b) + y0b^2 - y0a^2)^2
       - 2*(Ra^2 + Rb^2)*(x0b - x0a)^2
       + 2*((y - y0a)^2 + (y - y0b)^2) * (x0b - x0a)^2 + (x0b - x0a)^4,
       y ] // Simplify // InputForm

Out[34]//InputForm= 
{{y -> (-(Ra^2*y0a) + Rb^2*y0a + x0a^2*y0a - 2*x0a*x0b*y0a + x0b^2*y0a + 
     y0a^3 - Ra^2*y0b + Rb^2*y0b + x0a^2*y0b - 2*x0a*x0b*y0b + x0b^2*y0b + 
     y0a^2*y0b - y0a*y0b^2 - y0b^3 + 
     Sqrt[-((x0a - x0b)^2*(Ra^4 + Rb^4 + x0a^4 - 4*x0a^3*x0b + 
         6*x0a^2*x0b^2 - 4*x0a*x0b^3 + x0b^4 + 2*x0a^2*y0a^2 - 
         4*x0a*x0b*y0a^2 + 2*x0b^2*y0a^2 + y0a^4 + 2*x0a^2*y0b^2 - 
         4*x0a*x0b*y0b^2 + 2*x0b^2*y0b^2 + 2*y0a^2*y0b^2 + 8*y0a*y0b^3 + 
         5*y0b^4 - 2*Ra^2*(Rb^2 + x0a^2 - 2*x0a*x0b + x0b^2 + y0a^2 - 
           y0b^2) - 2*Rb^2*(x0a^2 - 2*x0a*x0b + x0b^2 + y0a^2 + 4*y0a*y0b + 
           3*y0b^2)))])/(2*(x0a^2 - 2*x0a*x0b + x0b^2 + (y0a + y0b)^2))}, 
 {y -> (-(Ra^2*y0a) + Rb^2*y0a + x0a^2*y0a - 2*x0a*x0b*y0a + x0b^2*y0a + 
     y0a^3 - Ra^2*y0b + Rb^2*y0b + x0a^2*y0b - 2*x0a*x0b*y0b + x0b^2*y0b + 
     y0a^2*y0b - y0a*y0b^2 - y0b^3 - 
     Sqrt[-((x0a - x0b)^2*(Ra^4 + Rb^4 + x0a^4 - 4*x0a^3*x0b + 
         6*x0a^2*x0b^2 - 4*x0a*x0b^3 + x0b^4 + 2*x0a^2*y0a^2 - 
         4*x0a*x0b*y0a^2 + 2*x0b^2*y0a^2 + y0a^4 + 2*x0a^2*y0b^2 - 
         4*x0a*x0b*y0b^2 + 2*x0b^2*y0b^2 + 2*y0a^2*y0b^2 + 8*y0a*y0b^3 + 
         5*y0b^4 - 2*Ra^2*(Rb^2 + x0a^2 - 2*x0a*x0b + x0b^2 + y0a^2 - 
           y0b^2) - 2*Rb^2*(x0a^2 - 2*x0a*x0b + x0b^2 + y0a^2 + 4*y0a*y0b + 
           3*y0b^2)))])/(2*(x0a^2 - 2*x0a*x0b + x0b^2 + (y0a + y0b)^2))}}

preamble = -(Ra^2*y0a) + Rb^2*y0a + x0a^2*y0a - 2*x0a*x0b*y0a + x0b^2*y0a
    + y0a^3 - Ra^2*y0b + Rb^2*y0b + x0a^2*y0b - 2*x0a*x0b*y0b + x0b^2*y0b
    + y0a^2*y0b - y0a*y0b^2 - y0b^3;

Out[48]//CForm= 
   -(pow(Ra,2)*y0a) + pow(Rb,2)*y0a + pow(x0a,2)*y0a - 2*x0a*x0b*y0a + 
    pow(x0b,2)*y0a + pow(y0a,3) - pow(Ra,2)*y0b + pow(Rb,2)*y0b + 
    pow(x0a,2)*y0b - 2*x0a*x0b*y0b + pow(x0b,2)*y0b + pow(y0a,2)*y0b - 
    y0a*pow(y0b,2) - pow(y0b,3)

discriminant =
    -((x0a - x0b)^2 *
      (Ra^4 + Rb^4 + x0a^4 - 4*x0a^3*x0b + 6*x0a^2*x0b^2
       - 4*x0a*x0b^3 + x0b^4 + 2*x0a^2*y0a^2 - 4*x0a*x0b*y0a^2
       + 2*x0b^2*y0a^2 + y0a^4 + 2*x0a^2*y0b^2 - 4*x0a*x0b*y0b^2
       + 2*x0b^2*y0b^2 + 2*y0a^2*y0b^2 + 8*y0a*y0b^3 + 5*y0b^4
       - 2*Ra^2*(Rb^2 + x0a^2 - 2*x0a*x0b + x0b^2 + y0a^2 - y0b^2)
       - 2*Rb^2*(x0a^2 - 2*x0a*x0b + x0b^2 + y0a^2 + 4*y0a*y0b + 3*y0b^2)
      )
     );

Out[49]//CForm= 
   -(pow(x0a - x0b,2)*(pow(Ra,4) + pow(Rb,4) + pow(x0a,4) - 
        4*pow(x0a,3)*x0b + 6*pow(x0a,2)*pow(x0b,2) - 
        4*x0a*pow(x0b,3) + pow(x0b,4) + 2*pow(x0a,2)*pow(y0a,2) - 
        4*x0a*x0b*pow(y0a,2) + 2*pow(x0b,2)*pow(y0a,2) + pow(y0a,4) + 
        2*pow(x0a,2)*pow(y0b,2) - 4*x0a*x0b*pow(y0b,2) + 
        2*pow(x0b,2)*pow(y0b,2) + 2*pow(y0a,2)*pow(y0b,2) + 
        8*y0a*pow(y0b,3) + 5*pow(y0b,4) - 
        2*pow(Ra,2)*(pow(Rb,2) + pow(x0a,2) - 2*x0a*x0b + 
           pow(x0b,2) + pow(y0a,2) - pow(y0b,2)) - 
        2*pow(Rb,2)*(pow(x0a,2) - 2*x0a*x0b + pow(x0b,2) + 
           pow(y0a,2) + 4*y0a*y0b + 3*pow(y0b,2))))

denominator = 2*(x0a^2 - 2*x0a*x0b + x0b^2 + (y0a + y0b)^2);

Out[50]//CForm= 
   2*(pow(x0a,2) - 2*x0a*x0b + pow(x0b,2) + pow(y0a + y0b,2))

( y /. Out[34][[1]] ) == (preamble + Sqrt[discriminant]) / denominator

Out[42]= True

( y /. Out[34][[2]] ) == (preamble - Sqrt[discriminant]) / denominator

Out[44]= True



But which x solution corresponds to which y solution?

{ysol1, ysol2} = {{y -> (preamble + Sqrt[discriminant]) / denominator},
		  {y -> (preamble - Sqrt[discriminant]) / denominator}};

specifics = { x0a -> 12, x0b -> -13, y0a -> 4, y0b -> 15, Ra -> 35, Rb -> 30 };
Show[ 
    ParametricPlot[ {x0a+Ra*Cos[t],y0a+Ra*Sin[t]} /. specifics
		    , {t,0,2 Pi}
		    , DisplayFunction -> Identity
		  ],
    ParametricPlot[ {x0b+Rb*Cos[t],y0b+Rb*Sin[t]} /. specifics
		    , {t,0,2 Pi}
		    , DisplayFunction -> Identity
		  ],
    Graphics[{
	Point[{(x /. xsol1) /. ysol1, y /. ysol1} /. specifics],
	Point[{(x /. xsol2) /. ysol1, y /. ysol1} /. specifics]
	     }]
    , AspectRatio -> 1
    , PlotRange -> {{-50,50}, {-50,50}}
    , DisplayFunction -> $DisplayFunction
    ];

Exit
[Mathematica finished.]
