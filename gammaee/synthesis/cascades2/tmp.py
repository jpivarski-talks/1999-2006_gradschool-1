from math import *

s1 = 9.441
s4 = 9.480
bins = list(Numeric.arange(s1, s4, 0.0005))+[s4]

P1 = 35348.
P2 = -3696.7
P3 = 0.13580E+07
P4 = 0.12332E-02
P5 = 0.25350E-02
P6 = 9.4633

def g12(x):
  return 0.8*exp(-(x-P6)**2/2./P4**2)/sqrt(6.28318)*P4 + 0.2*exp(-(x-P6)**2/2./P5**2)/sqrt(6.28318)*P5

print sum(map(g12, bins))*P3

# ~~~Roughly~~~ agrees with what we get from subtract and count

