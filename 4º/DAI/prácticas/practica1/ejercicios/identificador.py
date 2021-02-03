# ejercicios/identificador.py
import string

def get_Letras(secuencia):
    if len(secuencia) > 2 and secuencia[len(secuencia)-1] in string.ascii_uppercase and secuencia[len(secuencia)-2] == ' ':
        return True
    else:
        return False

def get_Correo(secuencia):
    x = secuencia.find("@")
    y = secuencia.find(".com")
    if y == -1:
        y = secuencia.find(".es")
    if x != -1 and y != -1 and y > x+1:
        return True
    else:
        return False

def get_Digito(secuencia):
    i = 0
    x = True
    cont = 4
    espacioguion = [" ", "-"]
    numeros = [4, 9, 14]
    while i < len(secuencia) and x:
        if i not in numeros and secuencia[i] not in string.digits:
            x = False
            print(secuencia[i], i)
        elif i in numeros and secuencia[i] not in espacioguion:
            print(secuencia[i])
            x = False
        i +=1
    return x

secuencia = input()

if get_Letras(secuencia) == True:
    print("1 ) es lo de la palabara")
elif get_Correo(secuencia) == True:
    print("2 ) es lo del correo")
elif get_Digito(secuencia) == True:
    print("3 ) es lo del digito")