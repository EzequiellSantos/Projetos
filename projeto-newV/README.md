# 🎮 Bomberman CLI - Projeto de Estruturas de Dados

Um jogo **Bomberman** desenvolvido em C com interface **NCurses** que implementa uma **Árvore B+** para armazenamento e visualização de estatísticas dos jogadores.

## 📋 Resumo do Projeto

Este projeto combina um jogo multiplayer interativo com um sistema avançado de armazenamento de dados usando Árvore B+. Dois jogadores competem em um mapa dinâmico, plantando bombas e coletando itens, enquanto suas estatísticas são automaticamente armazenadas e organizadas em uma estrutura de dados eficiente para consulta e visualização.

## ✨ Funcionalidades Principais

### 🎮 Sistema de Jogo
- **Multiplayer local**: 2 jogadores com controles independentes
- **Mapa dinâmico**: Geração procedural de obstáculos e itens
- **Sistema de bombas**: Diferentes tipos de bombas com efeitos variados
- **Coleta de itens**: Power-ups que modificam as habilidades dos jogadores
- **Estatísticas em tempo real**: Vida, dano, distância percorrida e vitórias
- **Efeitos visuais**: Explosões animadas e feedback visual

### 🔐 Sistema de Autenticação
- Login e registro de usuários
- Persistência de dados entre sessões
- IDs únicos para cada jogador

### 📊 Sistema de Ranking e Visualização
- **Ranking tradicional**: Tabelas ordenadas por diferentes critérios
- **Árvore B+ Didática**: Visualização simplificada da estrutura
- **Árvore B+ Real**: Visualização interativa da estrutura interna completa
- **Múltiplos critérios**: Ordenação por dano, vitórias ou distância percorrida
- **Cores e emojis**: Interface rica e intuitiva

### 🌳 Implementação de Árvore B+
- **Inserção/Atualização**: Operações eficientes O(log n)
- **Persistência**: Salvamento e carregamento em disco
- **Visualização gráfica**: Representação visual da estrutura da árvore
- **Navegação interativa**: Exploração da árvore em tempo real

## 🛠️ Dependências e Instalação

### Pré-requisitos
- **Sistema Operacional**: Linux/Unix ou Windows com WSL/Cygwin
- **Compilador**: GCC (GNU Compiler Collection)
- **Bibliotecas**: NCurses

### 📥 Instalação das Dependências

#### **Ubuntu/Debian:**
```bash
sudo apt-get update
sudo apt-get install gcc make libncurses5-dev libncursesw5-dev