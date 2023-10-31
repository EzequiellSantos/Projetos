var fonteSize = document.getElementById('p-email');
var containerFontSize = 8;

function tamanhoAtualPage() {

  //função para atualizar o valor do fontsize do email, para nao ficar quenbrando a pagina em dispositivos pequenos
  const sizePage = Number(window.innerWidth)
  if(sizePage < 800 ){
    fonteSize.style.fontSize = `${sizePage / 100 + containerFontSize}px`
  }else if(sizePage > 992){
    fonteSize.style.fontSize = `${sizePage / 100 + 2}px`
  }
  else{
    fonteSize.style.fontSize = '100%'
  }
}

window.addEventListener('resize', tamanhoAtualPage);// resize => evento DOM

tamanhoAtualPage(); //pegar o valor atualizado da View-Port
