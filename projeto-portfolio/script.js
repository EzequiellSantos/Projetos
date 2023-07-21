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

