# Домашнее задание №3

## Сборка с помощью cmake:
```
$ git clone git@github.com:ur-os/decent_hw-3.git
$ cd decent_hw-3 && mkdir build && cd build
$ cmake ../
$ make
```
## Использование:
```
$ ./decent_hw_3 [split|recover]
```

### Split:
*stdin:*
```
key
n_share threshold
```
*stdout:*
```
key_shard_1
ket_shard_2
...
key_shard_n
```

### Recover:
*stdin:*
```
key_shard_1
ket_shard_2
...
key_shard_m
```
*stdout:
```
key
```

## Краткое описание:
Разделяет ключ на несколько шард-ключей, 
с некоторым пороговым значением.
При преъявлении прогового числа шард-ключей
восстанавливает исходный ключ.

## Тестовый пример:
### Split:
 - Ввели sha256 исходника нашей программы
 - Ввели на сколько шардов делим, и пороговое значение
![alter-text](https://sun9-34.userapi.com/jIns1YuFVexPQ4bcde5BTqyMUUa5InvtB42B8Q/lPFr0JQhmmk.jpg)
Получаем 12 ключей.
### Recover:
 - Через stdin вводим 7 ключей из предыдущего пункта
![alter-text](https://sun9-40.userapi.com/qiBqD6USEur0LWzFcKm-byXFgiYV2drvO4Nvcg/aY7Gkf7Ra64.jpg)
Получаем исходный ключ.
### Recover:
(демонстрация ошибки)
- Через stdin вводим 6 ключей из предыдущего пункта
![alter-text](https://sun9-21.userapi.com/vEFJeucbJXKyiBkDZJOGz6FhMH0fm2W48Qmg7A/0bjiMNNn2gQ.jpg)
Получаем мусор.

#### Собрка Crypto++ 8.3.0 для этого проекта: https://github.com/ur-os/decent_hw-2#crypto-830
