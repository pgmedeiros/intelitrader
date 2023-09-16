# Desafio 4 - Crie uma aplicação que recebe um arquivo de texto e monta um ranking de quantidade dos caracteres contidos

Nesse desafio, optei por criar uma solução flexível, que fosse capaz de analisar diversos tipos de caracteres além dos contidos na tabela ASCII. 
Para isso, construí uma árvore avl onde são salvos todos os caracteres lidos do texto e quantidade que cada um foi encontrado, como a árvore mantém
o seu balanceamento, o tempo de inserção sem mantém constante em O(log n). Depois, os caracteres são transferidos para um array com o exato tamanho de nós da árvore, esse processo leva O(n). 
Depois, é criado uma estrutura de Heap Máximo nesse array, utilizando o algoritmo Heapify, que possui complexidadade O(n). Por fim, a função getMaximo do Heap me permite pegar cada caractere em tempo O(1). 
Dessa forma, o algoritmo criado é capaz de resolver o problema, no pior caso, em O(n log n). 

Uma outra alternativa de projeto seria a criação de uma hash table, onde os indícies seriam utilizados como o valor do caractere na tabela, assim, tendo tempo de busca e atualização de valores O(1). Porém, essa solução limitaria o algoritmo 
a tabelas de caracteres pequenas em prol de performance. Pois, ela precisa criar um array do tamanho do número de caracteres que podem aparecer no arquivo de texto, caso fosse necessário lidar com a tabela Unicode, isso iria necessitar de um grande espaço de memória que pode ser subutilizado. 

