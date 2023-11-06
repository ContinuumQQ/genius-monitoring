# genius-monitoring


## Сборка

Программа напиана на ЯП Си

Для её сборки выполняем команду:
```
make
```

## Запуск

Для запуска сервера переходим в каталог server:
`cd server`

Указываем в конфигурации ip адрес и порт сервера 
`editor config.txt`

Запускаем сервер:
`./server`

Переходим в client:
`cd ../client`

Выполняем такие же действия с клиентом

## Логи

Каждую секунду в файл `log.txt` пишется информация об агенте:
```
[2023/11/6 11:36:39] Processor name: 12th Gen Intel(R) Core(TM) i5-12400.cpuMHz:1647.128 Thread(0).cpuMHz:1540.454 Thread(1).cpuMHz:1696.682 Thread(2).cpuMHz:1626.071 Thread(3).cpuMHz:1694.030 Thread(4).cpuMHz:1452.505 Thread(5).cpuMHz:1148.941 Thread(6).cpuMHz:1165.476 Thread(7).cpuMHz:2380.395 Thread(8).cpuMHz:2095.393 Thread(9).cpuMHz:2340.108 Thread(10).cpuMHz:1093.977 Thread(11).MemTotal:32627788kB.MemFree:22659312kB.MemAvailable:27253888kB.
```
