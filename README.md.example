# Aula 3 / Sistemas Operativos – 2025  
**Repositório:** Aula3-2025  
**Instituição:** ULHT  - Universidade Lusófona


---

## Descrição

Este repositório contém o código de base para a Aula 3 da disciplina de **Sistemas Operativos (2025)**. O objetivo é fornecer aos alunos uma estrutura de simulador de escalonador FIFO, com uma aplicação “Hello World” inicial e um scheduler já parcialmente implementado. Serve de ponto de partida para que os alunos aprendam:

- a clonar um repositório GitHub;  
- a compilar e testar um programa “Hello World”;  
- a integrar um scheduler (FIFO) no projeto;  
- a configurar deployment remoto para sincronização automática de ficheiros com um servidor Linux.

---

## Estrutura do repositório

| Pasta / Ficheiro | Descrição |
|------------------|-----------|
| `main.c` / `hello_world.c` | Programa simples “Hello World”. Usado para confirmar que o ambiente está a funcionar correctamente. |
| `scheduler/` | Pasta com código relacionado ao escalonador FIFO. Contém implementação do FIFO, filas de processos, bursts, etc. |
| `queue.h` / `queue.c` | Estruturas de dados para filas de processos (FIFO). |
| `burst_queue.h` / `burst_queue.c` | Gestão dos bursts (CPU / I/O) de cada processo. |
| `fifo.h` / `fifo.c` | Lógica do escalonador FIFO. Recebe processos pela ordem de chegada e os executa sem preempção. |
| `app.c`, `app-pre.c` | Exemplos de aplicações / tarefas para simulação de carga de trabalho. |
| `CMakeLists.txt` | Ficheiro de configuração para construir o projecto usando CMake. |
| `run_apps.sh` | Script para compilar e executar a simulação facilmente no Linux. |
| `README.md` | Este ficheiro, com instruções e contexto. |

---

## Guião de utilização

Aqui ficam os passos que vamos seguir em aula (conforme o guião):

1. **Clonar o repositório**  
   `git clone https://github.com/ULHT-SistemasOperativos/Aula3-2025.git`

2. **Compilar e correr o “Hello World”**  
   - Abrir o projeto em CLion (ou outro IDE) ou terminal;  
   - Compilar com CMake;  
   - Executar o programa principal (`main.c` ou ficheiro equivalente).  

3. **Explorar o scheduler e os seus componentes**  
   - Verificar `scheduler/`, `fifo.c`, `queue.c`, `burst_queue.c`, etc;  
   - Entender como os processos e bursts são definidos nas apps;  
   - Ver como FIFO gere a ordem de execução.  

4. **Configurar Deployment remoto em CLion**  
   - Ir a *Settings → Build, Execution, Deployment → Deployment*;  
   - Criar uma configuração SFTP para o servidor Linux;  
   - Em *Mappings*, definir o caminho local do projeto e o caminho remoto correspondente.  

5. **Testar sincronização**  
   - Criar ou adicionar ficheiros no CLion;  
   - Verificar que aparecem no servidor Linux;  
   - Executar o scheduler para confirmar que tudo funciona integrado.  

---

## Como contribuir / modificar

- Se quiserem experimentar outros algoritmos de escalonamento (ex: Round Robin, SJF, etc.), podem criar novas pastas ou ficheiros dentro de `scheduler/` seguindo a interface definida por `fifo.h`.  
- Testem com diferentes cargas de trabalho modificando `app.c` ou `app-pre.c`.  
- Verifiquem os tempos de bursts, espera, tempo total de execução, etc, para comparar desempenho entre algoritmos.

---

## Requisitos e dependências

- CLion (ou outra IDE com suporte a C / CMake)  
- GCC ou clang / compilador de C compatível  
- Sistema Linux ou servidor remoto com acesso via SSH/SFTP (para deployment)  
- Acesso à internet (para clonar o repositório)  

---

## Licença

(Indicar aqui a licença, se aplicável — exemplo: MIT, GPL, etc.)

---

## Autor / Contacto

- Docentes: Paulo Guedes, Martijn Kuipers, Daniel Silveira
- Email: p4693@ulusofona.pt, martijn.kuipers@ulusofona.pt, p6902@ulusofona.pt
- Versão: 1.0 (início do semestre 2025)

---

