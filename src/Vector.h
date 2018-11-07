#ifndef AISDI_LINEAR_VECTOR_H
#define AISDI_LINEAR_VECTOR_H

#include <cstddef>
#include <initializer_list>
#include <stdexcept>

namespace aisdi {

    template<typename Type>
    class Vector {
    public:
        using difference_type = std::ptrdiff_t;
        using size_type = std::size_t;
        using value_type = Type;
        using pointer = Type *;
        using reference = Type &;
        using const_pointer = const Type *;
        using const_reference = const Type &;

        class ConstIterator;

        class Iterator;

        using iterator = Iterator;
        using const_iterator = ConstIterator;

        pointer container;
        size_type size;
        size_type capacity;

        void reallocateMemory(size_type newCapacity){
            pointer temp = new Type[newCapacity];
            for(size_type i=0;i<this->size;i++){
                temp[i]=this->container[i];
            }
            delete [] container;
            this->container=temp;
            this->capacity*=2;

        }

        Vector(): size(0), capacity(2) {
            this->container = new Type[2];
        }

        Vector(std::initializer_list<Type> l):Vector() {
            for(auto i=l.begin();i!=l.end();i++){
                this->append(*i);
            }
        }

        Vector(const Vector &other):Vector() {
            for(auto i=other.begin();i!=other.end();i++){
                this->append(*i);
            }
        }

        Vector(Vector &&other):container(nullptr), size(0), capacity(0) {
            std::swap(this->container,other.container);
            std::swap(this->size,other.size);
            std::swap(this->capacity,other.capacity);

        }

        ~Vector() {
            delete [] container;
        }

        Vector &operator=(const Vector &other) {
            if(this!=&other){
                this->erase(this->cbegin(),this->cend());
                for(auto i=other.begin();i!=other.end();i++){
                    this->append(*i);
                }
            }
            return *this;
        }

        Vector &operator=(Vector &&other) {
            if(this!=&other){

                std::swap(this->container,other.container);
                std::swap(this->size,other.size);
                std::swap(this->capacity,other.capacity);
                delete [] other.container;
                other.container= nullptr;
                other.capacity=0;
                other.size=0;
            }
            return *this;
        }

        bool isEmpty() const {
            return size==0;
        }

        size_type getSize() const {
            return size;
        }

        void append(const Type &item) {
            if(this->size+1>this->capacity){
                reallocateMemory(this->capacity*2);
            }
            this->container[size]=item;
            this->size++;

        }

        void prepend(const Type &item) {
            this->insert(this->cbegin(),item);
        }



        void insert(const const_iterator &insertPosition, const Type &item) {
            if(this->size+1>this->capacity) {
                pointer temp = new Type[this->capacity * 2];
                for(size_type i=0;i<insertPosition.index;i++){
                    temp[i]=this->container[i];
                }
                temp[insertPosition.index]=item;
                for(size_type i=insertPosition.index;i<this->size;i++){
                    temp[i+1]=this->container[i];
                }
                delete [] container;
                this->size++;
                this->container=temp;
            }
            else if(this->isEmpty()){
                this->append(item);
            }
            else {
                for(size_type i=this->size; i>insertPosition.index; i--){
                    this->container[i]=this->container[i-1];
                }
                this->container[insertPosition.index]=item;
                this->size++;
            }



        }

        Type popFirst() {
            if(this->isEmpty()) throw std::out_of_range("");
            value_type value = this->container[0];
            for(size_type i=1;i<this->size;i++){
                container[i-1]=container[i];
            }
            this->size--;
            return value;
        }

        Type popLast() {
            if(this->isEmpty()) throw std::out_of_range("");
            value_type value = this->container[this->size-1];
            this->size--;
            return value;
        }

        void erase(const const_iterator &possition) {
            if(this->isEmpty() || possition.index>=this->size) throw std::out_of_range("");

            for(auto i=possition.index;i<this->size-1;i++){
                container[i]=container[i+1];
            }
            this->size--;
        }

        void erase(const const_iterator &firstIncluded, const const_iterator &lastExcluded) {
            if(this->isEmpty()) throw std::out_of_range("");
            if(firstIncluded==lastExcluded) return;

            size_type counter=lastExcluded.index-firstIncluded.index;
            if(counter==this->size){
                this->size=0;
                return;
            }
            for(auto i=lastExcluded.index;i<this->size;i++){
                this->container[i-counter] = this->container[i];
            }
            this->size-=counter;
        }

        iterator begin() {
            return Iterator(ConstIterator(this,0));
        }

        iterator end() {
            return Iterator(ConstIterator(this,this->size));
        }

        const_iterator cbegin() const {
            return ConstIterator(this,0);
        }

        const_iterator cend() const {
            return ConstIterator(this,this->size);
        }

        const_iterator begin() const {
            return cbegin();
        }

        const_iterator end() const {
            return cend();
        }
    };

    template<typename Type>
    class Vector<Type>::ConstIterator {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = typename Vector::value_type;
        using difference_type = typename Vector::difference_type;
        using pointer = typename Vector::const_pointer;
        using reference = typename Vector::const_reference;

        const Vector* vector;
        size_type index;

        explicit ConstIterator(): vector(nullptr), index(0) {}

        ConstIterator(const Vector* v,size_type i): vector(v), index(i) {}

        reference operator*() const {
            if(this->vector->isEmpty() || this->index>this->vector->size+1) throw std::out_of_range("");

            return this->vector->container[index];
        }

        ConstIterator &operator++() {
            if(this->index+1>this->vector->size) throw std::out_of_range("");

            this->index++;
            return *this;
        }

        ConstIterator operator++(int) {
            ConstIterator temp(this->vector,this->index);

            this->operator++();
            return temp;
        }

        ConstIterator &operator--() {
            if(this->index==0) throw std::out_of_range("");

            this->index--;
            return *this;
        }

        ConstIterator operator--(int) {
            ConstIterator temp(this->vector,this->index);

            this->operator--();
            return temp;
        }

        ConstIterator operator+(difference_type d) const {
            if(this->index+d>this->vector->size) throw std::out_of_range("");

            ConstIterator temp(this->vector,this->index+d);
            return temp;
        }

        ConstIterator operator-(difference_type d) const {
            if(this->index-d<0) throw std::out_of_range("");

            ConstIterator temp(this->vector,this->index-d);
            return temp;
        }

        bool operator==(const ConstIterator &other) const {
            return this->vector==other.vector && this->index==other.index;
        }

        bool operator!=(const ConstIterator &other) const {
            return this->vector!=other.vector || this->index!=other.index;
        }
    };

    template<typename Type>
    class Vector<Type>::Iterator : public Vector<Type>::ConstIterator {
    public:
        using pointer = typename Vector::pointer;
        using reference = typename Vector::reference;

        explicit Iterator() {}

        Iterator(const ConstIterator &other)
                : ConstIterator(other) {}

        Iterator &operator++() {
            ConstIterator::operator++();
            return *this;
        }

        Iterator operator++(int) {
            auto result = *this;
            ConstIterator::operator++();
            return result;
        }

        Iterator &operator--() {
            ConstIterator::operator--();
            return *this;
        }

        Iterator operator--(int) {
            auto result = *this;
            ConstIterator::operator--();
            return result;
        }

        Iterator operator+(difference_type d) const {
            return ConstIterator::operator+(d);
        }

        Iterator operator-(difference_type d) const {
            return ConstIterator::operator-(d);
        }

        reference operator*() const {
            // ugly cast, yet reduces code duplication.
            return const_cast<reference>(ConstIterator::operator*());
        }
    };

}

#endif // AISDI_LINEAR_VECTOR_H
