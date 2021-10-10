from django.shortcuts import render, HttpResponse, redirect
from .models import Libro, Prestamo
from .forms import LibroForm, PrestamoForm
from django.views.decorators.csrf import csrf_exempt
from django.contrib.auth.models import User




def index(request):
	context = {}
	return render(request, 'home.html', context)

def home(request):
	context = {}
	return render(request, 'home.html', context)

# def login(request):
# 	context = {}
# 	return render(request, '../../templates/account/login.html', context)

def test_template(request):
	context = {}
	return render(request, 'test.html', context)


# ACCESO


def get_libros(request):
	return render(request,'get_libros.html',{'libros': Libro.objects.all()})

def get_libro(request, id):
	return render(request,'get_libros.html',{'libros': Libro.objects.all().filter(id=id)})

def get_prestamos(request):
	return render(request,'get_prestamos.html',{'prestamos': Prestamo.objects.all()})

def get_prestamo(request,id):
	return render(request,'get_prestamos.html',{'prestamos': Prestamo.objects.all().filter(id=id)})


# AÑADIR


def add_libros(request):
	if request.method == 'POST':
		mensaje = ''
		libro = Libro()
		form = LibroForm(request.POST)
		if form.is_valid():
			libro.titulo = form.cleaned_data['titulo']
			libro.autor = form.cleaned_data['autor']
			libro.fecha = form.cleaned_data['fecha']
			libro.editorial = form.cleaned_data['editorial']
			libro.save()
			return redirect(get_libro, Libro.objects.all().order_by("-id")[0].id)
	else:
		mensaje = ''
		form = LibroForm()
	return render(request, 'add_libros.html', {'form':form})

def add_prestamos(request):
	if request.method == 'POST':
		prestamo = Prestamo()
		form = PrestamoForm(request.POST)
		if form.is_valid():
			prestamo.libro = form.cleaned_data['libro']
			prestamo.fecha = form.cleaned_data['fecha']
			prestamo.usuario = form.cleaned_data['usuario']
			prestamo.save()
			return redirect(get_prestamo, Prestamo.objects.all().order_by("-id")[0].id)
	else:
		form = PrestamoForm()
	return render(request, 'add_prestamos.html', {'form':form})


# EDITAR


def edit_libros(request):
	if request.method == 'POST':
		libro = Libro.objects.get(id=request.session['id'])
		form = LibroForm(request.POST)
		if form.is_valid():
			libro.titulo = form.cleaned_data['titulo']
			libro.autor = form.cleaned_data['autor']
			libro.fecha = form.cleaned_data['fecha']
			libro.editorial = form.cleaned_data['editorial']
			libro.save()
		return redirect(get_libro, request.session['id'])
	libros = Libro.objects.all()
	return render(request,'edit_libros.html',{'libros': libros})

@csrf_exempt 
def edit_libros_form(request):
	request.session['id'] = request.POST['libro']
	libro = Libro.objects.all().filter(id=request.POST['libro'])
	form = LibroForm()
	for l in libro:
		form.fields['titulo'].initial = l.titulo
		form.fields['autor'].initial = l.autor
		form.fields['fecha'].initial = l.fecha
		form.fields['editorial'].initial = l.editorial

	return render(request, 'edit_libros_form.html', {'form':form, 'libros':libro})

def edit_prestamos(request):
	if request.method == 'POST':
		prestamo = Prestamo.objects.get(id=request.session['id'])
		form = PrestamoForm(request.POST)
		if form.is_valid():
			prestamo.libro = form.cleaned_data['libro']
			prestamo.fecha = form.cleaned_data['fecha']
			prestamo.usuario = form.cleaned_data['usuario']
			prestamo.save()
		return redirect(get_prestamo, request.session['id'])
	prestamos = Prestamo.objects.all()
	return render(request,'edit_prestamos.html',{'prestamos': prestamos})

@csrf_exempt 
def edit_prestamos_form(request):
	request.session['id'] = request.POST['prestamo_id']
	prestamo = Prestamo.objects.all().filter(id=request.POST['prestamo_id'])
	form = PrestamoForm()
	for l in prestamo:
		form.fields['libro'].initial = l.libro
		form.fields['fecha'].initial = l.fecha
		form.fields['usuario'].initial = l.usuario

	return render(request, 'edit_prestamos_form.html', {'form':form, 'prestamos':prestamo})
	


# BORRAR


@csrf_exempt 
def delete_libros(request):
	if request.method == 'POST':
		Libro.objects.all().filter(id=request.POST['libro']).delete()
		return redirect(delete_libros)
	libros = Libro.objects.all()
	return render(request,'delete_libros.html',{'libros': libros})

@csrf_exempt 
def delete_prestamos(request):
	if request.method == 'POST':
		Prestamo.objects.all().filter(id=request.POST['prestamo_id']).delete()
		return redirect(delete_prestamos)
	prestamos = Prestamo.objects.all()
	return render(request,'delete_prestamos.html',{'prestamos': prestamos})