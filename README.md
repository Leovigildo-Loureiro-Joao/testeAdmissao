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
    
- **Gerir testes** por disciplina (adicionar/editar/remover)
    
- **Visualizar** todos os cursos e testes
    
- **Ver resultados** dos alunos
    
- **Editar conteúdo** existente
    

### 🎓 Módulo Aluno

- **Realizar testes** de admissão
    
- **Obter resultados** imediatos com correção automática
    
- **Sistema de pontuação** na escala 0-20
    
- **Interface intuitiva** com questões randomizadas
    

## 🚀 Como Compilar

### Pré-requisitos

- GCC (GNU Compiler Collection)
    
- Sistema Linux/Windows com suporte a C
    

### Compilação

``` bash

# Compilar tudo
make all

# Apenas módulo admin
make admin

# Apenas módulo aluno  
make aluno

# Limpar compilações
make clean

# Ajuda com todos os comandos
make help
```
## 📋 Como Usar

### 1. Executar como Administrador

``` bash

# No Linux
./bin/admin

# No Windows  
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
    

### 3. Adicionar/Editar Testes

1. Selecionar "2-Editar Prova"
    
2. Escolher curso desejado
    
3. Selecionar disciplina
    
4. Escolher opção:
    
    - "Adicionar teste" - Criar novas questões
        
    - "Editar pergunta" - Modificar questões existentes
        
    - "Remover disciplina" - Eliminar disciplina
        

### 4. Realizar Teste como Aluno

``` bash

# No Linux
./bin/aluno

# No Windows
windows_bin/aluno.exe
```
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
### Aluno

```c

typedef struct {
    int numInscricao;
    char nome[100]; 
    char curso[100];
    float media;        // Média final (0-20)
} Aluno;
```
## 💾 Armazenamento de Dados

- **Formato**: Arquivos binários (.dat)
    
- **Localização**: Pasta `data/`
    
- **Estrutura**: Dados serializados em estruturas C
    

### Ficheiros:

- `cursos.dat` - Todos os cursos e seus testes
    
- `alunos.dat` - Resultados e dados dos alunos
    

## 🎮 Funcionalidades Detalhadas

### Para Administradores:

- ✅ Criar e configurar cursos completos
    
- ✅ Adicionar/remover/editar disciplinas
    
- ✅ Criar testes com múltiplas questões
    
- ✅ Validação automática de dados de entrada
    
- ✅ Sistema de edição de questões existentes
    
- ✅ Visualização organizada de todos os cursos
    
- ✅ Consulta de resultados dos alunos
    
- ✅ Remoção segura de cursos e disciplinas
    

### Para Alunos:

- ✅ Sistema de inscrição com número único
    
- ✅ Realizar testes de admissão completos
    
- ✅ Interface com questões aleatórias
    
- ✅ Correção automática imediata
    
- ✅ Resultados na escala 0-20
    
- ✅ Cálculo de média por disciplina e curso
    
- ✅ Salvamento automático de progresso
    

## 🔧 Características Técnicas

- **Linguagem**: C puro (C99 standard)
    
- **Persistência**: Arquivos binários com serialização
    
- **Interface**: Terminal/Console com menus intuitivos
    
- **Compilação**: Cross-platform (Linux/Windows)
    
- **Organização**: Código modular e reutilizável
    
- **Validação**: Verificação de erros técnicos nas questões
    
- **Segurança**: Prevenção de dados duplicados e corrompidos
    

## 🎯 Cursos Pré-Definidos

O sistema inclui 5 cursos completos com testes:

1. **Ciência da Computação** - Matemática, Português, Física
    
2. **Engenharia de Construção Civil** - Matemática, Física, Desenho Técnico
    
3. **Arquitetura** - Desenho Artístico, História da Arte, Matemática
    
4. **Eletrônica e Telecomunicações** - Matemática, Eletrônica, Física
    
5. **Recursos Humanos** - Português, Psicologia, Direito Trabalhista
    

Cada curso possui 3 disciplinas com 3 questões cada, totalizando 45 questões elaboradas.

## 🐛 Resolução de Problemas

### Erro Comum: "Erro ao criar ou abrir o file"

- Verifique se a pasta `data/` existe
    
- Confirme permissões de escrita no diretório
    
- Execute com permissões de administrador se necessário
    

### Dados Não Persistem

- Verifique espaço em disco disponível
    
- Confirme que o processo não foi interrompido
    
- Execute `make clean && make all` para recompilar
    

### Problemas de Compilação

- Certifique-se que tem GCC instalado
    
- Verifique a estrutura de pastas do projeto
    
- Confirme que todos os headers estão presentes
    

## 📞 Suporte

Para issues ou dúvidas:

1. Verifique a estrutura de pastas
    
2. Confirme que todos os ficheiros de header estão presentes
    
3. Execute `make clean && make all` para recompilar completamente
    
4. Verifique os logs no terminal para mensagens de erro específicas
    

## 🔄 Atualizações Recentes

- **Sistema completo de edição** de questões existentes
    
- **Funcionalidades de remoção** de cursos e disciplinas
    
- **Visualização de resultados** dos alunos no admin
    
- **Correção de bugs** no cálculo de médias
    
- **Otimização** do sistema de randomização de questões
    
- **Melhoria** na validação de dados de entrada
    

## 👨‍💻 Desenvolvido Por

Sistema desenvolvido para fins académicos com foco em eficiência, usabilidade e código limpo.

---

**🎓 Transformando a experiência de testes de admissão universitária!**