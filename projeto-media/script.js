var animateButton = function (e) {
    e.preventDefault;
    //reset animation
    e.target.classList.remove("animate");

    e.target.classList.add("animate");
    setTimeout(function () {
        e.target.classList.remove("animate");
    }, 700);
};

var bubls = document.getElementsByClassName("bubl");

for (var i = 0; i < bubls.length; i++) {
    bubls[i].addEventListener("click", animateButton, false);
}

///////////////////////////

var ver = document.getElementById('ver')
var res = document.getElementById('res')
ver.addEventListener('click', clicou)

const materia = [
    'AI:',
    'Bio:',
    'Ed.Fís:',
    'Filo:',
    'Fís:',
    'Geo:',
    'his:',
    'Espan:',
    'Ingle:',
    'Portu:',
    'Mate:',
    'OET:',
    'Quim:',
    'RET:',
    'Socio:',
    'Formação Cidadã Undefined_:'

]

function clicou(){
    var notas = 0
    for ( var Mat = 1  ; Mat <=16 ; Mat++){
        notas += Number(prompt(`Qual a nota ${materia[Mat - 1]}`))
    }
    var notasfrm = Number.parseFloat(notas.toFixed(2))
    var total = notasfrm / 16

    if(total < 6){
        res.innerHTML += `<p> Sua média final é: <mark class='nobix'>${total}</mark></p>`
    }else if(total < 8){
        res.innerHTML += `<p> Sua média final é: <mark class="intr">${total}</mark></p>`
    }else{
        res.innerHTML += `<p> Sua média final é: <mark class="bix">${total}</mark></p>`
    }
    
}