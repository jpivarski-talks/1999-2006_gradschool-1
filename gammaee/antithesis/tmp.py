
u1runs = {}
u2runs = {}
u3runs = {}
u1data = {}
u2data = {}
u3data = {}

u1runs["cont"] = []
u2runs["cont"] = []
u3runs["cont"] = []
u1runs["high"] = []
u2runs["high"] = []
u3runs["high"] = []

u1runs["jan16"] = setup_runs(1, 123164, 123178)
u1runs["jan30"] = setup_runs(1, 123596, 123718)
u1runs["feb06"] = setup_runs(1, 123781, 123893)
u1runs["feb13"] = setup_runs(1, 124080, 124092)
u1runs["feb20"] = setup_runs(1, 124102, 124214)
u1runs["feb27"] = setup_runs(1, 124279, 124394)
u1runs["mar06"] = setup_runs(1, 124436, 124519)
u1runs["mar13"] = setup_runs(1, 124625, 124736)
u1runs["apr08"] = setup_runs(1, 125254, 125262)
u1runs["apr09"] = setup_runs(1, 125285, 125295)
u1runs["apr10"] = setup_runs(1, 125303, 125416)

u2runs["may29"] = setup_runs(2, 126449, 126568)
u2runs["jun11"] = setup_runs(2, 126776, 126783)
u2runs["jun12"] = setup_runs(2, 126814, 126915)
u2runs["jul10"] = setup_runs(2, 127588, 127615)
u2runs["jul24"] = setup_runs(2, 127924, 127933)
u2runs["aug07"] = setup_runs(2, 128303, 128316)

u3runs["nov28"] = setup_runs(3, 121884, 122007)
u3runs["dec05"] = setup_runs(3, 122069, 122178)
u3runs["dec12"] = setup_runs(3, 122245, 122326)
u3runs["dec19"] = setup_runs(3, 122409, 122527)
u3runs["dec26"] = setup_runs(3, 122535, 122757)
u3runs["jan02"] = setup_runs(3, 122766, 122881)
u3runs["jan09"] = setup_runs(3, 122993, 123101)

for r in initialrunlist:
  if r not in mybadruns:
    if runsummary[r].res == 1 and runsummary[r].kind == 'c':
      u1runs["cont"].append(r)
    if runsummary[r].res == 2 and runsummary[r].kind == 'c':
      u2runs["cont"].append(r)
    if runsummary[r].res == 3 and runsummary[r].kind == 'c':
      u3runs["cont"].append(r)

for r in initialrunlist:
  if r not in mybadruns:
    if runsummary[r].res == 1 and runsummary[r].kind == 'h':
      u1runs["high"].append(r)
    if runsummary[r].res == 2 and runsummary[r].kind == 'h':
      u2runs["high"].append(r)
    if runsummary[r].res == 3 and runsummary[r].kind == 'h':
      u3runs["high"].append(r)

u1data["cont"] = [get_runs(u1runs["cont"], lumisource=lumisource)]
u2data["cont"] = [get_runs(u2runs["cont"], lumisource=lumisource)]
u3data["cont"] = [get_runs(u3runs["cont"], lumisource=lumisource)]

u1data["high"] = [get_runs(u1runs["high"], lumisource=lumisource)]
u2data["high"] = [get_runs(u2runs["high"], lumisource=lumisource)]
u3data["high"] = [get_runs(u3runs["high"], lumisource=lumisource)]

u1data["jan16"] = setup_data(u1runs["jan16"], lumisource=lumisource)
u1data["jan30"] = setup_data(u1runs["jan30"], lumisource=lumisource)
u1data["feb06"] = setup_data(u1runs["feb06"], lumisource=lumisource)
u1data["feb13"] = setup_data(u1runs["feb13"], lumisource=lumisource)
u1data["feb20"] = setup_data(u1runs["feb20"], lumisource=lumisource)
u1data["feb27"] = setup_data(u1runs["feb27"], lumisource=lumisource)
u1data["mar06"] = setup_data(u1runs["mar06"], lumisource=lumisource)
u1data["mar13"] = setup_data(u1runs["mar13"], lumisource=lumisource)
u1data["apr08"] = setup_data(u1runs["apr08"], lumisource=lumisource)
u1data["apr09"] = setup_data(u1runs["apr09"], lumisource=lumisource)
u1data["apr10"] = setup_data(u1runs["apr10"], lumisource=lumisource)

u2data["may29"] = setup_data(u2runs["may29"], lumisource=lumisource)
u2data["jun11"] = setup_data(u2runs["jun11"], lumisource=lumisource)
u2data["jun12"] = setup_data(u2runs["jun12"], lumisource=lumisource)
u2data["jul10"] = setup_data(u2runs["jul10"], lumisource=lumisource)
u2data["jul24"] = setup_data(u2runs["jul24"], lumisource=lumisource)
u2data["aug07"] = setup_data(u2runs["aug07"], lumisource=lumisource)

u3data["nov28"] = setup_data(u3runs["nov28"], lumisource=lumisource)
u3data["dec05"] = setup_data(u3runs["dec05"], lumisource=lumisource)
u3data["dec12"] = setup_data(u3runs["dec12"], lumisource=lumisource)
u3data["dec19"] = setup_data(u3runs["dec19"], lumisource=lumisource)
u3data["dec26"] = setup_data(u3runs["dec26"], lumisource=lumisource)
u3data["jan02"] = setup_data(u3runs["jan02"], lumisource=lumisource)
u3data["jan09"] = setup_data(u3runs["jan09"], lumisource=lumisource)
