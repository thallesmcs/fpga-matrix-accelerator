#include <stdio.h>
#include <xparameters.h>
#include "platform.h"
#include "xil_printf.h"
#include "xtmrctr.h"
#include "xmatrix_mult_hw.h" // Driver da IP

// ===================================================================================
// Constantes e Instâncias Globais
// ===================================================================================
#define MATRIX_SIZE 16

XMatrix_mult_hw hw_ip;
XTmrCtr timer_dev;

// static int A[MATRIX_SIZE][MATRIX_SIZE]= {
//     {1, 2, 3},
//     {4, 5, 6},
//     {7, 8, 9}
// };
// static int B[MATRIX_SIZE][MATRIX_SIZE] = {
//     {9, 8, 7},
//     {6, 5, 4},
//     {3, 2, 1}
// };
static int A[MATRIX_SIZE][MATRIX_SIZE];
static int B[MATRIX_SIZE][MATRIX_SIZE];
static int C_sw[MATRIX_SIZE][MATRIX_SIZE];
static int C_hw[MATRIX_SIZE][MATRIX_SIZE];

// ===================================================================================
// Funções de Apoio (matrix_mult_sw e verify_results como antes)
// ===================================================================================
void matrix_mult_sw(int mat_a[MATRIX_SIZE][MATRIX_SIZE], int mat_b[MATRIX_SIZE][MATRIX_SIZE], int mat_c[MATRIX_SIZE][MATRIX_SIZE]) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            mat_c[i][j] = 0;
            for (int k = 0; k < MATRIX_SIZE; k++) {
                mat_c[i][j] += mat_a[i][k] * mat_b[k][j];
            }
        }
    }
}

int verify_results() {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            if (C_sw[i][j] != C_hw[i][j]) {
                xil_printf("ERRO: Discrepância em C[%d][%d]: SW=%d, HW=%d\n\r", i, j, C_sw[i][j], C_hw[i][j]);
                return -1;
            }
        }
    }
    return 0;
}

// ===================================================================================
// Função Principal (main)
// ===================================================================================
int main() {
    init_platform();

    xil_printf("\n");

    xil_printf("--- Início do Teste de Aceleracao de Multiplicacao de Matriz ---\n\r");

    XMatrix_mult_hw_Initialize(&hw_ip, XPAR_MATRIX_MULT_HW_0_BASEADDR);
    XTmrCtr_Initialize(&timer_dev, XPAR_XTMRCTR_0_BASEADDR);

    // 1. PREPARAÇÃO DOS DADOS
    for(int i = 0; i < MATRIX_SIZE; i++) {
        for(int j = 0; j < MATRIX_SIZE; j++) {
            A[i][j] = i + j;
            B[i][j] = i - j;
        }
    }

    // 2. EXECUÇÃO EM SOFTWARE (BASELINE)
    xil_printf("Executando multiplicacao em Software...\n\r");
    XTmrCtr_Start(&timer_dev, 0);
    u32 start_time_sw = XTmrCtr_GetValue(&timer_dev, 0);
    matrix_mult_sw(A, B, C_sw);
    u32 stop_time_sw = XTmrCtr_GetValue(&timer_dev, 0);
    u32 software_time = stop_time_sw - start_time_sw;
    XTmrCtr_Stop(&timer_dev, 0);
    XTmrCtr_Reset(&timer_dev, 0);

    // 3. EXECUÇÃO EM HARDWARE
    xil_printf("Executando multiplicacao em Hardware...\n\r");
    
    // 3.1 Escreve os dados para a IP usando a estrutura switch-case
    for (int i = 0; i < MATRIX_SIZE; i++) {
        // 'A[i]' é um ponteiro para o início da linha 'i' da matriz A.
        // O driver espera um ponteiro para os dados e o número de palavras (int) a serem escritas.
        switch(i) {
            case 0: XMatrix_mult_hw_Write_A_0_Words(&hw_ip, 0, A[i], MATRIX_SIZE); break;
            case 1: XMatrix_mult_hw_Write_A_1_Words(&hw_ip, 0, A[i], MATRIX_SIZE); break;
            case 2: XMatrix_mult_hw_Write_A_2_Words(&hw_ip, 0, A[i], MATRIX_SIZE); break;
            case 3: XMatrix_mult_hw_Write_A_3_Words(&hw_ip, 0, A[i], MATRIX_SIZE); break;
            case 4: XMatrix_mult_hw_Write_A_4_Words(&hw_ip, 0, A[i], MATRIX_SIZE); break;
            case 5: XMatrix_mult_hw_Write_A_5_Words(&hw_ip, 0, A[i], MATRIX_SIZE); break;
            case 6: XMatrix_mult_hw_Write_A_6_Words(&hw_ip, 0, A[i], MATRIX_SIZE); break;
            case 7: XMatrix_mult_hw_Write_A_7_Words(&hw_ip, 0, A[i], MATRIX_SIZE); break;
            case 8: XMatrix_mult_hw_Write_A_8_Words(&hw_ip, 0, A[i], MATRIX_SIZE); break;
            case 9: XMatrix_mult_hw_Write_A_9_Words(&hw_ip, 0, A[i], MATRIX_SIZE); break;
            case 10: XMatrix_mult_hw_Write_A_10_Words(&hw_ip, 0, A[i], MATRIX_SIZE); break;
            case 11: XMatrix_mult_hw_Write_A_11_Words(&hw_ip, 0, A[i], MATRIX_SIZE); break;
            case 12: XMatrix_mult_hw_Write_A_12_Words(&hw_ip, 0, A[i], MATRIX_SIZE); break;
            case 13: XMatrix_mult_hw_Write_A_13_Words(&hw_ip, 0, A[i], MATRIX_SIZE); break;
            case 14: XMatrix_mult_hw_Write_A_14_Words(&hw_ip, 0, A[i], MATRIX_SIZE); break;
            case 15: XMatrix_mult_hw_Write_A_15_Words(&hw_ip, 0, A[i], MATRIX_SIZE); break;
        }
        // Faz o mesmo para a matriz B
         switch(i) {
            case 0: XMatrix_mult_hw_Write_B_0_Words(&hw_ip, 0, B[i], MATRIX_SIZE); break;
            case 1: XMatrix_mult_hw_Write_B_1_Words(&hw_ip, 0, B[i], MATRIX_SIZE); break;
            case 2: XMatrix_mult_hw_Write_B_2_Words(&hw_ip, 0, B[i], MATRIX_SIZE); break;
            case 3: XMatrix_mult_hw_Write_B_3_Words(&hw_ip, 0, B[i], MATRIX_SIZE); break;
            case 4: XMatrix_mult_hw_Write_B_4_Words(&hw_ip, 0, B[i], MATRIX_SIZE); break;
            case 5: XMatrix_mult_hw_Write_B_5_Words(&hw_ip, 0, B[i], MATRIX_SIZE); break;
            case 6: XMatrix_mult_hw_Write_B_6_Words(&hw_ip, 0, B[i], MATRIX_SIZE); break;
            case 7: XMatrix_mult_hw_Write_B_7_Words(&hw_ip, 0, B[i], MATRIX_SIZE); break;
            case 8: XMatrix_mult_hw_Write_B_8_Words(&hw_ip, 0, B[i], MATRIX_SIZE); break;
            case 9: XMatrix_mult_hw_Write_B_9_Words(&hw_ip, 0, B[i], MATRIX_SIZE); break;
            case 10: XMatrix_mult_hw_Write_B_10_Words(&hw_ip, 0, B[i], MATRIX_SIZE); break;
            case 11: XMatrix_mult_hw_Write_B_11_Words(&hw_ip, 0, B[i], MATRIX_SIZE); break;
            case 12: XMatrix_mult_hw_Write_B_12_Words(&hw_ip, 0, B[i], MATRIX_SIZE); break;
            case 13: XMatrix_mult_hw_Write_B_13_Words(&hw_ip, 0, B[i], MATRIX_SIZE); break;
            case 14: XMatrix_mult_hw_Write_B_14_Words(&hw_ip, 0, B[i], MATRIX_SIZE); break;
            case 15: XMatrix_mult_hw_Write_B_15_Words(&hw_ip, 0, B[i], MATRIX_SIZE); break;
        }
    }

    // 3.2 Inicia a IP e mede o tempo de execução do núcleo
    XTmrCtr_Start(&timer_dev, 0);
    u32 start_time_hw = XTmrCtr_GetValue(&timer_dev, 0);
    XMatrix_mult_hw_Start(&hw_ip);
    while (!XMatrix_mult_hw_IsDone(&hw_ip));
    u32 stop_time_hw = XTmrCtr_GetValue(&timer_dev, 0);
    u32 hardware_time = stop_time_hw - start_time_hw;
    XTmrCtr_Stop(&timer_dev, 0);

    // 3.3 Lê o resultado da matriz C da IP
    // Como C não foi particionada, usamos a função única de leitura.
    XMatrix_mult_hw_Read_C_Words(&hw_ip, 0, (int*)C_hw, MATRIX_SIZE * MATRIX_SIZE);
    
    // 4. VERIFICAÇÃO E RESULTADOS FINAIS
    xil_printf("Verificando resultados...\n\r");
    if (verify_results() == 0) {
        xil_printf("SUCESSO: O resultado do Hardware e igual ao do Software!\n\n\r");
    } else {
        xil_printf("FALHA: O resultado do Hardware e diferente do Software!\n\n\r");
    }

    // Imprime a matriz de resultado do Hardware para visualização
    xil_printf("\n--- Matriz de Resultado do Hardware (C_hw) ---\n\r");
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            // Imprime cada elemento com um espaço
            xil_printf("%d ", C_hw[i][j]);
        }
        // Pula para a próxima linha no final de cada linha da matriz
        xil_printf("\n\r");
    }

    xil_printf("\n");

    // Imprime a matriz de resultado do Software para visualização
    xil_printf("\n--- Matriz de Resultado do Software (C_sw) ---\n\r");
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            // Imprime cada elemento com um espaço
            xil_printf("%d ", C_sw[i][j]);
        }
        // Pula para a próxima linha no final de cada linha da matriz
        xil_printf("\n\r");
    }

    xil_printf("\n");


    xil_printf("--- Analise de Performance ---\n\r");
    xil_printf("Tempo de execucao em Software: %d ciclos de clock\n\r", software_time);
    xil_printf("Tempo de execucao em Hardware: %d ciclos de clock\n\r", hardware_time);
    float speedup = (float)software_time / (float)hardware_time;
    printf("Speedup (Software / Hardware) = %.2fx\n\r", speedup);
    xil_printf("--------------------------------\n\r");

    cleanup_platform();
    return 0;
}