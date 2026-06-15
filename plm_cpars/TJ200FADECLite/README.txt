Como compilar os projetos em C++ no Angstrom (Linux utilizado na FPGA Cyclone V):


** PRIMEIRA BUILD DO PROJETO: **
- Copie a pasta do projeto para dentro do Angstrom, na pasta Desktop (utilizar preferencialmente FileZilla).
- Abra o VNC e conecte-se ao Angstrom.
- Acesse a pasta do projeto.
- Dentro da pasta, clique em qualquer parte branca e abra o terminal.
- No terminal faça a seguinte sequencia de comandos:

mkdir build

cd build

cmake ..

make -j4

- Após a finalização da compilação, execute o arquivo criado na pasta build.



** BUILDS POSTERIORES (REBUILD): **
- Altere o projeto no computador e envie para o Angstrom, sobrescrevendo os arquivos anteriores.
	- IMPORTANTE! Verifique se nos arquivos enviados não há nenhuma pasta "build", pois esta pasta não pode ser sobrescrita dentro do Angstrom!
- Após a finalização da cópia, abra a pasta do projeto dentro do Angstrom e acesse a pasta build.
- Dentro da pasta build, abra o terminal.
- Execute os seguintes comandos:

make clean

make -j4

- Após a finalização da compilação, execute o arquivo criado na pasta build.
