//
// Created by victor on 4/10/17.
//

#ifndef CAVITY_MT_HANDLE_H
#define CAVITY_MT_HANDLE_H


class handle {
public:

    static handle *Get_handle();
    static handle *handle_instance;
    template <typename T>
    int creat_new_alloc(T size, T addr);
    struct alloc_str * get_alloc();
    void show();
    struct alloc_str{
        int size;
        int addr;
        struct alloc_str *next;
    }*alloc;

private:
    handle();
    handle(handle const&);
    handle& operator=(handle const&);
    ~handle();

};


#endif //CAVITY_MT_HANDLE_H
