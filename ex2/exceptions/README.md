Синтаксис:

## MATH_EXCEPTION  - математическое исключение

======

## NULL_POINTER_EXCEPTION - исключение нулевого указателя

======
 
## TRY({code}) - в скобках в фигурных скобках пишем код, который нужно выполнить 

======

## CATCH(exc, code) - exc - исключение, code - код в фигурных скобках

======

## THROW(exc)  - exc - исключение,

======

## DELETE_FROM_STACK - удаление все со стека (Не нужно использовать, они вшиты в другие дефайны)

======

## SAFE_DELETE(var, NAME) - помечаем переменную, как нужную для удаление.  var - переменная, Name - название типа




Реализовано, что если вызвано исключение во время удаление из стека, завершаем работа программы.


Но вообще, можно было не добавлять этого, потому что в моем случае, стек бы отчистился до конца в любом случае