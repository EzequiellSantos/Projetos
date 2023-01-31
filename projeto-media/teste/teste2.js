
var add = document.getElementById('ver')
var res = document.getElementById('res')
var add_2 = document.getElementById('finl')
var res_2 = document.getElementById('res_2')

var arry = []


add.addEventListener('click', clicou)
add_2.addEventListener('click', finalizar)


function clicou(){
    var num = document.getElementById('num')

    arry.push(Number(num.value))
    res_2.innerText = ''
    res.innerHTML += `<div id="del">Valor ${num.value} add</div>`

    num.value = ''
    num.focus()


}

var del = document.getElementById('del')
del.addEventListener('click', deletou)


 function deletou (){
        res.innerHTML = `>>>${arry.pop()}`
}

function finalizar(){
    let tot = arry.length
    res_2.innerHTML += `${tot}<br>`
}