
import info

# create list ojbect
l = list(range(7))

# run C py function returning list len
print("CC len: {:d}".format( info.getFloatsByRef(l) ))

# run PYTHON built in function returning list len
print("PY len: {:d}".format( len(l) ))
