/**
 * @file test_reloj.c
 * @author Joel Jassan <joeljassan@hotmail.com>
 * @brief Funciones de testing tipo TDD para las funciones de reloj.c
 * @date 2023-06-10
 * 
 * @copyright Copyright (c) 2023. All rights reserved.
 * 
 */


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
    const uint8_t SET_INICIAL[] = {1, 2, 3, 4, 0, 0};
    clock_t reloj = ClockCreate(TICKS_PER_SECOND);
    ClockSetTime(reloj, SET_INICIAL, sizeof(SET_INICIAL));
}

/* ---  Testing Function Implementation  ------------------------------------------------------- */



// ‣ Al inicializar el reloj está en 00:00 y con hora invalida.
void test_start_up(void) {
    const uint8_t ESPERADO [] = {0, 0, 0, 0, 0, 0};
    uint8_t hora [CLOCK_SIZE] = {0xFF};
    clock_t reloj = ClockCreate(TICKS_PER_SECOND);

    TEST_ASSERT_FALSE(ClockGetTime(reloj, hora, CLOCK_SIZE));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, hora, CLOCK_SIZE);
}


// ‣ Al ajustar la hora el reloj queda en hora y es válida.
void test_adjust_time (void) {
    const uint8_t ESPERADO [] = {1, 2, 3, 4, 0, 2};
    uint8_t hora [CLOCK_SIZE] = {0xFF};
    clock_t reloj = ClockCreate(TICKS_PER_SECOND);

    TEST_ASSERT_TRUE(ClockSetTime(reloj, ESPERADO, CLOCK_SIZE));
    TEST_ASSERT_TRUE(ClockGetTime(reloj, hora, CLOCK_SIZE));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, hora, CLOCK_SIZE);
}

// ‣ Después de n ciclos de reloj la hora avanza un segundo, diez segundos, un minutos, diez minutos, 
// una hora, diez horas, y un día completo.

// Aumenta la unidad de los segundos
void test_increment_uni_second(void) {
    uint8_t hora [] = {1, 2, 3, 4, 0, 1};
    const uint8_t ESPERADO [] = {1, 2, 3, 4, 0, 2};

    clock_t reloj = ClockCreate(TICKS_PER_SECOND);
    ClockSetTime(reloj, hora, CLOCK_SIZE);
    ClockAddTime(reloj, CLOCK_SIZE);

    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, reloj, CLOCK_SIZE);
}

// Aumenta la decena de los segundos
void test_increment_dec_second(void) {
    uint8_t hora [] = {1, 2, 3, 4, 0, 9};
    const uint8_t ESPERADO [] = {1, 2, 3, 4, 1, 0};

    clock_t reloj = ClockCreate(TICKS_PER_SECOND);
    ClockSetTime(reloj, hora, CLOCK_SIZE);
    ClockAddTime(reloj, CLOCK_SIZE);

    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, reloj, CLOCK_SIZE);
}

// Aumenta la unidad de segundos, con decenas de segundos en cuenta maxima
void test_increment_uni_second_with_max_dec(void) {
    uint8_t hora [] = {1, 2, 3, 4, 5, 8};
    const uint8_t ESPERADO [] = {1, 2, 3, 4, 5, 9};

    clock_t reloj = ClockCreate(TICKS_PER_SECOND);
    ClockSetTime(reloj, hora, CLOCK_SIZE);
    ClockAddTime(reloj, CLOCK_SIZE);

    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, reloj, CLOCK_SIZE);
}

// Aumenta la unidad de los minutos
void test_increment_uni_min(void) {
    uint8_t hora [] = {1, 2, 3, 4, 5, 9};
    const uint8_t ESPERADO [] = {1, 2, 3, 5, 0, 0};

    clock_t reloj = ClockCreate(TICKS_PER_SECOND);
    ClockSetTime(reloj, hora, CLOCK_SIZE);
    ClockAddTime(reloj, CLOCK_SIZE);

    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, reloj, CLOCK_SIZE);
}

// Aumenta la decena de los minutos
void test_increment_dec_min(void) {
    uint8_t hora [] = {1, 2, 4, 9, 5, 9};
    const uint8_t ESPERADO [] = {1, 2, 5, 0, 0, 0};

    clock_t reloj = ClockCreate(TICKS_PER_SECOND);
    ClockSetTime(reloj, hora, CLOCK_SIZE);
    ClockAddTime(reloj, CLOCK_SIZE);

    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, reloj, CLOCK_SIZE);
}

// Aumenta la unidad de los minutos, con decenas en cuenta maxima
void test_increment_uni_min_with_max_dec(void) {
    uint8_t hora [] = {1, 2, 5, 3, 5, 9};
    const uint8_t ESPERADO [] = {1, 2, 5, 4, 0, 0};

    clock_t reloj = ClockCreate(TICKS_PER_SECOND);
    ClockSetTime(reloj, hora, CLOCK_SIZE);
    ClockAddTime(reloj, CLOCK_SIZE);

    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, reloj, CLOCK_SIZE);
}

// Aumenta la unidad de las horas
void test_increment_uni_hour(void) {
    uint8_t hora [] = {1, 2, 5, 9, 5, 9};
    const uint8_t ESPERADO [] = {1, 3, 0, 0, 0, 0};

    clock_t reloj = ClockCreate(TICKS_PER_SECOND);
    ClockSetTime(reloj, hora, CLOCK_SIZE);
    ClockAddTime(reloj, CLOCK_SIZE);

    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, reloj, CLOCK_SIZE);
}

// Aumenta la decena de las horas
void test_increment_dec_hour(void) {
    uint8_t hora [] = {1, 9, 5, 9, 5, 9};
    const uint8_t ESPERADO [] = {2, 0, 0, 0, 0, 0};

    clock_t reloj = ClockCreate(TICKS_PER_SECOND);
    ClockSetTime(reloj, hora, CLOCK_SIZE);
    ClockAddTime(reloj, CLOCK_SIZE);

    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, reloj, CLOCK_SIZE);
}

// Aumenta la unidad de las horas, con decenas en cuenta maxima
void test_increment_uni_hour_with_max_dec(void) {
    uint8_t hora [] = {2, 2, 5, 9, 5, 9};
    const uint8_t ESPERADO [] = {2, 3, 0, 0, 0, 0};

    clock_t reloj = ClockCreate(TICKS_PER_SECOND);
    ClockSetTime(reloj, hora, CLOCK_SIZE);
    ClockAddTime(reloj, CLOCK_SIZE);

    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, reloj, CLOCK_SIZE);
}

// Aumenta la unidad de horas para reiniciar todo a cero
void test_clock_to_zero(void) {
    uint8_t hora [] = {2, 3, 5, 9, 5, 9};
    const uint8_t ESPERADO [] = {0, 0, 0, 0, 0, 0};

    clock_t reloj = ClockCreate(TICKS_PER_SECOND);
    ClockSetTime(reloj, hora, CLOCK_SIZE);
    ClockAddTime(reloj, CLOCK_SIZE);

    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, reloj, CLOCK_SIZE);
}

// Aumento en lugar aleatorio
void test_increment_random(void) {
    uint8_t hora [] = {1, 8, 2, 0, 5, 7};
    const uint8_t ESPERADO [] = {1, 8, 2, 0, 5, 8};

    clock_t reloj = ClockCreate(TICKS_PER_SECOND);
    ClockSetTime(reloj, hora, CLOCK_SIZE);
    ClockAddTime(reloj, CLOCK_SIZE);

    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, reloj, CLOCK_SIZE);
}

/* Falta:
 * (-) limitar las horas que se pueden poner en set clock
*/



// ‣ Fijar la hora de la alarma y consultarla. Separo en dos metodos (set y get)
void test_start_up_alarm(void) {
    const uint8_t ESPERADO [] = {0, 0, 0, 0, 0, 0};
    uint8_t alarm_time [CLOCK_SIZE] = {0xFF};
    clock_t alarma = ClockCreate(TICKS_PER_SECOND);

    TEST_ASSERT_FALSE(AlarmGetTime(alarma, alarm_time, CLOCK_SIZE));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, alarm_time, CLOCK_SIZE);
}

void test_adjust_alarm (void) {
    const uint8_t ESPERADO [] = {1, 2, 4, 4, 1, 2};
    uint8_t alarm_time [CLOCK_SIZE] = {0xFF};
    clock_t alarma = ClockCreate(TICKS_PER_SECOND);

    TEST_ASSERT_TRUE(AlarmSetTime(alarma, ESPERADO, CLOCK_SIZE));
    TEST_ASSERT_TRUE(AlarmGetTime(alarma, alarm_time, CLOCK_SIZE));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, alarm_time, CLOCK_SIZE);
}

/* Falta:
 * (-) limitar las horas que se pueden poner en set alarm
*/

/*---  End of File  ---------------------------------------------------------------------------- */