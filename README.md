### Desafio 3 - Crie uma aplicação que codifica/decodifica arquivos para Base64

Nesse desafio, optei por limitar o escopo do problema aos caracteres da tabela ASCII. Porém, podendo ser alterado para abarcar novas tabelas de códigos, tanto adicionando novos comportamentos as funções de junção e separação de bits quanto as funções de leitura e escrita do C.

Três funções são comuns no encode e decode. São elas: createSingleBinary, separateBitsToSomeSize e write. As funções createSingleBinary e separateBitsToSomeSize são dependentes do tamanho de cada "palavra" do array de bits, ou seja, é constante a 3 na decodificação e constante a 4 na codificação. Portanto, ambos possuem complexidade O(1). Já a função write, será repetida conforme o tamanho do arquivo, portanto, possui complexidade O(n).

A função convertArrayToBase64Index(decode) é constante para o tamanho da "palavra", portanto tem complexidade O(1) e o mesmo acontece para a função base64IndexToValue(encode).

Portanto, o algoritmo é capaz de resolver o problema, no pior caso, com complexidade O(n).

### Desafio 4 - Crie uma aplicação que recebe um arquivo de texto e monta um ranking de quantidade dos caracteres contidos

Nesse desafio, em oposição ao anterior, optei por criar uma solução com uma estrutura flexível, que fosse capaz de analisar diversos tipos de caracteres além dos contidos na tabela ASCII. Bastando, para isso, trocar as funções de leitura e escrita do C.

Para isso, construí uma Árvore AVL onde são salvos todos os caracteres lidos do texto e a quantidade que cada um foi encontrado. Como a árvore mantém o seu balanceamento, o tempo de inserção se mantém constante em O(log n). 

Depois, os caracteres são transferidos para um array com o exato tamanho de nós da árvore, esse processo leva O(n). 

Após isso, é criado uma estrutura de Heap Máximo nesse array, utilizando o algoritmo Heapify, que possui complexidadade O(n). Por fim, a função getMaximo do Heap me permite pegar cada caractere em tempo O(1). 

Dessa forma, o algoritmo criado é capaz de resolver o problema, no pior caso, com complexidade O(n log n). 

Uma outra alternativa de projeto seria a criação de uma Hash Table, onde os indíces seriam utilizados como o valor do caractere na tabela, assim, tendo tempo de busca e atualização de valores O(1). Porém, essa solução limitaria o algoritmo a tabelas de caracteres pequenas em prol da performance. Pois, ela precisa criar um array do tamanho do número de caracteres que podem aparecer no arquivo de texto, caso fosse necessário lidar com a tabela Unicode, isso iria necessitar de um grande espaço de memória que poderia ser subutilizado. 

