var saida = document.getElementById("date");

var atual = new Date()
var nameDay = atual.getDay()
var dia = atual.getDate()
var mes = atual.getMonth()
var nameMonth = atual.getMonth()
var ano = atual.getFullYear()

switch (nameDay){
    case 0:
        nameDay = "Domingo"
        break
    case 1:
        nameDay = "Segunda-feira"
        break
    case 2:
        nameDay = "Terça-feira"
        break   
    case 3:
        nameDay = "Quarta-feira"
        break   
    case 4:
        nameDay = "Quinta-feira"
        break     
    case 5:
        nameDay = "Sexta-feira"
        break       
    case 6:
        nameDay = "Sábado"
        break         
}

switch (nameMonth){
    case 1:
        nameMonth = "Jan"
        break
    case 2:
        nameMonth = "Fev"
        break
    case 3:
        nameMonth = "Mar"
        break
    case 4:
        nameMonth = "Abr"
        break
    case 5:
        nameMonth = "Mai"
        break
    case 6:
        nameMonth = "Jun"
        break
    case 7:
        nameMonth = "Jul"
        break
    case 8:
        nameMonth = "Ago"
        break
    case 9:
        nameMonth = "Set"
        break
    case 10:
        nameMonth = "Out"
        break
    case 11:
        nameMonth = "Nov"
        break
    case 12:
        nameMonth = "Dez"
        break
}


saida.innerHTML = `<p>${nameDay} ${dia} ${nameMonth} ${ano}`
