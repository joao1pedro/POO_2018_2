# Carro - João Pedro Oliveira Santiago

O objetivo desta prática é criar uma Classe denominada **Carro** que funcione como um carro. Ou seja, **carro** deve permitir a entrada e/ou saída de passageiros, abastecer e por fim andar desde que haja combustível suficiente para completar a viagem e haja alguma pessoa dentro do carro.

- Como foi feito:

  - O primeiro passo foi fazer a inicialização do carro. **Carro** inicia sem nenhum passageiro, de tanque vazio e kilometragem zerada.

  - Mais adiante duas funcções foram criadas são elas **in (embarcar)** e **out (desembarcar)** considerando as restrições de que **carro** tem capacidade máxima de **dois** passageiros e que não pode desembarcar se a quantidade de passageiros for inferior a **um**.

  - Também foi necessário a criação de uma função para abastecer o carro. Ela foi chamada de **fuel** e funciona de forma simples, abastece o carro de acordo com a quantidade passada pelo usuário, porém, com uma observação, o tanque de combustível tem o limite de 10 litros. Portanto, toda quantidade de combustivel superior a 10 litros é descartada.

  - Por fim foi criada a função **drive (andar)** que tem como condições, número de passageiros maior que zero, e se a gasolina for maior ou igual a distancia digitada pelo usuário dividida por 10 (visto que o carro tem consumo fixo de 10 kilometros por litro). Se essas condições forem atendidas, o carro anda, aumenta kilometragem e gasta combustivel.

- Oque você aprendeu?
  - Aprendi que structs na linguagem C++ funcionam como classes, ou seja, uma classe é algo que modela e tem-se planejamento, portanto, é onde define as caracteristicas, que para essa prática trata-se do carro.

  - E que o carro em si é o objeto, que pode ser manipulado.

- O que você ainda tem dificuldade?
  - Desde que entrei na universidade estudei basicamente a linguagem C pura, portanto, algumas coisas me pareceram estranhas a princípio. Um exemplo é que agora as funções da struct **carro** são definidas dentro da própria struct. E isso creio que seja pelo fato de em C++ struct ser uma classe, e pelo meu entendimento de classe, a classe deve saber seus atributos. Então, a dificuldade para essa pŕatica foi não conhecer a sintaxe de como as coisas funcionam em C++.

- Quanto tempo levou para fazer a atividade?

 - O tempo de desenvolvimento foi de aproximadamente 2 horas e meia.
  