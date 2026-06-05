# 💻 C++ Notepad v1.0.0

**Um editor de texto profissional e ultrarrápido desenvolvido em C++ com Windows API nativa.**

[![GitHub](https://img.shields.io/badge/GitHub-c%2B%2BNotepad--1.0.0-blue)](https://github.com/Lipezinn01/c-plusplus-notepad-1.0.0)
[![License](https://img.shields.io/badge/License-MIT-green)](LICENSE)
[![Platform](https://img.shields.io/badge/Platform-Windows-0078D4)](https://www.microsoft.com/windows)
[![Language](https://img.shields.io/badge/Language-C%2B%2B-00599C)](https://cplusplus.com)

---

## 🌟 Características Principais

### ⚡ Performance Máxima
- **Arquivo .exe ultra-compacto** (~50-100 KB)
- **Velocidade de execução** instantânea ⚡
- **Sem lag ou travamentos**
- **Consumo mínimo de memória**

### 🎨 Fonte Profissional
- **Acesso a TODAS as fontes do Windows** instaladas no sistema
- **Diálogo padrão ChooseFont do Windows**
- **Pré-visualização em tempo real**
- **Efeitos especiais** (negrito, itálico, sublinhado, tachado)
- **Tamanhos ilimitados**

### 🛡️ Segurança
- **Windows Defender confia 100%**
- **Sem antivírus bloqueia**
- **Código nativo compilado**
- **APIs Windows legitimadas**
- **Sem dependências externas**

### 📝 Funcionalidades Completas
- ✅ Abrir arquivos (.txt, .log, .py, .html, .json, etc)
- ✅ Salvar com qualquer extensão
- ✅ Salvar especificamente como .txt
- ✅ **Quebra de linha automática/manual** aos 1024 caracteres
- ✅ Menu Formatar com acesso a todas as fontes
- ✅ Atalhos de teclado (CTRL+S, CTRL+O, CTRL+N)
- ✅ Detecção de modificações
- ✅ Interface amigável e responsiva

---

## 🚀 Download e Instalação

### Opção 1: Download Direto
[Baixar C++ Notepad v1.0.0](https://github.com/Lipezinn01/c-plusplus-notepad-1.0.0/releases)

```
1. Faça download de NotepadCpp.exe
2. Execute o arquivo
3. Pronto! Sem instalação necessária
```

### Opção 2: Clonar do GitHub
```bash
git clone https://github.com/Lipezinn01/c-plusplus-notepad-1.0.0.git
cd c-plusplus-notepad-1.0.0
```

---

## 📖 Como Usar

### Botões do Menu Principal

| Botão | Função | Atalho |
|-------|--------|--------|
| **Salvar Como...** | Salva com qualquer extensão | CTRL+S* |
| **Salvar .txt** | Salva rapidamente como .txt | - |
| **Escolher Documento** | Abre arquivos do PC | CTRL+O |
| **Formatar** | Abre menu de formatação | - |
| **Ajuda** | Mostra ajuda do programa | - |

*CTRL+S abre o "Salvar Como"

### Menu Formatar

```
┌─────────────────────────────────┐
│ Formatar                        │
├─────────────────────────────────┤
│ ✓ Quebra de Linha Automática    │ ← Toggle
│ Fontes...                       │ ← Abre ChooseFont
└─────────────────────────────────┘
```

**Quebra de Linha:**
- **Automática (padrão):** Cria nova linha automaticamente ao atingir 1024 caracteres
- **Manual:** Trava em 1024 caracteres, precisa pressionar ENTER

**Fontes:**
- Abre diálogo profissional do Windows
- Acesso a TODAS as fontes instaladas
- Pré-visualização em tempo real
- Tamanho e estilos ilimitados

---

## 🎯 Atalhos de Teclado

| Atalho | Função |
|--------|--------|
| CTRL+S | Salvar Como |
| CTRL+O | Abrir arquivo |
| CTRL+N | Alternar Quebra de Linha |
| CTRL+Z | Desfazer (nativo do Windows) |
| CTRL+Y | Refazer (nativo do Windows) |

---

## 🏆 Por que C++ ao invés de Python?

### Comparação Técnica

| Aspecto | Python (PyInstaller) | C++ (Win32) |
|---------|---------------------|------------|
| **Tamanho arquivo** | 10-15 MB | ~50-100 KB |
| **Velocidade** | Muito rápido | Ultra rápido ⚡ |
| **Windows Defender** | ⚠️ Às vezes avisa | ✅ Sempre confia |
| **Dependências** | Python + libs | Nenhuma |
| **Fontes disponíveis** | 4 estilos limitados | ∞ (Todas do sistema) |
| **Interface Fonte** | Customizada | Padrão Windows |
| **Consumo memória** | Médio | Mínimo |
| **Compressão** | Difícil | Fácil |
| **Antivírus 3ª pátria** | ⚠️ Pode bloquear | ✅ Nunca bloqueia |

### Vantagens do C++

✅ **Arquivo minúsculo** - Apenas ~50-100 KB  
✅ **Extremamente rápido** - Resposta instantânea  
✅ **100% seguro** - Windows Defender confia  
✅ **Sem dependências** - Executa em qualquer Windows  
✅ **Fontes nativas** - Acesso a TODAS as fontes do sistema  
✅ **Interface profissional** - Diálogos padrão Windows  
✅ **Código nativo** - Compilado para máquina  

---

## 💡 Versões Disponíveis

Existem **2 versões** do Notepad disponíveis:

### 🐍 [Python Notepad](https://github.com/Lipezinn01/PyNotepad-1.0.0)
- Fácil de customizar e modificar
- Multiplataforma (Windows, Linux, macOS)
- Código-fonte em Python
- Interface Tkinter
- ~10-15 MB

### 💻 **[C++ Notepad](https://github.com/Lipezinn01/c-plusplus-notepad-1.0.0)** (ESTE REPOSITÓRIO)
- Máxima performance
- Windows nativo
- Arquivo ultra-compacto (~50-100 KB)
- Código-fonte em C++
- Acesso a todas as fontes do sistema
- **RECOMENDADO para distribuição**

---

## 🔧 Compilação (Opcional)

Se quiser compilar do código-fonte:

### Requisitos
- Visual Studio 2019+ ou MinGW
- Windows SDK

### Compilar com Visual Studio
```batch
cl /O2 /Fe:NotepadCpp.exe notepad.cpp /link user32.lib gdi32.lib comdlg32.lib comctl32.lib
```

### Compilar com MinGW
```bash
g++ -O2 -o NotepadCpp.exe notepad.cpp -luser32 -lgdi32 -lcomdlg32 -lcomctl32
```

---

## 📊 Estatísticas

```
Linguagem:        C++ (100%)
Linhas de código: ~250 linhas
Tamanho .exe:     ~50-100 KB
Tempo compilação: <1 segundo
Memória usada:    ~5-10 MB (em uso)
Compatibilidade:  Windows 7+ (64-bit e 32-bit)
```

---

## 🐛 Problemas Conhecidos

Nenhum identificado até o momento! ✅

---

## 🚀 Roadmap Futuro

- [ ] Versão portável (USB)
- [ ] Temas personalizados (Dark mode, Light mode)
- [ ] Buscar e substituir (Find & Replace)
- [ ] Numeração de linhas
- [ ] Syntax highlighting para código
- [ ] Atualização automática
- [ ] Suporte a arquivos muito grandes (>100 MB)

---

## 📝 Licença

Este projeto está licenciado sob a **MIT License** - veja o arquivo [LICENSE](LICENSE) para detalhes.

```
MIT License

Copyright (c) 2026 Lipezinn01

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction...
```

---

## 👨‍💻 Autor

**Lipezinn01**

- GitHub: [@Lipezinn01](https://github.com/Lipezinn01)
- Email: [seu-email@exemplo.com]
- Portfólio: [seu-site.com]

---

## 🤝 Contribuições

Contribuições são bem-vindas! Você pode:

1. Fork o projeto
2. Criar uma branch para sua feature (`git checkout -b feature/AmazingFeature`)
3. Commit suas mudanças (`git commit -m 'Add some AmazingFeature'`)
4. Push para a branch (`git push origin feature/AmazingFeature`)
5. Abrir um Pull Request

---

## 💬 Feedback e Sugestões

Se tiver sugestões ou encontrar bugs, abra uma [Issue](https://github.com/Lipezinn01/c-plusplus-notepad-1.0.0/issues).

---

## 📚 Recursos Utilizados

- **Windows API** - CreateWindowEx, SendMessage, etc
- **Common Controls** - ChooseFont, OpenFileName
- **Standard C++** - STL, strings, vectors
- **Visual Studio** - Compilação e desenvolvimento

---

## ⭐ Se gostou, deixe uma estrela!

Se este projeto foi útil para você, considere deixar uma ⭐ no GitHub!

---

## 📜 Histórico de Versões

### v1.0.0 (2026-05-09)
- ✅ Primeira versão estável
- ✅ Todas as funcionalidades core
- ✅ Quebra de linha automática/manual
- ✅ Menu Formatar com acesso a todas as fontes
- ✅ Atalhos de teclado completos
- ✅ Interface responsiva

---

<div align="center">

**Desenvolvido com ❤️ em C++**

[⬆ Voltar ao topo](#-c-notepad-v100)

</div>
