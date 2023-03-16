#include "cards.hh"

// TODO: Implement the methods here


Cards::Cards():
    top_(nullptr)
{ 

}

Card_data *Cards::get_topmost()
{
    return top_;
}

void Cards::add(int id)
{
    Card_data *card = new Card_data{id, top_};
    top_ = card;
}

void Cards::print_from_top_to_bottom(ostream &s)
{
    Card_data *current = top_;
    int index = 1;

    while(current != nullptr)
    {
        s << index++ << ": " << current->data <<endl;
        current = current->next;
    }
}

bool Cards::remove(int &id)
{
    if(top_ == nullptr)
    {
        return false;
    }

    Card_data *temp = top_;
    top_ = temp->next;

    delete temp;

    return true; //chay function thanh cong
}

bool Cards::bottom_to_top()
{
    //check empty
    if(top_ == nullptr)
    {
        return false;
    }

    //when deck is size 1, we do nothing but return true
    if(top_->next == nullptr)
    {
        return true;
    }

    //dat ten the last 2 elements
    Card_data *last = top_;
    Card_data *second_last;

    //loop het ca list de tim den khi nao last-> nullptr
    while(last->next != nullptr)
    {
        second_last = last;
        last = last->next;
    }

    //dua len top
    second_last->next = nullptr;

    last->next = top_;
    top_ = last;

    return true;
}

bool Cards::top_to_bottom()
{
    //check empty
    if(top_ == nullptr)
    {
        return false;
    }

    //when deck is size 1, we do nothing but return true
    if(top_->next == nullptr)
    {
        return true;
    }

    //tim last truoc da
    //muon tim last thi phai dinh nghia top
    Card_data *last = top_, *temp;

    while(last->next != nullptr)
    {
        last = last->next;
    }

    //make the second top len top
    //make top xuong bottom
    last->next = top_;
    temp = top_;
    top_ = top_->next;
    temp->next = nullptr;

    return true;

}

void Cards::print_from_bottom_to_top(ostream &s)
{
    if(top_ == nullptr)
    {
        return;
    }
    recursive_print(top_, s);
}

Cards::~Cards()
{
    Card_data *current = top_;
    Card_data *temp;
    while(current != nullptr)
    {
        temp = current;
        current = current->next;
        delete temp;
    }
}

int Cards::recursive_print(Card_data *top, ostream &s)
{
    //tail-recursive, first find the last card
    //-> cascade of prints

    //trivial case: when pointer point to the bottom card
    if(top->next == nullptr)
    {
        s << 1 << ": " <<top->data <<endl;
        return 1;
    }

    //recursive tu top den bottom
    int index = recursive_print(top->next, s);
    s << ++index << ": " <<top->data<<endl;

    return index;
}
