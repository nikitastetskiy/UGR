from django.urls import path
from . import views

urlpatterns = [
  path('', views.index, name='index'),
  path('', views.home, name='home'),
  path('test_template', views.test_template, name='test_template'),
  path('libros/add', views.add_libros, name='add_libros'),
  path('prestamos/add', views.add_prestamos, name='add_prestamos'),
  path('libros/get', views.get_libros, name='get_libros'),
  path('prestamo/get', views.get_prestamos, name='get_prestamos'),
  path('prestamo/get/<int:id>', views.get_prestamo, name='get_prestamo'),
  path('libros/get/<int:id>', views.get_libro, name='get_libro'),
  path('libros/edit', views.edit_libros, name='edit_libros'),
  path('libros/edit_form', views.edit_libros_form, name='edit_libros_form'),
  path('prestamos/edit', views.edit_prestamos, name='edit_prestamos'),
  path('prestamos/edit_form', views.edit_prestamos_form, name='edit_prestamos_form'),
  path('libros/delete', views.delete_libros, name='delete_libros'),
  path('prestamos/delete', views.delete_prestamos, name='delete_prestamos'),
]