const noteInput = document.querySelector("#noteInput");
const addNoteButton = document.querySelector("#addNote");
const notesList = document.querySelector("#notes");
const averageElement = document.querySelector("#average");
const themeToggleBtn = document.querySelector(".theme-toggler")
const calculadora = document.querySelector(".calculadora")
const toggleIcon = document.querySelector(".toggler-icon")

let notes = [];

noteInput.addEventListener('keydown', function(event){
  if(event.keyCode === 13){//validação da tecla enter(código 13)

    if (noteInput.value.length == '') {

      alert('Digite uma Nota!')   
  
    }else{
      event.preventDefault()
      const note = parseFloat(noteInput.value);
      if (!isNaN(note)) {
        notes.push(note);
        noteInput.value = "";
        renderNotes();
      }
    }
  }      
}) 


addNoteButton.addEventListener("click", () => {
  
  if (noteInput.value.length == '') {

    alert('Digite uma Nota!')   

  }else{

    const note = parseFloat(noteInput.value);
    if (!isNaN(note)) {
      notes.push(note);
      noteInput.value = "";
      renderNotes();
    }
  }
});

function renderNotes() {
  notesList.innerHTML = "";
  noteInput.focus()


  for (let i = 0; i < notes.length; i++) {
    const note = notes[i];
    const noteElement = document.createElement("li");
    //criando a lista de todas as notas
    noteElement.innerText = note;

    const editButton = document.createElement("button");
    editButton.setAttribute('class', 'edit')
    editButton.innerHTML ='<img src="editar.png">' ;
    //criação do botão de editas
    
    editButton.addEventListener("click", () => {
      noteInput.value = note;
      notes.splice(i, 1);
      renderNotes();
      //atualização das notas
    });
    noteElement.appendChild(editButton);

    const deleteButton = document.createElement("button");
    deleteButton.setAttribute('class', 'delet')
    deleteButton.innerHTML= '<img src="excluir.png">';
    //criação do botão de deletar

    deleteButton.addEventListener("click", () => {
      notes.splice(i, 1);
      renderNotes();
      //atualização do delete das notas
    });
    noteElement.appendChild(deleteButton);

    notesList.appendChild(noteElement);
  }
  updateAverage();
}

function updateAverage() {
  let sum = 0;
  for (const note of notes) {
    sum += note;
  }
  const average = sum / notes.length;
  averageElement.innerText = average.toFixed(2);
  //calculaando a média da todas as notas presentes
}

//exibindo o toggle theme
const menu = document.querySelector("#menu")
menu.onclick = () =>{
  themeToggleBtn.style.display = 'block'
  menu.style.transition = 'all 0.01s ease'
  menu.style.padding = '1px 1px 40px 15px'   
}

themeToggleBtn.onmouseout = () =>{
  themeToggleBtn.style.display = 'none'
  menu.style.transition = 'all 0.5s ease'
  menu.style.padding = '1px 1px 5px 15px'
}



//mudando o tema da calculadora
let isLight = true

themeToggleBtn.onclick = () => {
  calculadora.classList.toggle("light")
  themeToggleBtn.classList.toggle("active")
  toggleIcon.classList.toggle("active")
  isLight = !isLight  
}

function reload(){
window.location.reload(true)
//botão limpar
}