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