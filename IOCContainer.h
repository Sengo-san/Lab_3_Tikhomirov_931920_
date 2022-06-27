#ifndef IOCCONTAINER_H
#define IOCCONTAINER_H

//#include <QCoreApplication>
// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <functional>
#include <cstdlib>
#include <memory>
#include <map>

using namespace std;

/*

Получение кода типа;

Прежде чем мы сможем безопасно сохранить способ получения класса,
подписывающегося на определенный интерфейс, мы должны выделить для этого код типа.

В предложенной реализации  реализации контейнера IOC  есть статическая целочисленная переменная,
которая определяет идентификатор следующего типа, который будет выделен,
и экземпляр статической локальной переменной для каждого типа,
к которому можно обратиться, вызвав метод GetTypeID.
*/

class IOCContainer

{

    static int s_typeId;
public:
    //one typeid per type

    template<typename T>
    static int GetTypeID()
    {

        static int typeId = s_typeId++;
        return typeId;
    }

    /*
     Получение экземпляров объекта;

     Теперь, когда  есть идентификатор типа, мы должны иметь возможность хранить какой-то фабричный объект,
     чтобы показать тот факт, что мы не знаем, как создать объект.(так как мы не знаем как создать объект)

     Хранить все фабрики в одной коллекции, для этого выбираем абстрактный базовый класс,
     из которого будут производиться фабрики, и реализацию, которая захватывает функтор для последующего вызова.
     Можно использовать std :: map для хранения фабрик, а же можно рассмотреть  другие варианты для эффективности.

    */
    class FactoryBase

    {

    public:

        virtual ~FactoryBase() {}

    };

    //todo: consider sorted vector

    map<int, shared_ptr<FactoryBase>> factories;

    template<typename T>

    class CFactory : public FactoryBase

    {
        //std::function
        std::function<std::shared_ptr<T>()> functor;
    public:
        ~CFactory() {}

        CFactory(std::function<std::shared_ptr<T>()> functor)

            :functor(functor)

        {

        }

        std::shared_ptr<T> GetObject()
        {
            return functor();
        }

    };

    template<typename T>

    std::shared_ptr<T> GetObject()

    {

        auto typeId = GetTypeID<T>();
        auto factoryBase = factories[typeId];
        auto factory = std::static_pointer_cast<CFactory<T>>(factoryBase);
        return factory->GetObject();
    }

    /*
    Регистрация экземпляров
    */

    //Базовая реализация - регистрация функтора

    template<typename TInterface, typename ...TS>
    void RegisterFunctor(std::function<std::shared_ptr<TInterface>(std::shared_ptr<TS> ...ts)> functor)
    {
        factories[GetTypeID<TInterface>()] = std::make_shared<CFactory<TInterface>>([=] {return functor(GetObject<TS>()...); });
    }

    //Регистрация экземпляра объекта
    template<typename TInterface>
    void RegisterInstance(std::shared_ptr<TInterface> t)
    {
        factories[GetTypeID<TInterface>()] = std::make_shared<CFactory<TInterface>>([=] {return t; });
    }

    //Работаем с указателем на функцию
    template<typename TInterface, typename ...TS>
    void RegisterFunctor(std::shared_ptr<TInterface>(*functor)(std::shared_ptr<TS> ...ts))
    {
        RegisterFunctor(std::function<std::shared_ptr<TInterface>(std::shared_ptr<TS> ...ts)>(functor));
    }


    //Фабрика, которая будет вызывать необходимый конструктор для каждого экземпляра
    template<typename TInterface, typename TConcrete, typename ...TArguments>
    void RegisterFactory()
    {
        RegisterFunctor(
            std::function<std::shared_ptr<TInterface>(std::shared_ptr<TArguments> ...ts)>(
                [](std::shared_ptr<TArguments>...arguments) -> std::shared_ptr<TInterface>
        {
            return std::make_shared<TConcrete>(std::forward<std::shared_ptr<TArguments>>(arguments)...);
        }));

    }


    //Фабрика, которая будет возвращать один экземпляр  объекта  для каждого вызова
    template<typename TInterface, typename TConcrete, typename ...TArguments>
    void RegisterInstance()
    {
        RegisterInstance<TInterface>(std::make_shared<TConcrete>(GetObject<TArguments>()...));
    }
};

IOCContainer gContainer;

//Иницализация не нулевым значением


int IOCContainer::s_typeId = 121;


//Здесь, примеры различных интерфесов, классов

class ISomeObjX

{

public:

    virtual ~ISomeObjX() { }

    virtual void TestMethodX() = 0;

};



class ObjX : public ISomeObjX

{

public:

    ObjX()

    {

    }

    void TestMethodX()

    {

        std::cout << "This is ObjX" << std::endl;

    }

};

class IAmAThing

{

public:

    virtual ~IAmAThing() { }

    virtual void TestThis() = 0;

};



class IAmTheOtherThing

{

public:

    virtual ~IAmTheOtherThing() { }

    virtual void TheOtherTest() = 0;

};



class TheThing : public IAmAThing

{

public:

    TheThing()

    {

    }

    void TestThis()

    {

        std::cout << "A Thing" << std::endl;

    }

};

class TheOtherThing : public IAmTheOtherThing

{

    std::shared_ptr<IAmAThing> m_thing;

public:

    TheOtherThing(std::shared_ptr<IAmAThing> thing) :m_thing(thing)

    {

    }

    void TheOtherTest()

    {

        m_thing->TestThis();

    }

};


class IRepository
{
public:
    virtual string Save()=0;
};

class Repository : public IRepository
{
public:
    string Save()
    {
        return "I am saving data to Database.";
    }
};

class TextRepository : public IRepository
{
public:
    string Save()
    {
        return "I am saving data to TextFile.";
    }
};

class PurchaseBl
{
 private:
      IRepository* _repository;
 public:
     PurchaseBl(IRepository *repository)
    {
        _repository = repository;
    }

    string SavePurchaseOrder()
    {
        return _repository->Save();
    }
};


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

#endif // IOCCONTAINER_H
