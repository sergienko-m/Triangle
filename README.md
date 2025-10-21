# 🧮 Лабораторна робота №6 — Об’єктно-орієнтоване програмування  
**Тема:** Розробка програм з користувацькими класами.  
**Варіант:** 8  
**Автор:** Сергієнко Максим, група **Alk-43**

---

## 🎯 Мета роботи
Ознайомитися з принципами створення класів у C++ та їх використанням у програмах.  
Навчитися розробляти класи з конструкторами, методами, перевантаженням операторів і демонстрацією роботи з об’єктами.

---

## 🧩 Завдання варіанту 8
> **Створити клас трикутників.**  
> Членами класу є довжини сторін трикутника.  
> Методами класу є:
> - введення трикутника з клавіатури;  
> - виведення трикутника на екран;  
> - обчислення периметра та площі за формулою Герона.  
>
> **Перевантажити оператори:**  
> - префіксний `++` — збільшує сторони трикутника на 1;  
> - префіксний `--` — зменшує сторони трикутника на 1.  
>
> Написати програму, що демонструє роботу з класом.

---

## ⚙️ Алгоритм виконання
1. Оголосити клас `Triangle` з полями `a`, `b`, `c` — сторони трикутника.  
2. Реалізувати методи:
   - `read()` — введення сторін з клавіатури з перевіркою;  
   - `print()` — виведення на екран;  
   - `perimeter()` — обчислення периметра;  
   - `area()` — обчислення площі за формулою Герона.  
3. Перевантажити оператори `++` та `--`.  
4. У функції `main()` створити об’єкт класу, викликати методи та перевірити роботу операторів.

---

## 💻 Код програми

```cpp
#include <iostream>
#include <iomanip>
#include <cmath>
#include <stdexcept>
#include <limits>
#include <io.h>
#include <fcntl.h>

class Triangle {
    double a{}, b{}, c{};
    static bool isTriangle(double x, double y, double z) {
        return (x > 0 && y > 0 && z > 0) && (x + y > z) && (x + z > y) && (y + z > x);
    }
public:
    Triangle() = default;
    Triangle(double a, double b, double c) { set(a, b, c); }
    void set(double A, double B, double C) {
        if (!isTriangle(A, B, C))
            throw std::invalid_argument("Некоректні довжини сторін");
        a = A; b = B; c = C;
    }
    void read() {
        using std::wcin; using std::wcout;
        while (true) {
            wcout << L"Введіть три сторони: ";
            double A, B, C;
            if (!(wcin >> A >> B >> C)) {
                wcout << L"Помилка! Спробуйте ще раз.\\n";
                wcin.clear();
                wcin.ignore(std::numeric_limits<std::streamsize>::max(), L'\\n');
                continue;
            }
            if (isTriangle(A, B, C)) { a=A; b=B; c=C; break; }
            wcout << L"Це не трикутник!\\n";
        }
    }
    void print() const {
        std::wcout << L"Трикутник: a=" << a << L", b=" << b << L", c=" << c << L"\\n";
    }
    double perimeter() const { return a + b + c; }
    double area() const {
        double p2 = perimeter() / 2.0;
        return std::sqrt(p2 * (p2 - a) * (p2 - b) * (p2 - c));
    }
    Triangle& operator++() {
        double A = a + 1, B = b + 1, C = c + 1;
        if (!isTriangle(A, B, C))
            throw std::logic_error("Некоректний трикутник");
        a=A; b=B; c=C; return *this;
    }
    Triangle& operator--() {
        double A = a - 1, B = b - 1, C = c - 1;
        if (!isTriangle(A, B, C))
            throw std::logic_error("Некоректний трикутник");
        a=A; b=B; c=C; return *this;
    }
};

int main() {
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin),  _O_U16TEXT);

    Triangle t;
    t.read();
    std::wcout << L"\\nПочаткові дані:\\n";
    t.print();
    std::wcout << L"Периметр: " << t.perimeter() << L"\\n";
    std::wcout << L"Площа: " << t.area() << L"\\n";

    ++t;
    std::wcout << L"\\nПісля ++:\\n"; t.print();

    --t;
    std::wcout << L"\\nПісля --:\\n"; t.print();
}
