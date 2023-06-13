/**
 * @file test_reloj.c
 * @author Joel Jassan <joeljassan@hotmail.com>
 * @brief Funciones de testing tipo TDD para las funciones de reloj.c
 * @date 2023-06-10
 * 
 * @copyright Copyright (c) 2023. All rights reserved.
 * 
 */


// ‣ Fijar la hora de la alarma y consultarla.
// ‣ Fijar la alarma y avanzar el reloj para que suene.
// ‣ Fijar la alarma, deshabilitarla y avanzar el reloj para no
// suene.
// ‣ Hacer sonar la alarma y posponerla.
// ‣ Hacer sonar la alarma y cancelarla hasta el otro dia..

/* ---  Headers files inclusions  -------------------------------------------------------------- */

#include "unity.h"
#include "reloj.h"

/* ---  Macros definitions  -------------------------------------------------------------------- */

#define CLOCK_SIZE 6
#define TICKS_PER_SECOND 5

/*---  Private Function Implementation  -------------------------------------------------------- */

void setUp(void) {
    static const uint8_t SET_INICIAL[] = {1, 2, 3, 4, 0, 0};
    clock_t reloj = ClockCreate(TICKS_PER_SECOND);
    ClockSetTime(reloj, SET_INICIAL, sizeof(SET_INICIAL));
}

/* ---  Testing Function Implementation  ------------------------------------------------------- */

// Al inicializar el reloj está en 00:00 y con hora invalida.
void test_start_up(void) {
    static const uint8_t ESPERADO [] = {0, 0, 0, 0, 0, 0};
    uint8_t hora [CLOCK_SIZE] = {0xFF};
    clock_t reloj = ClockCreate(TICKS_PER_SECOND);

    TEST_ASSERT_FALSE(ClockGetTime(reloj, hora, CLOCK_SIZE));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, hora, CLOCK_SIZE);
}


// Al ajustar la hora el reloj queda en hora y es válida.
void test_adjust_time (void) {
    static const uint8_t ESPERADO [] = {1, 2, 3, 4, 0, 2};
    uint8_t hora [CLOCK_SIZE] = {0xFF};
    clock_t reloj = ClockCreate(TICKS_PER_SECOND);

    TEST_ASSERT_TRUE(ClockSetTime(reloj, ESPERADO, CLOCK_SIZE));
    TEST_ASSERT_TRUE(ClockGetTime(reloj, hora, CLOCK_SIZE));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, hora, CLOCK_SIZE);
}

//Después de n ciclos de reloj la hora avanza un segundo, diez segundos, un minutos, diez minutos, 
//una hora, diez horas, y un día completo.

// Aumenta la unidad de los segundos
void test_increment_uni_second(void) {
    static const uint8_t SET_INICIAL[] = {1, 2, 3, 4, 0, 0};
    static const uint8_t ESPERADO [] = {1, 2, 3, 4, 0, 1};

    clock_t reloj = ClockCreate(TICKS_PER_SECOND);
    ClockSetTime(reloj, SET_INICIAL, sizeof(SET_INICIAL));
    ClockAddTime(reloj, CLOCK_SIZE);

    TEST_ASSERT_EQUAL_UINT8_ARRAY(reloj, ESPERADO, CLOCK_SIZE);
}
/*---  End of File  ---------------------------------------------------------------------------- */