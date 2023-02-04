class Notas {

    constructor(){
        this.id = 1
        this.arrayNotas = []
    }

    adicionou (){
        let foco = document.getElementById('numero')
        let notas = this.lerDados()

        if (this.validaCampos(notas)) {
            this.adicionar(notas);
        }

        this.listaTabela();
        this.cancelar();
        foco.focus()

    }

    listaTabela(){
        let tbody = document.getElementById('tbody')
        tbody.innerText = ''

        for(let i = 0 ; i < this.arrayNotas.length; i++){
            let tr = tbody.insertRow();

            let td_id = tr.insertCell();
            let td_nota = tr.insertCell();
            let td_acoes = tr.insertCell();
            
            td_id.innerText = this.arrayNotas[i].id;
            td_nota.innerText = this.arrayNotas[i].valorDanota;

            let imgEdit = document.createElement('img');
            imgEdit.src = 'editar.png';

            let imgDelete = document.createElement('img')
            imgDelete.src = 'excluir.png';

            td_acoes.appendChild(imgEdit);
            td_acoes.appendChild(imgDelete);

        }
    }

    adicionar(notas) {
        this.arrayNotas.push(notas);
        this.id++;
    }

    lerDados(){
        let notas = {}

        notas.id = this.id
        notas.valorDanota = document.getElementById('numero').value;


        return notas 
        
    }

    validaCampos(){
        let msg = '' 

        if(notas.valorDanota == ''){
            msg += '- Adicione uma Nota \n';
        }

        if(msg != ''){
            alert(msg);
            return false
        }

        return true;
    }

    cancelar (){
        document.getElementById('numero').value = ''
    }
}

var notas= new Notas();

function calculou(){
    alert("calculou")
}

function deletou(){
    alert('deletou')
}