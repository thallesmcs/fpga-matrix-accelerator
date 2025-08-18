# Software (MicroBlaze + Vitis 2025.1)

Este diretório contém a plataforma exportada do Vivado (`platforms/`) e a aplicação de teste (`matrix_test_app/`).

## Plataforma

- `platforms/design_1_wrapper.xsa`: exporte o XSA a partir do projeto Vivado (com bitstream incluso). O nome pode variar.

## Aplicação de teste

- Diretório: `matrix_test_app/`
- Objetivo: validar o acelerador de multiplicação 16x16 via MicroBlaze
- Entrada/saída: matrizes em memória; logs via UART

Passos no Vitis 2025.1:

1. Crie uma plataforma a partir do `.xsa` em `platforms/`
2. Crie/importe a aplicação a partir de `matrix_test_app/`
3. Compile e rode

Consulte `matrix_test_app/README.md` para detalhes específicos da aplicação.
