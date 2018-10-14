# 01 Carro -

O objetivo desta prática é criar uma Classe denominada **Carro** que funcione como um carro. Ou seja, **carro** deve permitir a entrada e/ou saída de passageiros, abastecer e por fim andar desde que haja combustível suficiente para completar a viagem e haja alguma pessoa dentro do carro.
  - Atividade feita individualmente.

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

 # Topic 02 - 

O objetivo desta prática é simular a alocação de uma topic, cuja apresenta *n* cadeiras e *m* cadeiras preferenciais. De modo que quando algum passageiro entre na topic, se ele tiver idade de 60 anos ou mais ele é prioridade e portanto deve ser alocado em cadeiras preferenciais, essas cadeiras preferenciais são as cadeiras mais a frente do veiculo. (Por ora atividade não finalizada).
  - Atividade feita individualmente.

- Como foi feito:
  - Foram necessárias a criação de três classes, são elas: **Topic, Passageiroc e Controller**.
  - **Passageiro** é a classe responsável por construir os passageiros *default* a partir do método construtor e por encaminhar o fluxo de saída de acordo com os objetos inseridos.
  - **Topic** é a classe que compõe a topic, tendo então as funções que fazem parte da topic. Como inPass(entrar passageiros), outPass(sair passageiros) e por fim a toString(que mostra as disposições de cadeiras, sendo elas preenchidas ou não).
  - **Controller** é a classe que faz ligação entra a interação do usuário com as chamadas das funções, feitas a partir de métodos de entrada/saída e um shell(tradutor) de comandos.
  

- Oque você aprendeu?
  - Sobre métodos destrutores.
  - Classe de controle.
  - Métodos de entrada/saida e shell(tradutor).
  
- O que você ainda tem dificuldade?
  - Tive dificuldades em criar a função de sair(**out**), pois em muitas tentativas feitas a mesma apresentou bugs. Portanto, ela não está funcional.
  

- Quanto tempo levou para fazer a atividade?
  - Por volta de 6 a 7 horas, considerando o tempo que tentei fazer a função cuja tive dificuldades de maneiras diferente.

# Contato - 03

O objetivo desta prática é fazer um objeto contato telefonico, cuja, este possui um nome, um telefone, e este telefone possui um *label(identificador)*.
Pratica feita individualmente.

- Como foi feito:
  - Foram criadas três classes, a padrão de **Controller** e uma de **Contato** e outra de **Fone**. A classe Contato possui um vector de Fones. **Fone** deve validar os telefones inseridos, permitindo apenas os seguintes caracteres : {0123456789().}. E é necessário métodos para adicionar números nos contatos, assim como remover dado um id(id correspondente ao label do telefone que deseja-se remover).

- O que você aprendeu?
  - Aprendi o que é, e o porque utilizar algum método **static**.
  - Como utilizar string::find e string::npos para procurar caracteres.

- O que você ainda tem dificuldade?
  - Nessa atividade o ponto chave e maior questinonamento foi como implementar a função de validar um fone. Então durante o desenvolvimento fiz algumas pesquisas aos sites StackOverflow e learncpp e encontrei a possibilidade de utilizar find e npos para procurar caracteres.

- Quanto tempo levou para realizar a atividade?
  - De três a três horas e meia.

# Pet - Tamagotchi - 04

O objetivo desta prática é fazer jogo conhecido como *Tamagotchi* onde o jogador cuida de seu bichinho *(pet)*, brincando, banhando, dando comida e dando banho. Nosso **pet** deve possuir um nome, e seu nome deve ter uma opção de ser atualizado caso desejado.

- Como foi feito:
  - Foi criada uma classe denominada **Pet** cuja foi inicializada com seus *default* construtores e a mesma é responsável pelos métodos capazes de manipular os status do pet. Para manipular os status do pet, foram utilizados métodos **set**.

- O que você aprendeu?
  - Aprendi o que são métodos **get** e **set** e onde utiliza-los.

- O que você ainda tem dificuldade?
  - Nessa atividade não tive dificuldades em realiza-la.

- Quanto tempo levou para realizar a atividade?
  - Em torno de três horas.
  
# Agiota - 05

O objetivo desta prática é criar um programa que gerencie clientes de um agiota. Trabalho feito individualmente.

- Como foi feito: 
  - Foram criadas três classes, são elas: **Cliente, Movimentacao e Agiota**. Um agiota deve ser capaz de: possutir um capital cujo poderá emprestar, adicionar clientes, fazer emprestimos para clientes, receber pagamentos de clientes, e caso perder a paciencia com algum cliente devedor, mata-lo.
  
- O que você aprendeu?
  - Nesta prática foi necessário utilizar alguns conceitos já adquiridos anteriormente por meio de outras aulas/atividades. São estes conceitos: apagar um indice i desejado de um vector. Utilizar um vector de modo a guardar um "histórico" de dados. E ter a possibilidade de possuir mais de um cliente, diferentemente do que acontecia na atividade contato por exemplo, pois para contato tinhamos que gerenciar apenar um "cliente/contato" e para o agiota necessitamos trabalhar com vários clientes.

- O que você ainda tem dificuldade?
  - Tive um pouco de dificuldade para implementar a função de pay(pagamento) cuja tinha que encontrar o cliente corretor que fez o pagamento para por fim atualizar o valor da divida do cliente.

- Quanto tempo levou para realizar a atividade?
  - Por volta de quatro horas.

# Agiota com repositorios - 06

# Repositório I - 07

O objetivo dessa atividade é implementar um repositório por meio de **templates** capaz de adicionar, remover, mostrar objetos das classes **professor, aluno, disciplinas**, de modo que, apenas a implementação de um métodos genéricos com base em respositórios permita essa implementação.

- Como foi feito:
  - Foram criadas classes **professor, aluno, disciplina** cuja cada uma era constituida apenas de seus respectivos métodos contrutores e toString.
  - Além destas três classes, foi criada uma classe chamada repositório, qual tem os métodos de adicionar, remover, mostrar, obter elementos passados por meio de templates. Deste modo, permitindo uso deste template para qualquer uma das três classes vista acima.

- O que você aprendeu?
  - A utilização de templates e mapas.

- O que você ainda tem dificuldade?
  - Nesta atividade não tive dificuldades.

- Quanto tempo levou para realizar a atividade?
  - Um total próximo a quatro horas.