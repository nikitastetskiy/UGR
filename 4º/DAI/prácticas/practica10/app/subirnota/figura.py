#!/usr/bin/env python

from random import randrange as r

IMAGEN_ANCHO=700		# El ancho de las distintas figuras y el lienzo
IMAGEN_ALTO=700			# El alto de las distintas figuras y el lienzo
TRAZO=5					# El grosor del trazo
MAX_FIGURAS=20			# La cantidad de figuras o shapes
OPACIDAD=1.0			# La opacidad o la opacity

# Se crea un color random para el fondo

rand_color = lambda: '#'+''.join(['abcdef1234567890'[r(15)] for _ in range(6)])

BACKGROUND=rand_color()

def write():
	# versión xml
	txt = "<?xml version='1.0'?>"
	# ancho y alto del lienzo
	txt += "<svg width='%s' height='%s'>" % (IMAGEN_ANCHO,IMAGEN_ALTO)
	# ancho y alto del background
	txt += "<rect height='%s' width='%s' fill='%s'/>" % (\
		IMAGEN_ALTO, IMAGEN_ANCHO, BACKGROUND)

	txt += ''.join("%s" % rand_figuras() for _ in range(MAX_FIGURAS))

	return (txt+"</svg>")

def rand_figuras():
	figura = r(4)
	text = ""
	#Creación de rectángulos
	if not figura:
		text += "<rect x='%s'" % (r(IMAGEN_ANCHO))
		text += " y='%s'" % (r(IMAGEN_ALTO))
		text += " width='%s'" % (r(IMAGEN_ANCHO/2))
		text += " height='%s'" % (r(IMAGEN_ANCHO/2))
	#Creación de circulos
	elif figura == 1:
		text += "<circle cx='%s'" % (r(IMAGEN_ANCHO))
		text += " cy='%s'" % (r(IMAGEN_ALTO))
		text += " r='%s'" % (r(min(IMAGEN_ANCHO, IMAGEN_ALTO)/4))
	#Creación de elipses
	elif figura == 2:
		text += "<ellipse cx='%s'" % (r(IMAGEN_ANCHO))
		text += " cy='%s'" % (r(IMAGEN_ALTO))
		text += " rx='%s'" % (r(IMAGEN_ANCHO/2))
		text += " ry='%s'" % (r(IMAGEN_ANCHO/2))
	#Creación de lineas
	else:
		text += "<polyline points='"
		for _ in range(1,r(6)+3):
			text += "%s %s, " % (r(IMAGEN_ANCHO),r(IMAGEN_ANCHO))
		text += "'"
	#Creación del color y la opacidad (si no son lineas)
	if (r(2) == 0 and figura != 3):
		text += " fill='%s' fill-opacity='%s'/>" % (rand_color(), OPACIDAD) 
	else:
		text += " fill='none' stroke-width='%s'" % (r(TRAZO))
		text += " stroke='%s' stroke-opacity='%s'/>" % (rand_color(), OPACIDAD)
		
	return text