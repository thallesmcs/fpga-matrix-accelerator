### Aplicação: Teste do Acelerador de Matrizes

#### Objetivo

Esta aplicação em C verifica o funcionamento do acelerador de hardware para multiplicação de matrizes. Ela inicializa matrizes na memória, envia os ponteiros para o IP de HLS, inicia a aceleração e compara o resultado com uma multiplicação feita por software.

#### Dependências de Hardware

-   **Processador:** Esta aplicação foi desenvolvida para rodar em um processador **Microblaze**.
-   **Acelerador:** Requer que o design de hardware contenha o IP de multiplicação de matrizes gerado pelo HLS.
-   **AXI Timer:** Esta aplicação utiliza IP aberta da xilinx para comparar o tempo de execução.

#### Plataforma Alvo

Exporte o hardware (com bitstream) no Vivado para a pasta:
`../../platforms/`

Exemplo de arquivo de plataforma:
`../../platforms/design_1_wrapper.xsa`

Abra no Vitis 2025.1, crie a plataforma a partir do `.xsa`, depois crie/importe este projeto de aplicação e execute no MicroBlaze.