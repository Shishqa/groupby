# GroupBy

> задание: [docs/assignment.md](./docs/assignment.md)

## Сборка

```
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

## Запуск (в папке build)

```
./bin/group <path> <key_idx> <agg_idx> <agg_type>
```

### Генерация данных

```
./bin/generate
```

### Тесты

```
cd tests
ctest
```

> Параметры памяти: [src/groupby/settings.hpp](./src/groupby/settings.hpp)
