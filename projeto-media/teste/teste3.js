var mat =  
    [   "mat",
        "geo",
        "filo",
        "his",
        "tec",
        "pika",
        "di",
        "ed",
        "fis",
        "geo"
    ]


var array = []
var foco = document.getElementById('numero')
this.id = 1
    
    function adicionou (){

        var tbody = document.getElementById('tbody')
        var numero = Number(document.getElementById('numero').value)
        foco.focus()


        array.push(numero)


        tbody.innerText = ''

        for(let i = 0; i < array.length; i++){
            let tr = tbody.insertRow()

            let td_notas = tr.insertCell()
            let td_acoes = tr.insertCell()

            td_notas.innerText = numero
            

            let imgDelete = document.createElement('img')
            imgDelete.src = 'excluir.png'
            imgDelete.setAttribute('onclick', "deletou("+this.array[i].id+")")
            
            td_acoes.appendChild(imgDelete)

        }
        
        console.log(array)

        
    }

    function deletou(id){

        let tbody = document.getElementById('tbody')

        for(let i = 0; i < array.length; i++){
            if(array[i].id == id){
                array.slice(i, 1)
                tbody.deleteRow(i)
            }
        }

        console.log(array)

    }
