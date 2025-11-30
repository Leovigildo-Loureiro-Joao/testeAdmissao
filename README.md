# 📚 Sistema de Testes de Admissão

## 🎯 Descrição

Sistema desenvolvido em C para criação, gestão e aplicação de testes de admissão em ambiente universitário. Permite aos administradores criar cursos, disciplinas e testes, enquanto os alunos podem realizar os testes e obter resultados imediatos.

## 🏗️ Estrutura do Projeto

``` text

projeto/
├── src/
│   ├── admin/           # Código do administrador
│   │   ├── main_admin.c    # Menu principal do admin
│   │   └── utils.c         # Funções auxiliares
│   ├── aluno/           # Código do aluno
│   │   ├── main_student.c  # Menu principal do aluno
│   │   └── aluno.c         # Funções do aluno
│   └── common/          # Código compartilhado
│       ├── curso.c         # Gestão de cursos
│       └── teste.c         # Gestão de testes
├── include/             # Headers
│   ├── admin.h
│   ├── teste.h
│   └── common.h
├── bin/  
├── windows_bin/                 # Executáveis compilados
├── data/               # Dados da aplicação
└── Makefile
```

## 👥 Módulos do Sistema

### 🛠️ Módulo Administrador

- **Criar cursos** com múltiplas disciplinas
- **Gerir testes** por disciplina
- **Editar conteúdo** existente
- **Visualizar** todos os cursos e testes

### 🎓 Módulo Aluno

- **Realizar testes** de admissão
- **Obter resultados** imediatos
- **Visualizar** histórico de desempenho

## 🚀 Como Compilar

### Pré-requisitos

- GCC (GNU Compiler Collection)
- Sistema Linux/Windows com suporte a C

### Compilação

```bash

# Compilar tudo
make all

# Apenas módulo admin
make admin

# Apenas módulo aluno
make aluno

# Limpar compilações
make clean 

# Acedera a todos comandos para compilar ou usar o projecto
make help 
```
## 📋 Como Usar

### 1. Executar como Administrador

```bash
#no Linux
./bin/admin

#no Windows
windows_bin/admin.exe
```
**Menu do Administrador:**

```text

======================================
     Bem vindo Administrador
======================================
1-Criar Prova
2-Editar Prova  
3-Ver Provas
4-Visualizar Resultados
5-Sair
```
### 2. Criar um Novo Curso

1. Selecionar "1-Criar Prova"
2. Inserir nome do curso
3. Definir número de disciplinas
4. Adicionar nome de cada disciplina
5. O sistema salva automaticamente

### 3. Adicionar Testes a Disciplinas

1. Selecionar "2-Editar Prova"
2. Escolher curso desejado
3. Selecionar disciplina
4. Escolher "Adicionar teste"
5. Inserir perguntas e respostas

## 🏗️ Estruturas de Dados Principais

### Curso

```c

typedef struct {
    char nome[100];
    int num_disc;
    Teste teste[20];  // Array de disciplinas
} Curso;
```
### Teste (Disciplina)

```c

typedef struct {
    char nome[100];
    int qtd;          // Número de questões
    Question asks[20]; // Array de questões
} Teste;
```
### Questão

```c
typedef struct {
    char question[200];
    char solution[200];    // Resposta correta
    char other[3][200];    // Respostas incorretas
} Question;
```

## 💾 Armazenamento de Dados

- **Formato**: Arquivos binários (.dat)
- **Localização**: Pasta `data/`
- **Estrutura**: Dados serializados em estruturas C

### Ficheiros:

- `cursos.dat` - Todos os cursos e seus testes
- `resultados.dat` - Resultados dos alunos

## 🎮 Funcionalidades Detalhadas

### Para Administradores:

- ✅ Criar e configurar cursos
- ✅ Adicionar/remover disciplinas
- ✅ Criar testes com múltiplas questões
- ✅ Validação de dados de entrada
- ✅ Edição de conteúdo existente
- ✅ Visualização de todos os cursos

### Para Alunos:

- ✅ Realizar testes de admissão
- ✅ Interface de questões aleatórias
- ✅ Correção automática
- ✅ Resultados imediatos

## 🔧 Características Técnicas

- **Linguagem**: C puro
- **Persistência**: Arquivos binários
- **Interface**: Terminal/Console
- **Compilação**: Cross-platform (Linux/Windows)
- **Organização**: Código modular

## 🐛 Resolução de Problemas

### Erro Comum: "Erro ao criar ou abrir o file"

- Verifique se a pasta `data/` existe
- Confirme permissões de escrit

### Dados Não Persistem

- Execute com permissões de administrador se necessário
- Verifique espaço em disco

## 📞 Suporte

Para issues ou dúvidas:

1. Verifique a estrutura de pastas
2. Confirme que todos os ficheiros de header estão presentes
3. Execute `make clean && make all` para recompilar 

## 👨‍💻 Desenvolvido Por

Sistema desenvolvido para fins académicos com foco em eficiência e usabilidade.

---

**🎓 Transformando a experiência de testes de admissão universitária!**