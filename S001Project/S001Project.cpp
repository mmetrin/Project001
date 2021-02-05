#include <iostream>

int main()
{
	std::cout << "Hello World!\n";
	char a[256]; //1 строка
	char b[256]; // 2 строка
	char c[] = "%s";


	char result[514];
	__asm
	{
		//заполнение первой строки

		//копирование адреса (первый операнд - это регистр общего назначения, а второй - адрес ячейки памяти)
		lea esi, a

		//помещение в стек
		push esi

		lea eax, c
		push eax

		//вызов функции по адресу
		call scanf

		add esp, 8
		mov eax, -1

		//используем декремент (уменьшаем на единицу)
		dec esi

		//заполнение второй строки
		lea esi, b
		push esi
		lea eax, c
		push eax
		call scanf
		add esp, 8
		mov eax, -1
		dec esi

		//соединение
		lea esi, [a]
		lea edi, [result]

		b1:

		//данная инструкция загружает данные из источника (ESI) в аккумулятор (EAX)
		lods

			//cохраняет значение аккумулятора (EAX) по адресу приёмника
			stos

			//cmp используется для сравнения двух операндов
			cmp al, 0

			//переход, если не равно нулю с помощью jnz
			jnz b1

			lea esi, [b]
			dec edi

			b2 :
		lods
			stos
			cmp al, 0
			jnz b2

	}
	std::cout << result;

}

