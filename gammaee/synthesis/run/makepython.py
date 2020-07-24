import cPickle, sys, Numeric, hist

class RunRecord: pass
execfile(sys.argv[1])

# This will fail if the .py is empty and rec doesn't exist: no .p file
# will be made.
cPickle.dump(rec, open(sys.argv[2], 'w'), -1)

