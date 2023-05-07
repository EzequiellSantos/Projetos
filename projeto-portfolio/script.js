class MobileNavbar {
    constructor(mobileMenu, navList, navLinks) {
        this.mobileMenu = document.querySelector(mobileMenu)
        this.navList = document.querySelector(navList)
        this.navLinks = document.querySelectorAll(navLinks)
        this.activeClass = "active"
        this.desactiveClass = "desactive"

        this.handleClick = this.handleClick.bind(this)
    }

    animateLinks() {
        this.navLinks.forEach((link, index) => {
            console.log(index)
            link.style.animation
            ? (link.style.animation = "")
            : (link.style.animation = `navLinkFade 0.5s ease forwards ${index / 7 + 0.3}s`)
        })
    }

    handleClick() {
        this.navList.classList.toggle(this.activeClass)
        this.animateLinks()
    }

    addClickEvent() {
        this.mobileMenu.addEventListener("click", this.handleClick)
    }

    init() {
        if(this.mobileMenu) {
            this.addClickEvent()
        }
        return this;
    }
}

const mobileNavbar = new MobileNavbar(
    ".mobile-menu",
    "#nav-list",
    "#nav-list li"
)
mobileNavbar.init()
/* 

O código acima não é meu :(
youtube -> Tiger Codes

*/

////////////////////////    

let burgerMenu = document.getElementsByClassName('mobile-menu')[0]
let lineOne = document.getElementsByTagName('div')[1]
let lineTwo = document.getElementsByTagName('div')[2]
let lineThree = document.getElementsByTagName('div')[3]
let navMenu = document.getElementById('menu')
let ulMenu = document.getElementsByTagName('ul')[0]

burgerMenu.addEventListener('mouseover', clicou)
burgerMenu.addEventListener('', none)
navMenu.addEventListener('mouseout', fora)


/* function clicou(){

    lineOne.style.transform = 'rotate(-45deg) translate(-8px, 8px)'
    lineTwo.style.opacity = '0'
    lineThree.style.transform = 'rotate(45deg) translate(-5px, -7px)'

    ulMenu.style.position = 'fixed'
    burgerMenu.style.position = 'fixed' 
}

function fora(){
        ulMenu.style.position = 'absolute'
        burgerMenu.style.position = 'absolute'
        lineTwo.style.opacity = '1'
    }


function clickOut(clickfora){
    if(clickfora == false) {
        lineOne.style.transform = 'rotate(45deg) translate(-8px, 8px)'
        lineTwo.style.opacity = '0'
        lineThree.style.transform = 'rotate(45deg) translate(-5px, -7px)'

        ulMenu.style.position = 'absolute'
        burgerMenu.style.position = 'absolute'
    } else {
        
    }
    clickOut(clicou)
}  */ 

/* if (!clicadoDentroDoElemento) 
        lineOne.style.transform = 'none'
        lineTwo.style.opacity = '1'
        lineThree.style.transform = 'none' */

        function clicou(){
        
            ulMenu.style.position = 'fixed' 
           /*  burgerMenu.style.position = 'fixed'  */
        }
        




