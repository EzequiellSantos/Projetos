# Estrutura uSolutions

_Estrutura de projeto._

---

## Visão geral

Reunir e conceituar a proposta de acordo com as necessidades, pode ser incluído bem mais funcionalidades na medida que é avançado

## Pontos Principais

- Ambiente
- Funcionalidades
- Melhorias e Sustentações

- - - 

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
 >  - Pedidos
 >  - Entregas
 >  - Produtos
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

## 2 Funcionalidades

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
````
- code
- descrição
- categoria
- localização
- qty
- qty minima
- preço
- 
````

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

````
- nome cliente
- endereço 
(NÚMERO, RUA, BAIRRO, CIDADE, ESTADO se for diferente)
- Contato de um responsável pela compra do produto (sujeito a mensagens automáticas)
- email (opcional)
- data de nascimento
- a combinar
````

Dados da venda:

Model:
````
- Produto
- data
- associação ao cliente
- quantidade
- forma de pagamento
- (ternarios: parcelas)
- Prioridade de entrega
````

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

### 3 Melhorias e Sustentações
- Emissão de notas fiscais caso necessário para a venda de produtos






_Última atualização: AAAA-MM-DD_