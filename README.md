<div align="center">

# KSBoard

## Проект находится в процессе разработки

## Описание

</div>

Попытка реализовать аналог arduino на Российском микроконтроллере [K1986BE92F1I](https://ic.milandr.ru/products/mikrokontrollery_i_protsessory/32_razryadnye_mikrokontrollery/k1986ve92f1i/) от `АО "ПКК Миландр"`

<div align="center">

## Сборка

</div>

Для сборки используется `GNU Make` совместно с оффициальными инструментами пакета `arm-none-eabi` новейшей версии для разработки под архитектуру `ARM`

Команда для сборки прошивки:

```> make build```

Команда для загрузки прошивки:

```> make load PORT="[COM-Порт]"```

Команда для очистки прошивки:

```> make clean```
