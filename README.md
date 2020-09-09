# oop_exercise_01

	При работе программы запрашиваются две битовые строки, т.е. пользователь должен ввести по 128 нулей и единиц.
	Примеры таких строк есть в файле tests.txt
	Затем на экран выводится список доступных команд, некоторые из них реализованны как методы класса BitString, некоторые - как операторы.
	При выполнении некоторых команд потребуется также ввести дополнительны данные (к которой из двух строк применить команду, какой шаг сдвига использовать (для команд сдвига))
	Операцию проверки включения реализовал как проверку того, "стоят ли в строке 2 единицы на местах, на которых стоят единицы в строке 1", т.е., если говорить о строках как о битовых множествах, включены ли все элементы множества "строка 1" во множество "строка 2"
	
	В библиотеку ULL_arifm.cpp вынесены вспомогательные функции для работы с переменными типа unsigned long long.
	
	Добавил несколько скриншотов работающей программы с примерами ввода и разных команд
