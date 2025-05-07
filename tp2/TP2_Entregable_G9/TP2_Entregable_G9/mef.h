#ifndef MEF_H
#define MEF_H

/**
 * @brief Inicializa la Máquina de Estados Finitos.
 * 
 * Configura el estado inicial, inicializa el generador de números aleatorios
 * y limpia la pantalla LCD.
 */
void MEF_init();

/**
 * @brief Actualiza el estado de la Máquina de Estados Finitos.
 * 
 * Este método maneja la lógica de transición entre estados y las acciones
 * correspondientes según la entrada del usuario y el temporizador.
 */
void MEF_update();

#endif