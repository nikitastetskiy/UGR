# ejercicios/fibonacci.py
import os
fibo=[]

f = open("fibo.txt", "r")

suma = 0
num = f.read()
num = int(num)
fibo.append(suma)
suma = 1

for i in range(1, num):
    fibo.append(suma)
    suma = fibo[i-1]+fibo[i]

if os.path.exists("fiboResul.txt"):
    os.remove("fiboResul.txt")
f = open("fiboResul.txt", "w")

for i in fibo:
    i = str(i)
    f.write(i+'\n')
f.close()