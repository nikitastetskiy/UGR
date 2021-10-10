from django import forms

from .models import Libro, Prestamo

class LibroForm(forms.ModelForm):

    class Meta:
        model = Libro
        fields = ('titulo', 'autor', 'fecha', 'editorial',)

class PrestamoForm(forms.ModelForm):

    class Meta:
        model = Prestamo
        fields = ('libro', 'fecha', 'usuario',)