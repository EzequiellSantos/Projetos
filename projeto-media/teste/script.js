          const noteInput = document.querySelector("#noteInput");
          const addNoteButton = document.querySelector("#addNote");
          const notesList = document.querySelector("#notes");
          const averageElement = document.querySelector("#average");

          
          let notes = [];
           

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
              noteElement.innerText = note;
    
              const editButton = document.createElement("button");
              editButton.setAttribute('class', 'edit')
              editButton.innerHTML ='<img src="editar.png">' ;
              editButton.addEventListener("click", () => {
                noteInput.value = note;
                notes.splice(i, 1);
                renderNotes();
              });
              noteElement.appendChild(editButton);
    
              const deleteButton = document.createElement("button");
              deleteButton.setAttribute('class', 'delet')
              deleteButton.innerHTML= '<img src="excluir.png">';
              deleteButton.addEventListener("click", () => {
                notes.splice(i, 1);
                renderNotes();
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
          }
          
         function reload(){
          window.location.reload(true)
         }