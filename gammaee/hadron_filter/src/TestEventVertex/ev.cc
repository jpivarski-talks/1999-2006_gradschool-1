#include <iostream>
#include <vector>
#include <math.h>
#include <assert.h>
#include "ev.h"

int main( int argc, char** argv )
{
   for ( double theta = 0.;  theta < 2*M_PI;  theta += 0.1*M_PI ) {
      double x = cos(theta);
      double y = sin(theta);

      cout << "Show[ ParametricPlot[{Cos[t],Sin[t]},{t,0," << atan2(y,x)
 << "}, DisplayFunction -> Identity ]," << endl
	   << "      Graphics[{Point[{" << x << "," << y << "}]}]," << endl
	   << "      PlotRange -> {{-2,2},{-2,2}}, AspectRatio -> 1, DisplayFunction -> $DisplayFunction ];" << endl;
   }
}
