//
// Created by victor on 4/10/17.
//

#ifndef CAVITY_MT_HANDLE_H
#define CAVITY_MT_HANDLE_H


class handle {
public:

    static handle *Get_handle();
    static handle *handle_instance;
    int creat_new_alloc(int size, int addr);
//    struct alloc_str * get_alloc();
    void show();
    struct alloc_str{
        int size;
        int addr;
        struct alloc_str *next;
    }*alloc;

    handle();
    ~handle();
private:
    handle(handle const&);
    handle& operator=(handle const&);


};


#endif //CAVITY_MT_HANDLE_H
