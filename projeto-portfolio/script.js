var fonteSize = document.getElementById('p-email');
var containerFontSize = 9;

function tamanhoAtualPage() {
  
  //função para atualizar o valor do fontsize do email, para nao ficar quenbrando a pagina em dispositivos pequenos

  const sizePage = Number(window.innerWidth)
  fonteSize.style.fontSize = `${sizePage / 100 + containerFontSize}px`
}

window.addEventListener('resize', tamanhoAtualPage);// resize => evento DOM

tamanhoAtualPage(); //pegar o valor atualizado da View-Port








