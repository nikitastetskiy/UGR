from django.db import models
from django.contrib.auth.models import User
from django.utils import timezone

class Libro(models.Model):
	id = models.IntegerField(primary_key=True)
	titulo = models.CharField(max_length=200)
	autor  = models.CharField(max_length=100)
	fecha = models.DateField(default=timezone.now)
	editorial = models.CharField(max_length=100)

	def __str__(self):
		return self.titulo

class Prestamo(models.Model):
	id = models.IntegerField(primary_key=True)
	libro   = models.ForeignKey(Libro, on_delete=models.CASCADE)
	fecha   = models.DateField(default=timezone.now)
	usuario = models.ForeignKey(User, on_delete=models.CASCADE)