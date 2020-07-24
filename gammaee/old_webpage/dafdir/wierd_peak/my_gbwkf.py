import math

def abs(x):
    if (x>0.): return x
    else: return -x

def g(x, sig):
    if (abs(x) > 5.*sig):
        return 0
    else:
        return math.exp( -x**2./2./sig**2. ) / sig / math.sqrt(2.*math.pi)

def bw(x, gam):
    return (gam/2) / (x^2 + gam^2/4) / math.pi
