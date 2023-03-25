#include <iostream>
#include <memory>
#include "cards.hh"


Cards::Cards(): top_( nullptr ) {
}


void Cards::add(int id) {
    shared_ptr<Card_data> new_card
            = make_shared<Card_data>(Card_data{id, top_});
    top_ = new_card;
}

void Cards::print(ostream& s) {
    shared_ptr<Card_data> to_be_printed = top_;
    int nr = 1; //this is a counter

    while( to_be_printed != 0 ) {
      s << nr << ": " << to_be_printed->data << endl;
      to_be_printed = to_be_printed->next;
      ++nr;
    }
}

bool Cards::remove(int &id)
{
    //cai nay no remove top nhung van tra ve ket qua la true
    if(top_ == nullptr) return false;
    else
    {
        //tao mot cai shared_ptr de chi vao top_ va second_
        shared_ptr<Card_data> to_be_removed = top_;
;
        id = to_be_removed->data;
        top_ = top_->next;

        return true;
    }
}

void Cards::reverse()
{
    shared_ptr<Card_data> current = top_;
    shared_ptr<Card_data> before = nullptr;
    shared_ptr<Card_data> after = nullptr;

    while(current != nullptr)
    {   after = current->next;
        current->next = before;
        before = current; //bay gio current->next=current
        current = after;
    }
    top_ = before;
}

