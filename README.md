# Oven Share

## Introdução

A programação concorrente e a sincronização
entre processos são desafios importantes no
desenvolvimento de sistemas. Neste trabalho,
iremos explorar a programação concorrente
utilizando threads POSIX (pthreads) em
linguagem C. O objetivo é simular a utilização
compartilhada de um forno microondas por três
estudantes em uma república. Foram estabelecidas
regras de prioridade, onde o sênior tem prioridade
sobre o veterano, que tem prioridade sobre o
calouro. Além disso, cada estudante recebe a visita
de outro estudante de mesma prioridade. Utilizaremos
mutexes e variáveis de condição para garantir a correta
sincronização e priorização dos estudantes no uso do forno.

No problema proposto, a primeira etapa consiste na
sincronização entre os estudantes. Se o forno estiver
livre, o estudante que chegar primeiro na cozinha poderá
utilizá-lo. Caso contrário, o estudante terá que aguardar
até que o forno seja desocupado. Pessoas de maior
prioridade têm preferência sobre as de menor prioridade.
A implementação envolverá a utilização de mutexes para
garantir o acesso exclusivo ao forno e variáveis de
condição para gerenciar a ordem de utilização.

Ao desenvolver essa solução, iremos aprofundar nosso
conhecimento em programação concorrente, sincronização
de processos e utilização de recursos compartilhados
de forma segura. Será necessário lidar com situações de
inanição e deadlock, e iremos explorar as funcionalidades
das threads POSIX (pthreads) para garantir a correta
sincronização e priorização dos estudantes no uso do forno
microondas.

## Requisitos do Sistema

Para compilar e executar o programa,
o sistema deve atender aos seguintes requisitos:

* Sistema Operacional Unix/Linux.
* Compilador C compatível com a biblioteca GNU libc6-dev.
* Make para automatizar a compilação/execução do programa.
* Acesso aos recursos posix.

## Instalação

Para obter o código-fonte mais recente do Oven-Share,
você pode clonar o repositório Git. Siga as etapas abaixo
para realizar uma clonagem:

1. Abra o termininal
2. Navegue até o diretório onde você deseja clonar o projeto.

   ```cd /caminho/para/sua/pasta/```
3. Agora, clone o repositório Git executando o seguinte comando:

   ```git clone https://github.com/Akles-Camoleze/oven-share.git ```

4. Aguarde até que o Git termine de clonar o repositório.
   Você verá mensagens indicando o progresso da clonagem.

Após concluir essas etapas, você terá o código-fonte do Oven Share
clonado no seu diretório local. Agora você pode aceitar com as etapas
de configuração e compilação conforme descrito na documentação.

## Execução

Após seguir os passos de [instalação](#instalação), o programa pode ser executado com o comando:

```bash
make ./oven-share
```

## Funcionalidades

Foi implementado apenas o primeiro módulo do trabalho. Onde, o forno é acessado de forma mutuamente exclusiva e os
estudantes entram na fila conforme a sua prioridade (Sênior, Veterano e Calouro). Além disso, para evitar inanição
daqueles que possuem menor prioridade, estes são beneficiados por um processo de envelhecimento. 