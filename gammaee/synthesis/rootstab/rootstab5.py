from math import *
import rootntuple, cPickle as pickle

class RunSummary : pass
runsummary = pickle.load(open("/home/mccann/synthesis/lumieff/runsummary.p"))

low_runs = [124684, 124685, 124687, 124688, 124690, 124691, 124699, 124701, 124702, 124704, 124705, 124706, 124707, 124708, 124709, 124712, 124713, 124714, 124716, 124718, 124719, 124720, 124721, 124722, 124725, 124726, 124727, 124728, 124729, 124730, 124731, 124732, 124733, 124734, 124735, 124736]
high_runs = [125360, 125361, 125362, 125363, 125364, 125366, 125368, 125369, 125370, 125372, 125373, 125375, 125377, 125378, 125380, 125382, 125384, 125389, 125391, 125392, 125395, 125396, 125397, 125398, 125399, 125400, 125403, 125404, 125405, 125407, 125408, 125416]

def getntuple(run):
  return rootntuple.RootNtuple("/home/mccann/synthesis/root/db_"+str(run)+".root:/UpsilonGammaEEAnalysisProc/nt1")

low = getntuple(low_runs[0])
for r in low_runs[1:]:
  low += getntuple(r)

high = getntuple(high_runs[0])
for r in high_runs[1:]:
  high += getntuple(r)

def hadron(type):
  return type % 10 == 1

def gamgam(type):
  return int(floor(type / 10)) % 10 == 1

def bhabha(type):
  return int(floor(type / 100)) % 10 == 1

#    m_cut[0] = (v[k_trignum] > 0);
#    m_cut[1] = (fabs(v[k_d0close]) < 0.005);
#    m_cut[2] = (fabs(v[k_wz]) < 0.075  ||
# 	       (v[k_wz] == -1000.  &&  fabs(v[k_z0close]) < 0.075));
#    m_cut[3] = (v[k_p1] < 0.8);
#    m_cut[4] = (v[k_coolvisen] > 0.4);
#    m_cut[5] = (v[k_l4dec] > 0.);

# ['run', 'event', 'trig', 'type', 'd0close', 'anyz', 'p1x', 'p1y', 'p1z', 'p2x', 'p2y', 'p2z', 'visen', 'coolvisen', 'frozenvisen', 'tracks', 'rawtk', 'oppositesides', 'e1', 'e2', 'e3', 'phi1', 'cos1', 'phi2', 'cos2', 'oppositecharge', 'eisr', 'econstr', 'cosp', 'cosn', 'wpz', 'pdotp', 'ccen', 'neue', 'l4dec', 'chen']

cuts_trigger = lambda n: int(n.trig) % 10000 % 1000 > 0
cuts_d0close = lambda n: abs(n.d0close) < 0.005
cuts_anyz    = lambda n: abs(n.anyz) < 0.075
cuts_p1      = lambda n: sqrt(n.p1x**2+n.p1y**2+n.p1z**2) / runsummary[int(n.run)].energy < 0.8
cuts_visen   = lambda n: n.coolvisen > 0.4
cuts_l4dec   = lambda n: int(n.l4dec) > 0
cuts_hadron = [cuts_trigger, cuts_d0close, cuts_anyz, cuts_p1, cuts_visen, cuts_l4dec]

# for n in low:
# #   if hadron(n.type) and not cuts_all(n.trig, n.d0close, n.anyz, n.p1x, n.p1y, n.p1z, n.run, n.coolvisen, n.l4dec):
# #     print hadron(n.type), "vs", \
# #           cuts_trigger(n.trig), \
# #           cuts_d0close(n.d0close), \
# #           cuts_anyz(n.anyz), \
# #           cuts_p1(n.p1x, n.p1y, n.p1z, n.run), \
# #           cuts_visen(n.coolvisen), \
# #           cuts_l4dec(n.l4dec)
#   if not hadron(n.type) and cuts_all(n.trig, n.d0close, n.anyz, n.p1x, n.p1y, n.p1z, n.run, n.coolvisen, n.l4dec):
# #     print hadron(n.type), "vs", \
# #           cuts_trigger(n.trig), \
# #           cuts_d0close(n.d0close), \
# #           cuts_anyz(n.anyz), \
# #           cuts_p1(n.p1x, n.p1y, n.p1z, n.run), \
# #           cuts_visen(n.coolvisen), \
# #           cuts_l4dec(n.l4dec)

# #    print int(n.type)
# #    print n.rawtk
# #    print int(n.trig) % 10000 % 1000
# #    print abs(n.d0close), abs(n.anyz)
# #     print sqrt(n.p1x**2+n.p1y**2+n.p1z**2) / runsummary[int(n.run)].energy
#     print sqrt(n.p1x**2+n.p1y**2+n.p1z**2) / runsummary[int(n.run)].energy + ccen - neue - e1/2. - e2/2.
# #    print n.coolvisen

# # fails this test because sqrt(n.p1x**2+n.p1y**2+n.p1z**2) != n.p1
# # (p1 includes bremsstrahlung showers)

#    m_cut[0] = (v[k_trignum] > 0);
#    m_cut[1] = (v[k_oppositecharge] > 0);
#    m_cut[2] = (v[k_p2] > 0.7);
#    m_cut[3] = (fabs(v[k_d0close]) < 0.005);
#    m_cut[4] = (fabs(v[k_wz]) < 0.075  ||
# 	       (v[k_wz] == -1000.  &&  fabs(v[k_z0close]) < 0.075));
#    m_cut[5] = (v[k_eisr] < 0.2);
#    m_cut[6] = (v[k_econstr] < 0.2);
#    m_cut[7] = (v[k_cos1] < 0.79  &&  v[k_cos2] < 0.76) || (v[k_cos1] < 0.76  &&  v[k_cos2] < 0.79);
#    m_cut[8] = (v[k_e2] > 0.4);
#    m_cut[9] = (v[k_l4dec] > 0);

cuts_oppositecharge = lambda n: n.oppositecharge != 0.
cuts_p2             = lambda n: sqrt(n.p2x**2+n.p2y**2+n.p2z**2) / runsummary[int(n.run)].energy > 0.7
cuts_eisr           = lambda n: n.eisr < 0.2
cuts_econstr        = lambda n: n.econstr < 0.2
cuts_cosp           = lambda n: 0.6 < n.cosp < 0.8
cuts_e2             = lambda n: n.e2 > 0.4
cuts_bhabha = [cuts_trigger, cuts_oppositecharge, cuts_p2, cuts_d0close, cuts_anyz, cuts_eisr, cuts_econstr, cuts_cosp, cuts_e2, cuts_l4dec]

low_hadrons = 0
low_bhabhas = 0
for n in low:
  ishad = True
  for c in cuts_hadron:
    if not c(n):
      ishad = False
      break
  isbha = True
  for c in cuts_bhabha:
    if not c(n):
      isbha = False
      break

  if ishad: low_hadrons += 1
  if isbha: low_bhabhas += 1

high_hadrons = 0
high_bhabhas = 0
for n in high:
  ishad = True
  for c in cuts_hadron:
    if not c(n):
      ishad = False
      break
  isbha = True
  for c in cuts_bhabha:
    if not c(n):
      isbha = False
      break

  if ishad: high_hadrons += 1
  if isbha: high_bhabhas += 1

print low_hadrons, low_bhabhas, high_hadrons, high_bhabhas
print 1. * low_hadrons / low_bhabhas, 1. * high_hadrons / high_bhabhas
print (1. * high_hadrons / high_bhabhas) / (1. * low_hadrons / low_bhabhas)


