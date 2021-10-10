#./app/app.py
import os, model
from flask import Flask, render_template, request, session, redirect, url_for
from ejercicios import identificador, corchete, criba, fibonacci, ordenamiento
from subirnota import figura

app = Flask(__name__)
app.secret_key = b'_5#y2L"F4Q8z\n\xec]/'

# Historial de las páginas
def setAndClean():
    session["url1"] = ''
    session["url2"] = ''
    session["url3"] = ''
    session["name1"] = ''
    session["name2"] = ''
    session["name3"] = ''

def setVisitPages(url, name):
    try:
        if(session["name1"] == name):
            session["url1"] = session["url2"]
            session["name1"] = session["name2"]
            session["url2"] = session["url3"]
            session["name2"] = session["name3"]
            session["url3"] = url
            session["name3"] = name
        elif(session["name2"] == name):
            session["url2"] = session["url3"]
            session["name2"] = session["name3"]
            session["url3"] = url
            session["name3"] = name
        elif(session["name3"] != name):
            session["url1"] = session["url2"]
            session["name1"] = session["name2"]
            session["url2"] = session["url3"]
            session["name2"] = session["name3"]
            session["url3"] = url
            session["name3"] = name
    except:
        setAndClean()

@app.route('/')
def index():
    if 'logged' in session.keys():
        setVisitPages("/", "Pagina Principal")
    return render_template("index.html")

@app.route('/login', methods=['GET', 'POST'])
def login():
    resultado = ''
    if 'logged' in session.keys():
        setVisitPages("/login", "Pagina Login")
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        resultado = model.loginBD(username, password)

    if resultado == "Claves correctas":
        return redirect(url_for("index"))
    return render_template('login.html', mensaje=resultado)

@app.route("/logout", methods=['GET', 'POST'])
def logout():
    session.clear()
    setAndClean()
    return redirect(url_for("index"))

# Registro
@app.route('/register', methods=['GET', 'POST'])
def register():
    resultado = ''
    if 'logged' in session.keys():
        setVisitPages("/register", "Pagina Registro")
    if request.method == 'POST':
        if request.form['password1'] != request.form['password2']:
            resultado = 'Las contraseñas no coinciden'
            return render_template('register.html', mensaje=resultado)
        else:
            username = request.form['username']
            password = request.form['password1']
        if model.registBD(username, password) == True:
            resultado = 'Correcto'
            return render_template('register.html', mensaje=resultado)
        else:
            resultado = "El usuario ya existe"
            return render_template('register.html', mensaje=resultado)
    return render_template('register.html', mensaje=resultado)

@app.route('/perfil', methods=['GET', 'POST'])
def perfil():
    if 'logged' in session.keys():
        setVisitPages("/perfil", "Pagina Perfil")
    return render_template('perfil.html')

@app.route('/ajustes', methods=['GET', 'POST'])
def editUser():
    mensaje = ''
    if 'logged' in session.keys():
        setVisitPages("/ajustes", "Pagina Ajustes")

    if request.method == 'POST':
        if request.form['password1'] != request.form['password2']:
            mensaje = 'Las contraseñas no coinciden.'
        else:
            username = request.form['username']
            password = request.form['password1']
            model.editBD(username, password)
            mensaje = 'La contraseña ha sido cambiada.'
        return render_template('ajustes.html', mensaje=mensaje)
    return render_template('ajustes.html', mensaje=mensaje)

#ejercicio de email, tarjeta de credito o nombre
#{{url_for('static', filename='identificador.py')}}
@app.route('/identificador', methods=['GET', 'POST'])
def ejercicio_uno():
    resultado = ''
    if 'logged' in session.keys():
        setVisitPages("/identificador", "Ejercicio Identificador")
    if request.method == 'POST':
        num = request.form['num']
        resultado = identificador.resultado(num)
    return render_template('ejercicios/identificador.html', res=resultado)

#ejercicio de los corchetes []]][]
@app.route('/corchete', methods=['GET', 'POST'])
def ejercicio_dos():
    resultado = ''
    solucion = ''
    if 'logged' in session.keys():
        setVisitPages("/corchete", "Ejercicio Corchete")
    if request.method == 'POST':
        num = request.form['num']
        resultado = corchete.resultado(num)
        if("Si" in resultado):
            solucion = True
        else:
            solucion = False
    return render_template('ejercicios/corchete.html', res=resultado, sol=solucion)

#ejercicio de los nº primos (criba)
@app.route('/criba', methods=['GET', 'POST'])
def ejercicio_tres():
    resultado = ''
    if 'logged' in session.keys():
        setVisitPages("/criba", "Ejercicio Criba")
    if request.method == 'POST':
        num = request.form['num']
        resultado = criba.resultado(num)
    return render_template('ejercicios/criba.html', res=resultado)

#ejercicio del fibonacci
@app.route('/fibonacci', methods=['GET', 'POST'])
def ejercicio_cuatro():
    secuencia = ''
    if 'logged' in session.keys():
        setVisitPages("/fibonacci", "Ejercicio Fibonacci")
    if request.method == 'POST':
        num = request.form['num']
        if os.path.exists("ejercicios/fibo.txt"):
            os.remove("ejercicios/fibo.txt")
        with open("ejercicios/fibo.txt", "w") as fo:
            fo.write(num)
        fibonacci.resultado()
        with open("ejercicios/fiboResul.txt", "r") as file:
            for line in file.readlines():
                secuencia += (line.rstrip()) + '\n'
    return render_template('ejercicios/fibonacci.html', res=secuencia)

#ejercicio del ordenamiento
@app.route('/ordenamiento', methods=['GET', 'POST'])
def ejercicio_cinco():
    resultado = ''
    if 'logged' in session.keys():
        setVisitPages("/ordenamiento", "Ejercicio Ordenamiento")
    if request.method == 'POST':
        num = request.form['num']
        resultado = ordenamiento.resultado(num)
    return render_template('ejercicios/ordenamiento.html', res=resultado)

#ejercicio de nota
@app.route('/subirnota')
def ejercicio_subirnota():
    resultado = ''
    if 'logged' in session.keys():
        setVisitPages("/subirnota", "Ejercicio Subir Nota")
    if request.method == 'GET':
        resultado = figura.write()
    return render_template('ejercicios/subirnota.html', res=resultado)

@app.errorhandler(404)
def page_not_found(e):
    # note that we set the 404 status explicitly
    return 'Error 404'
