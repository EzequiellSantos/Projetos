var  materias = window.prompt('Quantas matérias tem o seu curso?')

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
var input = document.getElementById('input')

ver.addEventListener('click', clicou)
    
var p1 = document.getElementsByTagName('p')[0]
if(materias > 1){
p1.innerHTML = `<p class="p1">Para Cursos Com <span class="quant">${materias}</span> Matérias</p>`}else if(materias == 1){
    p1.innerHTML = `<p class="p1">Para Cursos Com <span class="quant">${materias}</span> Matéria</p>`
}else{
    p1.innerHTML = '<p>[ERROR_]</p>'
}

const materia = [
    /* 'AI:',
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
    'Formação Cidadã Undefined_:' */
    '1 :',
    '2 :',
    '3 :',
    '4 :',
    '5 :',
    '6 :',
    '7 :',
    '8 :',
    '9 :',
    '10 :',
    '11 :',
    '12 :',
    '13 :',
    '14 :',
    '15 :',
    '16 :',
    '17 :',
    '18 :',
    '19 :',
    '20 :'
    
]

function clicou(){
    var input = document.createElement('input')
    input.setAttribute("type","number")

    
    var notas = 0
    for ( var Mat = 1  ; Mat <= materias; Mat++){
        notas += Number(prompt(`Qual a nota de ${materia[Mat - 1]}`))
    }

    var total = notas / materias
    var totalfrm = parseFloat(total.toFixed(2)) 

    if(total < 6){
        res.innerHTML += `<p> Sua média final é: <mark class='nobix'>${totalfrm}</mark></p>`
    }else if(total < 8.5){
        res.innerHTML += `<p> Sua média final é: <mark class="intr">${totalfrm}</mark></p>`
    }else if(total <= 10){
        res.innerHTML += `<p> Sua média final é: <mark class="bix">${totalfrm}</mark></p>`
    }else{
        res.innerHTML = '<p>A sua nota <mark class="nobix">Ultrapassou 10.00</mark> verifique os dados novamente</p><hr class="mnr">'
    }
     
}