var input = document.getElementById('input')
var ver = document.getElementById('ver')
var res = document.getElementById('res')
var saida = document.getElementById('saida')
ver.addEventListener('click', clicou)

function clicou(){
    /* 

    var valor = (Number(input.value) * 2) / 2
    res.innerText = `${valor}` 
    
    */
    var notas = 0
    for(var mat = 1 ; mat <= 2 ; mat ++){

        /* notas += saida.innerHTML = '<input type="number" inputmode="decimal">' */

        notas += Number(prompt('digite a nota'))
    }

    var total = notas / 2
    res.innerText = `${total}`


}