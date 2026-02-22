#include <stdio.h> 
#include <iomanip>


namespace NSorting{
    const double RANGE_MIN= - 100.0;
    const int STRING_CAPACITY = 65;
    const double RANGE_MAX = 100.0;
    const double RANGE = 200.0;
    const int BUCKETS_COUNT = 2000;

    typedef struct TItem
{
    double Key;
    char Value[STRING_CAPACITY];
    struct TItem* Next;
}; TItem;



    class IBucketSorter{
        public:
            virtual void AddItem(double key, const char* value) = 0;
            virtual void Sort() = 0;
            virtual void Print() = 0;
            virtual ~IBucketSorter() {}   
    };

    class TBucketSorter : public IBucketSorter {
        public:
        TBucketSorter(){
            Buckets = new TItem*[BUCKETS_COUNT];

            for (int i = 0; i < BUCKETS_COUNT; i++){
                Buckets[i] = nullptr;
            }
        }

        ~TBucketSorter(){
            for (int i = 0; i < BUCKETS_COUNT; i++){
                TItem* current = Buckets[i];
                while (current != nullptr){
                    TItem* temp = current;
                    current = current -> Next;
                    delete temp;
                }
            }
           delete[] Buckets;
        }


        void AddItem(double key, const char* value) override{
            int index = CalculateIndex(key);

            TItem* newItem = new TItem;
            newItem->Key = key;

            for (int i = 0; i < STRING_CAPACITY - 1; i++){
                newItem->Value[i] = value[i];
                if (value[i] == '\0'){
                    break;
                }
            }
            newItem -> Value[STRING_CAPACITY - 1] = '\0';

            newItem->Next = Buckets[index];
            Buckets[index] = newItem;
        }


        void Sort() override{
            for (int i = 0; i < BUCKETS_COUNT; i++){
                if (Buckets[i] != nullptr){
                    Buckets[i] = InsertionSortList(Buckets[i]);
                }
            }
        }

        void Print() override{
            for (int i = 0; i < BUCKETS_COUNT; i++){
                TItem* current = Buckets[i];
                while (current != nullptr){
                    printf("%g/t%s/n", current->Key, current->Value);
                    current = current -> Next;
                }
            }
        }


        private:

            TItem** Buckets;

            int CalculateIndex(double key){
                double normalized = (key - RANGE_MIN) / RANGE;
                if (normalized < 0.0){
                    normalized = 0.0;
                }
                if (normalized >= 1.0){
                    normalized = 0.99999;
                }
                return static_cast<int>(normalized * BUCKETS_COUNT);
            }

            TItem* InsertionSortList(TItem* head){
                if (head == nullptr || head->Next == nullptr){
                    return head;
                }
                TItem* sorted = nullptr;
                TItem* current = head;

                while (current != nullptr){
                    TItem* next = current -> Next;

                    if (sorted == nullptr || sorted->Key >= current->Key){
                        current-> Next = sorted;
                        sorted = current;
                    } else {
                        TItem* search = sorted;
                        while (search -> Next != nullptr && search->Next->Key < current->Key){
                            search = search->Next;
                        }
                        current->Next = search->Next;
                        search->Next = current;
                }
                current = next;
            }
            return sorted;
        }
    };
}

int main(){
    NSorting::TBucketSorter sorter;

    double tempKey;
    char tempValue[NSorting::STRING_CAPACITY];

    while(scanf("%lf\t%64[^\n]", &tempKey, tempValue) != EOF){
        sorter.AddItem(tempKey, tempValue);
    }
    sorter.Sort();
    
    sorter.Print();

    return 0;
}
