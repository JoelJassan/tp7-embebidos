/**
 * @file test_reloj.c
 * @author Joel Jassan <joeljassan@hotmail.com>
 * @brief Funciones de testing tipo TDD para las funciones de reloj.c
 * @date 2023-06-10
 * 
 * @copyright Copyright (c) 2023. All rights reserved.
 * 
 */


// ‣ Después de n ciclos de reloj la hora avanza un segundo,
// diez segundos, un minutos, diez minutos, una hora, diez
// horas y un día completo.
// ‣ Fijar la hora de la alarma y consultarla.
// ‣ Fijar la alarma y avanzar el reloj para que suene.
// ‣ Fijar la alarma, deshabilitarla y avanzar el reloj para no
// suene.
// ‣ Hacer sonar la alarma y posponerla.
// ‣ Hacer sonar la alarma y cancelarla hasta el otro dia..

/* ---  Headers files inclusions   ------------------------------------------------------------- */

#include "unity.h"
#include "reloj.h"

/*---  Testing Function Implementation  -------------------------------------------------------- */

// Al inicializar el reloj está en 00:00 y con hora invalida.
void test_start_up(void) {
    static const uint8_t ESPERADO [] = {0, 0, 0, 0, 0, 0};
    uint8_t hora [6] = {0xFF};

    clock_t reloj = ClockCreate(5);
    TEST_ASSERT_FALSE(ClockGetTime(reloj, hora, 6));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, hora, 6);
}


// Al ajustar la hora el reloj queda en hora y es válida.
void test_adjust_time (void) {
    static const uint8_t ESPERADO [] = {1, 2, 3, 4, 0, 0};
    uint8_t hora [6] = {0xFF};

    clock_t reloj = ClockCreate(5);
    TEST_ASSERT_TRUE(ClockSetTime(reloj, ESPERADO, 4));
    TEST_ASSERT_TRUE(ClockGetTime(reloj, hora, 6));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, hora, 6);
}
/*---  End of File  ---------------------------------------------------------------------------- */