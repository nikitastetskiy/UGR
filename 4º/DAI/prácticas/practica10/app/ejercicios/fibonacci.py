# ejercicios/fibonacci.py
import os

def resultado():
    fibo=[]

    f = open("ejercicios/fibo.txt", "r")

    suma = 0
    num = f.read()

    try:
        num = int(num)
    except ValueError:
        if os.path.exists("ejercicios/fiboResul.txt"):
            os.remove("ejercicios/fiboResul.txt")
        f = open("ejercicios/fiboResul.txt", "w")
        f.write("Lo has escrito mal")
        f.close()
        return 0

    num = int(num)
    fibo.append(suma)
    suma = 1

    for i in range(1, num):
        fibo.append(suma)
        suma = fibo[i-1]+fibo[i]

    if os.path.exists("ejercicios/fiboResul.txt"):
        os.remove("ejercicios/fiboResul.txt")
    f = open("ejercicios/fiboResul.txt", "w")

    for i in fibo:
        i = str(i)
        f.write(i+'<br>')
    f.close()