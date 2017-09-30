#include "buffer_gap.hpp"
#include <iostream>
#include <cstring>
#include <cassert>

namespace buffer_gap {
    struct char_dynarray_t
    {
        char* buffer;
        char* buffer_end;
        char* gap;
        char* gap_end;
    };

    namespace  {
        std::size_t max(std::size_t a, std::size_t b)
        {
            return a>b?a:b;
        }

        void move_gap(char_dynarray array, std::size_t where)
        {
            //индексация начинается с нуля, а не с еденицы
            std::size_t gap_n = array->gap_end - array->gap;//Ширина окна
            std::size_t gap_i = array->gap - array->buffer;//Начало окна

            if (where == gap_i)
                return;
            if (where < gap_i){
                std::memmove(array->buffer + where + gap_n, array->buffer + where, gap_i-where);
                array->gap  = array->buffer + where;
                array->gap_end = array->buffer + where + gap_n;
            }else if(where > gap_i){
                std::memmove(array->gap, array->gap_end, where +gap_n - (array->gap_end-array->buffer) );
                array->gap += where - gap_i;
                array->gap_end += where - gap_i;
            }
        }
    }
    char_dynarray init()
    {
        char_dynarray array = new char_dynarray_t;
        array->buffer = array->gap = new char[1];
        array->buffer_end = array->buffer + 1;;
        array->gap_end = array->buffer_end;
        return array;
    }

    std::size_t size(const_char_dynarray array)
    {
        return (array->buffer_end - array->buffer - (array->gap_end-array->gap));
    }

    char read_element(const_char_dynarray array, std::size_t i)
    {
        --i;//индексация с 0
        assert(i <= size(array));
        if (i >= static_cast<std::size_t>(array->gap-array->buffer))
            i += array->gap_end-array->gap;
        return array->buffer[i];
    }

    void insert_element(char_dynarray array, char element, std::size_t where)
    {
         --where;
        assert(where <= size(array));
        if (array->gap_end - array->gap <= 1){
            std::size_t new_size = max((array->buffer_end-array->buffer)*3/2,4);
            std::size_t gap_size = new_size - size(array);
            char* new_buffer = new char[new_size];
            std::memmove(new_buffer,array->buffer, (array->gap - array->buffer));
            std::memmove(new_buffer + (array->gap - array->buffer) + gap_size, array->gap_end, array->buffer_end - array->gap_end);
            std::size_t gap_position = array->gap - array->buffer;
            delete[] array->buffer;
            array->buffer = new_buffer;
            array->buffer_end = new_buffer + new_size;
            array->gap = new_buffer + gap_position;
            array->gap_end = array->gap + gap_size;
        }
            move_gap(array,where);
            if(element != ' '){
            array->buffer[where] = element;
            array->gap++;
            }
    }

    void delete_element(char_dynarray array, std::size_t where)
    {
        --where;
        assert(where <= size(array)-1);
        move_gap(array,where+1);//ставлю окно справа от удаляемого элемента
        array->gap--;
    }

    bool compare_dynarray(const_char_dynarray array1, const_char_dynarray array2)
    {
        if (size(array1) != size(array2))
            return false;
        for(std::size_t i=1; i <= size(array1); ++i)//ведем индексацию с 1,так как в read_element есть --i
            if (read_element(array1,i) != read_element(array2,i))
                return false;
        return true;
    }

    void destroy(char_dynarray array)
    {
        delete[] array->buffer;
        delete array;
    }
}
