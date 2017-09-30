#include <iostream>
#include "../common/buffer_gap.hpp"
#include <cassert>

int main()
{
    //проверка начального состояния буферного окна на пустоту
    {
        buffer_gap::char_dynarray array = buffer_gap::init();
        assert(size(array) == 0);
        buffer_gap::destroy(array);
    }

     //добавление в пустой массив, с левого/правого края непустого массива, в середину
    {
        buffer_gap::char_dynarray array = buffer_gap::init();

        buffer_gap::insert_element(array,'A',1);//Вставка в пустой массив
        assert(buffer_gap::read_element(array,1) == 'A');

        buffer_gap::insert_element(array,'B',2);//С правого края непустого массива
        assert(buffer_gap::read_element(array,2) == 'B');

        buffer_gap::insert_element(array,'C',1);//Вставка с левого края непустого массива
        assert(buffer_gap::read_element(array,1) == 'C');

        buffer_gap::insert_element(array,'D',2);//Вставка в середину массива
        assert(buffer_gap::read_element(array,2) == 'D');
        destroy(array);
    }

    //удаление с левого/правого края непустого массива, из середины.
    {
        buffer_gap::char_dynarray array = buffer_gap::init();

        for(std::size_t i=1; i<11; ++i)
            buffer_gap::insert_element(array,'a'+ i - 1,i);

        buffer_gap::delete_element(array,1);//Удаление с левого края непустого массива
        assert(((buffer_gap::read_element(array,1) == 'b')) && (buffer_gap::size(array) == 9));

        buffer_gap::delete_element(array, 9);
        assert(buffer_gap::size(array) == 8);//Удаление с правого края непустого массива

        buffer_gap::delete_element(array, 4);
        assert(buffer_gap::size(array) == 7);//Удаление из середины массива

        buffer_gap::destroy(array);
    }

    //Пара вставок/удалений в одну позицию подряд.
     {
        buffer_gap::char_dynarray array = buffer_gap::init();

        //Две вставки, два удаления
        for (std::size_t i=1; i<3; ++i){
            buffer_gap::insert_element(array,'A',1);
            assert(buffer_gap::read_element(array,i) == 'A');
        }

        for (std::size_t i = 1; i<3;++i){
            buffer_gap::delete_element(array,1);
            assert(buffer_gap::size(array) == 2-i);
        }

        destroy(array);
    }

    {//тест сравнения двух буферных окон
        buffer_gap::char_dynarray array1 = buffer_gap::init();
        buffer_gap::char_dynarray array2 = buffer_gap::init();
        for (std::size_t i=1; i<6; ++i){
            buffer_gap::insert_element(array1,'a'+i,i);
            buffer_gap::insert_element(array2,'a'+i,i);
        }
        assert(buffer_gap::compare_dynarray(array1,array2) == true);

        for (std::size_t i=1; i<6; ++i)
            buffer_gap::insert_element(array2,'a'+i+1,i);
        assert(buffer_gap::compare_dynarray(array1, array2) == false);

        destroy(array1);
        destroy(array2);
    }
}

