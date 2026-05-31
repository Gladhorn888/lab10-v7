/**
 * @file stack.h
 * @brief Динамический стек целых чисел на основе массива.
 *
 * Предоставляет операции push, pop, peek, проверки пустоты/заполненности
 * и автоматическое расширение при необходимости.
 *
 * Коды ошибок:
 * - STACK_SUCCESS (0)             — успешное выполнение
 * - STACK_ERROR_NULL (-1)         — передан NULL-указатель
 * - STACK_ERROR_EMPTY (-2)        — стек пуст (при pop/peek)
 * - STACK_ERROR_MEMORY (-3)       — ошибка выделения памяти
 * - STACK_ERROR_INVALID_CAP (-4)  — неверная начальная ёмкость
 */

#ifndef STACK_H
#define STACK_H

#ifdef __cplusplus
extern "C" {
#endif

/** Коды ошибок */
typedef enum {
    STACK_SUCCESS = 0,
    STACK_ERROR_NULL = -1,
    STACK_ERROR_EMPTY = -2,
    STACK_ERROR_MEMORY = -3,
    STACK_ERROR_INVALID_CAP = -4
} stack_error_t;

/** Дескриптор стека */
typedef struct stack_t stack_t;

/**
 * @brief Создаёт новый стек.
 * @param capacity начальная ёмкость (должна быть > 0)
 * @return указатель на stack_t или NULL при ошибке
 */
stack_t *stack_create(size_t capacity);

/**
 * @brief Уничтожает стек и освобождает память.
 * @param s указатель на стек (допустим NULL, тогда ничего не делает)
 */
void stack_destroy(stack_t *s);

/**
 * @brief Добавляет элемент на вершину стека.
 * При необходимости автоматически расширяет буфер вдвое.
 * @param s указатель на стек
 * @param value значение для добавления
 * @return код ошибки
 */
stack_error_t stack_push(stack_t *s, int value);

/**
 * @brief Извлекает элемент с вершины стека.
 * @param s указатель на стек
 * @param value [out] указатель для сохранения извлечённого значения (не NULL)
 * @return код ошибки
 */
stack_error_t stack_pop(stack_t *s, int *value);

/**
 * @brief Возвращает элемент с вершины без удаления.
 * @param s указатель на стек
 * @param value [out] указатель для сохранения значения
 * @return код ошибки
 */
stack_error_t stack_peek(const stack_t *s, int *value);

/**
 * @brief Проверяет, пуст ли стек.
 * @param s указатель на стек
 * @return 1 если пуст, 0 если нет, -1 при NULL-указателе
 */
int stack_is_empty(const stack_t *s);

/**
 * @brief Проверяет, заполнен ли стек (size == capacity).
 * Следующий push вызовет перераспределение памяти.
 * @param s указатель на стек
 * @return 1 если заполнен, 0 если нет, -1 при NULL-указателе
 */
int stack_is_full(const stack_t *s);

/**
 * @brief Возвращает текущее количество элементов.
 * @param s указатель на стек
 * @return размер или (size_t)-1 при NULL
 */
size_t stack_size(const stack_t *s);

/**
 * @brief Возвращает текущую ёмкость буфера.
 * @param s указатель на стек
 * @return ёмкость или (size_t)-1 при NULL
 */
size_t stack_capacity(const stack_t *s);

#ifdef __cplusplus
}
#endif

#endif // STACK_H
