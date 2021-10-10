# ejercicios/criba.py
criba=[]

num = input()
num = int(num)

for i in range(num):
    booleano = True
    for x in range(i):
        if x != 0 and x != 1 and x!=i and (i % x) == 0:
            booleano = False
    
    if booleano:
        criba.append(i)
for i in criba:
    print (i)
