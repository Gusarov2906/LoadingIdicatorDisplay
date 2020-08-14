filename = "output.txt"
filename1 = "output1.txt"
res= []

with open (filename) as f:
    i = 0
    a = 0
    for line in f:
        if line.startswith("Str",0,len(line)) or line.startswith("\n",0,len(line)):
            i+=1
            continue

        if a == 8 :
            break
        a+=1
        res.append(line)
res1 = []
print(res)
for i in range(len(res)):
    res1.append(bytearray(res[i].encode('utf-8')))
    res1[i]=res1[i][:-1]
with open (filename1,'wb') as f:
    for item in res1:
        f.write(item)
