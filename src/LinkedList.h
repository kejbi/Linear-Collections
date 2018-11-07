#ifndef AISDI_LINEAR_LINKEDLIST_H
#define AISDI_LINEAR_LINKEDLIST_H

#include <cstddef>
#include <initializer_list>
#include <stdexcept>

namespace aisdi {

    template<typename Type>
    class LinkedList {


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

    private:
        struct Element {
            value_type value;
            Element *next;
            Element *previous;
        };

    public:
        Element *first;
        Element *last;
        size_type size;



        LinkedList() {
            this->first = nullptr;
            this->last = nullptr;
            this->size = 0;
        }

        LinkedList(std::initializer_list<Type> l): LinkedList(){
            for(auto it = l.begin(); it!=l.end(); it++){
                this->append(*it);
            }
        }

        LinkedList(const LinkedList &other):LinkedList(){
            for(auto it = other.begin(); it!=other.end(); it++){
                this->append(*it);
            }
        }

        LinkedList(LinkedList &&other):LinkedList() {
            std::swap(this->first,other.first);
            std::swap(this->last,other.last);
            std::swap(this->size,other.size);
        }

        ~LinkedList() {
            if(first!= nullptr){
                erase(this->cbegin(),this->cend());
            }
        }

        LinkedList &operator=(const LinkedList &other) {
            if(this!=&other){
                this->erase(this->cbegin(),this->cend());
                for(auto it = other.begin(); it!=other.end(); it++){
                    this->append(*it);
                }
            }
            return *this;
        }

        LinkedList &operator=(LinkedList &&other) {
            if(this!=&other){
                this->erase(this->cbegin(),this->cend());
                std::swap(this->first,other.first);
                std::swap(this->last,other.last);
                std::swap(this->size,other.size);
            }
            return *this;
        }

        bool isEmpty() const {
            return size == 0;
        }

        size_type getSize() const {
            return size;
        }

        void append(const Type &item) {
            Element* temp;
            if(size==0){
                temp = new Element{item, nullptr, nullptr};
                first = temp;
                last = temp;
            }
            else{
                temp = new Element{item, nullptr, last};
                last -> next = temp;
                last = temp;
            }
            size++;

        }

        void prepend(const Type &item) {
            insert(this->cbegin(),item);
        }

        void insert(const const_iterator &insertPosition, const Type &item) {
            if(insertPosition.element == nullptr){
                this->append(item);
            }
            else{
                Element *temp;
                if(insertPosition.element==first){
                    temp = new Element{item, first, nullptr};
                    first->previous= temp;
                    first=temp;
                }
                else{
                    temp = new Element{item,insertPosition.element,insertPosition.element->previous};
                    insertPosition.element->previous->next = temp;
                    insertPosition.element->next->previous = temp;
                }

                size++;
            }
        }

        Type popFirst() {
            if(first==nullptr) throw std::out_of_range("No elements");
            value_type deletedValue = first -> value;
            if(size==1){
                delete first;
                first = nullptr;
                last = nullptr;
                size--;
                return deletedValue;
            }
            Element* temp=first->next;
            temp->previous= nullptr;
            delete first;
            first = temp;
            size--;
            return deletedValue;
        }

        Type popLast() {
            if(last==nullptr) throw std::out_of_range("No elements");
            value_type deletedValue = last -> value;
            if(size==1){
                delete last;
                first = nullptr;
                last = nullptr;
                size--;
                return deletedValue;
            }
            Element* temp=last->previous;
            temp->next= nullptr;
            delete last;
            last = temp;
            size--;
            return deletedValue;
        }

        void erase(const const_iterator &possition) {
            if(possition.element == nullptr) throw std::out_of_range("");
            if(possition.element == first){
                this->popFirst();
            }
            else if(possition.element == last){
                Element* temp=last->previous;
                temp->next= nullptr;
                delete last;
                last = temp;
                size--;
            }
            else{
                possition.element->previous->next=possition.element->next;
                possition.element->next->previous=possition.element->previous;

                delete possition.element;
                size--;
            }

        }

        void erase(const const_iterator &firstIncluded, const const_iterator &lastExcluded) {
            if(firstIncluded.element == nullptr) throw std::out_of_range("");
            if(firstIncluded == lastExcluded) return;
            Element *temp = firstIncluded.element;
            Element *nextTemp;
            Element *firstIncludedPrevious = firstIncluded.element->previous;
            while(temp !=lastExcluded.element){
                nextTemp=temp->next;
                delete temp;
                temp = nextTemp;
                size--;
            }
            if(temp == nullptr){
                if(firstIncludedPrevious == nullptr){
                    first= nullptr;
                    last = nullptr;
                    return;
                }
                firstIncludedPrevious->next= nullptr;
                last = firstIncludedPrevious;
            }
            else if(firstIncludedPrevious== nullptr){
                temp ->previous= nullptr;
                first = temp;
            }
            else{
                firstIncludedPrevious->next=temp;
                temp->previous=firstIncludedPrevious;
            }

        }

        iterator begin() {
            return Iterator(ConstIterator(first,this));
        }

        iterator end() {
            return Iterator(ConstIterator(nullptr,this));
        }

        const_iterator cbegin() const {
            return ConstIterator(first,this);
        }

        const_iterator cend() const {
            return ConstIterator(nullptr, this);
        }


        const_iterator begin() const {
            return cbegin();
        }

        const_iterator end() const {
            return cend();
        }
    };

    template<typename Type>
    class LinkedList<Type>::ConstIterator {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = typename LinkedList::value_type;
        using difference_type = typename LinkedList::difference_type;
        using pointer = typename LinkedList::const_pointer;
        using reference = typename LinkedList::const_reference;

        const LinkedList* list;
        Element *element;

        explicit ConstIterator():element(nullptr), list(nullptr)  {}

        ConstIterator(Element *element, const LinkedList* list):list(list),element(element) {}

        reference operator*() const {
            if(this->element!= nullptr){
                return this->element->value;

            }
            else{
                throw std::out_of_range("");
            }
        }

        ConstIterator &operator++() {
            if(this->element == nullptr) throw std::out_of_range("");

            this->element=this->element->next;
            return *this;

        }

        ConstIterator operator++(int) {
            ConstIterator temp(this->element,this->list);
            this->operator++();
            return temp;
        }

        ConstIterator &operator--() {
            if(this->list->isEmpty() || this->element==this->list->first) throw std::out_of_range("");
            if(this->element== nullptr){
                this->element=this->list->last;
            }
            else{
                this -> element = this -> element -> previous;
            }
            return *this;
        }

        ConstIterator operator--(int) {
            ConstIterator temp(this->element, this->list);
            this->operator--();
            return temp;
        }

        ConstIterator operator+(difference_type d) const {
            if(this->element == nullptr) throw std::out_of_range("");

            Element* temp = this -> element;
            for(auto i=0; i<d; i++){
                if(temp== nullptr) throw std::out_of_range("");
                temp = temp -> next;
            }

            return ConstIterator(temp,this->list);
        }

        ConstIterator operator-(difference_type d) const {
            if(this->list->isEmpty()) throw std::out_of_range("");

            Element* temp = this -> element;
            if(temp == nullptr){
                temp=this->list->last;
            }
            for(auto i=1; i<d; i++){
                if(temp->previous == nullptr) throw std::out_of_range("");
                else{
                    temp = temp -> previous;
                }
            }

            return ConstIterator(temp, this->list);
        }

        bool operator==(const ConstIterator &other) const {
            return (this -> element == other.element);

        }

        bool operator!=(const ConstIterator &other) const {
            return (this -> element != other.element);
        }
    };

    template<typename Type>
    class LinkedList<Type>::Iterator : public LinkedList<Type>::ConstIterator {
    public:
        using pointer = typename LinkedList::pointer;
        using reference = typename LinkedList::reference;

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

#endif // AISDI_LINEAR_LINKEDLIST_H
