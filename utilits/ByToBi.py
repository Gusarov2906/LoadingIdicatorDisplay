from bitstring import BitArray
import numpy as np

#filename = input("Write file name: ")
filename = "font6x8"
size = 8
lines = []
arrays = []
def convert(a):
    res = BitArray(hex=a)
    res = res.bin
    return res
syms  = []
with open (filename) as f:
    for line in f:
        lines.append(line.split(" //")[0])
        if (line.split(" //")[1]):
            syms.append((line.split(" //")[1]).split()[0])
for i in range(len(lines)):
    lines[i] = lines[i].split(",")
for i in range(len(lines)):
    for j in range(len(lines[i])):
        lines[i][j] = list(convert(lines[i][j]))

i = 0
for sym in lines:
        arrays.append(np.rot90(np.array([sym[0],
        sym[1],
        sym[2],
        sym[3],
        sym[4],
        sym[5]]), k = 1, axes = (0, 1)))

print(arrays)


#with open ("output.txt",'w') as f:
    #i=0
#    for line in lines:
        #i+=1
        #f.write(f'Str {i} \n')
#        for sym in line:
    #        for item in sym:
    #            f.write(item)
    #            f.write(',')
            #f.write('\n')
        #f.write('\n')
#for item in syms:
#    print(f"'{item}',", end='')
with open ("output.txt",'w') as f:
    for sym in arrays:
        for line in sym:
            for byte in line:
                f.write(byte)
                f.write(',')
    f.write('\n')
