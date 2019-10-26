
import info

# create list ojbect
l = [float(0.01* i) for i in range(10)]

l[-2] = int(99)

# run C py function returning list len
print("CC status: {:d}".format( info.getFloatsByRef(l) ))
print(l)

# run PYTHON built in function returning list len
print("PY len: {:d}".format( len(l) ))
