//Осиновсков Илья, 10 вариант, СКБ-162_1

#ifndef BUFFER_GAP_HPP
#define BUFFER_GAP_HPP
#include <cstddef>

namespace buffer_gap {

    //struct char_dynarray_t;//неполный тип

    using char_dynarray = struct char_dynarray_t*;//указатель на неполный классовый тип, который описан в этом же описании

    using const_char_dynarray = const char_dynarray_t*;// Псевдоним типа "неизменяемый динамический массив" для соблюдения const-корректности

    char_dynarray init(); //Задание начального состояния. Ассимптотическая сложность: O(1). С передачей владения.

    std::size_t size(const_char_dynarray array);//Возвращение числа хранимых элементов. Ассимптотическая сложность: O(1)

    char read_element(const_char_dynarray array, std::size_t i);//Чтение символа из заданной позиции. Ассимптотическая сложность: O(1)

    void insert_element(char_dynarray array, char element, std::size_t where);//Вставка символа в заданную позицию. Ассимптотическая сложность: амортизированная O(1)

    void delete_element(char_dynarray array, std::size_t where);//Удаление символа из заданной позиции. Ассимптотическая сложность: O(1)

    bool compare_dynarray(const_char_dynarray array1, const_char_dynarray array2);//Сравнение содержимого двух буферных окон. Ассимптотическая сложность: O(n)

    void destroy(char_dynarray array);//удаление выделенной под бурное окно памяти

}

#endif // BUFFER_GAP_HPP
