# ED--Trabalho-1--Cidades-mais-proximas

Tarefa 1: (consulta cidade)
objetivo: dado o codigo_ibge retorne as informações desta cidade
descrição: construa um tabela hash com tratamento de colisões utilizando um hash duplo para armazenar todas as cidades brasileiras do link 
https://github.com/kelvins/municipios-brasileiros/blob/main/json/municipios.json, a chave desta hash deve ser o codigo_ibge. Ao consultar um codigo_ibge seu código deverá retornar todas as informações desta cidade presente no banco de dados. Fiquem a vontade para reutilizar o código utilizado em sala nesta tarefa.

Tarefa 2 (vizinhos mais próximo de uma cidade dado o seu codigo_ibge)
objetivo:  Dado o código_ibge,  você deverá retornar o codigo_ibge das N cidades vizinhas mais próximas, onde N é um parâmetro do usuário.
descrição: Para a busca pela vizinhança construa uma kdtree utilizando uma ABB (sugestão, consulte o chatgpt sobre esta estrutura para esta tarefa). Na KDtree você deve alternar latitude e longitude.

Tarefa 3 (combinar tarefa 1 e 2).
objetivo: dado o nome de uma cidade retornar todas as informações das N cidades vizinhas mais próximas. 
descrição: crie uma outra tabela hash que dado o nome da cidade retorne o codigo_ibge. De posse do codigo_ibge utilize o código da tarefa 2 para retornar os vizinhos mais próximos e o código da tarefa 1 para retornar as informações das cidades vizinhas.
  
Entrega:
1  -  link para o código no github 
2  -  link para o youtube com um vídeo de 8 minutos com a explicação do código e a execução das três tarefas.  

Trabalho individual

Plágio entre alunos: será considerado zero tanto para quem passou quanto para quem copiou. Não repasse seu código para o seu colega em hipótese alguma. No entanto fiquem livres para discutir e explicar entre vocês ideias e possibilidades. 

Plágio da internet ou chatgpt:  não serão permitas cópias destas fontes, no entanto vocês são encorajados a utilizar o chatgpt e a internet como material de consulta.  Minha sugestão, principalmente para o caso do chatgpt, é que você olhe e entenda as ideias principais do código,  feche o código fornecido pela plataforma, e implemente de sua cabeça a funcionalidade desejada.
