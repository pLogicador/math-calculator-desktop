const resultado = document.querySelector(".result");
const botoes = document.querySelectorAll(".arithmetic-button, .numberbutton, .token, .button-zero ");

let entradaAtual = '';
let operador = '';
let primeiroValor = null;
const maxDigitosVisor = 16;

// Função para atualizar o visor de resultados
function atualizaResultado(){
    if (entradaAtual.length > maxDigitosVisor){
        // Limita o número de dígitos no visor
        entradaAtual = entradaAtual.slice(0, maxDigitosVisor);
    }
    resultado.textContent = entradaAtual;
}

// Função que lida com os cliques e operadores aritiméticos
function cliqueButtom( evento ){
    const valorButtom = evento.target.textContent;

    if (!isNaN( valorButtom )){
        entradaAtual += valorButtom; 
    } else if ( valorButtom == 'C' ){
        entradaAtual = ' ';
        primeiroValor = null;
        operador = ' ';

    } else if ( valorButtom === '+/-' && entradaAtual !== '' ){
        entradaAtual = ( -parseFloat(entradaAtual) ).toString();

    } else if ( valorButtom === '%' ){
        entradaAtual = ( parseFloat(entradaAtual) / 100 ).toString();

    } else if ( valorButtom === '=' ) {
        if ( primeiroValor !== null && operador !== '' ) {
            switch (operador) {
                case '+':
                    entradaAtual = ( primeiroValor + parseFloat(entradaAtual) ).toString();
                    break;
                case '-':
                    entradaAtual = ( primeiroValor - parseFloat(entradaAtual) ).toString();
                    break;
                case 'x':
                    entradaAtual = ( primeiroValor * parseFloat(entradaAtual) ).toString();
                    break;
                case '/':
                    if ( parseFloat(entradaAtual) != 0 ){
                        entradaAtual = ( primeiroValor / parseFloat(entradaAtual) ).toString();
                    } else {
                        entradaAtual = "Divisão por zero";
                    }
                    break;
            }
            operador = '';
            primeiroValor = null;
        }

    /*  Quando não há um primeiro valor definido, definimos o primeiroValor e o 
        operador, mas não exibimos o operador no visor.*/
    } else if ( primeiroValor == null ) {
        // Isso aguarda a entrada do segundo número
        primeiroValor = parseFloat( entradaAtual );
        operador = valorButtom;
        entradaAtual = '';
    } else {
        operador = valorButtom;
    }

    atualizaResultado();

}


// Adiciona um ouvinte de envento para cada botão pressionado
botoes.forEach(( buttom )=>{
    buttom.addEventListener('click', cliqueButtom )
})