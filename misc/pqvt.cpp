template<typename T>
class VectorPQ {
    private: 
    vector<T> elem;
    CPUjob job; 
    public:
    // typename vector<T>::iterator iterator; 
    // typename vector<T>::iterator begin() {return elem.begin();}
    // typename vector<T>::iterator end() {return elem.end();}
    T getSize(); 
    bool isEmpty(); 
    void insert(const T data); 
    T removeMin(); 
    T& operator[](T index); 
};
struct EmptyDLList : public std::runtime_error {
  explicit EmptyDLList(char const* msg=nullptr): runtime_error(msg) {}
};
template<typename T> 
T VectorPQ<T>::getSize() {return elem.size();}
template<typename T>
bool VectorPQ<T>::isEmpty() {return (elem.size()==0);}

template<typename T>
void VectorPQ<T>::insert(const T data) {
    elem.push_back(data); 
}

template<typename T> 
T VectorPQ<T>::removeMin() {
    if (isEmpty()) {
        throw EmptyDLList("Empty list");
    }
    T min = *min_element(elem.begin(), elem.end());
    return min; 
}
template<typename T>
T& VectorPQ<T>::operator[](T index) {
    if (index > elem.getSize()) {
        throw invalid_argument("index out of bound"); 
    } 
    return elem[index]; 
}
