# MPI

Este respositório apresenta os códigos fontes utilizados no livro de 
Programação Paralela - Editora Casa do Código - 2022. Adicionalmente 
apresentamos um texto de apoio para a preparação do ambiente de 
execução.

## Preparação do ambiente de execução MPI

Apresentamos aqui um breve roteiro sobre a instalação e configuração da
biblioteca MPI, assim como executar um programa MPI em algumas
distribuições de sistemas operacionais Posix.

### Introdução 

Primeiro devemos considerar que há várias implementações disponíveis
para o MPI, algumas gratuitas e outras comerciais. O processador e a
rede de interconexão utilizados pelo sistema onde as aplicações serão
executadas são alguns dos fatores a serem considerados na escolha da
distribuição adequada de MPI. Eventualmente, algumas distribuições
suportam mais de um tipo de processador ou de interface de rede, o que
lhes confere uma possibilidade maior de adequação às características do
seu ambiente.

É importante observar que a arquitetura dos processadores muda de
geração para geração, com a inclusão de novas instruções e facilidades.
Uma tendência muito comum tem sido a melhoria das capacidade de
processamento vetorial do processadores, o que tem grande impacto no
desempenho final das aplicações científicas.

Alguns compiladores comerciais, como o Intel e PGI, podem gerar código
otimizado para diferentes arquiteturas de processadores em um único
executável, aliviando a necessidade de geração de códigos binários
separados para cada tipo de processador. O compilador de código aberto
GNU só tem suporte para essa facilidade nas versões mais recentes. A
seguir algumas das distribuições mais importantes:

-   OpenMPI - Mantida por um conjunto de diversos parceiros da área
    acadêmica, de pesquisa e da indústria, incluindo AMD, Bull, Cisco
    Systems, Centro de Computação de Alto Desempenho de Stuttgart
    (HLRS), IBM, Intel, Laboratório Nacional de Los Alamos e NVIDIA.
    Disponível em <https://www.open-mpi.org/>

-   MPICH - Mantida também por um conjunto de parceiros da área
    acadêmica, de pesquisa e da indústria. Tem como alvo sistemas de
    alto desempenho e suporta diversos compiladores, tais como GNU, LLVM
    Clang, Intel, PGI e Sun Studio. Disponível em
    <http://www.mpich.org/>

-   MVAPICH2 - É uma implementação derivada da MPICH e mantida pela
    Universidade Estadual de Ohio voltada para aplicações de alto
    desempenho com uso de redes de interconexão tais como
    OpenFabrics-IB, Omni-Path, OpenFabrics-iWARP, PSM e TCP/IP.
    Disponível em <http://mvapich.cse.ohio-state.edu/>

-   Intel® MPI Library - uma biblioteca de troca de mensagens que
    implementa a especificação MPICH de código aberto. Mantida e
    distribuída pela Intel. Possui uma versão gratuita para estudantes,
    acadêmicos e pesquisadores. Disponível em
    <https://software.intel.com/en-us/qualify-for-free-software>

O uso de programas paralelos adiciona um fator de complexidade relativo
ao tipo de rede de interconexão utilizada pelo sistema de computação no
qual o programa paralelo MPI vai ser executado. A maioria das
implementações atuais do MPI inclui suporte para diversos tipos de rede
em único programa executável, de modo que ele possa ser executado com
diferentes tipos de rede de interconexão sem necessidade de
recompilação.

Dependendo do seu equipamento, de sua aplicação e dos recursos
disponíveis, uma implementação pode ser melhor do que a outra.
Essas distribuições evoluem ao longo do tempo mas, no momento da redação
deste livro, as características a seguir podem ser destacadas.

O OpenMPI é bastante flexível em termos de plataformas de *hardware*,
com suporte para Infiniband, mas o desempenho global é ligeiramente
inferior ao de outras implementações como Intel MPI e MVAPICH2. O
OpenMPI também suporta a rede Cray Gemini, mas não é uma implementação
oficialmente suportada pela Cray.

O MPICH é uma implementação de referência, sendo considerada uma das
implementações mais populares do padrão MPI, servindo de base para uma
série de implementações derivadas como IBM MPI, Cray MPI, Intel MPI e
MVAPICH, entre outras. Contudo, o seu suporte para InfiniBand é
precário, ao contrário do OpenMPI. Mas suas variantes como Intel MPI e o
MVAPICH2 possuem um suporte bastante eficiente para InfiniBand. Se
considerarmos o conjunto da MPICH e suas variantes, o suporte de rede é
extremamente variado, incluindo tanto o InfiniBand e redes de
interconexão proprietárias como Cray Seastar, Gemini e Áries, como
o IBM Blue Gene (/L, /P e /Q).

O MVAPICH2 é otimizado para InfiniBand, mas ele não tem uma boa
afinidade entre processos e cores em ambientes com múltiplas *threads*.

O Intel MPI tem bom desempenho e bastante flexibilidade de uso, quanto
aos tipos de processadores e redes suportadas, mas é um produto
comercial que requer a aquisição de uma licença de uso. Além da
Microsoft, é a única implementação MPI com suporte para o sistema
operacional Windows.

Em um eixo ortogonal ao suporte da plataforma de *hardware*, encontramos
a cobertura do padrão MPI. Nesse sentido, a implementação MPICH é de
longe muito superior. O MPICH foi a primeira implementação a suportar
cada lançamento do padrão MPI, desde a versão MPI-1 até a MPI-3. O
OpenMPI só recentemente suporta a versão MPI-3 e ainda assim
parcialmente (não tem suporte para o formato "external32" do MPI I/O,
por exemplo) e apresenta problemas em algumas plataformas. Tanto o
OpenMPI como o MPICH possuem suporte completo para o
MPI_THREAD_MULTIPLE, ou seja, se o processo é "multithreaded", múltiplas
*threads* podem usar a biblioteca MPI sem restrições.

Finalmente, em termos de gerenciamento de processos, onde o OpenMPI era
bem melhor há algum tempo atrás, agora o novo gerenciador de processos
do MPICH, o Hydra, é tão bom e tem a mesma usabilidade e facilidades que
o ORTE, do OpenMPI. O velho gerenciado do MPICH, chamado MPD, era
difícil de usar e sem muitas opções, mas foi tornado obsoleto já há
alguns anos.

Maiores informações sobre o OpenMPI e MPICH podem ser obtidas em
<https://github.com/open-mpi/ompi/blob/master/README.md> e
<https://www.mpich.org/documentation/guides/>, respectivamente.

### Instalação 

Vamos considerar como instalar e configurar as duas
distribuições mais importantes disponíveis como software de código
aberto e gratuitas: OpenMPI e MPICH. Felizmente a maioria das
distribuições Linux já conta pacotes disponíveis para instalação dessas
versões, o que torna muito mais fácil esta tarefa.

#### Fedora, CentOS e similares 

Basicamente, os diversos tipos de implementação MPI podem ser instalados
diretamente a partir do repositório:

-   **OpenMPI**

    ``` {}
    $ sudo dnf install openmpi
    $ sudo dnf install openmpi-devel
    ```

-   **MPICH**

    ``` {}
    $ sudo dnf install mpich
    $ sudo dnf install mpich-devel
    ```

#### Ubuntu, Debian e similares

-   **OpenMPI**

    Basicamente, instalar o OpenMPI do repositório:

    ``` {}
    $ sudo apt-get install openmpi-bin
    $ sudo apt-get install openmpi-doc
    $ sudo apt-get install libopenmpi-dev
    ```

-   **MPICH**

    Instale o pacote MPICH diretamente do repositório:

    ``` {}
    $ sudo apt-get install mpich
    $ sudo apt-get install mpich-doc
    $ sudo apt-get install libmpich-devel
    ```

#### MacOS 

-   **OpenMPI**

    A instalação automatizada do OpenMPI é possível no MacOS com a
    instalação do programa *homebrew*, no endereço <https://brew.sh/>,
    com o seguinte comando:

    ``` {}
    $ /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
    ```

    E então digitar o seguinte comando:

    ``` {}
    $ brew install open-mpi
    ```

-   **MPICH**

    A instalação automatizada do MPICH é possível no MacOS com a
    instalação do programa *homebrew*, no endereço <https://brew.sh/>,
    com o seguinte comando:

    ``` {}
    $ /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
    ```

    E então digitar o seguinte comando:

    ``` {}
    $ brew install mpich
    ```

#### Windows

No Windows, a opção preferencial é usar o emulador de terminal Cygwin ou o Windows Subsystem 
para Linux (WSL) para Windows 10. Ambos fornecem uma interface semelhante à maioria dos clusters HPC.

Se você decidir usar o Cygwin, precisará instalar alguns pacotes usando o instalador do Cygwin. 
Se você já tem o Cygwin instalado, você deve executar o instalador e certificar-se de que os 
seguintes pacotes estejam selecionados:

    - gcc-core e gcc-fortran
    - openmpi, libopenmpi40, libopenmpihf08_40, libopenmpiusef08_40, openmpi-devel e openmpi-devel.
    - zlib e zlib-devel
    - make e cmake
    - git
    - vim ou seu editor de texto preferido

Você pode verificar se funciona compilando qualquer programa C ou Fortran usando o compilador *mpicc* ou *mpifort*.

No Windows, se você usar o Visual Studio, poderá instalar o Microsoft MPI. O download inclui dois arquivos, 
*msmpisetup.exe* e *msmpisdk.msi*. Baixe e execute os dois instaladores. Siga estas instruções para criar um projeto 
com o compilador e a biblioteca MPI.

### Compilação 

Para compilar um arquivo fonte prog.c, digite:

``` {}
$ mpicc -o prog prog.c
```

Para compilar um arquivo em Fortran, os seguintes comandos são
possíveis:

``` {}
$ mpif77 -o prog prog.f
$ mpif90 -o prog prog.f90
```

### Configurando o SSH 

Para a execução em ambientes com um pequeno número de máquinas
conectadas via rede, é importante configurar o ambiente para que não
seja necessário o uso de senhas cada vez que executarmos um comando em
outra máquina. Para isso, deve-se criar e configurar o uso de chaves SSH
para todas as máquinas da rede. Neste exemplo, assumimos que existem 2
máquinas nomeadas como *maquina1* e *maquina2*, e um nome de usuário
*gabriel*.

Primeiro criamos o diretório \$HOME/.ssh com o comando:

``` {}
maquina1:~$ mkdir $HOME/.ssh
```

E em seguida geramos uma chave púbica e uma chave privada com o comando:

``` {}
maquina1:~$ ssh-keygen -t rsa -b 4096 -C "gabriel@exemplo.edu"
```

Pressione a tecla "Entre" para responder às perguntas seguintes com o
padrão.

``` {}
Enter file in which to save the key (/home/gabriel/.ssh/id_rsa): [Press enter]
Enter passphrase (empty for no passphrase): [Type a passphrase]
Enter same passphrase again: [Type passphrase again]
Your identification has been saved in /home/gabriel/.ssh/id_rsa.
Your public key has been saved in /home/gabriel/.ssh/id_rsa.pub.
The key fingerprint is:
01:0f:f4:3b:ca:85:d6:17:a1:7d:f0:68:9d:f0:a2:db Seu_email@exemplo.edu
```

Copie agora a chave pública, $id\_rsa.pub$, para o arquivo
$authorized\_keys$ de modo a permitir o acesso a essa máquina.

``` {}
maquina1:~$ cd ~/.ssh
maquina1:~/.ssh$ cat id_rsa.pub >> authorized_keys
```

Na máquina 2, deve ser criado também um diretório \midtilde{~}$/.ssh$, novamente
com o comando:

``` {}
maquina2:~$ mkdir ~/.ssh
```

Agora, você deve enviar a chave privada, $id\_rsa$, e a chave pública
$id\_rsa.pub$, da máquina 1 para máquina 2, usando o comando *scp* para
isso:

``` {}
maquina1:~$ scp ~/.ssh/id_rsa gabriel@maquina2:~/.ssh/
maquina1:~$ scp ~/.ssh/id_rsa.pub gabriel@maquina2:~/.ssh/
```

Agora, copie o arquivo $id\_rsa.pub$ para o arquivo $authorized\_keys$,
de modo que a máquina 1 possa fazer acesso à maquina 2 sem uso de senha:

``` {}
maquina2:~$ cd ~/.ssh
maquina2:~/.ssh$ cat id_rsa.pub >> authorized_keys
```

#### Executando um programa 

Para executar o programa, digamos, com 4 processos, devemos copiar o
executável para o seu diretório de trabalho e digitar:

``` {}
$ mipexec -n 4 prog
```

O comando $mpiexec$ permite opções mais elaboradas:

``` {}
$ mpiexec -n 1 -host paraty : -n 19 prog
```

Dispara o processo com ranque 0 na máquina "paraty" e outros 19
processos divididos entre as demais máquinas. Para executar através de
múltiplas máquinas:

``` {}
$ mpiexec --hostfile hostfile -n 4 prog
```

Onde *hostfile* é um arquivo contendo o nome ou IP das máquinas onde
deseja executar a aplicação, por exemplo:

``` {}
paraty:2
charitas:3
barra:2
```

Onde o número ao lado do nome de cada máquina indica o total de
processos a serem executados. Os comentários neste arquivo são
precedidos com o caractere "\#". Para saber mais opções, digite:

``` {}
$ mpiexec --help
```

#### Gerenciador de Recursos 

Gerenciadores de recursos como SGE, PBS, SLURM são comuns em muitos
*clusters* gerenciados. Nesse caso, o MPI detecta a sua existência e
interage automaticamente com eles. No caso do PBS, você pode criar um
arquivo *script* como a seguir:

``` {}
# declarar um nome para esta tarefa como sample_job
#PBS -N my_parallel_job
# solicita que a tarefa seja executada na fila com nome parallel
#PBS -q parallel
# solicita um total de 4 processadores para esta tarefa (2 nós e 2 processadores por nó)
#PBS -l nodes=2:ppn=2
# solicita 4 horas de tempo de processador
#PBS -l cput=0:04:00
# combina a saída padrão e a saída de erro do PBS
#PBS -j oe
# envia um email quando a tarefa inicia e quando ela termina e aborta
#PBS -m bea
# especifica o seu endereço de e-mail
#PBS -M John.Smith@dartmouth.edu
#muda para o diretório onde a sua tarefa vai ser submetida
cd $PBS_O_WORKDIR
#inclui o caminho completo com o nome do programa MPI a ser executado
mpirun -machinefile $PBS_NODEFILE -np 4 /path_to_executable/program_name
exit 0
```

As tarefas podem ser submetidas como:

``` {}
$ qsub -l nodes=2:ppn=2 teste.sub
```

O **mpiexec** vai saber automaticamente da existência do PBS no sistema
e pergunta o número total de processadores alocados (4 no caso), e quais
nós foram alocados para o processamento da tarefa. O uso é similar para
outros gerenciadores de recurso. Mais opções para o comando **qsub**
podem ser encontradas em <https://www.jlab.org/hpc/PBS/qsub.html>.
