from bitstring import BitArray
#filename = input("Write file name: ")
filename = "font6x8"
size = 8
lines = []
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
        lines[i][j] = convert(lines[i][j])
i = 0
for line in lines:
    i+=1
    print(f'matrix {i}')
    for j in range(8):
        for k in range(6):
            print(line[k][j], end='')
        print()
    print()

with open ("output.txt",'w') as f:
    #i=0
    for line in lines:
        #i+=1
        #f.write(f'Str {i} \n')
        for sym in line:
            for item in sym:
                f.write(item)
                f.write(',')
            #f.write('\n')
        #f.write('\n')
for item in syms:
    print(f"'{item}',", end='')
