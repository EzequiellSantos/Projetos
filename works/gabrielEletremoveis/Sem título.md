# Estrutura uSolutions

_Estrutura de projeto._

---

## Visão geral

Reunir e conceituar a proposta de acordo com as necessidades, pode ser incluído bem mais funcionalidades na medida que é avançado

## Pontos Principais

- Ambiente
- Proposta de Funcionalidades
- Fluxo
- Melhorias e Sustentações

---

## 1 Tecnologias

- React
- Express
- Node.js
- Mongo DB Atlas

### 1.1 Hospedagem

- vercel
- compra de domínio (futuramente)

### 1.2 Frontend Interface

- Inventário
  > - Pedidos
  > - Entregas
  > - Produtos
- Comercial
  > - Vendas
  > - Relatórios
  > - Catálogo
  > -
- clientes
- Financeiro
- Administração

Bases para o design:

- mobile first
- Responsivo

Garantir que seja acessivel tanto para celulares e PCs
interface moderna com design intuitivo a nivel empresárial, garantindo uma boa visualização por partes dos funcionarios e gerência

trazendo em evidência a performance antes de qualquer coisa

### 1.2.1 Cores

Cores modernas, para que traga conceitos implicitos de inovação para gerencia

### 1.3 Backend

sincronização: permitir a gravação de dados locais e realizar a conexão enviar dados

## 2 Proposta de Funcionalidades

Funcionalidades Voltadas para gerência

- Gerencial

### 2.1 Gerencial

As etapas do gerencial irá do chão do almox até o nivel de clientes, passando pelos setores de:

- almox
- comercial
- financeiro

Especificamente nessa ordem

### 2.1.1 Almox

Responsável por cadastrar, alterar e ter o controle sob todas as categorias, deixando que a autonomia de informações circulem de maneira segura e fiel pelo restante da aplicação.

Garantir o controle de embarques para entregas com mais autonomia e otimização de recursos.

Pontos a destacar:

- atualização constante para garantir um catálogo fiel
- quantidade de produtos
- descrição clara
- identificação em cada produto

Funcionalidades

---

- organização na localização do produto para realocações e buscas para entregas
- controle de entrada e saída de produtos
- relatorio de movimentos de produtos

Controle de estoque, baixa automaticamente de acorod co a venda feitas por vendedores, atualização de status de estoque e como consequência quantidade real no catálogo atualizada.

Almox terá uma funcionalidades para encaminhamento de entregas, produtos separados por lugares para facilitar a organização

_obs: definir prioridade de locais para facilitar o desembarque e economia de recursos_

_obs2: desenhar fluxo de entradas e saidas para facilitar geração de etiquetas de produtos_

Model

```
- code
- descrição
- categoria
- localização
- qty
- qty minima
- preço
-
```

### 2.1.2 Comercial

Responsável pelo giro da empresa, destacando a coleta real e fiel de dados de clientes e vendedores, bem como entregar um catálogo confiável e real de produtos disponibilizados para a venda, garantindo uma confiança nos dados do cliente para futuras consultas.

Verificações de clientes ao realizar venda, venda nao autorizada a clientes RUINS

sistema nao permite o cadastro no nome do cliente base no histórico de cliente ruim

---

Funcionalidades

Geração de relatórios:

- relatorios mensais de vendas e clientes:
  vendas obtidas, clientes novos, clientes renovando compras
- relatórios semanais de vendas e clientes
- relatorios semanais e mensais e anuais de vendas por vendendores
- faturamentos obtidos por vendendores, semanais, mensais e anuais (nivel gerencial)

Consulta de Catálogo Online:

- através da internet
- realizar armazenamento em cache local para visualizar em areas offlines
  (sujeito a alterações em tempos reais e sincronização ao voltar conexão)

dados a coletarem do cliente:

Model:

```
- nome cliente
- endereço
(NÚMERO, RUA, BAIRRO, CIDADE, ESTADO se for diferente)
- Contato de um responsável pela compra do produto (sujeito a mensagens automáticas)
- email (opcional)
- data de nascimento
- a combinar
```

Dados da venda:

Model:

```
- Produto
- data
- associação ao cliente
- quantidade
- forma de pagamento
- (ternarios: parcelas)
- Prioridade de entrega
```

_obs: quem irá fazxer o cadastro completo da venda, desde o produto até o _

### 2.1.3 Financeiro

Setor com inovações fortes, com exibição de realatórios para planejamentos futuros, garantir histórico de clientes para que seja consultado.

---

Funcionalidades

- permitir impressão / consultas de dados com bse nas vendas realizadas sem precisar realizar preenchimento manual de acordo com as vendas realizadas
- relatorios de clientes BONS MEDIOS e RUINS
- cobranças automaticas
- geração de relatorios de históricos de cobranças
- relatorios - semanais, mensais e anuais
- historicos de pagamentos
- negociações com dividas anteriores _extrair da base de dados clientes com atrasos_
- relatorios de contas em abertas, com nível de criticidades de contas para definir priorização de negociações
-

## 3 Fluxo

### 3.1 Gestão

Cadastra os vendedores

Cadastra os cobradores

Cadastra outros empresas parceiras (opcional)

### 3.2 Estoque

Cadastra os produtos e gerencia as quantidadese
Quantidade e descrições usadas nas vendas e no catálogo

> quando realizar a compra, o produto vai ser retirado do estoque, no sistema, mas fisicamente ele ainda vai estar em estoque.... logo qualquer movimentaçao feita no estoque nao pode ser realizar apenas por "vista" e sim por leitura de codigo pois pode ter 1 unico produto restante e o mesmo ja esta vendidod (situação aplicada para revenda para outra empresa)

Entrega dos pedidos

    aba de cadastro de embarque, com suporte apra leitura de QRCODE no input, para ler os produtos que foram para entrega e designar de qual vendedor é aqueles produtos

futurua implementação: Ao constar que o produto embarcou, logo atualizar o estatus do produto na vcnda e nao no estoque, constar coo enviando para embarque

junto com o produto vaiser entregue o carnê fisico do cliente com as informações para paagmento e informações da venda (_responsável financeiro_)

    suporte para impressão do carnê do cliente, para que o carnê venha com as parcelas da venda definidas na hora do cadastro completo da venda, com, Qrcode manipulado para chavepix e valor da parcela para o cliente realizar o pagamento opcional da venda.

### 3.3 Comercial

PRIMEIRA FORMA DE VENDA (B2C)

_O vendedor:_

Realiza a consulta do catálogo

Consulta de historico de cliente

    consulta nos dados que vem do banco de dados

Após a cosulta realiza o pré Cadastro da ficha no sistema com as infornações basica para cadastro da ficha do cliente

    Permitir a consulta e criação tanto online e offline SE CADASTRADO NO BANCO a consulta do cliente

    nome, nome conhecido, data d enasc, cpf, rg, rua, n°, bairro, cidade, referencia,referencia, fone, celular, isCliente, isCasaPropria, onde trabalçha, mfone, mnae, conhecido, esposo, conhecido, qual o vendedor ???????

_A VENDA SÒ È FECHADA SE O CLIENTE FOR CONFIÁVEL_

> O vendedor irá escolher qual também foi o produto, parcela ??????

Logo em seguida sera mostrado no sistemas uma parte com a lista de pre cadastros de cada vendedores

_O assistente do escritório:_

> Realiza o cadastro completo do clientente com a venda????

> _de onde ele vai pega essa informação? se o intuito é deixar a ficha online e apos completar realizar a impressão?_

    Cadastro do produto vendido (codigo / descrição), com o metodo de pagamento e também a quantidade de parcela a ser cobrada, qual o dia da cobrança que o cliente escolheu (10, 20, 30) ect..

    È verificado se teve a entrada da compra, cadastrado data de compra, vencimento, total das parcelas, plano

Quando a venda é feita, o produto no estoque é dado baixa, e logo em seguida o catálogo também é atualziado a quantidade para ser integrado.

SEGUNDA FORMA DE VENDA (B2B)

revenda de eletrodoméstiscos entre outros crediários, sendo cadatrado a venda normalmente, porem em vez de cliente, é outra empresa

> Qual a frequencia de acontecimento

### 3.4 Financeiro

verifica clientes que estão com as parcelas em atrasos e terao uma visualização d econtrole de cobranças por dias, e também no gera

    Ver as cobranças acumuladas que não foram cobradas da cobrança anterior

gerar realtorio de cobranças por localidade e designar o cobrador para cada cobrança

imprimir as fichas de cobranças com os dados ja preenchidos para que o cobrador possa leva-las para o cliente assinar

Quando o cobrador retornar, vai ser coletados as ifnormaçõe de pagamento, e adiconado no sistema o valor que foi recebido do cliente especifico e qual a parcela referente ao pagamento

    Por parte do Eschema de parcelas, saber se foi pag em atraso ou não, e logo atualizar o idicador do cliente, se ele é bom medio ou ruim

essas informaçõe serão registras e logo servirão de base para gerar os seguintes relatórios:

     - quanto cada cobrador está cobrando de pelos clientes de cada vendedor
     - Saber quanto e a porcentagem do foi cobrado e do que ta faltando de cada semana de cobrança (semana do dia 10, semana do dia 20, semana do dia 30)
     - quantos clientes tem as faturas em abertos
     - alerttar os clientes sobre a proximidade de vencimento da parcela
     - alertar para a gestao da empresa quais os clientes tem suas faturas em abertas
     - alertar quais os clientes bons, medios e ruins
     - Prestação de contas, com os cobradores tantos recebidos, por datas, vendedores e

> - Bom
>   pagou tudo
>   sem atraso (ou dentro do vencimento)
>   ou pagamento à vista (pix/cartão)
> - Mediano
>   pagou tudo
>   mas teve atraso
> - Ruim
>   tem parcelas em aberto
>   ou deixou atrasar mais de X (ex: 2)

> Guardam recibos ou comprovantes?

## 4 Melhorias e Sustentações

- Emissão de notas fiscais caso necessário para a venda de produtos
- monitoramento de transações no bradesco
- - ### COM PIX DINAMICO
  - Opção 1 – Pix Dinâmico (RECOMENDADO)
    
    Esse é o melhor caminho hoje no Brasil.
    
    Como funciona:

    Seu sistema gera a cobrança Pix via API do Bradesco
    
    O Pix já nasce com:

    valor
    
    identificador único (txid)
    
    vínculo com o cliente/parcela


    O cliente paga
    
    O Bradesco notifica sua aplicação
    
    Você dá baixa automaticamente na parcela correta

  - Opção 2 – Boleto registrado (também funciona)

    Cada parcela = um boleto
    
    O boleto tem nosso número
    
    O banco informa liquidação
    
    Baixa automática
    
    Funciona bem, mas é:
    
    mais lento
    
    menos moderno
    
    depende de convênio ativo
- - ### COM BOLETO DINAMICO
    Seu sistema
    
       ↓
    
    API Bradesco — gera boleto
    
       ↓
    
    Cliente paga
    
       ↓
    
    Bradesco confirma pagamento
    
       ↓
    
    API/Webhook/Retorno CNAB
    
       ↓
    
    Você dá baixa na parcela correta
    
- - ### As principais funcionalidades da API de Cobrança do Bradesco incluem:

      Emissão de boletos (à vista ou parcelado)
  
      Consulta de boletos
  
      Consulta de liquidação
  
      Código de barras + linha digitável
  
      Boleto híbrido (boleto + Pix)
  
      Integração com extrato
    
- consulta no serasa integrado ao site
- controle de rotas de embarques

  _Última atualização: 2026-04-24_
