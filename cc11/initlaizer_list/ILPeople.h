#pragma once

#include <initializer_list>
#include "comm_include.h"

enum Gender {boy, girl};

class ILPeople
{
public:
    ILPeople();
    ~ILPeople();

public:
    //�� initializer_list<T> ��Ϊ�����Ĺ��캯��, ��֧���б��ʼ��
    ILPeople(initializer_list<pair<string, Gender>> l);

private:
    vector<pair<string, Gender>> data;
};

