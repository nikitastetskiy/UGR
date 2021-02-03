# ejercicios/criba.py

def resultado(id):
    criba=[]

    num = id
    secuencia = ''

    try:
        num = int(id)
    except ValueError:
        return "Lo has escrito mal"

    num = int(num)

    for i in range(num):
        booleano = True
        for x in range(i):
            if x != 0 and x != 1 and x!=i and (i % x) == 0:
                booleano = False
        
        if booleano:
            criba.append(i)
    for i in criba:
        secuencia += str(i) + '<br>'
    return secuencia
