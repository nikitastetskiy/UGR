# ejercicios/ordenamiento.py
import string
import random
from time import time

def ordenamientoBurbuja(unaLista):
        for numPasada in range(len(unaLista)-1,0,-1):
            for i in range(numPasada):
                if unaLista[i]>unaLista[i+1]:
                    temp = unaLista[i]
                    unaLista[i] = unaLista[i+1]
                    unaLista[i+1] = temp

def ord_seleccion(lista):
    n = len(lista)-1
    while n > 0:
        p = buscar_max(lista, 0, n)
        lista[p], lista[n] = lista[n], lista[p]
        n = n - 1

def buscar_max(lista, ini, fin):
    pos_max = ini
    for i in range(ini+1, fin+1):
        if lista[i] > lista[pos_max]:
            pos_max = i
    return pos_max

def ord_insercion(lista):
    for i in range(len(lista)-1):
        if lista[i+1]< lista[i]:
            reubicar(lista, i+1)

def reubicar(lista, p):
    v = lista[p]
    j = p
    while j > 0 and v < lista[j-1]:
        lista[j] = lista[j-1]
        j -= 1
    lista[j] = v

def ordenamientoPorMezcla(unaLista):
    print("Dividir ",unaLista)
    if len(unaLista)>1:
        mitad = len(unaLista)//2
        mitadIzquierda = unaLista[:mitad]
        mitadDerecha = unaLista[mitad:]

        ordenamientoPorMezcla(mitadIzquierda)
        ordenamientoPorMezcla(mitadDerecha)

        i=0
        j=0
        k=0
        while i < len(mitadIzquierda) and j < len(mitadDerecha):
            if mitadIzquierda[i] < mitadDerecha[j]:
                unaLista[k]=mitadIzquierda[i]
                i=i+1
            else:
                unaLista[k]=mitadDerecha[j]
                j=j+1
            k=k+1

        while i < len(mitadIzquierda):
            unaLista[k]=mitadIzquierda[i]
            i=i+1
            k=k+1

        while j < len(mitadDerecha):
            unaLista[k]=mitadDerecha[j]
            j=j+1
            k=k+1

def resultado(id):
    lista = []

    try:
        num = int(id)
    except ValueError:
        return "Lo has escrito mal"

    for i in range(int(id)):
        num = (random.randrange(100))
        lista.append(i)
        
    secuencia = ''
    start_time = time()
    ordenamientoBurbuja(lista)
    elapsed_time = time() - start_time

    start_time2 = time()
    ord_seleccion(lista)
    elapsed_time2 = time() - start_time

    start_time3 = time()
    ord_insercion(lista)
    elapsed_time3 = time() - start_time

    start_time4 = time()
    ord_insercion(lista)
    elapsed_time4 = time() - start_time

    secuencia += 'Ordenamiento burbuja: ' + str(elapsed_time) + '<br>'
    secuencia += 'Ordenamiento selección: ' + str(elapsed_time2) + '<br>'
    secuencia += 'Ordenamiento inserción: ' + str(elapsed_time3) + '<br>'
    secuencia += 'Ordenamiento mezcla: ' + str(elapsed_time4) + '<br>'
    return secuencia