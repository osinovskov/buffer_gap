#include <iostream>
#include "../common/buffer_gap.hpp"
#include <cassert>


void move(buffer_gap::char_dynarray array, std::size_t where)
{
    buffer_gap::insert_element(array, ' ', where);
}

void print(buffer_gap::char_dynarray array, std::size_t position)
{
    std::size_t size = buffer_gap::size(array);
    if (size==0){
        std::cout<<'|';
    }else{
        for(std::size_t i=1; i<= size;++i){
            if(i == position)
                std::cout<<'|';
            std::cout<<buffer_gap::read_element(array,i);
            if (( i+1 == position) && (position == size+1))
                std::cout<<'|';
        }
    }
    std::cout<<"\n";
}

int main()
{
    buffer_gap::char_dynarray array = buffer_gap::init();
    char element;
    std::size_t position = 1;
    while(std::cin>>element){
        switch (element) {
            case '<':
                if(position == 1)
                    break;
                move(array, --position);
                print(array,position);
                break;
            case '>':
                if(position == buffer_gap::size(array)+1)
                    break;
                move(array, ++position);
                print(array,position);
                break;
            case 'B':
                if (position == 1)
                    break;
                buffer_gap::delete_element(array,position-1);
                --position;
                print(array,position);
                break;
            case 'D'://delete не меняет полoжение курсора
                if (position == buffer_gap::size(array)+1)
                    break;
                buffer_gap::delete_element(array,position);
                print(array,position);
                break;
            default:
                buffer_gap::insert_element(array,element,position);
                ++position;
                print(array,position);
                break;
        }
    }
    buffer_gap::destroy(array);
}
