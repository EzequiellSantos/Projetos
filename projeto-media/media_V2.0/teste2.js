
var res = document.getElementById('res')
var res_2 = document.getElementById('res_2')
var arry = []



function adicionou (){
    var num = document.getElementById('num')

    if(Number(num.value.length) >= 0 && Number(num.value) <=10){
    arry.push(Number(num.value))
    res_2.innerHTML = ''
    res.innerHTML += `Nota ${num.value} adicionada <button id="del">deletar</button><br>`
    }else{
        alert('Digite Sua Nota')
    }
    num.value = ''
    num.focus()
}


/*
var del = document.getElementById('del')
del.addEventListener('click', deletou)


 function deletou (){
        arry.pop()
        res_2.innerHTML -= `>>>${arry}`
}
 */

 





function finalizou (){
    //// validação
    if(arry.length == 0 ){
       alert('Adicione Números')
    }else{
        
            ///// calcular a  media e soma dos itens
        let tot = arry.length
        let maior = arry[0]
        let menor = arry[0]
        let soma = 0
        let media = 0
        
        for(let pos in arry){
            soma += arry[pos]
            media = soma / tot
            if(arry[pos] > maior)
                maior = arry[pos]
            
            if(arry[pos] < menor)
                menor = arry[pos]
        
        }

        /// resposta ao usuário
        
        let mediatt = Number(media.toFixed(2))

        res_2.innerHTML = ''
        res_2.innerHTML = `${tot}`

        arry.sort()// organização da arry

        res_2.innerHTML += `<p>O Menor Número é o ${menor}</p>`
        res_2.innerHTML += `<p>O Maior Número é o ${maior}</p>`
        res_2.innerHTML += `<p>A Soma dos Valores é ${soma} </p>`
        res_2.innerHTML += `<p>A Média dos Valores é ${mediatt}</p>`

        var finl  = document.getElementById('finl')
        finl.innerHTML = '<div id="reset">Calcular Novamente</div>'
    }


        //////////// botão de reiniciar a página
    var reset = document.getElementById('reset')
    reset.addEventListener('click', reload)

    function reload(){
        window.location.reload(true)
    }
} 

// https://pt.stackoverflow.com/questions/549721/como-somar-medidas-de-um-array

/* 

colocar um backspace dps de cada número inserido


*/