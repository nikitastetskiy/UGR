# ejercicios/corchete.py
import random
import string

def get_random_secuencia_string(length):
    corchete = '[]'
    secuencia = ''.join(random.choice(corchete) for i in range(length))
    return secuencia

def resultado(id):
    n = id
    n = int(n)
    secuencia = get_random_secuencia_string(n)
    cont = 0

    for i in secuencia:
        if i == '[':
            cont+=1
        if i == ']':
            cont-=1
        if cont == -1:
            break

    if cont == 0:
        return(secuencia + " -> Si están balanceados")
    else:
        return(secuencia + " -> No están balanceados")