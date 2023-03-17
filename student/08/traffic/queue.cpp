#include "queue.hh"

// Implement the member functions of Queue here

Queue::Queue(unsigned int cycle):
    first_(nullptr), last_(nullptr),
    is_green_(false), cycle_(cycle)
{

}

Queue::~Queue()
{
   while(first_ != nullptr)
    {
        Vehicle *vehicle_to_be_allocated = first_;
        first_ = first_->next;

        delete vehicle_to_be_allocated;
    }
}

void Queue::enqueue(const string &reg)
//CAI NAY CUNG CO DOAN NO PRINT
{
    if(is_green_ == false)
    {
        Vehicle *new_last = new Vehicle{reg, nullptr};

        //truong hop empty
        if(first_ == nullptr)
        {
            first_ = new_last;
            last_ = new_last;
        }
        else
        {
            last_->next = new_last;
            last_ = new_last;
        }

    }
    else
    {
        cout << "GREEN: The vehicle "<<reg<<" need not stop to wait"<<endl;
    }
}

void Queue::switch_light()
{
    if(is_green_ == false) //RED -> GREEN
        {
            if(first_ == nullptr) //empty
            {
                is_green_ = true;
                cout << "GREEN: No vehicles waiting in traffic lights" << endl;
            }

            else
            {
                cout << "GREEN: ";
                dequeue();
                cout<< endl;
            }
        }

    else
        {
            is_green_ = false;
            cout << "RED: No vehicles waiting in traffic lights" << endl;
        }
}

void Queue::reset_cycle(unsigned int cycle)
{
    cycle_ = cycle;
}

void Queue::print() const
{
    string vehicle_in_queue;
    string light;

    //check light
    if(is_green_ == true)
    {
        light = "GREEN: ";
        vehicle_in_queue = "No vehicles waiting in traffic lights";
    }
    else
    {
        light = "RED: ";
        if(first_ == nullptr)
        {
            vehicle_in_queue = "No vehicles waiting in traffic lights";
        }
        else
        {
            Vehicle *vehicle_to_be_printed = first_;
            while(vehicle_to_be_printed != nullptr)
            {
                vehicle_in_queue += " "+ vehicle_to_be_printed->reg_num;
                vehicle_to_be_printed = vehicle_to_be_printed->next;
            }
            vehicle_in_queue = "Vehicle(s)"+vehicle_in_queue+" waiting in traffic lights";
        }
    }
    cout << light << vehicle_in_queue <<endl;
}

void Queue::dequeue()
{
    if(first_ == nullptr)
    {
        return;
    }

    string vehicles_can_go = "";
    unsigned int i = 0;

    while(first_ != nullptr && i < cycle_)
    {
        Vehicle *vehicle_to_be_dequeued = first_;

        vehicles_can_go += " "+ vehicle_to_be_dequeued->reg_num;

        if ( first_ == last_ )
        {
           first_ = nullptr;
           last_ = nullptr;
        }

        else
        {
           first_ = first_->next;
        }

        delete vehicle_to_be_dequeued;
        i++;
    }
    cout << "Vehicle(s)"<<vehicles_can_go<<" can go on";
}
