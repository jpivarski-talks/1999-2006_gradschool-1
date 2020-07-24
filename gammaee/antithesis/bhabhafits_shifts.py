import biggles

names1 = ["jan16", "jan30", "feb06", "feb13", "feb20", "feb27", "mar06", "mar13", "apr03", "apr08", "apr09", "apr10"]
names2 = ["may29", "jun11", "jun12", "jul10", "jul24", "aug07"]
names3 = ["nov28", "dec05", "dec12", "dec19", "dec26", "jan02", "jan09"]

# U(1S) gg (MINOS)
#     area =  319.222190193        2.12
#     rmsbeam = 3.77898332112      0.0263
#     back =    9.35245823819      0.0218
#     jan16 =   0.240609780596     0.121
#     jan30 =   0.532886153782     0.097
#     feb06 =   0.233679169962     0.092
#     feb13 =   0.0549627226337    0.104
#     feb20 =   0.160661818497     0.099
#     feb27 =   0.112259329033     0.100
#     mar06 =   0.219895304517     0.120
#     mar13 =   0.568669674887     0.104
#     apr03 =   0.904486221013     0.145
#     apr08 =   0.786778708973     0.120
#     apr09 =   0.445348165738     0.128
#     apr10 =   0.747312963605     0.098

u1gg = [0.240609780596, 0.532886153782, 0.233679169962, 0.0549627226337, 0.160661818497, 0.112259329033, 0.219895304517, 0.568669674887, 0.904486221013, 0.786778708973, 0.445348165738, 0.747312963605]
u1gg_err = [0.121, 0.097, 0.092, 0.104, 0.099, 0.100, 0.120, 0.104, 0.145, 0.120, 0.128, 0.098 ]

# U(2s) gg (HESSE)
#     area =  133.211507233       1.55250764893  
#     rmsbeam = 4.16424969862     0.0478264571132
#     back =    9.33118325362     0.0156475876735
#     may29 =  -1.03832488008     0.201511538131 
#     jun11 =  -1.07988239788     0.154916429084 
#     jun12 =  -1.51427193529     0.161058064064 
#     jul10 =  -0.770597225561    0.127213599902 
#     jul24 =  -0.684404542801    0.220481064947 
#     aug07 =  -0.392068578403    0.210087124784 

u2gg = [-1.03832488008, -1.07988239788, -1.51427193529, -0.77059722556, -0.68440454280, -0.39206857840] 
u2gg_err = [0.201511538131, 0.154916429084, 0.161058064064, 0.127213599902, 0.220481064947, 0.210087124784] 

# U(3S) gg (MINOS)
#     area =   84.9230277774  1.87
#     rmsbeam = 4.50762704657 0.103
#     back =    9.31502157956 0.024
#     nov28 =  -2.29937800587 0.536
#     dec05 =  -4.06130713092 0.23974045011049999
#     dec12 =  -3.1797290744  0.31464513867999999
#     dec19 =  -2.09955840481 0.34893020820699999
#     dec26 =  -2.93022974685 0.21620136203199999
#     jan02 =  -2.69223785972 0.30939628792749996
#     jan09 =  -2.48164392013 0.400575831602

u3gg = [-2.2993780058, -4.0613071309, -3.1797290744, -2.0995584048, -2.9302297468, -2.6922378597, -2.4816439201] 
u3gg_err = [0.536, 0.239740450110, 0.314645138679, 0.348930208206, 0.216201362031, 0.309396287927, 0.400575831602] 

# U(1S) inee (MINOS)
#     area =  324.10          1.1647724265099999
#     rmsbeam = 3.78826720511 0.014130574200299999
#     back = 9.35975830341    0.0124726359698
#     jan16 = 0.43995128496   0.0692090486901
#     jan30 = 0.510453953796  0.049857913212249999
#     feb06 = 0.0393865886958 0.044073017997899998
#     feb13 = 0.121482561577  0.058843773784050001
#     feb20 = 0.0716885100899 0.053700689320200001
#     feb27 = 0.235279211218  0.053982727041649997
#     mar06 = 0.341791380564  0.07084608323274999
#     mar13 = 0.308639946732  0.053771874168299996
#     apr03 = 0.871866303365  0.071363937405499997
#     apr08 = 0.602604485207  0.059655161067349999
#     apr09 = 0.539936165122  0.065975243210049994
#     apr10 = 0.672894582578  0.0547719698804

u1inee = [0.43995128496, 0.510453953796, 0.039386588695, 0.121482561577, 0.071688510089, 0.235279211218, 0.341791380564, 0.308639946732, 0.871866303365, 0.602604485207, 0.539936165122, 0.672894582578] 
u1inee_err = [0.0692090486901, 0.0498579132122, 0.0440730179978, 0.0588437737840, 0.0537006893202, 0.0539827270416, 0.0708460832327, 0.0537718741682, 0.0713639374054, 0.0596551610673, 0.0659752432100, 0.0547719698804] 

# U(2S) inee (HESSE)
#     area =  134.243099282     0.749955332003   
#     rmsbeam = 4.17627005891   0.00533580359459 
#     back =    9.32659148004   0.00889687023621 
#     may29 =  -1.26365295117   0.0297105536805  
#     jun11 =  -1.14127837047   0.0849514567268  
#     jun12 =  -0.928183450655  0.101487930317   
#     jul10 =  -0.662023174224  0.0696226974485  
#     jul24 =  -0.755104492557  0.0552063402156  
#     aug07 =  -0.526232253623  0.114441251304   

u2inee = [-1.26365295117, -1.14127837047, -0.92818345065, -0.66202317422, -0.75510449255, -0.52623225362] 
u2inee_err = [0.029710553680, 0.084951456726, 0.101487930317, 0.069622697448, 0.055206340215, 0.114441251304] 

# U(3S) inee (MINOS)
#     area =   88.8178733524  1.0542664740450001
#     rmsbeam = 4.66319531916 0.0560393485579
#     back =    9.32390764057 0.01395383821885
#     nov28 =  -3.08670276898 0.18445716460099998
#     dec05 =  -3.79878701904 0.16648887750750002
#     dec12 =  -2.94503610632 0.1991394986635
#     dec19 =  -2.73838291066 0.2218775010505
#     dec26 =  -2.68377418599 0.13402338245450002
#     jan02 =  -2.69037693241 0.15056985467549999
#     jan09 =  -2.72244222944 0.18354775665600001

u3inee = [-3.08670276898, -3.79878701904, -2.94503610632, -2.73838291066, -2.68377418599, -2.69037693241, -2.72244222944] 
u3inee_err = [0.1844571646009, 0.1664888775075, 0.1991394986635, 0.2218775010505, 0.1340233824545, 0.1505698546754, 0.1835477566560] 

# U(1S) outee (MINOS)
#     area =  323.356            0.91994084237450002
#     rmsbeam = 3.81117299777    0.01130683294955
#     back =    9.3570928174     0.010277305498699998
#     jan16 =   0.410525992227   0.055817361070600001
#     jan30 =   0.590806616192   0.03845921617775
#     feb06 =   0.139542494039   0.035472876504300005
#     feb13 =   0.0269788616753  0.044485843442400003
#     feb20 =   0.0793834261764  0.042457799306549998
#     feb27 =   0.188389582564   0.044166534318749999
#     mar06 =   0.493238273524   0.0575730776704
#     mar13 =   0.380525500344   0.042049919371399999
#     apr03 =   0.82378364456    0.055955471669000001
#     apr08 =   0.600886301731   0.048345583477149998
#     apr09 =   0.646010701599   0.053284779549850003
#     apr10 =   0.704273160387   0.042609125244500001

u1outee = [0.41052599222, 0.59080661619, 0.13954249403, 0.02697886167, 0.07938342617, 0.18838958256, 0.49323827352, 0.38052550034, 0.82378364456, 0.60088630173, 0.64601070159, 0.70427316038] 
u1outee_err = [0.0558173610706, 0.0384592161777, 0.0354728765043, 0.0444858434424, 0.0424577993065, 0.0441665343187, 0.0575730776704, 0.0420499193713, 0.0559554716690, 0.0483455834771, 0.0532847795498, 0.0426091252445] 

# U(2S) outee (HESSE)
#     area =  133.987969754     1.31876078195    
#     rmsbeam = 4.16268441974   0.0616957048748  
#     back =    9.32466643979   0.00738732698613 
#     may29 =  -1.18409437209   0.0809302168538  
#     jun11 =  -1.07686130565   0.0697979226052  
#     jun12 =  -1.03888275814   0.10839926199    
#     jul10 =  -0.81180137209   0.053600373133   
#     jul24 =  -0.687066343026  0.0945415781548  
#     aug07 =  -0.678196380356  0.0912373278872  

u2outee = [-1.18409437209, -1.07686130565, -1.03888275814, -0.81180137209, -0.68706634302, -0.67819638035] 
u2outee_err = [0.08093021685, 0.06979792260, 0.10839926199, 0.05360037313, 0.09454157815, 0.09123732788] 

# U(3S) outee (MINOS)
#     area =   87.81          0.86041100377750002
#     rmsbeam = 4.61586857163 0.045886195914350003
#     back =    9.33450635422 0.01147334607095
#     nov28 =  -3.26950954112 0.154412757067
#     dec05 =  -3.81874447879 0.119568862537
#     dec12 =  -2.69523715354 0.1551377613935
#     dec19 =  -2.74889362332 0.160767851983
#     dec26 =  -2.66285796831 0.10492597384250001
#     jan02 =  -2.70059556893 0.130096282742
#     jan09 =  -2.90842427327 0.14542360482599997

u3outee = [-3.26950954112, -3.81874447879, -2.69523715354, -2.74889362332, -2.66285796831, -2.70059556893, -2.90842427327]
u3outee_err = [0.154412757067, 0.119568862537, 0.155137761393, 0.160767851983, 0.104925973842, 0.130096282742, 0.145423604825]

ggrange = Numeric.array(range(0, -len(names1), -1)) + 0.2
ineerange = Numeric.array(range(0, -len(names1), -1))
outeerange = Numeric.array(range(0, -len(names1), -1)) - 0.2
p = biggles.FramedPlot()
tmp1 = biggles.Points(u1gg, ggrange, size=1.5, type="filled circle")
p.add(tmp1)
p.add(biggles.SymmetricErrorBarsX(u1gg, ggrange, u1gg_err))
tmp2 = biggles.Points(u1inee, ineerange, size=2, type="triangle")
p.add(tmp2)
p.add(biggles.SymmetricErrorBarsX(u1inee, ineerange, u1inee_err))
tmp3 = biggles.Points(u1outee, outeerange, size=2, type="filled inverted triangle")
p.add(tmp3)
p.add(biggles.SymmetricErrorBarsX(u1outee, outeerange, u1outee_err))
tmp1.label = r"$\gamma\gamma$ luminosity"
tmp2.label = r"inner $e^+e^-$"
tmp3.label = r"outer $e^+e^-$"
p.add(biggles.PlotKey(0.6, 0.7, [tmp1, tmp2, tmp3]))
p.yrange = -len(names1), 1
p.y.ticks = ineerange
p.y.ticklabels = names1
p.y1.draw_subticks = 0
p.y.draw_ticks = 0
p.y2.draw_ticklabels = 0
p.xrange = -0.2, 1.2
p.x1.label = r"$M_{PDG} - M_{measured}$ for $\Upsilon(1S)$"
p.aspect_ratio = 11./8.5
p.show()
p.write_eps("/home/mccann/antithesis/plots/bhabhafits_shifts1.eps")

ggrange = Numeric.array(range(0, -len(names2), -1)) + 0.2
ineerange = Numeric.array(range(0, -len(names2), -1))
outeerange = Numeric.array(range(0, -len(names2), -1)) - 0.2
p = biggles.FramedPlot()
tmp1 = biggles.Points(u2gg, ggrange, size=1.5, type="filled circle")
p.add(tmp1)
p.add(biggles.SymmetricErrorBarsX(u2gg, ggrange, u2gg_err))
tmp2 = biggles.Points(u2inee, ineerange, size=2, type="triangle")
p.add(tmp2)
p.add(biggles.SymmetricErrorBarsX(u2inee, ineerange, u2inee_err))
tmp3 = biggles.Points(u2outee, outeerange, size=2, type="filled inverted triangle")
p.add(tmp3)
p.add(biggles.SymmetricErrorBarsX(u2outee, outeerange, u2outee_err))
tmp1.label = r"$\gamma\gamma$ luminosity"
tmp2.label = r"inner $e^+e^-$"
tmp3.label = r"outer $e^+e^-$"
p.add(biggles.PlotKey(0.15, 0.25, [tmp1, tmp2, tmp3]))
p.yrange = -len(names2), 1
p.y.ticks = ineerange
p.y.ticklabels = names2
p.y1.draw_subticks = 0
p.y.draw_ticks = 0
p.y2.draw_ticklabels = 0
p.xrange = -2, 0
p.x1.label = r"$M_{PDG} - M_{measured}$ for $\Upsilon(2S)$"
p.aspect_ratio = 11./8.5
p.show()
p.write_eps("/home/mccann/antithesis/plots/bhabhafits_shifts2.eps")

ggrange = Numeric.array(range(0, -len(names3), -1)) + 0.2
ineerange = Numeric.array(range(0, -len(names3), -1))
outeerange = Numeric.array(range(0, -len(names3), -1)) - 0.2
p = biggles.FramedPlot()
tmp1 = biggles.Points(u3gg, ggrange, size=1.5, type="filled circle")
p.add(tmp1)
p.add(biggles.SymmetricErrorBarsX(u3gg, ggrange, u3gg_err))
tmp2 = biggles.Points(u3inee, ineerange, size=2, type="triangle")
p.add(tmp2)
p.add(biggles.SymmetricErrorBarsX(u3inee, ineerange, u3inee_err))
tmp3 = biggles.Points(u3outee, outeerange, size=2, type="filled inverted triangle")
p.add(tmp3)
p.add(biggles.SymmetricErrorBarsX(u3outee, outeerange, u3outee_err))
tmp1.label = r"$\gamma\gamma$ luminosity"
tmp2.label = r"inner $e^+e^-$"
tmp3.label = r"outer $e^+e^-$"
p.add(biggles.PlotKey(0.1, 0.25, [tmp1, tmp2, tmp3]))
p.yrange = -len(names3), 1
p.y.ticks = ineerange
p.y.ticklabels = names3
p.y1.draw_subticks = 0
p.y.draw_ticks = 0
p.y2.draw_ticklabels = 0
p.xrange = -5, -1
p.x1.label = r"$M_{PDG} - M_{measured}$ for $\Upsilon(3S)$"
p.aspect_ratio = 11./8.5
p.show()
p.write_eps("/home/mccann/antithesis/plots/bhabhafits_shifts3.eps")

