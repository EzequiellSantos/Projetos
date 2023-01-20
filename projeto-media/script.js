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

/* var ver = document.getElementById('ver')
var res = document.getElementById('res')
var input = document.getElementById('input')
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
    'Formação Cidadã Undefined_ :'
    
]

prompt.focus()
function clicou(){
    var notas = 0
    for ( var Mat = 1  ; Mat <=16 ; Mat++){
        notas += Number(prompt(`Qual a nota de ${materia[Mat - 1]}`))
    }

    var total = notas / 16
    var totalfrm = parseFloat(total.toFixed(2))

    if(total <=10){
       if(total < 6){
        res.innerHTML += `<p> Sua média final é: <mark class='nobix'>${totalfrm}</mark></p><hr class="mnr">`
       }else if(total < 8.5){
        res.innerHTML += `<p> Sua média final é: <mark class="intr">${totalfrm}</mark></p><hr class="mnr">`
       }else{
        res.innerHTML += `<p> Sua média final é: <mark class="bix">${totalfrm}</mark></p><hr class="mnr">`
       }
    }else{
        res.innerHTML = '<p><mark class="nobix">Sua nota Ultrapassou 10.00 verifique os dados novamente</mark></p><hr class="mnr">'
    }
} */