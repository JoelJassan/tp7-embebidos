/**
 * @file test_reloj.c
 * @author Joel Jassan <joeljassan@hotmail.com>
 * @brief Funciones de testing tipo TDD para las funciones de reloj.c
 * @date 2023-06-10
 *
 * @copyright Copyright (c) 2023. All rights reserved.
 *
 */

/* ---  Headers files inclusions  -------------------------------------------------------------- */

#include "reloj.h"
#include "unity.h"

/* ---  Macros definitions  -------------------------------------------------------------------- */

#define TICKS_PER_SECOND 5

#define SIMULATE_SECONDS(FUNCTION, VALUE)                                      \
  for (int count = 0; count < VALUE; count++) {                                \
    for (int indice = 0; indice < TICKS_PER_SECOND; indice++) {                \
      FUNCTION;                                                                \
    }                                                                          \
  }

#define SIMULATE_TICKS(FUNCTION, VALUE)                                        \
  for (int count = 0; count < VALUE; count++) {                                \
    FUNCTION;                                                                  \
  }

/*---  Private Function Implementation  -------------------------------------------------------- */

void setUp(void) {
  const uint8_t SET_INICIAL[] = {1, 2, 3, 4, 0, 0};
  clock_t reloj = ClockCreate(TICKS_PER_SECOND);
  ClockSetTime(reloj, SET_INICIAL, sizeof(SET_INICIAL));
}

/* ---  Testing Function Implementation  ------------------------------------------------------- */

// ‣ Al inicializar el reloj está en 00:00 y con hora invalida.
void test_start_up(void) {
  const uint8_t ESPERADO[] = {0, 0, 0, 0, 0, 0};
  uint8_t hora[CLOCK_SIZE] = {0xFF};
  clock_t reloj = ClockCreate(TICKS_PER_SECOND);

  TEST_ASSERT_FALSE(ClockGetTime(reloj, hora, CLOCK_SIZE));
  TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, hora, CLOCK_SIZE);
}

// ‣ Al ajustar la hora el reloj queda en hora y es válida.
void test_adjust_time(void) {
  const uint8_t ESPERADO[] = {1, 2, 3, 4, 0, 2};
  uint8_t hora[CLOCK_SIZE] = {0xFF};
  clock_t reloj = ClockCreate(TICKS_PER_SECOND);

  TEST_ASSERT_TRUE(ClockSetTime(reloj, ESPERADO, CLOCK_SIZE));
  TEST_ASSERT_TRUE(ClockGetTime(reloj, hora, CLOCK_SIZE));
  TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, hora, CLOCK_SIZE);
}

// ‣ Después de n ciclos de reloj la hora avanza un segundo, diez segundos, un
// minutos, diez minutos, una hora, diez horas, y un día completo.

// Aumenta la unidad de los segundos
void test_increment_uni_second(void) {
  uint8_t hora[] = {1, 2, 3, 4, 0, 0};
  const uint8_t ESPERADO[] = {1, 2, 3, 4, 0, 1};

  clock_t reloj = ClockCreate(TICKS_PER_SECOND);
  ClockSetTime(reloj, hora, CLOCK_SIZE);
  SIMULATE_SECONDS(ClockRefresh(reloj, CLOCK_SIZE), 1);

  TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, reloj, CLOCK_SIZE);
}

// Aumenta la decena de los segundos
void test_increment_dec_second(void) {
  uint8_t hora[] = {1, 2, 3, 4, 0, 9};
  const uint8_t ESPERADO[] = {1, 2, 3, 4, 1, 0};

  clock_t reloj = ClockCreate(TICKS_PER_SECOND);
  ClockSetTime(reloj, hora, CLOCK_SIZE);
  SIMULATE_SECONDS(ClockRefresh(reloj, CLOCK_SIZE), 1);

  TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, reloj, CLOCK_SIZE);
}

// Aumenta la unidad de segundos, con decenas de segundos en cuenta maxima
void test_increment_uni_second_with_max_dec(void) {
  uint8_t hora[] = {1, 2, 3, 4, 5, 0};
  const uint8_t ESPERADO[] = {1, 2, 3, 4, 5, 9};

  clock_t reloj = ClockCreate(TICKS_PER_SECOND);
  ClockSetTime(reloj, hora, CLOCK_SIZE);
  SIMULATE_SECONDS(ClockRefresh(reloj, CLOCK_SIZE), 9);

  TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, reloj, CLOCK_SIZE);
}

// Aumenta la unidad de los minutos
void test_increment_uni_min(void) {
  uint8_t hora[] = {1, 2, 3, 4, 5, 0};
  const uint8_t ESPERADO[] = {1, 2, 3, 5, 0, 0};

  clock_t reloj = ClockCreate(TICKS_PER_SECOND);
  ClockSetTime(reloj, hora, CLOCK_SIZE);
  SIMULATE_SECONDS(ClockRefresh(reloj, CLOCK_SIZE), 10);

  TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, reloj, CLOCK_SIZE);
}

// Aumenta la decena de los minutos
void test_increment_dec_min(void) {
  uint8_t hora[] = {1, 2, 4, 9, 5, 0};
  const uint8_t ESPERADO[] = {1, 2, 5, 0, 0, 0};

  clock_t reloj = ClockCreate(TICKS_PER_SECOND);
  ClockSetTime(reloj, hora, CLOCK_SIZE);
  SIMULATE_SECONDS(ClockRefresh(reloj, CLOCK_SIZE), 10);

  TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, reloj, CLOCK_SIZE);
}

// Aumenta la unidad de los minutos, con decenas en cuenta maxima
void test_increment_uni_min_with_max_dec(void) {
  uint8_t hora[] = {1, 2, 5, 3, 5, 9};
  const uint8_t ESPERADO[] = {1, 2, 5, 4, 0, 8};

  clock_t reloj = ClockCreate(TICKS_PER_SECOND);
  ClockSetTime(reloj, hora, CLOCK_SIZE);
  SIMULATE_SECONDS(ClockRefresh(reloj, CLOCK_SIZE), 9);

  TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, reloj, CLOCK_SIZE);
}

// Aumenta la unidad de las horas
void test_increment_uni_hour(void) {
  uint8_t hora[] = {1, 3, 5, 9, 5, 9};
  const uint8_t ESPERADO[] = {1, 4, 0, 0, 0, 8};

  clock_t reloj = ClockCreate(TICKS_PER_SECOND);
  ClockSetTime(reloj, hora, CLOCK_SIZE);
  SIMULATE_SECONDS(ClockRefresh(reloj, CLOCK_SIZE), 9);

  TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, reloj, CLOCK_SIZE);
}

// Aumenta la decena de las horas
void test_increment_dec_hour(void) {
  uint8_t hora[] = {1, 9, 5, 9, 5, 9};
  const uint8_t ESPERADO[] = {2, 0, 0, 0, 0, 8};

  clock_t reloj = ClockCreate(TICKS_PER_SECOND);
  ClockSetTime(reloj, hora, CLOCK_SIZE);
  SIMULATE_SECONDS(ClockRefresh(reloj, CLOCK_SIZE), 9);

  TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, reloj, CLOCK_SIZE);
}

// Aumenta la unidad de las horas, con decenas en cuenta maxima
void test_increment_uni_hour_with_max_dec(void) {
  uint8_t hora[] = {2, 2, 5, 9, 5, 9};
  const uint8_t ESPERADO[] = {2, 3, 0, 0, 0, 8};

  clock_t reloj = ClockCreate(TICKS_PER_SECOND);
  ClockSetTime(reloj, hora, CLOCK_SIZE);
  SIMULATE_SECONDS(ClockRefresh(reloj, CLOCK_SIZE), 9);

  TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, reloj, CLOCK_SIZE);
}

// Aumenta la unidad de horas para reiniciar todo a cero
void test_clock_to_zero(void) {
  uint8_t hora[] = {2, 3, 5, 9, 5, 9};
  const uint8_t ESPERADO[] = {0, 0, 0, 0, 0, 8};

  clock_t reloj = ClockCreate(TICKS_PER_SECOND);
  ClockSetTime(reloj, hora, CLOCK_SIZE);
  SIMULATE_SECONDS(ClockRefresh(reloj, CLOCK_SIZE), 9);

  TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, reloj, CLOCK_SIZE);
}

// Aumento en lugar aleatorio
void test_increment_random(void) {
  uint8_t hora[] = {0, 0, 0, 0, 0, 0};
  const uint8_t ESPERADO[] = {0, 0, 0, 0, 0, 5};

  clock_t reloj = ClockCreate(TICKS_PER_SECOND);
  ClockSetTime(reloj, hora, CLOCK_SIZE);
  SIMULATE_SECONDS(ClockRefresh(reloj, CLOCK_SIZE), (60 * 60 * 24 + 5));

  TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, reloj, CLOCK_SIZE);
}

/* Falta:
 * (-) limitar las horas que se pueden poner en set clock
 */

// ‣ Fijar la hora de la alarma y consultarla. Separo en dos metodos (set y get)
void test_start_up_alarm(void) {
  const uint8_t ESPERADO[] = {0, 0, 0, 0, 0, 0};
  uint8_t alarm_time[ALARM_SIZE] = {0xFF};
  clock_t reloj = ClockCreate(TICKS_PER_SECOND);

  TEST_ASSERT_FALSE(AlarmGetTime(reloj, alarm_time, ALARM_SIZE));
  TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, alarm_time, ALARM_SIZE);
}

void test_adjust_alarm(void) {
  const uint8_t ESPERADO[] = {1, 2, 4, 4, 0, 0};
  uint8_t alarm_time[ALARM_SIZE] = {0xFF};
  clock_t reloj = ClockCreate(TICKS_PER_SECOND);

  TEST_ASSERT_FALSE(AlarmSetTime(reloj, ESPERADO, ALARM_SIZE));
  TEST_ASSERT_FALSE(AlarmGetTime(reloj, alarm_time, ALARM_SIZE));
  TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO, alarm_time, ALARM_SIZE);
}

// ‣ Fijar la alarma y avanzar el reloj para que suene.
void test_activated_alarm(void) {
  const uint8_t hora[] = {0, 0, 0, 0, 0, 0};
  const uint8_t alarm_time[] = {1, 1, 3, 0, 0, 0};
  clock_t reloj = ClockCreate(TICKS_PER_SECOND);

  ClockSetTime(reloj, hora, CLOCK_SIZE);
  AlarmSetTime(reloj, alarm_time, ALARM_SIZE);

  TEST_ASSERT_TRUE(ActivateAlarm(reloj));
}

void test_simulate_clock_with_alarm_on(void) {
  const uint8_t hora[] = {0, 0, 0, 0, 0, 0};
  const uint8_t alarm_time[] = {1, 1, 3, 0, 0, 0};
  clock_t reloj = ClockCreate(TICKS_PER_SECOND);

  ClockSetTime(reloj, hora, CLOCK_SIZE);
  AlarmSetTime(reloj, alarm_time, ALARM_SIZE);
  ActivateAlarm(reloj);

  SIMULATE_SECONDS(ClockRefresh(reloj, CLOCK_SIZE), (60 * 60 * 11 + 60 * 30));

  TEST_ASSERT_EQUAL_UINT8_ARRAY(reloj, alarm_time, ALARM_SIZE);
  TEST_ASSERT_TRUE(TriggerAlarm(reloj));
}

// ‣ Fijar la alarma, deshabilitarla y avanzar el reloj para que no suene.
void test_simulate_clock_with_alarm_off(void) {
  const uint8_t hora[] = {0, 0, 0, 0, 0, 0};
  const uint8_t alarm_time[] = {1, 1, 3, 0, 0, 0};
  clock_t reloj = ClockCreate(TICKS_PER_SECOND);

  ClockSetTime(reloj, hora, CLOCK_SIZE);
  AlarmSetTime(reloj, alarm_time, ALARM_SIZE);
  DeactivateAlarm(reloj);

  SIMULATE_SECONDS(ClockRefresh(reloj, CLOCK_SIZE), (60 * 60 * 11 + 60 * 30));

  TEST_ASSERT_FALSE(TriggerAlarm(reloj));
  TEST_ASSERT_EQUAL_UINT8_ARRAY(reloj, alarm_time, ALARM_SIZE);
}

// ‣ Hacer sonar la alarma y posponerla.
void test_postpone_alarm(void) {
  const uint8_t hora[] = {0, 0, 0, 0, 0, 0};
  const uint8_t alarm_time[] = {0, 0, 3, 0, 0, 0};
  const uint8_t alarm_time_post[] = {0, 0, 3, 5, 0, 0};

  clock_t reloj = ClockCreate(TICKS_PER_SECOND);

  ClockSetTime(reloj, hora, CLOCK_SIZE);
  AlarmSetTime(reloj, alarm_time, ALARM_SIZE);
  ActivateAlarm(reloj);

  SIMULATE_SECONDS(ClockRefresh(reloj, CLOCK_SIZE), (60 * 30));
  TEST_ASSERT_TRUE(TriggerAlarm(reloj));
  TEST_ASSERT_FALSE(PostponeAlarm(reloj));
}

// ‣ Hacer sonar la alarma y cancelarla hasta el otro dia.
void test_cancel_alarm(void) {
  const uint8_t hora[] = {0, 0, 0, 0, 0, 0};
  const uint8_t alarm_time[] = {0, 0, 3, 0, 0, 0};

  clock_t reloj = ClockCreate(TICKS_PER_SECOND);

  ClockSetTime(reloj, hora, CLOCK_SIZE);
  AlarmSetTime(reloj, alarm_time, ALARM_SIZE);
  ActivateAlarm(reloj);

  SIMULATE_SECONDS(ClockRefresh(reloj, CLOCK_SIZE), (60 * 30));
  TEST_ASSERT_TRUE(TriggerAlarm(reloj));
  TEST_ASSERT_TRUE(CancelAlarm(reloj));
}

/* Falta:
 * (-) limitar las horas que se pueden poner en set alarm (mismo metodo que set
 * clock)
 * (+) togglear la alarma para encendido y apagado
 */

void test_is_half_count_clock(void) {
  clock_t reloj = ClockCreate(TICKS_PER_SECOND*2); //multiplico x2 para que siempre sea par

  TEST_ASSERT_FALSE (ClockRefresh(reloj, CLOCK_SIZE)); //1 = 1
  SIMULATE_TICKS(ClockRefresh(reloj, CLOCK_SIZE), TICKS_PER_SECOND - 2); //1 + 3 = 4
  TEST_ASSERT_FALSE (ClockRefresh(reloj, CLOCK_SIZE)); //1 + 3 + 1 = 5
  TEST_ASSERT_TRUE (ClockRefresh(reloj, CLOCK_SIZE)); //1 +3 + 1 + 1 = 6
  SIMULATE_TICKS(ClockRefresh(reloj, CLOCK_SIZE), TICKS_PER_SECOND - 3); // 8
  TEST_ASSERT_TRUE (ClockRefresh(reloj, CLOCK_SIZE)); // 9 
  TEST_ASSERT_FALSE (ClockRefresh(reloj, CLOCK_SIZE)); // 0
}

/*---  End of File  ---------------------------------------------------------------------------- */