### Aplicação: Teste do Acelerador de Matrizes

#### Objetivo

Esta aplicação em C verifica o funcionamento do acelerador de hardware para multiplicação de matrizes. Ela inicializa matrizes na memória, envia os ponteiros para o IP de HLS, inicia a aceleração e compara o resultado com uma multiplicação feita por software.

#### Dependências de Hardware

-   **Processador:** Esta aplicação foi desenvolvida para rodar em um processador **Microblaze**.
-   **Acelerador:** Requer que o design de hardware contenha o IP de multiplicação de matrizes gerado pelo HLS.

#### Plataforma Alvo

Esta aplicação foi testada com a definição de hardware localizada em:
`../../platforms/acel_matrizes/design_1_wrapper.xsa`