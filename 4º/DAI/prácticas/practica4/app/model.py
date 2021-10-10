from pickleshare import PickleShareDB
from flask import Flask, session
app = Flask(__name__)

def loginBD(username, password):
    db = PickleShareDB('miBD')

    if username in db.keys() and db[username] and password == db[username]['pass']:
        session['logged'] = True
        session['username'] = username
        return "Claves correctas"
    else:
        return "Claves incorrectas"

def registBD(username, password):
    db = PickleShareDB('miBD')
    if username in db.keys():
        return False
    else:
        session['logged'] = True
        session['username'] = username
        db[username] = {'pass': password}
        return True
        

def editBD(username, password):
    db = PickleShareDB('miBD')
    if username in db.keys():
        del db[username]
    registBD(username, password)

def getBD(username):
    db = PickleShareDB('miBD')
    return db[username]