# ejercicios/numeros.py
import random

num = (random.randrange(100))

numin = -1

while numin != num:
    numin = input()
    numin = int(numin)
    if numin <= num:
        print("Tu estimación es muy baja")
    else:
        print("Tu estimación es muy alta")

print("olee era: ")

print(num)