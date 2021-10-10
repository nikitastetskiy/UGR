#./app/app.py
import os, model
from flask import Flask, render_template, request, session, redirect, url_for, jsonify
from ejercicios import identificador, corchete, criba, fibonacci, ordenamiento
from subirnota import figura
from pymongo import MongoClient
from flask_restful import (Resource, Api, reqparse)
from bson import ObjectId
from random_object_id import generate

client = MongoClient("mongo", 27017)
db = client.SampleCollections

app = Flask(__name__)
app.secret_key = b'_5#y2L"F4Q8z\n\xec]/'
api = Api(app)

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

## Práctica 4

client = MongoClient("mongo", 27017) # Conectar al servicio (docker) "mongo" en su puerto estandar
dbmongo = client.SampleCollections      # Elegimos la base de datos de ejemplo

@app.route('/searchbd', methods = ['GET', 'POST'])
def busqueda():
    if 'logged' in session.keys():
            setVisitPages("/searchbd", "MongoDB Búsqueda")
    if request.method == 'POST':
        busqueda = request.form['busqueda']
        if busqueda == '':
            return redireccion('vacio', None)
        array_poke = dbmongo.samples_pokemon.find({"name" : {"$regex" : busqueda}})
        return render_template('mongodb.html', pokemons = array_poke)
    else:
        return redireccion()

@app.route('/addbd', methods = ['GET', 'POST'])
def anadir():
    if 'logged' in session.keys():
            setVisitPages("/mongobd", "MongoDB Nuevo Pokémon")
    if request.method == 'POST':
        newPokemon = request.form['newPokemon']
        if newPokemon == '':
            return redireccion('vacio', None)
        if not len(list(dbmongo.samples_pokemon.find({"name" : newPokemon}))) > 0:
            dbmongo.samples_pokemon.insert_one({ "name": newPokemon })
            return redireccion('exitoAnadido', newPokemon)
        else:
            return redireccion('errorDuplicado', newPokemon)
    else:
        return redireccion()

@app.route('/modifybd', methods = ['GET', 'POST'])
def modificarAtributos():
    if request.method == 'POST':
        nombre = request.form['nombre']
        altura = request.form['altura']
        peso = request.form['peso']
        param_aux = 'Se han cambiado los atributos de '
        pok_aux = { "name": nombre }
        nuevos_valores = { "$set": { "height": altura } }
        if altura == '' or peso == '':
           return redireccion('vacio', None)
        dbmongo.samples_pokemon.update_one(pok_aux, nuevos_valores)
        param_aux += str(nombre)+': '+ str(altura) + ' y '
        nuevos_valores = { "$set": { "weight": peso } }
        dbmongo.samples_pokemon.update_one(pok_aux, nuevos_valores)
        param_aux += str(peso)
        datos_pokemon = dbmongo.samples_pokemon.find({"name" : nombre})
        if 'logged' in session.keys():
            setVisitPages("/modifybd?name="+str(nombre), "MongoDB Editar Pokémon: "+str(nombre))
        #return redireccion(datos_pokemon[0], None) Para ver todos los parametros
        return redireccion(param_aux, None)
    else:
        pokemon = request.args.get('name')
        if 'logged' in session.keys():
            setVisitPages("/modifybd?name="+str(pokemon), "MongoDB Editar Pokémon: "+str(pokemon))
        datos_pokemon = dbmongo.samples_pokemon.find({"name" : pokemon})

    return render_template('mongodb.html', datos = datos_pokemon[0])


@app.route('/deletebd', methods = ['GET', 'POST'])
def delete():
    if 'logged' in session.keys():
            setVisitPages("/mongobd", "MongoDB Borrar Pokémon")
    if request.method == 'POST':
        delPokemon = request.form['delPokemon']
        if delPokemon == '':
            return redireccion('vacio', None)
        if len(list(dbmongo.samples_pokemon.find({"name" : delPokemon}))) > 0:
            dbmongo.samples_pokemon.delete_one({ "name": delPokemon })
            return redireccion('exitoBorrado', delPokemon)
        else:
            return redireccion('errorBorrado', delPokemon)
    else:
        pokemon = request.args.get('name')
        if len(list(dbmongo.samples_pokemon.find({"name" : pokemon}))) > 0:
            dbmongo.samples_pokemon.delete_one({ "name": pokemon })
            return redireccion('exitoBorrado', pokemon)
        else:
            return redireccion('errorBorrado', pokemon)

@app.route('/mongobd')
def mongo():
    if 'logged' in session.keys():
            setVisitPages("/mongobd", "MongoDB Página Pokémon")
    return redireccion()

def redireccion(parametro=None, poke_aux=None):
    array_poke = dbmongo.samples_pokemon.find()
    if parametro is not None:
        return render_template('mongodb.html',pokemons = array_poke, param_aux = parametro, poke_aux = poke_aux)
    else:
        return render_template('mongodb.html',pokemons = array_poke)

# Práctica 5

@app.route('/api/pokemon', methods=['GET', 'POST'])
def api_1():
    if request.method == 'GET':
        lista = []
        array_pokemon = db.samples_pokemon.find().sort('id')
        for pokemon in array_pokemon:
            lista.append({
                '_id':            str(pokemon.get('_id')), # pasa a string el ObjectId
                'id':             pokemon.get('id'),
                'name':           pokemon.get('name'),
                'img':            pokemon.get('img'),
                'type':           pokemon.get('type'),
                'height':         pokemon.get('height'),
                'weight':         pokemon.get('weight'),
                'candy':          pokemon.get('candy'),
                'candy_count':    pokemon.get('candy_count'),
                'egg':            pokemon.get('egg'),
                'spawn_chance':   pokemon.get('spawn_chance'),
                'avg_spawns':     pokemon.get('avg_spawns'),
                'spawn_time':     pokemon.get('spawn_time'),
                'multipliers':    pokemon.get('multipliers'),
                'weaknesses':     pokemon.get('weaknesses'),
                'next_evolution': pokemon.get('next_evolution'),
            })
        return jsonify(lista)
    elif request.method == 'POST':
        
        _id = generate()
        id = ""
        name = ""
        img = ""
        # _type = ""
        height = ""
        weight = ""
        # candy = ""
        # candy_count = ""
        # egg = ""
        # spawn_chance = ""
        # avg_spawns = ""
        # spawn_time = ""
        # multipliers = ""
        # weaknesses = ""
        # next_evolution = ""

        if(request.get_json() is not None):
            if 'id' in request.get_json():
                id = request.get_json()['id']
            if 'name' in request.get_json():
                name = request.get_json()['name']
            if 'height' in request.get_json():
                height = request.get_json()['height']
            if 'weight' in request.get_json():
                weight = request.get_json()['weight']

        pokemon = { "_id": ObjectId(_id), "id":id, "name":name, "height":height, "weight":weight }
        db.samples_pokemon.insert_one(pokemon)
        pokemonjson = { "_id": (_id), "id":id, "name":name, "height":height, "weight":weight }
        return jsonify(pokemonjson)

@app.route('/api/pokemon/<idaux>', methods=['GET', 'PUT', 'DELETE'])
def api_2(idaux):
    if request.method == 'GET':
        try:
            pokemon = db.samples_pokemon.find_one({'_id':ObjectId(idaux)})
            return jsonify({
                '_id':            idaux,
                'id':             pokemon.get('id'),
                'name':           pokemon.get('name'),
                'img':            pokemon.get('img'),
                'type':           pokemon.get('type'),
                'height':         pokemon.get('height'),
                'weight':         pokemon.get('weight'),
                'candy':          pokemon.get('candy'),
                'candy_count':    pokemon.get('candy_count'),
                'egg':            pokemon.get('egg'),
                'spawn_chance':   pokemon.get('spawn_chance'),
                'avg_spawns':     pokemon.get('avg_spawns'),
                'spawn_time':     pokemon.get('spawn_time'),
                'multipliers':    pokemon.get('multipliers'),
                'weaknesses':     pokemon.get('weaknesses'),
                'next_evolution': pokemon.get('next_evolution'),
            })
        except:
          return jsonify({'error':'ERROR_NOT_FOUND'}), 400
    elif request.method == 'PUT':
        try:
            pokemon = db.samples_pokemon.find_one({'_id':ObjectId(idaux)})

            id = pokemon.get('id')
            name = pokemon.get('name')
            height = pokemon.get('height')
            weight = pokemon.get('weight')

            if(request.get_json() is not None):
                if 'id' in request.get_json():
                    id = request.get_json()['id']
                if 'name' in request.get_json():
                    name = request.get_json()['name']
                if 'height' in request.get_json():
                    height = request.get_json()['height']
                if 'weight' in request.get_json():
                    weight = request.get_json()['weight']

            id_new = { "$set": { 'id' : id , 'name' : name, 'height' : height, 'weight' : weight } }
            id_old = { '_id' : ObjectId(idaux) }
            db.samples_pokemon.update_one(id_old, id_new)

            pokemon = db.samples_pokemon.find_one({'_id':ObjectId(idaux)})
            return jsonify({
                'id':       pokemon.get('id'),
                'name':     pokemon.get('name'),
                'height':   pokemon.get('height'),
                'weight':   pokemon.get('weight')
            })
        except:
            return jsonify({'error':'ERROR_NOT_FOUND'}), 400
    elif request.method == 'DELETE':
        try:
            pokemon = db.samples_pokemon.find_one({'_id':ObjectId(idaux)})
            db.samples_pokemon.delete_one({ '_id' : pokemon.get('_id') })
            return jsonify({ '_id' : idaux, 'status' : 'borrado' })
        except:
            return jsonify({'error':'ERROR_NOT_FOUND'}), 400

# Para subir Nota

class apirestful_1(Resource):
    def get(self):
        lista = []
        array_pokemon = db.samples_pokemon.find().sort('id')
        for pokemon in array_pokemon:
            lista.append({
                '_id':            str(pokemon.get('_id')), # pasa a string el ObjectId
                'id':             pokemon.get('id'),
                'name':           pokemon.get('name'),
                'img':            pokemon.get('img'),
                'type':           pokemon.get('type'),
                'height':         pokemon.get('height'),
                'weight':         pokemon.get('weight'),
                'candy':          pokemon.get('candy'),
                'candy_count':    pokemon.get('candy_count'),
                'egg':            pokemon.get('egg'),
                'spawn_chance':   pokemon.get('spawn_chance'),
                'avg_spawns':     pokemon.get('avg_spawns'),
                'spawn_time':     pokemon.get('spawn_time'),
                'multipliers':    pokemon.get('multipliers'),
                'weaknesses':     pokemon.get('weaknesses'),
                'next_evolution': pokemon.get('next_evolution'),
            })
        return jsonify(lista)
    def post(self):
        _id = generate()
        id = ""
        name = ""
        img = ""
        # _type = ""
        height = ""
        weight = ""
        # candy = ""
        # candy_count = ""
        # egg = ""
        # spawn_chance = ""
        # avg_spawns = ""
        # spawn_time = ""
        # multipliers = ""
        # weaknesses = ""
        # next_evolution = ""

        if(request.get_json() is not None):
            if 'id' in request.get_json():
                id = request.get_json()['id']
            if 'name' in request.get_json():
                name = request.get_json()['name']
            if 'height' in request.get_json():
                height = request.get_json()['height']
            if 'weight' in request.get_json():
                weight = request.get_json()['weight']

        pokemon = { "_id": ObjectId(_id), "id":id, "name":name, "height":height, "weight":weight }
        db.samples_pokemon.insert_one(pokemon)
        pokemonjson = { "_id": (_id), "id":id, "name":name, "height":height, "weight":weight }
        return jsonify(pokemonjson)

api.add_resource(apirestful_1, "/apirestful/pokemon")

class apirestful_2(Resource):
    def get(self, idaux):
        try:
            pokemon = db.samples_pokemon.find_one({'_id':ObjectId(idaux)})
            return jsonify({
                '_id':            idaux,
                'id':             pokemon.get('id'),
                'name':           pokemon.get('name'),
                'img':            pokemon.get('img'),
                'type':           pokemon.get('type'),
                'height':         pokemon.get('height'),
                'weight':         pokemon.get('weight'),
                'candy':          pokemon.get('candy'),
                'candy_count':    pokemon.get('candy_count'),
                'egg':            pokemon.get('egg'),
                'spawn_chance':   pokemon.get('spawn_chance'),
                'avg_spawns':     pokemon.get('avg_spawns'),
                'spawn_time':     pokemon.get('spawn_time'),
                'multipliers':    pokemon.get('multipliers'),
                'weaknesses':     pokemon.get('weaknesses'),
                'next_evolution': pokemon.get('next_evolution'),
            })
        except:
          return jsonify({'error':'ERROR_NOT_FOUND'})

    def put(self, idaux):
        try:
            pokemon = db.samples_pokemon.find_one({'_id':ObjectId(idaux)})

            id = pokemon.get('id')
            name = pokemon.get('name')
            height = pokemon.get('height')
            weight = pokemon.get('weight')

            if(request.get_json() is not None):
                if 'id' in request.get_json():
                    id = request.get_json()['id']
                if 'name' in request.get_json():
                    name = request.get_json()['name']
                if 'height' in request.get_json():
                    height = request.get_json()['height']
                if 'weight' in request.get_json():
                    weight = request.get_json()['weight']

            id_new = { "$set": { 'id' : id , 'name' : name, 'height' : height, 'weight' : weight } }
            id_old = { '_id' : ObjectId(idaux) }
            db.samples_pokemon.update_one(id_old, id_new)

            pokemon = db.samples_pokemon.find_one({'_id':ObjectId(idaux)})
            return jsonify({
                'id':       pokemon.get('id'),
                'name':     pokemon.get('name'),
                'height':   pokemon.get('height'),
                'weight':   pokemon.get('weight')
            })
        except:
            return jsonify({'error':'ERROR_NOT_FOUND'})

    def delete(self, idaux):
        try:
            pokemon = db.samples_pokemon.find_one({'_id':ObjectId(idaux)})
            db.samples_pokemon.delete_one({ '_id' : pokemon.get('_id') })
            return jsonify({ '_id' : idaux, 'status' : 'borrado' })
        except:
            return jsonify({'error':'ERROR_NOT_FOUND'})

api.add_resource(apirestful_2, "/apirestful/pokemon/<string:idaux>")
