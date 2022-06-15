/* Put your decleration here */
template<class T> class MultiSet{
    public:
        MultiSet(int size = 20);
        /* You should add other functions to make the structure work  */


        /* The following is required for this assignment */
        /* It is not complete, you should design the APIs by yourself */
        void insertion(T item);
        void deletion(T item);
        int retrieval(T item);

        void setunion(MultiSet<T> sets);
        void intersection(MultiSet<T> sets);
        void difference(MultiSet<T> sets);

    private:
        int numitems;
        T *repararray;

};


template<class T> class MultiSet_Chaining{
    public:
        MultiSet_Chaining(int size = 20);
        /* You should add other functions to make the structure work  */



        /* The following is required for this assignment */
        /* It is not complete, you should design the APIs by yourself */
        void insertion(T item);
        void deletion(T item);
        int retrieval(T item);

        void setunion(MultiSet_Chaining<T> sets);
        void intersection(MultiSet_Chaining<T> sets);
        void difference(MultiSet_Chaining<T> sets);

    private:
        int numitems;
        T *repararray;

};