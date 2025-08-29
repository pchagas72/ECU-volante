#ifndef STOPWATCH_H
#define STOPWATCH_H

// This is an "include guard". It prevents this file from being included more than once
// during compilation, which avoids redefinition errors. It is a critical best practice.

/**
 * @brief Initializes and starts the stopwatch and display tasks.
 * * This function creates the necessary FreeRTOS queue and tasks to run the stopwatch.
 * The display must be initialized before calling this function.
 */
void stopwatch_start(void);


#endif // STOPWATCH_H
