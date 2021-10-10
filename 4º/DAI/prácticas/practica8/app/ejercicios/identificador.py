# ejercicios/identificador.py
import string
import re

def get_Letras(secuencia):
    return bool(re.match(r"[\w\s]+[A-Z]", secuencia))

def get_Correo(secuencia):
    return bool(re.match(r"^[_a-z0-9-]+(.[_a-z0-9-]+)@[a-z0-9-]+(.[a-z0-9-]+)(.[a-z]{2,3})$", secuencia))

def get_Digito(secuencia):
    return bool(re.match(r"^\d{4}([\ -]?)\d{4}\1\d{4}\1\d{4}$", secuencia))

def resultado(secuencia): 
    if get_Letras(secuencia) == True:
        return("1 ) es lo de la palabara")
    elif get_Correo(secuencia) == True:
        return("2 ) es lo del correo")
    elif get_Digito(secuencia) == True:
        return("3 ) es lo del digito")
    else:
        return("Lo has escrito mal")