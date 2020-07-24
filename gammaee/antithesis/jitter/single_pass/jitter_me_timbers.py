import biggles

jit = [0., 0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08]
area = [13.7041134854, \
        13.6962728075, \
        13.6968191682, \
        13.7011042101, \
        13.7058710013, \
        13.7035799692, \
        13.6434806522, \
        13.7554374656, \
        13.7095482018]
chi2 = [509.747164985, \
        513.55916247 , \
        515.711963245, \
        492.594786345, \
        538.8516039  , \
        502.544181088, \
        530.492721032, \
        537.961519449, \
        560.493530254]

p = biggles.FramedPlot()
p.add(biggles.Points(area, chi2, symboltype="filled circle", symbolsize=1))
for j, a, c in zip(jit, area, chi2):
  p.add(biggles.DataLabel(a, c, str(j), texthalign="left", textvalign="bottom"))
p.show()







jit = [0., 0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08]
area = [5.58588892168, \
        5.58754357581, \
        5.58737073678, \
        5.58538268329, \
        5.59492055608, \
        5.61570146438, \
        5.57188908818, \
        5.59586732048, \
        5.62158007523]
chi2 = [78.0905105133, \
        78.3938458983, \
        77.9247213509, \
        78.1658281021, \
        79.7748566443, \
        78.8762492829, \
        80.5179293378, \
        78.7436338248, \
        79.0933850524]
p = biggles.FramedPlot()
p.add(biggles.Points(area, chi2, symboltype="filled circle", symbolsize=1))
for j, a, c in zip(jit, area, chi2):
  p.add(biggles.DataLabel(a, c, str(j), texthalign="left", textvalign="bottom"))
p.show()




jit = [0., 0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08]
area = [3.58167681388, \
        3.58125358714, \
        3.57923692699, \
        3.5797754188 , \
        3.57806759672, \
        3.58728615967, \
        3.60020053845, \
        3.5875319112 , \
        3.61700292102]
chi2 = [412.014545775, \
        411.107162951, \
        412.811865371, \
        412.762219443, \
        418.81739125 , \
        413.301873491, \
        409.123392562, \
        419.900028968, \
        411.747967173]
p = biggles.FramedPlot()
p.add(biggles.Points(area, chi2, symboltype="filled circle", symbolsize=1))
for j, a, c in zip(jit, area, chi2):
  p.add(biggles.DataLabel(a, c, str(j), texthalign="left", textvalign="bottom"))
p.show()
