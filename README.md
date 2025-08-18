<a id="topo"></a>

FPGA Matrix Accelerator (16x16)

Este repositório contém um design completo de aceleração para multiplicação de matrizes 16x16 em FPGA, integrando:

- IP de multiplicação de matrizes gerado com Vitis HLS (submódulo `hls`)
- Projeto de hardware no Vivado 2025.1 com MicroBlaze, interconexões AXI e IP AXI Timer
- Aplicação de teste em C para validar o acelerador via MicroBlaze

![Arquitetura no Vivado](docs/images/arquitetura_viv.png)

## Navegação rápida

- [Estrutura do repositório](#estrutura)
- [Requisitos](#requisitos)
- [Como clonar](#clonar)
- [Fluxo resumido](#fluxo)
- [Observações importantes](#observacoes)

<a id="estrutura"></a>

## Estrutura do repositório

- `Hardware/` – Projeto Vivado 2025.1 (`acel_matrizes.xpr`), diagrama de blocos e constraints. Veja `Hardware/README.md`.
- `hls/` – Submódulo com projetos Vitis HLS (2024.2/2025.1) que geram os IPs. Veja `hls/README.md`.
- `Software/` – Plataforma exportada (`.xsa`) e aplicação de teste para MicroBlaze. Veja `Software/README.md`.

Target e ferramentas usadas:

- FPGA alvo: Xilinx Spartan-7 XC7S50-CSGA324
- Vivado: 2025.1
- Vitis HLS: 2024.2, 2025.1 e Classic
- Vitis (SDK): 2025.1

<!-- [Voltar ao topo](#topo) -->

<a id="requisitos"></a>

## Requisitos

- Sistema: Windows 10/11 64-bit
- Git com suporte a submódulos
- Xilinx Vivado e Vitis instalados (versões em "Target e ferramentas usadas")
- Licenças Xilinx ativas (Vivado/Vitis)
- Drivers: JTAG (Xilinx/Digilent) e USB-UART (FTDI) para a sua placa
- FPGA/placa compatível com XC7S50-CSGA324 (ou equivalente) com JTAG e UART

<!-- [Voltar ao topo](#topo) -->

<a id="clonar"></a>

## Como clonar

Este projeto usa `hls/` como submódulo git, apontando para o repositório:
https://github.com/thallesmcs/Vitis_HLS.git

Repositório principal:
https://github.com/thallesmcs/fpga-matrix-accelerator.git

Recomendado (clonar já trazendo o submódulo):

```powershell
git clone --recurse-submodules https://github.com/thallesmcs/fpga-matrix-accelerator.git
```

Se você já clonou sem submódulos, inicialize/atualize depois:

```powershell
cd fpga-matrix-accelerator
git submodule update --init --recursive
```

Opcional: para atualizar o submódulo para a revisão mais recente da branch remota (cuidado, isso muda o ponteiro):

```powershell
git submodule update --remote --merge
```

Observação: baixar o repositório como ZIP não inclui submódulos. Prefira usar `git clone` com `--recurse-submodules`.

<!-- [Voltar ao topo](#topo) -->

<a id="fluxo"></a>

## Fluxo resumido

Pré-requisito: confira "Requisitos" e siga "Como clonar" antes de iniciar.

1) Hardware (Vivado)
- Abra `Hardware/acel_matrizes.xpr` (Vivado 2025.1)
- Rode Synthesis/Implementation e gere o Bitstream
- Exporte o hardware com bitstream (XSA) para `Software/platforms/`

2) Software (Vitis)
- Crie uma plataforma a partir do `.xsa` exportado
- Crie/importe a aplicação de teste de `Software/matrix_test_app/`
- Compile e rode via MicroBlaze (UART para logs)

3) HLS (opcional)
- Use os projetos em `hls/` para atualizar/gerar IPs no Vitis HLS
- Reintegre o IP no Vivado se necessário

Detalhes por pasta estão nos READMEs locais:
- `Hardware/README.md`
- `Software/README.md`
- `hls/README.md` (já no submódulo)

<!-- [Voltar ao topo](#topo) -->

<a id="observacoes"></a>

## Observações importantes

- A pasta `hls/` é um submódulo: evite editar o conteúdo diretamente aqui; faça alterações no repositório do submódulo e atualize o ponteiro.
- O caminho do `.xsa` no `Software/platforms/` pode variar conforme a exportação. Ajuste no Vitis conforme o nome de arquivo que você exportar.

[Voltar ao topo](#topo)

<!-- ## Próximos passos sugeridos

- Automatizar export/import com scripts TCL (Vivado) e XSCT (Vitis)
- Adicionar testes automatizados de verificação de matriz (golden model) na aplicação
- Documentar versões de IP e parâmetros (largura de dados, latência, interface AXI) -->