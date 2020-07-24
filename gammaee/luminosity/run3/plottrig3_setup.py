import cPickle
class RunRecord: pass
run = {}
execfile("daf9/relatives.py")
cPickle.dump(run, open("daf9/relatives.p", "w"))
