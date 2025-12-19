#pragma once

enum class Operation {
    MULTIPLICATION,
    DIVISION,
    SUBTRACTION,
    ADDITION,
    POWER,
};

enum class ControlKey {
    EQUALS,     // Кнопка "Равно".
    CLEAR,      // Кнопка "C - сброс/очистить".
    MEM_SAVE,   // Кнопка "MS" - записать в память.
    MEM_LOAD,   // Кнопка "MR"  - считать из памяти.
    MEM_CLEAR,  // Кнопка "MC" - очистить память.
    PLUS_MINUS, // Кнопка "+-".
    BACKSPACE,  // Кнопка "Стереть последний символ".
    DOT_KEY,    // Десятичная точка
};
