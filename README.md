# Pato Burger · HamburgeriaPato

Jogo de terminal em **C**, desenvolvido em equipe para a disciplina de **Algoritmos e Estruturas de Dados (AED)**.

## O jogo

O jogador monta hambúrgueres a partir de pedidos exibidos por tempo limitado. É preciso memorizar os pedidos, respeitar a sequência dos ingredientes e administrar um estoque limitado e o saldo do restaurante.

- Cardápio com dez receitas e treze ingredientes.
- Pedidos aleatórios, com quantidade variável conforme o dia.
- Pagamento proporcional ao acerto da sequência de ingredientes.
- Compra e venda de ingredientes entre os dias.
- Custos de operação e fim de jogo quando as moedas acabam.
- Gravação de relatórios diários e de uso de ingredientes em arquivo de texto.

## Estruturas de dados na prática

| Recurso | Aplicação no projeto | Arquivo principal |
| --- | --- | --- |
| Pilha | Representação das receitas, montagem e inversão da sequência dos ingredientes | [pilha.h](pilha.h), [cardapio.h](cardapio.h) |
| Fila circular | Armazenamento e atendimento dos pedidos na ordem de chegada | [fila.h](fila.h) |
| Árvore AVL | Organização e busca dos ingredientes por nome, com balanceamento por rotações | [arvoreavl.h](arvoreavl.h), [loja_ingredientes.h](loja_ingredientes.h) |
| Ordenação por bolha (bubble sort) | Ordenação dos ingredientes por quantidade de usos | [loja_ingredientes.h](loja_ingredientes.h) |
| Arquivos de texto | Escrita e leitura dos relatórios com a biblioteca padrão de C | [aloca.h](aloca.h) |

O projeto também utiliza structs, ponteiros, alocação dinâmica, recursão, funções e separação do código em módulos.

## Como executar

### Requisitos

- **Windows**, pois o código utiliza `windows.h`, `Sleep`, `cls` e `chcp`.
- **GCC para Windows** disponível no `PATH` (por exemplo, uma instalação MinGW-w64).
- Terminal com suporte a UTF-8 e sequências de cor ANSI.

Não há bibliotecas externas além do compilador e das bibliotecas do sistema.

### Compilar e iniciar pelo PowerShell

Na pasta do repositório:

```powershell
gcc --version
New-Item -ItemType Directory -Force -Path output | Out-Null
gcc -std=c11 -finput-charset=UTF-8 main.c -o output/PatoBurger.exe
```

Se a compilação terminar sem erros:

```powershell
Push-Location output
try {
    .\PatoBurger.exe
} finally {
    Pop-Location
}
```

**Execute dentro de `output`.** O programa usa o caminho relativo `../alocacao.txt`, de modo que o relatório fica na raiz do projeto. O relatório anterior é sobrescrito ao iniciar uma nova partida.

Compile `main.c`; os arquivos `.h` são incluídos por ele e não devem ser compilados como programas separados.

### Controles

- Digite o número do ingrediente e pressione Enter para adicioná-lo.
- `13`: abrir o cardápio.
- `14`: consultar o estoque.
- `15`: finalizar o pedido.
- Entre os dias, use o menu da loja para comprar ou vender ingredientes.

## Organização do código

| Arquivo | Responsabilidade |
| --- | --- |
| [main.c](main.c) | Fluxo da partida, dias, pedidos, ganhos e custos |
| [cardapio.h](cardapio.h) | Receitas, geração dos pedidos e comparação dos hambúrgueres |
| [montagem.h](montagem.h) | Exibição dos ingredientes no terminal |
| [pilha.h](pilha.h) | Operações de pilha |
| [fila.h](fila.h) | Operações de fila circular |
| [arvoreavl.h](arvoreavl.h) | Operações e balanceamento da árvore AVL |
| [loja_ingredientes.h](loja_ingredientes.h) | Estoque, compra, venda e ordenação por uso |
| [aloca.h](aloca.h) | Gravação e leitura dos relatórios |

Os executáveis e relatórios são gerados localmente e ignorados pelo Git.

## Contexto acadêmico e autoria

Projeto desenvolvido por:

- Daniel Carneiro
- Davi Brito.
- Gustavo Neves.
- Miguel Carmo.


## Estado do projeto

Protótipo acadêmico para Windows. A versão preserva a implementação original do jogo, com oportunidades de melhoria na validação de entradas, nos relatórios e na portabilidade.


