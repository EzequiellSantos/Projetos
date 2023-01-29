
var res = document.getElementById('res')
var res_2 = document.getElementById('res_2')
var arry = []

function adicionou (){
    var num = document.getElementById('num')

    if(Number(num.value) >= 0 && Number(num.value) <=10){
    arry.push(Number(num.value))
    res_2.innerHTML = ''
    res.innerHTML += `Valor ${num.value} adicionado <br>`
    } else{
        alert('DIgite um Número acima de 0')
    }
    num.value = ''
    num.focus()
}
 


function finalizou (){
    if(arry.length == 0 ){
       alert('Adicione Números')
    }else{
        let tot = arry.length
        let maior = arry[0]
        let menor = arry[0]
        let soma = 0
        let media = 0
        
        for(let pos in arry){
            soma += arry[pos]
            media += soma / tot
            if(arry[pos] > maior)
                maior = arry[pos]
            
            if(arry[pos] < menor)
                menor = arry[pos]
        
        }
        
        let mediatt = Number(media.toFixed(2))

        res_2.innerHTML = ''
        res_2.innerHTML += `<p>Ao todo temos ${tot} Número Cadastrados </p>`

        arry.sort()

        res_2.innerHTML += `<p>O Menor Número é o ${menor}</p>`
        res_2.innerHTML += `<p>O Maior Número é o ${maior}</p>`
        

        res_2.innerHTML += `<p>A Soma dos Valores é ${soma} </p>`
        res_2.innerHTML += `<p>A Média dos Valores é ${mediatt}</p>`

    }
    
} 

// https://pt.stackoverflow.com/questions/549721/como-somar-medidas-de-um-array