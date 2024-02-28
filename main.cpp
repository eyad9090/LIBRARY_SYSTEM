#include<bits/stdc++.h>
using namespace std;
struct Helper
{
    char to_upper(char c)
    {
        if(is_lower(c))
        {
            c=(char)(c-'a'+'A');
        }
        return c;
    }
    char to_lower(char c)
    {
        if(is_upper(c))
        {
            c=(char)(c-'A'+'a');
        }
        return c;
    }
    char is_lower(char c)
    {
        if(c>='a'&&c<='z')
            return true;
        return false;
    }
    char is_upper(char c)
    {
        if(c>='A'&&c<='Z')
            return true;
        return false;
    }

    string to_lower(string str)
    {
        for(char &c:str)
        {
            if(is_upper(c))
            {
                c=to_lower(c);
            }
        }
        return str;
    }


    int string_to_integer(string number)
    {
        int ans=0;
        for(int i=0; i<number.size(); i++)
        {
            if(number[i]>='0'&&number[i]<='9')
            {
                ans=ans*10+(number[i]-'0');
            }
            else
                return -1;
        }
        return ans;
    }

    int get_integer_in_range(int range_start,int range_end)
    {
        fflush(stdin);
        string choice;
        getline(cin,choice);
        int ans=-1;
        while(ans==-1)
        {
            ans=string_to_integer(choice);
            if(ans>=range_start&&ans<=range_end)
            {
                return ans;
            }
            else
            {
                cout<<"Invalid\n";
                cout<<"Please enter valid number in range["
                    <<range_start<<"-"<<range_end<<"]: ";
                fflush(stdin);
                getline(cin,choice);
                ans=-1;
            }
        }
    }

    bool is_only_character_space(string str)
    {
        for(char c:str)
        {
            if( (c>='a'&&c<='z') || (c>='A'&&c<='Z')||c==' ' )
            {
                continue;
            }
            return false;
        }
        return true;
    }
    string get_character_space(string message)
    {
        cout<<message;
        string str;
        fflush(stdin);
        getline(cin,str);
        while(!is_only_character_space(str))
        {
            cout<<"invalid\n";
            cout<<message;
            cin>>str;
        }
        str=to_lower(str);
        return str;
    }
};

Helper helper;
struct User
{
    int id;
    string name;
    static int global_id;
    User()
    {
        id=0;
        name="";
    }
    void get_id()
    {
        id=global_id++;
    }
    void get_name()
    {
        name=helper.get_character_space("Enter your name:");
    }
    void get_data()
    {
        get_id();
        get_name();
    }
    void print_user()
    {
        cout<<"Id:"<<id<<"\t"<<"name:"<<name<<"\n";
    }
    bool is_equal(string &user_name)
    {
        if(name==user_name)
        {
            return true;
        }
        return false;
    }
    bool is_equal(User &user)
    {
        if(name==user.name
           &&id==user.id)
        {
            return true;
        }
        return false;
    }
};
int User::global_id=1;
struct Book
{
    int id;
    string name;
    int quantity;
    int user_sz;
    User users[100];
    static int global_id;
    Book()
    {
        id=0;
        name="";
        quantity=0;
        user_sz=0;
    }
    void get_id()
    {
        id=global_id++;
    }
    void get_quantity()
    {
        cout<<"Enter your quantity:";
        quantity=helper.get_integer_in_range(1,100);
    }
    void get_name()
    {
        name=helper.get_character_space("Enter your book name:");
    }
    void get_data()
    {
        get_id();
        get_name();
        get_quantity();
    }
    void print_book()
    {
        cout<<"Id:"<<id<<"\t"<<"Name:"<<name<<"\t"<<"Quantity:"<<quantity<<"\n";
    }
    bool is_equal(Book &book)
    {
        if(book.id==book.id&&
                book.name==book.name
                &&book.quantity==book.quantity)
        {
            return true;
        }
        return false;
    }
    bool is_equal(string &book_name)
    {
        if(name==book_name)
        {
            return true;
        }
        return false;
    }
    bool is_prefix(string &prefix)
    {
        if(prefix.size()>name.size())
        {
            return false;
        }
        prefix=helper.to_lower(prefix);
        string lower_name=helper.to_lower(name);
        for(int i=0; i<prefix.size(); i++)
        {
            if(prefix[i]!=lower_name[i])
            {
                return false;
            }
        }
        return true;
    }
    void print_users()
    {
        if(user_sz==0)
        {
            cout<<"No users borrowed this book\n";
        }
        for(int i=0; i<user_sz; i++)
        {
            users[i].print_user();
        }
    }
    bool borrow_book(User &user)
    {
        if(quantity==0)
        {
            return false;
        }
        users[user_sz++]=user;
        quantity--;
        return true;
    }
    int get_idx_user(User &user)
    {
        for(int i=0;i<user_sz;i++)
        {
            if(users[i].is_equal(user))
            {
                return i;
            }
        }
        return -1;
    }
    bool delete_user(User &user)
    {
        int idx=get_idx_user(user);
        if(idx==-1)
        {
            return false;
        }
        for(int i=idx;i<user_sz-1;i++)
        {
            users[i]=users[i+1];
        }
        user_sz--;
        return true;

    }
    void return_book(User &user)
    {
        if(delete_user(user))
        {
            quantity++;
        }
    }
    static bool comp_book_id(Book &book1,Book &book2)
    {
        return book1.id<book2.id;
    }
    static bool comp_book_name(Book &book1,Book &book2)
    {
        return book1.name<book2.name;
    }

};
int Book::global_id=1;

struct library_system
{
    int book_sz;
    int user_sz;
    Book books[500];
    User users[500];
    library_system()
    {
        book_sz=0;
        user_sz=0;
    }
    bool is_libary_full()
    {
        return book_sz==1000;
    }
    void add_book()
    {
        cout<<"-----Add book option------\n\n";
        if(is_libary_full())
        {
            cout<<"Library is full\n";
            return ;
        }
        Book book;
        book.get_data();
        books[book_sz++]=book;
    }
    void search_by_prefix()
    {
        cout<<"------search by prefix--------\n\n";
        string prefix=helper.get_character_space("Enter your prefix:");
        bool flag=false;
        for(int i=0; i<book_sz; i++)
        {
            Book book=books[i];
            if(book.is_prefix(prefix))
            {
                book.print_book();
                flag=true;
            }
        }
        if(!flag)
        {
            cout<<"Nothing\n";
        }
    }
    void print_books_id_sorted()
    {
        cout<<"-----Printing books by id----------\n\n";
        if(!book_sz)
        {
            cout<<"Empty library\n";
            return ;
        }
        sort(books,books+book_sz,Book::comp_book_id);
        for(int i=0; i<book_sz; i++)
        {
            books[i].print_book();
        }
    }
    void print_books_name_sorted()
    {
        cout<<"---printing books by name------------\n\n";
        if(!book_sz)
        {
            cout<<"Empty library\n";
            return ;
        }
        sort(books,books+book_sz,Book::comp_book_name);
        for(int i=0; i<book_sz; i++)
        {
            books[i].print_book();
        }
    }
    void print_users_who_borrow()
    {
        cout<<"-------------Print users-------\n\n";
        string book_name=helper.get_character_space("Enter book name:");
        int idx=get_book(book_name);
        books[idx].print_users();
    }
    void add_user()
    {
        cout<<"-----add user----------------\n\n";
        User user;
        user.get_data();
        users[user_sz++]=user;
    }
    bool is_valid_user(string &user_name)
    {
        for(int i=0;i<user_sz;i++)
        {
            if(users[i].is_equal(user_name))
            {
                return true;
            }
        }
        return false;
    }
    bool is_valid_book(string &book_name)
    {
        for(int i=0;i<book_sz;i++)
        {
            if(books[i].is_equal(book_name))
            {
                return true;
            }
        }
        return false;
    }
    int get_user(string &user_name)
    {
        int idx=-1;
        for(int i=0;i<user_sz;i++)
        {
            if(users[i].is_equal(user_name))
            {
                idx=i;
                break;
            }
        }
        return idx;
    }
    int get_book(string &book_name)
    {
        int idx=-1;
        for(int i=0;i<book_sz;i++)
        {
            if(books[i].is_equal(book_name))
            {
                idx=i;
                break;
            }
        }
        return idx;
    }
    void borrow_book()
    {
        cout<<"---------Borrow book------------------\n\n";
        string user_name;
        string book_name;
        do
        {
            user_name=helper.get_character_space("Enter user name:");
            book_name=helper.get_character_space("Enter book name:");
        }while(!is_valid_user(user_name)||
               !is_valid_book(book_name));

        User user=users[get_user(user_name)];
        if(!books[get_book(book_name)].borrow_book(user))
        {
            cout<<"There is not enough quantity of this book\n";
        }
        else
        {
            cout<<"Successfully borrowed\n";
        }
    }
    void return_book()
    {
        cout<<"---------Return book------------------\n\n";
        string user_name;
        string book_name;
        do
        {
            user_name=helper.get_character_space("Enter user name:");
            book_name=helper.get_character_space("Enter book name:");
        }while(!is_valid_user(user_name)||
               !is_valid_book(book_name));
        User user=users[get_user(user_name)];
        books[ get_book(book_name)].return_book(user);
        cout<<"Book returned successfully\n";
    }
    void print_users()
    {
        cout<<"------print users------------------\n\n";
        if(user_sz==0)
        {
            cout<<"There is no users\n";
            return ;
        }
        for(int i=0;i<user_sz;i++)
        {
            users[i].print_user();
        }
    }
    void menu()
    {
        cout<<"1) Add book\n"
            <<"2) Search book by prefix\n"
            <<"3) Print who borrowed book by name\n"
            <<"4) Print library by id\n"
            <<"5) Print library by name\n"
            <<"6) Add user\n"
            <<"7) User borrow book\n"
            <<"8) User return book\n"
            <<"9) Print users\n"
            <<"10) Exit\n";
    }
    void start_program()
    {
        while(true)
        {
            cout<<"-------menu-----------\n\n";
            menu();
            cout<<"Please enter you choice:";
            int choice=helper.get_integer_in_range(1,10);
            if(choice==1)
            {
                add_book();
            }
            else if(choice==2)
            {
                search_by_prefix();
            }
            else if(choice==3)
            {
                print_users_who_borrow();
            }
            else if(choice==4)
            {
                print_books_id_sorted();
            }
            else if(choice==5)
            {
                print_books_name_sorted();
            }
            else if(choice==6)
            {
                add_user();
            }
            else if(choice==7)
            {
                borrow_book();
            }
            else if(choice==8)
            {
                return_book();
            }
            else if(choice==9)
            {
                print_users();
            }
            else if(choice==10)
            {
                return;
            }
        }
    }
};


int main()
{
    library_system l=library_system();
    l.start_program();
    return 0;
}
