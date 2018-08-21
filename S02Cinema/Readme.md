# Sala de cinema - João Pedro Oliveira Santiago

O objetivo desta prática é criar uma **sala de cinema**, onde esta possui duas classes, uma chamada **Cliente** e outra chamada **Sala**.

- Como foi feito:
  - A classe chamada **Cliente** possui um método construtor, que por sua vez é um método capaz de determinar um default para a construção do objeto cliente. E essa classe é responsável por saber criar o cliente. Um cliente vai possuir **nome, telefone** e para facilitar a programação, temos uma variável booleana chamada **existe** que é responsável que determinar se o cliente existe ou não.
  
  - Para a impressão de um cliente é utilizada uma função chamada **toString** cuja atravez de um fluxo de dados, permite que os dados sejam armazenados no fluxo e por fim convertido em uma string.

  - **Sala** também necessita de uma método construtor, pelo mesmo motivo de cliente.

  - É utilizado uma estrutura *vector* de clientes para determinar a sala. E pelo método construtor de **Sala** é determinado que a sala inicie com as cadeiras vazias.

  - Para imprimir a sala é utilizada uma função que converte fluxo em string, assim como já feito para a classe cliente.

  - As funções **reservar** e **cancelar** foram feitas dentro da classe **Sala** pois é reservada uma cadeira que é um *vector* de clientes.

  - **Reservar** deve seguir algumas confições tais como: verificar se a cadeira passada pelo usuário existe; verificar se a cadeira já está ocupada; verificar se o cliente já possui uma cadeira na sala.

  - **Cancelar** deve percorrer todos os clientes e verificar se o nome do cliente cujo quer cancelar a reserva existe para alguma das cadeiras e, se existir, apagar seus dados.

- O que você aprendeu?

  - Aprendi um pouco mais sobre a relação entre classe e objeto.
  
  - Também sobre o método construtor, o porque ele é interessante de ser usado.

  - Conheci os chamados **fluxos** que podem ser transformados de fluxo para string e string para fluxo.

  - Conheci um pouco da estrutura *vector* e uma introdução sobre suas funcionalidades.

- O que você ainda tem dificuldades?

  - A principio compreender com clareza método construtor, fluxo e vectors. Porém, com algum tempo de estudo, essas estruturas (novidades para mim) se tornaram mais claras.

  - A maior dificuldade que encontrei foi ao tentar realizar o desafio utilizando ponteiros ao em vez da variável auxiliar boolena existe. Passei por volta de 6 horas em dias diferentes (1h30 á 2h por dia) tentando resolver este desafio. Porém, não tive exito em tal desafio.


