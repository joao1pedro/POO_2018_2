# 01 Carro -

O objetivo desta prática é criar uma Classe denominada **Carro** que funcione como um carro. Ou seja, **carro** deve permitir a entrada e/ou saída de passageiros, abastecer e por fim andar desde que haja combustível suficiente para completar a viagem e haja alguma pessoa dentro do carro.

- Com quem você fez?
  - Trabalho feito individualmente.

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

O objetivo desta prática é simular a alocação de uma topic, cuja apresenta *n* cadeiras e *m* cadeiras preferenciais. De modo que quando algum passageiro entre na topic, se ele tiver idade de 60 anos ou mais ele é prioridade e portanto deve ser alocado em cadeiras preferenciais, essas cadeiras preferenciais são as cadeiras mais a frente do veiculo. Método de inserir passageiros foi refeito pois a versão anterior alocava os passageiros erroneamente.

- Com quem você fez?
  - Trabalho feito individualmente.

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
  - Tive dificuldades em criar a função de sair(**out**), pois em muitas tentativas feitas a mesma apresentou bugs.
  

- Quanto tempo levou para fazer a atividade?
  - Por volta de 6 a 7 horas, considerando o tempo que tentei fazer a função cuja tive dificuldades de maneiras diferente.

# Contato - 03

O objetivo desta prática é fazer um objeto contato telefonico, cuja, este possui um nome, um telefone, e este telefone possui um *label(identificador)*.

- Com quem você fez?
  - Trabalho feito individualmente.

- Como foi feito:
  - Foram criadas três classes, a padrão de **Controller** e uma de **Contato** e outra de **Fone**. A classe Contato possui um vector de Fones. **Fone** deve validar os telefones inseridos, permitindo apenas os seguintes caracteres : {0123456789().}. E é necessário métodos para adicionar números nos contatos, assim como remover dado um id(id correspondente ao label do telefone que deseja-se remover).

- O que você aprendeu?
  - Aprendi o que é, e o porque utilizar algum método **static**.
  - Como utilizar string::find e string::npos para procurar caracteres.

- O que você ainda tem dificuldade?
  - Nessa atividade o ponto chave e maior questinonamento foi como implementar a função de validar um fone. Então durante o desenvolvimento fiz algumas pesquisas aos sites StackOverflow e learncpp e encontrei a possibilidade de utilizar find e npos para procurar caracteres.

- Quanto tempo levou para realizar a atividade?
  - De três a três horas e meia.

# Banco - EXTRA - 04

O objetivo desta prática é implementar um sistema que simula a conta de um único cliente, permitindo que este cliente faça operações de saque, deposito e extrato.

- Com quem você fez?
  - Trabalho feito individualmente.

- Como foi feito?
  - A conta era criada com um número digitado pelo usuario na abertura, com os valores de saldo/divida zerados(pelo construtor).
  A classe Conta possui uma variavel chamada saldo cuja como já dito, inicia em 0. Uma operação de deposito faz com que o saldo receba o saldo anterior somado ao valor de deposito feito no momento e isso é colocado em um vector de Operações chamado extrato. Assim como, de modo semelhante, um saque modifica o valor de saldo subtraindo o valor digitado do saldo atual, isto se o valor do saque menor ou igual ao saldo total. Do mesmo modo, essa operação é adicionada ao vector extrato. Para mostrar o extrato deve-se passar por todos os valores do vector mostrando-lhe caso seja o extrato completo, e para passar por n ultimos elementos caso extratoN.

- O que você aprendeu?
  - Um pouco mais de como manipular um vector e que as impressões podem ser alteradas de acordo com um padrão desejado.

- O que você ainda tem dificuldade?
  - Tive dificuldade para encontrar o indice certo para fazer a operação de extorno.

- Quanto tempo levou pra fazer a atividade?
  - Entre 3h30 a 4 h.

# Pet - Tamagotchi - 05

O objetivo desta prática é fazer jogo conhecido como *Tamagotchi* onde o jogador cuida de seu bichinho *(pet)*, brincando, banhando, dando comida e dando banho. Nosso **pet** deve possuir um nome, e seu nome deve ter uma opção de ser atualizado caso desejado.

- Com quem você fez?
  - Trabalho feito individualmente.

- Como foi feito:
  - Foi criada uma classe denominada **Pet** cuja foi inicializada com seus *default* construtores e a mesma é responsável pelos métodos capazes de manipular os status do pet. Para manipular os status do pet, foram utilizados métodos **set**.

- O que você aprendeu?
  - Aprendi o que são métodos **get** e **set** e onde utiliza-los.

- O que você ainda tem dificuldade?
  - Nessa atividade não tive dificuldades em realiza-la.

- Quanto tempo levou para realizar a atividade?
  - Em torno de três horas.
  
# Agiota - 06

O objetivo desta prática é criar um programa que gerencie clientes de um agiota. 

- Com quem você fez?
  - Trabalho feito individualmente.

- Como foi feito: 
  - Foram criadas três classes, são elas: **Cliente, Movimentacao e Agiota**. Um agiota deve ser capaz de: possutir um capital cujo poderá emprestar, adicionar clientes, fazer emprestimos para clientes, receber pagamentos de clientes, e caso perder a paciencia com algum cliente devedor, mata-lo.
  
- O que você aprendeu?
  - Nesta prática foi necessário utilizar alguns conceitos já adquiridos anteriormente por meio de outras aulas/atividades. São estes conceitos: apagar um indice i desejado de um vector. Utilizar um vector de modo a guardar um "histórico" de dados. E ter a possibilidade de possuir mais de um cliente, diferentemente do que acontecia na atividade contato por exemplo, pois para contato tinhamos que gerenciar apenar um "cliente/contato" e para o agiota necessitamos trabalhar com vários clientes.

- O que você ainda tem dificuldade?
  - Tive um pouco de dificuldade para implementar a função de pay(pagamento) cuja tinha que encontrar o cliente corretor que fez o pagamento para por fim atualizar o valor da divida do cliente.

- Quanto tempo levou para realizar a atividade?
  - Por volta de quatro horas.

# Agiota com repositorios - 07
- O objetivo deste trabalho é refazer a atividade 06(Agiota) utilizando conceitos de repositorios/mapas. Porém, nem todos os métodos funcionam como deveriam.

- Com quem você fez?
  - Trabalho feito individualmente.

- Como foi feito:
  - Foi criado um repositorio de **coisas** permitidos atravez do uso de templates e mapas.
  - Tal repositorio por trabalhar com "coisas" pode ser usado de acordo com a nossa necessidade, seja string, int, char etc.
  - Então foram criados métodos add, rm, get, exist para trabalhar com os mapas de "coisas".

- O que você aprendeu?
  - A trabalhar um pouco com repositorios, mapas, templates.

- O que você ainda tem dificuldade?
  - A trabalhar com mapas, visto que, eu por vezes confundia um pouco o uso destes com os vectors, algo que fez com que eu tivesse muito trabalho, pois, a confusão fez com que eu tentasse reaproveitar o código da atividade anterior, alterando algumas coisas e isso acabou não sendo o melhor. Portanto, tive que assistir as aulas sobre mapas, templates novamente para prosseguir.

- Quanto tempo levou para realizar a atividade?
  - Julgo que por conta da confusão com vectors, umas 9 horas no total (incluindo revisão de video aulas).

# Repositório I - 08

O objetivo dessa atividade é implementar um repositório por meio de **templates** capaz de adicionar, remover, mostrar objetos das classes **professor, aluno, disciplinas**, de modo que, apenas a implementação de um métodos genéricos com base em respositórios permita essa implementação.

- Com quem você fez?
  - Trabalho feito individualmente.

- Como foi feito:
  - Foram criadas classes **professor, aluno, disciplina** cuja cada uma era constituida apenas de seus respectivos métodos contrutores e toString.
  - Além destas três classes, foi criada uma classe chamada repositório, qual tem os métodos de adicionar, remover, mostrar, obter elementos passados por meio de templates. Deste modo, permitindo uso deste template para qualquer uma das três classes vista acima.

- O que você aprendeu?
  - A utilização de templates e mapas.

- O que você ainda tem dificuldade?
  - Nesta atividade não tive dificuldades.

- Quanto tempo levou para realizar a atividade?
  - Um total próximo a quatro horas.

# Serviço de anotações - 09

O Objetivo deste trabalho é proporcionar um sistema simples cuja permita login, logout, atualização de senha e escrever anotações dado um título e texto.

- Com quem você fez?
  - Trabalho feito individualmente.

- Como foi feito:
  - Essa prática tem o objetivo de criar um serviço de anotações, cujo são introduzidas anotações de título único (única chave) seguido de algum texto. Mas há um porém, para poder fazer a anotação o usuário deve estar logado no sistema, para tal, estudamos o conceito de como funciona um gerenciador de login capaz de permitir login e logout de um sistema.

- O que você aprendeu?
  - Como funciona um gerenciador de login com base em usuário e senha. 

- O que você ainda tem dificuldade?
  - Tive dificuldade para retornar um usuário que existe cadastrado no vector e para separar o gerenciador de login em uma classe especifica para tal função, visto que deixei o mesmo implementado na classe Controller juntamente ao shell(interpretador de comandos).

- Quanto tempo levou para realizar a atividade?
  - Algumas horas, creio que 3h.

# Cálculo de salário - 10
O objetivo deste exercicio é fazer um sistema capaz de cadastrar funcionarios que podem ter as seguintes classes: "Professor, STA e terceirizado". Os funcionarios possuem um nome **key** que é um identificador único. Ao serem cadastrados os funcionarios tem seu salário calculado de acordo com os atributos necessários para tal, podendo ter diárias especificas para cada funcionário.

- Com quem você fez?
  - Trabalho feito individualmente.

- Como foi feito:
  - Foi necessário a utilização de repositórios (templates) para cadastrar os funcionários e seus respectivos tipos.
  - Foi utilizado o conceito de herança, polimorfismo e métodos abstratos(virtuais) para tratar da classe mãe **Funcionario** e suas respectivas filhas **Professor, STA, Terceirizado**.


- O que você aprendeu?
  - A utilizar conceitos de herança, polimorfismo e classes abstratas.

- O que você ainda tem dificuldade?
  - Tive dificuldades para fazer o método responsável por atribuir bonus a todos os funcionários, visto que, não consegui encontrar uma forma de passar por todos os funcionários do repositório sem acessa-los pela **key**(identificador unico) de cada um. Mesmo sabendo o tanto de funcionários que tinham no repositorio a partir da função size().

- Quanto tempo levou para realizar a atividade?
  - Entre 6 a 7 horas em dias alternados.

# Trem - 11
- Escrever
