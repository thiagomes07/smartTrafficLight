# Cidade clara

<div align="center">
    <img src="assets/whiteState.png" alt="imagem da cidade quando está clara">
</div>

# Cidade escura

<div align="center">
    <img src="assets/darkState.png" alt="imagem da cidade quando está escura">
</div>

# Debounce com millis e adição de 1 segundo quando o farol estiver vermelho e o botão for pressionado.

<div align="center">
    <img src="assets/debounceCode.png" alt="Código que implementa o debounce">
</div>

Acima é possível observar o código que implementa o debounce via software e também que verifica se o farol está vermelho para atrasar mais um segundo.

# Requisição HTTP caso a cidade esteja escura e o farol vermelho

<div align="center">
    <img src="assets/httpRequestCode.png" alt="Código que implementa o a requisição http quando o farol está vermelho">
</div>

através do código acima, é possível notar a presença de uma verificação se a esp32 está conectada ao wifi caso o farol esteja vermelho e realiza uma requisição para a url do google.

