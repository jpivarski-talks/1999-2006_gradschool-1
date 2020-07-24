execfile("utilities.py")

tmprunlist = []
p1overflows = []

runlist1sc = []
hadxs1sc = []
hadxs1sc_err = []
oldhadxs1sc = []
oldhadxs1sc_err = []

runlist2sc = []
hadxs2sc = []
hadxs2sc_err = []
oldhadxs2sc = []
oldhadxs2sc_err = []

runlist3sc = []
hadxs3sc = []
hadxs3sc_err = []
oldhadxs3sc = []
oldhadxs3sc_err = []

for r in initialrunlist:
  if r not in mybadruns:
    therun = getdb(r)

    tmprunlist.append(r)
    p1overflows.append(1.*therun.hadron_p1.overflow/therun.bhabha)

    if runsummary[r].res == 1 and runsummary[r].kind == 'c':
      runlist1sc.append(r)
      
      h = therun.hadron
      g = therun.bhabha
      if r in mycarefulscan:
        h = therun.hadron_vstime.sum(0,0.99)
        g = therun.bhabha_vstime.sum(0,0.99)

      hadxs1sc.append(1.*h/g)
      hadxs1sc_err.append(1.*h/g*sqrt(1./h+1./g))

      h = therun.oldhadronall
      g = therun.bhabha
      if r in mycarefulscan:
        h = therun.oldhadronall_vstime.sum(0,0.99)
        g = therun.bhabha_vstime.sum(0,0.99)

      oldhadxs1sc.append(1.*h/g)
      oldhadxs1sc_err.append(1.*h/g*sqrt(1./h+1./g))

    if runsummary[r].res == 2 and runsummary[r].kind == 'c':
      runlist2sc.append(r)
      
      h = therun.hadron
      g = therun.bhabha
      if r in mycarefulscan:
        h = therun.hadron_vstime.sum(0,0.99)
        g = therun.bhabha_vstime.sum(0,0.99)

      hadxs2sc.append(1.*h/g)
      hadxs2sc_err.append(1.*h/g*sqrt(1./h+1./g))

      h = therun.oldhadronall
      g = therun.bhabha
      if r in mycarefulscan:
        h = therun.oldhadronall_vstime.sum(0,0.99)
        g = therun.bhabha_vstime.sum(0,0.99)

      oldhadxs2sc.append(1.*h/g)
      oldhadxs2sc_err.append(1.*h/g*sqrt(1./h+1./g))

    if runsummary[r].res == 3 and runsummary[r].kind == 'c':
      runlist3sc.append(r)
      
      h = therun.hadron
      g = therun.bhabha
      if r in mycarefulscan:
        h = therun.hadron_vstime.sum(0,0.99)
        g = therun.bhabha_vstime.sum(0,0.99)

      hadxs3sc.append(1.*h/g)
      hadxs3sc_err.append(1.*h/g*sqrt(1./h+1./g))

      h = therun.oldhadronall
      g = therun.bhabha
      if r in mycarefulscan:
        h = therun.oldhadronall_vstime.sum(0,0.99)
        g = therun.bhabha_vstime.sum(0,0.99)

      oldhadxs3sc.append(1.*h/g)
      oldhadxs3sc_err.append(1.*h/g*sqrt(1./h+1./g))

p = biggles.FramedPlot()
p.add(biggles.Points(tmprunlist, p1overflows, symboltype="filled circle", symbolsize=1))
# p.add(biggles.LineX(123102.5, type="dotted"))
# p.add(biggles.LineX(125651.5, type="dotted"))
p.add(biggles.LineX(123313.5, type="dotted"))
p.show()
p.write_eps("/cdat/dafe/mccann/tmp.ps")

weird1s = RunRecord()
for r, p1over in zip(tmprunlist, p1overflows):
  if p1over > 0.015:
    print r, runsummary[r].res, runsummary[r].kind
    if runsummary[r].res == 1 and runsummary[r].kind == 'c':
      weird1s += getdb(r)


p = (cccont1.hadron_p1 / cccont1.hadron).plot()
p.add((weird1s.hadron_p1 / weird1s.hadron).errorbars())
p.add((weird1s.hadron_p1 / weird1s.hadron).points())
p.add(biggles.LineX(0.8, linetype="dotted"))
p.yrange = 0, 0.03
p.show()
p.write_eps("/cdat/dafe/mccann/tmp.ps")


for r, p1over in zip(tmprunlist, p1overflows):
  if p1over > 0.015:
    print r, runsummary[r].res, runsummary[r].kind
    if runsummary[r].res == 1 and runsummary[r].kind == 'c':
      getdb(r).hadron_p1.plot().show()
      raw_input(str(r))


for r, p1over in zip(tmprunlist, p1overflows):
  if p1over > 0.015:
    print str(r)+", "


weirdones = [124452, 124454, 124456, 124458, 124462, 124464, 124465, 124466, 124467, 124469, 124472, 124473, 124474, 124475, 124477, 124478, 124479, 124480]
for r in initialrunlist:
#  if r in mybadruns and r in rdrunlists["all"]:
  if r in weirdones and r in rdrunlists["all"]:
    print r
    

########################################





p = biggles.FramedPlot()
p.add(biggles.Points(range(len(oldhadxs1sc)), oldhadxs1sc, symboltype="filled circle"))
p.add(biggles.SymmetricErrorBarsY(range(len(oldhadxs1sc)), oldhadxs1sc, oldhadxs1sc_err))
p.show()
themean = jt.wmean(zip(oldhadxs1sc, oldhadxs1sc_err))[0]
thechi2 = 0.
for h, e in zip(oldhadxs1sc, oldhadxs1sc_err):
  thechi2 += (h-themean)**2/e**2
print thechi2 / (len(oldhadxs1sc) - 1)

p = biggles.FramedPlot()
p.add(biggles.Points(range(len(oldhadxs2sc)), oldhadxs2sc, symboltype="filled circle"))
p.add(biggles.SymmetricErrorBarsY(range(len(oldhadxs2sc)), oldhadxs2sc, oldhadxs2sc_err))
p.add(biggles.LineX(98.5, linetype="dotted"))
p.yrange = 0.4, 0.6
p.show()
themean = jt.wmean(zip(oldhadxs2sc, oldhadxs2sc_err))[0]
thechi2 = 0.
for h, e in zip(oldhadxs2sc, oldhadxs2sc_err):
  thechi2 += (h-themean)**2/e**2
print thechi2 / (len(oldhadxs2sc) - 1)


print jt.wmean(zip(oldhadxs2sc[0:98], oldhadxs2sc_err[0:98])), jt.wmean(zip(oldhadxs2sc[99:-1], oldhadxs2sc_err[99:-1])), jt.wmean(zip(oldhadxs2sc[0:98], oldhadxs2sc_err[0:98]))[0]-jt.wmean(zip(oldhadxs2sc[99:-1], oldhadxs2sc_err[99:-1]))[0]



p = biggles.FramedPlot()
p.add(biggles.Points(range(len(oldhadxs3sc)), oldhadxs3sc, symboltype="filled circle"))
p.add(biggles.SymmetricErrorBarsY(range(len(oldhadxs3sc)), oldhadxs3sc, oldhadxs3sc_err))
p.show()
themean = jt.wmean(zip(oldhadxs3sc, oldhadxs3sc_err))[0]
thechi2 = 0.
for h, e in zip(oldhadxs3sc, oldhadxs3sc_err):
  thechi2 += (h-themean)**2/e**2
print thechi2 / (len(oldhadxs3sc) - 1)








p = biggles.FramedPlot()
p.add(biggles.Points(range(len(hadxs1sc)), hadxs1sc, symboltype="filled circle"))
p.add(biggles.SymmetricErrorBarsY(range(len(hadxs1sc)), hadxs1sc, hadxs1sc_err))
p.show()
themean = jt.wmean(zip(hadxs1sc, hadxs1sc_err))[0]
thechi2 = 0.
for h, e in zip(hadxs1sc, hadxs1sc_err):
  thechi2 += (h-themean)**2/e**2
print thechi2 / (len(hadxs1sc) - 1)

p = biggles.FramedPlot()
p.add(biggles.Points(range(len(hadxs2sc)), hadxs2sc, symboltype="filled circle"))
p.add(biggles.SymmetricErrorBarsY(range(len(hadxs2sc)), hadxs2sc, hadxs2sc_err))
p.add(biggles.LineX(98.5, linetype="dotted"))
p.yrange = 0.5, 0.7
p.show()
themean = jt.wmean(zip(hadxs2sc, hadxs2sc_err))[0]
thechi2 = 0.
for h, e in zip(hadxs2sc, hadxs2sc_err):
  thechi2 += (h-themean)**2/e**2
print thechi2 / (len(hadxs2sc) - 1)

print jt.wmean(zip(hadxs2sc[0:98], hadxs2sc_err[0:98])), jt.wmean(zip(hadxs2sc[99:-1], hadxs2sc_err[99:-1])), jt.wmean(zip(hadxs2sc[0:98], hadxs2sc_err[0:98]))[0]-jt.wmean(zip(hadxs2sc[99:-1], hadxs2sc_err[99:-1]))[0]

p = biggles.FramedPlot()
p.add(biggles.Points(range(len(hadxs3sc)), hadxs3sc, symboltype="filled circle"))
p.add(biggles.SymmetricErrorBarsY(range(len(hadxs3sc)), hadxs3sc, hadxs3sc_err))
p.show()
themean = jt.wmean(zip(hadxs3sc, hadxs3sc_err))[0]
thechi2 = 0.
for h, e in zip(hadxs3sc, hadxs3sc_err):
  thechi2 += (h-themean)**2/e**2
print thechi2 / (len(hadxs3sc) - 1)



###############################

# run trigger_ccstudy.py first for cc{peak,cont}{2,3}

p = biggles.Table(2,1)

p[0,0] = (ccpeak2.gamgam_e3GeVin + ccpeak2.gamgam_e3GeVout).plot()
p[0,0].add(((cccont2.gamgam_e3GeVin + cccont2.gamgam_e3GeVout) * 1. * (ccpeak2.gamgam_pureggin + ccpeak2.gamgam_pureggout) / (cccont2.gamgam_pureggin + cccont2.gamgam_pureggout)).steps(linetype="longdashed"))
themc = (getmc(2, "chibkgnd").gamgam_e3GeVin + getmc(2, "chibkgnd").gamgam_e3GeVout)
themc *= (ccpeak2.gamgam_e3GeVin + ccpeak2.gamgam_e3GeVout).sum() / themc.sum()
p[0,0].add(themc.steps(linetype="dotted"))
p[0,0].x1.label = r"Third-biggest shower (GeV) in $\Upsilon(2S)$ gamgam"

p[1,0] = (ccpeak3.gamgam_e3GeVin + ccpeak3.gamgam_e3GeVout).plot()
p[1,0].add(((cccont3.gamgam_e3GeVin + cccont3.gamgam_e3GeVout) * 1. * (ccpeak3.gamgam_pureggin + ccpeak3.gamgam_pureggout) / (cccont3.gamgam_pureggin + cccont3.gamgam_pureggout)).steps(linetype="longdashed"))
themc = (getmc(3, "chibkgnd").gamgam_e3GeVin + getmc(3, "chibkgnd").gamgam_e3GeVout)
themc *= (ccpeak2.gamgam_e3GeVin + ccpeak2.gamgam_e3GeVout).sum() / themc.sum() * 0.5
p[1,0].add(themc.steps(linetype="dotted"))
p[1,0].x1.label = r"Third-biggest shower (GeV) in $\Upsilon(3S)$ gamgam"

p.aspect_ratio = 1
p.show()
p.write_eps("plots/gamgam_chibkgnd.eps")

# normalized to have the same underflow bin
