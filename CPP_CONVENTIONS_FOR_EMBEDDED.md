# 1. Обязательные флаги компилятора (это основа)
Добавь в CMakeLists.txt:
```cmake
target_compile_options(${APP} PRIVATE
    -fno-exceptions
    -fno-rtti
    -fno-threadsafe-statics
    -fno-use-cxa-atexit          # не вызывает деструкторы глобальных объектов
    -ffreestanding               # или --specs=nano.specs
    -ffunction-sections
    -fdata-sections
    -Os                          # или -O2 + LTO
)

target_link_options(${APP} PRIVATE
    -Wl,--gc-sections
    -Wl,--print-memory-usage
)
```
Эти флаги убирают почти весь overhead C++ по сравнению с C.

# 2. Что можно / нельзя использовать

| Фича  | Можно?   | Влияние на размер         | Комментарий                             |
|-------|----------|---------------------------|-----------------------------------------|
| `std::array<T, N>` | Да       | Почти 0                   | Лучше C-массивов                        |
| `std::span<T>` (C++20) | Да       | 0                         | Zero-cost view                          |
| `constexpr` +  `consteval` | Да       | Часто уменьшает код       | Вычисления на этапе компиляции          |
| Шаблоны (templates) | Да, осторожно | Может раздуть             | Используй CRTP, не плодите типы         | 
| Классы + RAII      | **Сильно да** | Обычно уменьшает код      | Лучше чем ручной cleanup в C            |
| `std::vector / std::string` | Только с custom allocator         | + heap + overhead         | Лучше `std::array` или static pool      |
| `new / delete` | Нет (или custom)         | Добавляет heap + malloc   | Замени на placement new + static buffer |
| Virtual functions      | Избегать         | vtable + RTTI             | Используй CRTP                          |
| Глобальные объекты с ctor      | Избегать         | Добавляет `.init_array` + RAM | Делай explicit init()                   |
| `std::map / unordered_map` | Нет         | Большой overhead                          | -                                       |

# 3. Правила кодирования (чтобы размер ≈ C)

1. ### Всё статическое или stack-based
- `std::array`, `std::span`, `std::pmr::monotonic_buffer_resource` (C++17) с static буфером.  
- Никакого `new` в runtime, если не сделал свой pool-аллокатор.

2. ### Нет глобальных конструкторов
Плохо:
```c++
static SomeClass obj;        // ctor вызывается до main
```
Хорошо:
```c++
static SomeClass* obj = nullptr;
void init() { obj = new (static_buffer) SomeClass(); }  // placement new
```
3. ### RAII — твой лучший друг
Это единственная фича, которая обычно уменьшает размер кода по сравнению с C   
(автоматический unlock, disable interrupt и т.д.).
4. ### Шаблоны — только когда выгодно
- Хорошие: fixed-size queue, ring buffer, pinmux helper.
- Плохие: шаблон с 10 разными типами → 10 копий кода.
5. ### CRTP вместо виртуальных функций
Zero-overhead polymorphism.
6. ### Всё помечай `noexcept`
```c++
void critical() noexcept;
```
7. ### Используй `[[nodiscard]]`, `static_assert`, `constexpr`
   Это не добавляет размер, но ловит ошибки на этапе компиляции.
8. ### Избегай std:: алгоритмов, если они тянут большой код
Часто проще написать свой for-цикл (особенно на M0/M3).

# 4. Полезные паттерны (дают преимущество над C)

_ Static Pool Allocator + `placement new`  
_ Policy-Based Design (вместо наследования)  
_ Type Erasure с `std::span` или `void*` (очень лёгкий)  
_ Compile-time registers (как у тебя уже сделано)  
_ Zero-cost abstractions (`std::span`, `std::array`, `constexpr if`)  