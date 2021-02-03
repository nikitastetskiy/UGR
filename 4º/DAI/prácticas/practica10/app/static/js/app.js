// Este código jQuery funciona cuando se cargue la página
$(function () {

  $( document ).ready(function(){
    var $fila = $('#fila')

    $.ajax({
      type:'GET',
      url: '/api/pokemon',
      success:function(pokemons){
        $.each(pokemons, function(i, pokemon){
          $fila.append('<tr><td>'
          + pokemon.id + `<img class="card-img-top" src=${pokemon.img} alt="Imagen" style="width: 3rem;display:inline-block;margin-left:10%;vertical-align:top;margin-bottom:10%"></td><td>`
          + pokemon.name + '</td><td>' + pokemon.height + '</td><td>'
          + pokemon.weight + '</td>'
          + `<td><a name="move" id="move" href="/modifybd?name=${pokemon.name}" class="btn btn-warning btn-lg active" role="button" aria-pressed="true">Editar</a></td>` 
          + `</td><td> <button class="btn btn-danger btn-lg active" role="button" aria-pressed="true" input onclick="Borrar('${pokemon._id}')" >Borrar</button> </td></tr>`)
        });
      }
    });
  });

  // Buscar con input
  $('#buscar').keyup(function(){
    let value = $(this).val()
    var request_url = '/api/pokemon/' + value
    var $fila = $('#fila')

    if(value != ""){
      $.ajax({
        type:'GET',
        url: request_url,
        success:function(pokemons){
          // Limpiar consulta previa
          var div = document.getElementById('fila');
          while (div.firstChild) {
              div.removeChild(div.firstChild);
          }
            $fila.append('<tr><td>'
            + pokemons.id + `<img class="card-img-top" src=${pokemons.img} alt="Imagen" style="width: 3rem;display:inline-block;margin-left:10%;vertical-align:top;margin-bottom:10%"></td><td>`
            + pokemons.name + '</td><td>' + pokemons.height + '</td><td>'
            + pokemons.weight + '</td>'
            + `<td><a name="move" id="move" href="/modifybd?name=${pokemons.name}" class="btn btn-warning btn-lg active" role="button" aria-pressed="true">Editar</a></td>` 
            + `</td><td> <button class="btn btn-danger btn-lg active" role="button" aria-pressed="true" input onclick="Borrar('${pokemons._id}')" >Borrar</button> </td></tr>`)
          
        }
      });
    } else {
      $.ajax({
        type:'GET',
        url: '/api/pokemon',
        success:function(pokemons){
          $.each(pokemons, function(i, pokemon){
            $fila.append('<tr><td>'
            + pokemon.id + `<img class="card-img-top" src=${pokemon.img} alt="Imagen" style="width: 3rem;display:inline-block;margin-left:10%;vertical-align:top;margin-bottom:10%"></td><td>`
            + pokemon.name + '</td><td>' + pokemon.height + '</td><td>'
            + pokemon.weight + '</td>'
            + `<td><a name="move" id="move" href="/modifybd?name=${pokemon.name}" class="btn btn-warning btn-lg active" role="button" aria-pressed="true">Editar</a></td>` 
            + `</td><td> <button class="btn btn-danger btn-lg active" role="button" aria-pressed="true" input onclick="Borrar('${pokemon._id}')" >Borrar</button> </td></tr>`)
          });
        }
      });
    }
   
  });
});

// Funciona con un click en el botón
function Borrar(id) {
  // Restablecer funciones jQuery en el DOM que estabamos
  $(function () {
    var request_url = '/api/pokemon/' + id
    $.ajax({
      url: request_url,
      type:'DELETE',
      success:function(result){
      }
    });

    var value = $('#buscar').val()
    request_url = '/api/pokemon/' + value
    var $fila = $('#fila')
    
    if(value == ""){
      request_url = '/api/pokemon'
    }
    
    // Limpiar consulta previa
    var div = document.getElementById('fila');
    while (div.firstChild) {
        div.removeChild(div.firstChild);
    }

    $.ajax({
      type:'GET',
      url: request_url,
      success:function(pokemons){
        
        $.each(pokemons, function(i, pokemon){
          $fila.append('<tr><td>'
          + pokemon.id + `<img class="card-img-top" src=${pokemon.img} alt="Imagen" style="width: 3rem;display:inline-block;margin-left:10%;vertical-align:top;margin-bottom:10%"></td><td>`
          + pokemon.name + '</td><td>' + pokemon.height + '</td><td>'
          + pokemon.weight + '</td>'
          + `<td><a name="move" id="move" href="/modifybd?name=${pokemon.name}" class="btn btn-warning btn-lg active" role="button" aria-pressed="true">Editar</a></td>` 
          + `</td><td> <button class="btn btn-danger btn-lg active" role="button" aria-pressed="true" input onclick="Borrar('${pokemon._id}')" >Borrar</button> </td></tr>`)
        });
      }
    });
  });
}

// Para iniciar el mapa
function initMap() {
  let map = new google.maps.Map(document.getElementById('map'), {
      center: {lat: 35.895252, lng: -78.91968650000001},
      mapTypeId: 'satellite',
      zoom: 3,
      disableDefaultUI: true,
  });
      window.onload = setMarkers(map);
}

// iniciar los marcadores
function setMarkers(map) {
	// bucle que genera un detector de eventos y sprites para cada pokemon 
	$.ajax({
    type:'GET',
    url: '/api/pokemon',
    success:function(pokemons){
      $.each(pokemons, function(i, pokemon){
        var image = {
          url: pokemon.img,
          scaledSize: new google.maps.Size(75, 75)
      }
      var marker = new google.maps.Marker({
		    position: new google.maps.LatLng(numGen(80, -80, 3), numGen(-180, 180, 3)),
		    id: i,
		    map: map,
		    icon: image
      });
      
      attachSecretMessage(marker, "<p>"+ "ID: " + pokemon.id +"</p>"+
        "<p>"+ "Pokémon: " + pokemon.name +"</p>"+
        "<p>"+ "Altura: " + pokemon.height +"</p>"+
        "<p>"+ "Peso: " + pokemon.weight +"</p>");
      });
    }
  });
}

// función para aleatorizar números en un rango y con lugares decimales específicos 
var numGen =  function(to, from, fixed) {
  return (Math.random() * (to - from) + from).toFixed(fixed) * 1; 
}

// mensajes de los marcadores
function attachSecretMessage(marker, secretMessage) {
  const infowindow = new google.maps.InfoWindow({
    content: secretMessage,
  });
  marker.addListener("click", () => {
    infowindow.open(marker.get("map"), marker);
  });
}