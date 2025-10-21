// ЛР-06, варіант 8 — клас трикутника з ++/--
// Visual Studio, wide console (українська)
// -----------------------------------------
#include <iostream>
#include <iomanip>
#include <cmath>
#include <stdexcept>
#include <limits>

// для wide-консолі Windows
#include <io.h>
#include <fcntl.h>

class Triangle {
    double a{}, b{}, c{}; // сторони

    static bool isTriangle(double x, double y, double z) {
        return (x > 0 && y > 0 && z > 0) &&
            (x + y > z) && (x + z > y) && (y + z > x);
    }

public:
    Triangle() = default;
    Triangle(double a, double b, double c) { set(a, b, c); }

    // Встановити сторони з валідацією
    void set(double A, double B, double C) {
        if (!isTriangle(A, B, C))
            throw std::invalid_argument("Некоректні довжини сторін трикутника");
        a = A; b = B; c = C;
    }

    // Отримати сторони
    double A() const { return a; }
    double B() const { return b; }
    double C() const { return c; }

    // Ввід з клавіатури (з повтором до коректності)
    void read() {
        using std::wcin; using std::wcout;
        while (true) {
            wcout << L"Введіть три сторони (через пробіл): ";
            double A, B, C;
            if (!(wcin >> A >> B >> C)) {
                wcout << L"Помилка вводу. Спробуйте ще раз.\n";
                wcin.clear();
                wcin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');
                continue;
            }
            if (isTriangle(A, B, C)) {
                a = A; b = B; c = C;
                wcin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');
                break;
            }
            wcout << L"Це не трикутник (перевірте додатність і нерівності трикутника). Спробуйте ще раз.\n";
        }
    }

    // Вивід у консоль
    void print() const {
        using std::wcout;
        wcout << L"Трикутник: a=" << a << L", b=" << b << L", c=" << c << L"\n";
    }

    // Периметр
    double perimeter() const { return a + b + c; }

    // Площа (формула Герона)
    double area() const {
        double p2 = perimeter() / 2.0;
        return std::sqrt(p2 * (p2 - a) * (p2 - b) * (p2 - c));
    }

    // Префіксний ++ : збільшує всі сторони на 1 (валідність зберігається)
    Triangle& operator++() {
        double A = a + 1, B = b + 1, C = c + 1;
        // Додавання 1 до всіх сторін зберігає нерівності трикутника, але перевіримо на всяк.
        if (!isTriangle(A, B, C))
            throw std::logic_error("Операція ++ зробила трикутник некоректним");
        a = A; b = B; c = C;
        return *this;
    }

    // Префіксний -- : зменшує всі сторони на 1 (перевірка коректності обов'язкова)
    Triangle& operator--() {
        double A = a - 1, B = b - 1, C = c - 1;
        if (!isTriangle(A, B, C))
            throw std::logic_error("Операція -- призводить до некоректного трикутника");
        a = A; b = B; c = C;
        return *this;
    }
};

int main() {
    // wide-ввід/вивід для української в Windows-консолі
    (void)_setmode(_fileno(stdout), _O_U16TEXT);
    (void)_setmode(_fileno(stdin), _O_U16TEXT);

    using std::wcout; using std::fixed; using std::setprecision;

    wcout << fixed << setprecision(4);
    wcout << L"=== ЛР-06, варіант 8: Клас трикутника ===\n\n";

    try {
        Triangle t;
        // 1) Ввід і вивід
        t.read();
        wcout << L"\nПочаткові дані:\n";
        t.print();

        // 2) Периметр і площа
        wcout << L"Периметр: " << t.perimeter() << L"\n";
        wcout << L"Площа:    " << t.area() << L"\n";

        // 3) Демонстрація ++
        wcout << L"\nПісля префіксного ++:\n";
        ++t;
        t.print();
        wcout << L"Периметр: " << t.perimeter() << L"\n";
        wcout << L"Площа:    " << t.area() << L"\n";

        // 4) Демонстрація --
        wcout << L"\nПісля префіксного --:\n";
        --t;
        t.print();
        wcout << L"Периметр: " << t.perimeter() << L"\n";
        wcout << L"Площа:    " << t.area() << L"\n";
    }
    catch (const std::exception& ex) {
        // Якщо дані некоректні або операції роблять трикутник неможливим
        std::wcerr << L"\nПомилка: " << ex.what() << L"\n";
    }

    return 0;
}
