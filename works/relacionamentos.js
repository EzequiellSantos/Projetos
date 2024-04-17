db.embedded.insertOne({
    nome: "Kiel",
    idade: 17,
    endereco: {
        rua: "Fulano de tal",
        numero: "777",
        complemento: "Ciclano de tal"
    }
})

db.embedded.insertOne({
    nome: "Jão",
    idade: 50,
    enderecos:{
        casa: {
            rua: "Rua Maluca",
            numero: "888",
            complemento: "Casa"
        },
        trabalho: {
            rua: "Rua das Árvores ", 
            numero: "333",
            complemento: "Galpão"
        }
    }
})  

db.pessoas.insertOne({
    nome: 'kiel',
    idade: 17,
    profissao: 'programador'
})

const p = db.pessoas.findOne({nome: 'kiel'})

db.enderecos.insertOne({
    rua: 'Rua das flores',
    numero: '1415',
    complemento: 'Casa',
    pessoa_id: p._id
});

/////

db.pessoas.insertOne({
    nome: "Cachorro",
    idade: 29,
    profissao: "Todas"
})


const cachorro = db.pessoas.findOne({
    nome: "Cachorro"
})

const cachorroId = cachorro._id

db.compras.insertMany([
    {produtos: ["livro", "Celular"], pessoa_id: cachorroId},
    {produtos: ["Goiaba", "Tangerina", "Ossinho-do-Guloso"], pessoa_id: cachorroId},
    {produtos: ["Perfume", "Teclado"], pessoa_id: p._id},
    {produtos: ["Pacote-de-Pão", "Bolacha-Coquinho", "Chocolate"], pessoa_id: p._id}
])

////

db.cursos.insertMany([
    {nome: "PHP avançado"},
    {nome: "JavaScript básico"},
    {nome: "Banco de Dados noSQL"}
])

// o nome da collection intermediaria deve ser a junção das duas collections separada por underline e em ordem alfabética no singular

db.curso_pessoa.insertMany([
    {curso_id: php._id, pessoa_id: kiel._id},
    {curso_id: js._id, pessoa_id: kiel._id},
    {curso_id: php._id, pessoa_id: cachorro._id}
])

// todos os alunos que cursam JS

const IDsAlunos = []

db.curso_pessoa.find({curso_id: js._id}).forEach( function(aluno) {
    IDsAlunos.push(aluno.pessoa_id)
});


// $in

db.pessoas.find({ _id: {$in: IDsAlunos}})

// todos os alunos que cursam JS atualizado

const IDsAlunos2 = []

db.curso_pessoa.find({curso_id: js._id}).forEach( function(aluno) {
    IDsAlunos2.push(aluno.pessoa_id)
});