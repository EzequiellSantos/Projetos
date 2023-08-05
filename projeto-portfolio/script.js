window.addEventListener('scroll', function() {/* section fixada no topo */
  var section = document.querySelector('.fixed-section');
  var sectionOffset = section.offsetTop;
  var scrollPosition = window.scrollY;

  if (scrollPosition > sectionOffset) {
      section.classList.add('fixed');
  } else {
      section.classList.remove('fixed');
  }
});

/* Configurações Menu */
var imgMenu = document.getElementById('img-menu');
var linkIcon = document.getElementById('link-menu');
var imgIcon = document.getElementById('casa-icon');

var menu = document.getElementById('menu');
var allSetas = document.querySelector('.setas');
var setaOn = document.getElementById('seta01');
var setaTw = document.getElementById('seta02');
var setatr = document.getElementById('seta03');



menu.addEventListener('click', function() {

  if(linkIcon.classList.contains('mostrar')){

    menu.style.transition = 'all 0.6s ease-in-out' 
    linkIcon.classList.remove('mostrar')
    imgIcon.classList.remove('mostrar')
    menu.classList.remove('actived')

  }else{

    linkIcon.classList.add('mostrar')
    menu.classList.add('actived')
    menu.style.transition = 'all 0.6s ease-in-out'
    setTimeout( function() {
      imgIcon.classList.add('mostrar')
    }, 400)
  }
}) 

/* document.addEventListener('click', function(evento) {
  const clicadoDentroDoElemento = menu.contains(evento.target)

  if(!clicadoDentroDoElemento){
    imgIcon.style.display = 'none'
    menu.classList.remove('actived')
    menu.style.transition = 'all 0.6s ease-in-out'
  }
})
 */
////////////////////////////////////////////

const card = document.querySelector('#cards');

card.addEventListener('mousemove', handleMouseMove);
card.addEventListener('mouseout', resetCard);



function handleMouseMove(event) {
  const cardWidth = card.offsetWidth;
  const cardHeight = card.offsetHeight;
  const xAxis = (cardWidth / 2 - event.pageX) / 130;
  const yAxis = (cardHeight / 2 - event.pageY) / 100;



  card.style.transform = `perspective(1000px) rotateY(${xAxis}deg) rotateX(${yAxis}deg)`;
}

function resetCard() {
  card.style.transform = 'perspective(1000px) rotateY(0deg) rotateX(0deg)';
}

