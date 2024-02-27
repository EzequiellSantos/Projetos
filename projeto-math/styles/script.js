window.addEventListener('scroll', function () {
  
  /* section fixada no topo */
  var section = document.querySelector('.fixed-section');
  var sectionOffset = section.offsetTop;
  var scrollPosition = window.scrollY;

  if (scrollPosition > sectionOffset && this.window.innerWidth > 700) {

    section.classList.add('fixed');

  } else {

    section.classList.remove('fixed');

  }

});


/* Configurações Menu */


