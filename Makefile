# ========================
# 💥 Projeto: Teste Admissao (Cross-Compilation)
# ========================

# Compiladores
CC_LINUX = gcc
CC_WIN = x86_64-w64-mingw32-gcc

# Diretórios
SRC_DIR = src
INC_DIR = include
BIN_DIR = bin
DATA_DIR = data
WIN_DIR = windows_bin

# Executáveis
ADMIN_LINUX = $(BIN_DIR)/admin
ALUNO_LINUX = $(BIN_DIR)/aluno
ADMIN_WIN = $(WIN_DIR)/admin.exe
ALUNO_WIN = $(WIN_DIR)/aluno.exe

# Arquivos fonte
ADMIN_SRC = $(SRC_DIR)/admin/main_admin.c  $(SRC_DIR)/admin/utils.c $(SRC_DIR)/common/curso.c $(SRC_DIR)/common/teste.c
ALUNO_SRC = $(SRC_DIR)/aluno/main_student.c $(SRC_DIR)/aluno/aluno.c $(SRC_DIR)/admin/utils.c $(SRC_DIR)/common/curso.c $(SRC_DIR)/common/teste.c

# Flags de compilação
CFLAGS = -Wall -I$(INC_DIR)
CFLAGS_WIN = -Wall -I$(INC_DIR) -static-libgcc

# ========================
# Regras Principais
# ========================

# Compilar tudo (Linux)
all: admin aluno

# Compilar tudo para Windows
windows: admin-win aluno-win

# Compilar ambos sistemas
all-systems: all windows

# ========================
# Linux Targets
# ========================

# Programa do Administrador (Linux)
admin: $(ADMIN_SRC)
	@mkdir -p $(BIN_DIR) $(DATA_DIR)
	$(CC_LINUX) $(ADMIN_SRC) -o $(ADMIN_LINUX) $(CFLAGS)
	@echo "✅ Admin (Linux) compilado: $(ADMIN_LINUX)"

# Programa do Aluno (Linux)
aluno: $(ALUNO_SRC)
	@mkdir -p $(BIN_DIR) $(DATA_DIR)
	$(CC_LINUX) $(ALUNO_SRC) -o $(ALUNO_LINUX) $(CFLAGS)
	@echo "✅ Aluno (Linux) compilado: $(ALUNO_LINUX)"

# ========================
# Windows Targets
# ========================

# Programa do Administrador (Windows)
admin-win: $(ADMIN_SRC)
	@mkdir -p $(WIN_DIR) $(DATA_DIR)
	$(CC_WIN) $(ADMIN_SRC) -o $(ADMIN_WIN) $(CFLAGS_WIN)
	@echo "✅ Admin (Windows) compilado: $(ADMIN_WIN)"

# Programa do Aluno (Windows)
aluno-win: $(ALUNO_SRC)
	@mkdir -p $(WIN_DIR) $(DATA_DIR)
	$(CC_WIN) $(ALUNO_SRC) -o $(ALUNO_WIN) $(CFLAGS_WIN)
	@echo "✅ Aluno (Windows) compilado: $(ALUNO_WIN)"

# ========================
# Execução
# ========================

# Executar Admin (Linux)
run-admin: admin
	@echo "🚀 Executando Admin (Linux)..."
	@$(ADMIN_LINUX)

# Executar Aluno (Linux)
run-aluno: aluno
	@echo "🎓 Executando Aluno (Linux)..."
	@$(ALUNO_LINUX)

# Testar Admin no Wine
test-admin-win: admin-win
	@echo "🍷 Testando Admin no Wine..."
	@wine $(ADMIN_WIN) 2>/dev/null || echo "⚠️  Instale o Wine para testar: sudo apt-get install wine"

# Testar Aluno no Wine
test-aluno-win: aluno-win
	@echo "🍷 Testando Aluno no Wine..."
	@wine $(ALUNO_WIN) 2>/dev/null || echo "⚠️  Instale o Wine para testar: sudo apt-get install wine"

# Testar ambos no Wine
test-windows: test-admin-win test-aluno-win

# ========================
# Utilitários
# ========================

# Limpar tudo
clean:
	@rm -rf $(BIN_DIR) $(WIN_DIR)
	@echo "🧹 Limpeza concluída!"

# Listar arquivos compilados
list:
	@echo "📁 Linux:"
	@ls -la $(BIN_DIR)/ 2>/dev/null || echo "  (vazio)"
	@echo "📁 Windows:"
	@ls -la $(WIN_DIR)/ 2>/dev/null || echo "  (vazio)"

# Verificar dependências
check-deps:
	@echo "🔍 Verificando dependências..."
	@which $(CC_LINUX) >/dev/null && echo "✅ $(CC_LINUX) encontrado" || echo "❌ $(CC_LINUX) não encontrado"
	@which $(CC_WIN) >/dev/null && echo "✅ $(CC_WIN) encontrado" || echo "❌ $(CC_WIN) não encontrado - instale: sudo apt-get install mingw-w64"
	@which wine >/dev/null && echo "✅ Wine encontrado" || echo "❌ Wine não encontrado - instale: sudo apt-get install wine"

# Ajuda
help:
	@echo "🎯 COMANDOS DISPONÍVEIS:"
	@echo ""
	@echo "🏗️  COMPILAÇÃO:"
	@echo "  make all          - Compila para Linux"
	@echo "  make windows      - Compila para Windows"
	@echo "  make all-systems  - Compila para ambos"
	@echo "  make admin        - Apenas Admin (Linux)"
	@echo "  make admin-win    - Apenas Admin (Windows)"
	@echo "  make aluno        - Apenas Aluno (Linux)"
	@echo "  make aluno-win    - Apenas Aluno (Windows)"
	@echo ""
	@echo "🚀 EXECUÇÃO:"
	@echo "  make run-admin    - Executa Admin (Linux)"
	@echo "  make run-aluno    - Executa Aluno (Linux)"
	@echo "  make test-admin-win - Testa Admin no Wine"
	@echo "  make test-windows - Testa ambos no Wine"
	@echo ""
	@echo "🔧 UTILITÁRIOS:"
	@echo "  make clean        - Limpa tudo"
	@echo "  make list         - Lista arquivos compilados"
	@echo "  make check-deps   - Verifica dependências"
	@echo "  make help         - Mostra esta ajuda"

# Alvo padrão
.DEFAULT_GOAL := help
