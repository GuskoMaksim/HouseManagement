#pragma once

// Основной шаблон: по умолчанию типы разные
template <typename T, typename U>
struct is_same {
  static const bool value = false;
};

// Специализация шаблона: если типы одинаковы
template <typename T>
struct is_same<T, T> {
  static const bool value = true;
};
